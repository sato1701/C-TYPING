#ifndef MY_INCLUDE_H
#define MY_INCLUDE_H

int word_read();		//input.c

void calc_show(double, int, int);	//main.c
int get_cursor();
void show_title();
int menu();

void type_word(int, int*, int*);	//games.c

struct Words{
	char word[30];
	_Bool WasUsed;
};

#endif

