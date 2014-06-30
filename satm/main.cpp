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

    do
    {
        cout << "Please enter username: ";
        cin >> username;
        cout << "Please enter password: ";
        cin >> password;

        c = Customer::Login(username, password);

        if(c->IsAuthenticated())
        {
            if(c->IsAdministrator())
            {
                m = new MaintenanceMode(c);
                m->View();
            }
            else
            {
                o = new OnlineMode(c);
                o->View();
            }
            c->LogOut();
        }
        else
        {
            cout << "Invalid credentials. Please try again.";
        }
    } while(true);
}
