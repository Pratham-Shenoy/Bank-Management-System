#include<bits/stdc++.h>
#include<filesystem>
using namespace std;

class database
{
    public: 

    database()
    {
        loadusersfromfile();
    }
    double databaseaccessforbalance(string username)
    {
        for(auto user : users)
        {
            if(user.first==username)
            {
                return user.second.second;
            }
        }
        return 0.0;
    }
    void saveuserstofile()
    {
        ofstream send("user.txt");
        for(pair<string,pair<string,double>> user : users)
        {
            send<<user.first<<" "<<user.second.first <<" "<<user.second.second<<"\n";
        }
        send.close();
        
    }
    void loadusersfromfile()
    {cout << filesystem::absolute("user.txt") << '\n';
        ifstream read("user.txt");
        string username,password;
        double balance;
        string line;
        while(getline(read,line))
        {
            istringstream iss(line);
            iss>>username>>password>>balance;
            users[username].first=password;
            users[username].second=balance;
        }
        read.close();
    }
    void deleteuser(string username)
    {
        users.erase(username);
        saveuserstofile();
    }
    void updatedatabasewithnewuser(string username,string password, double balance)
    {
        users[username].first=password;
        users[username].second=balance;
    }
    bool userExists(string username,string password)
    {
        int count=0;
        for(auto user : users)
        {
            if(user.first==username && user.second.first==password)
            count++;
        }
        if(count==1)
        return true;
        return false;
    }
    void accountSummary(string usern,string password)
    {
        cout<<"username: "<<usern<<"\n";
        cout<<"balance: "<<users[usern].second<<"\n";
    }
    private:
    unordered_map<string,pair<string,double>> users;
};

class bankaccount
{
    private:
    string username,password;
    double balance;
    database &D;

    public:
    bankaccount(database &db) : D(db)
    {
    }
    void Dataforoperations(string &user,string &pass,double &bal)
    {
        username=user;
        password=pass;
        balance=bal;
    }
    void deposit(double transactionamt)
    {
        if(transactionamt>0)
        {
            balance+=transactionamt;
            D.updatedatabasewithnewuser(username,password,balance);
            D.saveuserstofile();
        }
    }
    void withdraw(double transactionamt)
    {
        if(transactionamt>0 && balance-transactionamt>0)
        {
            balance-=transactionamt;
            D.updatedatabasewithnewuser(username,password,balance);
            D.saveuserstofile();
        }
    }
};

int main()
{
    database D;
    bankaccount user(D);
    string username,password;
    double balance=0.0;
    double transactionAmt;
    int choice1,choice2;
    while(true)
    {
        cout<<"Enter 1 for creating an account\n2 for logging in\n3 for deleting account\n4 for exiting\n";
        cin>>choice1;
        if(choice1==1)
        {
            cout<<"Enter your username: ";
            cin>>username;
            cout<<"Enter your password: ";
            cin>>password;
            if(D.userExists(username,password))
            cout<<"Sorry user exists already!";
            else
            {
                user.Dataforoperations(username,password,balance);
                D.updatedatabasewithnewuser(username,password,balance);
                D.saveuserstofile();
            }
        }
        if(choice1==2)
        {                                             //D.userExists(username,password)
            cout<<"Enter your username: ";
            cin>>username;
            cout<<"Enter your password: ";
            cin>>password;
            if(D.userExists(username,password))
            {
            while(true)
            {
                balance=D.databaseaccessforbalance(username);
                user.Dataforoperations(username, password, balance);
                cout<<"Enter 1 for withdrawing amount\n 2 for depositing amount\n3 for viewing account summary\n4 for exiting\n";
                cin>>choice2;
                if(choice2==1)
                {
                    cout<<"Enter transaction amount: ";
                    cin>>transactionAmt;
                    user.withdraw(transactionAmt);
                }   
                if(choice2==2)
                {
                    cout<<"Enter transaction amount: ";
                    cin>>transactionAmt;
                    user.deposit(transactionAmt);
                }              
                if(choice2==3)
                {
                    D.accountSummary(username,password);
                }
                if(choice2==4)
                break;
            }
            }
            else
            cout << "Account doesn't exist";
        }
        if(choice1==3)
        {
            cout<<"Enter your username: ";
            cin>>username;
            cout<<"Enter your password: ";
            cin>>password;
            if(D.userExists(username,password))
            {
                D.deleteuser(username);
            }
        }
        if(choice1==4)
        break;
    }
}
