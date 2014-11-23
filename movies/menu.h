#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>

using namespace std;

class Menu
{
    private:

    public:

        Menu()
        {
        }

        string getString()
        {
            string input;
            cin >> input;
            return input;
        }

        int getInteger()
        {
           int number;
           cin >> number;
           this->clearBuffer();
           return number;
        }

        int getMoney()
        {
            int number;
            do
            {
                cin >> number;
                this->clearBuffer();

                if(number % 50 > 0 && number % 100 > 0)
                {
                    cout << "Only multiples of $50, $100, $500 and $1000 allowed" << endl;
                    cout << "Please try again." << endl;
                    cout << ": ";
                }
                else
                {
                    break;
                }
            } while(true);

            return number;
        }

        /*
         * TODO: implement password masking routine.
         *
         */
        string getPassword()
        {
            const char BACKSPACE_CHAR=127;
            const char RETURN_CHAR=10;
            string password;
            int ch = RETURN_CHAR;
            //ch = getchar();

            while( ch != RETURN_CHAR)
            {
                cout << "\b \b";

                if(ch==BACKSPACE_CHAR)
                {
                    if (password.length() != 0)
                    {
                        cout << "\b \b";
                        password.resize(password.length()-1);
                    }
                }
                else
                {
                    password += ch;
                    cout << '*';
                }
                //ch = getchar();
            }
            return password;
        }

        void clearBuffer()
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
};

#endif
