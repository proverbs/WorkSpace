#include "stdhead.h"
#include "Student.h"
#include "School.h"

using namespace std;

class Admit {
public:
	void start();//读入两个文件
	void checkin(int x);//第x轮志愿录取
private:
	vector<Student> stu;
	vector<School> sch;
};

void Admit::start() {
	cout << "Please input the filename of Student." << endl;
	cin >> studentName;
	cout << "Please input the filename of School." << endl;
	cin >> schoolName;
	//读取学校信息
	for (int i = 0; i < Volition::NUMBER_OF_MAJOR; i++) {
		checkin(i);
	}
}

void Admit::checkin(int x) {
	//打开文件
	//将没有被录取的学生读取到数组
	//排序
	//依次录取，并标记录取
	//写入文件
}