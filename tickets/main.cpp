#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ticket.h"

using namespace std;

int mainMenu();
Ticket * sellTicket();
void printTickets();
vector<Ticket> * readTicketsFromFile();
void writeTicketsToFile(vector<Ticket> * tickets);
void clearBuffer();
void simulateRaffle();

const char * FILENAME = "tickets.txt";

vector<Ticket> * tickets;

int main()
{
    int choice = 0;

    Ticket * ticket;
    tickets = readTicketsFromFile();

    do
    {
        choice = mainMenu(); 

        switch(choice)
        {
            case 1:
                ticket = sellTicket();
                tickets->push_back(*ticket);
                writeTicketsToFile(tickets);
                break;
            case 2:
                printTickets();
                break;
            case 3:
                simulateRaffle();
                break;
            case 4:
                //clear the tickets vector out of memory
                delete tickets;
                break;
            default:
                cout << "Invalid choice. Please try again" << endl;
        }

    } while(choice != 4);

    return 0;
}

int mainMenu()
{
    int choice = 0;
    cout << "******************************" << endl;
    cout << "1 ---- Sell Ticket" << endl;
    cout << "2 ---- View Sales" << endl;
    cout << "3 ---- Run Raffle" << endl;
    cout << "4 ---- Exit" << endl << ": ";
    cin >> choice;

    clearBuffer();

    return choice;
}

Ticket * sellTicket()
{
    string fname;
    string lname;
    string mname;
    string address;
    int ticket_no;

    Ticket * ticket;

    cout << "Please enter your first name: ";
    getline(cin, fname); 

    cout << endl << "Please enter your middle name: ";
    getline(cin, mname);

    cout << endl << "Please enter your last name: ";
    getline(cin, lname);

    cout << endl << "Please enter ticket number: ";
    cin >> ticket_no;

    clearBuffer();

    cout << endl << "Please enter address: ";
    getline(cin, address);

    ticket = new Ticket(fname, mname, lname, ticket_no, address);

    return ticket;
}

void clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(256, '\n');
}

void printTickets()
{
    vector<Ticket> * tickets = readTicketsFromFile();

    cout << endl;
    cout << "******** Ticket Sales **********" << endl;

    vector<Ticket>::iterator i = tickets->begin();
    vector<Ticket>::iterator end = tickets->end();

    cout << "Ticket Number" << '\t' << "First name" << '\t' << "Middle name" << '\t' << "Last name" << '\t' << "Address" << endl;

    for(; i != end; i++)
    {
        cout << i->getTicketNumber() << "\t" << i->getCustomer()->getFirstName() << "\t";
        cout << i->getCustomer()->getMiddleName() << "\t" << i->getCustomer()->getLastName() << "\t";
        cout << i->getAddress() << "\t" << endl << '\n';
    }
}

void simulateRaffle()
{
    srand(unsigned(time(NULL)));
    Ticket ticket;

    std::random_shuffle(tickets->begin(), tickets->end());
    int length = min(3, (int)tickets->size());

    if(length > 0) {
        cout << "**************** AND THE WINNERS ARE ****************";
    }

    for(int i = 0; i < length; i++)
    {
        ticket = tickets->at(i);
        cout << ticket.getTicketNumber() << "\t" << ticket.getCustomer()->getFirstName() << "\t";
        cout << ticket.getCustomer()->getMiddleName() << "\t" << ticket.getCustomer()->getLastName() << "\t";
        cout << ticket.getAddress() << "\t" << endl;
    }
}

vector<Ticket> * readTicketsFromFile()
{
    std::vector<Ticket> * tickets = new std::vector<Ticket>();
    Ticket * ticket;

    ifstream input;
    std::string::size_type prev_pos = 0, pos = 0;
    std::vector<std::string> output;
    string line;

    input.open(FILENAME, std::ifstream::in);

    while(getline(input, line))
    {
        cout << line;
        prev_pos = 0;
        pos = 0;

        while((pos = line.find('\t', pos)) != std::string::npos)
        {
            string substring(line.substr(prev_pos, pos - prev_pos));
            output.push_back(substring);
            prev_pos = ++pos;
        }

        output.push_back(line.substr(prev_pos, pos - prev_pos));

        if(output.size() == 5)
        {
            ticket = new Ticket(output.at(0), output.at(1), output.at(2), atoi(output.at(3).c_str()), output.at(4));
            tickets->push_back(*ticket);
        }

        output.clear();
    }
    
    return tickets;
}

void writeTicketsToFile(vector<Ticket> * tickets)
{
    ofstream output;
    output.open(FILENAME, std::ofstream::trunc);

    vector<Ticket>::iterator i = tickets->begin();
    vector<Ticket>::iterator end = tickets->end();

    for(; i != end; i++) {
        output << i->getTicketNumber() << "\t" << i->getCustomer()->getFirstName() << "\t";
        output << i->getCustomer()->getMiddleName() << "\t" << i->getCustomer()->getLastName() << "\t";
        output << i->getAddress() << "\t" << endl;
    }

    output.close();
}
