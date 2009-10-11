/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */

int initdsp();
int resizedsp(int start);
void closedsp();
void step_state_bomb(struct struc_state * state, struct struc_texts *texts);
void step_state_plane(struct struc_state * state);
void display_state(struct struc_state * state, struct struc_texts *texts);
void rh(unsigned int numofblocks, unsigned char min, unsigned char max, unsigned char houses[WIDTH], unsigned int *sum);
void welcomescreen();
int winlosewindow(struct struc_state *state);
char * printhof(char names[9][21], char dates[9][11], int scores[9], unsigned char numoffame, unsigned char nowres, int score);
void hof(struct struc_state *state);
int seltext(int houses_text[WIDTH], struct struc_texts *texts, int houselen);
void resizehandler(int signum);
int initsignal();
int dropsignal();
int gx(int x);
int gy(int y);
void gerase();
void fillspace();
