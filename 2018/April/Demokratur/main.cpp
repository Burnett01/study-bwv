/*
  © Steven Agyekum
*/

#include <QCoreApplication>
#include <QProcess>
#include <string>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

#define MAX_PEOPLE 10
#define PARTY_RED 1
#define PARTY_BLACK 2
#define MAX_ROUNDS 500000
#define WRAPAROUND 20

// Playground
void draw(int *people)
{
    int inRed = 0;
    int inBlack = 0;

    for(int i = 0; i < MAX_PEOPLE; i++)
    {
        if((i % WRAPAROUND == 0))
            std::cout << std::endl;

        switch(people[i])
        {
        case PARTY_RED:
            std::cout << "0";
            inRed++;
            break;
        case PARTY_BLACK:
            std::cout << "1";
            inBlack++;
            break;
        default:
            std::cout << "X";
            break;
        }

        std::cout << "|";
    }

    std::cout << std::endl;

    std::cout << "People in Red: " << inRed << std::endl;
    std::cout << "People in Black: " << inBlack << std::endl;

    if( inRed == MAX_PEOPLE || inBlack == MAX_PEOPLE )
    {
        std::cout << "Dictatorship" << std::endl;
        system( "pause" );
        exit( 0 );
    }

    system("CLS");
}

// Bounds checking
int withinBounds(int a, int b)
{
    return ( a >= 0 && a <= b ); // a <= b
}

// Convience one another to vote for their party
int persuade(int a, int b)
{
    a = (a > b) ? a : b;
    b = (b > a) ? b : a;

    return (rand() > RAND_MAX / a ) ? a : b;
}

// Entry point
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand (time(NULL));
    int people[MAX_PEOPLE] = { 0 };

    std::cout << "Empty Playground: " << std::endl;
    draw( people );

    for(int d = 0; d < MAX_ROUNDS; d++)
    {
        std::cout << std::endl << std::endl << "Conversation: " << (d + 1) << std::endl;

        // Randomly assign person to a random party
        size_t iterPerson = 0;

        while(1)
        {
            if(iterPerson == MAX_PEOPLE)
                break;

            // Get the person by a random index 0-399
            size_t person = (rand() % MAX_PEOPLE);

            // Get a random party 1-2
            size_t party = (rand() % 2 + 1);

            // For the first round...
            if( d == 0 )
            {
                // ...check if person was already assigned to a party
                if( people[person] > 0 ) continue;

                // Assign party to person
                people[person] = party;

            } else {

                // Wraparound
                int left = (person-1);
                int right = (person+1);
                int upper = (person-WRAPAROUND);
                int lower = (person+WRAPAROUND);

                // Fallback (init with persons current party)
                int persuader = person;

                // Check whether neighbor prefers a different party
                if( withinBounds(left, MAX_PEOPLE-1) && people[left] != people[person] )
                {
                    persuader = persuade(person, left);
                }
                else if( withinBounds(right, MAX_PEOPLE-1) && people[right] != people[person] )
                {
                    persuader = persuade(person, right);
                }
                else if( withinBounds(upper, MAX_PEOPLE-1) && people[upper] != people[person] )
                {
                    persuader = persuade(person, upper);
                }
                else if( withinBounds(lower, MAX_PEOPLE-1) && people[lower] != people[person] )
                {
                    persuader = persuade(person, lower);
                }
				
				// Persuader bounds check
                if(!withinBounds(persuader, MAX_PEOPLE-1))
                {
                    std::cout << "PROBLEM: PERSUADER NOT WITHIN BOUNDS! " << persuader << std::endl;
                    system("pause");
                }

                // Assign party of persuader to current person
                people[person] = people[persuader];
                break; // no break = let all people talk each round
                       // break = let one person talk per round

            }

            iterPerson++;
        }

        draw( people );
    }

    std::cout << std::endl << std::endl << "End of program" << std::endl;
    return a.exec();
}





