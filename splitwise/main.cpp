// adding the code for the main function to test the Splitwise class
//please add this too, I created a branch and merged
#include <iostream>
#include <vector>
#include <string>
using namespace std; 
class user{
    int id;
    string name;
    public:
    user(int id, string name): id(id), name(name) {}
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
};   
class split{
    int id;
    double amount;
    user* owed;
    user* paidBy;
    public:
    split(int id, double amount, user* owed, user* paidBy): id(id), amount(amount), owed(owed), paidBy(paidBy) {}
    int getId() const {
        return id;
    }
    double getAmount() const {
        return amount;
    }
    user* getOwed() const {
        return owed;
    }
    user* getPaidBy() const {
        return paidBy;
    }
    void setAmount(double amount) {
        this->amount = amount;
    }
    void setOwed(user* owed) {
        this->owed = owed;
    }
    void setPaidBy(user* paidBy) {
        this->paidBy = paidBy;
    }
};
   
class splitType{
    public:
    virtual void splitAmount(double amount, vector<user*> users, vector<split>& splits) = 0;
    virtual ~splitType() {}
};
class equalSplit : public splitType{
    void splitAmount(double amount, vector<user*> users, vector<split>& splits ) override {
        double splitAmount = amount / users.size();
        for (auto user : users) {
            splits.push_back(split(splits.size() + 1, splitAmount, user, nullptr));
            cout << user->getName() << " owes " << splitAmount << endl;
        }
    }
};
class percentageSplit : public splitType{
    vector<double> percentages;
    public:
    percentageSplit(vector<double> percentages): percentages(percentages) {}
    void splitAmount(double amount, vector<user*> users, vector<split>& splits) override {
        for (size_t i = 0; i < users.size(); i++) {
            double splitAmount = amount * (percentages[i] / 100);
            splits.push_back(split(splits.size() + 1, splitAmount, users[i], nullptr));     
            cout << users[i]->getName() << " owes " << splitAmount << endl;
        }
    }
};

class transaction{
public:
    string from;
    vector<user*> to;
    splitType* type;
    vector<split> splits;
    transaction(string from, vector<user*> to, splitType* type): from(from), to(to), type(type) {}
    void addTransaction(double amount) {
        type->splitAmount(amount, to, splits);
    }
};
int main() {
    user* user1 = new user(1, "Alice");
    user* user2 = new user(2, "Bob");
    user* user3 = new user(3, "Charlie");
    vector<user*> users = {user1, user2, user3};
    splitType* equal = new equalSplit();
    transaction t1("Alice", users, equal);
    t1.addTransaction(300);
    splitType* percentage = new percentageSplit({50, 30, 20});
    transaction t2("Bob", users, percentage);
    t2.addTransaction(200);
    delete user1;
    delete user2;
    delete user3;
    delete equal;
    delete percentage;
    return 0;
}