#ifndef INPUT_H
#define INPUT_H

int word_read();
void calc_show(double, int, int);

struct Words{
	char word[20];
	_Bool WasUsed;
} contents[100];

#endif

