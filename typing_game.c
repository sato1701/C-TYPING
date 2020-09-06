#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

struct Words{
	char word[15];
	_Bool WasUsed;
} contents[50];

int data_read();
void calc_show(double, int, int);

int main(){
	const int FILE_NUM = data_read();
	int c_index = 0;
	int w_index = 0;
	int all_count = 0;
	int success_count = 0;
	char tmp;
	char show_word[15] = "\0";
	clock_t start, end;

	start = clock();

	while(c_index < FILE_NUM){
		while(contents[c_index].word[w_index] != '\0'){

			system("cls");
			printf("typing miss ... %2d\n\n", all_count - success_count);
			puts(contents[c_index].word);
			strncpy(show_word, contents[c_index].word, w_index);
			puts(show_word);

			tmp = getch();

			if(tmp == 0x1b){
				printf("強制終了！");
				exit(0);
			}
			if(tmp == contents[c_index].word[w_index]){
				w_index++;
				success_count++;
			}
			all_count++;
		}
		c_index++;
		w_index = 0;
		for(int k = 0; k < 15; k++)
			show_word[k] = '\0';
	}
	end = clock();

	calc_show((double)(end-start) / CLOCKS_PER_SEC, success_count, all_count);
	return 0;
}

int data_read(){
	FILE *datafile;
	int file_num = 0;
	int word_end;

	datafile = fopen("WordsFile.txt", "r");
	if(datafile == NULL){
		printf("ファイルの読み取りでエラーが発生しました。\n");
		exit(1);
	}

	fscanf(datafile, "%d\n", &file_num);
	for(int i=0; i < file_num; i++){
		fgets(contents[i].word, 20, datafile);
		word_end = strlen(contents[i].word)-1;
		contents[i].word[word_end] = '\0';
	}

	fclose(datafile);

	return file_num;
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
	printf("正確性..  %.2lf\n", accuracy);
	printf("score..  %.2lf\n", score);
}
