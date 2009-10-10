#define _GNU_SOURCE
#define __GNUC_VA_LIST_1
/*
    The above line is for alpha, because debian porters/admins don't help
    me getting an alpha acc, or boot up lully, faure, etc.
    If it doesn't work I'm sorry. If it push down other archs, sorry.
    Please see the bug report for bombardier which is reported by ivan e moore.

    I give the copyright of the above line to (C) 2001. Ivan E. Moore, James Troup.
*/
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
