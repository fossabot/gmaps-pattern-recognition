#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "string.h"
#include "outilslib.h"
#include "bmplib.h"
#include "imageIO.h"
#include "transfoPixel.h"

void affiche_menu(void)
{
	printf("\t MENU\n");
	printf("\t1_ Dupliquer une image\n");
	printf("\t2_ Creer 3 matrices a partir d'une image\n");
	printf("\t3_ Creer une image a partir de 3 matrices (vous devez d'abord creer les matrices)\n");
	printf("\t4_ Transformer une image en noir et blanc\n");
	printf("\t44_ Fait resortir l echelle\n");
	printf("\t444_ Quantification\n");
	printf("\t5_ Transformer une image en niveau de gris\n");
	printf("\t--------Visualisation------\n");
	printf("\t6_ Affiche punaise principale\n");
	printf("\t7_ Affiche punaise bleu fonce\n");
	printf("\t8_ Affiche punaise bleu fonce avec rouge\n");
	printf("\t9_ Affiche Echelle (dans terminal)\n");
	printf("\t10_ Pictogramme marron\n");
	printf("\t11_ TEST Signature\n");
	printf("\t--------Coordonnees--------\n");
	printf("\t12_ Affiche punaise principale coordonnee\n");
	printf("\t13_ Affiche punaise bleu fonce coordonnee\n");
	printf("\t14_ Affiche punaise bleu fonce avec rouge coordonnee\n");
	printf("\t--------Calcul des distances en m--------\n");
    printf("\t16_ Calcule distance punaise principal vers les hotels libre \n");
    printf("\t17_ Calcule distance punaise principal vers metro \n");
    printf("\t18_ Calcule distance punaise principal vers picto vert \n");
    printf("\t19_ Calcule distance punaise principal vers picto marron \n");
    printf("\t--------Assitant Vocal--------\n");
    printf("\t20_ Lecture de text.txt en vocal \n");
    printf("\t-------------------------------\n");
    printf("\tAide Image = l01 e01 e02 m01 m02 m03\n");
	printf("\t0_ Quitter \n");
}

int main(void)
{
    printf("Traitement d'images\n\n");

    DonneesImageRGB *image;
    int valeur = 0;

    int** rouge = NULL;
    int** vert = NULL;
    int** bleu = NULL;
    int** nb = NULL;
    int r = 0;
    int v = 0;
    int b = 0;
    int* tabCoor= malloc(3 * sizeof(int *));
    int* tabRVB= malloc(3 * sizeof(int *));
    int** tabSignature = NULL;

    int echelle; //contient distance en metre
    int metreChoisi; //contient distance choisi
    char nomImage[50];
    char nomFichier[50];

    do
	{
	    affiche_menu();
        scanf("%d", &valeur);

		switch (valeur){
		    printf("Entrer le niveau de gris : \n");
		    case 1:
                // lecture du nom generique des images
                printf("nom de l'image a traiter : ");
                scanf("%s",nomImage);

                // creation d'un duplicata
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");

                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;

                strcpy(nomFichier, nomImage);
                strcat(nomFichier, "2");
                strcat(nomFichier,".bmp");
                printf("ecriture\n");
                ecrisBMPRGB_Dans(image,nomFichier);
                system(nomFichier);

                break;

			case 2:
			    // lecture du nom de l'image
                printf("nom de l'image a traiter : ");
                scanf("%s",nomImage);

                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture \n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                cree3matrices(image,rouge,vert,bleu);

				break;

            case 3:

				printf("nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Creation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"MVI.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

             case 4:
				printf("NB nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                //cherchePunaiseBlanche3(image,rouge,vert,bleu);
                couleur2NoirBlanc(image,rouge,vert,bleu,nb);
                printf("Creation de l'image \n");
			    matricesVersImage(image,nb,nb,nb);
                printf("ecriture \n");
                strcat(nomImage,"NB.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

		  	case 44:
				printf("NB nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                //cherchePunaiseBlanche3(image,rouge,vert,bleu);
                couleur2Echelle(image,rouge,vert,bleu,nb); //prendre le nb
                //couleur2Uni2(image,rouge,vert,bleu,nb);
                printf("Creation de l'image \n");
			    //matricesVersImage(image,rouge,vert,bleu);
                matricesVersImage(image,nb,nb,nb); // couleur2Echelle
                printf("ecriture \n");
                strcat(nomImage,"echelle.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 444:
				printf("NB nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                //cherchePunaiseBlanche3(image,rouge,vert,bleu);
                couleur2NG(image,rouge,vert,bleu,nb);
                quantification(image,2,nb); //prendre le nb
                //couleur2Uni2(image,rouge,vert,bleu,nb);
                printf("Creation de l'image \n");
			    //matricesVersImage(image,rouge,vert,bleu);
                matricesVersImage(image,nb,nb,nb); // couleur2Echelle
                printf("ecriture \n");
                strcat(nomImage,"echelle.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

		  	case 5:
				printf("NG nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                //cherchePunaiseBlanche3(image,rouge,vert,bleu);
                couleur2NG(image,rouge,vert,bleu,nb);
                printf("Creation de l'image \n");
			    matricesVersImage(image,nb,nb,nb);
                printf("ecriture \n");
                strcat(nomImage,"NG.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

		  	case 6:
				printf("Punaise principale nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePunaisePrincipale(image,rouge,vert,bleu);
                printf("Creation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"punaisePrin.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 7:
				printf("Punaise secondaire nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePunaiseBlanche(image,rouge,vert,bleu);
               // cherchePunaiseBlanche3(image,rouge,vert,bleu);
                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"punaiseSec1.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 8:
				printf("Punaise secondaire avec rouge nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                //cherchePunaiseBlanche3(image,rouge,vert,bleu);
                cherchePunaiseRouge(image,rouge,vert,bleu);
                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"punaiseSec2.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 9:
				printf("Echelle nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                /*chercheEchelle(image,rouge,vert,bleu); //---
                tabRVB = afficheMasqueNumero(image,rouge,vert,bleu,tabRVB); //Ici on annule la couleur rouge[i][j] == 239 && vert[i][j] == 239 && bleu[i][j] == 238 9x9 =dim
                */
                couleur2Echelle(image,rouge,vert,bleu,nb); // pour avoir l echellle
                echelle = chercheEchelleMetre(image, nb, nb, nb); // pour avoir l echellle
                //printf("==>%d",echelle);
                //chercheEchelle(image,rouge,vert,bleu);
                //printf("->%d ->%d ->%d", tabRVB[0], tabRVB[1], tabRVB[2]);
                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"punaise.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 11:
				printf("Signature nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                tabSignature = alloueMatrice(tabSignature,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des icones dans image \n");

                DonneesImageRGB *imgicon; //Img icone en bdd
                imgicon = lisBMPRGB("BddIcons/stade.bmp");
                *tabSignature = afficheSignature(imgicon,rouge,vert,bleu,tabSignature); //signature d'une image = [rgb 1er pixel][taille][r][g][b]
                /*tabSignature[0][0] = 507;
                tabSignature[0][1] = 6;
                tabSignature[0][2] = 869;
                tabSignature[0][3] = 869;
                tabSignature[0][4] = 869;*/
              //  chercheSignature(image,rouge,vert,bleu,tabSignature);
                //chercheEchelle(image,rouge,vert,bleu);
                //printf("->%d ->%d ->%d", tabSignature[0], tabSignature[1], tabSignature[2]);
                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"punaise.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

		  case 12:
				printf("Punaise principale nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePunaisePrincipale3(image,rouge,vert,bleu);
                printf("Creation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordPrincipale.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 13:
				printf("Punaise secondaire nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePunaiseBlanche3(image,rouge,vert,bleu);
                printf("Creation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordBleu.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 14:
				printf("Punaise secondaire rouge nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePunaiseRouge3(image,rouge,vert,bleu);
                printf("Creation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordBleuRouge.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;


            case 10:

				printf("Pictogramme marron nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                return 0;
                printf("Creation des matrices \n");
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);
                printf("Recherche des punaises \n");
                cherchePictogramme(image,rouge,vert,bleu);
                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"PictMarron.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);

		  		break;

            case 16:
				printf("Calcule distance punaise principal vers les hotels libre nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                tabSignature = alloueMatrice(tabSignature,image);
                cree3matrices(image,rouge,vert,bleu);

                *tabCoor=cherchePunaisePrincipale4(image, rouge, vert, bleu, tabCoor);
                printf("Coordonne principale X = %d et Y = %d\n", tabCoor[2], tabCoor[1]);

                //donnee reçu
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);

                couleur2Echelle(image,rouge,vert,bleu,nb); // pour avoir l echellle
                echelle = chercheEchelleMetre(image, nb, nb, nb); // pour avoir l echellle
                //printf("==>%d",echelle);

                //Nombre de metre
                printf("\n Nombre de metre de la recherche : ");
                scanf("%d",&metreChoisi);

                calculCoord(image, rouge, vert, bleu, tabCoor, echelle,metreChoisi);

                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordBleu.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);
                freeMatrice(rouge,image); //free
                freeMatrice(vert,image); //free
                freeMatrice(bleu,image); //free
                freeMatrice(nb,image); //free

		  		break;

             case 17:
				printf("Calcule distance punaise principal vers les metro nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                tabSignature = alloueMatrice(tabSignature,image);
                cree3matrices(image,rouge,vert,bleu);

                *tabCoor=cherchePunaisePrincipale4(image, rouge, vert, bleu, tabCoor);
                printf("Coordonne principale X = %d et Y = %d\n", tabCoor[2], tabCoor[1]);

                //donnee reçu
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);

                //  ECHELLLE
                couleur2Echelle(image,rouge,vert,bleu,nb); // pour avoir l echellle
                echelle = chercheEchelleMetre(image, nb, nb, nb); // pour avoir l echellle
                //printf("==>%d",echelle);

                 //Nombre de metre
                printf("\n Nombre de metre de la recherche : ");
                scanf("%d",&metreChoisi);

                calculCoordMetro(image, rouge, vert, bleu, tabCoor, echelle, metreChoisi);

                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordMetro.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);
                freeMatrice(rouge,image); //free
                freeMatrice(vert,image); //free
                freeMatrice(bleu,image); //free
                freeMatrice(nb,image); //free

		  		break;

            case 18:

				printf("Calcule distance punaise principal vers les cimetiere nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                tabSignature = alloueMatrice(tabSignature,image);
                cree3matrices(image,rouge,vert,bleu);

                *tabCoor=cherchePunaisePrincipale4(image, rouge, vert, bleu, tabCoor);
                printf("Coordonne principale X = %d et Y = %d\n", tabCoor[2], tabCoor[1]);

                //donnee reçu
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);

                //  ECHELLLE
                couleur2Echelle(image,rouge,vert,bleu,nb); // pour avoir l echellle
                echelle = chercheEchelleMetre(image, nb, nb, nb); // pour avoir l echellle
                //printf("==>%d",echelle);

                 //Nombre de metre
                 printf("\n Nombre de metre de la recherche : ");
                scanf("%d",&metreChoisi);

                calculCoordCim(image, rouge, vert, bleu, tabCoor, echelle, metreChoisi);

                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordMetro.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);
                freeMatrice(rouge,image); //free
                freeMatrice(vert,image); //free
                freeMatrice(bleu,image); //free
                freeMatrice(nb,image); //free

		  		break;

            case 19:

				printf("Calcule distance punaise principal vers les cimetiere nom de l'image a traiter : ");
                scanf("%s",nomImage);
                strcpy(nomFichier, nomImage);
                strcat(nomFichier,".bmp");
                printf("lecture\n");
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                tabSignature = alloueMatrice(tabSignature,image);
                cree3matrices(image,rouge,vert,bleu);

                *tabCoor=cherchePunaisePrincipale4(image, rouge, vert, bleu, tabCoor);
                printf("Coordonne principale X = %d et Y = %d\n", tabCoor[2], tabCoor[1]);

                //donnee reçu
                image = lisBMPRGB(nomFichier);
                if (image == NULL)
                    return 0;
                rouge = alloueMatrice(rouge,image);
                vert = alloueMatrice(vert,image);
                bleu = alloueMatrice(bleu,image);
                nb = alloueMatrice(nb,image);
                cree3matrices(image,rouge,vert,bleu);

                //  ECHELLLE
                couleur2Echelle(image,rouge,vert,bleu,nb); // pour avoir l echellle
                echelle = chercheEchelleMetre(image, nb, nb, nb); // pour avoir l echellle
                //printf("==>%d",echelle);

                //Nombre de metre
                 printf("\n Nombre de metre de la recherche : ");
                scanf("%d",&metreChoisi);

                calculCoordMarron(image, rouge, vert, bleu, tabCoor, echelle, metreChoisi);

                printf("\nCreation de l'image \n");
			    matricesVersImage(image,rouge,vert,bleu);
                printf("ecriture \n");
                strcat(nomImage,"coordMarron.bmp");
                ecrisBMPRGB_Dans(image,nomImage);
                system(nomImage);
                freeMatrice(rouge,image); //free
                freeMatrice(vert,image); //free
                freeMatrice(bleu,image); //free
                freeMatrice(nb,image); //free

		  		break;

        case 20:

				printf("Lecture de vocale de text.txt");
				//system(nomImage);
                system("start DSpeech/DSpeech.exe");
                Sleep(3000);
                //system("start test.txt");
                HWND hMPlayer = FindWindow(NULL,TEXT("DSpeech - text.txt"));
                printf("le handle de la fenêtre de DSpeech est : 0x%X",hMPlayer);
                SetForegroundWindow(hMPlayer);
                Sleep(3000);
                PostMessage(hMPlayer,WM_KEYDOWN,VK_F5,0);


		  		break;

            case 0:
				valeur = 0 ;
                break;

            default:
                   printf( "Valeur erronee \n");
		}
	}
	while ( valeur != 0 );

    return 0;
}
