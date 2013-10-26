#include <stdlib.h>
#include <string.h>
#include "words.h"
#include "dazi.h"
#include "file.h"

//����ͷ
words head[MAX_WORD_COUNT];
int total = 0;
//����ȡ���Ƿ�����
int sequenceFlag = 0;
//����ȡ���Ƿ�����
void setSeqence(int flag)
{
	sequenceFlag = flag;
}
//����str��ֵ
void setString(char *str)
{
	static int num; 
	if (sequenceFlag)
	{
		num = (num+1) % total_word;
	} else {
		num = rand() % total_word;
	}
	strcpy(str, word[num]);
}
//����һ���µĵ��ʽ��
void setWord(words *word)
{
	words *temp = word;
	setString(temp->str);
	temp->pos.Y = 0;
	temp->pos.X = (rand() % (WIDTH-strlen(temp->str)));	
	temp->pos.Y -= 1;
}

//���һ�����ʵ�������
int addWord()
{
	if (total >= MAX_WORD_COUNT)
	{
		return -1;
	}

	setWord(&head[total]);
	total++;

	return 0;
}

	//ɾ��һ������
int deleteWord(char c)
{
	int i;

	for (i=0;i<total;i++)
	{
		if (c == head[i].str[0])
			break;
	}
	if (i>=total) //û�� 
	{
		return -1;
	}
	//�ŵ���ǰ �����뵥����
	strcpy(specailOne.str, head[i].str + 1);
	specailOne.pos = head[i].pos;
	specailOne.pos.X += 1;

	for (;i<total-1;i++)
	{
		head[i] =head[i+1];
	}
	total--;

	return 0;
}
//�ж��Ƿ�������ַ���ͷ�ĵ��ʣ�����λ�� 
int hasWord(char str)
{
	int i;
	for (i=0;i<total;i++)
	{
		if (head[i].str[0]==str)
			break;
	}
	if (i < total)
		return i;
	return -1;
}
//ɾ���ַ�����һ���ַ�
void removeHead(char *str)
{
	int i;
	for (i=0; str[i]; i++)
		str[i] = str[i+1];
}
//ɾ��һ���ַ� 
int deleteChar(char c)
{
	if (specailOne.str[0] == '\0') //
	{
		return deleteWord(c);
	} else {
		if (c == specailOne.str[0]){
			removeHead(specailOne.str);
			specailOne.pos.X += 1;
			return 0;
		}
	}
	return -1;
}

//���еĵ�����
int wordLength()
{
	return total;
}
//���е�������һ��
void downWords()
{
	int i;
	for (i=0; i<total; i++) {
		head[i].pos.Y += 1;
		if (head[i].pos.Y >= HEIGHT){
			head[i].pos.Y = HEIGHT;
			fail();
			total = 0;
		}
	}
	if (specailOne.str[0] != '\0')
	{
		specailOne.pos.Y += 1;
		if (specailOne.pos.Y >= HEIGHT)
		{
			specailOne.str[0] = '\0';
			fail();
		}
	}
}
void mycopy(char *taget, char *src)
{
	int i =0;
	while(src[i])
		taget[i]=src[i++];
}
//���ô��ڻ�����
void setWindowsBuffer(char *buffer)
{
	int i;
	memset(buffer, ' ', HEIGHT*WIDTH);
	for (i=0; i<total; i++)
		mycopy(buffer+head[i].pos.X+head[i].pos.Y*WIDTH, head[i].str);
}
//��ʾ���е��ʣ�������
void showWords()
{
	int i;
	for (i=0; i<total; i++)
		printf("%s(%d,%d) ", head[i].str,head[i].pos.X, head[i].pos.Y);
		//printf("%s ", p->str);
	printf("\n");
}