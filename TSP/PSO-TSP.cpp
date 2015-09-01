#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm> 
#include <fstream> 

#define BUG system("pause")

const int N = 100;

using namespace std;

vector< pair<int, int> > v[N];
vector<int> p[N];
vector<int> pbest[N];
vector<int> gbest;
int value[N];
int bestvalue;
int seq[N];
int dis[N][N];
int n = 4;
int m = 3;

vector< pair<int, int> > v1;
vector< pair<int, int> > v2;

double alpha = 0.5;
double bet = 0.5;

int ans = 999999999;

inline void  pt(vector<int> a) {
	for (int i = 0; i < a.size(); i++) cout << a[i] << "  ";
	cout << endl;
}

inline void ps(vector< pair<int , int> > a) {
	for (int i = 0; i < a.size(); i++) cout << "<" << a[i].first << "," << a[i].second << ">  ";
	cout << endl;
}

inline int evaluate(vector<int> s) {//计算路径长度 
	int res = dis[s[n - 1]][s[0]];
    for (int i = 0; i < n - 1; i++) {
    	res += dis[s[i]][s[i + 1]];
	}
	return res;
}

inline void getgbest() {//获取gbest[x] 
    for (int i = 0; i < m; i++) {
        value[i] = evaluate(p[i]);
    }
    
    for (int i = 0; i < m; i++) {
        if (value[i] > bestvalue) {
            bestvalue = value[i];
            gbest = p[i];
        } 
    }
}

inline void getpbest() {//获取pbest 
    for (int i = 0; i < m; i++) {
        if (evaluate(p[i]) > evaluate(pbest[i])) {
            pbest[i] = p[i];
            ans = evaluate(p[i]);
        } 
    }
}

inline void init() {
    srand(time(0));
    int x, y;
    for (int i = 0; i < n; i++) seq[i] = i;
    //随机化初始序列 
    for (int i = 0; i < m; i++) {
        random_shuffle(seq, seq + n);
        for (int j = 0; j < n; j++)
            p[i].push_back(seq[j]);
        pbest[i] = p[i];//初始化pbest 
    }
    //随机化初始速度,只有一个轮换 
    for (int i = 0; i < m; i++) {
        x = rand() % n;
        y = rand() % n;
        v[i].push_back(make_pair(x, y));
    }
    //获取群体最优位置 
    gbest = p[0];
    getgbest();
}

void changev(int x) {
    //对速度进行调整，随机化删除轮换 
    for (int i = 0; i < v1.size(); i++) {
        double gl = rand() * 1.0 / RAND_MAX;
        if (gl > alpha) v1.erase(v1.begin() + i);
    }
    for (int i = 0; i < v2.size(); i++) {
        double gl = rand() * 1.0 / RAND_MAX;
        if (gl > bet) v2.erase(v2.begin() + i);
    }
    
    //位置+速度 
    for (int i = 0; i < v[x].size(); i++) {
        swap(p[x][v[x][i].first], p[x][v[x][i].second]);
    }
    for (int i = 0; i < v1.size(); i++) {
        swap(p[x][v1[i].first], p[x][v1[i].second]);
    }
    for (int i = 0; i < v2.size(); i++) {
        swap(p[x][v2[i].first], p[x][v2[i].second]);
    }
    /*
    cout << x << endl;
    pt(p[x]);
    BUG;
    */
}

inline int find(vector<int> b, int x) {
	for (int i = 0; i < n; i++)
		if (b[i] == x) return i;
}

inline bool cmp(vector<int> a, vector<int> b) {
	for (int i = 0; i < n; i++)
		if (a[i] != b[i]) return false;
	return true;
}

vector< pair<int, int> > getsubstract(vector<int> a, vector<int> b) {
    vector< pair<int, int> > res;
    while (!cmp(a, b)) {
        for (int i = 0; i < n; i++) {
            if (b[i] != a[i]) {
                int x = find(b, a[i]);
                res.push_back(make_pair(i, x));
                swap(b[i], b[x]);
                break;
            }
        }
    }
    return res;
}

inline void move() {
    for (int i = 0; i < m; i++) {
        v1 = getsubstract(pbest[i], p[i]);
        v2 = getsubstract(gbest, p[i]);
        changev(i);
    }
}

inline void read() {//读入距离 
	ifstream input("TSP.txt");
	input >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			input >> dis[i][j];
	input.close();
}



int main() {
	/*
	vector<int> a;
	vector<int> b;
	a.push_back(1);a.push_back(3);a.push_back(2);a.push_back(0);
	b.push_back(2);b.push_back(0);b.push_back(3);b.push_back(1);
	pt(a);
	pt(b);
	vector< pair<int ,int> > sb = getsubstract(a, b);
	ps(sb);
	BUG;
	*/
    read();
    /*
    vector<int> a;
	a.push_back(0);a.push_back(3);a.push_back(1);a.push_back(2);
	cout << evaluate(a) << endl;
	BUG;
    */
	init();
    while (1) {
        move();
        for (int i = 0; i < m; i++) {
        	/*
        	if (p[i][0] == 0 && p[i][0] == 3 && p[i][0] == 1 && p[i][0] == 2) {
        		cout << "ssdffsdfsdfsda" << endl;
        		BUG;
			}
			*/
		}
        getpbest();
        getgbest();
        //cout << ans << endl; 
    }
    return 0;
}
