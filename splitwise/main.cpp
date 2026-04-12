// adding the code for the main function to test the Splitwise class
//please add this too, I created a branch and merged
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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
    virtual void splitAmount(double amount,user* from, vector<user*> users, vector<split>& splits) = 0;
    virtual ~splitType() {}
};
class equalSplit : public splitType{
    void splitAmount(double amount, user* from, vector<user*> users, vector<split>& splits ) override {
        double splitAmount = amount / users.size();
        for (auto user : users) {
            if (user != from) {
                splits.push_back(split(splits.size() + 1, splitAmount, user, from));
                cout << user->getName() << " owes " << splitAmount << endl;
            }
        }
    }
};
class percentageSplit : public splitType{
    vector<double> percentages;
    public:
    percentageSplit(vector<double> percentages): percentages(percentages) {}
    void splitAmount(double amount, user* from, vector<user*> users, vector<split>& splits) override {
        for (size_t i = 0; i < users.size(); i++) {
            double splitAmount = amount * (percentages[i] / 100);
            splits.push_back(split(splits.size() + 1, splitAmount, users[i], from));     
            cout << users[i]->getName() << " owes " << splitAmount << endl;
        }
    }
};

class transaction{
public:
    user* from;
    vector<user*> to;
    splitType* type;
    vector<split> splits;
    double amount;
    transaction(user* from, double amount, vector<user*> to, splitType* type): from(from), amount(amount), to(to), type(type) {}
    void addTransaction() {
        type->splitAmount(amount,from, to, splits);
    }
    vector<split> getSplits() const {
        return splits;
    }
};

class balance{
    unordered_map<user*, unordered_map<user*, double>> balances;
public:
    void updateBalance(split split) {
        user* owed = split.getOwed();
        user* paidBy = split.getPaidBy();
        double amount = split.getAmount();
        balances[owed][paidBy] += amount;
        balances[paidBy][owed] -= amount;
    }
    void showBalance(user* user) {
        cout << "Balance for " << user->getName() << ":" << endl;
        for (const auto& entry : balances[user]) {
            cout << "  Owes " << entry.first->getName() << ": " << entry.second << endl;
        }
};

class splitwise{
    unordered_map<user*, vector<transaction>> transactions;
    void createTransaction(user* from, vector<user*> to, splitType* type, double amount) {
        transaction t(from,amount,to, type);
        t.addTransaction();
        transactions[from].push_back(t);
    }
  


};
int main() {
    user* user1 = new user(1, "Alice");
    user* user2 = new user(2, "Bob");
    user* user3 = new user(3, "Charlie");
    vector<user*> users = {user1, user2, user3};
    splitType* equal = new equalSplit();
    transaction t1(user1,300, users, equal);
    t1.addTransaction();
    splitType* percentage = new percentageSplit({50, 30, 20});
    transaction t2(user1,200, users, percentage);
    t2.addTransaction();
    delete user1;
    delete user2;
    delete user3;
    delete equal;
    delete percentage;
    return 0;
}