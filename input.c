#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "my_include.h"

extern struct Words contents[100];

int word_read(int game_type){
	FILE *datafile;
	int file_index = 0;
	int word_end;

	if(game_type == 1)
		datafile = fopen("data/KeyWords.txt", "r");
	else if(game_type == 2)
		datafile = fopen("data/Functions.txt", "r");
	else if(game_type == 3)
		datafile = fopen("data/Sentence.txt", "r");
	else{
		system("cls");
		puts("ファイルの読み取りでエラーが発生しました。");
		puts("3秒後に終了します。");
		Sleep(3000);
		exit(1);
	}

	if(datafile == NULL){
		system("cls");
		printf("ファイルの読み取りでエラーが発生しました。\n");
		puts("3秒後に終了します。");
		Sleep(3000);
		exit(1);
	}

	while((fgets(contents[file_index].word, 30, datafile)) != NULL){
		word_end = strlen(contents[file_index].word)-1;
		contents[file_index].word[word_end] = '\0';
		file_index++;
	}

	fclose(datafile);

	return file_index;
}
