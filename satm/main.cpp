#include <stdio.h>
#include <stdlib.h>
#include "maintenance.h"
#include "online.h"

using namespace std;

int main()
{

    Customer * c;
    MaintenanceMode * m;
    OnlineMode * o;

    string username;
    string password;

    int ch;

    do
    {
        cout << "Please enter username: ";
        cin >> username;
        cout << "Please enter password: ";
        cin >> password;

        try
        {
            c = Customer::login(username, password);
        }
        catch(int e)
        {
            if(e == -999)
            {
                cout << "Error: unable to read accounts file.";
            }
        }

        if(c->isAuthenticated())
        {
            if(c->isAdministrator())
            {
                m = new MaintenanceMode(c);
                m->view();
                delete m;
            }
            else
            {
                o = new OnlineMode(c);
                o->view();
                delete o;
            }
            c->logOut();
            delete c;
        }
        else
        {
            cout << "Invalid credentials. Please try again." << endl;
        }
    } while(true);
}
