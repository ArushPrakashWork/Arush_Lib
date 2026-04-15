// Library Management System with permanent file storage
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to store book details
struct Book
{
    int id;              // Unique book ID
    string title;        // Book title
    string author;       // Author name
    int quantity;        // Available quantity
};

// Structure to store member account details
struct Account
{
    int memberId;        // Unique member ID
    string name;         // Member name
    int issuedBookId;    // ID of currently issued book
    bool hasBook;        // Whether member currently has a book
};

// Global arrays for books and members
Book books[50];
Account accounts[50];
int totalBooks = 0;
int totalAccounts = 0;

// Save all books to file permanently
void saveBooks()
{
    ofstream file("books.txt");
    file << totalBooks << endl;
    for (int i = 0; i < totalBooks; i++)
    {
        file << books[i].id << endl;
        file << books[i].title << endl;
        file << books[i].author << endl;
        file << books[i].quantity << endl;
    }
    file.close();
}

// Load books from file when program starts
void loadBooks()
{
    ifstream file("books.txt");
    if (!file)
        return;

    file >> totalBooks;
    file.ignore();

    for (int i = 0; i < totalBooks; i++)
    {
        file >> books[i].id;
        file.ignore();
        getline(file, books[i].title);
        getline(file, books[i].author);
        file >> books[i].quantity;
        file.ignore();
    }
    file.close();
}

// Save all member accounts permanently
void saveAccounts()
{
    ofstream file("accounts.txt");
    file << totalAccounts << endl;
    for (int i = 0; i < totalAccounts; i++)
    {
        file << accounts[i].memberId << endl;
        file << accounts[i].name << endl;
        file << accounts[i].issuedBookId << endl;
        file << accounts[i].hasBook << endl;
    }
    file.close();
}

// Load member accounts from file
void loadAccounts()
{
    ifstream file("accounts.txt");
    if (!file)
        return;

    file >> totalAccounts;
    file.ignore();

    for (int i = 0; i < totalAccounts; i++)
    {
        file >> accounts[i].memberId;
        file.ignore();
        getline(file, accounts[i].name);
        file >> accounts[i].issuedBookId;
        file >> accounts[i].hasBook;
        file.ignore();
    }
    file.close();
}

// Add new books to library
void addBooks()
{
    int ch;
    cout << "How many books do you want to add? ";
    cin >> ch;
    cin.ignore();

    for (int i = totalBooks; i < totalBooks + ch; i++)
    {
        cout << "\nEnter details of Book " << i + 1 << endl;
        cout << "Enter Book ID: ";
        cin >> books[i].id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, books[i].title);

        cout << "Enter Author Name: ";
        getline(cin, books[i].author);

        cout << "Enter Quantity: ";
        cin >> books[i].quantity;
        cin.ignore();
    }

    totalBooks += ch;
    saveBooks();
    cout << "\nBooks saved permanently.\n";
}

// Create a new member account
void createAccount()
{
    cout << "\nEnter Member ID: ";
    cin >> accounts[totalAccounts].memberId;
    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, accounts[totalAccounts].name);

    accounts[totalAccounts].issuedBookId = -1;
    accounts[totalAccounts].hasBook = false;

    totalAccounts++;
    saveAccounts();
    cout << "\nLibrary account created successfully.\n";
}

// Display all books
void showBooks()
{
    for (int i = 0; i < totalBooks; i++)
    {
        cout << "\nID: " << books[i].id;
        cout << "\nTitle: " << books[i].title;
        cout << "\nAuthor: " << books[i].author;
        cout << "\nQuantity: " << books[i].quantity << endl;
    }
}

// Issue a book to a member
void issueBook()
{
    int memberId, bookId;
    cout << "\nEnter Member ID: ";
    cin >> memberId;
    cout << "Enter Book ID to issue: ";
    cin >> bookId;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].memberId == memberId)
        {
            for (int j = 0; j < totalBooks; j++)
            {
                if (books[j].id == bookId && books[j].quantity > 0)
                {
                    books[j].quantity--;
                    accounts[i].issuedBookId = bookId;
                    accounts[i].hasBook = true;
                    saveBooks();
                    saveAccounts();
                    cout << "\nBook issued successfully.\n";
                    return;
                }
            }
        }
    }
    cout << "\nIssue failed. Check member ID or book availability.\n";
}

// Return a previously issued book
void returnBook()
{
    int memberId;
    cout << "\nEnter Member ID: ";
    cin >> memberId;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].memberId == memberId && accounts[i].hasBook)
        {
            for (int j = 0; j < totalBooks; j++)
            {
                if (books[j].id == accounts[i].issuedBookId)
                {
                    books[j].quantity++;
                    accounts[i].issuedBookId = -1;
                    accounts[i].hasBook = false;
                    saveBooks();
                    saveAccounts();
                    cout << "\nBook returned successfully.\n";
                    return;
                }
            }
        }
    }
    cout << "\nReturn failed.\n";
}

// Main menu-driven function
int main()
{
    loadBooks();      // Load previous book data
    loadAccounts();   // Load previous member data

    int choice;

    while (true)
    {
        cout << "\n====== Library Management System ======\n";
        cout << "1. Add Books\n";
        cout << "2. Create Library Account\n";
        cout << "3. Show Books\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBooks();
            break;
        case 2:
            createAccount();
            break;
        case 3:
            showBooks();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            returnBook();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
