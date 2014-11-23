#include <string>
#include <iostream>
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
            title = this->getString();
            cout << endl << "Enter director: ";
            director = this->getString();
            cout << endl << "Enter duration in minutes: ";
            duration = this->getInteger();
            cout << endl << "Enter status (1 - active, 0 - inactive): ";
            status = this->getInteger();

            Movie * m = new Movie(code, pg_rating, duration, director, movie_type, status);
            m->save();
            delete m;
        }

        void updateMovie()
        {
        }

        void movieSchedule()
        {
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
