#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "user.h"
#include "worker.h"
#include "customer.h"

using namespace std;

void init();

int main()
{

    //this here for now
    init();
    //------

    User * u;
    WorkerMode * w;
    CustomerMode * c;
    string username;
    string password;
    bool exit;

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
        if(u->isWorker())
        {
            w = new WorkerMode(u);
            w->view();
            delete w;
        }
        else
        {
            c = new CustomerMode(u);
            c->view();
            delete c;
        }
        u->logOut();
        delete u;
    }
    else
    {
        cout << "Invalid credentials. Please try again." << endl;
    }
}

void init()
{
    ofstream output;
    output.open("login.dat", std::ofstream::trunc);
    output << "damion" << "\t" << "password123" << "\t" << "Damion Allen"  << "\t" << 1 << endl;
    output.close();
}
