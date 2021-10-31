//#include <WinSock2.h>
//#include<my_global.h>
#include "mainFunc.h"

#pragma comment(lib,"libmySQL.lib")
using namespace std;

#define UP 0//w
#define DOWN 1//s
#define LEFT 2//a
#define RIGHT 3//d
#define SUBMIT 4 // 스페이스바


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

//중복 확인 위한 변수들
char check0[20] = "0"; 
char check1[20] = "1";
char checkno[20] = "없음";

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
			//회원 관리
			customerCare();
			break;
		}
		case 1: {
			//디자이너 관리
			designerManagement();
			break;
		}
		case 2: {
			//일정 관리
			reservationStatus();
			break;
		}
		default:
			return;
		}
	}
	
	return ;
}

//메인(회원,디자이너,예약) 기능 선택
int menuDraw() {
	system("cls");
	x = 100, y = 35;
	gotoxy(x, y);
	cout << "w : 위";
	gotoxy(x, ++y);
	cout << "s : 아래";
	gotoxy(x, ++y);
	cout << "space : 선택";

	setMenuXY();
	gotoxy(x - 9, y-4);
	cout << " **미용실 회원 관리 프로그램**";
	gotoxy(x - 9, y - 3);
	cout << "===============================";

	gotoxy(x - 2, y);
	cout << ">  고객 관리";
	gotoxy(x, y + 1);
	cout << " 디자이너 관리";
	gotoxy(x, y + 2);
	cout << " 예약 현황";
	gotoxy(x, y + 3);
	cout << " 종	료";

	
	

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

//메인 선택시 사용하는 키
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

//회원관리 데이터 출력 
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

//회원 관리 키(기능) 선택
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

//디자이너 관리 데이터 출력
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

//디자이너 관리 키(기능) 선택
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

//일정 현황 데이터 출력
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

//일정 현황 키(기능) 선택
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


//디자이너, 예약 현황 데이터 출력 틀
void eageDraw(const char* add) {
	x = 20; y = 7;
	gotoxy(x, y);
	cout << "-----------------------------------------------------------";
	gotoxy(x, ++y);
	printf("   이름");
	
	gotoxy(x += 12, y); 
	printf("전화번호");
	gotoxy(x += 16, y); 
	printf("% s", add);
	gotoxy(x += 16, y);
	printf("비고");

	x = 20;
	gotoxy(x, ++y);
	cout << "-----------------------------------------------------------";

}

//회원 관리 데이터 출력 틀
void cc_eageDraw(const char* add) {
	x = 20; y = 7;
	gotoxy(x, y);
	cout << "-----------------------------------------------------------";
	gotoxy(x, ++y);
	printf("   이름");

	gotoxy(x += 12, y);
	printf("전화번호");
	gotoxy(x += 16, y);
	printf("적립금");
	gotoxy(x += 12, y);
	printf("% s", add);
	gotoxy(x += 12, y);
	printf("비고");

	x = 20;
	gotoxy(x, ++y);
	cout << "-----------------------------------------------------------";

}

//회원 관리 화면 그리기
void cc_draw() {
	system("cls");

	cc_eageDraw("담당");
	setTitleXY();
	cout << "* 고객 관리 *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     회원 추가   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "  회원 정보 변경   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "    적립금 추가       ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "    적립금 사용       ";
	gotoxy(x, ++y);
	cout << "------------------";

	x = 100, y = 35;
	gotoxy(x, y);
	cout << "1 : 회원추가";
	gotoxy(x, ++y);
	cout << "2 : 회원 정보 수정";
	gotoxy(x, ++y);
	cout << "3 : 적립금 추가";
	gotoxy(x, ++y);
	cout << "4 : 적립금 사용";

}
//디자이너 관리 화면 그리기
void dm_draw() {
	system("cls");
	eageDraw("근무 시간");
	setTitleXY();
	cout << "* 디자이너 *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "  디자이너 추가   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "디자이너 정보 변경   ";
	gotoxy(x, ++y);
	cout << "------------------";

	x = 95, y = 35;
	gotoxy(x, y);
	cout << "1 : 디자이너 추가";
	gotoxy(x, ++y);
	cout << "2 : 디자이너 정보 수정";
}

//예약 관리 화면 그리기
void rs_draw() {
	system("cls");
	eageDraw("예약 시간");
	setTitleXY();
	cout << "* 예약 현황 *";
	setSelctedXY();
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     일정 추가   ";
	gotoxy(x, ++y);
	cout << "------------------";

	y += 3;
	gotoxy(x, y);
	cout << "------------------";
	gotoxy(x, ++y);
	cout << "     일정 수정   ";
	gotoxy(x, ++y);
	cout << "------------------";

	x = 100, y = 35;
	gotoxy(x, y);
	cout << "1 : 일정 추가";
	gotoxy(x, ++y);
	cout << "2 : 일정 수정";

}

//회원 추가
void CC_add() {
	char name[15],phone[20], charge[15], detail[45];
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "꼭 띄어쓰기 없이 해주세요";
	gotoxy(x, ++y);
	cout << "   없을시  \"없음\" 입력";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* 회원 추가 *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "이름 : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "전화번호(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "담당 : ";
	cin >> charge;
	gotoxy(x, ++y);
	cout << "비고 : ";
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
		cout << "이미 가입한 회원 입니다." << endl;
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
			cout << "가입이 완료되었습니다." << endl;
			Sleep(2000);
			return;
		}
		

		if (strcmp(charge, checkno) == 0) {
			sprintf(query, "insert into customer values('%s', '%s','%s',0,'%s');", name, phone, charge, detail);
			int a = mysql_query(mysql, query);

			system("cls");
			gotoxy(50, 20);
			cout << "가입이 완료되었습니다." << endl;
			Sleep(2000);
			return;
		}
		else {
			system("cls");
			gotoxy(50, 20);
			cout << "없는 디자이너 입니다." << endl;
			Sleep(2000);

		}

	}

	return;
}

//회원 정보 수정
void CC_revise() {
	char name[15], phone[20], charge[15];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "수정할 회원의 전화번호(000-0000-0000) : ";
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
	cout << "꼭 띄어쓰기 없이 해주세요";
	gotoxy(x, ++y);
	cout << "   없을시  \"없음\" 입력";

	if (strcmp(sql_row[0], check1) == 0) {
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* 회원 수정 *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "이름 : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "전화번호(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "담당 : ";
		cin >> charge;

		sprintf(nquery, "update customer set name='%s', phone_num='%s',charge='%s' where phone_num='%s'; ", name,phone,charge,sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}

		system("cls");
		gotoxy(45, 20);
		cout << "회원 정보 수정이 완료되었습니다.";
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "없는 회원 입니다.";
		Sleep(1500);
	}
}

//회원 적립금 추가
void CC_reward_add() {
	char phone[20];
	int price;

	system("cls");
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "꼭 띄어쓰기 없이 해주세요";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* 적립금 *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "전화번호(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "결제 금액(숫자만) : ";
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
		cout << "적립금이 등록되었습니다.";
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "없는 회원 입니다.";
		Sleep(1500);
	}
}

//회원 적립금 사용
void CC_reward_use() {
	char phone[20];
	int price;

	system("cls");

	x = 45, y = 35;
	gotoxy(x, y);
	cout << "꼭 띄어쓰기 없이 해주세요";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* 적립금 *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "전화번호(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "사용 금액(숫자만) : ";
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
		cout << "적립금 사용 완료";
		Sleep(1500);

	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "없는 회원 입니다.";
		Sleep(1500);
	}
}

//디자이너 추가
void DM_add() {
	char name[15], phone[20], time[45], detail[45];
	system("cls");
	x = 45, y = 35;
	gotoxy(x, y);
	cout << "꼭 띄어쓰기 없이 해주세요";
	gotoxy(x, ++y);
	cout << "   없을시  \"없음\" 입력";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* 디자이너 추가 *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "이름 : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "전화번호(000-0000-0000) : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "근무 시간(00:00~00:00) : ";
	cin >> time;
	gotoxy(x, ++y);
	cout << "비고 : ";
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
		cout << "이미 있는 디자이너 입니다." << endl;
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
		cout << "없는 디자이너 입니다." << endl;
		Sleep(1500);
	}
}

//디자이너 정보 수정
void DM_revise() {
	char name[15], phone[20], time[45];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "수정할 디자이너의 전화번호(000-0000-0000) : ";
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
		cout << "꼭 띄어쓰기 없이 해주세요";

		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* 디자이너 수정 *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "이름 : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "전화번호(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "근무 시간(00:00~00:00) : ";
		cin >> time;

		sprintf(nquery, "update designer set name='%s', phone_num='%s',time='%s' where phone_num='%s'; ", name, phone, time, sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		
		system("cls");
		gotoxy(45, 20);
		cout << "디자이너 정보 수정 완료" << endl;
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(50, 20);
		cout << "없는 디자이너 입니다." << endl;
		Sleep(1500);
	}

}

//일정 추가
void RS_add() {
	char name[15], phone[20], rs_time[45], detail[45];
	
	system("cls");

	x = 45, y = 35;
	gotoxy(x, y);
	cout << "꼭 띄어쓰기 없이 해주세요";
	gotoxy(x, ++y);
	cout << "   없을시  \"없음\" 입력";

	setMenuXY();
	gotoxy(x, y - 4);
	cout << "* 일정 추가 *";
	x -= 5;
	gotoxy(x, ++y);
	cout << "이름 : ";
	cin >> name;
	gotoxy(x, ++y);
	cout << "전화번호 : ";
	cin >> phone;
	gotoxy(x, ++y);
	cout << "예약시간 : ";
	cin >> rs_time;
	gotoxy(x, ++y);
	cout << "비고 : ";
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
	cout << "일정이 등록 되었습니다." << endl;
	Sleep(1500);
}
void RS_revise() {
	char name[15], phone[20], time[15];
	char sphone[15];
	system("cls");
	setMenuXY();

	cout << "예약한 회원의 전화번호(000-0000-0000) : ";
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
	cout << "꼭 띄어쓰기 없이 해주세요";
	gotoxy(x, ++y);
	cout << "   없을시  \"없음\" 입력";

	if (strcmp(sql_row[0], check1) == 0) {
		setMenuXY();
		gotoxy(x, y - 4);
		cout << "* 일정 수정 *";
		x -= 5;
		gotoxy(x, ++y);
		cout << "이름 : ";
		cin >> name;
		gotoxy(x, ++y);
		cout << "전화번호(000-0000-0000) : ";
		cin >> phone;
		gotoxy(x, ++y);
		cout << "예약시간(00:00) : ";
		cin >> time;

		sprintf(nquery, "update reservation set name='%s', phone_num='%s',re_time='%s' where phone_num='%s'; ", name, phone, time, sphone);
		int a = mysql_query(mysql, nquery);
		if (a != 0) {
			printf("error : %s", mysql_error(mysql));
			return;
		}
		
		system("cls");
		gotoxy(45, 20);
		cout << "일정 변경 완료" << endl;
		Sleep(1500);
	}
	else if (strcmp(sql_row[0], check0) == 0) {
		system("cls");
		gotoxy(45, 20);
		cout << "없는 일정 입니다." << endl;
		Sleep(1500);
	}
}
