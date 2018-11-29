#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

char ascii(int num) {
	char char_ascii = num;
	return char_ascii;
}

void goToXY(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}


void limites() {

	for (int i{ 2 }; i < 37; ++i) {
		goToXY(i, 3); cout << ascii(205);
		goToXY(i, 33); cout << ascii(205);
	}

	for (int i{ 40 }; i < 44; ++i) {
		goToXY(i, 3); cout << " ";
		goToXY(i, 33); cout << " ";
	}

	for (int i{ 45 }; i < 78; ++i) {
		goToXY(i, 3); cout << ascii(205);
		goToXY(i, 33); cout << ascii(205);
	}

	for (int i{ 0 }; i < 78; ++i) {
		goToXY(i, 2); cout << i;
	}
	
	for (int i{ 4 }; i < 15; ++i) {
		goToXY(2, i); cout << ascii(186);
		goToXY(77, i); cout << ascii(186);
	}

	for (int i{ 15 }; i < 19; ++i) {
		goToXY(2, i); cout << " ";
		goToXY(77, i); cout << " ";
	}

	for (int i{ 19 }; i < 33; ++i) {
		goToXY(2, i); cout << ascii(186);
		goToXY(77, i); cout << ascii(186);
	}
	
	for (int i{ 0 }; i < 34; ++i) {
		goToXY(0, i); cout << i;
	}

	goToXY(2, 3); cout << ascii(201);
	goToXY(2, 33); cout << ascii(200);
	goToXY(77, 3); cout << ascii(187);
	goToXY(77, 33); cout << ascii(188);
}

void ocultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = false;

	SetConsoleCursorInfo(hCon, &cci);

}

void personaje() {
	goToXY(37, 30); cout << " " << ascii(207);
	goToXY(37, 31); cout << ascii(205) << ascii(190) << ascii(205);
	goToXY(37, 32); cout << " " << ascii(220);
	goToXY(37, 33); cout << ascii(217) << " " << ascii(192);
}

int main() {
	
	ocultarCursor();
	limites();
	personaje();

	cout << endl;
	system("pause");
	return 0;
}