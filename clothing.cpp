#include <sstream>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int quantity, const std::string size, const std::string brand) :
    Product("clothing", name, price, quantity),
    size_(size),
    brand_(brand)
{}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const {
    set<string> nameWords = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);
    set<string> keys = setUnion(nameWords, brandWords);
    return keys;
}

std::string Clothing::displayString() const {
    stringstream ss;
    ss << name_ << "\n"
       << "Size: " << size_ << " Brand: " << brand_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}