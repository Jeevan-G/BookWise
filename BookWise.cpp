#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string genre;
    int quantity;
    bool available;

public:
    Book(const string& isbn, const string& title, const string& author,
         const string& genre, int quantity)
        : isbn(isbn), title(title), author(author), genre(genre), quantity(quantity), available(true) {}

    void displayDetails() const {
        cout << "ISBN: " << isbn << "\nTitle: " << title << "\nAuthor: " << author
                  << "\nGenre: " << genre << "\nQuantity: " << quantity << "\n";
        if (available)
            cout << "Availability: Available\n";
        else
            cout << "Availability: Not Available\n";
    }

    void updateQuantity(int change) {
        quantity += change;
        if (quantity <= 0)
            available = false;
        else
            available = true;
    }

    bool isAvailable() const {
        return available;
    }

    const string& getISBN() const {
        return isbn;
    }
};

class Member {
private:
    int id;
    string name;
    string contact;

public:
    Member(int id, const string& name, const string& contact)
        : id(id), name(name), contact(contact) {}

    void displayDetails() const {
        cout << "ID: " << id << "\nName: " << name << "\nContact: " << contact << "\n";
    }

    int getId() const {
        return id;
    }
};

class Transaction {
private:
    string bookId;
    int memberId;
    time_t date;
    bool isIssue;

public:
    Transaction(string bookId, int memberId, bool isIssue)
        : bookId(bookId), memberId(memberId), isIssue(isIssue) {
        time(&date);
    }

    string getBookId() const {
        return bookId;
    }

    int getMemberId() const {
        return memberId;
    }

    time_t getDate()  {
        return date;
    }

    bool isBookIssue() const {
        return isIssue;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    void addMember(const Member& member) {
        members.push_back(member);
    }

    Book* findBookByISBN(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    Member* findMemberById(int memberId) {
        for (auto& member : members) {
            if (member.getId() == memberId) {
                return &member;
            }
        }
        return nullptr;
    }

    void issueBook(const string& isbn, int memberId) {
        Book* book = findBookByISBN(isbn);
        Member* member = findMemberById(memberId);

        if (book && member && book->isAvailable()) {
            book->updateQuantity(-1);
            transactions.push_back(Transaction(isbn, memberId, true));
            cout << "Book issued successfully.\n";
        } else {
            cout << "Failed to issue book.\n";
        }
    }

    void returnBook(const string& isbn, int memberId) {
        Book* book = findBookByISBN(isbn);
        Member* member = findMemberById(memberId);

        if (book && member) {
            book->updateQuantity(1);
            transactions.push_back(Transaction(isbn, memberId, false));
            cout << "Book returned successfully.\n";
        } else {
            cout << "Failed to return book.\n";
        }
    }

    void displayTransactions()  {
        cout << "---- Transaction History ----\n";
        for (const auto& transaction : transactions) {
            cout << "Book ID: " << transaction.getBookId() << "\n";
            cout << "Member ID: " << transaction.getMemberId() << "\n";
            // char* ch=transaction.getDate();
            // cout << "Date: " << ctime(&ch );
            cout << "Type: " << (transaction.isBookIssue() ? "Issue" : "Return") << "\n";
            cout << "-----------------------------\n";
        }
    }
};

// User interface functions
void displayMainMenu() {
    cout << "===== Library Management System =====\n";
    cout << "1. Add Book\n";
    cout << "2. Add Member\n";
    cout << "3. Issue Book\n";
    cout << "4. Return Book\n";
    cout << "5. Display Transactions\n";
    cout << "6. Exit\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

void addBook(Library& library) {
    string isbn, title, author, genre;
    int quantity;

    cout << "Enter ISBN: ";
    cin >> isbn;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Genre: ";
    getline(cin, genre);
    cout << "Enter Quantity: ";
    cin >> quantity;

    Book newBook(isbn, title, author, genre, quantity);
    library.addBook(newBook);
    cout << "Book added successfully.\n";
}

void addMember(Library& library) {
    int id;
    string name, contact;

    cout << "Enter Member ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);

    Member newMember(id, name, contact);
    library.addMember(newMember);
    cout << "Member added successfully.\n";
}

void issueBook(Library& library) {
    string isbn;
    int memberId;

    cout << "Enter ISBN: ";
    cin >> isbn;
    cout << "Enter Member ID: ";
    cin >> memberId;

    library.issueBook(isbn, memberId);
}

void returnBook(Library& library) {
    string isbn;
    int memberId;

    cout << "Enter ISBN: ";
    cin >> isbn;
    cout << "Enter Member ID: ";
    cin >> memberId;

    library.returnBook(isbn, memberId);
}

int main() {
    Library library;

    // Sample initialization
    Book book1("123456789", "Sample Book 1", "Author 1", "Fiction", 5);
    Book book2("987654321", "Sample Book 2", "Author 2", "Non-Fiction", 3);
    library.addBook(book1);
    library.addBook(book2);

    Member member1(101, "John Doe", "john@example.com");
    Member member2(102, "Jane Smith", "jane@example.com");
    library.addMember(member1);
    library.addMember(member2);

    bool exitProgram = false;
    while (!exitProgram) {
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                addMember(library);
                break;
            case 3:
                issueBook(library);
                break;
            case 4:
                returnBook(library);
                break;
            case 5:
                library.displayTransactions();
                break;
            case 6:
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

