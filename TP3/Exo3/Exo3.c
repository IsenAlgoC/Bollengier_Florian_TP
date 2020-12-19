#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<locale.h>

#define NBMAXNOTES 30 /* taille du tableau */

void swap(int* a, int* b)	/* definition de la fonction pour intervertir 2 valeurs */
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(float arr[], int arr2[], int low, int high) /* Definition de la fonction pour trouver le pivot du quickSort*/
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index du plus petit element

	for (int j = low; j <= high - 1; j++)
	{
		// Si l'élément est plus petit que le pivot
		if (arr[j] < pivot)
		{
			i++;    // incremente l'index du plus petit élement
			swap(&arr[i], &arr[j]);
			swap(&arr2[i], &arr2[j]);

		}
	}
	swap(&arr[i + 1], &arr[high]);
	swap(&arr2[i + 1], &arr2[high]);

	return (i + 1);
}

void quickSort(float arr[], float arr2[], int low, int high)/* appel des fonctions pour le quickSort */
{
	if (low < high)
	{
		int pi = partition(arr, arr2, low, high);
		quickSort(arr, arr2, low, pi - 1);
		quickSort(arr, arr2, pi + 1, high);
	}
}

int main()
{
	setlocale(LC_ALL, "fr-FR");
	float moyenne = 0; /* moyenne des notes */
	int nb = 0; /* nombre de note entrées*/
	int nb2 = 0; /* nombre de note entrées pour suivre l'indice */
	float note[NBMAXNOTES]; /* note entrée */
	int indice[NBMAXNOTES] = { 0 }; /* indice des notes */
	char rep = 0; /* stocke la rep user*/
	bool arret = false; /* condition de sortie du do while*/
	int abs = 0; /* compteur d'absent(s) */
	float max = 0; /* valeur maximale du tableau initialisé à 0 par dafaut */
	float min = 20; /* valeur minimale du tableau initialisé à 20 par defaut*/
	int i = 0; /* compteur */
	float somme = 0; /* somme des notes du tableau */
	float var = 0; /* calcule la variance*/
	float ec = 0; /* calcule l'écart type*/
	float rank[NBMAXNOTES]; /* tableau de note rangées */
	int n = sizeof(rank) / sizeof(rank[0]); // définition du quickSort
	int j = 0; /* compteur */


	for (i = 0; i < NBMAXNOTES; i++) /* remplir le tableau de -2 */
	{
		note[i] = -2;
	}

	do
	{
		printf("entrez la note no %d :\n", nb + 1 - abs); /* récuperation des notes */
		scanf_s("%f", &note[nb]);


		if ((note[nb] >= 0) && (note[nb] <= 20)) /* teste si la note respecte les conditions */
		{
			if (note[nb] > max) /* cherche la valeur maximale */
			{
				max = note[nb];
			}
			if (note[nb] < min) /* cherche la valeur minimale */
			{
				min = note[nb];
			}
			indice[nb2] = nb2 + 1;
			nb++; /* incrementation du nombre de note */
			nb2++; /* incrementation de l'indice de note */

		}
		else /* si conditions non respectees */
		{
			note[nb] = -2;
			printf("Vous avez tapé une note invalide, l'élève est-il (A)bsent ou voulez vous arrêter la saisie (O)ui (N)on ?\n"); /* demande l'intention de l utilisateur */
			rep = _getch();/* recupération de la saisie du clavier */

			if (rep == 'A') /* il y a un absent */
			{
				note[nb] = -1; /* ajoute un absent au tableau */
				nb = nb + 1; /* incremente le compteur de note */
				abs++; /* incremente le nombre d'absent*/
				printf("un absent a ete comptee\n");
			}
			if (rep == 'O')
			{
				arret = true; /* sort du do while */
			}
			if (rep == 'N')
			{
				printf("reprise du programe\n"); /* Reprise du programme en demandant une nouvelle note*/
			}
		}

	} while ((nb < 30) && (arret == false)); /* boucle tant que 30 notes sont pas rentrées ou tant que l'utilisateur ne dit pas stop*/

	for (i = 0; i < nb; i++) /* parcours le tableau pour les resultats finaux */
	{

		if ((note[i] != -2) && (note[i] != -1)) /* conditions d une note valide*/
		{
			somme = (somme + note[i]); /* effectue la somme des notes valides */
		}
	}
	moyenne = somme / ((nb)-abs);
	i = 0;
	for (i = 0; i < nb; i++) /* parcours le tableu pour les resultats finaux */
	{
		if ((note[i] != -2) && (note[i] != -1)) /* condition d'une note*/
		{
			var = var + pow((note[i] - moyenne), 2);
		}

	}
	var = var / (nb - 1 - abs);
	ec = sqrt(var);

	printf("La moyenne est de %.2f\nIl ya %d absences.\nla plus petite note est %.2f, la plus grande est %.2f,\nL écart type vaut %.2f\n", moyenne, abs, min, max, ec); /* affichage des resultats */
	printf("\n");
	printf("No note Valeur note\n");
	for (i = 0; i < nb; i++) /* affiche le tableau non trié*/
	{
		if ((note[i] != -2) && (note[i] != -1)) /* condition d une note valide */
		{
			rank[j] = note[i]; /* copie les notes de i dans rank pour ranger rank (tri)*/
			j++; // parcours rank 
			printf("%d \t %.2f\n", indice[i], note[i]); /* affiche les notes et leur ordre d entrée*/

		}
	}
	quickSort(rank, indice, 0, n - 1); /* appel de la fonction de tri*/
	printf("\n");
	printf("tableau trié\n");
	printf("Rang:\t No note \t Valeur note \n");
	for (i = 30; i > 0; i--) /* affiche le tableau non trié */
	{
		if (((rank[i] <= 20) && (rank[i] >= 0)) && (indice[i] > 0)) /* condition pour afficher seulement les notes sans addresse tab (quicksort commence par la fin du tableau) */
		{
			printf("%d \t %d \t\t %.2f\n", 30 - i, indice[i], rank[i]);
		}
	}
	return 0;
}
