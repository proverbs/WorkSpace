#include "stdhead.h"
#include "Reader.h"

using namespace std;

class BookManager {
private:
    vector<LibraryBook> book;
    vector<Reader> reader;
public:
    BookManager();
    void show();//add main module
    void viewName(string name);
    void viewId(string id);
    void add();
    void updata(string id);
    void delet(string id);
    void lendBook(string id);
    void returnBook(string id);
    void save();
    void viewReader(string name);
    void addReader();
    void deleteReader(string name);
	void updataReader(string name);
};

BookManager::BookManager() {
    ifstream input("data.txt");
    
    string bookName;
    string press;
    string author;
    string isbn;
    string id;
    bool isBorrowed;
    vector<string> name;
    vector<string> lendTime;
    vector<string> returnTime;
    string tmp;
    
    while (input >> bookName) {
        input >> press;
        input >> author;
        input >> isbn;
        input >> id;
        input >> isBorrowed;
        //system("pause");
        name.clear();
        while (true) {
            input >> tmp;
            if (tmp == "#") break;
            name.push_back(tmp);
        }
        
        lendTime.clear();
        while (true) {
            input >> tmp;
            if (tmp == "#") break;
            lendTime.push_back(tmp);
        }
        
        returnTime.clear();
        while (true) {
            input >> tmp;
            if (tmp == "#") break;
            returnTime.push_back(tmp);
        }
        book.push_back(LibraryBook(bookName, press, author, isbn, id, isBorrowed, name, 
        	lendTime, returnTime));
    }
    input.close();
    
    input.open("reader.txt");
    
    string readerName;
    while (input >> readerName) {
    	input >> id;
    	while (input >> tmp) {
    		if (tmp == "#") break;
    		for (int i = 0; i < (int)book.size(); i++)
    			if (book[i].getId() == tmp) {
					reader[i].getNowBook().push_back(&book[i]);
				}
		}
		
    	while (input >> tmp) {
    		if (tmp == "#") break;
    		for (int i = 0; i < (int)book.size(); i++)
    			if (book[i].getId() == tmp) {
					reader[i].getPreBook().push_back(&book[i]);
				}
		}
	}
	input.close();
}

void BookManager::save() {
	ofstream output("data.txt");
	for (int i = 0; i < (int)book.size(); i++) {
		book[i].save(output);
	}
	output.close();
	
	output.open("reader.txt");
	for (int i = 0; i < (int)reader.size(); i++) {
		reader[i].save(output);
	}
	output.close();
}

void BookManager::show() {
    cout << "Please choose your operation." << endl;
    cout << "1. View a book via name." << endl;
    cout << "2. View a book via id." << endl;
    cout << "3. Add a book." << endl;
    cout << "4. Updata a book via id." << endl;
    cout << "5. Delete a book via id" << endl;
    cout << "6. Lend." << endl;
    cout << "7. Return." << endl;
    cout << "8. View reader's information via name." << endl;
    cout << "9. Delete a reader via name." << endl;
    cout << "10. Add a reader." << endl;
	cout << "11. Updata a reader via name." << endl;
    cout << "12. Exit." << endl;
    int opt;
    cin >> opt;
    if (opt == 1) {
    	cout << "Please input the name." << endl;
        string name;
        cin >> name;
        viewName(name);
    }
    else if (opt == 2) {
    	cout << "Please input the id." << endl;
        string id;
        cin >> id;
        viewId(id);
    }
    else if (opt == 3) {
        add();
    }
    else if (opt == 4) {
    	cout << "Please input the id." << endl;
        string id;
        cin >> id;
        updata(id);
    }
    else if (opt == 5) {
    	cout << "Please input the id." << endl;
        string id;
        cin >> id;
        delet(id);
    }
    else if (opt == 6) {
    	cout << "Please input the id." << endl;
        string id;
        cin >> id;
        lendBook(id);
    }
    else if (opt == 7) {
    	cout << "Please input the id." << endl;
        string id;
        cin >> id;
        returnBook(id);
    }
    else if (opt == 8) {
    	cout << "Please input the name." << endl;
        string name;
        cin >> name;
        viewReader(name);
    }
    else if (opt == 9) {
    	cout << "Please input the name." << endl;
        string name;
        cin >> name;
        deleteReader(name);
    }
    else if (opt == 10) {
        addReader();
    }
	else if (opt == 11) {
    	cout << "Please input the name." << endl;
        string name;
        cin >> name;
        updataReader(name);
    }
    else {
    	save();
        return;
    }
    show();
}

void BookManager::viewName(string name) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getBookName() == name) {
            book[i].view();
            flag = true;
            cout << endl;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
}

void BookManager::viewId(string id) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getId() == id) {
            book[i].view();
            flag = true;
            cout << endl;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
}

void BookManager::add() {
    book.push_back(LibraryBook());
    book[book.size() - 1].updata();
}

void BookManager::updata(string id) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getId() == id) {
            book[i].updata();
            flag = true;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
    else cout << "Updata successfully." << endl;
}

void BookManager::delet(string id) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getId() == id) {
            book.erase(book.begin() + i);
            flag = true;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
    else cout << "Delete successfully." << endl;
}

void BookManager::lendBook(string id) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getId() == id) {
        	cout << "Please input the reader's name." << endl;
        	string str;
        	cin >> str;
        	book[i].setName(str);
            book[i].setStatus(1);
            book[i].setLendTime();
            for (int j = 0; j < (int)reader.size(); j++)
            	if (reader[j].getName() == str) {
            		reader[j].borrowBook(&book[i]);
            		break;
				}
            flag = true;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
    else cout << "Borrow successfully." << endl;
}

void BookManager::returnBook(string id) {
    bool flag = false;
    for (int i = 0; i < (int)book.size(); i++) {
        if (book[i].getId() == id) {
        	cout << "Please input the reader's name." << endl;
        	string str;
        	cin >> str;
            book[i].setStatus(0);
            book[i].setReturnTime();
            for (int j = 0; j < (int)reader.size(); j++)
            	if (reader[j].getName() == str) {
            		reader[j].returnBook(&book[i]);
            		break;
				}
            flag = true;
            break;
        }
    }
    if (!flag) cout << "Not found." << endl;
    else cout << "Return successfully." << endl;
}

void BookManager::viewReader(string name) {
	bool flag = false;
	for (int i = 0; i < (int)reader.size(); i++)
		if (reader[i].getName() == name) {
			reader[i].view();
			flag = true;
			break;
		}
	if (!flag) cout << "Not found." << endl;
}

void BookManager::addReader() {
	string name, id;
	cout << "Please input the reader's name." << endl;
	cin >> name;
	cout << "Please input the reader's id." << endl;
	cin >> id;
	reader.push_back(Reader(name, id));
}

void BookManager::deleteReader(string name) {
	bool flag = false;
	for (int i = 0; i < (int)reader.size(); i++)
		if (reader[i].getName() == name) {
			reader.erase(reader.begin() + i);
			flag = true;
			break;
		}
	if (!flag) cout << "Not found." << endl;
    else cout << "Delete successfully." << endl;
}

void BookManager::updataReader(string name) {
	bool flag = false;
	for (int i = 0; i < (int)reader.size(); i++)
		if (reader[i].getName() == name) {
			reader[i].updata();
			flag = true;
			break;
		}
	if (!flag) cout << "Not found." << endl;
}