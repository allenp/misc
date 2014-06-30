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

        void View()
        {
            cout << "1. Deposits Log" << endl;
            cout << "2. Withdrawals Log" << endl;
            cout << "3. Third Party Transfers Log" << endl;
            cout << "4. Check Account Balances Log" << endl;
            cout << "5. exit";
            this->GetInteger();
        }
};
