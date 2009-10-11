/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */

char *fdgetline(int fd)
{
    char *newline=NULL;
    char buf[1];
    int i=0;
    int eol=0;

    while ((!eol) && (read(fd,buf,1)==1))
    {
        newline=realloc(newline, ++i);
        newline[i-1]=buf[0];
        if (newline[i-1]==10)
        {
            newline[i-1]=0;
            eol=1;
        }
    }
    if ((newline) && (newline[i-1]!=0))
    {
        newline=realloc(newline, ++i);
        newline[i-1]=0;
    }
    return newline;
}
