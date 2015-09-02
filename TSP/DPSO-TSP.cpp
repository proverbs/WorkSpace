//DPSO���TSP���⣬û�м����Ż������ܲ� 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <ctime>

#define N 100

using namespace std;

struct Vec {
    int a[N]; 
};

int n;
Vec x[N], gbest, pbest[N];
int rd[N];
int sx[N], sy[N];
int dis[N][N];
int value[N];

const double c1 = 0.2;
const double c2 = 0.3;

inline int prev(const Vec& a, int s);
inline Vec mul(double c, const Vec& a);
inline Vec sub(const Vec& s1, const Vec& s2);
inline void addxv(Vec& s1, const Vec& s2);
inline Vec addvv(const Vec& s1,const Vec& s2);

inline void read() {//���� 
    ifstream input("TSP.txt");
    input >> n;
    for (int i = 1, tmp; i <= n; i++) {
        input >> tmp >> sx[i] >> sy[i];
    }
    //�������겢�������������� 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            dis[i][j] = (int)sqrt((sx[i] - sx[j]) * (sx[i] - sx[j]) + (sy[i] - sy[j]) * (sy[i] - sy[j]));
        }
    input.close();
}

inline void init() {//��ʼ�� 
    for (int i = 1; i <= n; i++) {
        rd[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        random_shuffle(rd + 1, rd + n + 1);
        for (int j = 1; j < n; j++) {
            x[i].a[rd[j]] = rd[j + 1];
        }
        x[i].a[rd[n]] = rd[1];
        pbest[i] = x[i];
    }
    gbest = pbest[1];
}

inline int val(const Vec& a) {//����X��value 
    int res = 0;
    for (int i = 1, j = 1; j <= n; i = a.a[i], j++) {
        res += dis[i][a.a[i]];
    }
    return res;
}

inline void getvalue() {//�����������ӵ�value 
    for (int i = 1; i <= n; i++) {
        value[i] = val(x[i]);
    }
}

inline void getpbest() {//��ȡ������ʷ����pbest[i] 
    for (int i = 1; i <= n; i++){
        if ( val(pbest[i]) > value[i] ) {
            pbest[i] = x[i];
        }
    }
}

inline void getgbest() {//��ȡ��Ⱥ����gbest 
    for (int i = 1; i <= n; i++) {
        if (val(gbest) > val(pbest[i])) {
            gbest = pbest[i];
        }
    }
}

inline Vec getv() {//��ȡһ�����V 
	Vec x1, x2;
	random_shuffle(rd + 1, rd + n + 1);
    for (int i = 1; i < n; i++) {
        x1.a[rd[i]] = rd[i + 1];
    }
    x1.a[rd[n]] = rd[1];
    random_shuffle(rd + 1, rd + n + 1);
    for (int i = 1; i < n; i++) {
        x2.a[rd[i]] = rd[i + 1];
    }
    x2.a[rd[n]] = rd[1];
    return sub(x1, x2);
}

inline void move() {//�����ƶ� 
    Vec x1, x2, x3, vs;
    for (int i = 1; i <= n; i++) {
		if (rand() % 4 > 2) {//������һ����������ƶ� 
			vs = getv();
		}
		else {
			x1 = sub(pbest[i], x[i]);
	        x1 = mul(c1, x1);
	        x2 = sub(gbest, x[i]);
	        x2 = mul(c2, x2);
	        vs = addvv(x1, x2);
		}
        addxv(x[i], vs);
    }
}

inline Vec sub(const Vec& s1, const Vec& s2) {//X�ļ��� 
    Vec res;
    for (int i = 1; i <= n; i++) {
        if (s1.a[i] == s2.a[i]) {
            res.a[i] = 0;
        }
        else {
            res.a[i] = s1.a[i];
        }
    }
    return res;
}

inline Vec mul(double c, const Vec& a) {//V������ 
    Vec res;
    for (int i = 1; i <= n; i++) {
        if (rand() * 1.0 / RAND_MAX < c) {
            res.a[i] = a.a[i];
        }
        else {
            res.a[i] = 0;
        }
    }
    return res;
}

inline Vec addvv(const Vec& s1,const Vec& s2) {//V��V�ļӷ� 
    Vec res;
    for (int i = 1; i <= n; i++) {
        if (s2.a[i] != 0) {
            res.a[i] = s2.a[i];
        }
        else {
            res.a[i] = s1.a[i];
        }
    }
    return res;
}

inline void addxv(Vec& s1, const Vec& s2) {//X��V�ļӷ� 
    Vec res;
    for (int i = 1; i <= n; i++) {
        if ( s2.a[i] ==0 || s1.a[i] == s2.a[i]) {
            ;
        }
        else {
            s1.a[prev(s1, s2.a[i])] = s1.a[s2.a[i]];
            s1.a[s2.a[i]] = s1.a[i];
            s1.a[i] = s2.a[i];
        }
    }
}

inline int prev(const Vec& a, int s) {//Ѱ��prev(vi) 
    for (int i = 1; i <= n; i++)
        if (a.a[i] == s) {
            return i;
        }
}

int main() {
    srand(time(0));
    read();
    init();
    getvalue();
    getpbest();
    getgbest();
    int cas = 0; 
    while (1) {
        move();
        getvalue();
        getpbest();
        getgbest();
        //ÿ1000�����һ�ν�� 
        if (cas % 1000 == 0) cout << val(gbest) << endl;
        cas++;
    }
    return 0;
}
