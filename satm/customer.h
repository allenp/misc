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
            else
            {
                return new Customer("234234234", "Random", "Person", 2342, true, false);
            }
        }
};
