#ifndef BOOK_H
#define BOOK_H

#include "product.h" // comes w the other inclusion stuff!! string, set, etc


class Book : public Product {
    public:
    Book(const std::string name, double price, int quantity, const std::string ISBN, const std::string authour);
    virtual ~Book();

    std::set<std::string> keywords () const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

    private:
    std::string ISBN_;
    std::string author_;
};

#endif