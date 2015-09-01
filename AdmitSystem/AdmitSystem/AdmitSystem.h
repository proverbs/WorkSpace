#include "stdhead.h"
#include "Student.h"

using namespace std;

class AdmitSystem {
public:
    AdmitSystem();
    ~AdmitSystem();
    void init();
    void save();
    void login();
    Student* finduser(string number, string password);
private:    
    vector<Student> studentDate;
	ifstream input;
	string filename;
};

AdmitSystem::AdmitSystem() {
    cout << "Please input the filename you want to load." << endl;
    cin >> filename;
    input.open(filename.c_str());
    init();
    input.close();
    login();
}

AdmitSystem::~AdmitSystem() {
    save();
}

void AdmitSystem::init() {
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
        studentDate.push_back(Student(name, gender, number, score, id, password, type, status, volition));
    }
}

void AdmitSystem::save() {
    ofstream output(filename.c_str());
	for (int i = 1; i < (int)studentDate.size(); i++) {
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
				output << studentDate[i].getVolition(j).getIdOfMajor(k + 1) << " ";
			}
			output << studentDate[i].getVolition(j).getAdjustable() << " ";
		}
	}
}

void AdmitSystem::login() {
    int opt;
    cout << "Please choose you operation:" <<endl;
    cout << "1: Log in." << endl;
    cout << "2: Exit." << endl;
    cin >> opt;
    if (opt == 2) return;
    
    string number;
    string password;
    cout << "Please input your exam number." << endl;
    cin >> number;
    cout << "Please input your password." << endl;
    cin >> password;
    Student* user;
    user = finduser(number, password);
    if (!user) {
        cout << "Exam number or password is incorrect." << endl;
        login();
    }
    else {
        cout << "Log in successfully." << endl;
        user->show();
    }
}

Student* AdmitSystem::finduser(string number, string password) {
    for (int i = 0; i < (int)studentDate.size(); i++) {
        if (studentDate[i].getNumber() == number && studentDate[i].getPassword() == password) {
            return &studentDate[i];
        }
    }
    return 0;
}
