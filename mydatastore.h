#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <deque>

#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    bool addToCart(std::string username, Product* p);
    bool viewCart(std::string username);
    bool buyCart(std::string username);

private:
    std::set<Product*> products_;
    std::map<std::string, User*> users_; 
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::deque<Product*> > carts_;
};

#endif