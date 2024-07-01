

#include <iostream>
#include <string>
#include <vector>
#include "library.h"
#include "account.h"

void showMenu() {
    std::cout << "Library Management System\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Remove Book\n";
    std::cout << "3. Search Book\n";
    std::cout << "4. List All Books\n";
    std::cout << "5. Borrow Book\n";
    std::cout << "6. Return Book\n";
    std::cout << "7. What is ISBN?\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void showAccountMenu() {
    std::cout << "Account Management System\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Log In\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void explainISBN() {
    std::cout << "ISBN (International Standard Book Number) is a unique numeric commercial book identifier.\n";
    std::cout << "ISBNs are assigned to each edition and variation (except reprints) of a book.\n";
    std::cout << "For example, if you have a book with the ISBN 978-3-16-148410-0, this is the unique identifier for that book edition.\n";
}

bool getInput(std::string& input) {
    std::getline(std::cin, input);
    return input != "exit";
}

int main() {
    Library library;
    int choice;
    Account currentAccount("", "");

    while (true) {
        showAccountMenu();
        std::cin >> choice;
        std::cin.ignore();  // Clear newline character from input buffer

        if (choice == 0) break;

        std::string username, password;
        switch (choice) {
        case 1: // Create Account
            std::cout << "Enter username (type 'exit' to cancel): ";
            if (!getInput(username)) break;

            std::cout << "Enter password (type 'exit' to cancel): ";
            if (!getInput(password)) break;

            {
                Account newAccount(username, password);
                if (newAccount.saveToFile()) {
                    std::cout << "Account created successfully.\n";
                }
                else {
                    std::cout << "Failed to create account.\n";
                }
            }
            break;

        case 2: // Log In
            std::cout << "Enter username (type 'exit' to cancel): ";
            if (!getInput(username)) break;

            std::cout << "Enter password (type 'exit' to cancel): ";
            if (!getInput(password)) break;

            if (Account::loadFromFile(username, currentAccount) && currentAccount.getPassword() == password) {
                std::cout << "Logged in successfully.\n";

                // Main library management loop
                while (true) {
                    showMenu();
                    std::cin >> choice;
                    std::cin.ignore();  // Clear newline character from input buffer

                    if (choice == 0) break;

                    std::string title, author, isbn;
                    switch (choice) {
                    case 1:
                        std::cout << "Enter title (type 'exit' to cancel): ";
                        if (!getInput(title)) break;

                        std::cout << "Enter author (type 'exit' to cancel): ";
                        if (!getInput(author)) break;

                        std::cout << "Enter ISBN (type 'exit' to cancel): ";
                        if (!getInput(isbn)) break;

                        library.addBook(Book(title, author, isbn));
                        currentAccount.addBook("Book added: " + title + ", " + author + ", ISBN: " + isbn);
                        break;

                    case 2:
                        std::cout << "Enter ISBN to remove (type 'exit' to cancel): ";
                        if (!getInput(isbn)) break;

                        library.removeBook(isbn);
                        break;

                    case 3:
                        std::cout << "Enter ISBN to search (type 'exit' to cancel): ";
                        if (!getInput(isbn)) break;

                        if (Book* book = library.searchBook(isbn)) {
                            std::cout << "Found: " << book->getTitle() << " by " << book->getAuthor() << std::endl;
                        }
                        else {
                            std::cout << "Book not found.\n";
                        }
                        break;

                    case 4:
                        library.listBooks();
                        break;

                    case 5:
                        std::cout << "Enter ISBN to borrow (type 'exit' to cancel): ";
                        if (!getInput(isbn)) break;

                        if (Book* book = library.searchBook(isbn)) {
                            if (!book->getBorrowedStatus()) {
                                book->borrowBook();
                                std::cout << "You borrowed: " << book->getTitle() << std::endl;
                                currentAccount.borrowBook("Book borrowed: " + book->getTitle() + ", " + book->getAuthor() + ", ISBN: " + isbn);
                            }
                            else {
                                std::cout << "Book is already borrowed.\n";
                            }
                        }
                        else {
                            std::cout << "Book not found.\n";
                        }
                        break;

                    case 6:
                        std::cout << "Enter ISBN to return (type 'exit' to cancel): ";
                        if (!getInput(isbn)) break;

                        if (Book* book = library.searchBook(isbn)) {
                            if (book->getBorrowedStatus()) {
                                book->returnBook();
                                std::cout << "You returned: " << book->getTitle() << std::endl;
                            }
                            else {
                                std::cout << "Book was not borrowed.\n";
                            }
                        }
                        else {
                            std::cout << "Book not found.\n";
                        }
                        break;

                    case 7:
                        explainISBN();
                        break;

                    default:
                        std::cout << "Invalid choice.\n";
                        break;
                    }
                }
            }
            else {
                std::cout << "Invalid username or password.\n";
            }
            break;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
