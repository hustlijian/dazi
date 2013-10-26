#include <stdlib.h>
#include <string.h>
#include "words.h"
#include "dazi.h"
#include "file.h"

//单词头
words head[MAX_WORD_COUNT];
int total = 0;
//单词取得是否有序
int sequenceFlag = 0;
//设置取词是否有序
void setSeqence(int flag)
{
	sequenceFlag = flag;
}
//设置str的值
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
//生成一个新的单词结点
void setWord(words *word)
{
	words *temp = word;
	setString(temp->str);
	temp->pos.Y = 0;
	temp->pos.X = (rand() % (WIDTH-strlen(temp->str)));	
	temp->pos.Y -= 1;
}

//添加一个单词到单词链
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

	//删除一个单词
int deleteWord(char c)
{
	int i;

	for (i=0;i<total;i++)
	{
		if (c == head[i].str[0])
			break;
	}
	if (i>=total) //没有 
	{
		return -1;
	}
	//放到当前 的输入单词中
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
//判断是否有这个字符开头的单词，返回位置 
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
//删除字符串第一个字符
void removeHead(char *str)
{
	int i;
	for (i=0; str[i]; i++)
		str[i] = str[i+1];
}
//删除一个字符 
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

//现有的单词数
int wordLength()
{
	return total;
}
//所有单词下落一行
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
//设置窗口缓冲区
void setWindowsBuffer(char *buffer)
{
	int i;
	memset(buffer, ' ', HEIGHT*WIDTH);
	for (i=0; i<total; i++)
		mycopy(buffer+head[i].pos.X+head[i].pos.Y*WIDTH, head[i].str);
}
//显示现有单词，调试用
void showWords()
{
	int i;
	for (i=0; i<total; i++)
		printf("%s(%d,%d) ", head[i].str,head[i].pos.X, head[i].pos.Y);
		//printf("%s ", p->str);
	printf("\n");
}