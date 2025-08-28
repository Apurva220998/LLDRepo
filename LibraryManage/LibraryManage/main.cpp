#include <iostream>
using namespace std;
class IObserver{
public:
    virtual void update(const string& message)=0;
    virtual ~IObserver(){}
};
class user: public IObserver{
public:
    string username;
    vector<IObserver*> observers;
    
    user(string name):username(name){}
    string getName(){
        return username;
    }
    void update(const string& message)
    {
        std::cout<<"Text Message: "<<message<<endl;
    }
    void addObserver(IObserver* ob)
    {
        observers.push_back(ob);
    }
    void removeObserver(IObserver* ob)
    {
        observers.erase(remove(observers.begin(), observers.end(), ob), observers.end());

    }
    void notifyAll(string & msg)
    {
        for(auto os:observers)
        {
            os->update(msg);
        }
    }
    
};
class Book{
public:
    string author;
    string bName;
    int bookId;
    bool isAvail;
    string issuer;
    vector<IObserver*> wishList;
    Book(int bookId,string bName,string author,string issuer):bookId(bookId),bName(bName),author(author),issuer(issuer){isAvail=true;}
    bool isAvailable(){
        return isAvail;
    }
    void issued(){
        isAvail=false;
    }
    void free(){
        isAvail=true;
    }
    void setOwner(string name){
        issuer=name;
    }
    string getOwner(){
        return issuer;
    }
    string getAuthor(){
        return author;
    }
    string getBookName(){
        return bName;
    }
    void addToWishlist(user* u){
        wishList.push_back(u);
    }
    
    vector<IObserver*> getWishList(){
        return wishList;
    }
    void notifyWaitlist() {
            for(auto* obs : wishList) {
                obs->update("📚 The book '" + bName + "' is now available!");
            }
            wishList.clear();  // clear after notifying
        }
};
class library{
public:
    vector<Book*> books;
    void addBook(Book* b){
        books.push_back(b);
    }
    void removeBook(Book* b)
    {
        auto it=find(books.begin(),books.end(),b);
        books.erase(it);
    }
    vector<Book*> getBooks()
    {
        return books;
    }
};

/*class consoleDisplay:public IObserver{
public:
    void update(const string& message)
    {
        std::cout<<"CONSOLE: "<<message<<endl;
    }
    
};
class MessageDisplay:public IObserver{
public:
    void update(const string& message)
    {
        std::cout<<"Text Message: "<<message<<endl;
    }
    
};*/



class LibabryManager{
public:
    
    void issueBook(Book* b,user* u)
    {
        if(b->isAvailable())
        {
            b->issued();
            b->setOwner(u->getName());
            //string msg=u->getName()+" has issued "+b->getBookName()+" by Author "+b->getAuthor();
            std::cout<<u->getName()<<" has issued "<<b->getBookName()<<" by Author "<<b->getAuthor()<<endl;
        }
        else{
            b->addToWishlist(u);
        }
        
        
    }
    void returnBook(Book* b)
    {
        //string msg=b->getBookName()+" has been returned "+" Now available for issuing";
        //vector<IObserver*> wishList=b->getWishList();
        std::cout<<b->getBookName()<<" has been returned "<<" by Author "<<b->getAuthor()<<endl;
        b->notifyWaitlist();
        b->setOwner("");
        b->free();
        

    }
    
};

class searchBook{
public:
    virtual Book* search(string value,library* lb)=0;
    virtual ~searchBook(){}
};

class searchByAuthor: public searchBook{
public:
    Book* search(string value,library* lb){
        vector<Book*> books=lb->getBooks();
        for(auto bk: books)
        {
            if(value==bk->getAuthor())
            {
                return bk;
            }
        }
        return nullptr;
    }
    ~searchByAuthor(){}
};

class searchByName: public searchBook{
public:
    
    Book* search(string value,library* lb){
        vector<Book*> books=lb->getBooks();
        for(auto bk: books)
        {
            if(value==bk->getBookName())
            {
                return bk;
            }
        }
        return nullptr;
    }
    ~searchByName(){}
};

int main(int argc, const char * argv[]) {
    user* u1=new user("BUBU");
    user* u2=new user("DUDU");
    
    Book* b1=new Book(1,"naugthy book","some desparate guy","");
    Book* b2=new Book(2,"Romance novel","Hopeless romantic","");
    
    library* lb=new library();
    lb->addBook(b1);
    lb->addBook(b2);
    
    LibabryManager* lbm=new LibabryManager();
    
    
    searchBook* sbn=new searchByName();
    Book* found=sbn->search("naugthy book",lb);
    
    if(found)
    {
        lbm->issueBook(found,u1);
    }
    else std::cout<<"Book not found\n";
    
    lbm->issueBook(b1,u2);
    
    if(found)lbm->returnBook(found);

    
    
    return 0;
}
