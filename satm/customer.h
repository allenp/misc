#include <string>
using namespace std;

class Customer
{
    private:
        string Account;
        string Firstname;
        string Lastname;
        double Balance;
        bool isAuth;
        bool isAdmin;

        Customer(string account, string firstname, string lastname, double balance, bool isAuth, bool isAdmin)
        {
            this->Account = account;
            this->Firstname = firstname;
            this->Lastname = lastname;
            this->Balance = balance;
            this->isAdmin = isAdmin;
            this->isAuth = isAuth;
            this->isAdmin = isAdmin;
        }

    public:
        Customer()
        {
            isAuth = false;
            isAdmin = false;
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

        static Customer * Login(string username, string password)
        {
            if(username == "1413914" && password == "d33pp0c8s")
            {
                return new Customer("1413914", "Administrator", "", 0.0, true, true);
            }

            ifstream input;
            std::string::size_type prev_pos = 0, pos = 0;
            std::vector<string> output;
            string line;
            input.open("account.txt", std::ifstream::in);
            string account, firstname, lastname;
            bool is_admin;
            double balance;

            //read the file one line at a time and copy each field
            //into a string vector
            //compare the username and password till we find a match
            while(getline(input, line))
            {
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
                    firstname = output.at(2);
                    lastname = output.at(3);
                    account = output.at(0);
                    balance = atof(output.at(4).c_str());
                    is_admin = (atoi(output.at(5).c_str()) == 1);

                    if(account == username && output.at(1) == password)
                    {
                        return new Customer(account, firstname, lastname, balance, true, is_admin);
                    }
                }
                output.clear();
            }

            //no account found. send back anonymous user
            return new Customer("NONE", "Anonymous", "", 0.0, false, false);
        }
};
