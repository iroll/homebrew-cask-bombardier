/* Bombardier */
/* The GNU Bombing utility */
/* Copyright (C) 2001, 2009 Gergely Risko */
/* Can be licensed under the terms of GPL v3 or above */

struct struc_state
{
    unsigned char houses[WIDTH];
    int houses_text[WIDTH];
    unsigned char line;
    unsigned char x;
    unsigned char bombx;
    unsigned char bomby;
    unsigned char willbebombed;
    unsigned char crashed;
    unsigned int city;
    unsigned int blocks;
    unsigned int numofblocks;
    unsigned char exit;
    unsigned int delay;
    int score;
    char *text;
    struct timeval tvusleeputan, szamolashoz, uu, ue;
    signed long int bombsleep, usleepelni;
    int shouldpause;
};

struct struc_texts
{
    unsigned char minfloor;
    unsigned char maxfloor;
    char *text;
};
