#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "my_include.h"

#define cont_count_MAX 20 //一時的に使用　後に、プレイヤーが設定

extern struct Words contents[100];

void type_word(const int FILE_NUM, int *success_count, int *all_count){
	int cont_count = 0;
	int cont_index = 0;
	int word_index = 0;
	*success_count = 0;
	*all_count = 0;
	char tmp;
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
			strncpy(show_word, contents[cont_index].word, word_index);
			puts(show_word);

			tmp = getch();

			if(tmp == 0x1b){
				printf("強制終了！");
				exit(0);
			}
			if(tmp == contents[cont_index].word[word_index]){
				word_index++;
				*success_count+=1;
			}
			*all_count+=1;
		}
		cont_count++;
		word_index = 0;
		for(int k = 0; k < 30; k++)
			show_word[k] = '\0';
	}
}
