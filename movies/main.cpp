#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "user.h"

using namespace std;

int main()
{
    User * u;
    string username;
    string password;

    do
    {
        cout << "Please enter username: ";
        cin >> username;
        cout << "Please enter password: ";
        cin >> password;

        try
        {
            u = User::login(username, password);
        }
        catch(int e)
        {
            if(e == -999)
            {
                cout << "Error: unable to read login file.";
            }
        }

        if(u->isAuthenticated())
        {
            if(u->isAdministrator())
            {
                /*
                w = new WorkerMode(u);
                w->view();
                delete w;
                */
            }
            else
            {
                /*
                cus = new CustomerMode(u);
                cus->view();
                delete cus;
                */
            }
            u->logOut();
            delete u;
        }
        else
        {
            cout << "Invalid credentials. Please try again." << endl;
        }
    } while(true);

}
