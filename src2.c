/**
 * Programme de calculatrice
 * Programme calculatrice
 * 
 */


                        /*****************************************************
                                * AJOUT DES LIBRAIRIES NECESSAIRES*
                        *****************************************************/

#include <stdio.h>


enum {     /** structure des opérations*/
   ADD = 1,    /** addition*/
   SUBTRACT,  /** soustraction*/
   MULTIPLY,  /** multiplication*/
   DIVIDE,   /** Division*/
   YES = 10,
   NO = 20,
};

void affichage();

                        /*****************************************************
                                        * PROGRAMME PRINCIPAL *
                        *****************************************************/

/**
* \brief Programme principale
* \detail Cette fonction sers a écécuter l'intégralitée des opérations tel que:
* - une division
* - une addition
* - une multiplication
* - une soustraction
*
* c'est très basique
* \return int le code d'erreur ou de succes
*/

int main(void) {     // programme principal
   int choice;      // Variable qui permet de choisir le type d'opérations
   double values[2];


   for(;;) {     // boucle infinie pour pouvoir effectuer plusieurs calculs sans devoir re-compiler
       printf(
           "\n\nC a l c u l a t o r\n\n"   // affichage du menu
           "C h o o s e :\n\n"
           " S u m    ( 1 )  \t"
           " S u b t r a c t i o n    ( 2 )\n\n"
           " M u l t i p l i c a t i o n    ( 3 )  \t"
           " D i v i s i o n    ( 4 )\n\n"
       );
       if(scanf(" %d", &choice) != 1) {    // Condition si le choix entré n'est pas correct ( Si il n'y a pas qu'une valeur )
            printf("La valeur entrée est incorrect\n");
            return 1;
       }
       printf("\n\nE n t e r   F i r s t    N u m b e r :\n");    
       if(scanf("%lf", &values[0]) != 1) {
            printf("La valeur entrée est incorrect\n");   // Condition si le choix entré n'est pas correct ( Si il n'y a pas qu'une valeur )
            return 1;
       }
       printf("\n\nE n t e r   S e c o n d    N u m b e r :\n");
       if(scanf("%lf", &values[1]) != 1) {
            printf("La valeur entrée est incorrect\n");    // Condition si le choix entré n'est pas correct "flottant" ( Si il n'y a pas qu'une valeur )
            return 1;
       }


       if (choice == ADD) {                                 // SI le choix = ADD, l'utilisateur a choisi l'addition
           double result = values[0] + values[1];  //Calcul
           printf("%g + %g = %g", values[0], values[1], result);
       } else if(choice == SUBTRACT) {                     // Si le choix = SUBSTRACT, l'utilisateur a choisi la soustraction
           double result = values[0] - values[1];    //Calcul
           printf("%g - %g = %g", values[0], values[1], result);
       } else if(choice == MULTIPLY) {                     // Si le choix = MULTIPLY, l'utilsateut a choisi la multiplication
           double result = values[0] * values[1];   //Calcul
           printf("%g * %g = %g", values[0], values[1], result);
       } else if(choice == DIVIDE) {                        // Si le chois = DIVIDE, l'utilisateur a choisi la division
           double result = values[0] / values[1];   //Calcul
           printf("%g / %g = %g", values[0], values[1], result);     // affichage du résultat
       }
       printf("\n\nC h o o s e     a g a i n ?\n");   // demande à l'utilisateur si il souhaite réaliser une nouvelle opération
       printf("    ( Y e s     = =    S a y     1 0 !)\n");
       printf("    ( N o     = =    S a y     2 0 !)\n");
       if(scanf("%d", &choice) != 1) {     // determine le choix de l'utilisateur et fait en fonction
            printf("La valeur entrée est incorrect\n");
            return 1;
       }
       if(choice == NO)  // Si l'utilisateur entre " NO ", arrêt du programme
           break;
   }
   printf("\n\n F I N\n\n"); // Affiche la fin du programme à l'utilisateur
   affichage();
}

/**
* \brief Fonction d'affichage
* \detail ca sert a rien
* - du tout
* - vraiment rien
* - meme pas a faire joli
* - mais il fallais deux fonctions et la calculatrice étais pas bien longue...
*
* vous allez bien?
*/
void affichage(){
    printf("coucou je sers a rien mdr");
}
