#include <iostream>
#include <exception>
#include <string>
#include <iomanip>
using namespace std;

// custom exception classes for handling specific error scenarios in the BankAccount class
class InsufficientFundsException : public exception
{
private:
    string message;

public:
    InsufficientFundsException(string msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// custom exception class for handling invalid amount scenarios in the BankAccount class
class InvalidAmountException : public exception
{
private:
    string message;

public:
    InvalidAmountException(string msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// custom exception class for handling invalid email scenarios
class InvalidEmailException : public exception
{
private:
    string message;

public:
    InvalidEmailException(string msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// function to validate email address format
void validEmail(string email)
{
    // check if the email contains '@' and '.'
    if (email.find('@') == string::npos || email.find('.') == string::npos)//npos is a constant representing "not found" in the string. If either '@' or '.' is not found in the email string, the function throws an InvalidEmailException with a message indicating that the email address is invalid.
    { // if '@' or '.' is not found in the email string, throw an InvalidEmailException
        throw InvalidEmailException("Invalid email address.");
    }
    cout << "Email address: " << email << endl;
}

class BankAccount
{
private:
    string accountHolder;
    int accountNumber;
    double balance;

public:
    // constructor to initialize the bank account with account holder's name, account number, and initial balance
    BankAccount(string acchold, int accnum, double bal)
    {
        accountHolder = acchold;
        accountNumber = accnum;
        balance = bal;
    }
    // deposit method to add money to the account
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            throw InvalidAmountException("Invalid deposit amount.");
        }
        else
        {
            balance += amount;
            cout << "Deposit successful. New balance: " << fixed << setprecision(2) << balance << endl; // setprecision(2) to display balance with 2 decimal places
        }
    }
    // withdraw method to subtract money from the account if sufficient funds are available
    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            throw InvalidAmountException("Invalid withdrawal amount.");
        }
        if (amount > balance)
        {
            throw InsufficientFundsException("Insufficient funds.");
        }
        else
        {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << fixed << setprecision(2) << balance << endl; // fixed and setprecision(2) to display balance with 2 decimal places. if we don't use fixed, it will display in scientific notation if the balance is very small or very large.
        }
    }
    // displatInfo method to show the account details including account holder's name, account number, and current balance
    void displayInfo()
    {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
    }
};

int main()
{
    BankAccount account("John Doe", 12345, 1000.0);
    cout << "------Initial Account Details----" << endl;
    account.displayInfo();

    cout << "\n ------Valid Deposit----" << endl;
    try
    {
        account.deposit(500.0);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "\n ------valid Withdrawal----" << endl;
    try
    {
        account.withdraw(200.0);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "\n ------Invalid Deposit----" << endl;
    try
    {
        account.deposit(-100.0);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "\n ------Invalid Withdrawal----" << endl;
    try
    {
        account.withdraw(2000.0);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "\n ------Final Account Details----" << endl;
    account.displayInfo();

    cout << "\n ------Invalid Email----" << endl;
    try
    {
        validEmail("invalidemail.com");
    }
    catch (const InvalidEmailException &e)
    {
        cout << e.what() << endl;
    }

    cout << "\n ------Valid Email----" << endl;
    try
    {
        validEmail("validemail@example.com");
    }
    catch (const InvalidEmailException &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}