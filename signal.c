#include "bombardier.h"

extern struct struc_state state;

void resizehandler(int signum)
{
    state.shouldpause=1;
    endwin();
}

int initsignal()
{
    signal(SIGWINCH, resizehandler);
    
    return 1;
}

void ungetchhandler(int signum)
{
    endwin();
    refresh();
}

int dropsignal()
{
    signal(SIGWINCH, ungetchhandler);
    
    return 1;
}
