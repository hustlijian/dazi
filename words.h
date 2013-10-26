#ifndef WORDS_H
#define WORDS_H

#include <windows.h>
#define MAX_WORD_LENGHT		20
#define MAX_WORD_COUNT		1000

typedef struct _words 
{
	char str[MAX_WORD_LENGHT];
	COORD pos;
}words;

//添加一个单词到单词链
int addWord();
//删除一个字符 
int deleteChar(char c);
//判断是否有这个单词
int hasWord(char str);
//现有的单词数
int wordLength();
//所有单词下落一行
void downWords();
//设置窗口缓冲区
void setWindowsBuffer(char *buffer);
//显示现有单词，调试用
void showWords();
//设置取词是否有序
void setSeqence(int flag);

//现有单词总数 
extern int total;
#endif