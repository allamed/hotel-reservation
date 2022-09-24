#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "client.h"
#include "reservation.h"
#include "date.h"
#include "chambre.h"



int main()

{
    int choix=0;
    printf("\n\n ************************* ACCUEIL ****************************");
    do {printf("\n\n\n  1  :  GESTION DES RESERVATIONS\n\n");
        printf("\n  2  :  GESTION DES CLIENTS\n\n");
        printf("\n  3  :  GESTION DES CHAMBRES\n\n");
        printf("\n  4  :  GESTION DU PARKING\n\n\n");
        printf("   veuiller taper le numero correspondant a votre choix\n ");
        scanf("%d",&choix);
        if (choix!=1&&choix!=2&&choix!=3&&choix!=4) printf("veuillez entrer un choix valide");
        }while (choix!=1&&choix!=2&&choix!=3&&choix!=4);
    if (choix==1) { system("cls"); gerer_reservation();}
    if (choix==2) { system("cls"); gerer_client(); }
    if (choix==3){ system("cls"); gerer_chambre();}
    if (choix==4){ system("cls"); gerer_parking();}

}



// gestion du parking
#include <conio.h>
#include <windows.h>
#define Voiture 1
#define MOTO 2



struct vehicule
{
	int num ;
	int lig ; /*lignes */
	int col ; /*colonnes */
    int type ;
    struct tm *at;

} ;

struct vehicule *voiture[2][10] ;
	struct vehicule *moto[2][10] ;
int parkinfo[4][10] ;   /* tableau de 2 dimensions pour le comptage de nombre total des véhicules */
int vehiculecompt ;    /* compter le nombre total des véhicules */
int voiturecompt ;	   /* compter le nombre de voitures */
int motocompt ;       /* compter le nombre de motos */


void affichage( ) ;
void changecol ( struct vehicule * ) ;
struct vehicule * add ( int, int, int, int ) ;
void del ( struct vehicule * ) ;
void obtenirligcol ( int, int * ) ;
void getrcbyinfo ( int, int, int * ) ;
void show() ;
int randint();
int backupw();
int backupr();
struct vehicule * addonstart ( int, int, int, int ) ;
void facture_totale(int ,struct tm *ct1,struct tm *ct2);
void temps_arrivee(int);


void changecol ( struct vehicule *v )
{
	v -> col--;
}

struct tm* date_heure()
  {

        time_t ts;
        struct tm *ct;

        ts = time(NULL);
        ct = localtime(&ts);
        return ct ;

  }

int inserer_enregis(int veh,int type,int lig,int col, struct tm *ct )
 {
    FILE *fptr;
    fptr = fopen("date.arrivee", "a");

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas . \n");
        return 0 ;
    }

    fprintf(fptr,"\n");
    fprintf(fptr,"%d ",veh);
    fprintf(fptr,"%d ",type);
    fprintf(fptr,"%d ",lig);
    fprintf(fptr,"%d ",col);

    fprintf(fptr,"%d/%d/%d  ",
                              ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900);

   fprintf(fptr,"%d:%d:%d  ",
                ct->tm_hour, ct->tm_min, ct->tm_sec);



        fclose(fptr);

  }


int inserer_enregis2(int veh, struct tm *ct )
  {
    FILE *fptr;
    fptr = fopen("date.depart", "a");

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas . \n");
        return 0 ;
    }

    fprintf(fptr,"\n");
    fprintf(fptr,"%d ",veh);


         fprintf(fptr,"%d/%d/%d  ",
                ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900);

   fprintf(fptr,"%d:%d:%d  ",
                ct->tm_hour, ct->tm_min, ct->tm_sec);



        fclose(fptr);
  }


void heure_arrivee(int num)
{


    int veh ,type,lig,col ;
    int mois,jour,annee,hour,min,sec;
    int mois2,jour2,annee2,hour2,min2,sec2;

    int mois1,jour1,annee1,hour1,min1,sec1;
    int mois3,jour3,annee3,hour3,min3,sec3;

    FILE *fptr;
    fptr = fopen("date.arrivee", "r");

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas \n");
        return 0 ;
    }

 while(!feof(fptr))
 {
     fscanf(fptr,"\n");
     fscanf(fptr,"%d ",&veh);
        fscanf(fptr,"%d ",&type);
       fscanf(fptr,"%d ",&lig);
        fscanf(fptr,"%d ",&col);
    fscanf(fptr,"%d/%d/%d  ",
                &jour, &mois, &annee);

   fscanf(fptr,"%d:%d:%d  ",
                &hour, &min, &sec);

   if(veh == num)
   {
     jour2 = jour;
     mois2 = mois;
     annee2 = annee;
     hour2 = hour;
     min2 = min;
     sec2 = sec ;

    }


 }


 fclose(fptr);


 FILE *fptr1;
    fptr1 = fopen("date.depart", "r");

    if (fptr1 == NULL)
    {
        printf(" Le fichier n'existe pas . \n");
        return 0 ;
    }

 while(!feof(fptr1))

 {
     fscanf(fptr1,"\n");
     fscanf(fptr1,"%d ",&veh);

     fscanf(fptr1,"%d/%d/%d  ",
                &jour1, &mois1, &annee1);

     fscanf(fptr1,"%d:%d:%d  ",
                &hour1, &min1, &sec1);

   if(veh == num)
    {
     jour3 = jour1;
     mois3 = mois1;
     annee3 = annee1;
     hour3 = hour1;
     min3 = min1;
     sec3 = sec1 ;

     }
 }


 fclose(fptr1);

     int tsec1,tsec2,tsec3;
      tsec1 =  sec3;
      tsec1 += min3*60;
      tsec1 += (hour3*60)*60;
      tsec2 =  sec2;
      tsec2 += min2*60;
      tsec2 += (hour2*60)*60;

   tsec3 = tsec1 - tsec2 ;
   int secnd , minute ,hours;
   int secc , temp1,temp2,temp3,temp4 ;
       secnd = tsec3 % 60 ;
       temp1 = tsec3 - secnd ;
       temp2 = temp1/60 ;
       minute = temp2 % 60 ;
       temp4 = temp2 - minute ;
       hours = temp4 /60 ;

     printf(" Vous avez garé votre vehicule pendant : %d/%d/%d",hours,minute,secnd);

}


int randint()
{
    int r ;
    srand(time(NULL));
    r = rand() % 20;
    return r ;
}

void feuille(int veh,int type,int lig,int col, struct tm *ct)
{

FILE *fptr;
    fptr = fopen("date.feuille", "a");

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas .\n");
        return 0 ;
    }

    fprintf(fptr,"\n");
    fprintf(fptr,"%d ",veh);
        fprintf(fptr,"%d ",type);
        fprintf(fptr,"%d ",lig);
        fprintf(fptr,"%d ",col);

        fprintf(fptr,"%d/%d/%d  ",
                ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900);

   fprintf(fptr,"%d:%d:%d  ",
                ct->tm_hour, ct->tm_min, ct->tm_sec);
   fprintf(fptr,"%d ",50);


   fclose(fptr);


}

int historique_enregis(int val)
{
  FILE *fptr;
  if(val==1)
  fptr = fopen("date.arrivee", "r");
  else if(val ==2)
  fptr = fopen("date.depart", "r");
  else if(val==3)
  fptr = fopen("date.feuille", "r");
  else
 {printf(" Données invalides ! ");
  return 0 ;}

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas . \n");
        return 0 ;
    }

 char strg;
 strg = getc(fptr);

 while(!feof(fptr))
 {
	printf("%c",strg);
    strg = getc(fptr);
 }
   return 0 ;
 }

int backupw()
{
    int r,c ;

    FILE *fptr;
    fptr = fopen("backupwr.dat", "w");

    if (fptr == NULL)
    {
        printf(" Le fichier n'existe pas. \n");
        return 0 ;
    }


  for(r=0;r<4;r++)
   for(c=0;c<10;c++)
    {

    fprintf(fptr,"\n");
    fprintf(fptr,"%d ",parkinfo[r][c]);

        fprintf(fptr,"%d ",r);
        fprintf(fptr,"%d ",c);

         fprintf(fptr,"%d ",vehiculecompt);
         fprintf(fptr,"%d ",voiturecompt);
         fprintf(fptr,"%d ",motocompt);

    }
        fclose(fptr);
}

int backupr()
{
     int r,c ;
     int park[4][10];
     FILE *fptr;
     fptr = fopen("backupwr.dat", "r");
     if (fptr == NULL)
      {
        printf(" Le fichier n'existe pas . \n");
        return 0 ;
      }

 int rr ,cc ,veh,voit,mot,numb;
  for(r=0;r<4;r++)
   for(c=0;c<10;c++)
    {

    fscanf(fptr,"\n");
    fscanf(fptr,"%d ",&park[r][c]);
    numb = park[r][c];

        fscanf(fptr,"%d ",&rr);
        fscanf(fptr,"%d ",&cc);

         fscanf(fptr,"%d ",&veh);
         fscanf(fptr,"%d ",&voit);
         fscanf(fptr,"%d ",&mot);

 if(numb!=0)
 {

        	  if ( r == 0 || r == 1 )
             voiture[r][c] = addonstart(1,numb,r,c);

             else
    	     moto[r][c] = addonstart(2,numb,r,c);
 }
    }
        fclose(fptr);

}


struct vehicule * add ( int t, int num, int lig, int col )
{
    struct vehicule *v ;
    int r ;

    v = ( struct vehicule * ) malloc ( sizeof ( struct vehicule ) ) ;

    v -> type = t ;
    v -> lig = lig ;
    v -> col = col ;

	  if ( t == Voiture)
      voiturecompt++ ;
    else
    	motocompt++ ;
        vehiculecompt++ ;

	  parkinfo[lig][col] = num ;
      v->at = date_heure();
	  inserer_enregis(num,t,lig,col,date_heure());
	   backupw(t);
	  r = randint();
	  if(r < 5 )
      {
          printf("\a");
          printf("\a");
          feuille(num,t,lig,col,date_heure());

      }

    return v ;
}

struct vehicule * addonstart ( int t, int num, int lig, int col )
{
    struct vehicule *v ;
    int r ;

    v = ( struct vehicule * ) malloc ( sizeof ( struct vehicule ) ) ;

    v -> type = t ;
    v -> lig = lig ;
    v -> col = col ;

    if ( t == Voiture )
      voiturecompt++ ;
    else
      motocompt++ ;

    vehiculecompt++ ;
    parkinfo[lig][col] = num ;
    return v ;
}


void del ( struct vehicule *v )
  {
    int c ;

	parkinfo[v -> lig][v -> col] = 0 ;

	if ( v -> type == Voiture )
    voiturecompt-- ;
    else
    motocompt-- ;

	vehiculecompt-- ;
	backupw();
}


void obtenirligcol( int type, int *arr )
{
  int r, c, fromlig = 0, tolig= 2 ;

  if ( type == MOTO )
  {
    fromlig += 2 ;
    tolig += 2 ;
  }

	for ( r = fromlig ; r < tolig ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkinfo[r][c] == 0 )
			{
				arr[0] = r ;
				arr[1] = c ;
        return ;
			}
		}
	}

	if ( r == 2 || r == 4 )
	{
   	arr[0] = -1 ;
    arr[1] = -1 ;
  }
}


void getrcbyinfo ( int type, int num, int *arr )
{
  int r, c, fromlig = 0, tolig = 2 ;

  if ( type == MOTO )
	{
    fromlig += 2 ;
    tolig += 2 ;
	}

	for ( r = fromlig ; r < tolig ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkinfo[r][c] == num )
			{
				arr[0] = r ;
				arr[1] = c ;
        return ;
			}
		}
	}

	if ( r == 2 || r == 4 )
	{
		arr[0] = -1 ;
		arr[1] = -1 ;
	}
}


void affichage( )
{
  int r, c ;

  printf ( " Voitures ->\n" ) ;

  for ( r = 0 ; r < 4 ; r++ )
  {
    if ( r == 2 )
		  printf ( " Motos ->\n" ) ;

    for ( c = 0 ; c < 10 ; c++ )
      printf ( "%d\t", parkinfo[r][c] ) ;
    printf ( "\n" ) ;
	}
}

void gerer_parking()
{
	int choice, type, number, lig = 0, col = 0 ;
	int i, tarr[2] ;
	int finish = 1 ;
	backupr();
	int num_client;
	client cl;



  system ( "cls" ) ;


	while ( finish )
	{
    system ( "cls" ) ;

		printf ( "\n\n ******************* GESTION DU PARKING *******************\n\n\n" ) ;
		printf ( "  1.  Arrivée d'un véhicule .\n\n" ) ;
		printf ( "  2.  Le nombre total des Véhicules garés .\n\n" ) ;
		printf ( "  3.  Le nombre total des Voitures garées .\n\n" ) ;
		printf ( "  4.  Le nombre total des Motos garées .\n\n" ) ;
		printf ( "  5.  Afficher l'ordre de garage des véhicules .\n\n" ) ;
		printf ( "  6.  Départ d'un véhicule .\n\n" ) ;
		printf ( "  7.  Voir l'historique .\n\n" ) ;
		printf ( "  8.  Quitter \n\n" ) ;

		scanf ( "%d", &choice ) ;

		switch ( choice )
		{
			case 1 :
          system ( "cls" ) ;
				  printf ( "\n Ajouter : \n" ) ;

          type = 0 ;
          do { printf ("\n  Entrer le numero du client titulaire du vehicule\n");
          scanf("%d",&num_client);
          if (!rechercher_client(num_client,&cl)) printf("\n  Il n'y a pas de client sous ce numero\n");
          } while (!rechercher_client(num_client,&cl));
          while ( type != Voiture && type != MOTO )
          {
            printf ( " Entrer un véhicule (1 dans le cas d'une Voiture / 2 dans le cas d'une MOTO ): \n" ) ;
            scanf ( "%d", &type ) ;
            if ( type != Voiture && type != MOTO )
                printf ( "\n Type de véhicule invalide !\n" ) ;
          }

				  printf ( " Entrer le numéro d'immatriculation du véhicule : " ) ;
				  scanf ( "%d", &number ) ;

				  if ( type == Voiture || type == MOTO )
				  {
					  obtenirligcol ( type, tarr ) ;

					  if ( tarr[0] != -1 && tarr[1] != -1 )
					  {
						  lig = tarr[0] ;
						  col = tarr[1] ;

              if ( type == Voiture )
                voiture[lig][col] =  add ( type, number, lig, col ) ;
              else
							  moto[lig - 2][col] = add ( type, number, lig, col ) ; ;
            }
              else
            {

              if ( type == Voiture )
                printf ( "\n Désolé, pas de place disponible pour garer une Voiture ! \n" ) ;
              else
                printf ( "\n Désolé, pas de place disponible pour garer une Moto !\n" ) ;

            }
          }
				  else
				  {
            printf ( " Type invalide !! \n" ) ;
					  break ;
          }

          printf ( "\n Appuyez sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

      case 2 :
          system ( "cls" ) ;
				  printf ( " Le nombre total des véhicules garés est : %d\n", vehiculecompt ) ;
          printf ( "\n Appuyez sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

			case 3 :
          system ( "cls" ) ;
				  printf ( " Le total des voitures garées : %d\n", voiturecompt ) ;
          printf ( "\n Appuyez sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

			case 4 :
          system ( "cls" ) ;
				  printf ( " Total des Motos garées : %d\n", motocompt ) ;
          printf ( "\n Appuyez sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

			case 5 :
          system ( "cls" ) ;
				  printf ( " Afficher \n" ) ;
				  affichage( ) ;
          printf ( "\n Appuyez sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

			case 6 :
          system ( "cls" ) ;
				  printf ( " Le Départ\n" ) ;
          type = 0 ;

          while ( type != Voiture && type != MOTO )
          {
					  printf ( " Entrer le type de véhicule (1 pour une voiture / 2 pour une moto ): \n" ) ;
            scanf ( "%d", &type ) ;
	          if ( type != Voiture && type != MOTO )
						  printf ( "\n Type de véhicule invalide !\n" ) ;
          }
				  printf ( " Entrer un nombre: "  ) ;
				  scanf ( "%d", &number ) ;

  				if ( type == Voiture || type == MOTO )
	  			   {

		  			getrcbyinfo ( type, number, tarr ) ;
			  		if ( tarr[0] != -1 && tarr[1] != -1 )
				  	{
				  	    inserer_enregis2(number,date_heure());
				  	    heure_arrivee(number);
              col = tarr [1] ;

              if ( type == Voiture )
              {
                lig = tarr [0] ;
	              del ( voiture[lig][col] ) ;

				                    for ( i = col ; i < 9 ; i++ )
							  {
								  voiture[lig][i] = voiture[lig][i + 1] ;

							  }
                free ( voiture[lig][i] ) ;

					  voiture[lig][i] = NULL ;
              }

						  else
              {
                lig = tarr[0] - 2 ;
							  if ( ! ( lig < 0 ) )
							  {
								  del ( moto[lig][col] ) ;
								  for ( i = col ; i < 9 ; i++ )
								  {
									  moto[lig][i] = moto[lig][i + 1] ;

								  }
								  moto[lig][i] = NULL ;
                }
              }
            }
					  else
            {
              if ( type == Voiture )
							  printf ( "\n Numéro d'immatriculation invalide , ou la voiture ayant ce numéro est garée autre part !\n" ) ;
              else
                printf ( "\n Numéro d'immatriculation invalide , ou la Moto ayant ce numéro est garée autre part !\n" ) ;
            }
          }
          printf ( "\n Appuyer sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
				  break ;

    case 8 :

          system ( "cls" ) ;
        /*  for ( lig = 0 ; lig < 2 ; lig++ )
          {
            for ( col = 0 ; col < 10 ; col++ )
            {
              if ( voiture[lig][col] -> num != 0 )
                free ( voiture[lig][col] ) ;
              if ( moto[lig][col] -> num != 0 )
							  free ( moto[lig+2][col] ) ;
            }
          }*/
				  main() ;




				   getch();
				  break ;

    case 7 :
              system ( "cls" ) ;
     int opt ;
		printf ( " Tables d'enregistrements .\n" ) ;
  			 printf ( " Appuyer sur : 1 pour l'historique d'Arrivée .\n" ) ;
             printf ( " Appuyer sur : 2 pour l'historique de Départ .\n" ) ;
                                printf ( " Appuyer sur : 3 pour la Feuille .\n" ) ;
     			scanf ( "%d", &opt ) ;
           historique_enregis(opt);
 printf ( "\n Appuyer sur n'importe quelle touche pour continuer..." ) ;
          getch( ) ;
                break ;
    }
	}
  return 0 ;
}
















