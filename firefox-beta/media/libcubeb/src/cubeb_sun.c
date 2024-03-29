/*
 * Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
 * FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
 */
/*
 * Copyright (c) 2013 Ginn Chen <ginnchen@gmail.com>
 *
 * This program is made available under an ISC-style license.  See the
 * accompanying file LICENSE for details.
 */
#include <poll.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/audio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stropts.h>
#include "cubeb/cubeb.h"
#include "cubeb-internal.h"

/* Macros copied from audio_oss.h */
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (C) 4Front Technologies 1996-2008.
 *
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
#define OSSIOCPARM_MASK 0x1fff          /* parameters must be < 8192 bytes */
#define OSSIOC_VOID     0x00000000      /* no parameters */
#define OSSIOC_OUT      0x20000000      /* copy out parameters */
#define OSSIOC_IN       0x40000000      /* copy in parameters */
#define OSSIOC_INOUT    (OSSIOC_IN|OSSIOC_OUT)
#define OSSIOC_SZ(t)    ((sizeof (t) & OSSIOCPARM_MASK) << 16)
#define __OSSIO(x, y)           ((int)(OSSIOC_VOID|(x<<8)|y))
#define __OSSIOR(x, y, t)       ((int)(OSSIOC_OUT|OSSIOC_SZ(t)|(x<<8)|y))
#define __OSSIOWR(x, y, t)      ((int)(OSSIOC_INOUT|OSSIOC_SZ(t)|(x<<8)|y))
#define SNDCTL_DSP_SPEED        __OSSIOWR('P', 2, int)
#define SNDCTL_DSP_CHANNELS     __OSSIOWR('P', 6, int)
#define SNDCTL_DSP_SETFMT       __OSSIOWR('P', 5, int)  /* Selects ONE fmt */
#define SNDCTL_DSP_GETODELAY    __OSSIOR('P', 23, int)
#define SNDCTL_DSP_HALT_OUTPUT  __OSSIO('P', 34)
#define AFMT_S16_LE     0x00000010
#define AFMT_S16_BE     0x00000020

#if defined(WORDS_BIGENDIAN) || defined(__BIG_ENDIAN__)
#define AFMT_S16_NE    AFMT_S16_BE
#else
#define AFMT_S16_NE    AFMT_S16_LE
#endif

#define DEFAULT_AUDIO_DEVICE "/dev/audio"
#define DEFAULT_DSP_DEVICE   "/dev/dsp"

#define BUF_SIZE_MS 10

#if defined(CUBEB_SUNAUDIO_DEBUG)
#define DPR(...) fprintf(stderr, __VA_ARGS__);
#else
#define DPR(...) do {} while(0)
#endif

static struct cubeb_ops const sunaudio_ops;

struct cubeb {
  struct cubeb_ops const * ops;
};

struct cubeb_stream {
  cubeb * context;
  pthread_t th;			  /* to run real-time audio i/o */
  pthread_mutex_t mutex;	  /* protects fd and frm_played */
  int fd;			  /* link us to sunaudio */
  int active;			  /* cubec_start() called */
  int conv;			  /* need float->s16 conversion */
  int using_oss;
  unsigned char *buf;		  /* data is prepared here */
  unsigned int rate;
  unsigned int n_channles;
  unsigned int bytes_per_ch;
  unsigned int n_frm;
  unsigned int buffer_size;
  int64_t frm_played;
  cubeb_data_callback data_cb;    /* cb to preapare data */
  cubeb_state_callback state_cb;  /* cb to notify about state changes */
  void *arg;			  /* user arg to {data,state}_cb */
};

static void
float_to_s16(void *ptr, long nsamp)
{
  int16_t *dst = ptr;
  float *src = ptr;

  while (nsamp-- > 0)
    *(dst++) = *(src++) * 32767;
}

static void *
sunaudio_mainloop(void *arg)
{
  struct cubeb_stream *s = arg;
  int state;

  DPR("sunaudio_mainloop()\n");

  s->state_cb(s, s->arg, CUBEB_STATE_STARTED);

  pthread_mutex_lock(&s->mutex);
  DPR("sunaudio_mainloop(), started\n");

  for (;;) {
    if (!s->active) {
      DPR("sunaudio_mainloop() stopped\n");
      state = CUBEB_STATE_STOPPED;
      break;
    }

    if (!s->using_oss) {
      audio_info_t info;
      ioctl(s->fd, AUDIO_GETINFO, &info);
      if (s->frm_played > info.play.samples + 3 * s->n_frm) {
        pthread_mutex_unlock(&s->mutex);
        struct timespec ts = {0, 10000}; // 10 ms
        nanosleep(&ts, NULL);
        pthread_mutex_lock(&s->mutex);
        continue;
      }
    }

    pthread_mutex_unlock(&s->mutex);
    unsigned int got = s->data_cb(s, s->arg, s->buf, s->n_frm);
    DPR("sunaudio_mainloop() ask %d got %d\n", s->n_frm, got);
    pthread_mutex_lock(&s->mutex);

    if (got < 0) {
      DPR("sunaudio_mainloop() cb err\n");
      state = CUBEB_STATE_ERROR;
      break;
    }

    if (s->conv) {
      float_to_s16(s->buf, got * s->n_channles);
    }

    unsigned int avail = got * 2 * s->n_channles; // coverted to s16
    unsigned int pos = 0;

    while (avail > 0 && s->active) {
      int written = write(s->fd, s->buf + pos, avail);
      if (written == -1) {
        if (errno != EINTR && errno != EWOULDBLOCK) {
          DPR("sunaudio_mainloop() write err\n");
          state = CUBEB_STATE_ERROR;
          break;
        }
        pthread_mutex_unlock(&s->mutex);
        struct timespec ts = {0, 10000}; // 10 ms
        nanosleep(&ts, NULL);
        pthread_mutex_lock(&s->mutex);
      } else {
        pos += written;
        DPR("sunaudio_mainloop() write %d pos %d\n", written, pos);
        s->frm_played += written / 2 / s->n_channles;
        avail -= written;
      }
    }

    if ((got  < s->n_frm)) {
      DPR("sunaudio_mainloop() drained\n");
      state = CUBEB_STATE_DRAINED;
      break;
    }
  }

  pthread_mutex_unlock(&s->mutex);
  s->state_cb(s, s->arg, state);

  return NULL;
}

/*static*/ int
sunaudio_init(cubeb **context, char const *context_name)
{
  DPR("sunaudio_init(%s)\n", context_name);
  *context = malloc(sizeof(*context));
  (*context)->ops = &sunaudio_ops;
  (void)context_name;
  return CUBEB_OK;
}

static char const *
sunaudio_get_backend_id(cubeb *context)
{
  return "sunaudio";
}

static void
sunaudio_destroy(cubeb *context)
{
  DPR("sunaudio_destroy()\n");
  free(context);
}

static int
sunaudio_stream_init(cubeb *context,
                  cubeb_stream **stream,
                  char const *stream_name,
                  cubeb_stream_params stream_params, unsigned int latency,
                  cubeb_data_callback data_callback,
                  cubeb_state_callback state_callback,
                  void *user_ptr)
{
  struct cubeb_stream *s;
  DPR("sunaudio_stream_init(%s)\n", stream_name);
  size_t size;

  s = malloc(sizeof(struct cubeb_stream));
  if (s == NULL)
    return CUBEB_ERROR;
  s->context = context;

  // If UTAUDIODEV is set, use it with Sun Audio interface
  char * sa_device_name = getenv("UTAUDIODEV");
  char * dsp_device_name = NULL;
  if (!sa_device_name) {
    dsp_device_name = getenv("AUDIODSP");
    if (!dsp_device_name) {
      dsp_device_name = DEFAULT_DSP_DEVICE;
    }
    sa_device_name = getenv("AUDIODEV");
    if (!sa_device_name) {
      sa_device_name = DEFAULT_AUDIO_DEVICE;
    }
  }

  s->using_oss = 0;
  // Try to use OSS if available
  if (dsp_device_name) {
    s->fd = open(dsp_device_name, O_WRONLY | O_NONBLOCK);
    if (s->fd >= 0) {
      s->using_oss = 1;
    }
  }

  // Try Sun Audio
  if (!s->using_oss) {
    s->fd = open(sa_device_name, O_WRONLY | O_NONBLOCK);
  }

  if (s->fd < 0) {
    free(s);
    DPR("sunaudio_stream_init(), open() failed\n");
    return CUBEB_ERROR;
  }

  if (s->using_oss) {
    if (ioctl(s->fd, SNDCTL_DSP_SPEED, &stream_params.rate) < 0) {
      DPR("ioctl SNDCTL_DSP_SPEED failed.\n");
      close(s->fd);
      free(s);
      return CUBEB_ERROR_INVALID_FORMAT;
    }

    if (ioctl(s->fd, SNDCTL_DSP_CHANNELS, &stream_params.channels) < 0) {
      DPR("ioctl SNDCTL_DSP_CHANNELS failed.\n");
      close(s->fd);
      free(s);
      return CUBEB_ERROR_INVALID_FORMAT;
    }

    int format = AFMT_S16_NE;
    if (ioctl(s->fd, SNDCTL_DSP_SETFMT, &format) < 0) {
      DPR("ioctl SNDCTL_DSP_SETFMT failed.\n");
      close(s->fd);
      free(s);
      return CUBEB_ERROR_INVALID_FORMAT;
    }
  } else {
    audio_info_t audio_info;
    AUDIO_INITINFO(&audio_info)
    audio_info.play.sample_rate = stream_params.rate;
    audio_info.play.channels = stream_params.channels;
    audio_info.play.encoding = AUDIO_ENCODING_LINEAR;
    audio_info.play.precision = 16;
    if (ioctl(s->fd, AUDIO_SETINFO, &audio_info) == -1) {
      DPR("ioctl AUDIO_SETINFO failed.\n");
      close(s->fd);
      free(s);
      return CUBEB_ERROR_INVALID_FORMAT;
    }
  }

  s->conv = 0;
  switch (stream_params.format) {
    case CUBEB_SAMPLE_S16NE:
      s->bytes_per_ch = 2;
      break;
    case CUBEB_SAMPLE_FLOAT32NE:
      s->bytes_per_ch = 4;
      s->conv = 1;
      break;
    default:
      DPR("sunaudio_stream_init() unsupported format\n");
      close(s->fd);
      free(s);
      return CUBEB_ERROR_INVALID_FORMAT;
  }

  s->active = 0;
  s->rate = stream_params.rate;
  s->n_channles = stream_params.channels;
  s->data_cb = data_callback;
  s->state_cb = state_callback;
  s->arg = user_ptr;
  if (pthread_mutex_init(&s->mutex, NULL) != 0) {
    free(s);
    return CUBEB_ERROR;
  }
  s->frm_played = 0;
  s->n_frm = s->rate * BUF_SIZE_MS / 1000;
  s->buffer_size = s->bytes_per_ch * s->n_channles * s->n_frm;
  s->buf = malloc(s->buffer_size);
  if (s->buf == NULL) {
    close(s->fd);
    free(s);
    return CUBEB_ERROR;
  }

  *stream = s;
  DPR("sunaudio_stream_init() end, ok\n");
  return CUBEB_OK;
}

static void
sunaudio_stream_destroy(cubeb_stream *s)
{
  DPR("sunaudio_stream_destroy()\n");
  if (s->fd > 0) {
    // Flush buffer
    if (s->using_oss) {
      ioctl(s->fd, SNDCTL_DSP_HALT_OUTPUT);
    } else {
      ioctl(s->fd, I_FLUSH);
    }
    close(s->fd);
  }
  free(s->buf);
  free(s);
}

static int
sunaudio_stream_start(cubeb_stream *s)
{
  int err;

  DPR("sunaudio_stream_start()\n");
  s->active = 1;
  err = pthread_create(&s->th, NULL, sunaudio_mainloop, s);
  if (err) {
    s->active = 0;
    return CUBEB_ERROR;
  }
  return CUBEB_OK;
}

static int
sunaudio_stream_stop(cubeb_stream *s)
{
  void *dummy;

  DPR("sunaudio_stream_stop()\n");
  if (s->active) {
    s->active = 0;
    pthread_join(s->th, &dummy);
  }
  return CUBEB_OK;
}

static int
sunaudio_stream_get_position(cubeb_stream *s, uint64_t *p)
{
  int rv = CUBEB_OK;
  pthread_mutex_lock(&s->mutex);
  if (s->active && s->fd > 0) {
    if (s->using_oss) {
      int delay;
      ioctl(s->fd, SNDCTL_DSP_GETODELAY, &delay);
      int64_t t = s->frm_played - delay / s->n_channles / 2;
      if (t < 0) {
        *p = 0;
      } else {
        *p = t;
      }
    } else {
      audio_info_t info;
      ioctl(s->fd, AUDIO_GETINFO, &info);
      *p = info.play.samples;
    }
    DPR("sunaudio_stream_get_position() %lld\n", *p);
  } else {
    rv = CUBEB_ERROR;
  }
  pthread_mutex_unlock(&s->mutex);
  return rv;
}

static struct cubeb_ops const sunaudio_ops = {
  .init = sunaudio_init,
  .get_backend_id = sunaudio_get_backend_id,
  .destroy = sunaudio_destroy,
  .stream_init = sunaudio_stream_init,
  .stream_destroy = sunaudio_stream_destroy,
  .stream_start = sunaudio_stream_start,
  .stream_stop = sunaudio_stream_stop,
  .stream_get_position = sunaudio_stream_get_position
};
