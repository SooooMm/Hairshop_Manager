#pragma once
#include <conio.h>
#include <windows.h>
#include <cctype>
#include <stdio.h>
#include <iostream>
#include <string>
#include <mysql.h>
#include<string.h>

int x, y;

int keyControl();
void ChooseCCKey();
void ChooseDMKey();
void ChooseRSKey();

void eageDraw(const char*); //사각형 테두리
int menuDraw();
void gotoxy(int, int);

void customerCare();
void designerManagement();
void reservationStatus();

void CC_add();
void CC_reward();
void CC_revise();

void DM_add();
void DM_revise();

void RS_add();
void RS_revise(); 
void meno();
