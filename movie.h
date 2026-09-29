#ifndef MOVIE_H
#define MOVIE_H

#include "product.h" // comes w the other inclusion stuff!! string, set, etc


class Movie : public Product {
    public:
    Movie(const std::string name, double price, int quantity, const std::string genre, const std::string rating);
    virtual ~Movie();

    std::set<std::string> keywords () const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

    private:
    std::string genre_;
    std::string rating_;
};

#endif