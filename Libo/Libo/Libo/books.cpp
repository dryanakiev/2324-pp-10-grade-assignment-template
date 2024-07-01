

#include <string>

class Book {
public:
    Book(std::string title, std::string author, std::string isbn)
        : title(title), author(author), isbn(isbn), isBorrowed(false) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    bool getBorrowedStatus() const { return isBorrowed; }
    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isBorrowed;
};
