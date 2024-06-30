//!                                                  BANKING MANAGEMENT SYSTEM        
//*                                                 Project By Adithya Bharadwaj C      
#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;
#define minbalance 500
#define maxdeposit 900000
#define bankcode 21520

class account
{
    private:
    int accountnumber;      
    static int nextnumber;
    string fname;
    string lname;
    float balance;

    public:
    account (){}
    account(string fname,string lname,float balance)
    {
        nextnumber++;
        this->fname=fname;
        this->lname=lname;
        this->balance=balance;
        accountnumber=nextnumber;

    }
    int get_accountno()
    {
        return accountnumber;
    }
    double get_balance()
    {
        return balance;
    }
    string get_fname()
    {
        return fname;
    }
    string get_lname()
    {
        return lname;
    }
    int get_nextnumber()
    {
        return nextnumber;
    }

    void set_nextnumber(int x)
    {
        nextnumber=x;
    }

    void deposit(int amt)
    {
        balance=balance+amt;
    }

    void withdraw(int amt)
    {
        if(balance-amt<minbalance)
        {
            cout<<"INSUFFICIENT FUNDS"<<endl;
        }
        else
        {
            balance=balance-amt;
        }
    }

    friend ostream &operator <<(ostream &os,account &acc)
    {
        os<<"ACCOUNT NUMBER : "<<acc.accountnumber<<endl;
        os<<"FIRST NAME : "<<acc.fname<<endl;
        os<<"LAST NAME : "<<acc.lname<<endl;
        os<<"BALANCE : "<<acc.balance<<endl;
        return os;
    }
    friend ofstream &operator <<(ofstream &ofs,account &acc)
    {
        ofs<<acc.accountnumber<<endl;
        ofs<<acc.fname<<endl;
        ofs<<acc.lname<<endl;
        ofs<<acc.balance<<endl;
        return ofs;
    }

    friend ifstream &operator >>(ifstream &ifs,account &acc)
    {
        ifs>>acc.accountnumber;
        ifs>>acc.fname;
        ifs>>acc.lname;
        ifs>>acc.balance;
        return ifs;
    }
};
int account::nextnumber=bankcode;

class manage 
{
    private:
    unordered_map<int,account>map;

    public:

    manage()
    {
        account ac;

        ifstream ifs;
        ifs.open("Banking.txt");
        if(!ifs)
        {
            cout<<"Error is opening file"<<endl;
            return;
        }
        while(!ifs.eof())
        {
            ifs>>ac;
            map[ac.get_accountno()]=ac;
        }

        ac.set_nextnumber(ac.get_accountno());
        ifs.close();
    }

    account open_account(string fname,string lname,float balance)
    {
        account acc(fname,lname,balance);
        
        map[acc.get_accountno()]=acc;

        ofstream ofs;
        ofs.open("Banking.txt",ios::app);
        ofs<<acc;
        ofs.close();
        return acc;
    }
    account checkbalance(int accnum)
    {
        return map[accnum];
    }

    account deposit(int accnum,int amt)
    {
        map[accnum].deposit(amt);
        clearfile();
        update_file();
        return map[accnum];

    }
    account withdraw(int accnum,int amt)
    {
        map[accnum].withdraw(amt);
        clearfile();
        update_file();
        return map[accnum];
    }
    void update_file()
    {
        ofstream ofs;
        ofs.open("Banking.txt");
       for(auto it=map.begin();it!=map.end();it++)
       {
        ofs<<it->second;
       }
        ofs.close();
    }

    void clearfile()
    {
        ofstream ofs;
        ofs.open("Banking.txt",ios::trunc);
        ofs.close();
    }
    account close(int accnum)
    {
        map.erase(accnum);
        ofstream ofs;
        ofs.open("Banking.txt",ios::trunc);
        ofs.close();
        update_file();
    }

    account clear_all()
    {
        int c;
        cout<<"YOU ARE ABOUT TO CLEAR THE ENTIRE BANK DATA "<<endl<<"ARE YOU SURE YOU WANT TO DELETE"<<endl<<"IF YES TYPE 1"<<endl;
        cin>>c;
        if(c==1)
        {
        cout<<"HOPE YOU CHOSE THE WISE DESICION"<<endl;
        cout<<"BANK's WHOLE  DATA IS NOW DELETED"<<endl;
        map.clear();
        clearfile();
        update_file();
        }
    }
    
    void display()
    {
        for(auto it=map.begin();it!=map.end();it++)
        {
            cout<<it->second;
            cout<<endl<<endl;
        }
    }



    
};
int main()
{   
    int password =2152;
    int upass;
    account acc;
    manage bank;

    int accnt;
    float amount;
    string fname;
    string lname;
    float balance;
    int ch;

    while(1)
    {
        cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
        cout<<"                                         BANKING MANAGEMENT SYSTEM                                    "<<endl;
        cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
        cout<<"                                             1.OPEN ACCOUNT                                           "<<endl;
        cout<<"                                             2.CHECK BALANCE                                            "<<endl;
        cout<<"                                             3.DEPOSIT                                               "<<endl;
        cout<<"                                             4.WITHDRAWAL                                                  "<<endl;
        cout<<"                                             5.CLOSE ACCOUNT                                          "<<endl;
        cout<<"                                             6.DISPLAY ALL ACCOUNTS(ADMIN)                             "<<endl;
        cout<<"                                             7.CLEAN WHOLE DATA    (admin)                                                  "<<endl;
        cout<<"                                             PRESS ANY KEY TO QUIT (OTHER THAN 1-7)                                                    "<<endl;

        cout<<"ENTER YOUR OPTION"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:
            cout<<"Enter your FIRST_NAME"<<endl;
            cin>>fname;
            cout<<"Enter your LAST_NAME"<<endl;
            cin>>lname;
            cout<<"Enter your initial deposit(--minimum deposit 500--)"<<endl;
            cin>>balance;

            acc=bank.open_account(fname,lname,balance);
            cout<<"CONGRATULATION YOUR ACCOUNT HAS BEEN CREATED SUCCESSFULLY"<<endl;
            cout<<"THANK YOU FOR OPENING YOUR SAFE AND SECURE ACCOUNT IN OUR BANK "<<endl;
            cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
            cout<<                                                                 acc                                          ;
            cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
            cout<<endl<<endl;
            break;


            case 2:
            cout <<"Enter your account number for balance enquiry"<<endl;
            cin>>accnt;
            acc=bank.checkbalance(accnt);
            cout<<acc;
            break;

            case 3:
            cout<<"Enter amount to deposit"<<endl;
            cin>>amount;
            cout<<"Enter your account number"<<endl;
            cin>>accnt;
            acc=bank.deposit(accnt,amount);
            cout<<"Successfully depositted :RS"<<amount<<endl;
            cout<<acc;
            break;
            case 4:
            cout<<"Enter amount to withdraw"<<endl;
            cin>>amount;
            cout<<"Enter your account number"<<endl;
            cin>>accnt;
            acc=bank.withdraw(accnt,amount);
            cout<<"Successfully withdrawn :RS"<<amount<<endl;
            cout<<acc;
            break;
            
            case 5:
            cout<<"Enter your account number"<<endl;
            cin>>accnt;
            bank.close(accnt);
            break;
        
            case 6:
            cout<<"Enter password"<<endl;
            cin>>upass;
            if(upass==password)
            {
                bank.display();
            }
            else
            {
               cout<< "ACCESS DENIED"<<endl;
               return 0;
            }
            break;
            
            case 7:
            cout<<"Enter Password"<<endl;
            cin>>upass;
            if(upass==password)
            {
                bank.clear_all();
            }
            break;
            default:
            cout<<"THANK YOU FOR USING OUR BANK SERVICES"<<endl;
            exit(1);
            break;

    }
    }

}