#include "stdhead.h"

using namespace std;


class BookInformation {
protected:
    string bookName;
    string press;
    string author;
    string isbn;
    string id;
public:
    BookInformation();
    void viewInfo();
    void updata();
    string getBookName();
    string getId();
};

BookInformation::BookInformation() {
    bookName = press = author = isbn = id = "null";
}

void BookInformation::viewInfo() {
    cout << "BookName: " << bookName << endl;
    cout << "Press: " << press << endl;
    cout << "Author: " << author << endl;
    cout << "Isbn: " << isbn << endl;
    cout << "Id: " << id << endl;
    cout << endl;
}

string BookInformation::getBookName() {
    return bookName;
}

string BookInformation::getId() {
    return id;
}

void BookInformation::updata() {
    cout << "Please input the information of the book." << endl;
    cout << "Please input Name, Press, Author, Isbn, Id." << endl;
    cin >> bookName;
    cin >> press;
    cin >> author;
    cin >> isbn;
    cin >> id;
    cout << "Operate successfully." << endl;
}