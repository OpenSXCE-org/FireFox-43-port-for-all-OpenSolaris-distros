#!/bin/bash
#
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

export PATH=/opt/csw/gcc4/bin:/opt/csw/bin:/usr/gnu/bin:/usr/sfw/bin:/usr/bin:/usr/openwin/bin:/usr/ucb
export FFvers=`/bin/cat /tmp/FFvers`

cd firefox-${FFvers}/RELEASE_BUILD
echo "\n\ngmake install can only be run as superuser via sudo."
echo "Please authenticate yourself ... :\n"
echo "(you may need to add the following line with visudo to /etc/sudoers and rerun ./MAKE_INSTALL.sh:)\n"
echo "yourusername	ALL=(ALL) NOPASSWD: ALL\n"
mkdir -p ../../log
sudo -u root gmake install |tee ../../log/004__GMAKE__FF${FFvers}_OpenSolaris_x86_x64_INSTALL_AS_SUPERUSER-LOG.txt

