#include "stdhead.h"
#include "Student.h"
#include "School.h"

using namespace std;

class Admit {
public:
	void start();//���������ļ�
	void checkin(int x);//��x��־Ը¼ȡ
private:
	vector<Student> stu;
	vector<School> sch;
};

void Admit::start() {
	cout << "Please input the filename of Student." << endl;
	cin >> studentName;
	cout << "Please input the filename of School." << endl;
	cin >> schoolName;
	//��ȡѧУ��Ϣ
	for (int i = 0; i < Volition::NUMBER_OF_MAJOR; i++) {
		checkin(i);
	}
}

void Admit::checkin(int x) {
	//���ļ�
	//��û�б�¼ȡ��ѧ����ȡ������
	//����
	//����¼ȡ�������¼ȡ
	//д���ļ�
}