#include "BookInformation.h"
#include "stdhead.h"

using namespace std;

class LibraryBook : public BookInformation {
private:
    bool isBorrowed;
    vector<string> name;
    vector<string> lendTime;
    vector<string> returnTime;
public:
    LibraryBook();
    LibraryBook(string bookName, string press, string author, string isbn, string id,
		bool isBorrowed, vector<string> name, vector<string> lendTime, vector<string> returnTime);
    void view();
    void setStatus(bool s);
    void setLendTime();
    void setReturnTime();  
    void setName(string str);
    void save(ofstream& output);
};

LibraryBook::LibraryBook() : BookInformation() {
    isBorrowed = 0;
}

LibraryBook::LibraryBook(string bookName, string press, string author, string isbn, string id,
	bool isBorrowed, vector<string> name, vector<string> lendTime, vector<string> returnTime) {
    this->bookName = bookName;
    this->press = press;
    this->author = author;
	this->isbn = isbn;
	this->id = id;
	this->isBorrowed = isBorrowed;
	this->name = name; 
    this->lendTime = lendTime;
	this->returnTime = returnTime;
 }

void LibraryBook::view() {
    viewInfo();
    if (isBorrowed == 0) cout << "On shelf." << endl;
    else cout << "Not on shelf." << endl;
    for (int i = 0; i < (int)name.size(); i++) {
    	cout << i << endl;
        cout << "Reader's name: " << name[i] << endl;
        cout << "Lend time: " << lendTime[i] << endl;
        cout << "Return time: " << returnTime[i] << endl;
        cout << endl;
    }
    cout << endl;
}

void LibraryBook::setStatus(bool s) {
    isBorrowed = s;
}

void LibraryBook::setLendTime() {
    cout << "Please input time." << endl;
    string tim;
    cin >> tim;
    lendTime.push_back(tim);
    returnTime.push_back("null");
}

void LibraryBook::setReturnTime() {
    cout << "Please input time." << endl;
    string tim;
    cin >> tim;
    returnTime[returnTime.size() - 1] = tim;
}

void LibraryBook::setName(string str) {
	name.push_back(str);
}

void LibraryBook::save(ofstream& output) {
	output << bookName << " ";
	output << press << " ";
    output << author << " ";
    output << isbn << " ";
    output << id << " ";
    output << isBorrowed << " "; 
    for (int i = 0; i < (int)name.size(); i++) {
    	output << name[i] << " ";	
	}
	output << "# ";
	for (int i = 0; i < (int)lendTime.size(); i++) {
    	output << lendTime[i] << " ";	
	}
	output << "# ";
	for (int i = 0; i < (int)returnTime.size(); i++) {
    	output << returnTime[i] << " ";	
	}
	output << "#" << endl;
}