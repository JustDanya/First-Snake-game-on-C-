#include <iostream>
#include <conio.h>
#include <time.h>
#include <cstdlib>
using namespace std;
bool play = false;
bool crash = false;
int Fx;
int Fy;
int index = 0;
int vector = 0;
bool GameOver = false;
bool Grov = false;
bool Choice = false;
int score = 0;


class Zmeika {
private:
	bool EA = false;
public:
	int Zx;
	int Zy;
	int PrevX, PrevY;
	int GetX() { return Zx; }
	int GetY() { return Zy; }
	void Active() { EA = true; }
	bool GetActive() { return EA; }
	void Memory() { PrevX = Zx; PrevY = Zy; }
	void Move(int mode = 0) {
		switch (mode) {
		case 0:
			Zx++;
			break;

		case 1:
			Zy--;
			break;

		case 2:
			Zx--;
			break;

		case 3:
			Zy++;
			break;
		}
	}
};

void Randoomer() {
	srand(time(0));
	Fx = rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10;
	Fy = rand() % 10 + rand() % 10 + rand() % 10;
	if (Fx == 0 || Fx == 75) 	Fx = rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10;
	if (Fy == 0 || Fy == 25) Fy = rand() % 10 + rand() % 10 + rand() % 10;
}

void Update(Zmeika *obj, bool create = false) {

	for (int i = 0; i < 100; i++) {
		if (obj[i].GetActive() == true) 
		{
			if (i == 0) {
				switch (vector) {
				case 0:
					obj[i].Memory();
					obj[i].Move(0);
					break;

				case 1:
					obj[i].Memory();
					obj[i].Move(1);
					break;

				case 2:
					obj[i].Memory();
					obj[i].Move(2);
					break;

				case 3:
					obj[i].Memory();
					obj[i].Move(3);
					break;
				}
			}
			else {
				int m;
				m = i - 1;
				obj[i].Memory();
				obj[i].Zx = obj[m].PrevX;
				obj[i].Zy = obj[m].PrevY;
			}
		}
		else continue;
	}
	if (create == true) {
		index++;
		int mines = index - 1;
		obj[index].Active();
		obj[index].Zx = obj[mines].PrevX;
		obj[index].Zy = obj[mines].PrevY;
		Grov = false;
	}
	for (int i = 1; i < 100; i++) {
		if (obj[0].Zx == obj[i].Zx && obj[0].Zy == obj[i].Zy) GameOver = true;
	}
}

void Draw(Zmeika *obj) {
	system("cls");
	cout << '\n';
	for (int y = 0; y <= 25; y++) {
		for (int x = 0; x <= 75; x++) {
			bool ddraw = false;
			for (int i = 0; i < 100; i++) {
				if (obj[i].Zx == Fx && obj[i].Zy == Fy) {
					Randoomer();
					Grov = true;
					score += 10;
				}
				if (obj[i].GetX() == x && obj[i].GetY() == y )//&& obj[i].GetActive() == true)
				{
					ddraw = true;
					if (x == 0 || x == 75 || y == 25 || y == 0) GameOver = true;
				}
			}
			if (x == Fx && y == Fy) { cout << "o"; }
			else if (x == 0 || x == 75) cout << "|";
			else if (ddraw == true) cout << "*";
			else cout << " ";
		}
		cout << '\n';
	}
	cout << "SCORE---------------------------------------------------------------------" << score;
}

void Input(Zmeika *obj) {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			vector = 2;
			break;
		case 'd':
			vector = 0;
			break;
		case 'w':
			vector = 1;
			break;
		case 's':
			vector = 3;
			break;
		case 27:
			GameOver = true;
			break;
		}
	}
}


int main(int argc, char *argv[]) {
	float TIME;
	//////////////////////////
	//if (argc != 2)  TIME = 0.25;
	//else
	TIME = 0.05;
	/////////////////////////Object init///////////////////
	//////////
	Zmeika *A;
	A = new Zmeika[100];
	A[index].Active();
	A[index].Zx = 25;
	A[index].Zy = 10;
	/////////////////////////Time init/////////////////////
	clock_t start, current, update;
	start = clock();
	update = start + 0.5*CLOCKS_PER_SEC;
	/////////////////////////Game Cycle////////////////////
	Randoomer();
	while (!GameOver) {

		current = clock();

		if (current >= update) {
			try 
			{

			Draw(A);
			Input(A);
			Update(A);
			update = current + TIME * CLOCKS_PER_SEC;
			if (Grov == true)
				Update(A, true);

			}
			catch(...) {
				system("cls");
				cout << "BRUh" << endl;
				//system("pause");
			}
		}
	}
	return 0;
}
