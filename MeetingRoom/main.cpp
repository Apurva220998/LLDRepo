
#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum roomType { SMALL, MED, LARGE};

class meetingOrgInfo
{
public:
string meetingTitle;
int start;
int end;
vector<string> mailIds;
roomType type;
    
    meetingOrgInfo(string title,int start,int end,vector<string> mailIds,roomType type):meetingTitle(title),start(start),end(end),mailIds(mailIds),type(type){}
    
    string getTitle(){
        return meetingTitle;
    }
    vector<string> getMailIds(){
        return mailIds;
    }
    roomType getRoomType(){
        return type;
    }
};



class Calendar{
public:
    vector<int> cal;

void add(int start){
    cal.push_back(start);
}
    

};

class meetingRoom{
    
public:
int meetingId;
string loc;
roomType type;
Calendar cal;
    
    meetingRoom(int meetingId,string floor,roomType type):meetingId(meetingId),loc(floor),type(type){}

    roomType getType(){
        return type;
    }
    vector<int> getCalendar(){
        return cal.cal;
    }
};

class notification{
public:
virtual void send(meetingOrgInfo* meet)=0;
    virtual ~notification(){}
};
class email: public notification{
public:

    void send(meetingOrgInfo* meet){
        for(auto people: meet->getMailIds()){
            std::cout<<"email Sent to "<<people<<endl;
        }
    }
};

class meetingMgr{
public:
vector<meetingRoom*> rooms;


//methods
void addRoom(meetingRoom* rm){
    rooms.push_back(rm);
}


vector<meetingRoom*> findRoom(meetingOrgInfo* meet){
    vector<meetingRoom*> result;
    for(auto rm: rooms){
        if(rm->getType()==meet->type){
            auto tm=rm->getCalendar();
            auto it=find(tm.begin(),tm.end(),meet->start);
                if(it!=tm.end())
                std::cout<<"OOPs already booked"<<endl;
            else
                result.push_back(rm);
        }
    }
        return result;
}

void bookRoom(meetingRoom* rm,meetingOrgInfo* meet,notification* ntf){
    rm->cal.add(meet->start);
    std::cout<<"Meeting Room Booked for "<<meet->getTitle()<<endl;
    ntf->send(meet);
    
}
//void displaySchedule(){}

};
enum class notify{email};
class notificationFactory{
public:
    notification* getInstance(notify nt){
        switch(nt){
            case notify::email : return new email();
                break;
        }
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    meetingOrgInfo* meet=new meetingOrgInfo("TownHall", 13, 14,{"apu.com","bubu.com","dudu.com"}, roomType::SMALL);
    
    meetingRoom* mr1 = new meetingRoom(1,"12thFloor",roomType::SMALL);
    meetingRoom* mr2 = new meetingRoom(2,"11thFloor",roomType::LARGE);
    meetingRoom* mr3 = new meetingRoom(3,"13thFloor",roomType::MED);
    
    meetingMgr mgr;
    
    mgr.addRoom(mr1);
    mgr.addRoom(mr2);
    mgr.addRoom(mr3);
    
    auto rooms=mgr.findRoom(meet);
   
    mgr.bookRoom(rooms[0],meet,new email());
   
    
    return 0;
    
}
