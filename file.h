#ifndef FILE_H
#define FILE_H

#include "words.h"
#define MAX_PATH_LENGHT	 124

//读取文件初始化单词表
int setFile();
//设置单词文件的名字
int setFilename(char *path);

extern char word[MAX_WORD_COUNT][MAX_WORD_LENGHT];
extern int total_word;
#endif