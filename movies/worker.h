#include <string>
#include <iostream>
#include <ctime>
#include "menu.h"
#include "movie.h"

using namespace std;

class WorkerMode : Menu
{
    private:
        User * user;

    public:
        WorkerMode(User * user)
        {
            this->user = user;
        }

        void addMovie()
        {
            string code, title, director, movie_type, pg_rating;
            int duration, status;
            cout << "Enter movie code: ";
            code = this->getString();
            cout << endl << "Enter movie title: ";
            title = this->getLine();
            cout << endl << "Enter director: ";
            director = this->getLine();
            cout << endl << "Enter duration in minutes: ";
            duration = this->getInteger();
            cout << endl << "Enter status (1 - active, 0 - inactive): ";
            status = this->getInteger();

            Movie * m = new Movie(code, title, pg_rating, duration, director, movie_type, status);
            m->save();
            delete m;
        }

        void updateMovie()
        {
        }

        void movieSchedule()
        {
            time_t start = time(0);
            size_t Minute = 255;
            tm * now;

            now = localtime(&start);
            
            now->tm_hour = 11;
            now->tm_sec = 0;
            now->tm_min = 0;

            stringstream ss;
            ss << setw(2) << setfill('0') << now->tm_mday << "-";
            ss << setw(2) << setfill('0') << now->tm_mon << "-";
            ss << now->tm_year + 1900;
            string filename = ss.str();

            //get a movie
            //is it active? let's schedule it.
            //make note of the time + movie length
            //is the time + movie length less than 12pm?
            //if no, stop, otherwise continue.
            //save that as new time for next film
            //make a note of a break time
            //
            //save the movies to file movieschedule-dd-mm-yyyy.dat

            ifstream input;
            ofstream outfile;
            string::size_type prev_pos = 0, pos = 0;
            std::vector<string> bucket;
            string line;
            Movie * movie;

            input.open(MOVIE_FILE, std::ifstream::in);
            filename = "movieschedule-" + filename;
            outfile.open(filename.c_str(), std::ofstream::trunc);
            //TODO: check input and output are valid.
            while(getline(input, line))
            {
                prev_pos = 0;
                pos = 0;

                while((pos = line.find('\t', pos)) != string::npos)
                {
                    string substring(line.substr(prev_pos, pos - prev_pos));
                    bucket.push_back(substring);
                    prev_pos = ++pos;
                }

                bucket.push_back(line.substr(prev_pos, pos - prev_pos));

                if(bucket.size() == 7)
                {
                    //code, title, pg_rating, duration, director, movie_type, status
                    movie = new Movie(bucket.at(0), bucket.at(1), bucket.at(2), atoi(bucket.at(3).c_str()),
                            bucket.at(4), bucket.at(5), atoi(bucket.at(6).c_str()));
                    if(movie->isActive())
                    {
                        start = start + (movie->getDurationMin() * Minute);
                        //print out movie details to outfile
                        outfile << movie->toLogFormat();
                        now = localtime(&start);
                    }
                }
                bucket.clear();
            }
            outfile.close();
            input.close();
        }

        void buyTicket()
        {
        }

        void view()
        {
            int choice;
            do
            {
                if(this->user->isWorker())
                {
                    cout << "1. Add Movie" << endl;
                    cout << "2. Update Movie" << endl;
                    cout << "3. Generate Movie Schedule" << endl;
                    cout << "4. Buy Ticket" << endl;
                    cout << "5. Exit" << endl;
                    cout << ": ";

                    choice = this->getInteger();

                    switch(choice)
                    {
                        case 1:
                            addMovie();
                            break;
                        case 2:
                            updateMovie();
                            break;
                        case 3:
                            movieSchedule();
                            break;
                        case 4:
                            buyTicket();
                            break;
                        case 5:
                            cout << "Good bye!" << endl;
                            break;
                        default:
                            cout << "Invalid choice entered." << endl;
                    }
                }
                else
                {
                    cout << "You are not authorized to access this function." << endl;
                }
            } while(choice != 5);
        }
};
