#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "constants.h"


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
        int active;

    public:

        Movie(string code, string pg_rating, int duration, string director, string movie_type, int status)
        {
            this->code = code;
            this->pg_rating = pg_rating;
            this->duration_min = duration;
            this->director = director;
            this->movie_type = movie_type;
            this->active = status;
        }

        bool isValid()
        {
            return code.size() > 0 && title.size() > 0 && director.size() > 0;
        }

        string toLogFormat()
        {
            stringstream ss;
            ss << code << '\t';
            ss << pg_rating << '\t';
            ss << duration_min << '\t';
            ss << director << '\t';
            ss << movie_type << '\t';
            ss << active << endl;
            return ss.str();
        }

        bool save()
        {
            ifstream input;
            ofstream output;
            string line;
            int found;
            bool foundOnce = false;

            input.open(MOVIE_FILE, std::ifstream::in);
            output.open(MOVIE_TEMPORARY_FILE, std::ofstream::trunc);

            if( !input.fail() && !output.fail())
            {
                while(getline(input, line))
                {
                    found = -1;
                    found = line.find(this->code);
                    //the movie code is the first thing on the line
                    //so found should be 0
                    if(found == 0)
                    {
                        foundOnce = true;
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

                //movie doesnt exist?
                //add it to the end of the file
                if(!foundOnce)
                {
                    if(!this->isValid())
                    {
                        output << this->toLogFormat();
                    }
                    else
                    {
                        cout << "Movie data invalid. Will not save.";
                    }
                }

                input.close();
                output.close();

                rename(MOVIE_TEMPORARY_FILE, MOVIE_FILE);
            }
            else
            {
                cout << "Failed to save movie.";
            }

        }
};
