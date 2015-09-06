#include "stdhead.h"
#include "Volition.h"

using namespace std;

class Student {
public:
    Student(string name, string gender, string number, int score, string id, string password, string type, bool status, Volition* volition);
    void show();
    void modify();
    void confirm();
    string getNumber() const;
    string getPassword() const;
	string getName() const;
	string getGender() const;
	int getScore() const;
	string getId() const;
	string getType() const;
	bool getStatus() const;
	Volition& getVolition(int x);
	void updata();
private:    
    string name;
    string gender;
    string number;
    int score;
    string id;
    string password;
    string type;
    bool status;
    Volition volition[3];
};


Student::Student(string name, string gender, string number, int score, string id, string password, string type, bool status, Volition* volition) {
    this->name = name;
    this->gender = gender;
    this->number = number;
    this->score = score;
	this->id = id;
    this->password = password;
    this->type = type;
	this->status = status;
    for (int i = 0; i < 3; i++) {
        this->volition[i] = volition[i];
    }
}

void Student::show() {
    cout << "Your information is as follows." << endl;
	cout << "Name: " << name << endl;
	cout << "Gender: " << gender << endl;
	cout << "Number: " << number << endl;
	cout << "Score: " << score << endl;
	cout << "Id: " << id << endl;
	cout << "Type: " << type << endl;
	if (status) cout << "Status: Confirmed." << endl;
	else cout << "Status: Not Confirmed." << endl;

	for (int i = 0; i < 3; i++) {
        volition[i].show();
    }
    
    int opt;
    if (!status) {
        cout << "Please choose you operation:" <<endl;
        cout << "1: Modify your volitions." << endl;
        cout << "2: Confirm your volitions." << endl;
        cout << "3: Exit." << endl;
        cin >> opt;
        if (opt == 1) {
            modify();
            show();
        }
        else if (opt == 2) {
            confirm();
            show();
        }
        else if (opt == 3) {
            return;
        }
        else {
            show();
        }
    }
    else {
        cout << "Please choose you operation:" <<endl;
        cout << "1: Show your information." << endl;
        cout << "2: Exit." << endl;
		cin >>opt;
        if (opt == 1) {
            show();
        }
        else if (opt == 2) {
            return;
        }
        else {
            show();
        }
    }
}

void Student::modify() {
    for (int i = 0; i < 3; i++) {
        volition[i].modify();
    }
	cout << "Success." << endl;
    show();
}

void Student::confirm() {
    cout << "confirm?" << endl;
    cout << "1: Yes." << endl;
    cout << "2: No." << endl;
    int opt;
	cin >> opt;
    if (opt == 1) status = true;
    else if (opt == 2) status = false;
    else confirm();
}

void Student::updata() {
	cout << "Please input the new name of the student." << endl;
	cin >> name;
	cout << "Please input the new gender of the student." << endl;
	cin >> gender;
	cout << "Please input the new number of the student." << endl;
    cin >> number;
	cout << "Please input the new score of the student." << endl;
	cin >> score;
	cout << "Please input the new id of the student." << endl;
    cin >> id;
	cout << "Please input the new password of the student." << endl;
	cin >> password;
	cout << "Please input the new type of the student." << endl;
    cin >> type;
	cout << "Please input the new status of the student." << endl;
    cin >> status;
	cout << "Change successfully." << endl;
}

string Student::getNumber() const {
    return number;
}

string Student::getPassword() const {
    return password;
}

string Student::getName() const {
	return name;
}

string Student::getGender() const {
	return gender;
}

int Student::getScore() const {
	return score;
}

string Student::getId() const {
	return id;
}

string Student::getType() const {
	return type;
}

bool Student::getStatus() const {
	return status;
}

Volition& Student::getVolition(int x) {
	return volition[x];
}