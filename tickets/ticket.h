#include <iostream>
#include <string>
#include "name.h"

using namespace std;

class Ticket
{
    private:
        int ticketNumber;
        string hAddress;
        Name customer;

    public:

        Ticket(): customer() {
            ticketNumber = 0;
            hAddress = "";
        }

        Ticket(string fName, string mName, string lName, int ticket, string address)
            : customer(fName, mName, lName) {
            ticketNumber = ticket;
            hAddress = address;
        }

        Name * getCustomer()
        {
            return &customer;
        }

        string getAddress()
        {
            return hAddress;
        }

        int getTicketNumber()
        {
            return ticketNumber;
        }
};
