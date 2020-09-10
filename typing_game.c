#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include "my_include.h"

#define KB_UP 0x48	//キーボード入力判定用
#define KB_DOWN 0x50
#define KB_LEFT 0x4b
#define KB_RIGHT 0x4d
#define KB_ENTER 0x0D
#define KEY_W 0x77
#define KEY_S 0x73

struct Words contents[100];

int main(){
	const int FILE_NUM = word_read();	//初期化
	int success_count, all_count;
	clock_t time_start, time_end;
	srand((unsigned)time(NULL));
	int game_type;
	char start_menu[6][30] =
	{	"KeyWord mode",
		"Function mode",
		"Sentence mode",
		"See the ranking",
		"Help",
		"Exit"
	};

	do{
		system("cls");
		show_title();
		game_type = menu(start_menu, 6);
	}while(!game_type);

	time_start = clock();
	switch(game_type){
		case 1:		//word-mode
			type_word(FILE_NUM, &success_count, &all_count);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			exit(0);
		}
	time_end = clock();

	calc_show((double)(time_end-time_start) / CLOCKS_PER_SEC, success_count, all_count);

	puts("なにかキーを押してください。");
	getchar();
	return 0;
}

void calc_show(double time_diff, int success, int all){
	double wpm;
	double accuracy;
	double score;

	wpm = all / (time_diff / 60);
	accuracy = (double)success / all * 100;
	score = wpm * pow((accuracy/100), 3);

	system("cls");
	printf("time...  %.2lf[s]\n", time_diff);
	printf("WPM....  %.2lf\n", wpm);
	printf("score..  %.2lf\n\n", score);
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

int menu(const char menu[][30], const int ARRAY_NUM){
	static int cursor_y = 0;

	for(int i=0; i<ARRAY_NUM; i++){
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
		if(tmp == 1 && cursor_y+1 < ARRAY_NUM)
			cursor_y++;
	}
	return 0;
}

void show_title(){
	puts("+------------------+");
	puts("|                  |");
	puts("|   typing_game!   |");
	puts("|                  |");
	puts("+------------------+");
	puts("       make:sato1701\n");
}
