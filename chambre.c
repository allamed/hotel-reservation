#include <stdio.h>
#include <string.h>
#include "chambre.h"
#include "structure.h"
#define max_chambres 100



void gerer_chambre()
{
    int choix,choix2,n;

    chambre ch;
    do{
        printf("\n\n ******************* GESTION DES CHAMBRES *******************\n\n");
        //printf("1.remplissage\n");
        printf("\n   1  :  afficher toutes les chambres\n\n");
        printf("   2  :  Afficher les informations d'une chambre\n\n");
        printf("   3  :  ajouter une chambre\n\n");
        printf("   4  :  supprimer une chambre \n\n");
        printf("   5  :  modifier les informations d'une chambre\n\n");
        printf("   6  :  retour au menu principal");
        printf("\n\n Veuillez taper le numero correspondant a votre choix\n\n");
        scanf("%d", &choix);
         switch(choix)
    {

        case 1://affichage
            system("cls");
            printf("\n\n  1  :  Afficher les chambre par ordre du numero de chambre \n\n  2  :  Afficher les chambre par ordre croissant des prix/nuit \n");
            scanf("%d", &choix2);
            switch(choix2)
                {
                  case 1: {afficher_chambre_par_numero(); break;}
                  case 2 : {afficher_chambre_par_prix();break;}

                }

            printf("\n");
            break;

        case 2://rechercher une chambre

            printf("\n\n  Donner le numero de la chambre a afficher\n");
            scanf("%d",&n);
            if(rechercher_chambre(n,&ch)==1)
            {

             printf("\n|    No chambre    |      Etage     |      Prix      |        Type          \n");
            printf("=============================================================================================\n");
            printf("|        %d                 %d               %d              %s                \n",ch.num,ch.etage,ch.prix,ch.type );
            printf("---------------------------------------------------------------------------------------------\n");

            }
            else printf("\n\n Il n'y a pas de chambre sous le numero %d \n",n);

            printf("\n");
            break;
        case 3:// ajouter une chambre
            if(ajouter_chambre()==1) printf("\n\n la chambre a ete ajoutee avec succes");
            else printf("la chambre n'a pas ete ajoutee");
            break;
        case 4:// supprimer chambre

            printf("\n Donner le numero de la chambre a supprimer\n ");
            scanf("%d",&n);
            printf("\n La chambre numero %d va etre definitivement suprimee de la liste des chambres \n\n  1  :  confirmer\n\n  2  :  retour au menu chambres\n",n);
            scanf("%d",&choix2);
            switch(choix2){

                            case 1:
                                if(supprimer_chambre(n)==1) { system("cls"); printf("\n \n  La chambre numero %d a ete supprimee avec succes\n",n);}
                                else { system("cls"); printf("\n \n  Il n'y a pas de chambre sous le numero %d\n",n);}
                                break;
                            case 2:
                                break;
                          }
            printf("\n");
            break;
        case 5:
            printf("\n\nDonner le numero de la chambre a modifier\n");
            scanf("%d",&n);
            modifier_chambre(n);
            printf("\n");
            break;
        case 6:
            system("cls");
            main();
    }
    }while(choix!=9);
}



void afficher_chambre_par_numero(){
    int i=0,j,k;

    chambre c[max_chambres],p;

    FILE *f;
    f=fopen("fichier_chambre.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d %d %d %s\n",&c[i].num,&c[i].etage,&c[i].prix,c[i].type);
        i++;
    }fclose(f);

    //tri par numero
     for (j=0; j<i; j++)
     {

                for(k=0;k<i-j-1;k++)
                    {
                        if(c[k].num>c[k+1].num)
                        {
                           p=c[k];
                           c[k]=c[k+1];
                           c[k+1]=p;

                        }


                    }

     }
     system("cls");
        printf("\n\n*********************************LISTE DES CHAMBRES**************************************\n\n");
             printf("|    No chambre    |      Etage     |      Prix      |        Type          \n");
        printf("=============================================================================================\n");
    for (j=0; j<i; j++){



            printf("|        %d                 %d               %d              %s                \n",c[j].num,c[j].etage,c[j]. prix,c[j]. type );
        printf("---------------------------------------------------------------------------------------------\n");


}

}

void afficher_chambre_par_prix()
{
   int i=0,j,k;

    chambre c[max_chambres],p;

    FILE *f;
    f=fopen("fichier_chambre.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d %d %d %s\n",&c[i].num,&c[i].etage,&c[i].prix,c[i].type);
        i++;
    }fclose(f);
    //tri par prix
     for (j=0; j<i; j++)
     {

                for(k=0;k<i-j-1;k++)
                    {
                        if(c[k].prix>c[k+1].prix)
                        {
                           p=c[k];
                           c[k]=c[k+1];
                           c[k+1]=p;

                        }


                    }

     }
            system("cls");
            printf("\n\n***********************LISTE DES CHAMBRES PAR ORDRE DECROISSANT DU PRIX/NUIT****************************\n\n");
             printf("|    No chambre    |      Etage     |      Prix      |        Type          \n");
            printf("=============================================================================================\n");
    for (j=0; j<i; j++){
            printf("|        %d                 %d               %d              %s                \n",c[j].num,c[j].etage,c[j]. prix,c[j]. type );
            printf("---------------------------------------------------------------------------------------------\n");}
}


int rechercher_chambre(int n,chambre *ch){

    int existe=0;
    chambre c;
    FILE* f=fopen("fichier_chambre.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d %d %d %s\n",&c.num,&c.etage,&c.prix,c.type);
        if(c.num==n)
            {
                existe=1;
                *ch=c;
                break;
            }
    } fclose(f);

  return (existe);
}


int ajouter_chambre(){
    int compt,resultat=1;
    FILE* f_compt_r=fopen("compteur_chambre.txt", "r");
    fscanf(f_compt_r,"%d",&compt);
    fclose(f_compt_r);
    compt++;
    chambre c;
    c.num =compt;
    printf("\n\n  Veuillez remplir les informations de la chambre a ajouter");
    printf("\n\n Etage de la chambre : ");
    scanf("%d",&c.etage);
    printf("\n\n Prix pour une nuit : ");
    scanf("%d",&c.prix);
    printf("\n\n Type de chambre : ");
    scanf("%s",c.type);
    FILE *f;
    f=fopen("fichier_chambre.txt","a");
    if (fprintf(f,"%d %d %d %s\n",c.num,c.etage,c.prix,c.type)<0) resultat=0;
    fclose(f);
    FILE* f_compt_w=fopen("compteur_chambre.txt", "w");
    if (fprintf(f_compt_w,"%d",compt)<0) resultat=0;
    fclose(f_compt_w);
    return(resultat);


}

int supprimer_chambre(int n){
    int i=0,j,k,existe=0;
    chambre c[max_chambres];
    FILE* f=fopen("fichier_chambre.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d %d %d %s\n",&c[i].num,&c[i].etage,&c[i].prix,c[i].type);
        i++;
    } fclose(f);
    for(j=0;j<i;j++) { if (c[j].num==n) {existe=1; break;}}
    if(existe==1)
        {
        FILE* f_w=fopen("fichier_chambre.txt","w");
        fclose(f_w);
        FILE* f_a=fopen("fichier_chambre.txt","a");
        if (j!=0)
            {
            for(k=0;k<j;k++) fprintf(f_a,"%d %d %d %s\n",c[k].num,c[k].etage,c[k].prix,c[k].type);
            if (j!=i-1) for(k=j+1;k<i;k++) fprintf(f_a,"%d %d %d %s\n",c[k].num,c[k].etage,c[k].prix,c[k].type);
        }
        else{
            if(i>1)for(k=1;k<i;k++) fprintf(f_a,"%d %d %d %s\n",c[k].num,c[k].etage,c[k].prix,c[k].type);
            }

        fclose(f_a);
        }
    return (existe);


}

void modifier_chambre(int n){
    chambre c;
    if(rechercher_chambre(n,&c)==1)
            {

             printf("\n|    No chambre    |      Etage     |      Prix      |        Type          \n");
            printf("=============================================================================================\n");
            printf("|        %d                 %d               %d              %s                \n",c.num,c.etage,c.prix,c.type );
            printf("---------------------------------------------------------------------------------------------\n");
            if(supprimer_chambre(n))
                {
                printf("\n\n  Nouveau Numero :  "); scanf("%d",&c.num);
                printf("\n\n  Nouveau Etage :  "); scanf("%d",&c.etage);
                printf("\n\n  Nouveau Prix la nuit :  "); scanf("%d",&c.prix);
                printf("\n\n  Nouveau Type :  "); scanf("%s",c.type);
                //ajouter la chambre c au fichier
                FILE *f;
                f=fopen("fichier_chambre.txt","a");
                fprintf(f,"%d %d %d %s\n",c.num,c.etage,c.prix,c.type);
                fclose(f);
                printf("\n\n  Les modifications ont bien ete enregistrees\n\n");
                }


            }

    else printf("\n\n Il n'y a pas de chambre sous le numero %d \n",n);
}




