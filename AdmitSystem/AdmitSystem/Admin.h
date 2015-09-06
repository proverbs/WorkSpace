#include "stdhead.h"
#include "Student.h"
#include "Admit.h"

using namespace std;

class Admin {
public:
	void init();
	void show();
	Student* add();
	Student* findstudent(string num);
	void del(string num);
	void save();
	void checkin();//执行录取
private:
	string filename;
	string name;
	string password;
	vector<Student> stu;
};

void Admin::init() {
	cout << "Please input the filename." << endl;
	cin >> filename;
	ifstream input(filename.c_str());
	if (input.fail()) {
		cout << "Load failed." << endl;
		init();
	}

	string name;
    string gender;
    string number;
    int score;
    string id;
    string password;
    string type;
    bool status;
    Volition volition[3];

	string tmp;
	bool adj;
    
    while (input >> name) {
		//cout << name << endl;
        input >> gender;
		//cout << gender << endl;
        input >> number;
		//cout << number << endl;
        input >> score;
		//cout << score << endl;
        input >> id;
		//cout << id << endl;
        input >> password;
		//cout << password << endl;
        input >> type;
		//cout << type << endl;
        input >> status;
		//cout << status << endl;

        for (int i = 0; i < 3; i++) {
			input >> tmp;
            volition[i].setIdOfUniversity(tmp);
            for (int j = 0; j < Volition::NUMBER_OF_MAJOR; j++ ) {
				input >> tmp;
                volition[i].setIdOfMajor(j, tmp);
            }
			input >> adj;
            volition[i].setAdjustable(adj);
        }
        stu.push_back(Student(name, gender, number, score, id, password, type, status, volition));
    }
	input.close();
	cout << "Load succeed." << endl;
	show();
}

void Admin::show() {
	Student* tmp;
	cout << "Please choose your operation." << endl;
	cout << "1. Add a student." << endl;
	cout << "2. Delete a student." << endl;
	cout << "3. Modify a student." << endl;
	cout << "4. Exit." << endl;
	int opt;
	cin >> opt;
	if (opt == 1) {
		tmp = add();
		tmp->show();
	}
	else if (opt == 2) {
		cout << "Please input the number of the student." << endl;
		string num;
		cin >> num;
		tmp = findstudent(num);
		if (tmp == 0) {
			cout << "Not found." << endl;
			show();
		}
		else {
			tmp->show();
			cout << "Confirm?" << endl;
			cout << "1. Yes." << endl;
			cout << "2. No." << endl;
			int ct;
			cin >> ct;
			if (ct == 1) {
				del(num);
			}
		}
	}
	else if (opt == 3) {
		cout << "Please input the number of the student." << endl;
		string num;
		cin >> num;
		Student* tmp = findstudent(num);
		if (tmp == 0) {
			cout << "Not found." << endl;
			show();
		}
		else {
			tmp->updata();//只修改个人信息
			tmp->show();
		}
	}
	else {
		save();
		return;
	}
	show();
}

Student* Admin::add() {
	string name;
    string gender;
    string number;
    int score;
    string id;
    string password;
    string type;
    bool status;
	Volition volition[3];

	cout << "Please input the name of the student." << endl;
	cin >> name;
	cout << "Please input the gender of the student." << endl;
	cin >> gender;
	cout << "Please input the number of the student." << endl;
    cin >> number;
	cout << "Please input the score of the student." << endl;
	cin >> score;
	cout << "Please input the id of the student." << endl;
    cin >> id;
	cout << "Please input the password of the student." << endl;
	cin >> password;
	cout << "Please input the type of the student." << endl;
	cin >> type;
    status = 0;

	string tmp = "null";

	for (int i = 0; i < 3; i++) {
        volition[i].setIdOfUniversity(tmp);
        for (int j = 0; j < Volition::NUMBER_OF_MAJOR; j++ ) {
            volition[i].setIdOfMajor(j, tmp);
        }
        volition[i].setAdjustable(0);
    }
    stu.push_back(Student(name, gender, number, score, id, password, type, status, volition));
	cout << "Add successfully." << endl;
}

void Admin::del(string num) {
	for (int i = 0; i <(int)stu.size(); i++) {
		if (stu[i].getNumber == num) {
			stu.erase(stu.begin() + i);
			break;
		}
	}
	cout << "Delete successfully." << endl;
}

void Admin::save() {
	ofstream output(filename.c_str());
	for (int i = 0; i < (int)studentDate.size(); i++) {
		output << studentDate[i].getName() << " ";
		output << studentDate[i].getGender() << " ";
		output << studentDate[i].getNumber() << " ";
		output << studentDate[i].getScore() << " ";
		output << studentDate[i].getId() << " ";
		output << studentDate[i].getPassword() << " ";
		output << studentDate[i].getType() << " ";
		output << studentDate[i].getStatus() << " ";
		for (int j = 0; j < 3; j++) {
			output << studentDate[i].getVolition(j).getIdOfUniversity() << " ";
			for (int k = 0; k < Volition::NUMBER_OF_MAJOR; k++) {
				output << studentDate[i].getVolition(j).getIdOfMajor(k) << " ";
			}
			output << studentDate[i].getVolition(j).getAdjustable() << " ";
		}
		output << endl;
	}
}

void Admin::checkin() {
	Admit a;
	a.start();
}