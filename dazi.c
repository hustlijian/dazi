#include "dazi.h"
#include "words.h"
#include "file.h"

char title[] = "÷÷����";
HANDLE hOut; 
CONSOLE_SCREEN_BUFFER_INFO bBackInfo; //���ڻ�������Ϣ
CONSOLE_CURSOR_INFO cursorInfo;  //������Ϣ
UINT cp;
words specailOne;  //���ڴ���ĵ���
char screenBuffer[WIDTH*HEIGHT]; //���ڵĻ���������
UINT timerID; //��ʱ����ID
int delay = TIME_DELAY;
WORD attribute = F_Light_Green ; //��Ļ��ʾ����
WORD specailAttri = F_Light_Red; //��ǰ������ʾ���������ʽ
int musicFlag = 1; //�Ƿ�������
int failFlag = 0; //�Ƿ�ʧ��
//����Ļ
void clearScreen();
void PASCAL refresh(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2) ;

//��ʼ����ʱ�����ô���
int setWindow()
{
	SMALL_RECT rect;
	COORD size;
	
	COORD home= {0,0};
	DWORD result;

	rect.Left = rect.Top = 0;
	rect.Right = WIDTH -1;
	rect.Bottom = HEIGHT -1;
	SetConsoleWindowInfo(hOut, TRUE, &rect);
	
	size.X = WIDTH;
	size.Y = HEIGHT;
	SetConsoleScreenBufferSize(hOut, size);
	FillConsoleOutputAttribute(hOut, attribute, WIDTH*HEIGHT, home,&result);

	return 0;
}
//��ʼ��
int Init()
{
	CONSOLE_SCREEN_BUFFER_INFO bBackInfo; //���ڻ�������Ϣ
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
	cp = GetConsoleOutputCP(); //����ҳ
	SetConsoleOutputCP(437);
	GetConsoleScreenBufferInfo(hOut, &bBackInfo); //���洰����Ϣ
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cursorInfo);
	SetConsoleTitle(title);
	total = 0; //���е�������Ϊ0
	specailOne.str[0] = '\0'; //��
	
	if (setWindow())
	{
		printf("set window error!\n");
		return -1;
	}	
	srand( (unsigned)time( NULL ) );//�����������
	if (setFile())
	{
	//	printf("file open error!\n");
		return -1;
	}

	return 0;
}

//�˳�ʱ�ָ�
int Quit()
{
	SetConsoleScreenBufferSize(hOut, bBackInfo.dwSize);
	SetConsoleTextAttribute(hOut, bBackInfo.wAttributes);
	SetConsoleWindowInfo(hOut, FALSE, &(bBackInfo.srWindow));
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cursorInfo);
	SetConsoleOutputCP(cp);
	return 0;
}
//��ʾ��ǰ�ĵ���
void showSpecailWord()
{
	static int len;
	static COORD pos;
	DWORD result;

	FillConsoleOutputAttribute(hOut, attribute,len, pos, &result); //�ָ���ʾ����
	len = strlen(specailOne.str);
	pos = specailOne.pos;

	if (specailOne.str[0] == '\0')
		return ;
	FillConsoleOutputAttribute(hOut, specailAttri,strlen(specailOne.str), pos, &result);
	WriteConsoleOutputCharacter(hOut, specailOne.str, strlen(specailOne.str),pos, &result);
}
void showScreenBuffer()
{
	COORD home = {0,0};
	DWORD result;
	setWindowsBuffer(screenBuffer);
	WriteConsoleOutputCharacter(hOut, screenBuffer,WIDTH*HEIGHT,home,&result);
	showSpecailWord();
}
void resumeTimer()
{
	timerID = timeSetEvent(10, RESOLUTION, refresh, 0, TIME_ONESHOT);//��������
	if (timerID == 0)
	{
		printf("timer error!\n");
	}
}
void startTimer()
{
	if (failFlag)
		return ;	
	timerID = timeSetEvent(delay, RESOLUTION, refresh, 0, TIME_ONESHOT);
	if (timerID == 0)
	{
		printf("timer error!\n");
	}
}
void stopTimer()
{
	timeKillEvent(timerID);
}
//����Ļ
void clearScreen()
{
	COORD home = {0,0};
	DWORD result;
	memset(screenBuffer, ' ', HEIGHT*WIDTH);
	WriteConsoleOutputCharacter(hOut, screenBuffer,WIDTH*HEIGHT,home,&result);
}
void PASCAL refresh(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2) 
{ 
	addWord();
	downWords();
	showScreenBuffer();
	//showWords();
	startTimer();
}
//��ʾ�ַ���
void showString(char *str, COORD pos, WORD attri)
{
	DWORD result;
	FillConsoleOutputAttribute(hOut, attri,strlen(str),pos, &result);
	WriteConsoleOutputCharacter(hOut, str, strlen(str),pos, &result);
	
}


//���ùؿ�
void showLevel()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 3;
	int totalChoose = 4;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Speed level", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.Slow", pos, attribute);
	pos.Y += 2;
	showString("2.Faster", pos, attribute);
	pos.Y += 2;
	showString("3.Fastest", pos, specailAttri);
	pos.Y += 2;
	showString("0.Back", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose>=0 && choose <= 2)
	{
		//0: 1500
		//1: 1000
		//2: 500
		delay = TIME_DELAY - (choose * TIME_DELAY) / LEVEL_NUM;
	}
}
void showMusicSettings()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 0;
	int totalChoose = 2;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Music settings", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.On", pos, attribute);
	pos.Y += 2;
	showString("0.Off", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose == 0) //on
	{
		musicFlag = 1;
	} else {
		musicFlag = 0;
	}
}
//����ǰ��ɫ
void setForeColorSettings()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 10};
	int choose = 15;
	int totalChoose = 16;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("fore ground color", pos, specailAttri);
	pos.Y += 4;
	pos.X += 1;
	showString("1. Blue", pos, F_BLUE);
	pos.Y += 1;
	showString("2. Green", pos, F_GREEN);
	pos.Y += 1;
	showString("3. Aqua", pos, F_AQUA);
	pos.Y += 1;
	showString("4. Red", pos, F_RED);
	pos.Y += 1;
	showString("5. Purple", pos, F_PURPLE);
	pos.Y += 1;
	showString("6. Yellow", pos, F_YELLOW);
	pos.Y += 1;
	showString("7. White", pos, F_WHITE);
	pos.Y += 1;
	showString("8. Gray", pos, F_Gray);
	pos.Y += 1;
	showString("9. Light Blue", pos, F_Light_Blue);
	pos.Y += 1;
	showString("10.Light Green", pos, F_Light_Green);
	pos.Y += 1;
	showString("11.Light Aqua", pos, F_Light_Aqua );
	pos.Y += 1;
	showString("12.Light Red", pos, F_Light_Red);
	pos.Y += 1;
	showString("13.Light Purple", pos, F_Light_Purple);
	pos.Y += 1;
	showString("14.Light Yellow", pos, F_Light_Yellow);
	pos.Y += 1;
	showString("15.Light White", pos, F_Brigt_white);
	pos.Y += 1;
	showString("0.Back", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*1;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*1;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose<15 && choose >=0)
	{
		attribute &= 0xf0;
		attribute |= choose+1;
	}
}
//���ñ���ɫ
void setBackColorSettings()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 10};
	int choose = 9;
	int totalChoose = 10;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Background color", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.Black", pos, F_WHITE|B_BLACK);
	pos.Y += 2;
	showString("2.Blue", pos, F_WHITE|B_BLUE);
	pos.Y += 2;
	showString("3.Green", pos, F_WHITE|B_GREEN);
	pos.Y += 2;
	showString("4.Aqua", pos, F_WHITE|B_AQUA);
	pos.Y += 2;
	showString("5.Red", pos, F_WHITE|B_RED);
	pos.Y += 2;
	showString("6.Purple", pos, F_WHITE|B_PURPLE);
	pos.Y += 2;
	showString("7.Yellow", pos, F_WHITE|B_YELLOW);
	pos.Y += 2;
	showString("8.White", pos, F_BLUE|B_WHITE);
	pos.Y += 2;
	showString("9.Gray", pos, F_WHITE|B_Gray);
	pos.Y += 2;
	showString("0.Back", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose<9 && choose >=0)
	{
		attribute &= 0xf;
		attribute |= choose * 0x10;
		specailAttri &= 0xf;
		specailAttri |= choose * 0x10;
	}
}
//������ɫ
void showColorSettings()
{
	setForeColorSettings();
	setBackColorSettings();
	setWindow();
}
//���õ����ļ�
int showFileSettings()
{
	char path[MAX_PATH_LENGHT];
	clearScreen();
	printf("\ninput the filename: ");
	if(scanf("%s", path)==EOF)
		return -1;
	fflush(stdin);
	setFilename(path);
	setWindow();
	total = 0;
	return 0;
}
//����ȡ��˳��
void showSeqenceSettings()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 0;
	int totalChoose = 2;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Words sequence", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.Yes", pos, attribute);
	pos.Y += 2;
	showString("0.No", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose == 0) //on
	{
		setSeqence(1);
	} else {
		setSeqence(0);
	}
}

//���ý���
void showSettings()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 0;
	int totalChoose = 6;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Settings", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.Music", pos, attribute);
	pos.Y += 2;
	showString("2.Color", pos, attribute);
	pos.Y += 2;
	showString("3.File", pos, attribute);
	pos.Y += 2;
	showString("4.Sequence", pos, attribute);
	pos.Y += 2;
	showString("5.Exit", pos, attribute);
	pos.Y += 2;
	showString("0.Back", pos, attribute);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);

	switch (choose) {
	case 0: //music
		showMusicSettings();
		break;
	case 1: //color
		showColorSettings();
		break;
	case 2: // file
		showFileSettings();
		break;
	case 3: // sequence
		showSeqenceSettings();
		break;
	case 4: //Exit
		fail();
		break;
	default: //back
			break;
	}
	setWindow(); //�ָ�ͼ����ʾ
}
//�˳����� 
void showQuit()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 0;
	int totalChoose = 2;
	int quit = 0;
	int ypos;
	char c;
	
	clearScreen();
	showString("Do you want quit?", pos, specailAttri);
	pos.Y += 4;
	pos.X += 2;
	showString("1.Yes", pos, attribute);
	pos.Y += 2;
	showString("0.No", pos, attribute);

	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;
	
	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);
		
		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}
	fflush(stdin);
	if (choose == 0)
	{
		Quit();
		exit(0);
	}	
}
//��ʼ����
void showWelcome()
{
	COORD pos= {WIDTH/2 - 10, HEIGHT/2 - 6};
	int choose = 0;
	int totalChoose = 4;
	int quit = 0;
	int ypos;
	char c;

	clearScreen();
	showString("\1!!! welcome game!!! \1", pos, attribute);
	pos.Y += 4;
	pos.X += 4;
	showString("1.Start", pos, attribute);
	pos.Y += 2;
	showString("2.Setting", pos, specailAttri);
	pos.Y += 2;
	showString("3.Level", pos, attribute);
	pos.Y += 2;
	showString("0.Quit", pos, specailAttri);
	
	pos.X -= 2;
	pos.Y -= (totalChoose-1)*2;
	ypos = pos.Y;

	while (quit != 1) {
		//��ʾ���
		showString(" ", pos, specailAttri);
		pos.Y = ypos + choose*2;
		showString("\4", pos, specailAttri);

		c = getch();
		switch(c) {
		case KEY_OK:
			quit = 1;
			break;
		case KEY_QUIT:
			showQuit();
			break;
		default:
			if (c < 0)
			{
				c = getch();
				if (c == KEY_UP || c == KEY_LEFT) //��һ��
				{
					choose = (choose + totalChoose -1) % totalChoose;
				} else if (c == KEY_RIGHT || KEY_DOWN) //��һ��
				{
					choose = (choose + 1) % totalChoose;
				}
			}
			if (c>='0' && c < ('0'+totalChoose))
			{
				choose = c - '0';
				choose = (choose + totalChoose -1) % totalChoose;
			}
			break;
		}
	}

	switch(choose) {
	case 0: //start
		failFlag = 0;
		break;
	case 1: //settings
		showSettings();
		//���û���˳�
		showWelcome();
		break;
	case 2: //level
		showLevel();
		//���û���˳�
		showWelcome();
		break;
	case 3: //quit
		showQuit();
		//���û���˳�
		showWelcome();
		break;
	default: //error
		break;
	}
	setWindow(); //�������ô�����ʾ��Ϣ
}

int Run()
{
	char c;
	showWelcome();
	resumeTimer();
	while (1)
	{
		while(!kbhit()) //�м����� 
			if (failFlag)
				return 0;
		c = getch();
		if (c == KEY_QUIT) //ctrl+x,�˳�
		{
			fflush(stdin);
			stopTimer();
			showQuit();
			resumeTimer();
		}
		if (c == KEY_ESC) //settings
		{
			fflush(stdin);
			stopTimer();
			showSettings();
			resumeTimer();
		}
		if(deleteChar(c) == 0)
		{
			//�ɹ�
			if (musicFlag)
				MessageBeep(MB_ICONASTERISK);
		} else {
			if (musicFlag)
				MessageBeep(MB_ICONHAND);
		}
		showScreenBuffer();
		//showWords();
	}
	showQuit();
	stopTimer();
	return 0;
}
//ʧ��
void fail()
{
	stopTimer();
	failFlag = 1;	
}