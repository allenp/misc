#include "menu.h"
#include "transaction.h"

class OnlineMode : Menu
{
    private:
        Customer * customer;

    public:
        OnlineMode(Customer * customer)
        {
            this->customer = customer;
        }

        void doDeposit()
        {
            double money;
            cout << "Enter the amount to deposit: ";
            money = this->getDouble();
            Deposit * d;

            try
            {
                d = new Deposit(customer, money);
                d->complete();
                recordTransaction(d);
            }
            catch(int e)
            {
                if(e == -999)
                {
                    cout << "No funds specified for deposit." << endl;
                }
            }
        }

        void doWithdraw()
        {
            double money;
            Withdrawal * w;
            cout << "Enter amount to withdraw: ";
            money = this->getDouble();
            w = new Withdrawal(customer, money);

            try
            {
                w->complete();
                recordTransaction(w);
            }
            catch(int e)
            {
                if(e == -999)
                {
                    cout << "Insuficient funds in account. Withdrwal failure." << endl;
                }
            }
        }

        void doTransfer()
        {
            double money;
            string account;
            Customer * accountTo;

            Transfer * t;
            cout << "Enter amount to transfer: ";
            money = this->getDouble();
            cout << "Enter accout to send money to: ";
            account = this->getString();

            accountTo = Customer::getCustomer(account);

            try
            {
                if(accountTo != NULL)
                {

                    t = new Transfer(customer, accountTo, money);
                    t->complete();
                    recordTransaction(t);
                }
                else
                {
                    cout << "Invalid account specified." << endl;
                }
            }
            catch(int e)
            {
                if(e == -999)
                {
                    cout << "Insuficient funds in account. Withdrwal failure." << endl;
                }
            }
        }

        void doCheckBalance()
        {
            cout << "Your balance is: " << customer->getBalance() << endl;
            CheckBalance * c = new CheckBalance(customer);
            recordTransaction(c);
        }

        void recordTransaction(Transaction * transaction)
        {
            ofstream log_file;
            log_file.open(transaction->getLogFileName().c_str(), std::ofstream::app);

            if(!log_file.fail())
            {
                log_file << transaction->toLogFormat();
                log_file.close();
            }
            else
            {
                cout << "Unable to open log file: " << transaction->getLogFileName() << endl;
            }
        }

        void view()
        {
            int choice;
            do
            {
                cout << "***************************************" << endl;
                cout << "********** ACCOUNT VIEW ***************" << endl;
                cout << "1. Make a deposit" << endl;
                cout << "2. Make a withdrawal" << endl;
                cout << "3. Make a third party transfer." << endl;
                cout << "4. Check account balance. " << endl;
                cout << "5. Exit" << endl << ": ";
                choice = this->getInteger();
                switch(choice)
                {
                    case 1:
                        doDeposit();
                        break;
                    case 2:
                        doWithdraw();
                        break;
                    case 3:
                        doTransfer();
                        break;
                    case 4:
                        doCheckBalance();
                        break;
                    case 5:
                        cout << "Goodbye!" << endl;
                        break;
                    default:
                        cout << "Invalid choice. try again." << endl;
                }
            } while(choice != 5);
        }
};
