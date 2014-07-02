#include <iostream>
#include <fstream>
#include <vector>
#include "customer.h"
#include "menu.h"
#include "constants.h"

class MaintenanceMode : Menu
{
    private:
        Customer * customer;

    public:
        MaintenanceMode(Customer * customer)
        {
            this->customer = customer;
        }

        void init()
        {
            ofstream output;
            output.open(ACCOUNT, std::ofstream::trunc);

            output << "1413914" << "\t" << "d33pp0c8s" << "\t" << "Administrator" << "\t" << "Account" << "\t" << 0 << "\t" << 1 << endl;
            for(int i = 1000000; i < 1000011; i++)
            {

                output << i << "\t" << i << "\t" << "Customer " << i << "\t" << "Account" << "\t" << 350.00 << "\t" << 0 << endl;
            }

            output.close();
        }

        void newAccount()
        {
            string firstname, lastname, password;
            string account;
            double money;

            cout << "Enter account number: ";
            cin >> account;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter customer first name: ";
            cin >> firstname;
            cout << "Enter customer last name: ";
            cin >> lastname;
            cout << "Enter customer balance: ";
            cin >> money;

            Customer * c = new Customer(account, firstname, lastname, password, money);
            c->saveBalance();
        }

        void readLogFile(string filename)
        {
            ifstream log;
            string line;
            log.open(filename.c_str(), std::ofstream::in);
            if( !log.fail())
            {
                while(getline(log, line))
                {
                    cout << line << endl;
                }
            }
            else
            {
                cout << "No log file found: " << filename;
            }
        }

        void depositsLog()
        {
            cout << "***************** DEPOSIT LOG *************" << endl;
            readLogFile("deposit_log.txt");
            cout << endl << endl;
        }

        void withdrawalLogs()
        {
            cout << "***************** WITHDRAWL LOG *************" << endl;
            readLogFile("withdrawal_log.txt");
            cout << endl << endl;
        }

        void transferLogs()
        {
            cout << "***************** TRANSFER LOG *************" << endl;
            readLogFile("transfer_log.txt");
            cout << endl << endl;
        }

        void checkBalancesLog()
        {
            cout << "***************** CHECK BALANCES LOG *************" << endl;
            readLogFile("balance_log.txt");
            cout << endl << endl;
        }

        void logsMenu()
        {
            int choice;

            do
            {
                cout << "1. Deposits Log" << endl;
                cout << "2. Withdrawals Log" << endl;
                cout << "3. Third Party Transfers Log" << endl;
                cout << "4. Check Account Balances Log" << endl;
                cout << "5. Create new customer account" << endl;
                cout << "6. Previous Menu" << endl;
                choice = this->getInteger();

                switch(choice)
                {
                    case 1:
                        depositsLog();
                        break;
                    case 2:
                        withdrawalLogs();
                        break;
                    case 3:
                        transferLogs();
                        break;
                    case 4:
                        checkBalancesLog();
                        break;
                    case 5:
                        newAccount();
                        break;
                    case 6:
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                }
            }while(choice != 6);
        }

        void view()
        {
            int choice;
            do
            {
                if(this->customer->isAdministrator())
                {
                    cout << "1. Initialize S-ATM" << endl;
                    cout << "2. View Transaction Log" << endl;
                    cout << "3. exit" << endl << ": ";

                    choice = this->getInteger();

                    switch(choice)
                    {
                        case 1:
                            init();
                            break;
                        case 2:
                            logsMenu();
                            break;
                        case 3:
                            cout << "Goodbye!" << endl;
                            break;
                        default:
                            cout << "Invalid choice entered." << endl;
                    }
                }
                else
                {
                    cout << "You are not authorized to access this function." << endl;
                    choice = 3;
                }
            } while(choice != 3);
        }
};
