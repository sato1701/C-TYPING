#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "my_include.h"

#define cont_count_MAX 15

extern struct Words contents[50];

void type_word(const int FILE_NUM, int *success_count, int *all_count){
	int cont_count = 0;
	int cont_index = 0;
	int word_index = 0;
	*success_count = 0;
	*all_count = 0;
	char tmp = '\0';
	char show_word[30] = "";

	system("cls");
	for(int i=3; i>0; i--){
		printf("%d...", i);
		Sleep(1000);
	}

	while(cont_count < cont_count_MAX){
		do{
			cont_index = rand() % FILE_NUM;
		}while(contents[cont_index].WasUsed);
		contents[cont_index].WasUsed = TRUE;

		while(contents[cont_index].word[word_index] != '\0'){

			system("cls");
			printf("typing miss ... %2d\n\n", *all_count - *success_count);
			puts(contents[cont_index].word);
			if(tmp == ' ' && tmp == contents[cont_index].word[word_index-1])
				strcat(show_word, "_");
			else
				strncpy(show_word, contents[cont_index].word, word_index);
			puts(show_word);
			tmp = getch();

			if(tmp == 0x1b){
				printf("FORCED TERMINATION");
				puts("It ends after 3 seconds.");
				Sleep(3000);
				exit(0);
			}
			if(tmp == contents[cont_index].word[word_index]){
				word_index++;
				*success_count+=1;
			}
			if(0x20 <= tmp || tmp <= 0x7f)
			*all_count+=1;
		}
		cont_count++;
		word_index = 0;
		for(int k = 0; k < 30; k++)
			show_word[k] = '\0';
	}
}

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
	else
		return 0;

	if(datafile == NULL){
		system("cls");
		printf("An error occurred while reading the file.\n");
		puts("It ends after 3 seconds.");
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

