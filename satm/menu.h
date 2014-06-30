#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;

class Menu
{
    private:

    public:

        Menu()
        {
        }

        string GetString(char * buffer, int length=80)
        {
        }

        int GetInteger()
        {
           int number;
           cin >> number;
           this->ClearBuffer();
           return number;
        }

        float GetFloat()
        {
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
            int ch;
            ch = getchar();

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
                ch = getchar();
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
