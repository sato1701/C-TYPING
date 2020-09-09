#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_include.h"

int word_read(){
	FILE *datafile;
	int file_index = 0;
	int word_end;

	datafile = fopen("WordsFile.txt", "r");
	if(datafile == NULL){
		printf("ファイルの読み取りでエラーが発生しました。\n");
		exit(1);
	}

	while((fgets(contents[file_index].word, 20, datafile)) != NULL){
		word_end = strlen(contents[file_index].word)-1;
		contents[file_index].word[word_end] = '\0';
		file_index++;
	}

	fclose(datafile);

	return file_index;
}
