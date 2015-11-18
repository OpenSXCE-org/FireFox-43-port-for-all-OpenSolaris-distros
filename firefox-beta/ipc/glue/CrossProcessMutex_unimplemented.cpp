/*
 * Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
 * FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
 */
/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "CrossProcessMutex.h"

#include "nsDebug.h"

namespace mozilla {

CrossProcessMutex::CrossProcessMutex(const char*)
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform.");
}

CrossProcessMutex::CrossProcessMutex(CrossProcessMutexHandle)
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform.");
}

CrossProcessMutex::~CrossProcessMutex()
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform - woah! We should've aborted by now!");
}

void
CrossProcessMutex::Lock()
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform - woah! We should've aborted by now!");
}

void
CrossProcessMutex::Unlock()
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform - woah! We should've aborted by now!");
}

CrossProcessMutexHandle
CrossProcessMutex::ShareToProcess(base::ProcessId aTargetPid)
{
  NS_RUNTIMEABORT("Cross-process mutices not allowed on this platform - woah! We should've aborted by now!");
}

}
