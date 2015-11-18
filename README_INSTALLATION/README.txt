DONATION: FireFox43.0b3 pkg and src in GitHub unleashed  (initial version x86/x64 only, SPARC next week [if wanted], Illumos-x86/x64 kernel patch for flash-plugin support also next week if wanted]*, also DRM/KMS for Intel can* be released any time, also my openXsun patches and a SPARC-OpenIndiana)

 * := unless some so far unknown non-contributor that one never saw here for months suddenly opens his western bigmouth and urges me away once again.


Martin B. aka OpenSXCE.org (_HE_!) herewith **donates** 6 hyper-fulltime weeks of on average 15 unpaid hours per day (no joke, btw including weekends) to the OpenSXCE/DilOS/Illumos/OpenSolaris/Sun-Solaris/Oracle-Solaris/OpenIndiana/Hipster (and all other OpenSolaris based distros') communities.

Originally he wanted to publish this stuff in April (at the time for FireFox37 which he then after certain events only published as binary package, which can still be obtained from http://opensxce.org/.FF/37/i386/). But testing the water faced him with egoistic GIMME GIMME MOAR _____demands*_____, rather than any noticable support, like last time when he published OpenSXCE, like last time when he had created the SPARC-OpenIndiana LiveDVD, like last time when he released SPARC-Xorg in 2006, like last time when he published the Qemu port to SPARC-Solaris hosts in 2006, like last time when [...]
 
Folks called him a "capitalist", only because he dared to ask for some (so called) "donations".
Look how foolish this is:  A capitalist is somebody who does something for a profit. Profit would mean getting more - (a lot!) more - than having invested, rather than getting back maybe 5% of the actual costs (electricity, computer, hdd, food, powerdrinks, room, all bills in Germany are extremely high), plus additionally getting nothing for the actual time spent nor any other reward for the lack of income during all this time spent. Even a toilet-cleaner is rich in contrast, because he does get something for his time.

Who doesn't know (or understand) the difference between M.B. (who spent more than ten [probably more than twenty] thousand unpaid hours on OpenSolaris community related work since 2005 [and at Blastwave since 2003) should read: https://en.wikipedia.org/wiki/Capitalist_mode_of_production_%28Marxist_theory%29

"Anti-Social Capitalist" ??? 
--->> That's not him who loves OpenSolaris so much that he ruined his career.
NOPE: That's most readers of this mailing list, who only show up once in 2 years to make some useless one-liner comment.
And if they do, then only to criticize those few real OpenIndiana contributors that are really working on this (Hipster team!).
Yesterday there were such comments again (like "Hipster is going nowhere" or "write up instructions").
Thos instructions are on the openindiana page for years. But only those truly interested in contributing something would come across them, rather than some show-offs and time-wasters who can only blame and complain (the referred post was only a single example, other mailing list members are much worse).
True Anti-Social beings are those biz owners or well paid biz-admins who deploy OI countless times for commercial installations while keeping all the 1000's of Dollars for themselves, rather than giving anything back to the Hipster team.
I must say: It is a mistake that those few working on Hipster are giving it away for free.

Free software - the meaning has to be interpreted as open-src, but not necessarily free of charge all the time.
Especially not the binary iso's! Just take this hint as a well intended recommendation.
1000's are exploiting you, Hipster (rgds. to Rostov).

NetBSD Is Paying For DRM With KMS/GEM
http://www.phoronix.com/scan.php?page=news_item&px=MTMxMzg

But from me you expect that I release everything always for free, including my therefore (!) so far unpublished KMS/DRM (now upgraded to Oracle's better version)?
It fits well to the rest of western hypocrisy to always point the finger at others.
Overpaid folks who repeatedly stated that they have no time to contribute anything to OpenSolaris (because it's apparently not important enough to them, so they rather take the money elsewhere) BLAME me for being an "anti-social capitalist", only because I do contribute something for one and a half decades, but find it hard to survive?
That's like Obama saying ISIS is an enemy of the West (rather than its own creation and useful tool [proof in Part II below, simply listen to McCain's and H.Clinton's own statements on video tape]).


{
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# # # Part I.) TECHNICAL SCOPE: # # # # # # # # # # #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 
Unlike others who 1:1 either cloned && paste-used Sun/Oracle's Studio-diffs or NetBSD's Firefox gcc-port (or rather: tried hard ...), I developed this patch from scratch and used the former only as reference, where really required (e.g. where the build terminated or - felt lightyears later [when the build would finally succeed for the first time!!!] - in cases where some functionality was missing or broken, and where it was more convenient to look what's already there, although in most cases this was the easy part either way), thanks to Rich Teer's book "Solaris Systems programming", the famous Solaris series including "Solaris Internals" and Joerg Schilling's OpenSolaris book (available in German language) and of course the according man pages and system headers.

Before that I emulated being under the most-supported (Non-MacOS X) Firefox-UNIX platform: LinUX, by simply enabling all LinUX related preprocessor #ifdef directives:

by putting:

#elif defined(__sun__) || defined(__sun)
#define OS_LINUX 1

into ipc/chromium/src/build/build_config.h

and such as by putting:

    elif CONFIG['OS_ARCH'] == 'SunOS':
       os_solaris = 1

into ipc/chromium/moz.build.

After a while I found out about and tracked all the problems and to get an estimate how much trouble is ahead continued with -k or touch. Many open tabs, vi sessions, log files, certain suffixes I added to renamed files etc were involved.
Then I fixed all these invalid function calls. Then Did all the same for OpenBSD #ifdefs etc, in the hope this might shed some light into the flash-plugin under gcc built FF saga (the flash-plugin support on Illumos patched kernels is yet another topic, and affects all also Studio-compiled versions, I developed a workaround for OpenSXCE already in 2013 but never released it because Illumos thinks that I'm not valuable for their code base, so that was their idea, and that alone explains why I no longer wanted to publish the src, the rest depends on THEIR attitude, because my attitude has always been to play fair, but that was probably naive in the first place). I did that because I didn't test LinUX nor any BSD for a decade and always thought that those would not have flash-plugin problems with gcc (now after having isolated the problem, I'm not so sure anymore).

Arg, well, by doing so I used to grep the entire src hierarchy several times per 10 minutes, for days and weeks, and from the third */*/* on exceeded even g-grep's variable arguments list limits (needed to split it down into */*/[a-m]* and */*/[n-z]* etc [into up to five regex groups per each of the more populated levels]).
... and found out that some #ifdefs were forgotten in the Sun- provided and NetBSD patches.
But fixing them still didn't solve the main goal: What the hell caused flash-plugins from 9.x to 10. to crash with error A) and 11.x even with Error A) and B)???
I almost grew into a senior citizen with gray hair from that (but fortunately I don't have much hair anymore since I started with OpenSolaris). It was like what one would have called a war, before history reminded us how REAL WAR outside looks and feels. So this all here is rather fun.
All this was done on my poor Celeron G530 2.4GHz inside snv_130 (for optimum inter-distro compatibility) running in vbox, wait a pain - waaaaaiiiiiiiting ...

But before indeed reaching the luxury of messing with a non-working flash first one needed to actually get FF built!!!!!

But until I finally achieved this March ran through and then it was the end of April.
All daily/nightly/weekly/weekendly fulltime pain and unpaid!
To give an estimate: The FF git contains so many _file_ objects:

$ find firefox-43.0b3|wc -l      
138070

If on average each file has 1000 lines, then:

$ bc
138070*1000
138070000

voila - 138 MILLION lines of code.
And even if too many files are shorter that 1000 lines and if it "only" totals to 50 million lines: Happy reading!
In the past one said oh - WOW, this or that OS has a few million(s) lines of code.
Not so long ago  ...
Indeed extremely impressive what the mozilla.org team is achieving!!
(But are they doing this for fun or in the frame of industry-paid jobs??)

To shorten things up a bit, here the major difficulties and accordingly their references to related posts by others and followed by the solution or at least workaround:

/* {0.}.libxul linkage
{1.} plugin (kernel)
{2.} plugin (ggc-FF)
{3.} contextMenu
{4.} langpacks */

(problem/references/solution)

{0.}.libxul linkage
###PROBLEM:
Success was at first mostly prevented by the libxul linkage problem.
Which was probably the major stopper for most of all those who tried to get newer FireFox 30++ versions at least somehow at all compiled and especially linked to the finish line.
Because even with Studio - only the Sun-/Oracle diffs patched into FF24 were still easily buildable on snv_130 or also on Illumos (with include files derived from svc_147, which is pretty outdated compared to what Oracle meanwhile uses). Sun-Oracle's FF31 diffs patched into FF31 - no easy way. Not even with Studio 12.4. And for gcc Sun's patches are more a disadvantage than any help.
Also: Of course only a gcc built FF is what I wanted ;) But one which can play the flash-plugin (at least version 10 [as I thought at the time]). Meanwhile all this is fixed and solved like a charme.

###REFERENCES:
Oh, I see that one of the few others who ever really invested their own life and 1000's of hours of their private unpaid time to rescue OpenSolaris also ran into the same problem:

[oi-dev] NS_COM_GLUE and upstream FF patches
http://openindiana.org/pipermail/oi-dev/2013-December/002962.html

This describes the problem you would end up with forever.
Not exactly this, but variations of it.
We are not dealing with some usual trivial missing symbols here, but with pointers to pointers to pointers to functions dealing with object, implemented and various files, but never there where the output would suggest, but in different files.
While only one unresolved symbol would be shown per linker run, if it didn't exist, the next one would follow, and so on forever (literally).
It is samething that can keep you busy for a year. Especially troublesome are x86 assembly files for the media codecs, such as in 

media/libvpx/vpx_config_x86-linux-gcc.asm

It is a complex gcc visibility issue caused by the fact that Solaris still needs to default to its proprietary linker and even the very latest binutils still don't provide a fully functional gld or bfld or gold even though the problem was known for centuries.


Googling brings:
"gcc visibility error hidden firefox libxul.so"
https://www.google.de/search?q=gcc+visibility+error+hidden+gcc+firefox+li&ie=utf-8&oe=utf-8&gws_rd=cr&ei=kclKVtiIMcH0asTCl9gF#q=gcc+visibility+error+hidden+gcc+firefox+libxul.so


and only for "gcc visibility error hidden" (in both cases omit the double quotes, obviously) :
https://www.google.de/search?q=gcc+visibility+error+hidden+gcc+firefox+li&ie=utf-8&oe=utf-8&gws_rd=cr&ei=kclKVtiIMcH0asTCl9gF

You can add the most verbose output to CFLAGS and LDFLAGS, you can globally force brute-force visibility on or off in configure.in/configure or directly in:

config/gcc_hidden.h
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Begin all files as hidden visibility */
#pragma GCC visibility push(hidden)

... you can run a hundred manual compile or link commands: One ends staying hopeless for some while.

The point is, that the Solaris ld does not fully understand gcc's visibility logic.
HENCE the obvious solution would be to link FF with gnu-ld or bfld or gold, right?!
YEP, and I see that I'm not the only one who had that idea. But as written before: gld does not properly function on Solaris.
Which I find unbelievable. Maybe I will look myself into more details, as soon as time and $$$ial situation permits (if nobody helps, I must once again instantly stop all efforts and first job somewhere, so DO NOT COMPLAIN about unpublished src or delays, delays, deferrals!).

LD_ALTEXEC=/usr/bin/gld would instruct /usr/bin/ld to forward all linking requests by the gcc/g++ frontent to gld, rather than linking the objects itself.
But if you would attempt to set them globally your FF (or other larger project) build would not come all that far. The different command syntax for calling linking scripts is not the problem, although you might have to first deal with it.

Wrong compiler-calling linker and passing args for calling mapfiles:
-Wl,-M, .. results in:

(here during a configure run)

gld:/opt/csw/lib/gcc/i386-pc-solaris2.10/4.9.2/../../../libgcc-unwind.map: file format not recognized; treating as linker script
gld:/opt/csw/lib/gcc/i386-pc-solaris2.10/4.9.2/../../../libgcc-unwind.map:1: syntax error
configure: failed program was:

#line 3724 "configure"
#include "confdefs.h"

int main(){return(0);}
configure: error: installation or configuration problem: C++ compiler cannot create executables.

Or you may get: gld: unrecognized option '-Bdirect'
But all that's only cosmetics (wrong flags) and therefore no deal.

Next possible issue, although it also appears to involve broken gcc/gld visibility:

I'm in this case explicitly _not_ referring to:

Subject: 	[Bug ld/14852] gnu ld can't use a library linked via solaris ld, if that library uses a library linked with GNU ld

https://lists.gnu.org/archive/html/bug-binutils/2012-11/msg00049.html

nor 

https://lists.gnu.org/archive/html/bug-binutils/2012-11/msg00050.html

But the true problem is much worse and much older,
a set of age old real bugs in binutils' gld:

Timewarp 15 years back:
Re: ld broken on Solaris 8
https://sourceware.org/ml/binutils/2001-05/msg00173.html
http://www.sourceware.org/ml/binutils/2000-04/msg00333.html

But here we come already a bit closer (and look at the date!) :

https://sourceware.org/bugzilla/show_bug.cgi?id=1021

 Matthias Kurz 2005-06-17 09:41:56 UTC

Building mozilla under Solaris 10 fails. When g++ (3.4.4) tries to link regxpcom
it bombs out with the following errors:
mozilla/dist/bin/libnspr4.so: undefined reference to `fcntl@SUNW_0.9'
mozilla/dist/bin/libnspr4.so: undefined reference to `dlsym@SUNW_0.7'
mozilla/dist/bin/libnspr4.so: undefined reference to `pthread_join@SUNW_0.9'
mozilla/dist/bin/libnspr4.so: undefined reference to `select@SUNW_1.2'
mozilla/dist/bin/libnspr4.so: undefined reference to `rw_unlock@SUNW_0.9'
mozilla/dist/bin/libnspr4.so: undefined reference to `pthread_attr_destroy@SUNW_
0.9'
mozilla/dist/bin/libnspr4.so: undefined reference to `dlerror@SUNW_0.7'
.. and so on

I saw similiar reports from other users (google, see also 
http://sourceware.org/ml/binutils/2005-06/msg00466.html).

I need to build with GNU binutils because i use OpenPKG and it is the default there.


   (mk)



Whatever, this topic goes under in this long difficult to read ascii file.
And it is worth being discussed in a dedicated discussion thread @binutils and/or illumos.
To keep it short: The key to success was to link everything with Sun-ld, _except_ libxul.so 

And to implement it properly without user interaction this resulted in:

+++ 001__PORTED/firefox-beta/toolkit/library/autoconflibxul.mk  2015-11-11 04:12:33.031527320 +0100
@@ -0,0 +1,29 @@
+#*
+#* CDDL HEADER START
+#*
+#* The contents of this file are subject to the terms of the
+#* Common Development and Distribution License, Version 1.0 only
+#* (the "License").  You may not use this file except in compliance
+#* with the License.
+#*
+#* You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
+#* or http://www.opensolaris.org/os/licensing.
+#* See the License for the specific language governing permissions
+#* and limitations under the License.
+#*
+#* When distributing Covered Code, include this CDDL HEADER in each
+#* file and include the License file at usr/src/OPENSOLARIS.LICENSE.
+#* If applicable, add the following below this CDDL HEADER, with the
+#* fields enclosed by brackets "[]" replaced with your own identifying
+#* information: Portions Copyright [yyyy] [name of copyright owner]
+#*
+#* CDDL HEADER END
+#*
+#*
+#* Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
+#* FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
+#*
+
+//MKSHLIB = /usr/bin/gld $(DSO_PIC_CFLAGS) $(DSO_LDOPTS) -h $(DSO_SONAME) -o $@
+//OS_LDFLAGS = -lpthread        -z text -z ignore -R,'$$ORIGIN:$$ORIGIN/..' -z lazyload -z combreloc -z muldefs
+MKSHLIB = /usr/bin/env LD_ALTEXEC=/usr/bin/gld PATH=/usr/gcc/4.5/bin:/usr/gcc/4.7/bin:/usr/gcc/4.8/bin:$PATH $(CXX) $(CXXFLAGS) $(DSO_PIC_CFLAGS) $(DSO_LDOPTS) -Wl,-h,$(DSO_SONAME) -o $@


and


diff -Nurb 000__VANILLA/firefox-beta/toolkit/library/Makefile.in 001__PORTED/firefox-beta/toolkit/library/Makefile.in
--- 000__VANILLA/firefox-beta/toolkit/library/Makefile.in       2015-11-09 23:56:20.000000000 +0100
+++ 001__PORTED/firefox-beta/toolkit/library/Makefile.in        2015-11-11 04:23:35.762542329 +0100
@@ -1,8 +1,14 @@
+#*
+#* Copyright 2015 OpenSXCE.org Martin Bochnig <opensxce@mail.ru>
+#* FireFox 20/30/40++ gcc4.x port with Flash support for OpenSolaris++ x86/x64
+#*
+
 # This Source Code Form is subject to the terms of the Mozilla Public
 # License, v. 2.0. If a copy of the MPL was not distributed with this file,
 # You can obtain one at http://mozilla.org/MPL/2.0/.

 include $(topsrcdir)/toolkit/library/libxul.mk
+include $(topsrcdir)/toolkit/library/autoconflibxul.mk

 include $(topsrcdir)/config/config.mk



This locally overrides values imported by included and inter-included config files, although it took several hours before it was actually clear what is what and relevant versus not, example:



$ grep -n MKSHLIB ../config/*
../config/config.mk:627:EXPAND_MKSHLIB_ARGS = --uselist
../config/config.mk:629:EXPAND_MKSHLIB_ARGS += --symbol-order $(SYMBOL_ORDER)
../config/config.mk:631:EXPAND_MKSHLIB = $(EXPAND_LIBS_EXEC) $(EXPAND_MKSHLIB_ARGS) -- $(MKSHLIB)
../config/rules.mk:162:ifdef MKSHLIB
../config/rules.mk:165:MKSHLIB			= $(MKCSHLIB)
../config/rules.mk:170:endif # MKSHLIB
../config/rules.mk:445:MKSHLIB  += -Wl,+eNSGetModule -Wl,+eerrno
../config/rules.mk:448:MKSHLIB  += -Wl,+e_shlInit
../config/rules.mk:459:MKSHLIB += -bE:$(MOZILLA_DIR)/build/unix/aix.exp -bnoexpall
../config/rules.mk:834:	$(EXPAND_MKSHLIB) $(SHLIB_LDSTARTFILE) $(OBJS) $(SUB_SHLOBJS) $(DTRACE_PROBE_OBJ) $(MOZILLA_PROBE_LIBS) $(RESFILE) $(LDFLAGS) $(WRAP_LDFLAGS) $(STATIC_LIBS) $(SHARED_LIBS) $(EXTRA_DSO_LDOPTS) $(MOZ_GLUE_LDFLAGS) $(EXTRA_LIBS) $(OS_LIBS) $(SHLIB_LDENDFILE)
../config/rules.mk:837:	$(EXPAND_MKSHLIB) $(SHLIB_LDSTARTFILE) $(OBJS) $(SUB_SHLOBJS) $(RESFILE) $(LDFLAGS) $(WRAP_LDFLAGS) $(STATIC_LIBS) $(SHARED_LIBS) $(EXTRA_DSO_LDOPTS) $(MOZ_GLUE_LDFLAGS) $(EXTRA_LIBS) $(OS_LIBS) $(SHLIB_LDENDFILE)


{1.} plugin (kernel)
Exactly like all the other goodies (initial version x86/x64 only, SPARC next week [if wanted], Illumos-x86/x64 kernel patch for flash-plugin support also next week if wanted]*, also DRM/KMS (now upgraded to Oracle's better version) for Intel can* be released any time, also my openXsun patches and a SPARC-OpenIndiana, also my studio2gcc userland wrapper enhanced cw [enabling me to build an almost vanilla Oracle-userland-Sol12.latest without having to correct all their studio-only CFLAGS, CXXFLAGS and LDFLAGS pollution every time {I say pollution not in disrespect of Studio 12.4, but because in the original design userland was compiler-clean, and only carelessness by Oracle employees caused all this}])
... this can or could be published anytime.
BUT: Only if the "community" behaves. Otherwise I regret that I shared this FF43 patches and insides with you.

{2.} plugin (ggc-FF)
###problem: As you all know (because it was reported several times on this list)  ...:

Flash plugin 9.x and 10.x would still function, but not 11.x
(at different levels of modifications by default not even the older plugins worked on gcc4.[5-9] compiled firefox, I tested them all)

Error with 9.x and 10.x:
Not GTK2 toolkit (got 0).


Error with 11.x: 
bash-4.0$ [NPAPI 21961] WARNING: pipe error: Broken pipe: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/RELEASE/firefox-43.0b3/ipc/chromium/src/chrome/common/ipc_channel_posix.cc, line 760
[NPAPI 21961] ###!!! ABORT: Aborting on channel error.: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/RELEASE/firefox-43.0b3/ipc/glue/MessageChannel.cpp, line 1768
[NPAPI 21961] ###!!! ABORT: Aborting on channel error.: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/RELEASE/firefox-43.0b3/ipc/glue/MessageChannel.cpp, line 1768


###references: After all the weeks it took me to find this bug it is now somewhat frustrating so find out, that another one already found out the very same and even reported about it at mozilla - at first in 2011!!! (while firefox upstream nevertheless still continues to keep the unfixed version in its dev git).
It appears to be the same guy who ported the chrome browser to Solaris and got only ass-kicks from certain (NON-CONTRIBUTING) folks on this openindiana list.
Now - as you see he did in fact publish sources. Had those flamewar-lovers reacted in a somewhat more civilised way, maybe he would have helped you with the FF port. 

 GCC 3 ABI mask breaks Flash 10.3 compatibility on Solaris for Chromium compiled with gcc 4 #3
Open

https://github.com/mozilla/npapi-sdk/issues/3

###solution: 
third_party/npapi/bindings/npapi.h
@@ -334,7 +334,7
-#if (defined(XP_UNIX) && defined(__GNUC__) && (__GNUC__ >= 3))
+#if (defined(XP_UNIX) && defined(__GNUC__) && (__GNUC__ == 3))

As I found out myself, a single byte (== instead of >=) was causing all this trouble on Solaris kernels.
What's new after seeing this post: Aha! Only Solaris may be affected, not LiunUX nor BSD nor MacOSX (?)

{3.} contextMenu
###problem: At all Beta src releases after FF41.0b9, hence from FF42.0b1 on, suddenly on the canvas the main context-menu would be extremely extremely long (several screens) and show all sorts of ever envisioned entries, while no single of them (except Select All) would actually invoke any functionality.
The entries would show all crap - including once planned but never implemented functions - and would show always the same long menu independently of the context (no matter on which object one would place the mourse cursor).

###references to similar problems:
Screenshot:
http://forums.thedailywtf.com/forums/p/27789/324362.aspx

Search:
https://www.google.de/search?q=context+menu+long+firefox&ie=utf-8&oe=utf-8&gws_rd=cr&ei=XJBKVp-LLsS4UfnZi_AP

What's about the suddenly extremely long right mouse-click menu?
https://support.mozilla.org/en-US/questions/956675

very long right-click context menu is present
https://support.mozilla.org/en-US/questions/958458

Right click menu is huge, how do I get the old menu back so I can highlight a word and then search for it?
https://support.mozilla.org/en-US/questions/949976

###solution: It was one such thing which made me really upset.
Analysing the long list of git commits I knew it would be related to WebGLFormat, whatever I merged in or backed out, all the things that appeared to make sense did not work.
By patching and Solaris-building all 41.0b? and 42.0b? builds in a manner of reducing the intervall of the last known working versus first known unknown version I could track down, that the break appears from 41.0b9 to 42.0b1. But the gdiff -Nurb of those 2 resulted in thousands and thousands of lines  :(

--->> It was clear that the only solution was building a debug version of some post-41.b9 with all syms.
But even then I had made the mistake to only look after the 2 error messages created when instantiating the contextMenu by right-clicking onto the canvas.

And those were as you may observe in:


$ PATH=dist/lib:dist/bin:$PATH LD_LIBRARY_PATH_32=dist/lib:dist/bin /usr/lib/ld.so.1 dist/bin/firefox 
File descriptors set to 512
++DOCSHELL f045e800 == 1 [pid = 19010] [id = 1]
++DOMWINDOW == 1 (f045f000) [pid = 19010] [serial = 1] [outer = 0]
[19010] WARNING: Hardware Vsync support not yet implemented. Falling back to software timers: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/gfx/thebes/gfxPlatform.cpp, line 2404
++DOMWINDOW == 2 (f0463000) [pid = 19010] [serial = 2] [outer = f045f000]
++DOCSHELL eb276800 == 2 [pid = 19010] [id = 2]
++DOMWINDOW == 3 (eb27d800) [pid = 19010] [serial = 3] [outer = 0]
++DOMWINDOW == 4 (eb27e000) [pid = 19010] [serial = 4] [outer = eb27d800]
++DOMWINDOW == 5 (eb2d7400) [pid = 19010] [serial = 5] [outer = f045f000]
JavaScript error: resource://gre/modules/LoginManagerContextMenu.jsm, line 20: ReferenceError: Intl is not defined
++DOCSHELL ea7f6400 == 3 [pid = 19010] [id = 3]
++DOMWINDOW == 6 (ea7f6800) [pid = 19010] [serial = 6] [outer = 0]
++DOCSHELL ea7f6c00 == 4 [pid = 19010] [id = 4]
++DOMWINDOW == 7 (eb248f60) [pid = 19010] [serial = 7] [outer = 0]
[19010] WARNING: NS_ENSURE_SUCCESS(rv, rv) failed with result 0x80040111: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/dom/base/nsFrameLoader.cpp, line 268
++DOCSHELL e9d8ec00 == 5 [pid = 19010] [id = 5]
++DOMWINDOW == 8 (eb24a5e0) [pid = 19010] [serial = 8] [outer = 0]
[19010] WARNING: NS_ENSURE_SUCCESS(rv, rv) failed with result 0x80040111: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/dom/base/nsFrameLoader.cpp, line 268
++DOMWINDOW == 9 (eb24ad60) [pid = 19010] [serial = 9] [outer = eb24a5e0]
[19010] WARNING: NS_ENSURE_TRUE(globalObject && globalObject->GetGlobalJSObject()) failed: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/dom/base/nsDocument.cpp, line 8326
[19010] WARNING: NS_ENSURE_TRUE(globalObject && globalObject->GetGlobalJSObject()) failed: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/dom/base/nsDocument.cpp, line 8326
++DOMWINDOW == 10 (e9585800) [pid = 19010] [serial = 10] [outer = ea7f6800]
++DOMWINDOW == 11 (eb24c980) [pid = 19010] [serial = 11] [outer = eb248f60]
++DOMWINDOW == 12 (eb24cd40) [pid = 19010] [serial = 12] [outer = eb24a5e0]
++DOMWINDOW == 13 (e830f520) [pid = 19010] [serial = 13] [outer = eb24a5e0]
[19010] WARNING: attempt to modify an immutable nsStandardURL: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsStandardURL.cpp, line 1300
[19010] WARNING: NS_ENSURE_SUCCESS(rv, rv) failed with result 0x80070057: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/dom/quota/QuotaManager.cpp, line 3437
++DOCSHELL e5fba400 == 6 [pid = 19010] [id = 6]
++DOMWINDOW == 14 (e5fba800) [pid = 19010] [serial = 14] [outer = 0]
++DOMWINDOW == 15 (e5fbb000) [pid = 19010] [serial = 15] [outer = e5fba800]
JavaScript error: chrome://browser/content/nsContextMenu.js, line 21: TypeError: this.initMenu is not a function
[19010] ###!!! ASSERTION: unable to use nl_langinfo(CODESET): 'Error', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/intl/locale/unix/nsUNIXCharset.cpp, line 142
[19010] WARNING: GetDefaultCharsetForLocale: need to add multi locale support: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/intl/locale/unix/nsUNIXCharset.cpp, line 101
++DOCSHELL e3bb6000 == 7 [pid = 19010] [id = 7]
++DOMWINDOW == 16 (e3bb6400) [pid = 19010] [serial = 16] [outer = 0]
++DOMWINDOW == 17 (e3bb7000) [pid = 19010] [serial = 17] [outer = e3bb6400]
++DOMWINDOW == 18 (e3bb9400) [pid = 19010] [serial = 18] [outer = e3bb6400]
++DOCSHELL e3bba000 == 8 [pid = 19010] [id = 8]
++DOMWINDOW == 19 (e4fb3f20) [pid = 19010] [serial = 19] [outer = 0]
++DOMWINDOW == 20 (e4fb46a0) [pid = 19010] [serial = 20] [outer = e4fb3f20]
[19010] WARNING: Could not get disk status from nsIDiskSpaceWatcher: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/uriloader/prefetch/nsOfflineCacheUpdateService.cpp, line 315
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6480] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6600] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6480] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2634
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2721
++DOMWINDOW == 21 (e4fb4c40) [pid = 19010] [serial = 21] [outer = e4fb3f20]
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6a80] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6f00] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd7380] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
--DOCSHELL e5fba400 == 7 [pid = 19010] [id = 6]
JavaScript error: chrome://browser/content/nsContextMenu.js, line 21: TypeError: this.initMenu is not a function
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e95a3e80] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
--DOMWINDOW == 20 (e3bb7000) [pid = 19010] [serial = 17] [outer = e3bb6400] [url = about:blank]
--DOMWINDOW == 19 (e4fb46a0) [pid = 19010] [serial = 20] [outer = e4fb3f20] [url = about:blank]
--DOMWINDOW == 18 (eb24ad60) [pid = 19010] [serial = 9] [outer = eb24a5e0] [url = about:blank]
--DOMWINDOW == 17 (f0463000) [pid = 19010] [serial = 2] [outer = f045f000] [url = about:blank]
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [e3bd6600] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2634
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2721
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
--DOMWINDOW == 16 (eb24cd40) [pid = 19010] [serial = 12] [outer = 0] [url = about:blank]
++DOMWINDOW == 17 (e9d6e980) [pid = 19010] [serial = 22] [outer = eb24a5e0]
[19010] WARNING: 'err', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 3008
[19010] WARNING: nsSocketTransport Failed setting TCP_KEEPIDLE [f0673300] OS error[0x63] Option not supported by protocol: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2932
[19010] WARNING: 'NS_FAILED(rv)', file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/base/nsSocketTransport2.cpp, line 2784
[19010] WARNING: RasterImage::Init failed: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/image/ImageFactory.cpp, line 109
JavaScript error: chrome://browser/content/nsContextMenu.js, line 21: TypeError: this.initMenu is not a function
--DOMWINDOW == 16 (e5fbb000) [pid = 19010] [serial = 15] [outer = e5fba800] [url = about:blank]
--DOMWINDOW == 15 (e5fba800) [pid = 19010] [serial = 14] [outer = 0] [url = about:srcdoc]
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
JavaScript error: chrome://browser/content/nsContextMenu.js, line 21: TypeError: this.initMenu is not a function
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null
--DOCSHELL e3bb6000 == 6 [pid = 19010] [id = 7]
--DOCSHELL f045e800 == 5 [pid = 19010] [id = 1]
[19010] WARNING: cannot post event if not initialized: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/protocol/http/nsHttpConnectionMgr.cpp, line 194
[19010] WARNING: cannot post event if not initialized: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/protocol/http/nsHttpConnectionMgr.cpp, line 194
[19010] WARNING: cannot post event if not initialized: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/protocol/http/nsHttpConnectionMgr.cpp, line 194
[19010] WARNING: cannot post event if not initialized: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/netwerk/protocol/http/nsHttpConnectionMgr.cpp, line 194
--DOCSHELL e3bba000 == 4 [pid = 19010] [id = 8]
--DOCSHELL eb276800 == 3 [pid = 19010] [id = 2]
--DOCSHELL e9d8ec00 == 2 [pid = 19010] [id = 5]
--DOCSHELL ea7f6400 == 1 [pid = 19010] [id = 3]
--DOCSHELL ea7f6c00 == 0 [pid = 19010] [id = 4]
[19010] WARNING: NS_ENSURE_TRUE(context) failed: file /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/xpcom/threads/nsThread.cpp, line 761
--DOMWINDOW == 14 (eb2d7400) [pid = 19010] [serial = 5] [outer = f045f000] [url = resource://gre-resources/hiddenWindow.html]
--DOMWINDOW == 13 (e9585800) [pid = 19010] [serial = 10] [outer = ea7f6800] [url = about:blank]
--DOMWINDOW == 12 (eb24c980) [pid = 19010] [serial = 11] [outer = eb248f60] [url = about:blank]
--DOMWINDOW == 11 (f045f000) [pid = 19010] [serial = 1] [outer = 0] [url = resource://gre-resources/hiddenWindow.html]
--DOMWINDOW == 10 (ea7f6800) [pid = 19010] [serial = 6] [outer = 0] [url = about:blank]
--DOMWINDOW == 9 (eb248f60) [pid = 19010] [serial = 7] [outer = 0] [url = about:blank]
Hit MOZ_CRASH(Shutdown too long, probably frozen, causing a crash.) at /export/home/martin/DEVEL/FF/43/FF43.0b2__RELEASE/TEST/PATCHCREATION/001__PORTED/firefox-43.0b2/toolkit/components/terminator/nsTerminator.cpp:151
/usr/bin/pstack: 19010: No such file or directory
--DOMWINDOW == 8 (eb27e000) [pid = 19010] [serial = 4] [outer = 0] [url = about:blank]
--DOMWINDOW == 7 (eb27d800) [pid = 19010] [serial = 3] [outer = 0] [url = chrome://browser/content/browser.xul]
--DOMWINDOW == 6 (eb24a5e0) [pid = 19010] [serial = 8] [outer = 0] [url = http://opensxce.org/]
--DOMWINDOW == 5 (e830f520) [pid = 19010] [serial = 13] [outer = 0] [url = about:home]
--DOMWINDOW == 4 (e4fb3f20) [pid = 19010] [serial = 19] [outer = 0] [url = https://self-repair.mozilla.org/en-US/repair/]
--DOMWINDOW == 3 (e3bb9400) [pid = 19010] [serial = 18] [outer = 0] [url = data:application/vnd.mozilla.xul+xml;charset=utf-8,<window%20id='win'/>]
--DOMWINDOW == 2 (e3bb6400) [pid = 19010] [serial = 16] [outer = 0] [url = data:application/vnd.mozilla.xul+xml;charset=utf-8,<window%20id='win'/>]
--DOMWINDOW == 1 (e9d6e980) [pid = 19010] [serial = 22] [outer = 0] [url = http://opensxce.org/]
--DOMWINDOW == 0 (e4fb4c40) [pid = 19010] [serial = 21] [outer = 0] [url = https://self-repair.mozilla.org/en-US/repair/]
nsStringStats
 => mAllocCount:          99212
 => mReallocCount:        11728
 => mFreeCount:           99212
 => mShareCount:         180933
 => mAdoptCount:           5780
 => mAdoptFreeCount:       5780
 => Process ID: 19010, Thread ID: 1


... thse were:

JavaScript error: chrome://browser/content/browser.xul, line 1: TypeError: gContextMenu is null

and

JavaScript error: chrome://browser/content/nsContextMenu.js, line 21: TypeError: this.initMenu is not a function


This again lead me to some similar bug scenarios, but not identical ones:

https://www.google.de/search?q=%22TypeError:+gContextMenu+is+null%22&ie=utf-8&oe=utf-8&gws_rd=cr&ei=SJVKVo6MEMf_ac26sNAN

TypeError: gContextMenu is null
http://www.camp-firefox.de/forum/viewtopic.php?f=8&t=75369&start=0

Bug 978082 - Intermittent | browser_save_video.js,browser_save_video_frame.js | uncaught exception - TypeError: gContextMenu is null at chrome://browser/content/browser.xul:1 
https://bugzilla.mozilla.org/show_bug.cgi?id=978082

Bug 913176 - Intermittent browser_default_image_filename.js | uncaught exception - TypeError: gContextMenu is null at chrome://browser/content/browser.xul:1 | Test timed out 
https://bugzilla.mozilla.org/show_bug.cgi?id=913176

Target Undefined When Right Clicking In Firefox With Context Menu
http://stackoverflow.com/questions/14651785/target-undefined-when-right-clicking-in-firefox-with-context-menu


... and for the second error message:

No single identical result for this (even shortened) string if in double quotes:

"TypeError: this.initMenu is not a function"

No safe node or rm -R ~/.mozilla helped, so no extensions/add-ons could have been causing this.
Then I spent days reading, compiling, grep'ing, checking firefox's git log etc etc etc.
After a week I finally realized that with JS it is a mistake to only look for the final error messages. Because if something goes wrong during JS initialization some or all functionality might be broken until the hosting application gets restarted.
BANG!!!

So let's have a look at the full stdout and stderr from the console window running the debug version:

First interesting error:
JavaScript error: resource://gre/modules/LoginManagerContextMenu.jsm, line 20: ReferenceError: Intl is not defined

And at that moment it became all clear to me:

As silly as life can be, of course I had simply disabled internationalization support last spring, because I personally always prefer the C locale anyway, and also had enough other problems with first getting the port itself done, at the time.
And until now this has never been a problem and worked fine until FF41.0b9

Configuring with ../configure --enable-application=browser --prefix=/usr/lib/firefox`/bin/cat /tmp/FFvers`  --enable-official-branding --disable-updater --enable-debug-symbols=no --enable-update-channel=esr --disable-tests --enable-jemalloc --disable-dtrace --disable-xinerama --disable-crashreporter --disable-pulseaudio --disable-gstreamer --with-intl-api --disable-debug --enable-ipc --enable-default-toolkit=cairo-gtk2

soon brought the relieving confirmation, that indeed and in fact only this had been to problem from 42.0b1++ on.
NICE, how stupid. Okay and now that internationalization was on and fully building like a charm of course I wanted to give you also the language kits in preinstalled ready2run form in the binary package and althernative bins-tarball.

... which instantly brought up the next day of questions, finding odd user-unfriendliness in FF's handling of this, namely:


{4.} langpacks */
How to get the langpacks not only somehow to function on by one forcing end-users to perform manual installations one at a time following bogus outdated and often self-contradicting instructions somewhere on the mozilla site, often referring to oldtimers such as FF3 or 4.

No, my goal was:

###problem: 
A) * having all available 90++ langpacks installed 

B) * having them installed GLOBALLY, not even Oracle does this in Sol11.3 as I had to find out, they use jack's local ~/.mozilla, but I offer not a distro this time, but only installable software in a pkg and tar ball, cannot mess with anybody's $HOME

C) * I want the entire FF-UI to be in the corresponding language (rather than only in the objects dealing with the filesystem [open file/save as etc.]), where-ever this is fully imlemented in a language pack (not all have that)

D) * All plugins shall not get disabled by default on first run (if no ~/.mozilla exists, or if you already had that but run the new FF43 for the first time)

E) of course I want full automation: 
It shall instantly come up in the locale that the user is using and have its entire UI in the associated language.
No matter what the user specified during installation system-wide or locally for one session from gdm, it shall always work smoothly and without interaction. Without first forcing the user to:
i) install any langpack
ii) having to enable it
ii) having to set a single variable in about:config

In in extreme case, from the same env and cmd line one shall be able to say:
LANG=de_DE.UTF-8 /usr/lib/firefox43.0b3/lib/firefox-43.0/firefox
and it should come up like a genuine german version

while seconds later from the same window without changing the env:

LANG=ru_RU.UTF-8 /usr/lib/firefox43.0b3/lib/firefox-43.0/firefox
should bring up a fully localized Russian version and all the same for all other 90 locales (if and where UI-localization has full support) including zh_CN or Japanese.

I was surprised to learn, that in 40++ versions of FF this is no longer easy to be accomplished (as global installation that has zero dependencies to whatever in ~/.mozilla). At least not unless you found out how to do this.
I fund out by testing that Sun/Oracle Solaris 11.3 can does so only by means of jack's $HOME, while Hipster with its FF24 does have the langpacks all in place in the global extensions dir, but no single langpack appeared to be installed (regsitered) let alone activated not to mention activated by intl.locale.matchOS=true or general.useragent.locale

###REFERENCES:
Integrating Add-ons into Firefox
https://mike.kaply.com/2012/02/09/integrating-add-ons-into-firefox/

distribution/bundles Directory Gone in Firefox 40
https://mike.kaply.com/2015/05/19/distributionbundles-directory-gone-in-firefox-40/

Deploying Firefox in an enterprise environment
https://developer.mozilla.org/en-US/Firefox/Enterprise_deployment

AddOns for all users
https://support.mozilla.org/en-US/questions/966922

Extension Packaging
https://developer.mozilla.org/en-US/Add-ons/Extension_Packaging

Works for Seamonkey, but not for FF: Firefox/Seamonkey: How to install add-ons system-wide? 
http://www.linuxquestions.org/questions/linux-software-2/firefox-seamonkey-how-to-install-add-ons-system-wide-4175421566/

How do I install a language XPI globally and make it the default language?
http://www.cla5h.com/how-do-i-install-a-language-xpi-globally-and-make-it-the-default-language.html

Well, all of that did not work, unzipping it in place under /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/ also made no difference over not unzipping them.
Let me shorten it and here comes the ...

###SOLUTION:
--- 000__VANILLA/toolkit/mozapps/extensions/internal/XPIProviderUtils.js	2015-11-12 23:49:00.000000000 +0100
+++ 001__PORTED/toolkit/mozapps/extensions/internal/XPIProviderUtils.js	2015-11-16 01:54:30.570857314 +0100
@@ -1675,12 +1675,12 @@
 
     if (isDetectedInstall && aNewAddon.foreignInstall) {
       // If the add-on is a foreign install and is in a scope where add-ons
-      // that were dropped in should default to disabled then disable it
+      // that were dropped in should default to disabled then enable it anyway on OpenSolaris (preinstalled langpacks)
       let disablingScopes = Preferences.get(PREF_EM_AUTO_DISABLED_SCOPES, 0);
       if (aInstallLocation.scope & disablingScopes) {
-        logger.warn("Disabling foreign installed add-on " + aNewAddon.id + " in "
+        logger.warn("Enabling foreign installed add-on " + aNewAddon.id + " in "
             + aInstallLocation.name);
-        aNewAddon.userDisabled = true;
+        aNewAddon.userDisabled = false;
       }
     }
 
--- 000__VANILLA/modules/libpref/init/all.js	2015-11-12 23:48:53.000000000 +0100
+++ 001__PORTED/modules/libpref/init/all.js	2015-11-16 01:15:18.702792127 +0100
@@ -1836,7 +1836,7 @@
 pref("intl.charset.fallback.override",      "");
 pref("intl.charset.fallback.tld",           true);
 pref("intl.ellipsis",                       "chrome://global-platform/locale/intl.properties");
-pref("intl.locale.matchOS",                 false);
+pref("intl.locale.matchOS",                 true);
 // fallback charset list for Unicode conversion (converting from Unicode)
 // currently used for mail send only to handle symbol characters (e.g Euro, trademark, smartquotes)
 // for ISO-8859-1


Simply putting the default untouched langpacks from http://ftp.mozilla.org/pub/firefox/releases/43.0b3/linux-i686/xpi/ into a vanilla /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/ would recognize the LANG or LC_ALL exported by env in all file menu open/save as dialogues out of the box. BIG BUT: In Firefox's Tool>Add-Ons Menu would _not_ show any menu entry "Languages".

In addition to that: For some unknown reasons, the xpi files (must always match the corresponding release, which I cared of) only get recognized as installed/registered langpacks not by means of manually faking the installation tricks the tough way by creating dirs such as

d none usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/{972ce4c6-7e08-4474-a285-3208198ce6fd} 0755 root bin
f none usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/{972ce4c6-7e08-4474-a285-3208198ce6fd}/icon.png 0644 root bin
f none usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/{972ce4c6-7e08-4474-a285-3208198ce6fd}/chrome.manifest 0644 root bin
f none {972ce4c6-7e08-4474-a285-3208198ce6fd}/install.rdf 0644 root bin

manually (even though all ids matched it would always complain: id doesn't match ..).

But the solution was (despite tough to find, only testing brought me to it) simpler: 
#0.) perform a local installation of all xpi files stored somewhere into the local user's ~/.mozilla simply via Tool>Add-Ons>Extensions>Install_Add-on_from_file and selecting all at once, then clicking ok (which is not visible), but one can blindly hit [TAB] 4 times and then [SPACE].
#1.) Restart and close FF once (and make sure they were installed, accepted and enabled)
#2.) (cd /export/home/martin/.mozilla/firefox/0deafbum.default;tar cvf - ./extensions)|(cd /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/.;tar xvf -)

Any other variation did not succeed.
And doing the same from the same ~/.mozilla after a 2nd start of FF it would also break it again (fortunately I too a snapshot before that).
Needs further investigation for the next verion.
ATTENTION: Subfolders of /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions including /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/extensions/{972ce4c6-7e08-4474-a285-3208198ce6fd} need x-access for the user who wants to start firefox, therefore permissions must be 755. Otherwise the langpacks will not work. This appears to explain the subtle errors I got at first. Because after wget'ing them from mozilla at first they are all 0600.


INSTALL bins:
@@@@@UPDATE@@@@@: Flash Plugin 9/10/11.x 
... works now inside this gcc compiled Firefox!
That was a complete Novum when I reached this step in April. This took another tough week
of work night and day and night.
Nobody has ever achieved this before with a gcc build of FF on Solaris (at least nobody in the records and nobody who offered to donate this to the broader planet OpenSolaris).
From the src it appears that this must also affect other UNIX/LinUX OS ports, but I never tested this.


It was tested and is known to work with:
(instabilities and freezes related to videos that are in a too new format can always happen, but are not related to this port, while flash is closed src and I can only take their bins and make them work in FF as good as technically possible)

drwxr-xr-x 2 martin other       4 Dec 27  2007 flash_player_9_solaris_r115_x86
drwx------ 2 martin other       3 Nov  8  2011 flash_player_solaris_10_3_183_11_x86
drwx------ 2 martin other       3 Nov  3  2011 flash_player_solaris_11_1_102_56_x86
-rw------- 1 martin other 4752427 Nov  9  2011 flashplayer10_3r183_11_solaris_x86.tar.bz2
-rw------- 1 martin other 4755108 Aug  9  2011 flashplayer10_3r183_5_solaris_x86.tar.bz2
-rw------- 1 martin other 4752536 Aug 23  2011 flashplayer10_3r183_7_solaris_x86.tar.bz2
-rw------- 1 martin other 6084262 Nov  4  2011 flashplayer11_1r102_55_solaris_x86.tar.bz2
-rw------- 1 martin other 6212851 Mar 20  2012 flashplayer11_2r202_228_solaris_x86.tar.bz2
-rw------- 1 martin other 2859276 Jun 10  2010 flashplayer9r115_solaris_x86.tar.bz2


Attention: On all newer Illumos based Distros _except_ OpenSXCE you probably need some loading order
nonsense to get the Flash-Plugin 11.x initializing itself rather than crashing (only works sometimes, not with all codecs). 
In such cases you should remove your local libflashplayer.so from the plugins directory and set HTML5 as your default player (e.g. on youtube).
But that drmatically reduces compatibility and rather often you cannot watch a news or music video. Because ... : HTML5 nice and good, but often they still force use to use flash.




INSTALLATION:

$ cd ~/Downloads
$ wget http://opensxce.org/.FF/43.0b3/i386/firefox-43.0b3___Multilang__gcc4x-built__supports-flash-plugin__opensolaris-snv_130++_all_distros-i386.pkg.bz2
$ bunzip2 ./firefox-43.0b3___Multilang__gcc4x-built__supports-flash-plugin__opensolaris-snv_130++_all_distros-i386.pkg.bz2
$ su
# pkgrm SUNWfirefox43.0b3 (all other versions can be installed without a single namespace conflict)
# pkgadd -d ./firefox-43.0b3___Multilang__gcc4x-built__supports-flash-plugin__opensolaris-snv_130++_all_distros-i386.pkg



WHERE IS THE PLUGINS INSTALL DIR:

Global location: /usr/lib/firefox43.0b3/plugins (symlink) or /usr/lib/firefox43.0b3/lib/firefox-43.0/browser/plugins
Because by definition, given that I frequently want to test different flash plugins for testing, I always use ~/firefox/plugins which works.
To verify which plugins got recognized open FF and enter the special URL:   about:plugins
Don't forget that Flash will crash on Illumos kernels except on OpenSXCE (which is the only one with a kernel fix).



USAGE:

FF43.0b3 can be started in 3 different ways, either of the following ...

$ /usr/bin/firefox43.0b3

$ /usr/lib/firefox43.0b3/bin/firefox

or under JDS/Gnome from {Start}->{All Applications}->{Internet}->{Firefox 43.0b3 Beta}



UNINSTALL:
# pkgrm SUNWfirefox43-0b3


best regards, %m

email: opensxce@mail.ru
(This would in theory also be my PAYPAL address, but you know the joke about theory vs. practice)

}





{
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# # # Part II.) *non*-TECHNICAL SCOPE: # # # # # # # # #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 


Both OpenSXCE and the FF37 port could and can be downloaded anonymously by ANYone.
http://opensxce.org/.FF/37/i386/README.txt
http://svr4.opensxce.org/201405/i386/5.11/

No single capitalist ever paid the license price (as I requested in http://svr4.opensxce.org/RELEASE_NOTES__OpenSXCE2014.05_x86_x64_INTEL32-64_AMD32-64____sun4u_sun4v_SPARC.txt ).

The few donations (BIG THANKS TO THE FEW FRIENDS!!!) got smaller and more scarce.
No single so called "donation" arrived for months. I say "so called" because a more fitting term is: pay at least a small fraction of the costs that arise through this volunteer work).

But nevertheless all downloads are still available.
Is that what a "capitalist" would do?
M.B. lives in empoverished and hopelessly over-indebted conditions and of a total bank account balance of -1000 EUR has currently 1 Cent available (-999.999 EUR). Screenshot anytime  ...
One person claimed he wanted to "sponsor him" with 450 EUR per month.
A closer investigation proved that his company looked for some project assigned engineer that they could hire, but only had a budget of a montly 450 EUR.
What first appeared to be a helpful citizen who wanted to support OpenSXCE going to GitHub at closer investigation turned out to be attempted exploitation.
More: During the endless instructions for the 2 commercial projects I should work on for those promised 450 EUR (== no donation!) he reiterated several times: Hahaha, no, we here in my company *never* pay anything for software, hahaha. The only single exception is xyz (some commercial product he mentioned).
Nice community friend indeed!

Experiences with the  so called "community" stretch back more than 10 years.
Here another such example from 2007 (at the time I had already contributed MartUX [now OpenSXCE] as src and bins, the Xorg port to SPARC as src and bins, the port of the aperture driver to amd64 before xsvc got opened, the qemu-port to SPARC-Solaris hosts) :

http://echelog.com/logs/browse/opensolaris/1195513200

[06:33:47] <g4lt-U60> YAY m. Bochning is finally removed from the lists!  happy day indeed!
[06:40:52] <Tempt> Bochning?
[06:40:58] <Tempt> Another noisy listtwit?
[06:42:18] <g4lt-U60> Tempt, he's the one that was doing the "unscreib me" crap for the last week
[06:42:37] <Triskelios> Tempt: martin, as in martux
[06:42:48] <Tempt> oh
[06:42:51] <Tempt> loonix wankstain
[06:43:35] <Triskelios> eh... he's done good work. he was one of the main FOX people
[06:43:43] <Tempt> Oh.
[06:43:46] <Triskelios> has serious ... personality issues though
[06:43:57] <jmcp> Tempt: Martin of the "I deserve funding because I've spent all my time working on martux rather than trying to get a job now i'm in serious debt"
[06:44:07] <Tempt> Does anyone use Martux?
[06:44:44] * jmcp shrugs
[06:45:57] <Tempt> Meh
[06:46:08] <Triskelios> the SPARC Xorg stuff was written for it
[06:46:34] <Tempt> People with those sort of personality issues tend not to be able to sustain employment anyway.


> And here from just this August:  http://openindiana.org/pipermail/openindiana-discuss/2015-August/017864.html
> 
>  jay at m5.chicago.il.us
> Mon Aug 24 01:43:58 UTC 2015
> 
> And, speaking of OpenSXCE (from which one can apparently obtain a
> working version of Firefox 37) -- there was a huge amount of
> discussion on this mailing list a while back about OpenSXCE.  I do not
> want to re-awaken those sleeping threads, I truly do not want to read
> any more postings about whether the man who gave us OpenSXCE is
> irredeemably and irretrievably antisocial, or whether it is moral to
> donate money to someone whose political sympathies lie with people who
> blow up schoolbuses. 


--->> Who  <<--- is anti-social here?
This person who probably never donated much - if any - of his labour for free?
Which moral if any right do such "persons" have to talk about me like this?
His only achievement (pls. correct me if this is wrong) I know of consisted of having posted a trolling from time to time.

I know, this is a technical list. And I do understand the need to avoid political discussions.
But this jay at m5.chicago.il.us "person" claimed devastating lies about me and not a single person had the balls to contradict his claims.
What kind of "community" am I dealing with?

Here is my short response to him:

REMINDER:

General Wesley Clark explains ISIS was created by U.S. Allies 
https://www.youtube.com/watch?v=ojcoKnTGf4s

Wesley Clark: "Our friends and allies funded ISIS to destroy Hezbollah" 
https://www.youtube.com/watch?v=QHLqaSZPe98

Hillary Clinton : We created Al-Qaeda 
https://www.youtube.com/watch?v=Dqn0bm4E9yw

Hillary Clinton - We created ISIS 
https://www.youtube.com/watch?v=h5ff0EOj2WU


Exposing the I.S.I.S Lie: How President Obama & Hillary Clinton Created I.S.I.S. 
https://www.youtube.com/watch?v=RU8-bgfR83Q



UNFASSBAR!!! US Hauptziel IST kRIEG in Europa
(UNBELIEVABLE!!! USA's main goal is WAR IN EUROPE
https://www.youtube.com/watch?v=xi7M_P2ldsQ



NATO wants to "fight ISIS" to - in reality - support them even better than until now. 
GOAL: To remove Assad and to invade Iran. Then Russia/China are finally completely encircled.


https://www.youtube.com/results?search_query=mc+cain+isis

US Senator John McCain: "I know ISIS intimately, I've met them and I talk to them all the time."
https://www.youtube.com/watch?v=tgLj5s0Xk8A

ISIS : John McCain admits he met ISIS and says "We know these people intimately" (Sept 16, 2014) 
https://www.youtube.com/watch?v=vItuKKuz_7Y

McCain's ISIS Ties Are Too Numerous For America 
https://www.youtube.com/watch?v=C7VHPKlWJUQ


ISIS ISIL Leader with John McCain (US GOV)? - BREAKING NEWS ALERT
https://www.youtube.com/watch?v=Ba0jpRjGFDo


Confirmation now in that Paris attacks were false flag.

Because nothing says ‘False Flag’ like a ‘takfiri terror cell’ planning their exercise on the exact same day as the ‘government terror cell’.
http://www.globalresearch.ca/we-were-prepared-large-military-exercise-took-place-on-same-day-as-paris-terrorist-attacks/5489164

Washington Refines Its False Flag Operations — Paul Craig Roberts
http://www.paulcraigroberts.org/2015/11/16/washington-refines-its-false-flag-operations-paul-craig-roberts/

Thank you, America: Sinai plane terror victims:
https://www.google.de/search?q=sinai+plane+victims&source=lnms&tbm=isch&sa=X&ved=0CAgQ_AUoAmoVChMIgNqTpp-WyQIVyNgaCh0HDweA&biw=1280&bih=873
(mostly young women and children were on board)

I didn't see anybody changing his fb or twitter avatar to the Russian tricolore.
Unlike now in Paris.

This heartbreaking image shows 10 months young Darina, who is among the victims
http://www.zerohedge.com/sites/default/files/images/user92183/imageroot/2015/10/PlanesDarina_0.png

Russian Plane "Broke Apart In The Air," Officials Say As Investigators Frantically Search For "Clues"
http://www.zerohedge.com/news/2015-11-01/russian-plane-broke-apart-air-officials-say-investigators-frantically-search-clues

May I also ask: How was it possible that the USA knew in minutes the plane was shot down by ISIS, and that in less than 1 week sattelite images and so called "intelligence" could be provided, which are mysteriously still not available for MH17 let alone MH370 in 1.5 years??????????

Move on:

Published: October 2nd: INSANE MCCAIN: ARM SYRIAN REBELS TO SHOOT DOWN RUSSIAN PLANES 'Just like we did in Afghanistan' 
https://www.youtube.com/watch?v=qXinE5lSQYI

John McCain and Free Syrian Army of Israeli State Finally Shot Down a Russian Plane 
https://www.youtube.com/watch?v=lqwmdpvawog

Leuren Moret: McCain in false flag to down Russian airliner, caught just prior to Sinai crash 
https://www.youtube.com/watch?v=ChT4VDm_n8M

On FOX-News: US Senator John McCain says he'd give terrorists means to shoot down Russian planes. 
https://www.youtube.com/watch?v=paR_5iqnZsU

Published September 30th: BREAKING: John McCain To Arm Rebels with STA Missiles To Shoot Down Russian Jets 
https://www.youtube.com/watch?v=EM-bV19J6w8

Published October 2nd: Insane McCain Wants ISIS To Shoot Down Russian Jet Fighters 
https://www.youtube.com/watch?v=NaDPumW5qMQ

Published October 2nd: US Senator John McCain: Arm Syrian Rebels to shoot down Russian planes! 
https://www.youtube.com/watch?v=tDFql8eE0TA

Published October 2nd: Senator John McCain Wants Russian Fighter Jets Shot Down In Syria 
https://www.youtube.com/watch?v=YQIHCScb77o

Published October 31st: BREAKING: [CENSORED] SHOOTS DOWN RUSSIAN AIRLINER THANKS TO JOHN MCCAIN
https://www.youtube.com/watch?v=t7AUfWlGlmk



WHO is supporting terrorists, valued Mr. jay at m5.chicago.il.us???
Answer: IT IS *****YOU*****:

Kiev started shooting their own civilians weeks before the war started in Mai 2014.
YT is full of evidence (search in cyrillic).
It has nothing to do with the Kremlin.

Захват БМП в Мариуполе (другой ракурс) 11:42 9 мая 2014
https://www.youtube.com/watch?v=MhfPkHvFBvE


Let alone the Odessa massacre, the entire Marioupol massacre, and the
massacred Bus in Fevruary 2014 with people from Crimea that wanted to
travel back home from Anti-Maidan in Kiev.
And believe me: The West is the worst tyrant of all times.


https://www.google.de/search?q=odessa+pregnant+woman+massacre&source=lnms&tbm=isch&sa=X&ei=8lQfVaDPM47raMTugPgH&ved=0CAcQ_AUoAQ&biw=1280&bih=853

https://www.youtube.com/watch?v=LvVuFCYPx0Y

http://scgnews.com/the-odessa-massacre-what-really-happened

Very Real Neo-Nazi Threat in Ukraine. A compilation of what mainstream
media isn't showing.
https://www.youtube.com/watch?v=pYjsCJwcPWk

How the US Government Conquered Ukraine to Start WW3 With Russia
https://www.youtube.com/watch?v=V6yL_8lal3c


NATO bombing of Yugoslavia 1999. / NATO bombardovanje Jugoslavije 1999.
https://www.youtube.com/watch?v=gelCe981y0I

Documentary: "Why Zasto" - NATO bombing Yugoslavia IN 1999
https://www.youtube.com/watch?v=HxDcvhH2Ypc&list=PLRImknr7RoMDl2OvaP14Mx2mBMKgMeLbK

Reason Why I Hate USA - American Bombing of Serbia (based on lies and false completely made up pretexts, as every time!)
https://www.youtube.com/watch?v=Ju-Y73Qn05Q



I was born as a simple East-German in wonderful communist Soviet East-Berlin: 
It was a peaceful country, not invading "region" after "region", year after year since 1945, killing tens of millions!!!
And YES, I do have a right to say all this! Because before 1989 your God-darn Western propaganda mouthpieces promised us "Freedom of speech" and "democracy", "freedom" and all that noise!

What we in fact got from the golden West was this: 

TREUHANDKRIMINALITAET (aks "Privatization") :
beutezug ost https://www.youtube.com/results?search_query=beutezug+ost

and in Russia and now Ukraine:
Всё идёт по плану (Everything goes [well] according to plan) https://www.youtube.com/watch?v=QS54GkLRtrI

Compare this to """evil evil evil""" communism, my homeland East-Germany which got robbed off, de-industrialized and ensalved.
Here before 1989:

GDR:
Weiße Maus Verkehrspolizei DDR 1987 
https://www.youtube.com/watch?v=37iy1MB1Wh8

Berlin, Hauptstadt der DDR Teil 1 / Берлин, ГДР
https://www.youtube.com/watch?v=oZdxuOK3YuE

Soviet Union:
Наташа Королёва Жёлтые тюльпаны Песня 1990 
https://www.youtube.com/watch?v=E57T8XYa7OM

Moscow Olympic 1980 (BOYCOTTED by the USA, which dound it better to create Al-Quaeda during that time! According to Hillary Clinton herself)
https://www.youtube.com/watch?v=qt3xVMt0k4k

Yugoslavia:
Few Americans know little if anything about: Yugoslavia - the Good Old Days of Tito-style Communism
https://www.youtube.com/watch?v=0RRnCnO1Y2c



I feel ashamed and DISGUSTED by Germany's EU's and generally
Western actions.﻿ And also by such "community members" who care a damn shit for dead Russian women and children in Donbass or Egypt, let alone Syrians, Iraqis, Libyans, Afghans, Serbs and all the list through their amazing history as an "exceptional nation".

IMAGINE: I got excluded from the Illumos discuss list in 2013 by Madame Deidre Straughan (gets $$$ for being a "community architect" destroying the community but never submitted a line of code) for having said the truth. And the US-sponsored terror attacks in Wolgograd DID KILL circa 20 CIVILIANS during the Sochi Olympics, when busses where blown up. Nobody had a tear. Now after the next western false flag everybody jumps on the MSM hysteria and calls for WAR. Although the only french airplane carrier headed from France to the Middle East 2 days _before_ the "attacks" took place.

The ones who are spilling blood all over the planet - hint: It's not the Russians.
And it were not the communists in my home country - GermanDemocraticRepublic.
It's the West and the terror groups it create[d|s] and finance[d|s] for decades.
I'm not talking about politics here. Sure - that shall not be done on such lists.
But what we are dealing with here is not "politics", but mass-slaughter and endless genocides co-committed by our beloved "Nobel peace prize" winner Obomber and the EU of "western values".
I not only have every right to speak about this, but it is my duty. And should be everyone's who still wants to look in the mirror.
The day comes closer on which we no longer have the possibility to attend mailing lists. Who wants to let that happen and wait until his death with a paralyzed smile is free to do so! But I personally won't. GET THAT.

Let me close this non-technical section forced onto us triggered by folks who never contributed technically, such as this jay at m5.chicago.il.us 
(he started it and nobody ended it, this forces me to write all this, yet another time ...)
So if anybody wants to stop seeing such non-technical paragraphs, break the patttern ..., else it repeats while true.

Listen to murdered US presidents (the only US-presidents who really wanted to serve their nation (and the world) all got assassinated. That alone would cause any true American patriot to think twice about CNN-News sort of "reporting" across ___all___ western MSM, who are all repeating the very identical "reports" from Reuters and AFP (which all across the alleged spectrum are owned by 7 families!)

JFK - The Speech That Killed Him
https://www.youtube.com/watch?v=y8HTr-F-FVM

Eisenhower warns us of the military industrial complex. 
https://www.youtube.com/watch?v=8y06NSBBRtY

(From books) Thomas Jefferson warns of the dangers of central banks and national debt 
https://www.youtube.com/watch?v=UrxKOO0nKwc

In the old days (not only in communist countries) folks were educated and smart.
Not only "expert" idiots, but had some general wisdom, were interested in all truly important aspects of life and defended PEACE AND JUSTICE.
What a pathetic mass of equalized yes-sayers has this been washed into by "your" TV in just 3 decades?

Imagine somebody during WW2 reporting about the horrible crimes committed by Nazi-Germany would have come to this list with eyewittness reporting, tons of youtube footage and waterproof evidence.
And your only reaction would have been: ^^Sir, you violated the newly introduced "no-kveching-rule" which was just created _after_ your "hatred post".^^
THAT's what Illumos-devel has done in 2013.
And by doing so they are in fact complicit with genocides committed by their "government".
Contradicting the American Costitution by all accounts (as every US-administration since JFK).

For years I had not managed to grasp, why the LinUX, *BSD and other open-src communities disliked Solaris so much, even though Sun did open it in the form of OpenSolaris, and even though Solaris is one of the most adavanced operating systems ever created.
Over time when dealing with some folks the reason can only be: It has little to do with the software, but more with such McCain -Palin maniac fanboys in its Sun kernel team.

p.s. Back to the "Anti-Social Capitalist" bs: Why is nobody complaining about the fact, that certain users who never contribute anything substantial pollute the public oi- and other lists by spreading SPAM and ADS for their own private COMMERCIAL businesses, even in cases where all they "contributed" was a one-liner joke, such as here: http://openindiana.org/pipermail/openindiana-discuss/2015-November/018225.html  ???

If we want equal standards for all, then some should not be "more equal".
}






{
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# # # Part III.) THANKS: # # # # # # # # # # # # # # #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # 

Most of all I would like to thank my girlfriend and my family who have limitless amounts of 
understanding for the financial and time-realted problems caused by this.
I LOVE HER

And then: You can thank Al Hopper who pays for all my OpenSolaris related hosting, domain names etc since 2005!!!!!
Thanks also to all who ever sent me money (as listed in http://svr4.opensxce.org/RELEASE_NOTES__OpenSXCE2014.05_x86_x64_INTEL32-64_AMD32-64____sun4u_sun4v_SPARC.txt and to Ken Mays for his never-ending series of mentioning me on-list in some positive way, plus for having designed OpenSXCE.org's old (now outdated) website.

If anybody attempted to contact me via martin@martux.org since July: Please don't be upset. I no longer have any pw access because google claims "I'm running a biz", which would be nice but is not the case. They want 5 EUR per month and I cannot by any means pay that (especially not backwards from tip).
My new eMail address is: opensxce [[at]] mail.ru
If anybody would in fact want to give me some $$$ back for my work (after he tested if he likes it), then plese use that new email address, tnx.
If not, I cannot do anything about that, as all the way back to 2005 and 2003.
}

Sorry - won't spell-check or correction-read this anomore.
I dislike writing such long ANNOUNCE files.
Everything that needed to addressed has been said. By releasing this FF port the ball is now in your field.
If OpenIndiana and or Illumos is interested in any friendship, then everybody can see that I once again attempted to reach out and gave you my hand.
This time you have all FF related SRC patches. So it proves that I trust you.

You can thank friendly long-term community members from good old osol times, because without having seen that they repeatedly had some good words for me on the ml list and openindiana.org's FF page and the illumos site, this release would not have happened (regards and BIG tnx to all my misc. friends, as listed in http://svr4.opensxce.org/RELEASE_NOTES__OpenSXCE2014.05_x86_x64_INTEL32-64_AMD32-64____sun4u_sun4v_SPARC.txt !).



FOR THE DEMOCRATIC REPUBLICS, IMAGINE

Martin Bochnig
opensxce@mail.ru



