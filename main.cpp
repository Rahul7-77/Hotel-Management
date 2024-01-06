#include<bits/stdc++.h>
using namespace std;

map<pair<string,string>,vector<int>>m;

class hotel{
    private:
    vector<bool>totalrooms=vector<bool>(101,false);
    public:
    void roomAllocated(int n){
        this->totalrooms[n]=true;
    }
    int roomsAvailable(){
        int cnt=0;
        for(int i=1;i<=101;i++){
            if(totalrooms[i]){
                cnt++;
            }
        }
        return 100-cnt;
    }
    int firstVacant(){
        for(int i=1;i<=101;i++){
            if(!totalrooms[i]){
                return i;
            }
        }
        return -1;
    }
};

class user{
    private:
    string name;
    int age;
    vector<int>room_num;
    string phone_num;
    string password;
    string town;
    string state;
    string country;
    vector<string>complaints;
    public:
    // user(string n,int a,string ph_num,string p,string t,string s,string c){
    //     this->name=n;
    //     this->age=a;
    //     this->phone_num=ph_num;
    //     this->password=p;
    //     this->town=t;
    //     this->state=s;
    //     this->country=c;
    // }
	void setname(string n){
		this->name=n;
	}
	void setage(int ag){
		this->age=ag;
	}
	void setphone(string ph_num){
		this->phone_num=ph_num;
	}
	void setpassword(string p){
		this->password=p;
	}
	void settown(string t){
		this->town=t;
	}
	void setstate(string s){
		this->state=s;
	}
	void setcountry(string cou){
		this->country=cou;
	}
    void registerComplaint(string s){
        this->complaints.push_back(s);
    }
    void getall(){
        cout<< "Name of User : "<<this->name<<'\n';
        cout<< "Age of User : "<<this->age<<'\n';
        cout<<"Phone Number of User : "<<this->phone_num<<'\n';
        cout<< "Total Rooms of User : "<<this->room_num.size()<<'\n';
        cout<< "Town of User : "<<this->town<<'\n';
        cout<< "State of User : "<<this->state<<'\n';
        cout<< "Country of User : "<<this->country<<'\n';
        cout<< "Total complaints of User : "<<this->complaints.size()<<'\n';
	}
    int getAge(){
        return this->age;
    }
	int roomssize(){
		return this->room_num.size();
	}
    int getRoom(){
        return this->room_num.back();
    }
    string getName(){
        return this->name;
    }
    string getPassword(){
        return this->password;
    }
    string getTown(){
        return this->town;
    }
    string getState(){
        return this->state;
    }
    string getCountry(){
        return this->country;
    }
    void addNewRoom(int r_num){
        this->room_num.push_back(r_num);
    }
};

map<int,user>mp;

class userManager{
    private:
    public:
    void addUser(user &nuser){
        string name=nuser.getName();
        string password=nuser.getPassword();
		int size=nuser.roomssize();
        if(size==0){
			//vector<int>help;
			m[{name,password}].push_back(0);
		}
		else{
			int r_num=nuser.getRoom();
			m[{name,password}].push_back(r_num);
		}
    }
	bool islogin(string name,string password){
		if(m.find({name,password})==m.end()){
			return false;
		}
		return true;
	}
	int getRoom(string name,string password){
		return m[{name,password}][1];
	}
    void getUserRoomDetails(string name,string password){
        if(m.find({name,password})==m.end()){
            cout<<"Sorry! You haven't booked any rooms"<<'\n';
        }
        else{
            for(auto r:m[{name,password}]){
                cout<<"Room Allotted for you is "<<r<<'\n';
            }
        }
    }
};

class manager{
    string name;
    string password;
    public:
    void getRoomDetails(int r){
        user stay=mp[r];
        stay.getall();
    }
	user getuserinroom(int r){
		return mp[r];
	}
    void bookRoom(user &nuser,hotel &h,userManager &manager){
        int avl_rooms=h.roomsAvailable();
        if(avl_rooms==0){
            cout<<"Sorry! We are full"<<'\n';
        }
        else{
            int r_num=h.firstVacant();
            h.roomAllocated(r_num);
            mp[r_num]=nuser;
            nuser.addNewRoom(r_num);
            manager.addUser(nuser);
        }
    }
};

int main(){
	userManager um;
	manager manage;
	hotel h;
    while(true){
		cout<< "Press Below keys for smooth navigation : "<< '\n';
		cout<< "Press 1 for Admin Login" << '\n';
		cout<< "Press 2 for User login and Booking rooms" << '\n';
		cout<< "Press 3 for Exit " << '\n';
		int input;
		cin>>input;
		if(input==1){
			cout<< "Enter the password of Admin !"<< '\n';
			string password;
			cin>>password;
			if(password=="iamadmin"){
				cout<< "Hello Manager! Happy to have you here" << '\n';
				cout<< "Which Room you want to check? "<< '\n';
				int r_number;
				cin>>r_number;
				manage.getRoomDetails(r_number);
			}
			else{
				cout<< "Wrong password... Try again" << '\n';
				continue;
			}
		}
		else if(input==2){
			// user case;
			cout<< "Hello User! "<< '\n';
			cout<< " Please note you can book rooms only after login! "<< '\n';
			while(true){
				cout<< "Press 1 for login"<< '\n';
				cout<< "Press 2 to register"<< '\n';
				int userinput;
				cin>>userinput;
				if(userinput==1){
					string userloginName;
					cout<< "Enter your name : "<< '\n';
					cin>>userloginName;
					string userloginPassword;
					cout<< "Enter your Password : "<< '\n';
					cin>>userloginPassword;
					if(um.islogin(userloginName,userloginPassword)==false){
						cout<< " You are not Registered. Please Register !" << '\n';
						continue;
					}
					else{
						cout<< "Hello "<<userloginName<< '\n';
						//um.getUserRoomDetails(userloginName,userloginPassword);
						int userroom=um.getRoom(userloginName,userloginPassword);
						user two=manage.getuserinroom(userroom);
						bool flag=true;
						while(true){
							cout<< "Press 1 to book rooms"<< '\n';
							cout<< "Press 2 to exit" << '\n';
							int roomcheck;
							cin>>roomcheck;
							if(roomcheck==1){
								if(h.firstVacant()==-1){
									cout<< "Sorry we are full!"<< '\n';
									break;
								}
								else{
									int r_number=h.firstVacant();
									cout<< " Room allocated to you is : "<<r_number<< '\n';
									manage.bookRoom(two,h,um);
									um.addUser(two);
								}
							}
							else{
								flag=false;
								break;
							}
						}
						if(flag==false){
							break;
						}
					}
				}
				else if(userinput==2){
					// register here
					cout<< "Welcome to register portal!" << '\n';
					cout<< "Enter your Name" << '\n';
					string name;
					cin>>name;
					cout<< "Enter your Age" << '\n';
					int age;
					cin>>age;
					cout<< "Enter your Phone NUmber" << '\n';
					string phone_num;
					cin>>phone_num;
					cout<< "Enter your new password u want to keep for loggin in" << '\n';
					string password;
					cin>>password;
					cout<< "Enter your Town" << '\n';
					string town;
					cin>>town;
					cout<< "Enter your State" << '\n';
					string state;
					cin>>state;
					cout<< "Enter your Country" << '\n';
					string country;
					cin>>country;
					user one;
					one.setname(name);
					one.setage(age);
					one.setphone(phone_num);
					one.setpassword(password);
					one.settown(town);
					one.setstate(state);
					one.setcountry(country);
					um.addUser(one);
					bool flag=true;
					while(true){
						cout<< "Press 1 to book rooms"<< '\n';
						cout<< "Press 2 to exit "<< '\n';
						int roomcheck;
						cin>>roomcheck;
						if(roomcheck==1){
							if(h.firstVacant()==-1){
								cout<< "Sorry we are full!"<< '\n';
								break;
							}
							else{
								int r_number=h.firstVacant();
								cout<< " Room allocated to you is : "<<r_number<< '\n';
								manage.bookRoom(one,h,um);
								um.addUser(one);
							}
						}
						else{
							flag=false;
							break;
						}
					}
					if(flag==false){
						break;
					}
				}
				else{
					cout<< "Invalid key.... Exiting for Security Reasons !"<< '\n';
					break;
				}
			}
		}
		else{
			break;
		}
	}
}
