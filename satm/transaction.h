#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

#include "customer.h"

#ifndef MINIMUM
#define MINIMUM 1000.00f
#endif

using namespace std;

//abstract base transaction class
class Transaction
{
    protected:
        double previousBalance;
        int amount;
        time_t TransTime;

    public:

        Transaction()
        {
            TransTime = time(0);
        }

        /*
         * Formats the time when the transaction occurred
         */
        string getTimestamp()
        {
            tm * ltm = localtime(&TransTime);
            stringstream ss;

            ss << ltm->tm_year + 1900 << "-";
            ss << setw(2) << setfill('0') << ltm->tm_mon << "-";
            ss << setw(2) << setfill('0') << ltm->tm_mday;
            ss << " " << setw(2) << setfill('0') << ltm->tm_hour;
            ss << ":" << setw(2) << setfill('0') << ltm->tm_min;
            ss << ":" << setw(2) << setfill('0') << ltm->tm_sec;
            return ss.str();
        }

        /*
         * Each transaction type will know it's log file name
         */
        virtual string getLogFileName() =0;

        /*
         * Each transaction type will be able to generate it's own logging format as
         * a string
         */
        virtual string toLogFormat() =0;

        /*
         * Each transaction type will be able to perform the necessary operations against
         * the customer(s) accounts, including fee subtraction and account balance change
         */
        virtual void complete() =0;

        /*
         * Each transaction type knows it's own fees
         */
        virtual double getFee() =0;
};

/*
 * Handles deposit transactions
 */
class Deposit : public Transaction
{
    protected:
        Customer * customer;
        static const double fee = 10.00;

    public:
        Deposit(Customer * customer, int amount)
        {
            this->customer = customer;
            this->amount = amount;
        }

        string getLogFileName()
        {
            return "deposit_log.txt";
        }

        string toLogFormat()
        {
            stringstream ss;
            ss << this->getTimestamp() << '\t';
            ss << customer->getAccountLastThree() << "\t";
            ss << std::fixed << std::setprecision(2) << this->amount << "\t";
            ss << std::fixed << std::setprecision(2) << this->getFee() << "\t";
            ss << std::fixed << std::setprecision(2) << previousBalance << "\t";
            ss << std::fixed << std::setprecision(2) << customer->getBalance() << endl;
            return ss.str();
        }

        void complete()
        {
            previousBalance = customer->getBalance();
            customer->setBalance(customer->getBalance() + amount - fee);
            customer->saveBalance();
        }

        double getFee()
        {
            return fee;
        }
};

/*
 * Handles withdrawal transactions
 * Derives from Deposit since they are similar (sort of a negative deposit)
 * overrides only the necessary methods
 */
class Withdrawal : public Deposit
{
    public:
        Withdrawal(Customer * customer, int amount)
            : Deposit(customer, amount)
        {
        }

        string getLogFileName()
        {
            return "withdrawal_log.txt";
        }

        void complete()
        {
            if(customer->getBalance() >= (amount + MINIMUM + fee))
            {
                previousBalance = customer->getBalance();
                customer->setBalance(customer->getBalance() - amount - fee);
                customer->saveBalance();
            }
            else
            {
                throw -999;
            }
        }
};


/*
 * Handles transfer from one account to the next
 */
class Transfer : public Transaction
{
    private:
        Customer * to;
        Customer * from;
        static const double fee = 30.00;

    public:
        Transfer(Customer * to, Customer * from, int amount)
        {
            this->to = to;
            this->from = from;
            this->amount = amount;
        }

        string getLogFileName()
        {
            return "transfer_log.txt";
        }

        string toLogFormat()
        {
            stringstream ss;
            ss << this->getTimestamp() << '\t';
            ss << from->getAccountLastThree() << "\t";
            ss << to->getAccountLastThree() << "\t";
            ss << std::fixed << std::setprecision(2) << this->amount << "\t";
            ss << std::fixed << std::setprecision(2) << this->getFee() << "\t";
            ss << std::fixed << std::setprecision(2) << previousBalance << "\t";
            ss << std::fixed << std::setprecision(2) << from->getBalance() << endl;
            return ss.str();
        }

        void complete()
        {
            if(from->getBalance() >= (MINIMUM + amount + fee))
            {
                previousBalance = from->getBalance();
                from->setBalance(from->getBalance() - (amount + fee));
                from->saveBalance();

                to->setBalance(to->getBalance() + amount);
                to->saveBalance();
            }
            else
            {
                throw -999;
            }
        }

        double getFee()
        {
            return fee;
        }
};

/*
 * Handles balance checking
 */
class CheckBalance : public Transaction
{
    private:
        Customer * customer;
        static const double fee = 0.00;

    public:
        CheckBalance(Customer * customer)
        {
            this->customer = customer;
        }

        string getLogFileName()
        {
            return "balance_log.txt";
        }

        void complete()
        {
            //does nothing. doesn't need to since no fees are involved and the
            //balance doesn't get changed.
        }

        string toLogFormat()
        {
            stringstream ss;
            ss << this->getTimestamp() << "\t";
            ss << customer->getAccountLastThree() << "\t";
            ss << std::fixed << std::setprecision(2) << customer->getBalance() << "\t";
            ss << std::fixed << std::setprecision(2) << this->getFee() << endl;
            return ss.str();
        }

        double getFee()
        {
            return fee;
        }
};
