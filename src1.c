/**
 * Le fichier source contient un programme pour imprimer 
 * le calendrier d'une année spécifiée.
*/
#include <stdio.h>

/**
* \brief Calcule l'indice du jour de la semaine pour une date donnée
* \details Utilise l'algorithme de Zeller pour déterminer l'indice du jour de la semaine
* \param int jour Jour de la date
* \param int mois Mois de la date
* \param int annee Année de la date
* \return int Indice du jour de la semaine (0 pour dimanche, 1 pour lundi, etc.)
*/
int jourDeLaSemaine(int jour, int mois, int annee)
{
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    annee -= mois < 3;
    return (annee + annee / 4
            - annee / 100
            + annee / 400
            + t[mois - 1] + jour)
           % 7;
}

/**
* \brief Renvoie le nom du mois pour un numéro de mois donné
* \param int numeroMois Numéro du mois (0 pour janvier, 1 pour février, etc.)
* \return char* Nom du mois
*/
char* getNomDuMois(int numeroMois)
{
    char* mois;

    switch (numeroMois) {
    case 0:
        mois = "Janvier";
        break;
    case 1:
        mois = "Février";
        break;
    case 2:
        mois = "Mars";
        break;
    case 3:
        mois = "Avril";
        break;
    case 4:
        mois = "Mai";
        break;
    case 5:
        mois = "Juin";
        break;
    case 6:
        mois = "Juillet";
        break;
    case 7:
        mois = "Août";
        break;
    case 8:
        mois = "Septembre";
        break;
    case 9:
        mois = "Octobre";
        break;
    case 10:
        mois = "Novembre";
        break;
    case 11:
        mois = "Décembre";
        break;
    }
    return mois;
}

/**
* \brief Renvoie le nombre de jours dans un mois pour une année donnée
* \detail renvoi le nombre de jour dans un mois en calculant a partir des paramètres
*
* \param int numeroMois Numéro du mois (0 pour janvier, 1 pour février, etc.)
* \param int annee Année
* \return int Nombre de jours dans le mois
*/
int nombreDeJours(int numeroMois, int annee)
{
    // Janvier
    if (numeroMois == 0)
        return (31);

    // Février
    if (numeroMois == 1) {
        // Si l'année est bissextile, alors Février a 29 jours
        if (annee % 400 == 0
            || (annee % 4 == 0
                && annee % 100 != 0))
            return (29);
        else
            return (28);
    }

    // Mars
    if (numeroMois == 2)
        return (31);

    // Avril
    if (numeroMois == 3)
        return (30);

    // Mai
    if (numeroMois == 4)
        return (31);

    // Juin
    if (numeroMois == 5)
        return (30);

    // Juillet
    if (numeroMois == 6)
        return (31);

    // Août
    if (numeroMois == 7)
        return (31);

    // Septembre
    if (numeroMois == 8)
        return (30);

    // Octobre
    if (numeroMois == 9)
        return (31);

    // Novembre
    if (numeroMois == 10)
        return (30);

    // Décembre
    if (numeroMois == 11)
        return (31);
}

/**
* \brief Imprime le calendrier pour une année donnée
* \detail prend en paramètre une année et print l'intégralitée de son calendrier
* \param int annee Année pour laquelle le calendrier est généré
*/
void imprimerCalendrier(int annee)
{
    printf("     Calendrier - %d\n\n", annee);
    int jours;

    // Indice du jour de 0 à 6
    int actuel = jourDeLaSemaine(1, 1, annee);

    // i pour itérer à travers les mois
    // j pour itérer à travers les jours
    // du mois - i
    for (int i = 0; i < 12; i++) {
        jours = nombreDeJours(i, annee);

        // Imprimer le nom du mois actuel
        printf("\n ------------%s-------------\n",
               getNomDuMois(i));

        // Imprimer les colonnes
        printf(" Dim   Lun  Mar  Mer  Jeu  Ven  Sam\n");

        // Imprimer les espaces appropriés
        int k;
        for (k = 0; k < actuel; k++)
            printf("     ");

        for (int j = 1; j <= jours; j++) {
            printf("%5d", j);

            if (++k > 6) {
                k = 0;
                printf("\n");
            }
        }

        if (k)
            printf("\n");

        actuel = k;
    }
}

/**
* \brief Fonction principale
* \detail se sert de toute les procédures et fonctions précédentes
* \return int Code de retour
*/
int main()
{
    int annee; // Année pour laquelle le calendrier est généré
    printf("Entrez l'année souhaitée : ");
    scanf("%d", &annee);

    // Appel de la fonction
    imprimerCalendrier(annee);
    return 0;
}

