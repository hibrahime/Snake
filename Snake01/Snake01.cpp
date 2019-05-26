#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

//#define ZORLUK 1

#define YUKSEKLIK 29
#define GENISLIK 60

#define BASLANGIC_UZUNLUK 3
#define BASLANGIC_X 29
#define BASLANGIC_Y 14
#define ILK_YON 2

void ekranYazdir(char **ekran);
int tusOku();
char ** ekranOlustur(int **yilan, int *yem);
int ** yilanOlustur();
int ** yilanYonlendir(int yon, int **yilan);
int * yemOlustur();
int ** yilanBuyut(int **yilan);
bool yilanKendiniIsirdiMi(int **yilan);
int skor;
int puan = 0;
int ZORLUK = 1;
//deneme

void ekranYenile() {
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imlecGizle(bool gizle) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !gizle;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
	imlecGizle(true);
	int tus;
	skor = 0;
	bool pause = false;
	int yon = ILK_YON;
	char **ekran;
	int **yilan;
	int *yem;

	yilan = yilanOlustur();
	yem = yemOlustur();

	do
	{
		ekran = ekranOlustur(yilan, yem);
		ekranYazdir(ekran);

		tus = tusOku();
		switch (tus) {
		case 1:
			yon != 2 ? yon = 1 : yon = 2;
			break;
		case 2:
			yon != 1 ? yon = 2 : yon = 1;
			break;
		case 3:
			yon != 4 ? yon = 3 : yon = 4;
			break;
		case 4:
			yon != 3 ? yon = 4 : yon = 3;
			break;
		case 7:
			pause = !pause;
			break;
		}

		if (tus != 6 && !pause)
		{
			yilan = yilanYonlendir(yon, yilan);

			if (yilan[0][0] == 0 || yilan[1][0] == 0 || yilan[0][0] == GENISLIK - 1 || yilan[1][0] == YUKSEKLIK - 1 || yilanKendiniIsirdiMi(yilan))
			{
				system("cls");
				cout << "\n\n\n\n\n\t\tOyun Bitti! Puaniniz:\t" << puan << "\n\n\n\n\n";
				tus = 6;
			}

			if (yilan[0][0] == yem[0] && yilan[1][0] == yem[1])
			{
				yilan = yilanBuyut(yilan);
				yem = yemOlustur();
			}
		}

		Sleep(100 / ZORLUK);
	} while (tus != 6);
	cin >> tus;
}

void ekranYazdir(char **ekran) {
	ekranYenile();
	for (int i = 0; i < YUKSEKLIK; i++)
	{
		for (int j = 0; j < GENISLIK; j++)
		{
			cout << ekran[i][j];
		}
		if (i == 5)
		{
			cout << "\tSKOR:\t" << skor;
		}
		if (i == 6)
		{
			cout << "\tZORLUK:\t" << ZORLUK;
		}		if (i == 7)
		{
			cout << "\tPUAN:\t" << puan;
		}
		cout << "\n";
	}
}

int tusOku() {
	if (GetAsyncKeyState(VK_LEFT))
	{
		return 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		return 2;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		return 3;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		return 4;
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		return 5;
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		return 6;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		return 7;
	}
	else if (GetAsyncKeyState(VK_SUBTRACT))
	{
		if (ZORLUK > 1)
		{
			ZORLUK--;
		}
		return 8;
	}
	else if (GetAsyncKeyState(VK_ADD))
	{
		if (ZORLUK < 9)
		{
			ZORLUK++;
		}
		return 9;
	}
	else
	{
		return 0;
	}
}

char ** ekranOlustur(int **yilan, int *yem) {
	char **ekran;
	ekran = new char *[YUKSEKLIK];
	for (int i = 0; i < YUKSEKLIK; i++)
	{
		ekran[i] = new char[GENISLIK];
		for (int j = 0; j < GENISLIK; j++)
		{
			if (j == 0 || j == GENISLIK - 1 || i == 0 || i == YUKSEKLIK - 1)
			{
				ekran[i][j] = '#';
			}
			else
			{
				ekran[i][j] = ' ';
			}
		}
	}

	for (int i = 0; i < (YUKSEKLIK - 2)*(GENISLIK - 2) && yilan[0][i] > 0 && yilan[1][i] > 0; i++)
	{
		ekran[yilan[1][i]][yilan[0][i]] = '@';
	}

	ekran[yem[1]][yem[0]] = '&';
	return ekran;
}

int ** yilanOlustur() {
	int **yilan;

	yilan = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		yilan[i] = new int[(YUKSEKLIK - 2)*(GENISLIK - 2)];
		for (int j = 0; j < (YUKSEKLIK - 2)*(GENISLIK - 2); j++)
		{
			yilan[i][j] = -1;
		}
	}

	for (int i = 0; i < BASLANGIC_UZUNLUK; i++)
	{
		yilan[0][i] = BASLANGIC_X - i; yilan[1][i] = BASLANGIC_Y;
	}

	return yilan;
}

int ** yilanYonlendir(int yon, int **yilan) {
	for (int i = 0; i < (YUKSEKLIK - 2)*(GENISLIK - 2); i++)
	{
		if (yilan[0][i] < 0 && yilan[1][i] < 0)
		{
			for (int j = i - 2; j >= 0; j--)
			{
				yilan[0][j + 1] = yilan[0][j];
				yilan[1][j + 1] = yilan[1][j];
			}
			break;
		}
	}

	switch (yon) {
	case 1:
		yilan[0][0]--;
		break;
	case 2:
		yilan[0][0]++;
		break;
	case 3:
		yilan[1][0]--;
		break;
	case 4:
		yilan[1][0]++;
		break;
	}

	return yilan;
}

int * yemOlustur() {
	int * yemKonumu;
	yemKonumu = new int[2];
	srand(time(0));
	yemKonumu[0] = (rand() % (GENISLIK - 2)) + 1;
	yemKonumu[1] = (rand() % (YUKSEKLIK - 2)) + 1;
	return yemKonumu;
}

int ** yilanBuyut(int **yilan) {
	for (int i = 0; i < (YUKSEKLIK - 2)*(GENISLIK - 2); i++)
	{
		if (yilan[0][i] < 0 && yilan[1][i] < 0)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				yilan[0][j + 1] = yilan[0][j];
				yilan[1][j + 1] = yilan[1][j];
			}
			break;
		}
	}
	skor++;
	puan += skor * ZORLUK;
	return yilan;
}

bool yilanKendiniIsirdiMi(int **yilan) {
	for (int i = 1; i < (YUKSEKLIK - 2)*(GENISLIK - 2); i++)
	{
		if (yilan[0][i] == yilan[0][0] && yilan[1][i] == yilan[1][0])
		{
			return true;
		}
	}
	return false;
}