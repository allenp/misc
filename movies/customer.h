#include <string>
#include <iostream>
#include "menu.h"

using namespace std;

class CustomerMode : Menu
{
    private:
        User * user;

    public:
        CustomerMode(User *user)
        {
            this->user = user;
        }

        void movieSchedule()
        {
        }

        void buyTicket()
        {
        }

        void view()
        {
            int choice;
            do
            {
                cout << "1. Movie Schedule" << endl;
                cout << "2. Buy Ticket" << endl;
                cout << "3. Exit" << endl;
                cout << ": ";

                choice = this->getInteger();

                switch(choice)
                {
                    case 1:
                        movieSchedule();
                        break;
                    case 2:
                        buyTicket();
                        break;
                    case 3:
                        cout << "Good bye!" << endl;
                        break;
                    default:
                        cout << "Invalid choice entered." << endl;
                }
            }while(choice != 3);
        }
};
