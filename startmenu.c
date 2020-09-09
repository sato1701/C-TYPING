#include <stdio.h>
#include <conio.h>
#include "my_include.h"

#define KB_UP 0x48	//キーボード入力判定用
#define KB_DOWN 0x50
#define KB_LEFT 0x4b
#define KB_RIGHT 0x4d
#define KB_ENTER 0x0D
#define KEY_W 0x77
#define KEY_S 0x73

void show_title(){
	puts("+------------------+");
	puts("|                  |");
	puts("|   typing_game!   |");
	puts("|                  |");
	puts("+------------------+");
	puts("       make:sato1701\n");
}

int menu(){
	char menu[6][16] = {"Word mode",
						"Idiom mode",
						"Sentence mode",
						"See the ranking",
						"Help",
						"Exit"
					};
	static int cursor_y = 0;

	for(int i=0; i<6; i++){
		if(cursor_y == i)
			printf(" * ");
		else
			printf("   ");
		puts(menu[i]);
	}

	int tmp = get_cursor();
	if(tmp == 0)
		return cursor_y+1;

	else{
		if(tmp == -1 && cursor_y-1 >= 0)
			cursor_y--;
		if(tmp == 1 && cursor_y+1 <= 5)
			cursor_y++;
	}
	return 0;
}

int get_cursor(){
	CONTINUE:
	switch(getch()){
		case KB_UP:
		case KEY_W:
			return -1;

		case KB_DOWN:
		case KEY_S:
			return 1;

		case KB_ENTER:
			return 0;
		default:
			goto CONTINUE;
	}
}
