#include <iostream>
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

class GAME {
private:
	int ct;
	int mx;
	int score;
	int box[4][4];
	int org[4][4];
public:
	GAME() {
		ct = 0;
		mx = 0;
		score = 0;
		memset(box, 0, sizeof box);
	}
	
	void add() {
		int x, y;
		while (true) {
			x = rand() % 4;
			y = rand() % 4;
			if (box[x][y] == 0) {
				if (rand() % 2) box[x][y] = 4;
				else box[x][y] = 2;
				mx = max(mx, box[x][y]);
				break;
			}
		}
		ct++;
	}
	
	bool check() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				if (box[i][j] == box[i][j + 1]) return true;
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 3; i++)
				if (box[i][j] == box[i + 1][j]) return true;
		return false;
	}
	
	bool possible() {
		if (!full() || check()) return true;
		return false;
	}
	
	bool full() {
		return ct == 16;
	}
	
	bool finish() {
		return mx == 2048;
	}
	
	void Urotate() {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
				swap(box[3 - i][j], box[i][j]);
	}
	void Lrotate() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j <= 3 - i; j++)
				swap(box[3 - j][3 - i], box[i][j]);
	}
	
	void Rrotate() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j <= i; j++)
				swap(box[j][i], box[i][j]);
	}
	
	void pushdown() {
		for (int j = 0; j < 4; j++) {
			int i = 3, k = 3;
			while (true) {
				for (; i >= 0 && box[i][j] == 0; i--);
				if (i < 0) break;
				if (i == k) {
					i--;
					continue;
				}
				
				if (box[i][j] == box[k][j]) {
					box[k][j] *= 2;
					box[i][j] = 0;
					mx = max(mx, box[k][j]);
					score += box[k][j];
					ct--;
				}
				else {
					if (box[k][j] == 0) {
						box[k][j] = box[i][j];
						box[i][j] = 0;
					}
					else {
						k--;
						if (i == k) {
							i--;
							continue;
						}
						else {
							box[k][j] = box[i][j];
							box[i][j] = 0;
						}
					}
				}
			}
		}
	}
	
	void merge(char c) {
		if (c == 72) {
			Urotate();
			pushdown();
			Urotate();
		}
		else if (c == 75) {
			Lrotate();
			pushdown();
			Lrotate();
		}
		else if (c == 77) {
			Rrotate();
			pushdown();
			Rrotate();
		}
		else {
			pushdown();
		}
	}
	
	void show() {
		system("cls");
		printf("Author £º Proverbs\n\n");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (box[i][j] == 0) printf("-     ");
				else printf("%-4d  ",box[i][j]);
			}
			printf("\n\n");
		}
		printf("\n\n");
		printf("MAX : %d     SCORE : %d\n", mx, score);
	}
	
	void backup() {
		memcpy(org, box, sizeof org);
	}
	
	bool thesame() {
		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++)
				if (org[i][j] != box[i][j]) return false;
		return true;
	}
};

int main() {
	srand(time(0)); 
	GAME a;
	
	a.add();
	a.add();
	a.show();
	
	while (a.possible() && !a.finish()) {
		char b = getch();
		if (b == -32) {
			char c = getch();
			if (c == 72 || c == 75 || c == 77 || c == 80) {
				a.backup();
				a.merge(c);
				if (a.thesame()) continue;
				else a.add();
				a.show();
			}
		}
	} 
	if (a.finish()) cout << "Congratulations" << endl;
	else cout << "You idiot!\nYou did like a dog" << endl;
	system("pause");
	return 0;
}
