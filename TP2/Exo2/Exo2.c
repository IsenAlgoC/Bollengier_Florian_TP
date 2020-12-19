#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>


int main()
{
	setlocale(LC_ALL, "fr-FR");

	float longueur, largeur, hauteur; /* variables pour les dimensions du bagage */
	bool check = false; /* variable pour verifier que l'on recupere bien 3 valeurs */
	bool boucle = false;/* variable pour relancer le programme une fois un bagage testé */
	int go = 2;/* variable pour stocker l'intention de l utilisateur, initialisé a 2 car le test effectué est sur 0 ou 1*/

	do
	{
		printf("Voulez vous tester un bagage, si oui taper 1, sinon taper 0\n"); /* Savoir si l'utilasateur veut tester un bagage*/
		scanf_s("%d", &go);
		if (go == 1) /* verifie si l'utilisateur veut tester son bagage */
		{
			do
			{
				printf("Entrez la longeur de votre bagage\n"); /* recupère la longueur */
				scanf_s("%f", &longueur);

				printf("Entrez la largeur de votre bagage\n"); /* recupère la largeur */
				scanf_s("%f", &largeur);

				printf("Entrez la hauteur de votre bagage\n"); /* recupère la hauteur */
				scanf_s("%f", &hauteur);

				if (((longueur < 1) || (longueur > 150)) || ((largeur < 1) || (largeur > 150)) || ((hauteur < 1) || (hauteur > 150))) /* test dimensions */
				{
					printf("Invalide\n"); /* message d erreur */
					printf("Une ou plusieurs dimmensions est inferieur a 0 ou superieur a 150 cm \n");

					if ((longueur > 55) || (largeur > 35) || (hauteur > 25)) /* teste les conditions de dimension de bagage */
					{
						printf("votre bagage est trop grand\n"); /* message de refus */
					}
					else
					{
						printf("bagage valide\n"); /* bagage validé */
					}
				}
				else
				{
					check = true; /* 3 valeur entrées et bonne */
					printf("Votre bagage est validé\n");/* meaasage de validation*/
				}

			} while (check == false); /* boucle tant que 3 valeur bonnes ne sont pas entrees */
		}
		else /* si l'utilisateur ne veut pas tester de bagage */
		{
			boucle = true; /* change l'état de boucle pour relancer un test */
		}

	} while (boucle == false); /* si plus de test, arrête la boucle */

	system("PAUSE");
	return 0;
}
