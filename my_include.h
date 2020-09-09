#ifndef INPUT_H
#define INPUT_H

int word_read();		//input.c
void calc_show(double, int, int);

int get_cursor();		//startmenu.c
void show_title();
int menu();

void type_word(int, int*, int*);	//games.c

struct Words{
	char word[20];
	_Bool WasUsed;
} contents[100];

#endif

