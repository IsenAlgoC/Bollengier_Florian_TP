#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define CARRE(x) (x)*(x) /* define du calcul du carre */

int main()
{
	int nbr = 5; /*initialisation du nombre � 5 */
	printf("le carre de 5 est %d\n", CARRE(nbr)); /* affichage du carr� du nombre */
	printf("le carre de 5+1 est %d\n", CARRE(nbr + 1)); /* probl�me de priorit� de calcul non respect�, donc il faut ajouter des parenth�ses */
	return 0;
}
