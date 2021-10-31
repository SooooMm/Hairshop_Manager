//#include <WinSock2.h>
//#include<my_global.h>
#include "mainFunc.h"

#pragma comment(lib,"libmySQL.lib")
using namespace std;

#define UP 0//w
#define DOWN 1//s
#define LEFT 2//a
#define RIGHT 3//d
#define SUBMIT 4 // �����̽���


CONSOLE_SCREEN_BUFFER_INFO presentCur;

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setSelctedXY() {
	x = 90; y = 7;
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

//�ߺ� Ȯ�� ���� ������
char check0[20] = "0"; 
char check1[20] = "1";
char checkno[20] = "����";

void main() {
	system("cls");
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	system(" mode  con lines=40   cols=120 ");

	if (!mysql_real_connect(mysql, "localhost", "root", "Suy0Sm0tdo", "hairshop_manager", 3306, NULL, 0))
		fprintf(stderr, "mysql error : %s", mysql_error(mysql));
	else { 
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
			//ȸ�� ����
			customerCare();
			break;
		}
		case 1: {
			//�����̳� ����
			designerManagement();
			break;
		}
		case 2: {
			//���� ����
			reservationStatus();
			break;
		}
		default:
			return;
		}
	}
	
	return ;
}

//����(ȸ��,�����̳�,����) ��� ����
int menuDraw() {
	system("cls");
	x = 100, y = 35;
	gotoxy(x, y);
	cout << "w : ��";
	gotoxy(x, ++y);
	cout << "s : �Ʒ�";
	gotoxy(x, ++y);
	cout << "space : ����";

	setMenuXY();
	gotoxy(x - 9, y-4);
	cout << " **�̿�� ȸ�� ���� ���α׷�**";
	gotoxy(x - 9, y - 3);
	cout << "===============================";

	gotoxy(x - 2, y);
	cout << ">  �� ����";
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

//���� ���ý� ����ϴ� Ű
int keyControl() {
	char press = _getch();

	switch (press)
	{
	case 'w': case 'W': {
		return UP;
	}
	case 's': case 'S': {
		return DOWN;
	}
	case ' ': {
		return SUBMIT;
	}
	}
}


void customerCare() {
	cc_draw();
	ChooseCCKey();
}
void designerManagement() {
	dm_draw();
	ChooseDMKey();
}
void reservationStatus() {
	rs_draw();
	ChooseRSKey();
}

//ȸ������ ������ ��� 
void Show_CC_data() {
	x = 20; y = 10;
	gotoxy(x, y);
	int stat = mysql_query(mysql, "select * from customer; ");

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}
	sql_result = mysql_store_result(mysql);

	while (sql_row = mysql_fetch_row(sql_result)) {
		printf("   %s", sql_row[0]);
		gotoxy(x += 12, y);
		printf("%s", sql_row[1]);
		gotoxy(x += 16, y);
		printf("%s", sql_row[3]);
		gotoxy(x += 12, y);
		printf("%s", sql_row[2]);
		gotoxy(x += 12, y);
		printf("%s", sql_row[4]);
		x = 20;
		gotoxy(x, ++y);
	}
}

//ȸ�� ���� Ű(���) ����
void ChooseCCKey() {
	
	while (true) {
		cc_draw();
		Show_CC_data();
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
			CC_reward_add();
			break;
		}
		case '4': {
			gotoxy(100, 38);
			CC_reward_use();
			break;
		}
		case '0': {
			return;
		}
		}
	}
	
}

//�����̳� ���� ������ ���
void Show_DM_data() {
	x = 20; y = 10;
	gotoxy(x, y);
	int stat = mysql_query(mysql, "select * from designer; ");

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}
	sql_result = mysql_store_result(mysql);

	while (sql_row = mysql_fetch_row(sql_result)) {
		printf("   %s", sql_row[0]);
		gotoxy(x += 12, y);
		printf("%s", sql_row[1]);
		gotoxy(x += 16, y);
		printf("%s", sql_row[2]);
		gotoxy(x += 16, y);
		printf("%s", sql_row[3]);
		x = 20;
		gotoxy(x, ++y);
	}

}

//�����̳� ���� Ű(���) ����
void ChooseDMKey() {
	
	while (true) {
		dm_draw();
		Show_DM_data();
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
			return;
		}
		}
	}
	
}

//���� ��Ȳ ������ ���
void Show_RS_data() {
	x = 20; y = 10;
	gotoxy(x, y);
	int stat = mysql_query(mysql, "select * from reservation; ");

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}
	sql_result = mysql_store_result(mysql);

	while (sql_row = mysql_fetch_row(sql_result)) {
		printf("   %s", sql_row[0]);
		gotoxy(x += 12, y);
		printf("%s", sql_row[1]);
		gotoxy(x += 16, y);
		printf("%s", sql_row[2]);
		gotoxy(x += 16, y);
		printf("%s", sql_row[3]);
		x = 20;
		gotoxy(x, ++y);
	}

}

//���� ��Ȳ Ű(���) ����
void ChooseRSKey() {
	while(true){
		rs_draw();
		Show_RS_data();
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
			return;
		}
		}
	}
	
}


//�����̳�, ���� ��Ȳ ������ ��� Ʋ
void eageDraw(const char* add) {
	x = 20; y = 7;
	gotoxy(x, y);
	cout << "-----------------------------------------------------------";
	gotoxy(x, ++y);
	printf("   �̸�");
	
	gotoxy(x += 12, y); 
	printf("��ȭ��ȣ");
	gotoxy(x += 16, y); 
	printf("% s", add);
	gotoxy(x += 16, y);
	printf("���");

	x = 20;
	gotoxy(x, ++y);
	cout << "-----------------------------------------------------------";

}

//ȸ�� ���� ������ ��� Ʋ
void cc_eageDraw(const char* add) {
	x = 20; y = 7;
	gotoxy(x, y);
	cout << "-----------------------------------------------------------";
	gotoxy(x, ++y);
	printf("   �̸�");

	gotoxy(x += 12, y);
	printf("��ȭ��ȣ");
	gotoxy(x += 16, y);
	printf("������");
	gotoxy(x += 12, y);
	printf("% s", add);
	gotoxy(x += 12, y);
	printf("���");

	x = 20;
	gotoxy(x, ++y);
	cout << "-----------------------------------------------------------";

}

//ȸ�� ���� ȭ�� �׸���
void cc_draw() {
	system("cls");

	cc_eageDraw("���");
	setTitleXY();
	cout << "* �� ���� *";
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
	cout << "  ȸ�� ���� ����   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "    ������ �߰�       ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "    ������ ���       ";
	gotoxy(x, ++y);
	cout << "------------------";

	x = 100, y = 35;
	gotoxy(x, y);
	cout << "1 : ȸ���߰�";
	gotoxy(x, ++y);
	cout << "2 : ȸ�� ���� ����";
	gotoxy(x, ++y);
	cout << "3 : ������ �߰�";
	gotoxy(x, ++y);
	cout << "4 : ������ ���";

}
//�����̳� ���� ȭ�� �׸���
void dm_draw() {
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

	x = 95, y = 35;
	gotoxy(x, y);
	cout << "1 : �����̳� �߰�";
	gotoxy(x, ++y);
	cout << "2 : �����̳� ���� ����";
}

//���� ���� ȭ�� �׸���
void rs_draw() {
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

	x = 100, y = 35;
	gotoxy(x, y);
	cout << "1 : ���� �߰�";
	gotoxy(x, ++y);
	cout << "2 : ���� ����";

}

//ȸ�� �߰�
void CC_add() {
	char name[15],phone[20], charge[15], detail[45];
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";
	gotoxy(x, ++y);
	cout << "   ������  \"����\" �Է�";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ȸ�� �߰� *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> charge;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> detail;

	char query[255];
	sprintf(query, "select count(*) from customer where phone_num = '%s'; ", phone);
	int stat = mysql_query(mysql, query);

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return ;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);
	
	if (strcmp(sql_row[0], check1) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "�̹� ������ ȸ�� �Դϴ�." << endl;
		Sleep(2000);
	}
	else if (strcmp(sql_row[0], check0) == 0) {

		sprintf(query, "select count(*) from designer where name = '%s'; ", charge);
		int stat = mysql_query(mysql, query);

		if (stat != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}

		sql_result = mysql_store_result(mysql);
		sql_row = mysql_fetch_row(sql_result);


		if(strcmp(sql_row[0], check1) == 0){
			sprintf(query, "insert into customer values('%s', '%s','%s',0,'%s');", name, phone, charge, detail);
			int a = mysql_query(mysql, query);

			system("cls");
			gotoxy(50, 20);
			cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
			Sleep(2000);
			return;
		}
		

		if (strcmp(charge, checkno) == 0) {
			sprintf(query, "insert into customer values('%s', '%s','%s',0,'%s');", name, phone, charge, detail);
			int a = mysql_query(mysql, query);

			system("cls");
			gotoxy(50, 20);
			cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
			Sleep(2000);
			return;
		}
		else {
			system("cls");
			gotoxy(50, 20);
			cout << "���� �����̳� �Դϴ�." << endl;
			Sleep(2000);

		}

	}

	return;
}

//ȸ�� ���� ����
void CC_revise() {
	char name[15], phone[20], charge[15];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "������ ȸ���� ��ȭ��ȣ(000-0000-0000) : ";
	cin >> sphone;
	char nquery[255];
	sprintf(nquery, "select count(*) from customer where phone_num = '%s'; ", sphone);
	int stat = mysql_query(mysql, nquery);

	cout << sphone << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";
	gotoxy(x, ++y);
	cout << "   ������  \"����\" �Է�";

	if (strcmp(sql_row[0], check1) == 0) {
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* ȸ�� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "��� : ";
		cin >> charge;

		sprintf(nquery, "update customer set name='%s', phone_num='%s',charge='%s' where phone_num='%s'; ", name,phone,charge,sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}

		system("cls");
		gotoxy(45, 20);
		cout << "ȸ�� ���� ������ �Ϸ�Ǿ����ϴ�.";
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "���� ȸ�� �Դϴ�.";
		Sleep(1500);
	}
}

//ȸ�� ������ �߰�
void CC_reward_add() {
	char phone[20];
	int price;

	system("cls");
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ������ *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "���� �ݾ�(���ڸ�) : ";
	cin >> price;

	char query[255];
	sprintf(query,"select count(*) from customer where phone_num = '%s'; ", phone);
	int stat = mysql_query(mysql, query);
	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	if(stat!=0){
		printf("error : %s", mysql_error(mysql));
		return;
	}

	if (strcmp(sql_row[0], check1)==0) {
		sprintf(query, "select reward_point into @temp from customer where phone_num = '%s'; ", phone);
		int a = mysql_query(mysql, query);

		sprintf(query, " update customer set reward_point=(@temp+%d) where phone_num ='%s'; ", (int)(price*0.05),phone);
		a = mysql_query(mysql, query);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}

		system("cls");
		gotoxy(50, 20);
		cout << "�������� ��ϵǾ����ϴ�.";
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "���� ȸ�� �Դϴ�.";
		Sleep(1500);
	}
}

//ȸ�� ������ ���
void CC_reward_use() {
	char phone[20];
	int price;

	system("cls");

	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* ������ *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "��� �ݾ�(���ڸ�) : ";
	cin >> price;

	char query[255];
	sprintf(query, "select count(*) from customer where phone_num = '%s'; ", phone);
	int stat = mysql_query(mysql, query);
	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}


	if (strcmp(sql_row[0], check1) == 0) {
		sprintf(query, "select reward_point into @temp from customer where phone_num = '%s'; ", phone);
		int a = mysql_query(mysql, query);

		sprintf(query, " update customer set reward_point=(@temp-%d) where phone_num ='%s'; ", price, phone);
		a = mysql_query(mysql, query);

		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}

		system("cls");
		gotoxy(50, 20);
		cout << "������ ��� �Ϸ�";
		Sleep(1500);

	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "���� ȸ�� �Դϴ�.";
		Sleep(1500);
	}
}

//�����̳� �߰�
void DM_add() {
	char name[15], phone[20], time[45], detail[45];
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";
	gotoxy(x, ++y);
	cout << "   ������  \"����\" �Է�";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* �����̳� �߰� *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "�̸� : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "��ȭ��ȣ(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "�ٹ� �ð�(00:00~00:00) : ";
	cin >> time;
	gotoxy(x, ++y);
	cout << "��� : ";
	cin >> detail;


	char query[255];
	sprintf(query, "select count(*) from designer where phone_num = '%s'; ", phone);
	int stat = mysql_query(mysql, query);

	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	if (strcmp(sql_row[0], check1) == 0) {
		system("cls");
		gotoxy(45, 20);
		cout << "�̹� �ִ� �����̳� �Դϴ�." << endl;
		Sleep(1500);
		
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		sprintf(query, "insert into designer values('%s', '%s','%s','%s');", name, phone, time, detail);
		int a = mysql_query(mysql, query);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		system("cls");
		gotoxy(45, 20);
		cout << "���� �����̳� �Դϴ�." << endl;
		Sleep(1500);
	}
}

//�����̳� ���� ����
void DM_revise() {
	char name[15], phone[20], time[45];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "������ �����̳��� ��ȭ��ȣ(000-0000-0000) : ";
	cin >> sphone;
	char nquery[255];
	sprintf(nquery, "select count(*) from designer where phone_num = '%s'; ", sphone);
	int stat = mysql_query(mysql, nquery);

	cout << sphone << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	system("cls");

	if (strcmp(sql_row[0], check1) == 0) {
		x = 45, y = 35;
		gotoxy(x, y);
		cout << "�� ���� ���� ���ּ���";

		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* �����̳� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "�ٹ� �ð�(00:00~00:00) : ";
		cin >> time;

		sprintf(nquery, "update designer set name='%s', phone_num='%s',time='%s' where phone_num='%s'; ", name, phone, time, sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		
		system("cls");
		gotoxy(45, 20);
		cout << "�����̳� ���� ���� �Ϸ�" << endl;
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "���� �����̳� �Դϴ�." << endl;
		Sleep(1500);
	}

}

//���� �߰�
void RS_add() {
	char name[15], phone[20], rs_time[45], detail[45];
	
	system("cls");

	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";
	gotoxy(x, ++y);
	cout << "   ������  \"����\" �Է�";

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

	system("cls");
	gotoxy(50, 20);
	cout << "������ ��� �Ǿ����ϴ�." << endl;
	Sleep(1500);
}
void RS_revise() {
	char name[15], phone[20], time[15];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "������ ȸ���� ��ȭ��ȣ(000-0000-0000) : ";
	cin >> sphone;
	char nquery[255];
	sprintf(nquery, "select count(*) from reservation where phone_num = '%s'; ", sphone);
	int stat = mysql_query(mysql, nquery);

	cout << sphone << endl;
	if (stat != 0) {
		printf("error : %s", mysql_error(mysql));
		return;
	}

	sql_result = mysql_store_result(mysql);
	sql_row = mysql_fetch_row(sql_result);

	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "�� ���� ���� ���ּ���";
	gotoxy(x, ++y);
	cout << "   ������  \"����\" �Է�";

	if (strcmp(sql_row[0], check1) == 0) {
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* ���� ���� *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "�̸� : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "��ȭ��ȣ(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "����ð�(00:00) : ";
		cin >> time;

		sprintf(nquery, "update reservation set name='%s', phone_num='%s',re_time='%s' where phone_num='%s'; ", name, phone, time, sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		
		system("cls");
		gotoxy(45, 20);
		cout << "���� ���� �Ϸ�" << endl;
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(45, 20);
		cout << "���� ���� �Դϴ�." << endl;
		Sleep(1500);
	}
}
