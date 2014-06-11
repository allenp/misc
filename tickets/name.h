using namespace std;

class Name
{
    private:
        string hFName;
        string hMName;
        string hLName;

    public:

        Name()
        {
            this->hFName = "";
            this->hLName = "";
            this->hMName = "";
        }

        Name(string fName, string mName, string lName)
        {
            this->hFName = fName;
            this->hMName = mName;
            this->hLName = lName;
        }

        string getFirstName()
        {
            return this->hFName;
        }

        string getMiddleName()
        {
            return this->hMName;
        }

        string getLastName()
        {
            return this->hLName;
        }
};
