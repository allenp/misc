#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


using namespace std;

class Movie
{
    protected:
        string title;
        string code;
        string pg_rating;
        int duration_min;
        string director;
        string movie_type;
        int status;

    public:

        Movie()
        {
        }
}
