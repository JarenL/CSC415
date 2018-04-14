Build: make filecopy
Compile: ./filecopy

Info: The following program demonstrates the use of open() write() read() system calls from the UNIX|LINUX system.
This allows us to make use of the following flags to simplify FILE I/O when building our programs.

The following out output below displays the trace of our compiled programs which allows developers to make use of 
sys calls to track memory for any faults or leakage from our function calls. This also makes great usage when it comes 
to debugging. Below, we're tracking the list of sys calls and the number of times executed.  

open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
close(3)                                = 0
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
close(3)                                = 0
open("/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
close(3)                                = 0
open("/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
read(3, "# Locale name alias data base.\n#"..., 4096) = 2995
read(3, "", 4096)                       = 0
close(3)                                = 0
open("/usr/share/locale/en_US/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/en/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/en_US/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/en/LC_MESSAGES/coreutils.mo", O_RDONLY) = 3
close(3)                                = 0
open("./filecopy1", O_RDONLY|O_NOCTTY)  = 3
close(3)                                = 0
open("/proc/self/mountinfo", O_RDONLY)  = 3
read(3, "22 28 0:21 / /sys rw,nosuid,node"..., 1024) = 1024
read(3, "d-cgroups-agent,name=systemd\n34 "..., 1024) = 1024
read(3, "dev,noexec,relatime shared:21 - "..., 1024) = 1024
read(3, "ortname=mixed,errors=remount-ro\n"..., 1024) = 285
read(3, "", 1024)                       = 0
close(3)                                = 0
open("/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache", O_RDONLY) = 3
close(3)                                = 0
write(1, "Filesystem      Size  Used Avail"..., 49Filesystem      Size  Used Avail Use% Mounted on
) = 49
write(1, "/dev/nvme0n1p9   56G  8.7G   45G"..., 40/dev/nvme0n1p9   56G  8.7G   45G  17% /
) = 40
close(1)                                = 0
close(2)                                = 0
+++ exited with 0 +++