#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>


#ifndef ACCOUNT_FILE
#define ACCOUNT_FILE "account.txt"
#define ACCOUNT_TEMPORARY_FILE "account_temp.txt"
#endif

using namespace std;

/*
 * Class: Customer
 * Description: Manages the customer's account information
 * Which includes reading and writing to the accounts file
 * for Log-in and for recording account information
 *
 * The file format is:
 *
 * account# {tab} password {tab} firstName {tab} lastName {tab} balance {tab} isAdmin
 *
 *
 * the isAdmin field is used to set an account as having administrative privileges.
 */
class Customer
{
    private:
        string account;
        string firstName;
        string lastName;
        string password;
        double balance;
        bool isAuth;
        bool isAdmin;

        Customer(string account, string firstname, string lastname, string password, double balance, bool isAdmin)
        {
            this->account = account;
            this->firstName = firstname;
            this->lastName = lastname;
            this->balance = balance;
            this->isAdmin = isAdmin;
            this->password = password;
            this->isAdmin = isAdmin;
        }

    public:
        Customer()
        {
            isAuth = false;
            isAdmin = false;
        }

        string getAccount()
        {
            return account;
        }

        string getAccountLastThree()
        {
            std::string::size_type length = 3, start = account.size() - length;
            if(account.size() > length)
            {
                return account.substr(start, length);
            }
            else
            {
                return "";
            }
        }

        string getFirstName()
        {
            return firstName;
        }

        string getLastName()
        {
            return lastName;
        }

        double getBalance()
        {
            return balance;
        }

        void setBalance(double d)
        {
            balance = d;
        }

        bool isAuthenticated()
        {
            return isAuth;
        }

        bool isAdministrator()
        {
            return isAuth && isAdmin;
        }

        string toLogFormat()
        {
            stringstream ss;
            ss << account << '\t';
            ss << password << '\t';
            ss << firstName << '\t';
            ss << lastName << '\t';
            ss << std::fixed << std::setprecision(2) << balance << '\t';
            ss << isAdmin << endl;
            return ss.str();
        }

        void logOut()
        {
            this->isAuth = false;
            this->isAdmin = false;
            this->account = "";
            this->lastName = "";
            this->balance = 0.00;
        }

        bool verifyPassword(string password)
        {
            isAuth = (this->password == password);
            return isAuth;
        }


        //record the current customer balance back to the accounts file
        bool saveBalance()
        {
            ifstream input;
            ofstream output;
            string line;
            int found;

            input.open(ACCOUNT_FILE, std::ifstream::in);
            output.open(ACCOUNT_TEMPORARY_FILE, std::ofstream::trunc);

            if( !input.fail() && !output.fail())
            {
                while(getline(input, line))
                {
                    found = -1;
                    found = line.find(this->account);
                    //the account # is the first thing on the line
                    //so found should be 0
                    if(found == 0)
                    {
                        line = this->toLogFormat();
                    }
                    else
                    {
                        //just put the line back in the file as normal;
                        //have to add back the line break
                        line += "\n";
                    }
                    output << line;
                }

                input.close();
                output.close();

                rename(ACCOUNT_TEMPORARY_FILE, ACCOUNT_FILE);
            }

        }

        static Customer * login(string username, string password)
        {
            Customer * c;

            /*
             * Fail-safe in case we are unable to read the accounts file (say for instance on first initialisation)
             * This is the default administrator.
             */
            if(username == "1413914")
            {
                //administrator account requested
                c = new Customer("1413914", "Administrator", "Account", "d33pp0c8s", 0.0, true);
            }
            else
            {
                //retrieve customer information from the accounts file using their username
                c = Customer::getCustomer(username);
                if(c == NULL)
                {
                    //no account found.
                    c = new Customer("", "","", "NONE", 0.0, false);
                }
            }

            //check that the password provided is correct
            c->verifyPassword(password);

            return c;
        }

        static Customer * getCustomer(string username)
        {
            ifstream input;
            std::string::size_type prev_pos = 0, pos = 0;
            std::vector<string> output;
            string line;


            string account, firstName, lastName, password;
            bool is_admin;
            double balance;
            int found;

            /*
             * read the file one line at a time.
             * Test each line for the username provided.
             * If not found, skip that line and move to the next.
             * If found. break out the line into pieces and check the username again
             * if matches, create customer object and return it.
             */
            input.open(ACCOUNT_FILE, std::ifstream::in);
            if(! input.fail())
            {
                while(getline(input, line))
                {
                    found = line.find(username);

                    if(found < 0)
                    {
                        continue;
                    }

                    prev_pos = 0;
                    pos = 0;

                    //split each line at the tab breaks and store
                    //each part as a new string in the string vector
                    //when we are done, we should have six pieces of string
                    //for each part of the customer information
                    while((pos = line.find('\t', pos)) != string::npos)
                    {
                        string substring(line.substr(prev_pos, pos - prev_pos));
                        output.push_back(substring);
                        prev_pos = ++pos;
                    }

                    output.push_back(line.substr(prev_pos, pos - prev_pos));

                    //output.at(0) == account,
                    //output.at(1) == password,
                    //output.at(2) == firstname,
                    //output.at(3) == lastname,
                    //output.at(4) == balance,
                    //output.at(5) == is_admin
                    //
                    //We expect six pieces to be there
                    if(output.size() == 6)
                    {
                        account = output.at(0);
                        password = output.at(1);
                        firstName = output.at(2);
                        lastName = output.at(3);
                        balance = atof(output.at(4).c_str());
                        is_admin = (atoi(output.at(5).c_str()) == 1);

                        if(account == username)
                        {
                            //a match is found so return this customer to caller
                            return new Customer(account, firstName, lastName, password, balance, is_admin);
                        }
                    }
                    output.clear();
                }
            }
            else
            {
                throw -999;
            }
            return NULL;
        }
};

#endif
