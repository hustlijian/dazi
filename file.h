#ifndef FILE_H
#define FILE_H

#include "words.h"
#define MAX_PATH_LENGHT	 124

//��ȡ�ļ���ʼ�����ʱ�
int setFile();
//���õ����ļ�������
int setFilename(char *path);

extern char word[MAX_WORD_COUNT][MAX_WORD_LENGHT];
extern int total_word;
#endif