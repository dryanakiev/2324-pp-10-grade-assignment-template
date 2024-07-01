#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "books.h"

class Account {
private:
    std::string username;
    std::string password;
    std::vector<std::string> addedBooks;
    std::vector<std::string> borrowedBooks;

public:
    Account(const std::string& username, const std::string& password);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    const std::vector<std::string>& getAddedBooks() const;
    const std::vector<std::string>& getBorrowedBooks() const;

    // Methods
    bool saveToFile() const;
    static bool loadFromFile(const std::string& username, Account& account);
    void addBook(const std::string& bookInfo);
    void borrowBook(const std::string& bookInfo);
};

#endif // ACCOUNT_H
