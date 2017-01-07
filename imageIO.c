#include <stdio.h>
#include <stdlib.h>
#include "outilslib.h"
#include "bmplib.h"
#include "imageIO.h"
#include <math.h>
#include <time.h>


int** alloueMatrice(int ** tab, DonneesImageRGB *image)
// aloue une matrice de taille variable
{
    int i,j,M,N;
    N = image->hauteurImage; // ligne
  //  printf("Nombre de lignes %d \n",N);
    M = image->largeurImage; // colonne
   // printf("Nombre de colonnes %d \n\n",M);

    /* On veut avoir int * tab[N], sauf que tab sera créé dynamiquement */
    tab = malloc(N * sizeof(int *));
    if( tab == NULL )
    {
         fprintf(stderr,"Allocation impossible");
         exit(EXIT_FAILURE);
    }
    /* On crée maintenant les N tableaux de M éléments chacun */
    for(i = 0; i < N; i++){
        tab[i] = malloc(M * sizeof(int));

         if( tab[i] == NULL )
         {
              fprintf(stderr,"Allocation impossible");
              exit(EXIT_FAILURE);
         }
    }

    for(i = 0 ; i < N ; i++)
    {
        for(j= 0 ; j<M ; j++ )
        {
           tab[i][j]=0;
        }
    }
    return tab;
}

void freeMatrice(int** matrice,DonneesImageRGB *image)
// free une matrice de taille variable
{
    int N,M,i,j;

    M = image->largeurImage;
    N = image->hauteurImage;
    if(matrice != NULL)
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                free(matrice[i][j]);
            }
        }
    }
}


void cree3matrices(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
// convertit DonneesImageRGB *image en trois matrices rouge, vert, bleu
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    //printf("Nombre lignes %d \n",NBLIG);
    //printf("Nombre colonnes %d \n",NBCOL);

    int i,j,k=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            bleu[i][j]=image->donneesRGB[k];
            k++;
            vert[i][j]=image->donneesRGB[k];
            k++;
            rouge[i][j]=image->donneesRGB[k];
            k++;

        }

    /*for(i = 0 ; i < NBLIG ; i++)
    {
        for(j= 0 ; j< NBCOL ; j++ )
        {
            printf("bleu[%d][%d] = %d \t",i,j,bleu[i][j]);
        }
        printf("\n");
    }*/
}

void matricesVersImage(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
// convertit trois matrices rouge, vert, bleu en DonneesImageRGB *image
// attention : image doit être correctement alloue pour etre utilise
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int i,j,k=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            image->donneesRGB[k]=bleu[i][j];
            k++;
            image->donneesRGB[k]=vert[i][j];
            k++;
            image->donneesRGB[k]=rouge[i][j];
            k++;
        }
}

void sauveImage1composante(char *nom, DonneesImageRGB *image, int** gris)
// permet de sauvegarder le contenu de la matrice gris dans un fichier BMP code sur 24 bits
// attention : image doit être correctement alloue pour etre utilise
{
    matricesVersImage(image,gris,gris,gris);
    ecrisBMPRGB_Dans(image,nom);
}

void dupliqueImageCouleur(char *nom, DonneesImageRGB *image,int** rouge, int** vert, int** bleu,
                          int** rouge2, int** vert2, int** bleu2)
// copie l'image rouge, vert, bleu dans l'image rouge2, vert2, bleu2
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
     int i,j;

     for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            rouge2[i][j] = rouge[i][j];
            vert2[i][j] = vert[i][j];
            bleu2[i][j] = bleu[i][j];
        }
}


void dupliqueImage1composante(DonneesImageRGB *image,int** gris, int** gris2)
// copie l'image 1 composante gris dans l'image 1 composante gris2
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
     int i,j;

     for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
            gris2[i][j] = gris[i][j];
}


void quantification(DonneesImageRGB *image,int N, int** gris){
    int max, min, comparateur, maximumTableau, minimumTableau, moyenneTableau, i, j, k;
    int coef;
    int tab[N][1];
    maximumTableau = 0;
    minimumTableau = 0;
    moyenneTableau = 0;
	comparateur=0;
	max=gris[0][0];
	min=gris[0][0];

	 int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0 ; i<NBLIG ; i++)
    {
        for(j=0 ; j<NBCOL ; j++)
        {
            comparateur=gris[i][j];
            if(max<comparateur) max=comparateur;
        }
    }

	for (i=0 ; i<NBLIG ; i++)
    {
        for(j=0 ; j<NBCOL ; j++)
        {
            comparateur=gris[i][j];
            if(min>comparateur) min=comparateur;
        }
    }

    coef = (int) (max-min)/(N);
    printf("coef %d \n", coef);

    for(i=0; i<N ; i++)
    {
        if(i==0) {
            minimumTableau = min;
        }else{
            minimumTableau = maximumTableau;
        }
        maximumTableau = coef + maximumTableau;
        tab[i][0] = minimumTableau;
        tab[i][1] = maximumTableau;
        moyenneTableau = (int) (maximumTableau - (coef/2));
        tab[i][2] = moyenneTableau;
        printf("minimum %d \n", minimumTableau);
        printf("maximum %d \n", maximumTableau);
        printf("moyenne %d \n", moyenneTableau);
    }

    for (i=0 ; i<NBLIG ; i++)
	{
		for(j=0 ; j<NBCOL ; j++)
		{
		    for(k=0; k<N ; k++) {
                if(gris[i][j] > tab[k][0] && gris[i][j] < tab[k][1]) {
                    gris[i][j] = tab[k][2];
                    //printf("test %d", gris[i][j]);
                }
		    }
		}
	}
}

//arbvre
void couleur2Uni(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** nb){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
   // alloueMatrice(image,vert);

    int i,j=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            //si pas blanc, on met en noir
            if((rouge[i][j] < 153 && vert[i][j] < 195 && bleu[i][j] < 107) && (rouge[i][j] > 115 && vert[i][j] > 173 && bleu[i][j] > 52)){
                nb[i][j] = 255;
            }
            else {
                nb[i][j] = 0;
            }

        }
}


//arbvre
void couleur2Uni2(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** nb){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
   // alloueMatrice(image,vert);

    int i,j=0;
    int x=0;
    int y=0;

    for (i=x; i<NBLIG-15; i++)
        for (j=y; j<NBCOL-15; j++)
        {
             if((rouge[i][j] < 191 && vert[i][j] < 195 && bleu[i][j] < 195) && (rouge[i][j] > 68 && vert[i][j] > 68 && bleu[i][j] > 68)){
                if(((rouge[i][j]+vert[i][j]+bleu[i][j]) < (rouge[i][j]+vert[i][j]+bleu[i][j]+5)) && ((rouge[i][j]+vert[i][j]+bleu[i][j]) > (rouge[i][j]+vert[i][j]+bleu[i][j]-5)))
                {
                      for(x=-4+i;x<i+4;x++){
                        rouge[x][j] = 255;
                        vert[x][j] = 20;
                        bleu[x][j] = 10;

                    }
                }else{
                    rouge[i][j] = 55;
                    vert[i][j] = 250;
                    bleu[i][j] = 10;
                }

               /*
               for(x=-4+i;x<i+4;x++){
                     for(y=-4+j;y<j+4;y++){
                        //ne rien faire
                        printf("okok");

                    }
                }
                */

            }
            else {
                rouge[i][j] = 0;
                vert[i][j] = 0;
                bleu[i][j] = 0;
            }

        }
}

//calcule echelle
void couleur2Echelle(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** nb){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
   // alloueMatrice(image,vert);

    int i,j=0;

    for (i=0; i<30; i++)
        for (j=1100; j<1300; j++)
        {
            //si pas blanc, on met en noir
            if((rouge[i][j] < 191 && vert[i][j] < 195 && bleu[i][j] < 195) && (rouge[i][j] > 67 && vert[i][j] > 67 && bleu[i][j] > 67)){
                if(((rouge[i][j]+vert[i][j]+bleu[i][j]) < (rouge[i][j]+vert[i][j]+bleu[i][j]+5)) && ((rouge[i][j]+vert[i][j]+bleu[i][j]) > (rouge[i][j]+vert[i][j]+bleu[i][j]-5)))
                    nb[i][j] = 255;
                else
                     nb[i][j] = 0;
            }
            else {
                nb[i][j] = 0;
            }

        }
}


void couleur2NoirBlanc(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** nb){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
   // alloueMatrice(image,vert);

    int i,j=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            //si pas blanc, on met en noir
            if(rouge[i][j] <= 127 && vert[i][j] <= 127 && bleu[i][j] <= 127) {
                nb[i][j] = 0;
            }
            else {
                nb[i][j] = 255;
            }

        }
}


void couleur(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** nb){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
   // alloueMatrice(image,vert);

    int i,j=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            nb[i][j] = 255;
        }
}

void couleur2NG(DonneesImageRGB *image,int** rouge,int** vert,
                int** bleu,int** gris){

    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int i,j=0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
                gris[i][j] = (short int) rouge[i][j]*0.2125 + vert[i][j]*0.7254 + bleu[i][j]*0.0721;
                bleu[i][j]= gris[i][j];
                vert[i][j]= gris[i][j];
                rouge[i][j]= gris[i][j];
        }
}

//Affiche le masque (pour la detection des formes)
void afficheMasque(DonneesImageRGB *image,int** rouge,int** vert,int** bleu)
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int i,j=0;
    printf("taille %dx%d\n", NBLIG, NBCOL);
       for (i=0; i<NBLIG; i++)
        {
            for (j=0; j<NBCOL; j++)
            {
                if(rouge[i][j] == 255 && vert[i][j] == 255 && bleu[i][j] == 255) {
                    printf("/");
                } else {
                    printf("[%d,%d,%d]", rouge[i][j],vert[i][j],bleu[i][j]);
                }
            }
            printf("\n");
       }

}


void cherchePunaiseBlanche(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 76) && (bleu[i][j] == 167) && (vert[i][j] == 115))
            {

            }

            else if((rouge[i][j] == 75) && (bleu[i][j] == 166) && (vert[i][j] == 114))
            {

            }

            else if((rouge[i][j] == 0) && (bleu[i][j] == 129) && (vert[i][j] == 50))
            {

            }

            else if((rouge[i][j] == 62) && (bleu[i][j] == 160) && (vert[i][j] == 102))
            {

            }

            else if((rouge[i][j] == 62) && (bleu[i][j] == 160) && (vert[i][j] == 102))
            {

            }

            else if((rouge[i][j] == 13) && (bleu[i][j] == 135) && (vert[i][j] == 61))
            {

            }

             else if((rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61))
            {

            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
}


void cherchePunaiseBlanche2(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt = 0;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61))
            {
                cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
        cpt=(int) cpt/12;
        printf("nb punaise blanche %d", cpt);
}

//Isole juste 1 pixel qui corespond aux coordonnées des punaise bleu foncé
void cherchePunaiseBlanche3(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt = 0;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61))
            {
                //cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }

  for (i=0; i<NBLIG-3; i++)
        for (j=0; j<NBCOL; j++)
        {
            //if((rouge[i][j-1] == 255) && (bleu[i][j-1] == 255) && (vert[i][j-1] == 255) && (rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61)&& (rouge[i][j+1] == 12) && (bleu[i][j+1] == 135) && (vert[i][j+1] == 61))

            if(((rouge[i+1][j] == 12) && (bleu[i+1][j] == 135) && (vert[i+1][j] == 61)) && ((rouge[i+2][j] == 12) && (bleu[i+2][j] == 135) && (vert[i+2][j] == 61)) && ((rouge[i][j] == 255) && (bleu[i][j] == 255) && (vert[i][j] == 255)))
                {
                    cpt++;
                    printf("les coordonnee sont i = %d j = %d \n",i, j);
                    rouge[i][j] = 12;
                    bleu[i][j] = 135;
                    vert[i][j] = 61;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

        //cpt=(int) cpt/14;
        printf("nb punaise blanche %d", cpt);
}


void cherchePunaiseRouge(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 77) && (bleu[i][j] == 166) && (vert[i][j] == 114))
            {

            }

             else if((rouge[i][j] == 0) && (bleu[i][j] == 128) && (vert[i][j] == 53))
            {

            }

            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
}

//Isole juste 1 pixel qui corespond aux coordonnées des punaise bleu avec rouge
void cherchePunaiseRouge3(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt = 0;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 9) && (bleu[i][j] == 132) && (vert[i][j] == 60))
            {
                //cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }

  for (i=0; i<NBLIG-3; i++)
        for (j=0; j<NBCOL; j++)
        {
            //if((rouge[i][j-1] == 255) && (bleu[i][j-1] == 255) && (vert[i][j-1] == 255) && (rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61)&& (rouge[i][j+1] == 12) && (bleu[i][j+1] == 135) && (vert[i][j+1] == 61))

            if(
               ((rouge[i+1][j] == 9) && (bleu[i+1][j] == 132) && (vert[i+1][j] == 60))
               && ((rouge[i+2][j] == 9) && (bleu[i+2][j] == 132) && (vert[i+2][j] == 60))
               && ((rouge[i+3][j] == 9) && (bleu[i+3][j] == 132) && (vert[i+3][j] == 60))
               && ((rouge[i+4][j] == 9) && (bleu[i+4][j] == 132) && (vert[i+4][j] == 60))
               && ((rouge[i][j] == 255) && (bleu[i][j] == 255) && (vert[i][j] == 255)))
                {
                    cpt++;
                    printf("les coordonnee sont i = %d j = %d \n",i, j);
                    rouge[i][j] = 255;
                    bleu[i][j] = 255;
                    vert[i][j] = 255;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

        //cpt=(int) cpt/14;
        printf("nb punaise blanche %d", cpt);
}

void cherchePunaisePrincipale(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 42) && (vert[i][j] == 167) && (bleu[i][j] == 255))
            {

            }
            else if((rouge[i][j] == 82) && (vert[i][j] == 183) && (bleu[i][j] == 255))
            {

            }
            else if((rouge[i][j] == 2) && (vert[i][j] == 151) && (bleu[i][j] == 255))
            {

            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
}


//Isole juste 1 pixel qui corespond aux coordonnées des punaise principale
void cherchePunaisePrincipale3(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt = 0;



   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 42) && (bleu[i][j] == 255) && (vert[i][j] == 167))
            {
                //cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }

  for (i=0; i<NBLIG-5; i++)
        for (j=0; j<NBCOL; j++)
        {
            //if((rouge[i][j-1] == 255) && (bleu[i][j-1] == 255) && (vert[i][j-1] == 255) && (rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61)&& (rouge[i][j+1] == 12) && (bleu[i][j+1] == 135) && (vert[i][j+1] == 61))

            if(
               ((rouge[i+1][j] == 42) && (bleu[i+1][j] == 255) && (vert[i+1][j] == 167))
               && ((rouge[i+2][j] == 42) && (bleu[i+2][j] == 255) && (vert[i+2][j] == 167))
               && ((rouge[i+3][j] == 42) && (bleu[i+3][j] == 255) && (vert[i+3][j] == 167))
               && ((rouge[i+4][j] == 42) && (bleu[i+4][j] == 255) && (vert[i+4][j] == 167))
               && ((rouge[i+5][j] == 42) && (bleu[i+5][j] == 255) && (vert[i+5][j] == 167))
               && ((rouge[i][j] == 255) && (bleu[i][j] == 255) && (vert[i][j] == 255))
               )
                {
                    cpt++;
                    printf("les coordonnee sont i = %d j = %d \n",i, j);
                    rouge[i][j] = 255;
                    bleu[i][j] = 255;
                    vert[i][j] = 255;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

        //cpt=(int) cpt/14;
        printf("nb punaise blanche %d", cpt);
}




//Isole juste 1 pixel qui corespond aux coordonnées des punaise principale avec stockage dans un tabbleau
int* cherchePunaisePrincipale4(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int* tabCoor)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt = 0;



   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 42) && (bleu[i][j] == 255) && (vert[i][j] == 167))
            {
                //cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }

  for (i=0; i<NBLIG-5; i++)
        for (j=0; j<NBCOL; j++)
        {
            //if((rouge[i][j-1] == 255) && (bleu[i][j-1] == 255) && (vert[i][j-1] == 255) && (rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61)&& (rouge[i][j+1] == 12) && (bleu[i][j+1] == 135) && (vert[i][j+1] == 61))

            if(
               ((rouge[i+1][j] == 42) && (bleu[i+1][j] == 255) && (vert[i+1][j] == 167))
               && ((rouge[i+2][j] == 42) && (bleu[i+2][j] == 255) && (vert[i+2][j] == 167))
               && ((rouge[i+3][j] == 42) && (bleu[i+3][j] == 255) && (vert[i+3][j] == 167))
               && ((rouge[i+4][j] == 42) && (bleu[i+4][j] == 255) && (vert[i+4][j] == 167))
               && ((rouge[i+5][j] == 42) && (bleu[i+5][j] == 255) && (vert[i+5][j] == 167))
               && ((rouge[i][j] == 255) && (bleu[i][j] == 255) && (vert[i][j] == 255))
               )
                {
                    cpt++;
                    printf("les coordonnee sont i = %d j = %d (save dans tab)\n",i, j);
                    tabCoor[2] = i; tabCoor[1] = j;
                    rouge[i][j] = 255;
                    bleu[i][j] = 255;
                    vert[i][j] = 255;
                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

        //cpt=(int) cpt/14;
         //tabCoor[2] = 55; tabCoor[1] = 77;
        printf("nb punaise blanche %d", cpt);

        return tabCoor;
}


//Calcule les distance a partir de coordonnee
void calculCoord(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int* tabCoor, int echelle, int metreChoisi)
{
   printf("\n calculCoord X->(%d) Y->(%d)\n", tabCoor[1], tabCoor[2]);


   int i,j, trueMin = 2000, min = 0;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int truei = 0;
    int cpt = 0;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 12) && (bleu[i][j] == 135) && (vert[i][j] == 61))
            {
                //cpt++;
            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }

  for (i=0; i<NBLIG-3; i++)
        for (j=0; j<NBCOL; j++)
        {

            if(((rouge[i+1][j] == 12) && (bleu[i+1][j] == 135) && (vert[i+1][j] == 61)) && ((rouge[i+2][j] == 12) && (bleu[i+2][j] == 135) && (vert[i+2][j] == 61)) && ((rouge[i][j] == 255) && (bleu[i][j] == 255) && (vert[i][j] == 255)))
                {
                    cpt++;
                    truei = NBLIG - i;
                    //printf("les coordonnee sont i = %d j = %d ",truei, j);
                    min = calculDistance(tabCoor[1], j,tabCoor[2],truei,echelle, metreChoisi);

                    if(min<trueMin){
                        trueMin = min;
                    }

                    rouge[i][j] = 12;
                    bleu[i][j] = 135;
                    vert[i][j] = 61;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

        printf("distance de l'hotel le mieux place : %dM \n", trueMin);
        printf("nb punaise blanche %d", cpt);


}


//Calcule les distance a partir de coordonnee metro
void calculCoordMetro(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int* tabCoor, int echelle, int metreChoisi)
{
   printf("\n calculCoord X->(%d) Y->(%d)\n", tabCoor[1], tabCoor[2]);


    int i,j, trueMin = 2000, min = 0;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int truei = 0;
    int cpt = 0;
    int x,y;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if(
               (rouge[i][j] == 5) && (vert[i][j] == 12) && (bleu[i][j] == 129)
               || (rouge[i][j] == 97) && (vert[i][j] == 103) && (bleu[i][j] == 177)
               || ((rouge[i][j] == 0 && vert[i][j] < 7 && bleu[i][j] < 134) && (rouge[i][j] == 0 && vert[i][j] > 0 && bleu[i][j] > 107))
               )
            {
               // cpt++;
                rouge[i][j] = 0;
                vert[i][j] = 255;
                bleu[i][j] = 0;
            }
            else
            {
                rouge[i][j] = 0;
                vert[i][j] = 0;
                bleu[i][j] = 0;
            }
        }

  for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0))
                {
                    //cpt++;
                    //calculDistance(tabCoor[1], i,tabCoor[2],j);

                    for (x=i-16; x<16+i; x++){
                        for (y=j-16; y<16+j; y++){
                                if(y<NBCOL && x<NBLIG && y>0 && x>0){
                                    rouge[x][y] = 0;
                                    bleu[x][y] = 0;
                                    vert[x][y] = 0;
                                }

                        }
                    }

                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 255;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0))
            {
                    cpt++;
                    truei = NBLIG - i;
                     min = calculDistance(tabCoor[1], j,tabCoor[2],truei,echelle, metreChoisi);

                    if(min<trueMin){
                        trueMin = min;
                    }
            }
        }



        //cpt=(int) cpt/14;
        printf("distance de l'hotel le mieux place : %dM \n", trueMin);
        printf("nb metro %d", cpt);

}

//Affiche les cimetiere
void chercheCimetiere(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j, trueMin = 2000, min = 0;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0; i<NBLIG; i++)
    {
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 125) && (vert[i][j] == 178) && (bleu[i][j] == 67))
            {

            }
            else if ((rouge[i][j] == 127) && (vert[i][j] == 182) && (bleu[i][j] == 71))
            {

            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
    }
}

//Calcule les distance a partir de coordonnee metro
void calculCoordCim(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int* tabCoor, int echelle, int metreChoisi)
{
   printf("\n calculCoord X->(%d) Y->(%d)\n", tabCoor[1], tabCoor[2]);


    int i,j, trueMin = 2000, min = 0;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int truei = 0;
    int cpt = 0;
    int x,y;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if(
               (rouge[i][j] == 127) && (vert[i][j] == 182) && (bleu[i][j] == 71)
               || (rouge[i][j] == 125) && (vert[i][j] == 178) && (bleu[i][j] == 67)
               )
            {
               // cpt++;
                rouge[i][j] = 0;
                vert[i][j] = 255;
                bleu[i][j] = 0;
            }
            else
            {
                rouge[i][j] = 0;
                vert[i][j] = 0;
                bleu[i][j] = 0;
            }
        }

  for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0))
                {
                    for (x=i-16; x<16+i; x++){
                        for (y=j-16; y<16+j; y++){
                                if(y<NBCOL && x<NBLIG && y>0 && x>0){
                                    rouge[x][y] = 0;
                                    bleu[x][y] = 0;
                                    vert[x][y] = 0;
                                }
                        }
                    }

                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 255;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0))
            {
                    cpt++;
                    truei = NBLIG - i;
                    min = calculDistance(tabCoor[1], j,tabCoor[2],truei,echelle, metreChoisi);

                    if(min<trueMin){
                        trueMin = min;
                    }
            }
        }

        printf("distance de l'hotel le mieux place : %dM \n", trueMin);
        printf("nb cimetiere %d", cpt);

}


//Calcule les distance a partir de coordonnee metro
//if(((rouge[i][j] < 145 && vert[i][j] < 116 && bleu[i][j] < 108) && (rouge[i][j] > 128 && vert[i][j] > 108 && bleu[i][j] > 97)))
void calculCoordMarron(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int* tabCoor, int echelle, int metreChoisi)
{
   printf("\n calculCoord X->(%d) Y->(%d)\n", tabCoor[1], tabCoor[2]);


    int i,j, trueMin = 2000, min = 0;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int truei = 0;
    int cpt = 0;
    int x,y;

   for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if(((rouge[i][j] < 142 && vert[i][j] < 116 && bleu[i][j] < 108) && (rouge[i][j] > 129 && vert[i][j] > 108 && bleu[i][j] > 97)))
            {
               // cpt++;
                rouge[i][j] = 0;
                vert[i][j] = 255;
                bleu[i][j] = 0;
            }
            else
            {
                rouge[i][j] = 0;
                vert[i][j] = 0;
                bleu[i][j] = 0;
            }
        }

  for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0) && (rouge[i][j+1] == 0) && (vert[i][j+1] == 255) && (bleu[i][j+1] == 0)) //Limite les erreurs couleur isole
                {
                    //cpt++;
                    //calculDistance(tabCoor[1], i,tabCoor[2],j);

                    for (x=i-16; x<16+i; x++){
                        for (y=j-16; y<16+j; y++){
                                if(y<NBCOL && x<NBLIG && y>0 && x>0){
                                    rouge[x][y] = 0;
                                    bleu[x][y] = 0;
                                    vert[x][y] = 0;
                                }
                        }
                    }

                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 255;

                }
                else
                {
                    rouge[i][j] = 0;
                    bleu[i][j] = 0;
                    vert[i][j] = 0;
                }

        }

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {

            if((rouge[i][j] == 0) && (vert[i][j] == 255) && (bleu[i][j] == 0))
            {
                    cpt++;
                    truei = NBLIG - i;
                    //printf("les coordonnee sont i = %d j = %d ",truei, j);
                    min = calculDistance(tabCoor[1], j,tabCoor[2],truei,echelle, metreChoisi);

                    if(min<trueMin){
                        trueMin = min;
                    }
            }
        }

        printf("distance de l'hotel le mieux place : %dM \n", trueMin);
        printf("nb marron %d", cpt);

}




void chercheEchelle(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int cpt;
    int x, y;
    int r=0;
    int v=0;
    int b=0;
    int nb5detecte=0;

     for (i=0; i<NBLIG; i++)
     {
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 220) && (vert[i][j] == 220) && (bleu[i][j] == 219))
            {
                cpt++;
                for (x=i; x<9+i; x++){
                     for (y=j; y<9+j; y++){
                        if(rouge[i][j] == 239 && vert[i][j] == 239 && bleu[i][j] == 238) {
                        } else {
                                r =rouge[x][y]+r;
                                v =vert[x][y]+v;
                                b =bleu[x][y]+b;
                        }
                     }
                }
              printf("r %d", r);
              if(r == 5473)
                nb5detecte++;
            }

            //printf("%d %d %d\n",r,v,b);
            r=0; v=0; b=0;
        }
     }


    printf("cpt = %d , detecte num 5 =%d \n", cpt, nb5detecte);

}

//Affiche le masque (pour la detection des formes)
int* afficheMasqueNumero(DonneesImageRGB *image,int** rouge,int** vert,int** bleu, int* tabRVB)
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int i,j=0;
    int cpt=0;
    int r = 0;
    int v = 0;
    int b = 0;
    printf("taille %dx%d\n", NBLIG, NBCOL);
       for (i=0; i<NBLIG; i++)
        {
            for (j=0; j<NBCOL; j++)
            {
                if((rouge[i][j] == 239 && vert[i][j] == 239 && bleu[i][j] == 238)) {
                    //printf("/");
                }
                else if(rouge[i][j] == 255 && vert[i][j] == 255 && bleu[i][j] == 255){

                }
                else {
                      r =rouge[i][j]+r;
                      v =vert[i][j]+v;
                      b =bleu[i][j]+b;
                      cpt++;
                }
            }
       }
    printf("cpt = %d, %d %d %d\n",  cpt,r,v,b);
    tabRVB[0] = r; tabRVB[1] = v; tabRVB[2] = b;
    //printf("r = %d, v = %d, b = %d\n",  tabRVB[0], tabRVB[1], tabRVB[2]);

   return tabRVB;
}

//Affiche le masque (pour la detection des formes) [rgb 1er pixel][taille][r][g][b]
int* afficheSignature(DonneesImageRGB *image,int** rouge,int** vert,int** bleu, int* tabSignature)
{
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int j=0;
    int i = NBLIG/2; //On prend le milieu de l'image
    int cpt=0;
    int r = 0;
    int v = 0;
    int b = 0;
    printf("taille %dx%d\n", NBLIG, NBCOL);



        for (j=0; j<NBCOL; j++)
        {
            if(rouge[i][j] == 255 && vert[i][j] == 255 && bleu[i][j] == 255) {
                //printf("/");
            }
            else {
                  r =rouge[i][j]+r;
                  v =vert[i][j]+v;
                  b =bleu[i][j]+b;
                  if(cpt==0){
                     tabSignature[0] = rouge[i][j]+vert[i][j]+ bleu[i][j]; //couleur du 1er pixel (somme)
                  }
                  cpt++;
            }
        }
    tabSignature[1] = cpt; //taille horizontal

    tabSignature[2] = r;
    tabSignature[3] = v;
    tabSignature[4] = b;
    printf("color 1er pixel = %d taille = %d, r = %d, v = %d, b = %d\n",  tabSignature[0], tabSignature[1], tabSignature[2], tabSignature[3], tabSignature[4]);

   return tabSignature;
}

//Cherche sur l'image google maps les signature qui correspond (faire avant afficheSignature=[rgb 1er pixel][taille][r][g][b])
void chercheSignature(DonneesImageRGB *image, int** rouge,int** vert, int** bleu, int** tabSignature)
{
    int i,j,x,y;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int r = 0;
    int v = 0;
    int b = 0;

    for (i=0; i<NBLIG; i++)
    {
        for (j=0; j<NBCOL; j++)
        {
            for (x=0; x<1; x++) //changer et mettre taille de tabSignature
            {
                 if((rouge[i][j]+vert[i][j]+bleu[i][j])==tabSignature[x][0]) //Si detection du début d'une signature
                 {
                    for (y=j; y<tabSignature[x][1]+j; y++) //calcul de la signature (je pense y=j à verifier)
                    {
                        r =rouge[i][y]+r;
                        v =vert[i][y]+v;
                        b =bleu[i][y]+b;
                    }
                    if( r == tabSignature[x][2] && v == tabSignature[x][3] && b == tabSignature[x][4]) //Compare avec la signature
                    {
                        printf("IMG reconnu en bdd id=%d avec les coordonnees i=%d et j=%d\n",x,i,j);
                    }
                 }
                 r=0;v=0;b=0;
            }
        }
    }
}

int calculDistance(int X1,int X2, int Y1, int Y2, int echelle, int metreChoisi)
{
   int largeur;  //colonne
   int hauteur;  //ligne
   int distance; // l'hypothénuse
   int min;
    int distanceEnMetre=0;

   if(X2>X1)
   {
       largeur = X2 - X1;
   }
   else
   {
       largeur = X1 - X2;
   }

   if(Y2>Y1)
   {
       hauteur = Y2 - Y1;
   }
   else
   {
       hauteur = Y1 - Y2;
   }

    // printf(" largeur=%d ",largeur);
    // printf(" hauteur=%d ",hauteur);
    // 92pixel = 1 cm
    // distance pixel = distanceEnMetre

    distance = (sqrt((largeur*largeur)+(hauteur*hauteur)));

    if(echelle==500){
        distanceEnMetre = distance/117;
    }else{
        distanceEnMetre = distance/92;
    }

    distanceEnMetre = distanceEnMetre*echelle;
    //printf("\ndistanceEnMetre = %d et valeur choisi = %d m \n",distanceEnMetre, metreChoisi);

    /* lire l'heure courante */
   time_t now = time (NULL);
   /* la convertir en heure locale */
   struct tm tm_now = *localtime (&now);
   /* Creer une chaine JJ/MM/AAAA HH:MM:SS */
   char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];
   strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);
   /* afficher le resultat : */
   //printf ("'%s'\n", s_now);


    /* Ecriture dans un fichier texte */
    FILE* fichier = NULL;
    FILE* fichierText = NULL;

    fichier = fopen("log.txt", "a");
    fichierText = fopen("text.txt", "a");
    fprintf(fichier,"| %s |", s_now);

    if (fichier != NULL)
    {
       if(distanceEnMetre<metreChoisi){
            fprintf(fichier,"i = %d j = %d , distance pixel = %d et = %d m \n", X2, Y2, distance, distanceEnMetre);
            fprintf(fichierText,"i = %d j = %d , distance pixel = %d et = %d m \n", X2, Y2, distance, distanceEnMetre);
            printf("i = %d j = %d , distance pixel = %d et = %d m \n", X2, Y2, distance, distanceEnMetre);
            fclose(fichier);
            fclose(fichierText);
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier log.txt");
    }

    min = distanceEnMetre;
    return min;
}



void cherchePictogramme(DonneesImageRGB *image, int** rouge,int** vert, int** bleu)
{
    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;

    for (i=0; i<NBLIG; i++)
        for (j=0; j<NBCOL; j++)
        {
            if((rouge[i][j] == 141) && (vert[i][j] == 110) && (bleu[i][j] == 99))
            {

            }
            else
            {
                rouge[i][j] = 255;
                bleu[i][j] = 255;
                vert[i][j] = 255;
            }
        }
}


int chercheEchelleMetre(DonneesImageRGB *image, int** rouge,int** vert, int** bleu) {

    int i,j;
    int NBLIG = image->hauteurImage;
    int NBCOL = image->largeurImage;
    int nombre = 0;

     for (i=0; i<NBLIG; i++){
        for (j=0; j<NBCOL; j++){
            if(
               (rouge[i][j]==255 && vert[i][j]==255 && bleu[i][j]==255)&&
               (rouge[i][j+1]==255 && vert[i][j+1]==255 && bleu[i][j+1]==255)&&
               (rouge[i][j+2]==255 && vert[i][j+2]==255 && bleu[i][j+2]==255)&&
               (rouge[i][j+3]==255 && vert[i][j+3]==255 && bleu[i][j+3]==255)&&
               (rouge[i][j+4]==255 && vert[i][j+4]==255 && bleu[i][j+4]==255)&&
               (rouge[i][j+5]==0 && vert[i][j+5]==0 && bleu[i][j+5]==0)&&
               (rouge[i][j+6]==0 && vert[i][j+6]==0 && bleu[i][j+6]==0)&&
               (rouge[i][j+7]==0 && vert[i][j+7]==0 && bleu[i][j+7]==0)&&
               (rouge[i][j+8]==255 && vert[i][j+8]==255 && bleu[i][j+8]==255)&&
               (rouge[i][j+9]==255 && vert[i][j+9]==255 && bleu[i][j+9]==255)&&
               (rouge[i][j+10]==255 && vert[i][j+10]==255 && bleu[i][j+10]==255)&&
               (rouge[i][j+11]==255 && vert[i][j+11]==255 && bleu[i][j+11]==255)&&
               (rouge[i][j+12]==255 && vert[i][j+12]==255 && bleu[i][j+12]==255)
               ){
                    nombre = 50;

            }else if(
                   (rouge[i][j]==255 && vert[i][j]==255 && bleu[i][j]==255)&&
                   (rouge[i][j+1]==255 && vert[i][j+1]==255 && bleu[i][j+1]==255)&&
                   (rouge[i][j+2]==0 && vert[i][j+2]==0 && bleu[i][j+2]==0)&&
                   (rouge[i][j+3]==0 && vert[i][j+3]==0 && bleu[i][j+3]==0)&&
                   (rouge[i][j+4]==0 && vert[i][j+4]==0 && bleu[i][j+4]==0)&&
                   (rouge[i][j+5]==0 && vert[i][j+5]==0 && bleu[i][j+5]==0)&&
                   (rouge[i][j+6]==0 && vert[i][j+6]==0 && bleu[i][j+6]==0)&&
                   (rouge[i][j+7]==255 && vert[i][j+7]==255 && bleu[i][j+7]==255)&&
                   (rouge[i][j+8]==255 && vert[i][j+8]==255 && bleu[i][j+8]==255)&&
                   (rouge[i][j+9]==255 && vert[i][j+9]==255 && bleu[i][j+9]==255)&&
                   (rouge[i][j+10]==255 && vert[i][j+10]==255 && bleu[i][j+10]==255)&&
                   (rouge[i][j+11]==0 && vert[i][j+11]==0 && bleu[i][j+11]==0)&&
                   (rouge[i][j+12]==0 && vert[i][j+12]==0 && bleu[i][j+12]==0)&&
                   (rouge[i][j+13]==0 && vert[i][j+13]==0 && bleu[i][j+13]==0)&&
                   (rouge[i][j+14]==0 && vert[i][j+14]==0 && bleu[i][j+14]==0)&&
                   (rouge[i][j+15]==255 && vert[i][j+15]==255 && bleu[i][j+15]==255)&&
                   (rouge[i][j+16]==255 && vert[i][j+16]==255 && bleu[i][j+16]==255)&&
                   (rouge[i][j+17]==255 && vert[i][j+17]==255 && bleu[i][j+17]==255)&&
                   (rouge[i][j+18]==255 && vert[i][j+18]==255 && bleu[i][j+18]==255)&&
                   (rouge[i][j+19]==255 && vert[i][j+19]==255 && bleu[i][j+19]==255)
                    ){
                        nombre = 100;

                }else if(
                       (rouge[i][j]==255 && vert[i][j]==255 && bleu[i][j]==255)&&
                       (rouge[i][j+1]==255 && vert[i][j+1]==255 && bleu[i][j+1]==255)&&
                       (rouge[i][j+2]==255 && vert[i][j+2]==255 && bleu[i][j+2]==255)&&
                       (rouge[i][j+3]==255 && vert[i][j+3]==255 && bleu[i][j+3]==255)&&
                       (rouge[i][j+4]==255 && vert[i][j+4]==255 && bleu[i][j+4]==255)&&
                       (rouge[i][j+5]==0 && vert[i][j+5]==0 && bleu[i][j+5]==0)&&
                       (rouge[i][j+6]==0 && vert[i][j+6]==0 && bleu[i][j+6]==0)&&
                       (rouge[i][j+7]==0 && vert[i][j+7]==0 && bleu[i][j+7]==0)&&
                       (rouge[i][j+8]==0 && vert[i][j+8]==0 && bleu[i][j+8]==0)&&
                       (rouge[i][j+9]==255 && vert[i][j+9]==255 && bleu[i][j+9]==255)&&
                       (rouge[i][j+10]==255 && vert[i][j+10]==255 && bleu[i][j+10]==255)&&
                       (rouge[i][j+11]==0 && vert[i][j+11]==0 && bleu[i][j+11]==0)&&
                       (rouge[i][j+12]==255 && vert[i][j+12]==255 && bleu[i][j+12]==255)&&
                       (rouge[i][j+13]==255 && vert[i][j+13]==255 && bleu[i][j+13]==255)&&
                       (rouge[i][j+14]==0 && vert[i][j+14]==0 && bleu[i][j+14]==0)&&
                       (rouge[i][j+15]==0 && vert[i][j+15]==0 && bleu[i][j+15]==0)&&
                       (rouge[i][j+16]==0 && vert[i][j+16]==0 && bleu[i][j+16]==0)&&
                       (rouge[i][j+17]==255 && vert[i][j+17]==255 && bleu[i][j+17]==255)&&
                       (rouge[i][j+18]==255 && vert[i][j+18]==255 && bleu[i][j+18]==255)
                         ){
                            nombre=500;

                    }else if(
                       (rouge[i][j]==255 && vert[i][j]==255 && bleu[i][j]==255)&&
                       (rouge[i][j+1]==255 && vert[i][j+1]==255 && bleu[i][j+1]==255)&&
                       (rouge[i][j+2]==255 && vert[i][j+2]==255 && bleu[i][j+2]==255)&&
                       (rouge[i][j+3]==255 && vert[i][j+3]==255 && bleu[i][j+3]==255)&&
                       (rouge[i][j+4]==255 && vert[i][j+4]==255 && bleu[i][j+4]==255)&&
                       (rouge[i][j+5]==255 && vert[i][j+5]==255 && bleu[i][j+5]==255)&&
                       (rouge[i][j+6]==255 && vert[i][j+6]==255 && bleu[i][j+6]==255)&&
                       (rouge[i][j+7]==255 && vert[i][j+7]==255 && bleu[i][j+7]==255)&&
                       (rouge[i][j+8]==0 && vert[i][j+8]==0 && bleu[i][j+8]==0)&&
                       (rouge[i][j+9]==0 && vert[i][j+9]==0 && bleu[i][j+9]==0)&&
                       (rouge[i][j+10]==255 && vert[i][j+10]==255 && bleu[i][j+10]==255)&&
                       (rouge[i][j+11]==255 && vert[i][j+11]==255 && bleu[i][j+11]==255)&&
                       (rouge[i][j+12]==255 && vert[i][j+12]==255 && bleu[i][j+12]==255)&&
                       (rouge[i][j+13]==255 && vert[i][j+13]==255 && bleu[i][j+13]==255)&&
                       (rouge[i][j+14]==0 && vert[i][j+14]==0 && bleu[i][j+14]==0)&&
                       (rouge[i][j+15]==0 && vert[i][j+15]==0 && bleu[i][j+15]==0)&&
                       (rouge[i][j+16]==0 && vert[i][j+16]==0 && bleu[i][j+16]==0)&&
                       (rouge[i][j+17]==0 && vert[i][j+17]==0 && bleu[i][j+17]==0)&&
                       (rouge[i][j+18]==255 && vert[i][j+18]==255 && bleu[i][j+18]==255)&&
                       (rouge[i][j+19]==255 && vert[i][j+19]==255 && bleu[i][j+19]==255)&&
                       (rouge[i][j+20]==255 && vert[i][j+20]==255 && bleu[i][j+20]==255)&&
                       (rouge[i][j+21]==255 && vert[i][j+21]==255 && bleu[i][j+21]==255)&&
                       (rouge[i][j+22]==255 && vert[i][j+22]==255 && bleu[i][j+22]==255)&&
                       (rouge[i][j+23]==0 && vert[i][j+23]==0 && bleu[i][j+23]==0)
                         ){
                            nombre=200;
                         }
                }
            }

    printf("echelle = %d \n", nombre);

    return nombre;
}

//determiner moi les hotels a 100 m a la ronde, va renvoyer la valeur en pixel de 100m
int calculEchelleMetre(int echelle, int rayon){

// 92pixel = 1 cm
// x pixel = 50m
// distance reel 5000/10000/20000/50000 (en met tout en CM)
// distance sur la carte 1cm
// echelle = 1/5000 ou 1/10000...
/*
    Distance sur la carte : 1 | (rayon souhaite / 92 pour avoir en cm)
    Distance sur le terrain : 5000/10000/20000/50000 | x

    x = (5000ou10000ou20000ou50000 * (rayon souhaite)) / 1
    valeur exacte = x/92 pour avoir en pixel

*/
    int x =0,resultat=0;

    x = (echelle * (rayon)) / (1);
    resultat = x/92;

    return resultat;
}
