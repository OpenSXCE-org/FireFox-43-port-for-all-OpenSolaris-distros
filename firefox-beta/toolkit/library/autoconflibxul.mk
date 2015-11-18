#*
#* CDDL HEADER START
#*
#* The contents of this file are subject to the terms of the
#* Common Development and Distribution License, Version 1.0 only
#* (the "License").  You may not use this file except in compliance
#* with the License.
#*
#* You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
#* or http://www.opensolaris.org/os/licensing.
#* See the License for the specific language governing permissions
#* and limitations under the License.
#*
#* When distributing Covered Code, include this CDDL HEADER in each
#* file and include the License file at usr/src/OPENSOLARIS.LICENSE.
#* If applicable, add the following below this CDDL HEADER, with the
#* fields enclosed by brackets "[]" replaced with your own identifying
#* information: Portions Copyright [yyyy] [name of copyright owner]
#*
#* CDDL HEADER END
#*
#*
#* Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
#* FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
#*

//MKSHLIB = /usr/bin/gld $(DSO_PIC_CFLAGS) $(DSO_LDOPTS) -h $(DSO_SONAME) -o $@
//OS_LDFLAGS = -lpthread	 -z text -z ignore -R,'$$ORIGIN:$$ORIGIN/..' -z lazyload -z combreloc -z muldefs
MKSHLIB = /usr/bin/env LD_ALTEXEC=/usr/bin/gld PATH=/usr/gcc/4.5/bin:/usr/gcc/4.7/bin:/usr/gcc/4.8/bin:$PATH $(CXX) $(CXXFLAGS) $(DSO_PIC_CFLAGS) $(DSO_LDOPTS) -Wl,-h,$(DSO_SONAME) -o $@
