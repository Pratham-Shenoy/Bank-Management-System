/*#include<bits/stdc++.h>
using namespace std;

class Database
{
    public:
    Database()
    {
        loadUsersFromFile();
    }
    void loadUsersFromFile()
    {
        ifstream read("users.txt");
        while(read>>user>>Password>>balance)
        {
            users[user].first=Password;
            users[user].second=balance;
        }
        read.close();
    }
    void saveUserToFile(string username, string password)
    {
        user=username;
        Password=password;
        users[user].first=password;
        users[user].second=balance;
        ofstream sendDataToFile("users.txt");
        for(auto user : users)
        sendDataToFile<<user.first<<" "<<user.second.first<<" "<<user.second.second<<"\n";
         sendDataToFile.close();
    }
    bool userExists(string username)
    {
        if(users.find(username)==users.end())
        return false;
        return true;
    }
    void withdrawal(double transactionAmt)
    {
        if(balance-transactionAmt>0 && transactionAmt>0)
        {
            balance-=transactionAmt;
            saveUserToFile(user,Password);
        }
    }
    void deposit(double transactionAmt)
    {
        if(transactionAmt>0)
        {
            balance+=transactionAmt;
            saveUserToFile(user,Password);
        }
    }
    void accountSummary()
    {
        cout<<"username: "<<user;
        cout<<"balance: "<<balance;
    }
    void deleteAccount(string username)
    {
        ifstream read2("users.txt");
        ofstream sendDataToFile("temp.txt");
        while(read2>>user>>Password>>balance)
        {
            if(user!=username)
            sendDataToFile<<user<<" "<<Password<<" "<<balance<<"\n";
        }
        rename("temp.txt","users.txt");
    }
    private:
    unordered_map<string,pair<string,double>> users;
    string user,Password;
    double balance=0.0;
};

int main()
{
    Database database;
    int choice;
    double transactionAmt=0.0;
    string username,password;
    while(true)
    {
        cout<<"Enter: \n 1 for create account \n 2 for login \n 3 for deleting account \n 4 for exiting \n ";
        cin>>choice;
        if(choice==4)
        break;
        if(choice==1)
        {
            cin.ignore();
            cout<<"Enter your username: ";
            getline(cin,username);
            cout<<"Enter your password: ";
            cin>>password;
            if(!database.userExists(username))
            {
                cout<<"*proceed*\n";
                database.saveUserToFile(username,password);
                username=" ";
                password=" ";
            }
            else
            cout<<"Sorry! Account already exists :(\n";
        }
        if(choice==2)
        {
            cin.ignore();
            cout<<"Enter your username: ";
            getline(cin,username);
            cout<<"Enter your password:";
            cin>>password;
            if(database.userExists(username)){
            while(true)
                {
                    cout<<"Successfully logged in!\n Enter:\n1 for withdrawal\n2 for deposit\n3 for account summary\n4 for exit\n";
                    cin>>choice;
                    if(choice==1)
                    {
                        cout<<"Enter the withdrawal amount: ";
                        cin>>transactionAmt;
                        database.withdrawal(transactionAmt);
                        transactionAmt=0;
                    }
                    if(choice==2)
                    {
                        cout<<"Enter the deposit amount: ";
                        cin>>transactionAmt;
                        database.deposit(transactionAmt);
                        transactionAmt=0;
                    }
                    if(choice==3)
                    {
                        database.accountSummary();
                    }
                    if(choice==4)
                    break;
                }}
        }
        if(choice==3)
        {
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
            if(database.userExists(username))
            database.deleteAccount(username);
        }
    }
}         */

#include<bits/stdc++.h>
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
    {
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
        if(user.first==username && user.second.first==password)
        count++;
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
        cin.ignore();
        if(choice1==1)
        {
            cout<<"Enter your username: ";
            getline(cin,username);
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
            getline(cin,username);
            cout<<"Enter your password: ";
            cin>>password;
            if(D.userExists(username,password))
            {
            while(true)
            {
                user.Dataforoperations(username, password, balance);
                balance=D.databaseaccessforbalance(username);
                cout<<"Enter 1 for withdrawing amount\n 2 for depositing amount\n3 for viewing account summary\n4 for exiting\n";
                cin>>choice2;
                cin.ignore();
                if(choice2==1)
                {
                    user.Dataforoperations(username,password,balance);
                    cout<<"Enter transaction amount: ";
                    cin>>transactionAmt;
                    user.withdraw(transactionAmt);
                }   
                if(choice2==2)
                {
                    user.Dataforoperations(username,password,balance);
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
        }
        if(choice1==3)
        {
            cout<<"Enter your username: ";
            getline(cin,username);
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