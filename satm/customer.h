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

    public:
        Customer()
        {
            isAuth = false;
            isAdmin = false;
        }

        Customer(string account, string firstname, string lastname, double balance, bool isAdmin)
        {
            this->Account = account;
            this->Firstname = firstname;
            this->Lastname = lastname;
            this->Balance = balance;
            this->isAdmin = isAdmin;
            this->isAuth = true;
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
            return new Customer("93454234", "Paul", "Allen", 234.45, true);
        }
};
