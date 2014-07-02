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

        void depositsLog()
        {
        }

        void withdrawalLogs()
        {
        }

        void transferLogs()
        {
        }

        void setCustomer(Customer *customer)
        {
            this->customer = customer;
        }

        void logsMenu()
        {
            int choice;

            cout << "1. Deposits Log" << endl;
            cout << "2. Withdrawals Log" << endl;
            cout << "3. Third Party Transfers Log" << endl;
            cout << "4. Check Account Balances Log" << endl;
            choice = this->getInteger();

            switch(choice)
            {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    cout << "Invalid choice." << endl;
            }
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
