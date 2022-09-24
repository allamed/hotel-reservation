#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "client.h"
#define max_clients 100
#include "main.h"

void gerer_client()
{
    int choix=0,choix2;
   do { printf("\n\n ******************* GESTION DES CLIENTS *******************\n\n\n");
        printf("   1  :  Afficher les clients \n   2  :  Ajouter un client\n   3  :  supprimer un client\n   4  :  afficher les informations d'un client \n   5  :  Retourner a la page d'accueil\n\n veuiller taper le numero correspondant a votre choix\n  ");
        scanf("%d",&choix);
         if (choix!=1&&choix!=2&&choix!=3&&choix!=4&&choix!=5) printf("veuillez entrer un choix valide");
      }while (choix!=1&&choix!=2&&choix!=3&&choix!=4&&choix!=5);
    if(choix==1) { system("cls"); afficher_client ();}
    if(choix==2) { system("cls"); ajouter_client ();}
    if(choix==3)
      {int n,existe;
            client cl;

       do { system("cls");

            printf("\n\n Entrer le numero du client a supprimer\n");
            scanf("%d",&n);
            existe=rechercher_client(n,&cl);
             if(!existe)
                {
                    printf("\n il n' y a pas de client sous le numero %d\n",n);
                    do  {
                        printf("\n\n   1  : essayer avec un autre numero \n\n   2  : retour au menu clients\n");
                        scanf("%d",&choix);
                        if (choix==2) { system("cls");gerer_client();}

                        if (choix!=1&&choix!=2) printf("veuillez entrer un choix valide");
                        } while (choix!=1&&choix!=2);}
             else
                 {printf("|    no client    |      Nom     |      Prenom      |        GSM           |       Ville    \n");
                 printf("=============================================================================================\n");
                    {printf("|       %d              %s             %s              %ld            %s   \n",cl.n_client,cl.nom,cl.prenom,cl.tel,cl.ville );
                 printf("---------------------------------------------------------------------------------------------\n");}
                 do  {
                        printf("\n\n  1  : confirmer la suppression de ce client\n\n   2  : retour au menu clients\n\n");
                        scanf("%d",&choix2);
                        if (choix2==1) {supprimer_client (n);system("cls"); printf ("\n\n le client numero %d a ete supprime avec succes\n\n",n); gerer_client();}
                        if (choix2==2) gerer_client ();
                        if (choix2!=1&&choix2!=2) printf("veuillez entrer un choix valide");
                    }while (choix2!=1&&choix2!=2);}
        }  while (choix==1);}
    if(choix==4)
        { system("cls");
          int n,existe;
        printf("\n\n Entrer le numero du client a rechercher\n");
        scanf("%d",&n);
        client cl;
         existe=rechercher_client(n,&cl);
         if(!existe) printf("\n il n' y a pas de client sous le numero %d\n",n);
         else
         {printf("|    no client    |      Nom     |      Prenom      |        GSM           |       Ville    \n");
        printf("=============================================================================================\n");
        printf("|       %d              %s             %s              %ld            %s   \n",cl.n_client,cl.nom,cl.prenom,cl.tel,cl.ville );
        printf("---------------------------------------------------------------------------------------------\n");}
         printf("\n\n   1  :  Retourner au menu clients \n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n");
                    do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2&&choix!=3);
                    if(choix==1) {system("cls"); gerer_client();}
                    if(choix==2) {system("cls");main();}
                    if(choix==3) exit(0);}
    if(choix==5) { system("cls"); main();}


}





    void ajouter_client ()
    {   FILE* f_client;
        FILE* f1;
        client cl,cl1;
        int choix=0;
        printf("\n \n  entrer les informations du client\n");
        fflush(stdin);
        printf("\n entrer le nom du client\n");
        gets(cl.nom);
        fflush(stdin);
        printf("\n entrer le prénom du client\n");
        gets(cl.prenom);
        fflush(stdin);
        printf("\n entrer le numéro de telephone du client\n");
        scanf("%ld",&cl.tel);
        fflush(stdin);
        printf("\n entrer la ville d'appartenance du client \n\n");
        gets(cl.ville);
        fflush(stdin);
            // le num client va etre incremente automatiquement
            int compteur_client;
                        FILE* f_compt_r=fopen("compteur_client.txt", "r");
                        fscanf(f_compt_r,"%d",&compteur_client);
                        fclose(f_compt_r);
                        FILE* f_compt_w=fopen("compteur_client.txt", "w");
                        compteur_client++;
                        fprintf(f_compt_w,"%d", compteur_client);
                        fclose(f_compt_w);
            cl.n_client=compteur_client;

            f_client=fopen("fichier_client.txt","a");

            int effectuee=fprintf(f_client,"%d %s %s %ld %s\n",cl.n_client,cl.nom,cl.prenom,cl.tel,cl.ville);
             fclose(f_client);
                 if (effectuee>0)
               {
                        system("cls");

                printf("\n  L'inscription a ete effectuee avec succees\n\n   1  :  Inscrire un autre client\n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n");
                    do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2&&choix!=3);
                    if(choix==1) {system("cls"); ajouter_client();}
                    if(choix==2) {system("cls");main();}
                    if(choix==3) exit(0);
                }

            else printf("il y a eu une erreur pendant l'inscription du client");


    }


void supprimer_client(int n )
{
    int i=0,j,k;
    client cl1[max_clients];
    FILE* f_client=fopen("fichier_client.txt","r");
    while(!feof(f_client))
    {
        fscanf(f_client,"%d %s %s %ld %s\n",&cl1[i].n_client,cl1[i].nom,cl1[i].prenom,&cl1[i].tel,cl1[i].ville);
        i++;
    } fclose(f_client);
    for(j=0;j<i;j++) { if (cl1[j].n_client==n) break;}

    FILE* f_client_w=fopen("fichier_client.txt","w");
    fclose(f_client_w);
    FILE* f_client_a=fopen("fichier_client.txt","a");
    for(k=0;k<j;k++) fprintf(f_client_a,"%d %s %s %ld %s\n",cl1[k].n_client,cl1[k].nom,cl1[k].prenom,cl1[k].tel,cl1[k].ville);
    for(k=j+1;k<i;k++) fprintf(f_client_a,"%d %s %s %ld %s\n",cl1[k].n_client,cl1[k].nom,cl1[k].prenom,cl1[k].tel,cl1[k].ville);
    fclose(f_client_a);





}
void afficher_client()
{
    int i=0,j,choix;
    client cl1[max_clients];
    FILE* f_client=fopen("fichier_client.txt","r");
    while(!feof(f_client))
    {
        fscanf(f_client,"%d %s %s %ld %s\n",&cl1[i].n_client,cl1[i].nom,cl1[i].prenom,&cl1[i].tel,cl1[i].ville);
        i++;
    } fclose(f_client);
     system("cls");
        printf("\n\n*********************************LISTE DES CLIENTS**************************************\n\n");
             printf("|    no client    |      Nom     |      Prenom      |        GSM           |       Ville    \n");
        printf("=============================================================================================\n");
        for(j=0;j<i;j++)
            {printf("|       %d              %s             %s              0%ld            %s   \n",cl1[j].n_client,cl1[j].nom,cl1[j].prenom,cl1[j].tel,cl1[j].ville );
        printf("---------------------------------------------------------------------------------------------\n");}

        printf("\n\n   1  :  Retourner au menu clients \n\n   2  :  Retourner a la page d'accueil\n\n   3  :  EXIT\n\n");
                    do {printf("   veuiller taper le numero correspondant a votre choix\n ");
                        scanf("%d",&choix);
                        if (choix!=1&&choix!=2&&choix!=3) printf("veuillez entrer un choix valide");
                       }while (choix!=1&&choix!=2&&choix!=3);
                    if(choix==1) {system("cls"); gerer_client();}
                    if(choix==2) {system("cls");main();}
                    if(choix==3) exit(0);
}

int rechercher_client(int n,client *cl)
{
       int i=0,j,existe=0;
    client cl1[max_clients];
    FILE* f_client=fopen("fichier_client.txt","r");
    while(!feof(f_client))
    {
        fscanf(f_client,"%d %s %s %ld %s\n",&cl1[i].n_client,cl1[i].nom,cl1[i].prenom,&cl1[i].tel,cl1[i].ville);
        i++;
    } fclose(f_client);
    for(j=0;j<i;j++)
    {if (cl1[j].n_client==n)
        { existe=1;
        *cl=cl1[j];
            break;}
    }
    return (existe);
}

