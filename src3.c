/**
 * Ce programme permet de jouer une partie de Sudou
 * il prend pour base un programme precedemment codé mais en connaissant les consignes et en
 * les appliquant correctement...
 * consignes rajouees pour plus de challenge :
 * mettre la ligne en surbrillance puis colonne en surbrillance
 * les chiffres imposés sont affiches en rouge
 * les chiffres qui empèchent de poser un chiffre sont sur fond rouge
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * \def N
 * \detail Taille du coté d'un block
 * 
 * Changera la taillle de la grille mais n'affecte pas un bloc qui, lui, fera toujours du 3/3
*/
#define N 3

/**
 * \def TAILLE
 * \detail Taille de la grille complète
 * 
 * Il dimensionne tout ce qui touche à la taille de la grille globale et de la taille du tableau
*/
#define TAILLE N*N

/**
 * \def RIEN
 * \detail Chiffre a afficher en absence de caractère
*/
#define RIEN '.'

/**
 * \def CASE_FICHIER_VIDE
 * \detail Caractère en cas d'absence d'entrée
 * 
 * Quel caractère dans le fichier marque l'absence de valeur
*/
#define CASE_FICHIER_VIDE 0

/**
 * \def CASE_GRILLE_VIDE
 * \detail Caractère en cas d'absence d'entrée
 * 
 * Quel caractère dans la grille marque l'absence de valeur
*/
#define CASE_GRILLE_VIDE 0


/**
* \typedef tGrille
* \detail Tableau a deux dimensions de la taille de la grille de sudoku
*
*  Tableau a deux dimensions qui permet de stocker une grille de sudoku permettant une manipulation plus simple.
*/
typedef int tGrille[TAILLE][TAILLE];
/**
* \typedef JOLI
* \detail tableau qui contiens le mot "Joli"
*
*  typoe différent du premier contenant des lettres pour épeler le mot 'joli' car je n'ai plus d'inspiration...
*/
typedef char jOli[4];


void chargerGrille(tGrille grille);
void afficherGrille(tGrille aAfficher,int ligne, int colone, int erreur);
void saisir(int *chiffre);
bool possible(tGrille grille,int ligne,int colonne,int recherche);
bool quietPossible(tGrille grille,int ligne,int colonne,int recherche,int ligneIntrus,int colonneIntrus,int valeurIntrus);
bool grillePleine(tGrille grille);
void ligneTiret(int colonne);

/**
 * \detail Grille imposée
 * 
 * Permet de vérifier les caractères par rapport a la grille imposée a tout moment dans l'éxécution du programme
*/
tGrille grilleImposee; //variable globale pour une question d'acces

/**
* \fn int main()
* \detail Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal met en oeuvre les différentes fonctions et proédures afin de permettre de jouer une partie
* de sudoku
*/
int main(){
    jOli joli;
    joli[0] = 'j';
    joli[1] = 'o';
    joli[2] = 'l';
    joli[3] = 'i';

    for (int i = 0; i < 4; i++)
    {
        printf("%c",joli[i]);
    }
    printf("\n");
    

    tGrille grille1;
    int numLigne,numColonne,valeur;
    chargerGrille(grille1);
    afficherGrille(grille1,-1,-1,-1);
    while (!grillePleine(grille1))
    {
        printf("Indices de la case?\n");
        saisir(&numLigne);
        afficherGrille(grille1,numLigne-1,-1,-1);
        saisir(&numColonne);
        if ( grille1[numLigne-1][numColonne-1] != CASE_GRILLE_VIDE )
        {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }else{
            afficherGrille(grille1,numLigne -1,numColonne -1,-1);
            printf("Valeur a insérer ? ");
            saisir(&valeur);
            if (possible(grille1,numLigne,numColonne,valeur))
            {
                grille1[numLigne-1][numColonne-1] = valeur;
                afficherGrille(grille1,-1,-1,-1);
            }else{
                afficherGrille(grille1,numLigne -1,numColonne -1,valeur);
            }
        }
    }
    printf("Grille pleine partie terminé\n");
}


/**
* \fn void chargerGrille(tGrille g)
* \detail Initialise les grilles passées en paramètre
* \param g : Paramètre d'entrée/sortie qui représente la grille a remplir
* 
* Cette procédure initialise la grille passée en paramètre ainsi qu'une grille appellée "grilleImpose"
* A cause de problème de lecture elle initialise aussi la grille a 0 avant de lire les valeurs du fichier.
* 
*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    for (int i = 0; i < TAILLE; i++) //initialise la grille a 0 sinon meme si il y a une erreur de fichier la grille n'affiche pas d'erreur
    {
        for (int j = 0; j < TAILLE; j++)
        {
            g[i][j] = CASE_GRILLE_VIDE;
        }   
    }
    

    //strcpy(nomFichier,"Grille1.sud"); //permet de ne pas taper le nom de la grille pendant les phases de test
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int),TAILLE*TAILLE, f);
    }
    fclose(f);

    //initialise la grille dite impose
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(grilleImposee, sizeof(int),TAILLE*TAILLE, f);
    }
    fclose(f);
}
/************************
 *Fonctions d'afffichage*
*************************/
/**
* \fn void afficherGrille(tGrille aAfficher,int ligne,int colonne,int erreur)
* \detail Se charge de l'affichage de la grille
* \param aAfficher : Paramètre d'entrée correspondant à la grille à afficher
* \param ligne : Paramètre d'entrée correspondant à la ligne séléctionnée par l'utilisateur( doit etre -1 si pas de ligne séléctionnée)
* \param colonne : Paramètre d'entrée correspondant à la colonne séléctionnée par l'utilisateur( doit etre -1 si pas de colonne séléctionnée)
* \param erreur : Paramètre d'entrée permettant a la fonction de savoir si il y a des chffres qui posent problème et indique le chiffre en question( doit etre -1 si pas de valeur séléctionnée)
* 
* Cette procédure gère les différents afichages de la grille.
* Elle affiche la Grille imposée en rouge sur fond noir
* Elle affiche les charactères des lignes/colonnes en noir sur fond blanc
* Elle affiche les charactères qui posent problème pour poser un chiffre en blanc sur fond rouge
* Elle affiche en blanc sur fond noir tout caractère sans modification
* 
*/
void afficherGrille(tGrille aAfficher,int ligne,int colonne,int erreur){
    printf("      ");
    for (int k = 0; k < TAILLE; k++) {//change de colonne
        if (k == colonne)
        {
            printf(" \33[1;30;47m%d\033[0m",k+1);
        }else{
            printf("%2d",k+1);
        }
        
        if ((k-2) % 3 == 0){//vérifie si on peut placer un espace (-2 car on regarde la case précédente ET l'indice du tableau commence a 0)
            printf("  ");
        }
    }
    ligneTiret(colonne);

    for (int i = 0; i < TAILLE; i++) { //change de ligne
        if ( i == ligne){
            printf("\033[1;30;47m%2d   |\033[0m",i+1);
        }else{
            printf("%2d   |",i+1); //affichage de l'indice de colonne
        }
        for (int j = 0; j < TAILLE; j++) {//change de colonne
            if (aAfficher[i][j] != CASE_GRILLE_VIDE){ //est-ce que je dois affiche un point ?
                if ( ( erreur != -1 ) && !quietPossible(aAfficher,i +1,j+1,aAfficher[i][j],ligne,colonne,erreur)) // est-ce que le chiffre pose problème ?
                {
                    if (i == ligne)//le chiffre pose problème ET est sur la ligne séléctionnée
                    {
                        printf("\033[1;37;41m%2d\033[0m",aAfficher[i][j]);//blanc sur fond rouge avec l'espace
                    }else{// le chiffre pose juste problème
                        printf(" \033[1;37;41m%d\033[0m",aAfficher[i][j]);//blanc sur fond rouge sans l'espace
                    } 
                }else{ // le chiffre ne pose pas problème
                    if ( ( ligne == -1 ) && ( colonne == -1 ) ){ // pas de ligne ni colonne séléctionnée
                        if ( aAfficher[i][j] == grilleImposee[i][j] ){ //est-ce que le chiffre est fixe?
                            printf("\033[1;31m%2d\033[0m",aAfficher[i][j]); //rouge sur fond noir
                        }else{
                            printf("%2d",aAfficher[i][j]); //sans couleur
                        }
                    }else if ( (ligne != -1) && (colonne == -1) ){ //seulement la ligne séléctionnée
                        if (  (aAfficher[i][j] == grilleImposee[i][j]) && ( i == ligne) ){ // es ce que le chiffre est fixe ET sur la ligne?
                            printf("\033[1;31;47m%2d\033[0m",aAfficher[i][j]); //rouge sur fond blanc
                        }else if ( aAfficher[i][j] == grilleImposee[i][j] ){ // juste fixe mais pas sur la ligne
                            printf("\033[1;31m%2d\033[0m",aAfficher[i][j]); //rouge sur fond noir
                        }else{ //pas fixe
                            if (i == ligne){
                                printf("\033[1;30;47m%2d\033[0m",aAfficher[i][j]); //noir sur fond blanc
                            }else{
                                printf("%2d",aAfficher[i][j]); //normal
                            }
                        }
                    }else{ // ligne + colonne séléctionnées
                        if ( ligne == i ){
                            printf("\033[1;30;47m%2d\033[0m",aAfficher[i][j]); //noir sur fond blanc
                        }else if(colonne == j){
                            printf(" \033[1;30;47m%d\033[0m",aAfficher[i][j]); //noir sur fond blanc
                        }else if ( aAfficher[i][j] == grilleImposee[i][j] ){
                            printf("\033[1;31m%2d\033[0m",aAfficher[i][j]); //rouge sur fond noir
                        }else{
                            printf("%2d",aAfficher[i][j]); //normal
                        }
                    }
                }
            }else{ // affichage de point
                if ( ligne == i ){
                    printf("\033[1;30;47m%2c\033[0m",RIEN); //noir sur fond blanc avec l'espace de devant
                }else if( colonne == j ){
                    printf(" \033[1;30;47m%c\033[0m",RIEN); //noir sur fond blanc sans l'espace de devant
                }else{
                    printf("%2c",RIEN);
                }
            }
            if ((j-2) % 3 == 0){ //vérifie si on peut placer un "|" (-2 car on regarde la case précédente ET l'indice du tableau commence a 0)
                if ( i == ligne ) {
                    printf("\033[1;30;47m |\033[0m"); //noir sur fond blanc
                }else{
                    printf(" |");
                }
            }
        }
        if ((i-2) % 3 == 0){ //vérifie si on peut placer une ligne de tiret (-2 car on regarde la case précédente ET l'indice du tableau commence a 0)
            if (colonne != -1){
                ligneTiret(colonne);
            }else{
                ligneTiret(-1);
            }
        }else{
            printf("\n");
        }
    }
}

/**
 * \fn void ligneTiret(int colonne)
 * \detail affiche une ligne de tiret
 * \param colonne : Paramètre d'entrée qui correspond a une colonne séléctionnée
 * \see void afficherGrille(tGrille aAfficher,int ligne,int colonne,int erreur)
 * 
 * Utilisé par afficherGrille. Cette procédure affiche une ligne de tiret. Elle affiche en noir sur fond blanc le tiret de la colonne séléctionnée
*/
void ligneTiret(int colonne){
    float colonneCalcul;
    colonneCalcul = 0;
    colonneCalcul++;

    printf("\n"); 
    printf("     +");
    for (int j = 0; j < TAILLE/3; j++){ //répète le nombre de bloc
        printf("-");
        for (int i = 0; i < 5; i++){ // il faut afficher 5 tiret pour remplir un bloc
            if (colonneCalcul == ((colonne * 1.0) +1 ))
            {
                printf("\033[1;30;47m-\033[0m"); //noir sur fond blanc
            }else{
                printf("-");
            }
            colonneCalcul = colonneCalcul + 0.5; //il faut poser un tiret toute les 1/2 colonnes
        }
        colonneCalcul = colonneCalcul + 0.5;
        printf("-+");
    }
    printf("\n");
}
/********************************
 *fin des fonctions d'afffichage*
********************************/

/**
 * \fn void saisir(int *chiffre)
 * \detail Permet de saisir une veleur
 * \param chiffre : Paramètre d'entrée/sortie utilisé principalement en sortie. C'est le chiffre saisi
 * 
 * Permet la saisie d'un chiffre après vérification que le chiffre est valide ( entre 1 et 9 et entier).
 * Elle redemande la saisie en cas d'erreur
*/
void saisir(int *chiffre){
    int entreeInt;
    char entree[2];

    printf("Merci d'entrer un chiffre entre 1 et %d inclus\n>",TAILLE);
    scanf("%s",entree);

    while ( (sscanf(entree,"%d",&entreeInt) == 0) || ( entreeInt <= 0 ) || ( entreeInt > TAILLE ))
    {
        printf("Entrée invalide merci d'entrer un chiffre entre 1 et %d inclus\n",TAILLE);
        printf(">");
        scanf("%s",entree);
    }
    *chiffre = entreeInt;
}

/**
 * \fn bool possible(tGrille grille,int ligne,int colonne,int recherche)
 * \detail Vérifie si on peut placer une chiffre
 * \param grille : Paramètre d'entrée dans laquelle on recherche la valeur
 * \param ligne : Paramètre d'entrée de la ligne de la valeur que l'on vérifie
 * \param colonne : Paramètre d'entrée de la colonne de la valeur que l'on vérifie
 * \param recherche : Paramètre d'entrée corespondant a la valeur que l'on recherche
 * \return true si le chiffre est placable et false si l'entreé est considérée comme invalide
 * 
 * Fonction qui vérifie si l'on peut, ou non placer le chiffre dans : la colonne, la ligne et le block de 3*3
*/
bool possible(tGrille grille,int ligne,int colonne,int recherche){
    bool trouve,ligneBool,colonneBool;
    bool blocBool;
    trouve = false;
    ligneBool = false;
    colonneBool = false;
    blocBool = false;
    ligne = ligne-1;
    colonne = colonne -1;



    //vérifie si le caractère est présent dans la ligne
    for (int iLigne = 0; iLigne < TAILLE; iLigne++)
    {
        if ( grille[ligne][iLigne] == recherche )
        {
            trouve = true;
            ligneBool = true;
        }
    }

    //vérifie si le caractère est présent dans la colonne
    for (int iColonne = 0; iColonne < TAILLE; iColonne++)
    {
        if ( grille[iColonne][colonne] == recherche )
        {
            trouve = true;
            colonneBool = true;
        }
    }

    //j'initialise les coordonées auxquelles mon programme va devoir chercher dans le block

    //je calcule la position dans le bloc
    int positionLigneDansBloc,positionColonneBloc;
    positionColonneBloc = colonne + 1 ;
    positionLigneDansBloc = ligne + 1;
    while ( positionLigneDansBloc > 3 ){
        positionLigneDansBloc = positionLigneDansBloc - 3;
    }
    while ( positionColonneBloc > 3 ){
        positionColonneBloc = positionColonneBloc - 3;
    }


    //j'en déduis les coordonées de début et de fin de la recherche du chiffre
    int maxLigne,minLigne;
    if (positionLigneDansBloc == 3) {
        minLigne = ligne -2;
        maxLigne = ligne;
    }else if ( positionLigneDansBloc == 2) {
        minLigne = ligne - 1;
        maxLigne = ligne + 1;
    }else if( positionLigneDansBloc == 1){
        minLigne = ligne;
        maxLigne = ligne +2;
    }else{
        printf(">Erreur inatendue\n");
    }
    
    int maxColonne,minColonne;
    if ( positionColonneBloc == 3 ) {
        minColonne = colonne -2;
        maxColonne = colonne;
    }else if ( positionColonneBloc == 2 ) {
        minColonne = colonne - 1;
        maxColonne = colonne + 1;
    }else if (positionColonneBloc == 1 ){
        minColonne = colonne;
        maxColonne = colonne +2;
    }else{
        printf(">Erreur inatendue\n");
    }
    
    //j'éffectue ma recherche grace a mes coordonées:
    for (int iLigneBloc = minLigne; iLigneBloc < maxLigne; ++iLigneBloc) { //change la ligne
        for (int iColBloc = minColonne; iColBloc < maxColonne; ++iColBloc) { //change la colonne
            if ( grille[iLigneBloc][iColBloc] == recherche )
            {
                trouve = true;
                blocBool = true;
            }
        }
    }
    if (trouve)
    {
        if (ligneBool == true)
        {
            printf("La valeur est deja présente dans la ligne\n");
        }else if (colonneBool == true)
        {
            printf("La valeur est deja présente dans la colonne\n");
        }else if(blocBool == true)
        {
            printf("La valeur est deja présente dans le bloc\n");
        }
    }
    return !trouve; // la saisie est possible si je ne trouve rien je renvoie donc l'opposé
}


/**
 * \fn bool quietPossible(tGrille grillePre, int ligne, int colonne, int recherche, int ligneIntrus, int colonneIntrus, int valeurIntrus)
 * \detail Vérifie si on peut placer une chiffre.
 *
 * \param grillePre Paramètre d'entrée dans laquelle on recherche la valeur.
 * \param ligne Paramètre d'entrée de la ligne de la valeur que l'on vérifie.
 * \param colonne Paramètre d'entrée de la colonne de la valeur que l'on vérifie.
 * \param recherche Paramètre d'entrée correspondant à la valeur que l'on recherche.
 * \param ligneIntrus Paramètre d'entrée correspondant à la ligne de l'intrus.
 * \param colonneIntrus Paramètre d'entrée correspondant à la colonne de l'intrus.
 * \param valeurIntrus Paramètre d'entrée correspondant à la valeur de l'intrus.
 * \return False si le chiffre recherche pose problème par rapport à l'intrus.
 * \see bool possible(tGrille grille, int ligne, int colonne, int recherche)
 * 
 * Cette fonction place le chiffre intrus dans une grille alternative et vérifie si le chiffre recherche 
 * poserait problème par rapport à l'intrus. Elle est utilisée par afficherGrille et est une copie
 * de la fonction possible sans les messages d'erreur.
 */
bool quietPossible(tGrille grillePre, int ligne, int colonne, int recherche, int ligneIntrus, int colonneIntrus, int valeurIntrus){
    bool trouve;
    ligne = ligne-1;
    colonne = colonne -1;
    tGrille grille;
    trouve = false;

    //je copie la grille et je fais comme si l'intrus a tester y étais, comme ca si le chiffre a chercher trouve l'intrus alors il pose problème pour poser l'intrus
    for (int iCopie = 0; iCopie < TAILLE; iCopie++)
    {
        for (int jCopie = 0; jCopie < TAILLE; jCopie++)
        {
            grille[iCopie][jCopie]=grillePre[iCopie][jCopie];
        }
    }
    grille[ligneIntrus][colonneIntrus] = valeurIntrus;

    //a partir d'ici c'est exactement la même que possible mais sans les printf

    //vérifie si le caractère est présent dans la ligne
    for (int iLigne = 0; iLigne < TAILLE; iLigne++)
    {
        if ( ( grille[ligne][iLigne] == recherche ) && (iLigne != colonne ) )
        {
            trouve = true;
        }
    }

    //vérifie si le caractère est présent dans la colonne
    for (int iColonne = 0; iColonne < TAILLE; iColonne++)
    {
        if ( (grille[iColonne][colonne] == recherche) && (iColonne != ligne ) )
        {
            trouve = true;
        }
    }

    //j'initialise les coordonées auxquelles mon programme va devoir chercher dans le block

    //je calcule la position dans le bloc
    int positionLigneDansBloc,positionColonneBloc;
    positionColonneBloc = colonne + 1 ;
    positionLigneDansBloc = ligne + 1;
    while ( positionLigneDansBloc > 3 ){
        positionLigneDansBloc = positionLigneDansBloc - 3;
    }
    while ( positionColonneBloc > 3 ){
        positionColonneBloc = positionColonneBloc - 3;
    }


    //j'en déduis les coordonées de début et de fin de la recherche du chiffre
    int maxLigne,minLigne;
    if (positionLigneDansBloc == 3) {
        minLigne = ligne -2;
        maxLigne = ligne;
    }else if ( positionLigneDansBloc == 2) {
        minLigne = ligne - 1;
        maxLigne = ligne + 1;
    }else if( positionLigneDansBloc == 1){
        minLigne = ligne;
        maxLigne = ligne +2;
    }else{
        printf(">Erreur inatendue\n");
    }
    
    int maxColonne,minColonne;
    if ( positionColonneBloc == 3 ) {
        minColonne = colonne -2;
        maxColonne = colonne;
    }else if ( positionColonneBloc == 2 ) {
        minColonne = colonne - 1;
        maxColonne = colonne + 1;
    }else if (positionColonneBloc == 1 ){
        minColonne = colonne;
        maxColonne = colonne +2;
    }else{
        printf(">Erreur inatendue\n");
    }
    
    //j'éffectue ma recherche grace a mes coordonées:
    for (int iLigneBloc = minLigne; iLigneBloc < maxLigne; ++iLigneBloc) {//change la ligne
        for (int iColBloc = minColonne; iColBloc < maxColonne; ++iColBloc) {//change la colonne
            if ( (grille[iLigneBloc][iColBloc] == recherche) && ( ( iLigneBloc != ligne ) && ( iColBloc != colonne ) ) )
            {
                trouve = true;
            }
        }
    }
    return !trouve;//retourne false si on a trouvé le chiffre
}

/**
 * \fn bool grillePleine(tGrille grille)
 * \detail Vérifie si la grille est pleine
 * \param grille :Grille à vérifier
 * \return true si la grille est pleine et false si elle est vide
 * 
 * Cette fonction fait une recherche dans la grille pour vérifier si il reste une case vide
*/
bool grillePleine(tGrille grille){
    bool trouve;
    for (int i = 0; i < TAILLE; i++){//change de ligne
        for (int j = 0; j < TAILLE; j++){//change de colonne
            if ( grille[i][j] == CASE_GRILLE_VIDE )
            {
                trouve = true;
            }
        }
    }
    return !trouve;// je retourne l'inverse de trouver car si il n'y a pas de cse vide la grille est pleine
}
