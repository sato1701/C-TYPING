#include <time.h>
#ifndef MY_INCLUDE_H
#define MY_INCLUDE_H

//main.c
int get_cursor();
void show_title();
void result(double, int, int, int);
int menu();
int word_read(int);
void rank_save(char[], float);
void rank_read();
void rank_show();

//games.c
void type_word(int, int*, int*);

struct Words{
	char word[30];
	_Bool WasUsed;
};
struct Ranking {
	char name[20];
	float score;
	time_t play_time;
};

#endif

