#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
#include <time.h>





typedef struct date date;
struct date {
	int jour;
	int mois;
	int an;
};


typedef struct reserv res;
struct reserv
    {   int n_res;
        char d_res[10]; // la date de reservation ( à ne pas confondre avec d_debut et d_fin)
        int n_client;
        date d_debut;
        date d_fin;
        int n_ch; //le numero de la chambre a reserver
        int annule; // prend 1 si la reservation a ete annulee, 0 sinon
    };

typedef struct client client;
struct client
    {
        int n_client;
        char nom[30] ;
        char prenom[30];
        long tel;
        char ville[20];
        //int n_ch;
        //char action[50];
    };

    typedef struct{
    int num;
    int etage;
    int prix;
    char type[50];
    //char etatdereservation[80];
    //char description[80];
}chambre;


#endif // G_H_INCLUDED
