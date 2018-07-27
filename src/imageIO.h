void cree3matrices(DonneesImageRGB *image, int** rouge,
                   int** vert, int** bleu);
// convertit DonneesImageRGB *image en trois matrices rouge, vert, bleu

void matricesVersImage(DonneesImageRGB *image, int** rouge,
                       int** vert, int** bleu);
// convertit trois matrices rouge, vert, bleu en DonneesImageRGB *image
// attention : image doit être correctement alloue pour etre utilise

void sauveImage1composante(char *nom, DonneesImageRGB *image, int** gris);
// permet de sauvegarder le contenu de la matrice gris dans un fichier BMP code sur 24 bits
// attention : image doit être correctement alloue pour etre utilise

void dupliqueImageCouleur(char *nom, DonneesImageRGB *image,int** rouge, int** vert, int** bleu,
                          int** rouge2, int** vert2, int** bleu2);
// copie l'image rouge, vert, bleu dans l'image rouge2, vert2, bleu2

void dupliqueImage1composante(DonneesImageRGB *image,int** gris, int** gris2);
// copie l'image 1 composante gris dans l'image 1 composante gris2

void afficheMasque(DonneesImageRGB *image,int** rouge,int** vert,int** bleu);
//Affiche le masque (pour la detection des formes)

int** alloueMatrice(int ** tab, DonneesImageRGB *image);
//Alloue une matrice de taille variable
