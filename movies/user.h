#ifndef USER_H
#define USER_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;


class User
{
    private:
        string username;
        string password;
        bool isAuth;
        bool isAdmin;

        User(string username, string password, bool isAdmin)
        {
            this->username = username;
            this->password = password;
        }

    public:
        bool isAuthenticated()
        {
            return isAuth;
        }

        bool isAdministrator()
        {
            return isAuth && isAdmin;
        }

        void logOut()
        {
            isAuth = false;
            username = "";
            password = "";
            isAdmin = false;
        }

        bool verifyPassword(string password)
        {
            isAuth = (this->password == password);
            return isAuth;
        }

        static User * login(string username, string password)
        {
            User * u;
            u = new User(username, password, true);
            u->verifyPassword(password);
            return u;
        }
};

#endif
