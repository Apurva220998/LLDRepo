

#include <iostream>
#include <vector>
using namespace std;
enum RoomType {SINGLE, DOUBLE, SUITE};

string roomTypeToString(RoomType rt) {
    switch(rt) {
        case SINGLE: return "Single";
        case DOUBLE: return "Double";
        case SUITE:  return "Suite";
        default:     return "Unknown";
    }
}
class IRoom{
public:
    virtual string getDescription()=0;
    virtual double getPrice()=0;
    virtual bool isAvailable()=0;
    virtual void bookRoom()=0;
    virtual void freeRoom()=0;
    virtual ~IRoom(){}
};

class room: public IRoom{
public:
    int roomId;
    string type;
    bool isAvail;
    double price;
    vector<int> time;
    room(int id,RoomType ty,double price):roomId(id),type(roomTypeToString(ty)),price(price){isAvail=true;}
    
    string getDescription(){
        return type;
    }
   
    bool isAvailable(){
        return isAvail;
    }
    
    void bookRoom(){
        isAvail=false;
    }
    void freeRoom(){
        isAvail=true;
    }
    double getPrice()
    {
        return price;
    }
    string getType()
    {
        return type;
    }
};
class RoomDecorator:public IRoom{
protected:
    IRoom* wrappedRoom;
    
public:
    RoomDecorator(IRoom* r):wrappedRoom(r){}
    virtual ~RoomDecorator() { delete wrappedRoom; }
    bool isAvailable(){ return wrappedRoom->isAvailable();};
    void bookRoom(){wrappedRoom->bookRoom();}
    void freeRoom(){wrappedRoom->freeRoom();}
    
};
class jacuzzi:public RoomDecorator{
public:
    jacuzzi(IRoom* r):RoomDecorator(r){}
    string getDescription(){
        return (wrappedRoom->getDescription()+" + BathTub");
    }
    double getPrice(){
        return wrappedRoom->getPrice()+1000;
    }
};

class seaView:public RoomDecorator{
public:
    seaView(IRoom* r):RoomDecorator(r){}
    string getDescription(){
        return (wrappedRoom->getDescription()+"+ seaView");
    }
    double getPrice(){
        return wrappedRoom->getPrice()+2000;
    }
};

class singleRoom:public room{
public:
    singleRoom(int id,double price):room(id,SINGLE,price){}
};
class doubleRoom:public room{
public:
    doubleRoom(int id,double price):room(id,DOUBLE,price){}
};
class suiteRoom:public room{
public:
    suiteRoom(int id,double price):room(id,SUITE,price){}
};
class roomFactory{
public:
    static room* createRoom(RoomType type,int id,double price){
        switch(type){
            case SINGLE:
                return new singleRoom(id,price);
            case DOUBLE:
                return new doubleRoom(id,price);
            case SUITE:
                return new suiteRoom(id,price);
            default:
                throw std::invalid_argument("Room type is wrong");
        }
        
    }
};
class hotel{
    private:
    vector<room*> rooms;
    
    public:
    int hotelId;
    string hName;
    string location;
    hotel(int id,string name,string loc):hotelId(id),hName(name),location(loc){}
    void addRoom(room* r){
        rooms.push_back(r);
    }
    vector<room*> getAvailableRooms()
    {
        vector<room*> result;
        for(auto rm: rooms)
        {
            if(rm->isAvailable())
            {
                result.push_back(rm);
            }
        }
        return result;
    }
    string getName(){return hName;}
    string getLocation(){return location;}
    
    
};
class hotelManager{
public:
    vector<hotel*> hotels;
    void addHotel(hotel* h){hotels.push_back(h);}
    
    vector<hotel*> searchByLocation(string loc)
    {
         vector<hotel*> res;
         for(auto h:hotels)
         {
             if(h->getLocation()==loc)
             {
                 res.push_back(h);
             }
         }
        return res;
    }
    
    
};
class paymentGateway{
public:
    double amount;
    string mode;
    paymentGateway(double price,string mode):amount(price),mode(mode){}
    virtual bool pay(double price)=0;
    double getPrice()
    {
        return amount;
    }
    
};
class UPI:public paymentGateway{
    double price;
public:
    UPI(double price):paymentGateway(price,"UPI"){}
    bool pay(double price)
    {
        std::cout<<"Paid the Amount By UPI\n";
        return true;
    }
    double getPrice()
    {
        return price;
    }
};
class Card:public paymentGateway{
public:
    double price;
    Card(double price):paymentGateway(price,"Card"){}
    bool pay(double price)
    {
        std::cout<<"Paid the Amount By Card\n";
        return true;
    }
    double getPrice()
    {
        return price;
    }
};

class Booking{
public:
    string username;
    hotel* h;
    IRoom* rm;
    
    Booking(string username,hotel* h,IRoom* rm): username(username),h(h),rm(rm){
        rm->bookRoom();
    }
    void getBookingDetails(){
        std::cout<<username<<" has booked Hotel "<<h->getName()<<" with "<<rm->getDescription()<<" for price "<<rm->getPrice()<<endl;
    }
    void cancelBooking(){
        std::cout<<username<<" has cancelled "<<h->getName()<<"with "<<rm->getDescription()<<"for price"<<rm->getPrice()<<endl;
    }
    
    
};



class user{
public:
    hotelManager hm;
    string userName;
    user(string username):userName(username){}
    void hotelBooking(hotel* h,IRoom* rm,paymentGateway* pg)
    {
        if(rm->isAvailable()){
            Booking* bk=new Booking(userName,h,rm);
            if(pg->pay(pg->getPrice())){
                bk->getBookingDetails();
            }
        }
    }
    void cancelBooking(room* rm)
    {
        rm->freeRoom();
    }
    
    
};
int main(int argc, const char * argv[]) {
    
    hotel* h=new hotel(1,"Taj Mahal Palace","HYD");
    h->addRoom(roomFactory::createRoom(SUITE,101,5000));
    h->addRoom(roomFactory::createRoom(SINGLE,102,2000));
    h->addRoom(roomFactory::createRoom(DOUBLE,103,3000));
    
    hotel* h1=new hotel(1,"Lalit","GOA");
    h1->addRoom(roomFactory::createRoom(SUITE,201,5000));
    h1->addRoom(roomFactory::createRoom(SINGLE,202,2000));
    h1->addRoom(roomFactory::createRoom(DOUBLE,203,3000));
    
    hotelManager hm;
    hm.addHotel(h1);
    hm.addHotel(h);
    
    
    
    user* u=new user("bubu");
    vector<hotel*> res=hm.searchByLocation("GOA");
    if(res[0])
    {
        vector<room*> rooms= res[0]->getAvailableRooms();
        IRoom* decorate=new jacuzzi(new seaView(rooms[0]));
        u->hotelBooking(res[0],decorate,new UPI(decorate->getPrice()));
        /*cout << "Final Room Description: " << decorate->getDescription() << endl;
        cout << "Final Room Price: " << decorate->getPrice() << endl;*/
    }
    return 0;
}
