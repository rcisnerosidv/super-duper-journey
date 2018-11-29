#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>

using namespace std;

const int Arriba{ 72 };
const char char_Arriba = Arriba;
const int Izquierda{ 75 };
const char char_Izquierda = Izquierda;
const int Derecha{ 77 };
const char char_Derecha = Derecha;
const int Abajo{ 80 };
const char char_Abajo = Abajo;

char ascii(int num) {
	unsigned char char_ascii = num;
	return char_ascii;
}

void gotoxy(int x, int y) {

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);

}

void pintar_limites() {
	for (int i{ 2 }; i < 78; ++i) {
		gotoxy(i, 3); cout << ascii(205);
		gotoxy(i, 33); cout << ascii(205);
	}
	
	for (int i{ 4 }; i < 33; ++i) {
		gotoxy(2, i); cout << ascii(186);
		gotoxy(77, i); cout << ascii(186);
	}

	gotoxy(2, 3); cout << ascii(201);
	gotoxy(2, 33); cout << ascii(200);
	gotoxy(77, 3); cout << ascii(187);
	gotoxy(77, 33); cout << ascii(188);

}

void ocultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = false;

	SetConsoleCursorInfo(hCon, &cci);

}

class nave {
	int x, y;
	int corazones{ 3 };
	int vidas{ 3 };
public:
	nave(int _x, int _y, int _corazones, int _vidas) : x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}
	int X() { return x; }
	int Y() { return y; }
	int VID() { return vidas; }
	void cor() { corazones--; }
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void morir();
};

void nave::pintar() {
	char nave1{ 30 };

	gotoxy(x, y); cout << "  " << ascii(30) ;
	gotoxy(x, y + 1); cout << " " << ascii(40) << ascii(207) << ascii(41);
	gotoxy(x, y + 2); cout << ascii(30) << ascii(190) << " " << ascii(190) << ascii(30);
		

}

void nave::borrar() {
	gotoxy(x, y); cout << "       ";
	gotoxy(x, y+1); cout << "       ";
	gotoxy(x, y+2); cout << "       ";


}

void nave::mover() {

	if (kbhit()) {
		char tecla = getch();
		borrar();
		gotoxy(x, y); cout << " ";
		if (tecla == Izquierda && x > 6) x-=2;
		if (tecla == Derecha && x+6 < 75) x+=2;
		if (tecla == Arriba && y > 4) y--;
		if (tecla == Abajo && y+3 < 33) y++;
		if (tecla == 'e') corazones--;
		pintar();
		pintar_corazones();
	}


}

void nave::pintar_corazones() {
	gotoxy(50, 2); cout << "Vidas " << vidas;
	gotoxy(64, 2); cout << "Salud";
	gotoxy(70, 2); cout << "      ";
	for (int i{ 0 }; i < corazones; ++i) {

		gotoxy(70 + i, 2); cout << ascii(3);
	}
}

void nave::morir() {
	if (corazones == 0) {
		borrar();
		gotoxy(x, y);   cout << "   **   ";
		gotoxy(x, y+1); cout << "  ****  ";
		gotoxy(x, y+2); cout << "   **   ";
		Sleep(200);

		borrar();
		gotoxy(x, y);	  cout << " * ** *";
		gotoxy(x, y + 1); cout << "  **** ";
		gotoxy(x, y + 2); cout << " * ** *";
		Sleep(200);

		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();

	}


}

class Ast {
	int x, y;
public:
	Ast(int _x, int _y): x(_x), y(_y){}
	void pintar();
	void mover();
	void choque(class nave &N);
	int X() { return x; }
	int Y() { return y; }
};

void Ast::pintar() {
	gotoxy(x, y); cout << ascii(184);

}

void Ast::mover() {
	gotoxy(x, y); cout << " ";
	y++;
	if(y > 32 ){
		x = rand() % 71 + 5;
		y = 4;

	}
	pintar();

}

void Ast::choque(class nave &N) {

	if (x >= N.X() && x < N.X() + 6 && y >= N.Y() && y <= N.Y() + 2) {
		N.cor();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand() % 71 + 4;
		y = 4;

	}
}

class bala {
	int x, y;
public:
	bala(int _x, int _y): x(_x), y(_y){}
	int X() { return x; }
	int Y() { return y; }
	void mover();
	bool fuera();
};

void bala::mover() {
	gotoxy(x, y); cout << " ";
	if (y > 4) y--;
	gotoxy(x, y); cout << "*";
}

bool bala::fuera() {
	if (y == 4) return true;
	return false;
}

int main() {

	ocultarCursor();
	pintar_limites();
	nave N(37, 30, 3, 3);
	N.pintar_corazones();
	N.pintar();

	list<Ast*> A;
	list<Ast*>::iterator itA;
	for (int i{ 0 }; i < 5; ++i) {
		A.push_back(new Ast(rand() % 75 + 3, rand() % 5 + 4));
	}
	
	list<bala*> B;
	list<bala*>::iterator it;

	int x{ 37 }, y{ 7 };
	bool game_over = false;
	int puntos = 0;
	while (!game_over) {

		gotoxy(4, 2); cout << "Puntos " << puntos;
		if (kbhit()) //nos metemos a la rutina del juego el kbhit es para identificar cuando se pulsa una tecla
		{
			char tecla = getch();
			if (tecla == 'a')
				B.push_back(new bala(N.X() + 2, N.Y() - 1));
		}


		for (it = B.begin(); it != B.end();)
		{
			(*it)->mover(); //el operador flecha sirve para que se meta a sus      //el puntero es la direccion donde esta guardada la direccion
			if ((*it)->fuera()) {
				gotoxy((*it)->X(), (*it)->Y()); cout << " ";
				delete(*it);
				it = B.erase(it);
			}
			else {
				++it;
			}
		}

		for (itA = A.begin(); itA != A.end(); ++itA) {
			(*itA)->mover();
			(*itA)->choque(N);

		}

		for (itA = A.begin(); itA != A.end(); ++itA) {
			for (it = B.begin(); it != B.end();) {
				if ((*itA)->X() == (*it)->X() && (*itA)->Y() == (*it)->Y() || (*itA)->Y() == (*it)->Y()){

					gotoxy((*it)->X(), (*it)->Y()); cout << " ";
					delete(*it);
					it = B.erase(it);

					A.push_back(new Ast(rand() % 74 + 3, 4));
					gotoxy((*itA)->X(), (*itA)->Y()); cout << " ";
					delete(*itA);
					itA = A.erase(itA);

					puntos += 5;
				}
				else {
					++it;
				}
			}
		}

		if (N.VID() == 0) game_over = 0;

		N.morir();
		N.mover();
		Sleep(30);


	}
	system("pause");
	return 0;
}