#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compl�ter votre nom ici                                                */
/*   Nom :Bollengier                    Pr�nom :Florian                   */
/**************************************************************************/

extern bool modif;
#define IMPL_TAB // si d�fini, on compile pour une impl�mentation tableau du r�pertoire
// #define IMPL_LIST // si d�fini, on compile pour un impl�mentation Liste Cha�n�e du r�pertoire

/**********************************************************************/
/*  Ajout d'un contact dans le r�pertoire stock� en m�moire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compl�ter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr; 
		rep->nb_elts++;                   
		rep->est_trie = false;            
		modif = true;                     
		return(OK);
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		int i = 0;
		while ((i < rep->nb_elts) && (est_sup(enr, (GetElementAt(rep->liste, i)->pers)))) { i++; } 
		InsertElementAt(rep->liste, i, enr); 
		rep->nb_elts++;                      
		modif = true;                       
		rep->est_trie = true;                 
		return(OK);

	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compl�ter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		if (indice < rep->nb_elts)
		{
			for (int i = indice; i < rep->nb_elts - 1; i++)
			{
				*(rep->tab + i) = *(rep->tab + i + 1);
			}
		}
		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s, %s                 %s", enr.nom, enr.prenom, enr.tel); /* On affiche chaque champ avec le filtre %s */

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code � compl�ter ici
	// comme fonction affichage_enreg, mais avec pr�sentation align�es des infos
	printf("\n| %-30s|%-30s|%-20s", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code � compl�ter ici
	if (_stricmp(enr1.nom, enr2.nom) > 0) 
	{ 
		return(true); 
	} 
	if (_stricmp(enr1.nom, enr2.nom) < 0) { return(false); } 
	if (_stricmp(enr1.prenom, enr2.prenom) > 0) { 
		return(true);
	} 
	if (_stricmp(enr1.prenom, enr2.prenom) < 0)
	{
		return(false);
	}
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	int flag = 1; // flag servant � compter le nombres de permutations par boucle
	while (flag != 0)
	{
		flag = 0;
		for (int i = 0; i < rep->nb_elts - 1; i++)
		{
			if (est_sup(*(rep->tab + i), *(rep->tab + i + 1)))
			{
				Enregistrement tmp = *(rep->tab + i);
				*(rep->tab + i) = *(rep->tab + i + 1);
				*(rep->tab + i + 1) = tmp;
				flag++;
			}
		}
	}



	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
	strcpy_s(tmp_nom, MAX_NOM, nom);
	_strupr_s(tmp_nom, _countof(tmp_nom)); 
	ind_fin = rep->nb_elts;       
	for (int i = ind; i < ind_fin; i++)
	{
		strcpy_s(tmp_nom2, MAX_NOM, rep->tab + i);
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0)
		{
			return i;
		}
	}
	
#else
#ifdef IMPL_LIST
	strcpy_s(tmp_nom, MAX_NOM, nom);
	_strupr_s(tmp_nom, _countof(tmp_nom));
	ind_fin = rep->nb_elts;
	for (int i = ind; i < ind_fin; i++)
	{
		// on utilise la m�me mani�re que la liste � l'exeption de la mani�re dont on recup�re les �l�ment
		strcpy_s(tmp_nom2, MAX_NOM, GetElementAt(rep->liste, i)->pers.nom);
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0)
		{ 
			return i; 
		}
	}
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	char tab[MAX_TEL]; 
	int j = 0;       
	for (int i = 0; i < strlen(s); i++)
	{ 
		if (s[i] >= '0' && s[i] <= '9')
		{
			tab[j] = s[i];  
			j++;  
		}
	}
	tab[j] = '\0';  
	strcpy_s(s, MAX_TEL, tab); 
	return;
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");
	if (err != 0) 
	{ 
		return(ERROR);
	} 
	char buffer[MAX_NOM + MAX_NOM + MAX_TEL + 2];
	for (int i = 0; i < rep->nb_elts; i++) 
	{ 
		sprintf_s(buffer, MAX_NOM + MAX_NOM + MAX_TEL + 2, "%s%c%s%c%s\n", (rep->tab + i)->nom, SEPARATEUR, (rep->tab + i)->prenom, SEPARATEUR, (rep->tab + i)->tel);
		fputs(buffer, fic_rep); 
	}
	
#else
#ifdef IMPL_LIST
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w"); 
	if (err != 0)
	{ 
		return(ERROR);
	}
	char buffer[MAX_NOM + MAX_NOM + MAX_TEL + 2];
	for (int i = 0; i < rep->nb_elts; i++) 
	{
		
		sprintf_s(buffer, MAX_NOM + MAX_NOM + MAX_TEL + 2, "%s%c%s%c%s\n", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.tel);
		fputs(buffer, fic_rep);
	}
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				if (lire_champ_suivant(buffer, &idx, tmp.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;				
					if (lire_champ_suivant(buffer, &idx, tmp.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, tmp.tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		
					}
				}
				InsertElementAt(rep->liste, rep->liste->size, tmp);
#endif
#endif





			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */