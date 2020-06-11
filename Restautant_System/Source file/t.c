#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

struct snake
{
	int x;
	int y;
}s[50];

struct food
{
	int x;
	int y;		
}f;



int length = 3;
char direct = 'w';
char temp='w';
int eats = 0;
int flag=0;
int a=0;

void game(void)
{
		while (1)
	{
		a=0; 
		menu();
		isnake();
		system("cls");
		while (a)
		{
			
			gotoxy(0, 0);
			map();
			Sleep(300);
			changedirect();
			move();
			updatas();
			if (die())
				break;
		}
	}
}

void map()
{
	int  i=0;
	for (i = 0; i < 30; i++)
	{
		printf("¡ª");
	}
	printf("\n");
	for (i = 0; i < 30; i++)
	{
		printf("¡ª");
	}
	
	for (i = 0; i < 26; i++)
	{
		gotoxy(0, i+2);
		printf("||");
		gotoxy(58, i+2);
		printf("||");
	}
	gotoxy(0, 28);
	for (i = 0; i < 30; i++)
	{
		printf("¡ª");
	}
	printf("\n");
	for (i = 0; i < 30; i++)
	{
		printf("¡ª");
	}
}

void changedirect()
{
	if (_kbhit())
		temp = _getch();
	if (direct == 'w'&&temp == 's');
	else if (direct == 'd'&&temp == 'a');
	else if (direct == 'a'&&temp == 'd');
	else if (direct == 's'&&temp == 'w');
	else
	{
		direct = temp;
	}

}

void move()
{
	int i=0;
	if (eat())
	{
		s[length].x = f.x;
		s[length].y = f.y;
		length++;
	}
	for (i = 0; i < length -1; i++)
	{
		s[length-i - 1] = s[length-i-2];
	}
	switch (direct)
	{
		case 'w':s[0].y--; break;
		case 'a':s[0].x--; break;
		case 's':s[0].y++; break;
		case 'd':s[0].x++; break;
	default:
		break;
	}
	
}

void isnake()
{
	int i=0;
	s[0].x = 20;
	s[1].x = 20;
	s[2].x = 20;
	s[0].y = 11;
	s[1].y = 12;
	s[2].y = 13;
	for (i = 0; i < length; i++)
	{
		gotoxy(s[i].x, s[i].y);
		printf("a");
	}
}

void updatas()
{
		int i=0;
	system("cls");
	for (i = 0; i < length; i++)
	{
		gotoxy(s[i].x, s[i].y);
		printf("a");
	}
	formfood();
	
}

int eat(void)
{

	if (s[0].x == f.x&&s[0].y == f.y)
	{
		eats = 1;
		return 1;
	}
	else
		return 0;

}

void formfood()
{
	if (flag == 0||eats==1)
	{
		srand(time(0));
		f.x = rand() % (56) + 2;
		f.y = rand() % (26) + 2;
		flag = 1;
		eats = 0;
	}
	gotoxy(f.x, f.y);
	printf("O");
}

int die()
{
	if (s[0].x > 57 || s[0].x < 2 || s[0].y>27 || s[0].y < 2)

	{
		system("cls");
		gotoxy(70, 0);
		printf("Game Over ");
		gotoxy(70, 2);
		printf("Your score is %d",length);
		Sleep(2500);
		return 1;
	}
	else
		return 0;
}

void gotoxy(int a, int b)
{
	COORD Head;
	Head.X = a;
	Head.Y = b;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, Head);
}

void menu(void)
{
	char ch='a';
	gotoxy(0,0); 
	printf("*********************************************\n");
	printf("*********************************************\n");
	printf("\t\t\t1£©start\n");
	printf("\t\t\t2£©exit\n");
	scanf("%c",&ch);
	switch (ch)
	{
		case '1': a = 1; break;
		case '2': exit(1); break;
	default:
		{ 
		a = 0;
		break; 
		} 
	}
}
