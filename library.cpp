#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() {
        issued = false;
    }
};

void addBook() {
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    b.issued = false;

    ofstream file("books.txt", ios::app);
    file << b.id << "," << b.title << "," << b.author << ","
         << b.issued << endl;
    file.close();

    cout << "Book added successfully!\n";
}

void displayBooks() {
    ifstream file("books.txt");
    string line;

    cout << "\n--- Library Books ---\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchBook() {
    string keyword;
    cin.ignore();

    cout << "Enter title or author to search: ";
    getline(cin, keyword);

    ifstream file("books.txt");
    string line;

    bool found = false;

    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "Book Found: " << line << endl;
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Book not found.\n";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t p1 = line.find(',');
        int bookId = stoi(line.substr(0, p1));

        if (bookId == id) {
            found = true;

            size_t p2 = line.find(',', p1 + 1);
            size_t p3 = line.find(',', p2 + 1);

            string status = line.substr(p3 + 1);

            if (status == "0") {
                line = line.substr(0, p3 + 1) + "1";
                cout << "Book issued successfully!\n";
            } else {
                cout << "Book is already issued.\n";
            }
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t p1 = line.find(',');
        int bookId = stoi(line.substr(0, p1));

        if (bookId == id) {
            found = true;

            size_t p3 = line.rfind(',');

            string status = line.substr(p3 + 1);

            if (status == "1") {
                line = line.substr(0, p3 + 1) + "0";
                cout << "Book returned successfully!\n";
            } else {
                cout << "Book was not issued.\n";
            }
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}