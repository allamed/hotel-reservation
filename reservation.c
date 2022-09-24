#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "reservation.h"
#include "structure.h"
#include "client.h"
#define max_reservations 100
#define max_clients 100
#define max_chambres 100
#include "chambre.h"
#include "main.h"
// ce fichier comprend 4 fonctions: gestion reservations,afficher reservation ajouter reservation et annuler reservation
//fonction gestion des reservations
void gerer_reservation ()
{
    int choix=0;
   do { printf("\n\n ******************* GESTION DES RESERVATION *******************\n\n\n");
        printf("   1  :  Afficher les reservations \n\n   2  :  Ajouter une reservation\n\n   3  :  Annuler une reservation \n\n  4  :  Retour au menu principal \n\n  Veuiller taper le numero correspondant a votre choix\n  ");
        scanf("%d",&choix);
         if (choix!=1&&choix!=2&&choix!=3&&choix!=4) printf("veuillez entrer un choix valide");
      }while (choix!=1&&choix!=2&&choix!=3&&choix!=4);
    if(choix==1) { system("cls"); afficher_reservation ();}
    if(choix==2) { system("cls"); ajouter_reservation ();}
    if(choix==3) { system("cls"); annuler_reservation ();}
    if(choix==4) { system("cls"); main ();}

}

// fonction afficher les reservations
void afficher_reservation ()
{   int choix=0;
    do {printf("\n  Afficher toutes les reservations  :  1 \n\n  Afficher les reservations d'une periode precise  :  2\n\n  Veuillez taper le numero correspondant a votre choix \n");
        scanf("%d", &choix);
        if (choix!=1&&choix!=2) printf("\n Veuillez entrer un choix valide");
        }while (choix!=1&&choix!=2);
    if (choix == 1)
    //afficher toutes les reservations
        {
        FILE* f_res=fopen("fichier_res.txt", "r");
        res rf[max_reservations];
        int i=0,j;
        while(!feof(f_res))
        { fscanf(f_res,"%d %s %d %d %d %d %d %d %d %d %d\n",&rf[i].n_res, rf[i].d_res, &rf[i].n_client, &rf[i].d_debut.jour,&rf[i].d_debut.mois, &rf[i].d_debut.an,&rf[i].d_fin.jour,&rf[i].d_fin.mois, &rf[i].d_fin.an, &rf[i].n_ch,&rf[i].annule);
        i++;
        }
        fclose(f_res);
        system("cls");
        printf("\n\n*********************************LISTE DES RESERVATIONS**************************************\n\n");
        printf("| no reservation | date reservation | no client | date entree  |  date depart  |   no chambre \n");
        printf("=============================================================================================\n");
        for(j=0;j<i;j++)
            if (!rf[j].annule) {printf("        %d             %s          %d         %d/%d/%d        %d/%d/%d            %d     \n",rf[j].n_res,rf[j].d_res, rf[j].n_client, rf[j].d_debut.jour,rf[j].d_debut.mois, rf[j].d_debut.an,rf[j].d_fin.jour,rf[j].d_fin.mois, rf[j].d_fin.an, rf[j].n_ch );
        printf("---------------------------------------------------------------------------------------------\n");}

        }
    if (choix==2)//afficher les reservations d'une periode precise
        { date d1,d2;
          system("cls");
            do{

                printf("\n  Entrer la date debut de la periode des reservations a afficher\n Jour: ");
                scanf ("%d",&d1.jour);
                printf("\n Mois (en chiffres) : ");
                scanf ("%d",&d1.mois);
                printf("\n Annee : ");
                scanf ("%d",&d1.an);

                if (valid_date(d1)!=1) printf("\n La date n'est pas valide \n ");
                } while (valid_date(d1)!=1);
           do{
                printf("\n Entrer la date de fin de periode des reservations a afficher \n Jour: ");
                scanf ("%d",&d2.jour);
                printf("\n Mois (en chiffres) : ");
                scanf ("%d",&d2.mois);
                printf("\n Annee : ");
                scanf ("%d",&d2.an);
                if (valid_date(d2)!=1) printf("\n La date n'est pas valide \n ");
                if (precede(d2,d1)) printf("\n La date de fin de periode doit etre posterieure a la date de debut\n");
                } while (valid_date(d2)!=1 || precede(d2,d1));
            FILE* f_res=fopen("fichier_res.txt", "r");
            res rf[max_reservations];
            int i=0,j;
            while(!feof(f_res))
            { fscanf(f_res,"%d %s %d %d %d %d %d %d %d %d %d\n",&rf[i].n_res, rf[i].d_res, &rf[i].n_client, &rf[i].d_debut.jour,&rf[i].d_debut.mois, &rf[i].d_debut.an,&rf[i].d_fin.jour,&rf[i].d_fin.mois, &rf[i].d_fin.an, &rf[i].n_ch,&rf[i].annule);
            i++;
            }
            fclose(f_res);
            system("cls");
            printf("********************LISTE DES RESERVATIONS ENTRE LE %d/%d/%d ET %d/%d/%d********************\n\n",d1.jour, d1.mois, d1.an, d2.jour, d2.mois, d2.an);
            printf("| no reservation | date reservation | no client | date entree  |  date depart  |   no chambre \n");
            printf("=============================================================================================\n");
            int c=0;
            for(j=0;j<i;j++)
                {
                    if(precede(d1,rf[j].d_debut)&& precede(rf[j].d_debut,d2)&&(!rf[j].annule))
                    { printf("        %d             %s          %d         %d/%d/%d        %d/%d/%d           %d     \n",rf[j].n_res,rf[j].d_res, rf[j].n_client, rf[j].d_debut.jour,rf[j].d_debut.mois, rf[j].d_debut.an,rf[j].d_fin.jour,rf[j].d_fin.mois, rf[j].d_fin.an, rf[j].n_ch );
                      printf("---------------------------------------------------------------------------------------------\n");c++;
                    }

                }if (!c) { system("cls");
                            printf("********************LISTE DES RESERVATIONS ENTRE LE %d/%d/%d ET %d/%d/%d********************\n\n",d1.jour, d1.mois, d1.an, d2.jour, d2.mois, d2.an);
                            printf("\n\n  Il n ya pas eu de reservation dans cette periode\n");
                         }


        }
         printf("\n\n   1  :  Retourner au menu reservation\n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n");
        do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2&&choix!=3);
                    if(choix==1) { system("cls"); gerer_reservation();}
                    if(choix==2) { system("cls");main();}
                    if(choix==3) { system("cls"); printf(" AU REVOIR"); exit(0);}







}


// fonction ajouter reservation
     void ajouter_reservation()
    {
        res r;
        int i,j;//compteurs
        int libre,choix=0;
        int present=0;
        system("cls");
        printf("\n\n ******* AJOUTER UNE RESERVATION *******\n\n\n");

       do{ printf("   1  :  Reserver pour un client deja inscrit \n   2  :  inscrire un client\n   \n\n veuiller taper le numero correspondant a votre choix\n  ");
        scanf("%d",&choix);
         if (choix!=1&&choix!=2) printf("veuillez entrer un choix valide");
      }while (choix!=1&&choix!=2);

    if(choix==2) { system("cls"); ajouter_client ();}
    if(choix==1)
        {

           do {
                printf("\n \n   Entrer le numero du client\n");
                scanf("%d",&r.n_client);
                // maintenant on doit vérifier si le Num client saisi figure dans la liste client
                FILE* f_client=fopen("fichier_client.txt", "r");
                client cl[max_clients];
                i=0;
                while(!feof(f_client))
                    { fscanf(f_client,"%d %s %s %ld %s\n",&cl[i].n_client,cl[i].nom,cl[i].prenom, &cl[i].tel, cl[i].ville);
                    i++;
                    }
                    fclose(f_client);
                // verification
                // 'present' indique si le client est present dans la liste des clients
                for(j=0;j<i;j++)
                    if (cl[j].n_client==r.n_client) present=1;
                if (!present)

                       printf("  Ce client ne figure pas dans la liste de client \n ");




               } while (!present);


                do{

                    printf("\n  entrer la date d'entree \n jour: ");
                    scanf ("%d",&r.d_debut.jour);
                    printf("  mois (en chiffres) : ");
                    scanf ("%d",&r.d_debut.mois);
                    printf("  annee : ");
                    scanf ("%d",&r.d_debut.an);

                    if (valid_date(r.d_debut)!=1) printf("\n  la date n'est pas valide \n ");
                    } while (valid_date(r.d_debut)!=1);



               do{

                    printf("\n  entrer la date de fin de sejour \n jour: ");
                    scanf ("%d",&r.d_fin.jour);
                    printf("  mois (en chiffres) : ");
                    scanf ("%d",&r.d_fin.mois);
                    printf("  annee : ");
                    scanf ("%d",&r.d_fin.an);

                    if (valid_date(r.d_fin)!=1) printf("\n  la date n'est pas valide \n ");
                    if (precede(r.d_fin,r.d_debut)) printf("\n  la date de fin de sejour doit etre posterieure a la date d'entree\n");
                    } while (valid_date(r.d_fin)!=1 || precede(r.d_fin,r.d_debut));

                chambre ch;
               do {
                        do {
                            printf("  entrer le numero de la chambre a reserver\n");
                            scanf("%d",&r.n_ch);

                            if(!rechercher_chambre(r.n_ch,&ch))
                                   printf("\n  il n'y a pas de chambre avec ce numero , veuiller réessayer  \n ");
                           } while (!rechercher_chambre(r.n_ch,&ch));

                       //maintenant on doit verifier si la chambre est libre dans la periode entre d_debut et d_fin


                        FILE* f_res=fopen("fichier_res.txt", "r");
                        res rf[max_reservations];//pour y inserer le contenu du fichier res , je l'ai nommé rf pour ne pas le confondre a r qui correspond a la reservation en cours
                        i=0;
                        while(!feof(f_res))
                            { fscanf(f_res,"%d %s %d %d %d %d %d %d %d %d %d\n",&rf[i].n_res,rf[i].d_res, &rf[i].n_client, &rf[i].d_debut.jour,&rf[i].d_debut.mois, &rf[i].d_debut.an,&rf[i].d_fin.jour,&rf[i].d_fin.mois, &rf[i].d_fin.an, &rf[i].n_ch,&rf[i].annule);
                            i++;
                            }

                        fclose(f_res);
                        libre=1; //la chambre est par defaut libre

                        for(j=i-1;j>=0;j--)// on parcours les reservations de la fin vers le debut pour commencer par les reservations les plus recentes , c'est plus optimal en terme de nombre d'operation
                           {if (rf[j].n_ch==r.n_ch && precede(rf[j].d_debut, r.d_fin)&& precede(r.d_debut, rf[j].d_fin) &&(!rf[j].annule) )
                                {libre=0;//si la periode de reservation courante interfere avec une reservation anterieure, la chambre n'est pas li
                                break;}
                            }
                        if(!libre) printf("\n  cette chambre n'est pas libre pour la date indiquee, veuillez choisir une autre chambre\n");
               } while (!libre);
                //afficher les informations saisies
                system("cls");
                printf("\n veuillez verifier vos informations\n numero client: %d\n date d'entree : %d/%d/%d \n date de depart : %d/%d/%d \n numero de chambre : %d\n ",r.n_client,r.d_debut.jour,r.d_debut.mois, r.d_debut.an, r.d_fin.jour,r.d_fin.mois, r.d_fin.an, r.n_ch);
                int confirmation=0;
                printf("\n  taper 1 pour confirmer la reservation\n");
                scanf("%d",&confirmation);
                if (confirmation)
                    {   current_date(r.d_res);

                        int compteur_res;
                        FILE* f_compt_r=fopen("compteur_res.txt", "r");
                        fscanf(f_compt_r,"%d",&compteur_res);
                        fclose(f_compt_r);
                        FILE* f_compt_w=fopen("compteur_res.txt", "w");
                        compteur_res++;
                        fprintf(f_compt_w,"%d", compteur_res);
                        fclose(f_compt_w);
                        FILE* f_res=fopen("fichier_res.txt", "a");
                        fprintf(f_res,"\n%d %s %d %d %d %d %d %d %d %d %d",compteur_res,r.d_res, r.n_client, r.d_debut.jour,r.d_debut.mois, r.d_debut.an,r.d_fin.jour,r.d_fin.mois, r.d_fin.an, r.n_ch,0);
                        fclose(f_res);
                        int choix=0;
                        system("cls");
                        printf("\n  votre reservation a bien ete enregistree\n\n   1  :  Ajouter une autre reservation\n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n");
                        do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                            scanf("%d",&choix);
                            if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                           }while (choix!=1&&choix!=2&&choix!=3);
                        if(choix==1) ajouter_reservation();
                        if(choix==2) main();
                        if(choix==3) exit(0);
                    }

    }}
    void annuler_reservation()
    {
        int nr, existe=0,confirmation=0, choix=0;
        int i,j;//compteurs
        res rf[max_reservations];
        printf("\n\n ******* ANNULER UNE RESERVATION *******\n\n\n");

       do {
            printf("  Entrer le numero de la reservation a annuler\n");
            scanf("%d",&nr);

             FILE* f_res=fopen("fichier_res.txt", "r");

                    i=0;
                    while(!feof(f_res))
                        { fscanf(f_res,"%d %s %d %d %d %d %d %d %d %d %d\n",&rf[i].n_res,rf[i].d_res, &rf[i].n_client, &rf[i].d_debut.jour,&rf[i].d_debut.mois, &rf[i].d_debut.an,&rf[i].d_fin.jour,&rf[i].d_fin.mois, &rf[i].d_fin.an, &rf[i].n_ch,&rf[i].annule);
                        i++;
                        }

            fclose(f_res);


                    for(j=0;j<i;j++)
                       {if (rf[j].n_res== nr )
                            {existe++;//la reservation existe
                            rf[j].annule=1;
                            break;}
                        }
                    if(!existe) printf("\n il n' y a pas de reservation avec ce numero\n");
           } while (!existe);
            printf("| no reservation | date reservation | no client | date entree  |  date depart  | no chambre |\n");
            printf("=============================================================================================\n");
            printf("|       %d        |    %s    |    %d    |   %d/%d/%d   |    %d/%d/%d   |     %d     |\n",rf[j].n_res,rf[j].d_res, rf[j].n_client, rf[j].d_debut.jour,rf[j].d_debut.mois, rf[j].d_debut.an,rf[j].d_fin.jour,rf[j].d_fin.mois, rf[j].d_fin.an, rf[j].n_ch );
            printf("---------------------------------------------------------------------------------------------\n");
           printf("\n \n   1  :  Annuler cette reservation  \n\n  2  :  Retour au menu principal ");
           scanf("%d",&confirmation);
           if(confirmation==2) { system("cls"); main();}
           if(confirmation==1)
               {
                    FILE* f_res=fopen("fichier_res.txt", "w");
               int effectuee;
               for(j=0;j<i;j++)
               effectuee=fprintf(f_res,"%d %s %d %d %d %d %d %d %d %d %d\n",rf[j].n_res,rf[j].d_res, rf[j].n_client, rf[j].d_debut.jour,rf[j].d_debut.mois, rf[j].d_debut.an,rf[j].d_fin.jour,rf[j].d_fin.mois, rf[j].d_fin.an, rf[j].n_ch,rf[j].annule);
               fclose(f_res);
               if (effectuee>0)
               {
                        system("cls");
                printf("\n  La reservation numero : %d a bien ete annulee\n\n   1  :  Annuler une autre reservation\n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n",nr);
                    do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2&&choix!=3);
                    if(choix==1) {system("cls"); annuler_reservation();}
                    if(choix==2) {system("cls");main();}
                    if(choix==3) exit(0);}


               else

                {system("cls");
                    printf("il y a eu une erreur pendant l'annulation de cette reservation");
                printf("\n \n   1  :  Retourner a la page d'accueil\n\n   2  :  EXIT\n\n");
                    do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2);
                    system("cls");
                    if(choix==1) { system("cls"); main();}
                    if(choix==2) exit(0);
                }
                }





    }
