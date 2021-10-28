#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <cctype>
#include <iostream>
using namespace std;

#define UP 0//w
#define DOWN 1//s
#define LEFT 2//a
#define RIGHT 3//d
#define SUBMIT 4 // �����̽���

int keyControl();
void eageDraw(); //�簢�� �׵θ�
int menuDraw();
void gotoxy(int, int);
void customerCare();
void designerManagement();
void reservationStatus();
CONSOLE_SCREEN_BUFFER_INFO presentCur;

int main() {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	system(" mode  con lines=40   cols=120 "); 
	
	int menukey = menuDraw();
	switch (menukey)
	{
	case 0: {
		customerCare();
		break;
	}
	case 1: {
		designerManagement();
		break;
	}
	case 2: {
		reservationStatus();
		break;
	}
	case 3: {
		return 0;
	}
	default:
		break;
	}
	return 0;
}
int menuDraw() {
	int x = 50;
	int y = 18;
	
	gotoxy(x - 2, y);
	cout << ">  �� ����";
	gotoxy(x, y +1);
	cout << " �����̳� ����";
	gotoxy(x, y +2);
	cout << " ���� ��Ȳ";
	gotoxy(x, y +3);
	cout << " ��	��";

	while (true) {
		int key = keyControl();
		switch (key) {
		case UP: {
			if (y > 18) {
				gotoxy(x - 2, y);
				cout << "  ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 21) {
				gotoxy(x - 2, y);
				cout << "  ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}

		case SUBMIT: {
			return (y - 18); }
		}
	}
}
void customerCare() {
	system("cls");
	cout << "�������Դϴ�" << endl;
}
void designerManagement() {
	system("cls");
	cout << "�����̳ʰ���" << endl;
}
void reservationStatus() {
	system("cls");
	cout << "���� ��Ȳ �Դϴ�" << endl;
}
int keyControl() {
	char press = _getch();

	switch (press)
	{
		case 'w': case 'W': {
			return UP; 
		}
		case 'a': case 'A': {
			return LEFT;
		}
		case 's': case 'S': {
			return DOWN;
		}
		case 'd': case 'D': {
			return RIGHT;
		}
		case ' ': {
			return SUBMIT;
		}
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}