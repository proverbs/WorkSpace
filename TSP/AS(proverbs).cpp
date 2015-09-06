#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>

#define M 100
#define N 100
#define INF 99999999
#define BUG system("pause")

using namespace std;

const double alpha = 1.0;
const double bet = 7.0;
const double rou = 0.5;

int n, m;
vector<int> gr[M];
vector<int> gl;
int dis[N][N], sx[N], sy[N], ansgr[N];
double tao[N][N], val[N][N];
bool vis[M][N];
int bestsum = INF;

inline void init() {
	ifstream input("TSP.txt");
	input >> n;
	for (int i = 0, tmp; i < n; i++)
		input >> tmp >> sx[i] >> sy[i];
	for (int i = 0; i < n; i++) {
		dis[i][i] = INF;
		tao[i][i] = 0.0;
		for (int j = i + 1; j < n; j++) {
			dis[i][j] = 
			dis[j][i] = round(sqrt((sx[i] - sx[j]) * (sx[i] - sx[j]) + (sy[i] - sy[j]) * (sy[i] - sy[j])));	
		}
	}
	input.close();
	m = n;
}

inline void find(int num, int x, int bg) {
	vis[bg][x] = true;
	gr[bg].push_back(x);
	if (num == n) {
		gr[bg].push_back(bg);
		ansgr[bg] += dis[x][bg];
		return;
	}
	int minval = INF;
	int minnum;
	for (int i = 0; i < n; i++)
		if (!vis[bg][i] && dis[x][i] < minval) {
			minval = dis[x][i];
			minnum = i;
		}
	ansgr[bg] += minval;
	find(num + 1, minnum, bg);
}

inline void greedy() {
	/*��ʼ������,̰��ʱֻ��n������*/ 
	for (int i = 0; i < n; i++) {
		gr[i].clear();
		ansgr[i] = 0;
		for (int j = 0; j < n; j++) 
			vis[i][j] = false;
	}
	/*��n��λ�ó���Ѱ��̰�����·*/
	for (int i = 0; i < n; i++) {
		find(1, i, i);
		/*
		for (int j = 0; j < n; j++)
			cout << gr[i][j] << "   ";
		cout << endl; cout << ansgr[i] << endl;BUG;
		*/
	}
	int minval = INF;
	int minnum;
	for (int i = 0; i < n; i++)
		if (ansgr[i] < minval) {
			minval = ansgr[i];
			minnum = i;
		}
	bestsum = minval;
	/*
	cout << bestsum << endl;BUG;
	*/
	
	/*ʹ��̰�����·�����ʼ����Ϣ�ؾ���*/
	double t0 = n * 1.0 / minval;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			tao[i][j] = tao[j][i] = t0;//all edges??
}

inline void randsp() {
	/*���ݵĳ�ʼ��*/
	for (int i = 0; i < m; i++) {
		gr[i].clear();
		for (int j = 0; j < n; j++)
			vis[i][j] = false; 
	}
	/*�����ʼλ��*/ 
	for (int i = 0, tmp; i < m; i++) {
		tmp = rand() % n;
		gr[i].push_back(tmp);
		vis[i][tmp] = true;
	}
}

inline void run() {
	/*Ԥ��������*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j)
				val[i][j] = pow(tao[i][j], alpha) * pow(1.0 / dis[i][j], bet);
			else val[i][j] = 0; 
		}
	}
	/*n-1�֣�mֻ���ϵ��ƶ�*/ 
	vector<double> gl; 
	vector<int> select;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			gl.clear();
			select.clear();
			int x = gr[j][i - 1];
			double sumselect = 0.0; 
			for (int k = 0; k < n; k++)
				if (vis[j][k] == false) select.push_back(k);
			for (int k = 0; k < select.size(); k++) 
				sumselect += val[x][select[k]];
			for (int k = 0; k < select.size(); k++)
				gl.push_back(val[x][select[k]] / sumselect);
			for (int k = 1; k < select.size(); k++)
				gl[k] += gl[k - 1];
			double tmp = rand() * 1.0 / RAND_MAX;
			for (int k = 0; k < select.size(); k++)
				if (tmp <= gl[k]) {
					vis[j][select[k]] = true;
					gr[j].push_back(select[k]);
					break;
				}
		}
	}
	/*
	for (int i = 0; i < n; i++)
		cout << gr[0][i] << "   ";
	cout << endl;
	BUG;
	*/ 
}

inline void updata() {
	/*��Ϣ�صĻӷ�*/ 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tao[i][j] = (1.0 - rou) * tao[i][j];
	/*��Ϣ�ص�����*/ 
	for (int i = 0; i < m; i++) {
		int sum = 0; 
		gr[i].push_back(gr[i][0]);
		for (int j = 0; j < n; j++) sum += dis[gr[i][j]][gr[i][j + 1]];
		for (int j = 0; j < n; j++) {
			tao[gr[i][j]][gr[i][j + 1]] += 1.0 / sum;
		}
		if (bestsum > sum) {
			bestsum = sum;
		}
		//cout << sum << endl;
	}
}

int main() {
	srand(time(0));
	init();
	greedy();
	int cas = 20000;
	while (cas--) {
		randsp();
		run();
		updata();
	}
	cout << bestsum << endl; 
	return 0;
} 
