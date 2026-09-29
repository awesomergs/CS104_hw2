#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h" // comes w the other inclusion stuff!! string, set, etc


class Clothing : public Product {
    public:
    Clothing(const std::string name, double price, int quantity, const std::string size, const std::string brand);
    virtual ~Clothing();

    std::set<std::string> keywords () const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

    private:
    std::string size_;
    std::string brand_;
};

#endif