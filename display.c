/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */
#include "bombardier.h"
#include "VERSION"

void fillspace()
{
    int i,j;

    for (i=0;i<maxx;i++)
        for (j=0;j<maxy;j++) if (i<maxx/2-WIDTH/2 || i>=maxx/2+WIDTH/2 || j<maxy/2-HEIGHT/2 || j>maxy/2+HEIGHT/2) mvaddch(j,i,'.');
}

void gerase()
{
    erase();
    fillspace();
}

int resizedsp(int start)
{
    int getret;
    fd_set fds;

    if (start) getret=' ';
    else getret='a';
    dropsignal();
    refresh();
    getmaxyx(stdscr, maxy, maxx);
    while ((maxy<HEIGHT+1) || (maxx<WIDTH) || (getret!=' '))
    {
        FD_ZERO(&fds);FD_SET(0, &fds);
        erase();
        printw("Current size: %dx%d. Wanted size: %dx%d.\n", maxx, maxy, WIDTH, HEIGHT+1);
        if (maxy>=HEIGHT+1 && maxx>=WIDTH) printw("Press SPACE to continue!\n");
        refresh();
        select(1, &fds, NULL, NULL, NULL);
        getret=getch();
        endwin();
        refresh();
        getmaxyx(stdscr, maxy, maxx);
    }
    gerase();
    refresh();
    return 1;
}

int initdsp()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    curs_set(0);

    return 1;
}

void closedsp()
{
    flushinp();
    erase();
    refresh();
    endwin();
}

void welcomescreen()
{
    int l;
    fd_set fds;

    nodelay(stdscr,TRUE);
    do
    {
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        endwin();
        resizedsp(1);
        gerase();
        mvprintw(gy( 0),gx(0),"Version: %s", VERSION);
        mvprintw(gy( 5),gx(0),"              /----------------------------------------------\\");
        mvprintw(gy( 6),gx(0),"              |                  Bombardier                  |");
        mvprintw(gy( 7),gx(0),"              |            The GNU Bombing utility           |");
        mvprintw(gy( 8),gx(0),"              |----------------------------------------------|");
        mvprintw(gy( 9),gx(0),"              |     (C) Gergely Risko  <gergely@risko.hu>    |");
        mvprintw(gy(10),gx(0),"              |                  2001 - 2009                 |");
        mvprintw(gy(11),gx(0),"              |                                              |");
        mvprintw(gy(12),gx(0),"              |This program is free software. Can be licensed|");
        mvprintw(gy(13),gx(0),"              |   under the terms of the GNU General Public  |");
        mvprintw(gy(14),gx(0),"              |             License v2 or above.             |");
        mvprintw(gy(15),gx(0),"              |----------------------------------------------|");
        mvprintw(gy(16),gx(0),"              |                    Thanks                    |");
        mvprintw(gy(17),gx(0),"              |                                              |");
        mvprintw(gy(18),gx(0),"              |  Jochen Voss, Janos Lenart, Thimo Neubauer,  |");
        mvprintw(gy(19),gx(0),"              |  Peter Risko, Linus Torvalds, debian people  |");
        mvprintw(gy(20),gx(0),"              \\----------------------------------------------/");
        flushinp();
        refresh();
        select(1, &fds, NULL, NULL, NULL);
        l=getch();
        if (l=='q')
        {
            closedsp();
            exit(1);
        }
    } while (l!=' ');
}

int winlosewindow(struct struc_state *state)
{
    int retval;

    if ((state->crashed) || (state->exit))
    {
        int getret;

        gerase();
        refresh();
        hof(state);
        if (!state->exit)
        {
            mvprintw(gy(HEIGHT-2),gx(25), "/-----------------------------\\");
            mvprintw(gy(HEIGHT-1),gx(25), "|      Try again?([y]/n)      |");
            mvprintw(gy(HEIGHT),gx(25), "\\-----------------------------/");
            nodelay(stdscr,0);
            do
            {
                getret=getch();
            } while (!((getret=='n') || (getret=='N') || (getret=='Y') || (getret=='y') || (getret==10)));
            nodelay(stdscr,1);
        }
        else
        {
            nodelay(stdscr, 0);
            mvprintw(gy(HEIGHT), gx((WIDTH/2)-5), "Any key to quit");
            getch();
            getret='n';
        }
        if ((getret=='n') || (getret=='N'))
        {
            retval=0;
        }
        else
        {
            state->city=1;
            state->score=0;
            state->delay=USECSLEEP;
            retval=1;
        }
    }
    else
    {
        mvprintw(gy(10),gx(22), "/-----------------------------------\\");
        mvprintw(gy(11),gx(22), "| You won! Press a key to continue! |");
        mvprintw(gy(12),gx(22), "\\-----------------------------------/");
        nodelay(stdscr,0);
        getch();
        nodelay(stdscr,1);
        state->city++;
        retval=1;
    }

    return retval;
}

char * citycompute(unsigned char citynum)
{
    static char * ret;

    ret=malloc(16);
    switch (citynum)
    {
        case 1:
            ret="Wien";
            break;
        case 2:
            ret="Lion";
            break;
        case 3:
            ret="Budapest";
            break;
        case 4:
            ret="London";
            break;
        case 5:
            ret="Paris";
            break;
        case 6:
            ret="Madrid";
            break;
        case 7:
            ret="Helsinki";
            break;
        case 8:
            ret="Chicago";
            break;
        case 9:
            ret="Las Vegas";
            break;
        case 10:
            ret="Washington";
            break;
        case 11:
            ret="New York";
            break;
        default:
            free(ret);
            asprintf(&ret,"Unnamed %d", citynum);
    }
    return ret;
}

void display_state(struct struc_state * state, struct struc_texts *texts)
{
    char * statusstr;
    char earth[WIDTH+1];
    int i,j;

    gerase();
    if (state->text) mvprintw(gy(HEIGHT), gx(0), state->text);
    memset(earth, '=', WIDTH);
    earth[WIDTH]=0;
    mvprintw(gy(HEIGHT-1),gx(0),earth);
    if (state->willbebombed)
    {
        if (state->bomby-state->line-state->x/(WIDTH-1)>1) mvprintw(gy(state->bomby-2), gx(state->bombx), "_");
        if (state->bomby-state->line-state->x/(WIDTH-1)>0) mvprintw(gy(state->bomby-1), gx(state->bombx), "|");
        mvprintw(gy(state->bomby-0), gx(state->bombx), "W");
    }
    for (i=0;i<WIDTH;i++)
    {
        for (j=1;j<state->houses[i];j++)
        {
            mvaddch(gy(HEIGHT-j-1), gx(i), '#');
        }
        if (state->houses[i]) mvaddch(gy(HEIGHT-j-1), gx(i), j+64);
    }
    if ((state->willbebombed)&&(state->bomby<=state->line+5))
        mvaddch(gy((state->line)+(state->x+1)/WIDTH), gx((state->x+1)%WIDTH), 'v');
    else mvaddch(gy((state->line)+(state->x+1)/WIDTH), gx((state->x+1)%WIDTH), '-');
    mvaddch(gy((state->line)+(state->x+2)/WIDTH), gx((state->x+2)%WIDTH), 'O');
    switch (state->x%4)
    {
      case 0:
            mvaddch(gy(state->line), gx(state->x), '-');
        break;
      case 1:
            mvaddch(gy(state->line), gx(state->x), '\\');
        break;
      case 2:
            mvaddch(gy(state->line), gx(state->x), '|');
        break;
      case 3:
            mvaddch(gy(state->line), gx(state->x), '/');
        break;
    }
    asprintf(&statusstr, "Blocks: %.4d/%.4d, City: %15s (%.2d), Score: %7d", state->blocks, state->numofblocks, citycompute(state->city), state->city, state->score);
    mvprintw(gy(HEIGHT-1), gx(WIDTH/2-strlen(statusstr)/2), statusstr);
    free(statusstr);
    refresh();
}
