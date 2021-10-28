//#include <WinSock2.h>
//#include<my_global.h>
#include "mainFunc.h"

#pragma comment(lib,"libmySQL.lib")
//#pragma commecnt(lib,"ws2_32.lib");
using namespace std;

#define UP 0//w
#define DOWN 1//s
#define LEFT 2//a
#define RIGHT 3//d
#define SUBMIT 4 // �����̽���


CONSOLE_SCREEN_BUFFER_INFO presentCur;

void setSelctedXY() {
	x = 80; y = 7;
	gotoxy(x, y);
}
void setTitleXY() {
	x = 54; y = 5;
	gotoxy(x, y);
}
void setMenuXY() {
	x = 50; y = 18;
	gotoxy(x, y);
}

MYSQL* mysql = mysql_init(NULL);
MYSQL_RES* sql_result;
MYSQL_ROW sql_row;
int field;
int i;
char check0[20] = "0";
char check1[20] = "1";
char rs_memo[100];

int main() {
	system("cls");
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	system(" mode  con lines=40   cols=120 ");

	if (!mysql_real_connect(mysql, "localhost", "root", "Suy0Sm0tdo", "hairshop_manager", 3306, NULL, 0))
		fprintf(stderr, "mysql error : %s", mysql_error(mysql));
	else { 
		cout << "����"; 
		mysql_query(mysql, "set session character_set_connection=utf8;");

	}
	mysql_query(mysql, "set session character_set_connection=euckr;");
	mysql_query(mysql, "set session character_set_results=euckr;");
	mysql_query(mysql, "set session character_set_client=euckr;");

	while (true) {
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
	}
	
	return 0;
}

int menuDraw() {
	system("cls");
	setMenuXY();
	gotoxy(x - 9, y-4);
	cout << " **�̿�� ȸ�� ���� ���α׷�**";
	gotoxy(x - 9, y - 3);
	cout << "===============================";

	gotoxy(x - 2, y);
	cout << ">  ���� ����";
	gotoxy(x, y + 1);
	cout << " �����̳� ����";
	gotoxy(x, y + 2);
	cout << " ���� ��Ȳ";
	gotoxy(x, y + 3);
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

	eageDraw("���");
	setTitleXY();
	cout << "* ���� ���� *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     ȸ�� �߰�   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << " ȸ�� ���� ����   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     ������       ";
	gotoxy(x, ++y);
	cout << "------------------";

	
	ChooseCCKey();
	
}
void designerManagement() {
	system("cls");
	eageDraw("�ٹ� �ð�");
	setTitleXY();
	cout << "* �����̳� *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "  �����̳� �߰�   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "�����̳� ���� ����   ";
	gotoxy(x, ++y);
	cout << "------------------";

	
	ChooseDMKey();
	
}
void reservationStatus() {
	system("cls");
	eageDraw("���� �ð�");
	setTitleXY();
	cout << "* ���� ��Ȳ *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     ���� �߰�   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     ���� ����   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "       �޸�    ";
	gotoxy(x, ++y);
	cout << "------------------";
	gotoxy(x, y += 9);
	cout << "------------------";

	
	ChooseRSKey();
	
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
void ChooseCCKey() {
	
	while (true) {
		char press = _getch();
		switch (press)
		{
		case '1': {
			gotoxy(100, 38);
			CC_add();
			break;
		}
		case '2': {
			gotoxy(100, 38);
			CC_revise();
			break;
		}
		case '3': {
			gotoxy(100, 38);
			CC_reward();
			break;
		}
		case '0': {
			menuDraw();
			break;
		}
		}
	}
	
}
void ChooseDMKey() {
	
	while (true) {
		char press = _getch();
		switch (press)
		{
		case '1': {
			gotoxy(100, 38);
			DM_add();
			break;
		}
		case '2': {
			gotoxy(100, 38);
			DM_revise();
			break;
		}
		case '0': {
			menuDraw();
			return;
		}
		}
	}
	
}
void ChooseRSKey() {
	

	while(true){
		char press = _getch();
		switch (press)
		{
		case '1': {
			gotoxy(100, 38);
			RS_add();
			break;
		}
		case '2': {
			gotoxy(100, 38);
			RS_revise();
			break;
		}
		case '0': {
			menuDraw();
			return;
		}
		case 'm':case'M': {
			meno();
		}
		}
	}
	
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void eageDraw(const char* add) {
	x = 20; y = 7;
	gotoxy(x, y);
	cout << "--------------------------------------";
	gotoxy(x, ++y);
	printf("    �̸�    ��ȭ��ȣ  %s    ���", add);
	gotoxy(x, ++y);
	cout << "--------------------------------------";
	gotoxy(x, y += 13);
	cout << "--------------------------------------";

}
void CC_add() {
	char name[15],phone[20], charge[15], detail[45];
	system("cls");

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ȸ�� �߰� *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> charge;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> detail;

	
	char query[255];
	sprintf(query, "select count(*) from customer where name = '%s'; ", name);
	int stat = mysql_query(mysql, query);

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return ;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);

	cout << check1 << endl;

	if (strcmp(sql_row[0], check1) == 0) {
		cout << "�̹� ������ ȸ�� �Դϴ�." << endl;
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		sprintf(query, "insert into customer values('%s', '%s','%s',0,'%s');", name, phone, charge, detail);
		int a = mysql_query(mysql, query);
		cout << "���� ȸ�� �Դϴ�.";
	}

	//customerCare();
}
void CC_revise() {
	char name[15], phone[20], charge[15];
	char sname[15];
	system("cls");
	setMenuXY();

	cout << "������ ȸ���� �̸� : ";
	cin >> sname;
	char nquery[255];
	sprintf(nquery, "select count(*) from customer where name = '%s'; ", sname);
	int stat = mysql_query(mysql, nquery);

	cout << sname << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);
	cout << check1 << endl;

	if (strcmp(sql_row[0], check1) == 0) {
		cout << "ȸ�� ���� ��." << endl;
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* ȸ�� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "��� : ";
		cin >> charge;

		sprintf(nquery, "update customer set name='%s', phone_num='%s',charge='%s' where name='%s'; ", name,phone,charge,sname);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		cout << "fin";
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		cout << "���� ȸ�� �Դϴ�.";
	}

	//system("cls");
	
	//customerCare();
}
void CC_reward() {
	char name[15];
	int price;

	system("cls");
	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ������ *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "���� �ݾ� : ";
	cin >> price;

	char query[255];
	sprintf(query,"select count(*) from customer where name = '%s'; ", name);
	int stat = mysql_query(mysql, query);
	//cout << stat;
	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);

	//cout << "hihi";
	if(stat!=0){
		printf("error : %s", mysql_error(mysql));
		return;
	}

	cout << check1<<endl;
	
	if (strcmp(sql_row[0], check1)==0) {
		cout << "����" << endl;
		sprintf(query, "update customer set reward_point=1000 where name ='%s'; ", name);
		int a = mysql_query(mysql, query);
		//int num = sprintf(query, "select reward_point from customer where name = '%s'; ", name);
		//cout << num;
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		cout << "���� ȸ�� �Դϴ�.";
	}
	
	 
	
	
	//customerCare();
}
void DM_add() {
	char name[15], phone[20], time[45], detail[45];
	system("cls");
	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* �����̳� �߰� *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "�ٹ� �ð�(00 : 00 ~ 00 : 00) : ";
	cin >> time;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> detail;


	char query[255];
	sprintf(query, "select count(*) from designer where name = '%s'; ", name);
	int stat = mysql_query(mysql, query);

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);

	cout << check1 << endl;

	if (strcmp(sql_row[0], check1) == 0) {
		cout << "�̹� �ִ� �����̳� �Դϴ�." << endl;
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		sprintf(query, "insert into designer values('%s', '%s','%s','%s');", name, phone, time, detail);
		int a = mysql_query(mysql, query);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		cout << "���� �����̳� �Դϴ�.";
	}

	//designerManagement();
}
void DM_revise() {
	char name[15], phone[20], time[45];
	char sname[15];
	system("cls");
	setMenuXY();

	cout << "������ �����̳��� �̸� : ";
	cin >> sname;
	char nquery[255];
	sprintf(nquery, "select count(*) from designer where name = '%s'; ", sname);
	int stat = mysql_query(mysql, nquery);

	cout << sname << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);
	cout << check1 << endl;

	if (strcmp(sql_row[0], check1) == 0) {
		cout << "�����̳� ���� ���� ��." << endl;
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* �����̳� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "�ð� : ";
		cin >> time;

		sprintf(nquery, "update designer set name='%s', phone_num='%s',time='%s' where name='%s'; ", name, phone, time, sname);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		cout << "fin";
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		cout << "���� ȸ�� �Դϴ�.";
	}

	//system("cls");

	//customerCare();
}
void RS_add() {
	char name[15], phone[20], rs_time[45], detail[45];
	system("cls");
	setMenuXY();
	
	system("cls");
	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ���� �߰� *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "����ð� : ";
	cin >> rs_time;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> detail;

	char query[255];
	sprintf(query, "insert into reservation(name, phone_num,re_time,details) values('%s', '%s','%s','%s')", name, phone, rs_time, detail);
	int stat = mysql_query(mysql, query);
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	//reservationStatus();
}
void RS_revise() {
	char name[15], phone[20], time[15];
	char sname[15];
	system("cls");
	setMenuXY();

	cout << "������ ȸ���� �̸� : ";
	cin >> sname;
	char nquery[255];
	sprintf(nquery, "select count(*) from reservation where name = '%s'; ", sname);
	int stat = mysql_query(mysql, nquery);

	cout << sname << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	printf("%s\n", sql_row[0]);
	cout << check1 << endl;

	if (strcmp(sql_row[0], check1) == 0) {
		cout << "���� ���� ��." << endl;
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* ���� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "����ð� : ";
		cin >> time;

		sprintf(nquery, "update reservation set name='%s', phone_num='%s',re_time='%s' where name='%s'; ", name, phone, time, sname);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		cout << "fin";
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		cout << "���� ȸ�� �Դϴ�.";
	}

	//system("cls");

	//reservationStatus();
}
void meno() {
	system("cls");
	setMenuXY();

	cout << "�Է��� �޸�dd : ";
	cin >> rs_memo;


}