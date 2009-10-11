/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */

#include "bombardier.h"

void step_state_plane(struct struc_state * state)
{
    if (HEIGHT-1-((int)(state->x+2)/WIDTH)-state->houses[(state->x+2)%WIDTH]==state->line)
        state->crashed=1;
    else
    {
        state->x++;
        if ((state->x<WIDTH-3) && (state->blocks==0) && (state->line<HEIGHT-2) && (state->x%3==0))
            state->line++;
        if ((state->line==(HEIGHT-1)) && (state->x==(WIDTH-3)))
            state->x=WIDTH;
    }
}

void step_state_bomb(struct struc_state * state, struct struc_texts *texts)
{
    if (state->willbebombed)
    {
        state->bomby++;
        if (state->bomby>HEIGHT-2)
            state->willbebombed=0;
        else if ((HEIGHT-1)-state->houses[state->bombx]==state->bomby)
        {
            if (state->houses_text[state->bombx]==-1)
                state->houses_text[state->bombx]=seltext(state->houses_text, texts, state->houses[state->bombx]);
            if (!state->text)
            {
                free(state->text);
                state->text=NULL;
            }
            if (state->houses_text[state->bombx]!=-1)
                asprintf(&(state->text),texts[state->houses_text[state->bombx]].text);
            state->houses[state->bombx]--;
            state->blocks--;
            state->willbebombed--;
            if (state->willbebombed==0) state->houses_text[state->bombx]=-1;
            state->score++;
        }
    }
}
