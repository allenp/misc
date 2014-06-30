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

        void DoDeposit()
        {
            double money;
            cout << "Enter the amount to deposit: ";
            money = this->GetDouble();
            Deposit * d;

            try
            {
                d = new Deposit(customer, money);
                d->Complete();
                RecordTransaction(d);
            }
            catch(int e)
            {
                if(e == -999)
                {
                    cout << "No funds specified for deposit." << endl;
                }
            }
        }

        void DoWithdraw()
        {
            double money;
            Withdrawal * w;
            cout << "Enter amount to withdraw: ";
            money = this->GetDouble();
            w = new Withdrawal(customer, money);

            try
            {
                w->Complete();
                RecordTransaction(w);
            }
            catch(int e)
            {
                if(e == -999)
                {
                    cout << "Insuficient funds in account. Withdrwal failure." << endl;
                }
            }
        }

        void DoTransfer()
        {
            double money;
            string account;
            Customer * accountTo;

            Transfer * t;
            cout << "Enter amount to transfer: ";
            money = this->GetDouble();
            cout << "Enter accout to send money to: ";
            account = this->GetString();

            accountTo = Customer::GetCustomer(account);

            try
            {
                if(accountTo != NULL)
                {

                    t = new Transfer(customer, accountTo, money);
                    t->Complete();
                    RecordTransaction(t);
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

        void DoCheckBalance()
        {
            cout << "Your balance is: " << customer->GetBalance() << endl;
            CheckBalance * c = new CheckBalance(customer);
            RecordTransaction(c);
        }

        void RecordTransaction(Transaction * transaction)
        {
            //TODO: add exception handling on file write
            ofstream log_file;
            log_file.open(transaction->GetLogFilename().c_str(), std::ofstream::app);
            log_file << transaction->ToLogFormat();
            log_file.close();

            //TODO: update the customer's account balance in account.txt
            ofstream account_file;
        }

        void View()
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
                choice = this->GetInteger();
                switch(choice)
                {
                    case 1:
                        DoDeposit();
                        break;
                    case 2:
                        DoWithdraw();
                        break;
                    case 3:
                        DoTransfer();
                        break;
                    case 4:
                        DoCheckBalance();
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
