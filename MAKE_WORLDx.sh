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

export FFvers=43.0b3
set -- `getopt v: "$@"`
[ $# -lt 1 ] && exit 1	# getopt failed
while [ $# -gt 0 ]
do
    case "$1" in
	-v)	export FFvers="$2"; shift;;
	--)	shift; break;;
	-*)
                echo >&2 \
		"usage: $0 [-v FFvers] (default: 43.0b3) ..."
		exit 1;;
	*)	break;;		# terminate while loop
    esac
    shift
done
export PATH=/opt/csw/gcc4/bin:/opt/csw/bin:/usr/gnu/bin:/usr/sfw/bin:/usr/bin:/usr/openwin/bin:/usr/ucb
/bin/echo ${FFvers}>/tmp/FFvers
export FFvers=`/bin/cat /tmp/FFvers`
export SRC=firefox-${FFvers}.source.tar.xz

if [ -e ${SRC} ];
then
   echo "SRC archive ${SRC} already there, nothing to do."
else
   wget https://ftp.mozilla.org/pub/firefox/releases/${FFvers}/source/${SRC} --no-check-certificate
fi

PATH=/usr/local/bin:$PATH gtar xvfJ ./${SRC}
mkdir -p ./log
if [ -e firefox-${FFvers} ];
then
   rm -f firefox-beta;ln -s firefox-${FFvers} firefox-beta
fi
gpatch -p1<./FF${FFvers}_OpenSolaris_x86_x64.patch&>log/000__GPATCH__FF${FFvers}_OpenSolaris_x86_x64__SXCE_snv-130-LOG.txt
cd firefox-${FFvers}
mkdir RELEASE_BUILD
cd RELEASE_BUILD
set&>../../log/001__ENV-LOG.txt
uname -a >>../../log/001__ENV-LOG.txt
bash ../x05CONFIGURE__NONDEBUG.sh&>../../log/002__CONFIGURE__FF${FFvers}_OpenSolaris_x86_x64-LOG.txt
gmake &>../../log/003__GMAKE__FF${FFvers}_OpenSolaris_x86_x64-LOG.txt
gmake install &>../../log/004__GMAKE__FF${FFvers}_OpenSolaris_x86_x64_INSTALL_AS_SUPERUSER-LOG.txt

diff -Nurb 000__VANILLA/firefox-beta/browser/installer/package-manifest.in 001__PORTED/firefox-beta/browser/installer/package-manifest.in
