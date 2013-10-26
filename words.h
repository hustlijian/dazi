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

//���һ�����ʵ�������
int addWord();
//ɾ��һ���ַ� 
int deleteChar(char c);
//�ж��Ƿ����������
int hasWord(char str);
//���еĵ�����
int wordLength();
//���е�������һ��
void downWords();
//���ô��ڻ�����
void setWindowsBuffer(char *buffer);
//��ʾ���е��ʣ�������
void showWords();
//����ȡ���Ƿ�����
void setSeqence(int flag);

//���е������� 
extern int total;
#endif