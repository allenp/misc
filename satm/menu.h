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

        string GetString()
        {
            string input;
            cin >> input;
            return input;
        }

        int GetInteger()
        {
           int number;
           cin >> number;
           this->ClearBuffer();
           return number;
        }

        float GetDouble()
        {
            double number;
            cin >> number;
            this->ClearBuffer();
            return number;
        }

        /*
         * TODO: implement password masking routine.
         *
         */
        string GetPassword()
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

        void ClearBuffer()
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
};

#endif
