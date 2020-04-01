USAGE:
    ./UnixLs [options] [directory 1 or file 1] [directory 2 or file 2] ...

SAMPLE OUTPUT:

SpenC:Linux-ls-Command spenc$ ./UnixLs -il ~ 
1685298                drwx------  6    spenc  staff  192       Jan 18 2019 16:24  Music 
3681683                drwxr-xr-x  11   spenc  staff  352       Mar 27 2020 13:22  temp 
1076247                drwx------  8    spenc  staff  256       Aug 18 2019 11:59  Pictures 
1166985                drwxr-xr-x  16   spenc  staff  512       Mar 22 2020 19:36  code 
1076249                drwxr-xr-x  16   spenc  staff  512       Mar 28 2020 13:45  Desktop 
1076225                drwx------  75   spenc  staff  2400      Mar 29 2020 20:53  Library 
1685296                drwx------  3    spenc  staff  96        Nov 10 2018 11:12  Movies 
3126676                drwxr-xr-x  3    spenc  staff  96        Jan 28 2019 17:02  Applications 
1151699                drwx------  14   spenc  staff  448       Mar 29 2020 00:28  Dropbox 
1685295                drwx------  4    spenc  staff  128       Mar 22 2020 19:33  Documents 
1076239                drwx------  39   spenc  staff  1248      Mar 29 2020 16:52  Downloads 


SpenC:Linux-ls-Command spenc$ ./UnixLs -i .. 
17486627               Interactive-OS-Simulation
17490747               multi-threaded-chat-program
17145571               1_Assignment
18123243               Linux-ls-Command


SpenC:Linux-ls-Command spenc$ ./UnixLs -l . .. 
.: 
-rwxr-xr-x  1    spenc  staff  13676     Mar 29 2020 22:20  UnixLs 
-rw-r--r--  1    spenc  staff  236       Mar 25 2020 18:57  makefile 
-rw-r--r--  1    spenc  staff  4876      Mar 29 2020 22:20  UnixLs.o 
-rw-r--r--  1    spenc  staff  159115    Mar 29 2020 21:06  part1.pdf 
-rw-r--r--  1    spenc  staff  1398      Mar 29 2020 22:21  README.txt 
-rw-r--r--  1    spenc  staff  21499     Mar 29 2020 21:07  part1.docx 
-rw-r--r--  1    spenc  staff  4818      Mar 29 2020 22:19  UnixLs.c 

..: 
drwxr-xr-x  8    spenc  staff  256       Mar 23 2020 00:05  Interactive-OS-Simulation 
drwxr-xr-x  8    spenc  staff  256       Mar 25 2020 14:32  multi-threaded-chat-program 
drwxr-xr-x  9    spenc  staff  288       Mar 07 2020 17:22  1_Assignment 
drwxr-xr-x  11   spenc  staff  352       Mar 29 2020 22:21  Linux-ls-Command 
