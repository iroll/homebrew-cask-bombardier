// Bombardier
// The GNU Bombing utility
// (C)opyright Risko Gergely, 2001.
// Can be licensed under the terms of GPL v2 or above

#include "bombardier.h"
#include "texts.h"

struct struc_state state;
int maxx, maxy;

void init_state(struct struc_state * state)
{
    int i;
    
    for (i=0;i<WIDTH;i++) 
    {
	state->houses_text[i]=-1;
    }
    rh((int)(state->city*ADDBLOCK/(state->city+1))+DEFBLOCK,MINSIZE,MAXSIZE,state->houses,&(state->blocks));
    state->numofblocks=state->blocks;
    state->line=0;
    state->willbebombed=0;
    state->crashed=0;
    state->text=NULL;
}

int seltext(int houses_text[WIDTH], struct struc_texts *texts, int houselen)
{
    int i,retval=-1;
    unsigned char busytexts[NUM_OF_TEXTS];
    int randtexts[NUM_OF_TEXTS];
    int howmany=0;
    int sorsolt;
        
    for (i=0;i<NUM_OF_TEXTS;i++) busytexts[i]=0;
    for (i=0;i<WIDTH;i++) if (houses_text[i]!=-1) busytexts[houses_text[i]]=1;
    for (i=0;i<NUM_OF_TEXTS;i++)
    {
	if ((texts[i].minfloor<=houselen) && (texts[i].maxfloor>=houselen) &&
	    (!busytexts[i]))
	{
	    randtexts[howmany]=i;
	    howmany++;
	}
    }
    if (howmany)
    {
	sorsolt=randtexts[(int) (((float) howmany)*rand()/(RAND_MAX))];
	retval=sorsolt;
    }
    else
    {
	retval=-1;
    }
    return retval;
}

void events(int getret, struct struc_state *state)
{
    if ((getret == ' ') && (!state->willbebombed) && (state->line<HEIGHT-2))
    {
	state->score--;
        state->willbebombed=DESTROY;
	state->bombx=(state->x+1)%WIDTH;
	state->bomby=state->line+(int)((state->x+1)/WIDTH);
        flushinp();
    }
    else if ((getret == 'p') || (getret == 'P') || (state->shouldpause))
    {
	if (state->shouldpause)
	{
	    nodelay(stdscr,FALSE);
	    resizedsp(0);
	    nodelay(stdscr,TRUE);
	}
	display_state(state, texts);
        mvprintw(gy(HEIGHT-1), gx(0), "PAUSED! Any key to continue!"); clrtoeol();
	refresh();
	initsignal();
        nodelay(stdscr, FALSE);
        getch();
	nodelay(stdscr, TRUE);
	state->shouldpause=0;
    }
    else if ((getret == 'q') || (getret == 'Q'))
    {
        nodelay(stdscr, 0);
        mvprintw(gy(HEIGHT-1), gx(0), "If you really want to quit, press 'q' once again! Another key will continue!"); clrtoeol();
        getret=getch();
        nodelay(stdscr, 1);
        if ((getret == 'q') || (getret == 'Q')) state->exit=1;
    }
    else if ((getret >= '1') && (getret <= '9'))
    {
        unsigned char speed;

        speed=getret-48;
        state->delay=((USECSLEEP)/speed);
    }
}

int main()
{
    struct timeval tv;
    struct timeval ue,uu,forbomb;
    
    gettimeofday(&tv,NULL);
    srand(tv.tv_sec*tv.tv_usec);
    state.score=0;
    state.delay=USECSLEEP;
    state.exit=0;
    state.city=1;
    state.text=NULL;
    state.shouldpause=0;
    if (!initdsp())
    {
	fprintf(stderr, "The initialization of display was unsuccessfull! Exiting!\n");
	return 1;
    }
    else
    {
	welcomescreen();
	initsignal();
        do
	{
	    if (!state.text)
	    {
		free(state.text);state.text=NULL;
	    }
    	    init_state(&state);
	    while ((!state.crashed) && ((state.line<HEIGHT-2)||(state.blocks)) && (!state.exit)) 
	    {
		unsigned char k=1;
	    
    		state.x=0;
    		while ((state.x<WIDTH) && ((state.line<HEIGHT-2)||(state.blocks)) && (!state.crashed) && (!state.exit))
	        {
		    int getret;

	    	    getret=getch();
		    if (getret!=ERR) events(getret, &state);
		    gettimeofday(&state.tvusleeputan, NULL);
	    	    step_state_plane(&state);
		    if (state.willbebombed)
		    {
		        gettimeofday(&forbomb, NULL);
			forbomb.tv_usec+=1000000*(forbomb.tv_sec-state.tvusleeputan.tv_sec);
		        for (k=0;(k<BOMBFAST) && (state.willbebombed);k++)
			{
			    step_state_bomb(&state, texts);
		    	    display_state(&state, texts);
	    		    state.bombsleep=(state.delay-(forbomb.tv_usec-state.tvusleeputan.tv_usec))/BOMBFAST/2;
			    refresh();
			    if (state.bombsleep>20000)
			    {
				usleep(state.bombsleep);
			    }
		        }
		    }
		    else
		        display_state(&state, texts);
		    gettimeofday(&state.szamolashoz, NULL);
		    state.szamolashoz.tv_usec+=1000000*(state.szamolashoz.tv_sec-state.tvusleeputan.tv_sec);
	    	    state.usleepelni+=state.delay-(state.szamolashoz.tv_usec-state.tvusleeputan.tv_usec);
		    if (state.usleepelni>0)
		    {
		        gettimeofday(&ue, NULL);
		        usleep(state.usleepelni);
		        gettimeofday(&uu, NULL);
		        state.usleepelni-=(uu.tv_sec-ue.tv_sec)*1000000+(uu.tv_usec-ue.tv_usec);
		    }
	        }
	        state.line++;
	    }
	    if ((!state.crashed) && (!state.exit))
	    {
	        state.line=HEIGHT-2;
	        state.text="THE LANDING WAS SUCCESSFULL!!! CONGRATULATIONS!";
	        for (;state.x<WIDTH-2;state.x++)
		{
	    	    display_state(&state, texts);
		    usleep(state.delay);
		}
		flushinp();
	    }
	} while (winlosewindow(&state));
	closedsp();
    }
    
    return 0;
}
