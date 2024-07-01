

#include <iostream>
#include <vector>
#include "books.h"

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const std::string& isbn) {
        books.erase(std::remove_if(books.begin(), books.end(),
            [&](const Book& b) { return b.getISBN() == isbn; }), books.end());
    }

    Book* searchBook(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    void listBooks() const {
        for (const auto& book : books) {
            std::cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor()
                << ", ISBN: " << book.getISBN() << ", Borrowed: " << (book.getBorrowedStatus() ? "Yes" : "No") << std::endl;
        }
    }

private:
    std::vector<Book> books;
};
