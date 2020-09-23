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

struct Words contents[50];
struct Ranking ranking[10];

int main(){
	int success_count, all_count;
	clock_t time_start, time_end;
	srand((unsigned)time(NULL));
	int game_type;

	while(1){
		do{
			system("cls");
			show_title();
			game_type = menu(6);	//return 1-6
		}while(!game_type);
		const int FILE_NUM = word_read(game_type);	//初期化

		switch(game_type){
			case 1:		//word-mode
			case 2:		//Function-mode
			case 3:		//Sentence-mode
				time_start = clock();
				type_word(FILE_NUM, &success_count, &all_count);
				time_end = clock();
				if(game_type == 1)
					result((double)(time_end-time_start) / CLOCKS_PER_SEC, success_count, all_count);
				break;
			case 4:
				rank_show();
				break;
			case 5:
			case 6:
				return 0;
		}
	}
}

void result(double time_diff, int success, int all){
	double wpm;
	double accuracy;
	double score;
	char name[20];
	char yes_no;

	wpm = all / (time_diff / 60);
	accuracy = (double)success / all * 100;
	score = wpm * pow((accuracy/100), 3);

	system("cls");
	printf("time...  %.2lf[s]\n", time_diff);
	printf("WPM....  %.2lf\n", wpm);
	printf("score..  %.2lf\n\n", score);

	puts("Save the date?\t(y/n)");
	do{
		yes_no = getch();
	}while(!(yes_no == 'y' || yes_no == 'n'));
	if(yes_no == 'y'){
		puts("Please enter your name.");
		scanf("%19s", name);
		rank_save(name, score);
	}
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

int menu(){
	static int cursor_y = 0;
	char start_menu[6][50] =
	{	"KeyWord mode",
		"Function mode",
		"Sentence mode",
		"See the ranking (KeyWord mode only)",
		"Help",
		"Quit"
	};

	for(int i=0; i<6; i++){
		if(cursor_y == i)
			printf(" * ");
		else
			printf("   ");
		puts(start_menu[i]);
	}

	int tmp = get_cursor();
	if(tmp == 0)
		return cursor_y+1;

	else{
		if(tmp == -1 && cursor_y-1 >= 0)
			cursor_y--;
		if(tmp == 1 && cursor_y+1 < 6)
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

void rank_save(char now_name[20], float score){
	int insert_num  = 11;
	FILE *rankfile;
	rankfile = fopen("data/ranking.txt", "w");

	rank_read();
	for(int i=0; i<10; i++){
		if(score > ranking[i].score){
			insert_num = i;
			break;
		}
	}
	for(int rank_index = 9; insert_num<rank_index; rank_index--){
		strcpy(ranking[rank_index].name, ranking[rank_index-1].name);
		ranking[rank_index].score = ranking[rank_index-1].score;
		ranking[rank_index].play_time = ranking[rank_index-1].play_time;
	}
	if(insert_num != 11){
		strcpy(ranking[insert_num].name, now_name);
		ranking[insert_num].score = score;
		ranking[insert_num].play_time = time(NULL);
	}

	for(int i=0; i<10; i++)
		fprintf(rankfile, "%s %.2f %ld\n", ranking[i].name, ranking[i].score, ranking[i].play_time);
	fclose(rankfile);
}

void rank_read(){
	FILE *rankfile;
	rankfile = fopen("data/ranking.txt", "r");
	for(int i=0; i<10; i++)
		fscanf(rankfile, "%s %f %ld", ranking[i].name, &ranking[i].score, &ranking[i].play_time);
	fclose(rankfile);
}

void rank_show(){
	struct tm *r_time;
	rank_read();

	system("cls");
	printf("\n");
	puts("----Ranking (TOP 10)----");
	printf( "\n\n"
			"--------Name--------\t"
			"----score----\t"
			"-----time-----\n\n");
	for(int i = 0; i < 10; i++){
		r_time = localtime(&ranking[i].play_time);
		printf("%20s\t   %06.2f\t %d/%02d\t%02d:%02d\n",
			ranking[i].name, ranking[i].score, r_time->tm_mon+1, r_time->tm_mday, r_time->tm_hour, r_time->tm_min);
	}

	printf("\n\n");
	puts("Please pless any key.");
	getch();
}
