#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Words{
	char content[20];
	_Bool WasUsed;
} words[50];

int data_read();

int main(){
	const int FILE_NUM = data_read();

	for(int i = 0; i < FILE_NUM; i++)
		printf("%s\n", words[i].content);
	return 0;
}

int data_read(){
	FILE *datafile;
	int file_num = 0;
	int words_end;

	datafile = fopen("WordsFile.txt", "r");
	if(datafile == NULL){
		printf("ファイルの読み取りでエラーが発生しました。\n");
		exit(1);
	}

	fscanf(datafile, "%d\n", &file_num);
	for(int i=0; i < file_num; i++){
		fgets(words[i].content, 20, datafile);
		words_end = strlen(words[i].content)-1;
		words[i].content[words_end] = '\0';
	}

	fclose(datafile);

	return file_num;
}
