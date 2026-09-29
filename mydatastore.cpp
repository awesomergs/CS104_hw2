#include <iostream>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);

    set<string> keys = p->keywords();
    for (set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
        keywordMap_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string key = convToLower(u->getName());
    users_[key] = u;
    carts_[key];  
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    set<Product*> results;
    bool first = true;

    for (size_t i = 0; i < terms.size(); i++) {
        string term = convToLower(terms[i]);

        map<string, set<Product*> >::iterator it = keywordMap_.find(term);

        if (type == 0) {
            if (it == keywordMap_.end()) {
                return vector<Product*>();
            }
            if (first) {
                results = it->second;
                first = false;
            } else {
                results = setIntersection(results, it->second);
            }
        } else {
            if (it != keywordMap_.end()) {
                results = setUnion(results, it->second);
            }
        }
    }

    return vector<Product*>(results.begin(), results.end());
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(std::string username, Product* p)
{
    string key = convToLower(username);
    map<string, deque<Product*> >::iterator it = carts_.find(key);
    if (it == carts_.end()) {
        return false;
    }
    it->second.push_back(p);
    return true;
}

bool MyDataStore::viewCart(std::string username)
{
    string key = convToLower(username);
    map<string, deque<Product*> >::iterator it = carts_.find(key);
    if (it == carts_.end()) {
        return false;
    }

    deque<Product*>& cart = it->second;
    for (size_t i = 0; i < cart.size(); i++) {
        cout << "Item " << (i + 1) << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }
    return true;
}

bool MyDataStore::buyCart(std::string username)
{
    string key = convToLower(username);
    map<string, deque<Product*> >::iterator cartIt = carts_.find(key);
    if (cartIt == carts_.end()) {
        return false;
    }

    User* user = users_[key];
    deque<Product*>& cart = cartIt->second;
    deque<Product*> leftovers;

    for (size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            user->deductAmount(p->getPrice());
        } else {
            leftovers.push_back(p);
        }
    }

    cart = leftovers;
    return true;
}