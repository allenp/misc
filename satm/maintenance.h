#include <iostream>
#include "customer.h"
#include "menu.h"

class MaintenanceMode : Menu
{
    private:
        Customer * customer;

    public:
        MaintenanceMode(Customer * customer)
        {
            this->customer = customer;
        }

        void Init()
        {
        }

        void DepositsLog()
        {
        }

        void WithdrawalLogs()
        {
        }

        void TransferLogs()
        {
        }

        void setCustomer(Customer *customer)
        {
            this->customer = customer;
        }

        void LogsMenu()
        {
            int choice;

            cout << "1. Deposits Log" << endl;
            cout << "2. Withdrawals Log" << endl;
            cout << "3. Third Party Transfers Log" << endl;
            cout << "4. Check Account Balances Log" << endl;
            choice = this->GetInteger();

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

        void View()
        {
            int choice;
            do
            {
                if(this->customer->IsAdministrator())
                {
                    cout << "1. Initialize S-ATM" << endl;
                    cout << "2. View Transaction Log" << endl;
                    cout << "3. exit" << endl << ": ";

                    choice = this->GetInteger();

                    switch(choice)
                    {
                        case 1:
                            Init();
                            break;
                        case 2:
                            LogsMenu();
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
