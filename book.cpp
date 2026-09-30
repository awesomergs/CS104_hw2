#include <sstream>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string name, double price, int quantity, const std::string ISBN, const std::string author) : 
    Product("book", name, price, quantity), 
    ISBN_(ISBN), 
    author_(author)
{}

Book::~Book(){}

std::set<std::string> Book::keywords() const {
    set<string> nameWords = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);
    set<string> keys = setUnion(nameWords, authorWords);
    keys.insert(convToLower(ISBN_));
    return keys;
}

std::string Book::displayString() const
{
    stringstream ss;
    ss << name_ << "\n"
       << "Author: " << author_ << " ISBN: " << ISBN_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << ISBN_ << "\n" << author_ << endl;
}