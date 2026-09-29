#include <sstream>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, double price, int quantity, const std::string genre, const std::string rating) :
    Product("movie", name, price, quantity),
    genre_(genre),
    rating_(rating)
{}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const {
    set<string> keys = parseStringToWords(name_);
    keys.insert(convToLower(genre_));
    return keys;
}

std::string Movie::displayString() const {
    stringstream ss;
    ss << name_ << "\n"
    << "Genre: " << genre_ << "\n"
    << "Rating: " << rating_ << "\n"
    << "Price: $" << price_ << "\n"
    << "Quantity: " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}
