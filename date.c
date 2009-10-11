/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char * ascdate()
{
    time_t timet;
    struct tm *tm;
    static char *retstr;

    retstr=malloc(11);
    timet=time(NULL);
    tm=localtime(&timet);
    sprintf(retstr, "%4d-%.2d-%.2d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);

    return retstr;
}
