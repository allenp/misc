#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class Customer
{
    private:
        string Account;
        string Firstname;
        string Lastname;
        string _password;
        double Balance;
        bool isAuth;
        bool isAdmin;

        Customer(string account, string firstname, string lastname, string password, double balance, bool isAdmin)
        {
            this->Account = account;
            this->Firstname = firstname;
            this->Lastname = lastname;
            this->Balance = balance;
            this->isAdmin = isAdmin;
            this->_password = password;
            this->isAdmin = isAdmin;
        }

    public:
        Customer()
        {
            isAuth = false;
            isAdmin = false;
        }

        string GetAccount()
        {
            return Account;
        }

        string GetFirstname()
        {
            return Firstname;
        }

        string GetLastname()
        {
            return Lastname;
        }

        double GetBalance()
        {
            return Balance;
        }

        void SetBalance(double d)
        {
            Balance = d;
        }

        bool IsAuthenticated()
        {
            return isAuth;
        }

        bool IsAdministrator()
        {
            return isAuth && isAdmin;
        }

        void LogOut()
        {
            this->isAuth = false;
            this->isAdmin = false;
            this->Account = "";
            this->Lastname = "";
            this->Balance = 0.00;
        }

        bool VerifyPassword(string password)
        {
            isAuth = _password == password;
            return isAuth;
        }

        static Customer * Login(string username, string password)
        {
            Customer * c;

            if(username == "1413914")
            {
                //administrator account requested
                c = new Customer("1413914", "Administrator", "Account", "d33pp0c8s", 0.0, true);
            }
            else
            {
                c = Customer::GetCustomer(username);
                if(c == NULL)
                {
                    //no account found.
                    c = new Customer("", "","", "NONE", 0.0, false);
                }
            }

            c->VerifyPassword(password);

            return c;
        }

        static Customer * GetCustomer(string username)
        {
            ifstream input;
            std::string::size_type prev_pos = 0, pos = 0;
            std::vector<string> output;
            string line;
            input.open("account.txt", std::ifstream::in);
            string account, firstname, lastname, password;
            bool is_admin;
            double balance;

            //read the file one line at a time and copy each field
            //into a string vector
            //compare the username and password till we find a match
            while(getline(input, line))
            {
                cout << line << endl;

                prev_pos = 0;
                pos = 0;

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
                if(output.size() == 6)
                {
                    account = output.at(0);
                    password = output.at(1);
                    firstname = output.at(2);
                    lastname = output.at(3);
                    balance = atof(output.at(4).c_str());
                    is_admin = (atoi(output.at(5).c_str()) == 1);

                    if(account == username)
                    {
                        cout << "Account found." << endl;
                        return new Customer(account, firstname, lastname, password, balance, is_admin);
                    }
                }
                output.clear();
            }
        }
};

#endif
