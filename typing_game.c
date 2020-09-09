#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "my_include.h"

int main(){
	const int FILE_NUM = word_read();	//èâä˙âª
	int success_count, all_count;
	clock_t time_start, time_end;
	srand((unsigned)time(NULL));
	int game_type;

	do{
		system("cls");
		show_title();
		game_type = menu();
	}while(!game_type);

	time_start = clock();
	switch(game_type){
		case 1://word-mode
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

	puts("Ç»Ç…Ç©ÉLÅ[ÇâüÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB");
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
