#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include "structure.h"



// fonction qui verifie si une date a ete saisie correctement
 int valid_date(date date)
{
    int is_valid = 1, is_leap = 0;

    if (date.an >= 1800 && date.an <= 9999)
    {

        //  check whether year is a leap year
        if ((date.an % 4 == 0 && date.an % 100 != 0) || (date.an % 400 == 0))
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(date.mois >= 1 && date.mois <= 12)
        {
            // check for days in feb
            if (date.mois == 2)
            {
                if (is_leap && date.jour == 29)
                {
                    is_valid = 1;
                }
                else if(date.jour > 28)
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (date.mois == 4 || date.mois == 6 || date.mois == 9 || date.mois == 11)
            {
                if (date.jour > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(date.jour > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}

// fonction qui compare 2 dates , retourne 1 si la 1ere est anterieure a la 2eme , 0 sinon
int precede(date d1, date d2)
    {
        int a1=d1.an, m1=d1.mois, j1=d1.jour;
        int a2=d2.an, m2=d2.mois, j2=d2.jour;
        int resultat=1;

        if (a1>a2) resultat=0;
        if (a1==a2)
            { if (m1>m2) resultat=0;
              if (m1==m2)
                  {if (j1>=j2) resultat=0;}
            }
        return resultat;
    }
// fonction qui affecte la date du jour  a un tableau de caracteres
void current_date( char current[10] )
 {

    time_t timestamp = time( NULL );
    struct tm * pTime = localtime( & timestamp );


    strftime( current,11, "%d/%m/%Y", pTime );


    return 0;
}


