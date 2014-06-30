#include "menu.h"

class OnlineMode : Menu
{
    private:

    Customer * customer;

    public:
        OnlineMode(Customer * customer)
        {
            this->customer = customer;
        }

        void Deposit()
        {
        }

        void Withdraw()
        {
        }

        void Transfer(Customer * to)
        {
        }

        void CheckBalance()
        {
        }

        void View()
        {
            int choice;
            do
            {
                cout << "1. Make a deposit" << endl;
                cout << "2. Make a withdrawal" << endl;
                cout << "3. Make a third party transfer." << endl;
                cout << "4. Check account balance. " << endl;
                cout << "5. Exit" << endl << ": ";
                choice = this->GetInteger();
            } while(choice != 5);
            cout << "Goodbye!" << endl;
        }
};
