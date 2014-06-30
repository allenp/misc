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
        }
};
