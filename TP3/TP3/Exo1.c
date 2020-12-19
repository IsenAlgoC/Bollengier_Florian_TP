#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define CARRE(x) (x)*(x) /* define du calcul du carre */

int main()
{
	int nbr = 5; /*initialisation du nombre à 5 */
	printf("le carre de 5 est %d\n", CARRE(nbr)); /* affichage du carré du nombre */
	printf("le carre de 5+1 est %d\n", CARRE(nbr + 1)); /* problème de priorité de calcul non respecté, donc il faut ajouter des parenthèses */
	return 0;
}
