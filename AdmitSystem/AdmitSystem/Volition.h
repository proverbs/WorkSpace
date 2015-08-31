#include "stdhead.h"

using namespace std;

class Volition {
public:
    void show();
    void modify();
	void setIdOfUniversity(string id);
	void setIdOfMajor(int seq, string id);
	void setAdjustable(bool adj);
	string getIdOfUniversity() const;
	string getIdOfMajor(int seq) const;
	bool getAdjustable() const;
	const static int NUMBER_OF_MAJOR = 3;
private:    
    string idOfUniversity;
    string idOfMajor[NUMBER_OF_MAJOR];
    bool adjustable;
};

//const int Volition::NUMBER_OF_MAJOR = 3;类中静态常量的定义？？？？

string Volition::getIdOfUniversity() const {
	return idOfUniversity;
}
string Volition::getIdOfMajor(int seq) const {
	return idOfMajor[seq];
}
bool Volition::getAdjustable() const {
	return adjustable;
}


void Volition::setAdjustable(bool adj) {
	adjustable = adj;
}

void Volition::setIdOfMajor(int seq, string id) {
	idOfMajor[seq] = id;
}

void Volition::setIdOfUniversity(string id) {
	idOfUniversity = id;
}

void Volition::show() {
	cout << endl;
    cout << "University: " << idOfUniversity << endl;
	for (int i = 0; i < Volition::NUMBER_OF_MAJOR; i++) {
		cout << "Volition" << i + 1 << ": " << idOfMajor[i] << endl;
	}
	if (adjustable) cout << "Adjustable." << endl;
	else cout << "Unadjustable." << endl;
}

void Volition::modify() {
	cout << "Please input your volition information." << endl;
	cout << "Please input id of university." << endl;
	cin >> idOfUniversity;
	for (int i = 0; i < NUMBER_OF_MAJOR; i++) {
		cout << "Please input major " << i + 1 << "." << endl;
		cin >> idOfMajor[i];
	}
}