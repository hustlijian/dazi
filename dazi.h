#ifndef DAZI_H
#define DAZI_H
#include "words.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#pragma comment(lib,"Winmm.lib")

#define  WIDTH 35
#define  HEIGHT 38
//������ɫ

#define F_BLUE    0x1 
#define F_GREEN   0x2 
#define F_AQUA    0x3 
#define F_RED     0x4 
#define F_PURPLE  0x5 
#define F_YELLOW  0x6 
#define F_WHITE   0x7 
#define F_Gray    0x8 
#define F_Light_Blue     0x9 
#define F_Light_Green    0xA 
#define F_Light_Aqua     0xB
#define F_Light_Red      0xC 
#define F_Light_Purple   0xD 
#define F_Light_Yellow   0xE 
#define F_Brigt_white    0xF 

#define B_BLACK   0x00
#define B_BLUE    0x10 
#define B_GREEN   0x20
#define B_AQUA    0x30
#define B_RED     0x40
#define B_PURPLE  0x50 
#define B_YELLOW  0x60 
#define B_WHITE   0x70 
#define B_Gray    0x80 
//������������
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//ѡ������enter
#define KEY_OK	13
//�˳���:ctrl+X
#define KEY_QUIT 24
//���ü���Esc
#define KEY_ESC	27

//��ʱ��ʱ��
#define TIME_DELAY	1500
//����
#define LEVEL_NUM	3
//��ʱ������
#define RESOLUTION 1

extern HANDLE hOut;
extern CONSOLE_SCREEN_BUFFER_INFO bBackInfo; //���ڻ�������Ϣ
extern words specailOne;

int Init();
int Quit();
int Run();
//ʧ��
void fail();
#endif