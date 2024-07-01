

#include "account.h"
#include <fstream>
#include <iostream>
#include <sstream>

Account::Account(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

const std::vector<std::string>& Account::getAddedBooks() const {
    return addedBooks;
}

const std::vector<std::string>& Account::getBorrowedBooks() const {
    return borrowedBooks;
}

bool Account::saveToFile() const {
    std::ofstream outFile(username + ".txt");
    if (!outFile) {
        std::cerr << "Error: Failed to create or open file for account " << username << std::endl;
        return false;
    }

    outFile << "Username: " << username << "\n";
    outFile << "Password: " << password << "\n";

    if (!addedBooks.empty()) {
        outFile << "Added Books:\n";
        for (const auto& bookInfo : addedBooks) {
            outFile << bookInfo << "\n";
        }
    }

    if (!borrowedBooks.empty()) {
        outFile << "Borrowed Books:\n";
        for (const auto& bookInfo : borrowedBooks) {
            outFile << bookInfo << "\n";
        }
    }

    outFile.close();
    return true;
}

bool Account::loadFromFile(const std::string& username, Account& account) {
    std::ifstream inFile(username + ".txt");
    if (!inFile) {
        std::cerr << "Error: Failed to open file for account " << username << std::endl;
        return false;
    }

    std::string line;
    std::getline(inFile, line); // Read and ignore "Username: username"
    std::getline(inFile, line); // Read "Password: password"
    std::istringstream iss(line);
    std::string dummy, password;
    iss >> dummy >> password;

    account = Account(username, password);

    // Read added books
    while (std::getline(inFile, line)) {
        if (line == "Added Books:") {
            while (std::getline(inFile, line) && !line.empty()) {
                account.addedBooks.push_back(line);
            }
        }
        else if (line == "Borrowed Books:") {
            while (std::getline(inFile, line) && !line.empty()) {
                account.borrowedBooks.push_back(line);
            }
        }
    }

    inFile.close();
    return true;
}

void Account::addBook(const std::string& bookInfo) {
    addedBooks.push_back(bookInfo);
}

void Account::borrowBook(const std::string& bookInfo) {
    borrowedBooks.push_back(bookInfo);
}
