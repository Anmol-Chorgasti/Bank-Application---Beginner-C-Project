// Bank Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
// The core logic is that every time a change happens, the file needs to be rewritten entirely. 
//Approach 1, read everything into a map at the start of the program, then write the map into the file at the end of the program
//Approach 2, work with the file directly, but this will increase number of rewrites and lead to slower performance

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#define MIN_BALANCE 50

//Account class to store account ID, details of user, and initial balance
class Account
{
public:
    long accountID;
    std::string firstName;
    std::string lastName;
    double Balance;
    std::string password;
   

    Account(std::string firstName = "", std::string lastName = "", std::string password = "000", double Balance = 0, long accID = 0):firstName(firstName), lastName(lastName), password(password), Balance(Balance), accountID(accID)
    {
        this->Balance += MIN_BALANCE;
    }

    long getAccountID()
    {
        return accountID;
    }
    
    //overloading << operator to write in Account details to file
    friend std::ofstream& operator<<(std::ofstream& of, Account& acc);
    //overloading operator to read in Account details from file
    friend std::ifstream& operator>>(std::ifstream& rf, Account& acc);

    //overloading << operator to display Account when it is accessed
    friend std::ostream& operator<<(std::ostream& o, Account& acc);
};



class Bank
{
    static long AccountID;
    std::map<long, Account> accounts;

public:
    Bank()
    {
        //creates a file for the first run, and then just stores the data as it is in the subsequent runs
        //this ofstream line is only useful the first time the program is run!
        std::ofstream of("Bank Accounts.txt", std::ios::app);
        std::ifstream rf("Bank Accounts.txt");
        if (!rf)
            std::cout << "File not found" << std::endl;

        Account acc;
        while (rf >> acc)
        {
            //std::cout << acc;
            accounts.insert(std::pair<long, Account>(acc.getAccountID(), acc));
        }
        of.close();
        rf.close();
    }
    void display(long ID); //done
    void openAccount(); //done 
    bool login(long userID); //done
    void lastAccountID(); //done
    void deleteAccount(long userID); //done
    void withdraw(long userID); //done
    void deposit(long userID); //done
    void enquireBalance(long userID); //done
    void changePassword(long userID); //done
    const char* bankExists(long userID);
    ~Bank()
    {
        std::ofstream temp("Bank Accounts.txt", std::ios::trunc);
        if (!temp)
            std::cout << "File not found" << std::endl;

        std::map<long, Account>::iterator it;
        for (it = accounts.begin(); it != accounts.end(); it++)
        {
            temp << it->second;
        }

        temp.close();
    }

};

long Bank::AccountID = 0;



int main()
{
    //opening the file using ifstream object
    Bank objBank;
    objBank.lastAccountID();
    //Bank Logo and welcoming the user
    std::cout << "**********************************************" << std::endl;
    std::cout << "            WELCOME TO THE TYCS BANK          " << std::endl;
    std::cout << "**********************************************" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Please select what you would like to do:" << std::endl;
    std::cout << "1) Enter 1 to open a new account" << std::endl;
    std::cout << "2) Enter 2 to login to an existing account" << std::endl;
    std::cout << "3) Enter 3 to exit app" << std::endl;
   
    int userChoice = 0;
    std::cout << std::endl << "Enter your choice: ";
    std::cin >> userChoice;
    std::cout << std::endl;

    while (userChoice != 3)
    {
        switch(userChoice)
        {
        case 1:
            objBank.openAccount();
            break;
        //The main case is here - logic flow is that user tries to login, on successful login he then decides what he wants to do with his 
        case 2:
        {
            long userID = 0;
            std::string userPassword = "";
           
            std::cout << std::endl << std::endl;

            char tryAgain = 'n';
            do
            {
                std::cout << "Please enter the Account ID: ";
                std::cin >> userID;
                if (objBank.login(userID))
                {
                    std::cout << "**********************************************" << std::endl;
                    std::cout << "            WELCOME TO YOUR ACCOUNT           " << std::endl;
                    std::cout << "**********************************************" << std::endl;
                    std::cout << std::endl << std::endl;
                    int accChoice = 0;
                    std::cout << "Please select what you would like to do:" << std::endl;
                    std::cout << "1) Enter 1 to see all account details" << std::endl;
                    std::cout << "2) Enter 2 to enquire about current balance" << std::endl;
                    std::cout << "3) Enter 3 to withdraw money" << std::endl;
                    std::cout << "4) Enter 4 to deposit money" << std::endl;
                    std::cout << "5) Enter 5 to change password" << std::endl;
                    std::cout << "6) Enter 6 to delete your account" << std::endl;
                    std::cout << "7) Enter 7 to quit the app" << std::endl;
                    std::cout << std::endl << "Enter your choice: ";
                    std::cin >> accChoice;
                    std::cout << std::endl;

                    if (accChoice == 7)
                        break;
                    do
                    {
                        switch (accChoice)
                        {
                        case 1:                        
                            objBank.display(userID);
                            break;
                        case 2:
                            objBank.enquireBalance(userID);
                            break;
                        case 3:
                            objBank.withdraw(userID);
                            break;
                        case 4:
                            objBank.deposit(userID);
                            break;
                        case 5:
                            objBank.changePassword(userID);
                            break;
                        case 6:
                            objBank.deleteAccount(userID);
                            break;
                        case 7:
                            break;
                        default:
                            break;
                        }
                        std::cout << std::endl << "What would you like to do next? (1,2,3,4,5,6,7)? ";
                        std::cin >> accChoice;
                        std::cout << std::endl << std::endl;
                    } while (accChoice != 7); //or will not work here as if accChoice is 6, then accChoice != 7 will evaluate to True 
                    break;
                }
                else
                {
                    try
                    {
                        std::cout << "You either entered the wrong Account ID or Password" << std::endl;
                        objBank.bankExists(userID);
                        std::cout << "Enter y to try logging in again, n to stop trying, c to change password" << std::endl;
                        std::cin >> tryAgain;
                        if (tryAgain == 'c')
                            objBank.changePassword(userID);
                    }
                    catch (const char* error)
                    {
                        std::cout << error << std::endl;
                        break;
                    }
                        
                }
            } while (tryAgain != 'n');
            break;
        }          
        default:
            break;
        }

        std::cout << "What would you like to do next? (You can enter 1, 2 or 3) ";
        std::cin >> userChoice;
        std::cout << std::endl << std::endl;
    }    
}

void Bank::openAccount()
{
    AccountID += 1;
    std::string fname;
    std::string lname;
    std::string password;
    double iniBalance = 0;
    std::cout << "Thank you for your interest in opening an account with us!" << std::endl;
    std::cout << std::endl << "Please follow the below steps to open an account" << std::endl << std::endl;
    std::cout << "1. Please enter your first name: ";
    std::cin >> fname;
    std::cout << std::endl << "2. Please enter your last name: ";
    std::cin >> lname;
    std::cout << std::endl << "3. Please set a password for your account: ";
    std::cin >> password;
    std::cout << std::endl << "4. Enter the initial amount you want to deposit: ";
    std::cin >> iniBalance;
    Account acc(fname, lname, password, iniBalance, AccountID);
    accounts.insert(std::pair<long, Account>(acc.getAccountID(), acc));
    std::cout << std::endl << "Account Created!" << std::endl;
    std::cout << "Your Account ID is: " << acc.getAccountID() << std::endl;
    std::cout << "Please remember your Account ID and password as you will need them to login!" << std::endl;
}

void Bank::lastAccountID()
{
    if(!accounts.empty())
        this->AccountID = accounts.rbegin()->first;
    //std::cout << "The latest Account ID is " << this->AccountID << std::endl;
}

bool Bank::login(long userID)
{
    std::string password;
    std::map<long, Account>::iterator it = accounts.begin();
    bool login_status = false;
    for (it; it != accounts.end(); it++)
    {
        if (it->first == userID)
        {
            std::cout << "Please enter your password: ";
            std::cin >> password;

            if (it->second.password == password)
            {
                login_status = true;
                return login_status;
            }
        }
    }
    return login_status;
}

void Bank::display(long ID)
{
    std::cout << this->accounts.find(ID)->second;
}

void Bank::enquireBalance(long userID)
{
    std::cout << "Current Balance: " << this->accounts.find(userID)->second.Balance;
}

void Bank::changePassword(long userID)
{
    std::cout << "Enter your new password: ";
    std::string newPassword = "";
    std::cin >> newPassword;

    accounts.find(userID)->second.password = newPassword;
    std::cout << std::endl << "Password reset!" << std::endl << std::endl;
}

const char* Bank::bankExists(long userID)
{
    if (accounts.count(userID) == 1)
        return "Account ID is correct, check password";
    throw "Account ID does not EXIST!";
}

void Bank::deposit(long userID)
{
    double deposit = 0;
    std::cout << "Enter deposit amount: ";
    std::cin >> deposit;

    if (deposit > 0)
        accounts.find(userID)->second.Balance += deposit;
    else
        std::cout << "Cannot deposit 0 or negative amount. Perhaps you want to try withdrawing instead?" << std::endl;
    enquireBalance(userID);
}

void Bank::withdraw(long userID)
{
    double withdraw = 0;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> withdraw;

    if (withdraw <= accounts.find(userID)->second.Balance)
        accounts.find(userID)->second.Balance -= withdraw;
    else
        std::cout << "Balance lower than withdraw amount. Insufficient funds!" << std::endl;
    enquireBalance(userID);
}

void Bank::deleteAccount(long userID)
{
    if (accounts.find(userID)->second.Balance == 0)
    {
        accounts.erase(accounts.find(userID));
        std::cout << "Account deleted :(" << std::endl;
    }       
    else
    {
        std::cout << "Your current balance is: " << accounts.find(userID)->second.Balance;
        std::cout << std::endl << "You must have zero funds in your account before deleting account! Kindly withdraw your remaining balance" << std::endl;
        withdraw(userID);
        std::cout << std::endl << "Press 6 again if you wish to try and delete your account after emptying funds" << std::endl;
    }
}

std::ofstream& operator<<(std::ofstream& of, Account& acc)
{
    of << acc.accountID << " " << acc.password << " " << acc.firstName << " " << acc.lastName << " " << acc.Balance << std::endl;
    return of;
}

std::ostream& operator<<(std::ostream& o, Account& acc)
{
    o << "Account Number: " << acc.accountID << std::endl;
    o << "First Name: " << acc.firstName << std::endl;
    o << "Last Name: " << acc.lastName << std::endl;
    o << "Balance: " << acc.Balance << std::endl;
    return o;
}

std::ifstream& operator>>(std::ifstream& rf, Account& acc)
{
    rf >> acc.accountID >> acc.password >> acc.firstName >> acc.lastName >> acc.Balance;
    return rf;
}

