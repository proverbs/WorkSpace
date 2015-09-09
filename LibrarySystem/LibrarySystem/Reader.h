#include "stdhead.h"
#include "LibraryBook.h"

using namespace std;

class Reader {
private:
	string name;
	string id;
	vector<LibraryBook*> preBook;
	vector<LibraryBook*> nowBook;
public:
	Reader(string name, string id);
	string getName();
	void view();
	void updata();
	void borrowBook(LibraryBook* b);
	void returnBook(LibraryBook* b); 
	vector<class LibraryBook*>& getNowBook();
	vector<class LibraryBook*>& getPreBook();
	void save(ofstream& output);
}; 

vector<class LibraryBook*>& Reader::getNowBook() {
	return nowBook;
}

vector<class LibraryBook*>& Reader::getPreBook() {
	return preBook;
}

string Reader::getName() {
	return name;
}

void Reader::save(ofstream& output) {
	output << name << " ";
	output << id << " ";
	for (int i = 0; i < (int)nowBook.size(); i++)
		output << nowBook[i]->getId() << " ";
	output << "# ";
	for (int i = 0; i < (int)preBook.size(); i++)
		output << preBook[i]->getId() << " ";
	output << "#" << endl;
}

void Reader::updata() {
	cout << "Please input the reader's name." << endl;
	cin >> name;
	cout << "Please input the reader's id." << endl;
	cin >> id;
	cout << "Change successfully." << endl;
}

Reader::Reader(string name, string id) {
	this->name = name;
	this->id = id;
}

void Reader::borrowBook(LibraryBook* b) {
	nowBook.push_back(b);
}

void Reader::returnBook(LibraryBook* b) {
	preBook.push_back(b);
	for (int i = 0; i < (int)nowBook.size(); i++)
		if (nowBook[i]->getId() == b->getId()) {
			nowBook.erase(nowBook.begin() + i);
		}
}

void Reader::view() {
	cout << "Name: " << name << endl;
	cout << "Id: " << id << endl;
	cout << "NowBorrow: " << endl;
	for (int i = 0; i < (int)nowBook.size(); i++)
		nowBook[i]->view();
	cout << "PreBorrow: " << endl;
	for (int i = 0; i < (int)preBook.size(); i++)
		preBook[i]->view();
}