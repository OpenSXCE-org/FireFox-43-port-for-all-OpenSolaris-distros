/*
 * Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
 * FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
 */
/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: sw=2 ts=8 et :
 */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/ipc/BrowserProcessSubThread.h"
#include "chrome/common/notification_service.h"

#if defined(OS_WIN)
#include <objbase.h>
#endif

namespace mozilla {
namespace ipc {

//
// BrowserProcessSubThread
//

// Friendly names for the well-known threads.
static const char* kBrowserThreadNames[BrowserProcessSubThread::ID_COUNT] = {
  "Gecko_IOThread",  // IO
//  "Chrome_FileThread",  // FILE
//  "Chrome_DBThread",  // DB
//  "Chrome_HistoryThread",  // HISTORY
  "Gecko_Background_X11Thread",  // BACKGROUND_X11
};

/* static */ StaticMutex BrowserProcessSubThread::sLock;
BrowserProcessSubThread* BrowserProcessSubThread::sBrowserThreads[ID_COUNT] = {
  nullptr,  // IO
//  nullptr,  // FILE
//  nullptr,  // DB
//  nullptr,  // HISTORY
  nullptr,  // BACKGROUND_X11
};

BrowserProcessSubThread::BrowserProcessSubThread(ID aId) :
  base::Thread(kBrowserThreadNames[aId]),
  mIdentifier(aId),
  mNotificationService(nullptr)
{
  StaticMutexAutoLock lock(sLock);
  DCHECK(aId >= 0 && aId < ID_COUNT);
  DCHECK(sBrowserThreads[aId] == nullptr);
  sBrowserThreads[aId] = this;
}

BrowserProcessSubThread::~BrowserProcessSubThread()
{
  Stop();
  {
    StaticMutexAutoLock lock(sLock);
    sBrowserThreads[mIdentifier] = nullptr;
  }

}

void
BrowserProcessSubThread::Init()
{
#if defined(OS_WIN)
  // Initializes the COM library on the current thread.
  CoInitialize(nullptr);
#endif
  mNotificationService = new NotificationService();
}

void
BrowserProcessSubThread::CleanUp()
{
  delete mNotificationService;
  mNotificationService = nullptr;

#if defined(OS_WIN)
  // Closes the COM library on the current thread. CoInitialize must
  // be balanced by a corresponding call to CoUninitialize.
  CoUninitialize();
#endif
}

// static
MessageLoop*
BrowserProcessSubThread::GetMessageLoop(ID aId)
{
  StaticMutexAutoLock lock(sLock);
  DCHECK(aId >= 0 && aId < ID_COUNT);

  if (sBrowserThreads[aId])
    return sBrowserThreads[aId]->message_loop();

  return nullptr;
}

} // namespace ipc
} // namespace mozilla
