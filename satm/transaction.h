#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "customer.h"

#ifndef MINIMUM
#define MINIMUM 1000
#endif

using namespace std;

//abstract base transaction class
class Transaction
{
    protected:
        time_t TransTime;

    public:

        Transaction()
        {
            TransTime = time(0);
        }

        string GetTimestamp()
        {
            tm * ltm = localtime(&TransTime);
            stringstream ss;

            ss << ltm->tm_year + 1900 << "-";
            ss << ltm->tm_mon << "-";
            ss << ltm->tm_mday;
            ss << " " << ltm->tm_hour;
            ss << ":" << ltm->tm_min;
            ss << ":" << ltm->tm_sec;
            return ss.str();
        }

        virtual string GetLogFilename() =0;
        virtual string ToLogFormat() =0;
        virtual void Complete() =0;
};

//deposits
class Deposit : public Transaction
{
    protected:
        Customer * customer;
        double amount;

    public:
        Deposit(Customer * customer, double amount)
        {
            this->customer = customer;
            this->amount = amount;
        }

        string GetLogFilename()
        {
            return "deposit_log.txt";
        }

        string ToLogFormat()
        {
            stringstream ss;
            ss << this->GetTimestamp() << '\t';
            ss << customer->GetAccount() << "\t";
            ss << customer->GetFirstname() << "\t";
            ss << customer->GetLastname() << "\t";
            ss << amount << endl;
            return ss.str();
        }

        void Complete()
        {
            customer->SetBalance(customer->GetBalance() + amount);
        }
};

//withdrawals
class Withdrawal : public Deposit
{
    public:
        Withdrawal(Customer * customer, double amount) 
            : Deposit(customer, amount)
        {
        }

        string GetLogFilename()
        {
            return "withdrawal_log.txt";
        }

        void Complete()
        {
            if(customer->GetBalance() > (amount + MINIMUM))
            {
                customer->SetBalance(customer->GetBalance() - amount);
            }
            else
            {
                throw -999;
            }
        }
};


//transfers
class Transfer : public Transaction
{
    private:
        Customer * to;
        Customer * from;
        double amount;

    public:
        Transfer(Customer * to, Customer * from, double amount)
        {
            this->to = to;
            this->from = from;
            this->amount = amount;
        }

        string GetLogFilename()
        {
            return "transfer_log.txt";
        }

        string ToLogFormat()
        {
            stringstream ss;
            ss << this->GetTimestamp() << '\t';
            ss << from->GetAccount() << "\t";
            ss << from->GetFirstname() << "\t";
            ss << from->GetLastname() << "\t";
            ss << this->amount << "\t";
            ss << to->GetAccount() << "\t";
            ss << to->GetFirstname() << "\t";
            ss << to->GetLastname() << endl;
            return ss.str();
        }

        void Complete()
        {
            if(from->GetBalance() >= (MINIMUM + amount))
            {
                from->SetBalance(from->GetBalance() - amount);
                to->SetBalance(to->GetBalance() + amount);
            }
            else
            {
                throw -999;
            }
        }
};

class CheckBalance : public Transaction
{
    private:
        Customer * customer;

    public:
        CheckBalance(Customer * customer) 
        {
            this->customer = customer;
        }

        string GetLogFilename()
        {
            return "balance_log.txt";
        }

        void Complete()
        {
            //does nothing. doesn't need to.
        }

        string ToLogFormat()
        {
            stringstream ss;
            ss << this->GetTimestamp() << "\t";
            ss << customer->GetAccount() << "\t";
            ss << customer->GetFirstname() << "\t";
            ss << customer->GetLastname() << "\t";
            ss << customer->GetBalance() << endl;
            return ss.str();
        }
};
