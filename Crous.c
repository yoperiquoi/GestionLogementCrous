/*
Crous.c
Oscar CHAUMUZEAU
Thomas BLANC
Yoann PERIQUOI

Projet de structure de données
A1 2020

*/

#include"Crous.h"

Etudiant **chargerFetudiant (int *nb,int *max)
/*-----------------------//
Fonctionnalité : Charge le fichier texte étudiant dans un tableau dynamique
		     de pointeur sur structure.
Détails paramètres : nb => Nombre d'étudiants.
				 max => capacité maximale du tableau.  
return : retourne le tableau d'étudiant rempli. 
//-----------------------*/
{
	Etudiant **tab,**aux,e;
	FILE *flot;
	flot=fopen("etudiants.txt","r");
	if(flot==NULL)
	{
		printf("Probleme d'ouverture fichier : etudiants.txt.");
		exit(1);
	}
	*nb=0;
	*max=5;
	tab=(Etudiant**)malloc(*max*sizeof(Etudiant*));
	if(tab==NULL)
	{
		printf("Problème malloc pour les Etudiants");
		exit(2);
	}
	e=lireEtud(flot);
	while(!feof(flot))
	{
		if(*nb==*max)
		{
			aux=(Etudiant**)realloc(tab,(*max+5)*sizeof(Etudiant*));
			if(aux==NULL)
			{
				printf("problème realloc Etudiant");
				exit(2);
			}
			tab=aux;
			*max=*max+5;
		}
		tab[*nb]=(Etudiant*)malloc(sizeof(Etudiant));
		if(tab[*nb]==NULL)
		{
			printf("probleme realloc Etudiant");
			exit(2);
		}
		*tab[*nb]=e;
		*nb=*nb+1;
		e=lireEtud(flot);
	}
	fclose(flot);
	printf("\n\n\n");
	return tab;
}



Etudiant lireEtud(FILE *fe)
/*-----------------------//
Fonctionnalité : Lis une ligne d'etudiant 
Détails paramètres : Il reçoit le flot 
return : L'étudiant qui vient d'être lu
//-----------------------*/
{
	Etudiant e;
	fscanf(fe,"%d %s\n",&e.IdEtudiant,e.Civilite);
	fgets(e.Nom,22,fe);
	e.Nom[strlen(e.Nom)-1]='\0';
	fgets(e.Prenom,22,fe);
	e.Prenom[strlen(e.Prenom)-1]='\0';
	fscanf(fe,"\n%d%d%d",&e.Boursier,&e.Echelon,&e.Handicap);
	return e;
}


Etudiant **creationEtudiant(Etudiant **tetud,int *nbEtud,int *maxEtud,int *IdE,int *EchelonN)
/*-----------------------//
Fonctionnalité : Permet de remplir une structure étudiant avec 
			 les informations renseignées en paramètre.
Détails paramètres : tetud  => Tableau dynamique de pointeur sur structure. 
				 nbEtud => Nombre d'étudiants dans le tableau. 
				 maxEtud=> Nombre maximum de structure etudiant dans le tableau. 
				 IdE    => Identifiant de l'étudiant.
				 EchelonN=> Echelon de bourse. 
return : Retourne le tableau d'étudiant remplit avec le nouvel étudiant ajouté. 
//-----------------------*/
{
	Etudiant e;
	Etudiant **aux;
	int Civilite,trouve,rech,i;
	afficherEtudiants(tetud,*nbEtud);
	printf("Information à renseigner sur le nouvelle étudiant.\n");
	printf("Veuillez indiquer l'IdEtudiant et la civilité (Mr et Mme correspondant à 0 et 1) :\n");
	i=scanf("%d%d%*c",&e.IdEtudiant,&Civilite);
	rech=rechDico(tetud,*nbEtud,e.IdEtudiant,&trouve);
	while(trouve==1 || (Civilite!=0 && Civilite!=1))
	{
		printf("IdEtudiant ou civilité incorrect\n");
		printf("Veuillez indiquer l'IdEtudiant et la civilité (Mr et Mme correspondant à 0 et 1) :\n");
		scanf("%d%d%*c",&e.IdEtudiant,&Civilite);
		rech=rechDico(tetud,*nbEtud,e.IdEtudiant,&trouve);
	}
	if (Civilite==0)
		e.Civilite[0]='M';
	e.Civilite[1]='r';
	e.Civilite[2]='\0';
	if (Civilite==1)
		e.Civilite[0]='M';
	e.Civilite[1]='m';
	e.Civilite[2]='e';
	e.Civilite[3]='\0';
	*IdE=e.IdEtudiant;
	printf("Veuillez indiquer le Nom de l'étudiant :\n");
	fgets(e.Nom,22,stdin);
	e.Nom[strlen(e.Nom)-1]='\0';
	while(strlen(e.Nom)==0)
	{
		printf("Nom incorrect\n");
		printf("Veuillez indiquer le Nom de l'étudiant :\n");
		fgets(e.Nom,22,stdin);
		e.Nom[strlen(e.Nom)-1]='\0';
	}
	printf("Veuillez indiquer le Prenom de l'étudiant :\n");
	fgets(e.Prenom,22,stdin);
	e.Prenom[strlen(e.Prenom)-1]='\0';
	while(strlen(e.Prenom)==0)
	{
		printf("Nom incorrect\n");
		printf("Veuillez indiquer le Prenom de l'étudiant :\n");
		fgets(e.Prenom,22,stdin);
		e.Prenom[strlen(e.Prenom)-1]='\0';
	}
	printf("Veuillez indiquer si l'étudiant est boursier ou non (0 ou 1) puis son échelon de bourse :\n");
	i=scanf("%d%d",&e.Boursier,&e.Echelon);
	while((e.Echelon<=0 || e.Echelon>7)||(e.Boursier!=0 && e.Boursier!=1))
	{
		printf("Condition de bourse ou échelon incorrect.\n");
		printf("Veuillez indiquer si l'étudiant est boursier ou non (0 ou 1) puis son échelon de bourse :\n");
		scanf("%d%d",&e.Boursier,&e.Echelon);
	}
	*EchelonN=e.Echelon;
	printf("Veuillez indiquer si l'étudiant est handicapé ou non(0 ou 1) :\n");
	i=scanf("%d",&e.Handicap);
	while(e.Handicap!=0 && e.Handicap!=1)
	{
		printf("Condition d'handicap incorrect.\n");
		printf("Veuillez indiquer si l'étudiant est handicapé ou non(0 ou 1) :\n");
		scanf("%d",&e.Handicap);
	}
	tetud[*nbEtud]=(Etudiant*)malloc(sizeof(Etudiant));
	*tetud[*nbEtud]=e;
	*nbEtud=*nbEtud+1;
	if(*nbEtud==*maxEtud)
	{
		aux=(Etudiant**)realloc(tetud,(*maxEtud+5)*sizeof(Etudiant*));
		if(aux==NULL)
		{
			printf("Problème realloc Etudiant");
			exit(2);
		}
		tetud=aux;
		*maxEtud=*maxEtud+5;
	}
	afficherEtudiants(tetud,*nbEtud);
	return tetud;
}



void afficherEtudiants(Etudiant **tetud,int nb)
/*-----------------------//
Fonctionnalité : Affiche tous les étudiants
Détails paramètres : tetud->le tableau d'étudiants, nb->le nombre d'étudiants
//-----------------------*/
{
	int i;
	for(i=0;i<nb;i++)
	{
		afficher1Etudiant(*tetud[i]);
	}
	return;
}


void afficher1Etudiant(Etudiant tetud)
/*-----------------------//
Fonctionnalité : Affiche un seul étudiant
Détails paramètres :tetud->le tableau d'étudiants
//-----------------------*/
{
	printf("-------------------------\n");
	printf("%d\n%s\n%s\n%s\n",tetud.IdEtudiant,tetud.Civilite,tetud.Nom,tetud.Prenom);

	if(tetud.Boursier==1)
		printf("Boursier : %d\n",tetud.Echelon);
	else
		printf("Non Boursier : %d\n",tetud.Echelon);
	if(tetud.Handicap==1)
		printf("Handicapé\n");
	else
		printf("Non Handicapé\n");
	printf("-------------------------\n");

}



int rechDico(Etudiant **tetud, int n,int val,int *trouve)
/*-----------------------//
Fonctionnalité : Recherche dichotomique. 
Détails paramètres : tetud => Tableau de pointeur sur structure étudiant. 
				 n 	   => Taille du tableau tetud.
				 val   => Valeur recherchée dans le tableau. 
				 trouve=> Retourne le résultat de la recherche.  
return : retourne le rang où est l'IdEtudiant recherché, ou -1 si pas trouvé. 
//-----------------------*/

{
	int deb=0, m, fin=n-1;
	while(deb<=fin)
	{
		m=(deb+fin)/2;
		if (tetud[m]->IdEtudiant==val)
		{
			*trouve=1;
			return m;
		}
		if (val<tetud[m]->IdEtudiant)
			fin=m-1;
		else
			deb=m+1;
	}
	*trouve=0;
	return deb;
}




void triEchangeEtu(Etudiant *tetud[], int nb)
/*-----------------------//
Fonctionnalité : Tri les étudiants par Idetudiant 
Détails paramètres : tetud->tableau d'étudiants, nb->le nombre d'étudiants
//-----------------------*/
{
	int pge;
	while (nb>1)
	{
		pge=plusGrand(tetud,nb);
		echanger(tetud,pge,nb-1);
		nb=nb-1;
	}
	if(nb==1)
		return;
	pge=plusGrand(tetud,nb);
	echanger(tetud,pge,nb-1);
	triEchangeEtu(tetud,nb-1);
}



int plusGrand(Etudiant *tetud[], int nb)
/*-----------------------//
Fonctionnalité : Retourne le plus grand 
Détails paramètres : tetud->tableau d'étudiants, nb->le nombre d'étudiants
return : Retourne l'emplacement de l'IdEtudiant le plus grand
//-----------------------*/
{
	int pge=0,i;
	for (int i = 0; i < nb; ++i)
	{	
		if(tetud[i]->IdEtudiant>tetud[pge]->IdEtudiant)
			pge=i;
	}
	return pge;
}



void echanger(Etudiant *tetud[],int i, int j)
/*-----------------------//
Fonctionnalité : Echange les contenus des pointeurs 
Détails paramètres : tetud->tableau d'étudiants, i->le premier pointeur, j->le deuxième pointeur 
return : void 
//-----------------------*/
{
	Etudiant *aux;
	aux=tetud[i];
	tetud[i]=tetud[j];
	tetud[j]=aux;
}



void sauveTabEtudiant(Etudiant *tetud[], int nb)
/*-----------------------//
Fonctionnalité : Sauvegarde du tableau d'étudiants
Détails paramètres : tetud->tableau d'étudiants, nb->le nombre d'etudiants
return :void 
//-----------------------*/
{

	FILE *flot;
	int i;
	flot=fopen("etudiants.txt","w");
	if(flot==NULL)
	{
		printf("Erreur d'ouverture de fichier !\n");
		return ;
	}

	for(i=0;i<nb;i++)
	{
		fprintf(flot,"%d %s\n%s\n%s\n%d %d %d\n",tetud[i]->IdEtudiant,tetud[i]->Civilite,tetud[i]->Nom,tetud[i]->Prenom,tetud[i]->Boursier,tetud[i]->Echelon,tetud[i]->Handicap);
	}


	fclose(flot);
	return ;
}

int chargerFlogement(Logement tlog[],int max)
/*-----------------------//
Fonctionnalité : Charger le fichier Logement en tant que tableau statique de structures.
Détails paramètres: tlog[] 	=> Le tableau à remplir. 
				max 	=> La taille prédéfinie du tableau. 
return : Retourne la taille du tableau statique, soit le nombre de structures dedans. 
//-----------------------*/
{
	FILE *flot;
	int nb,i;
	flot=fopen("logements.txt","r");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier : logements.txt.\n");
		return -1;
	}
	fscanf(flot,"%d",&nb);
	if(nb==max)
	{
		printf("Tableau logement plein.\n");
		return -2;
	}
	for (i=0;i<nb;i++)
	{
		tlog[i]=lireLog(flot);
	}
	fclose(flot);
	return nb;
}


Logement lireLog(FILE *flot)
/*-----------------------//
Fonctionnalité : Lis dans le fichier les informations concernant un etudiant 
			 et les mets dans la structure Logment l.
Détails paramètres: flot => Le fichier de logement à lire. 
				l.Idlogment => Identifiant du logement.
				l.Type => Type de logement. 
				l.Dispo => Le statut de disponibilté du logment.
				l.Adapte = si le logement est adapté aux handicapés.  
return : Retourne la structure l remplie. 
//-----------------------*/
{
	Logement l;
	fscanf(flot,"%d",&l.IdLogement);
	fscanf(flot,"%d%d%d%*c",&l.Type,&l.Dispo,&l.Adapte);
	if(l.Dispo==1)
		fscanf(flot,"%d%*c",&l.IdEtudiant);
	fscanf(flot,"%*c");
	fgets(l.Nom,22,flot);
	l.Nom[strlen(l.Nom)-1]='\0';

	return l;
}

void afficherLogement(Logement *tlog,int nb)
/*-----------------------//
Fonctionnalité : Affiche le tableau de logement. 
Détails paramètres :	tlog => Le tableau de structure fixe chargé. 
					nb 	 => La taille du tableau de structure tlog.  
//-----------------------*/
{
	int i;
	for(i=0;i<nb;i++)
	{
		afficher1Logement(tlog[i]);
	}
	return;
}


void afficher1Logement(Logement l)
/*-----------------------//
Fonctionnalité :Affiche unbe ligne du tableau de logement soit toutes 
			les informations concernant un logement. 
Détails paramètres : l => Structure logement. 
//-----------------------*/
{
	printf("%d\t",l.IdLogement);
	if (l.Type==0)
		printf("Chambre\t");
	if (l.Type==1)
		printf("Studio\t");
	if (l.Type==2)
		printf("T1\t");
	if (l.Type==3)
		printf("T2\t");
	if (l.Dispo==0)
		printf("Disponible\t\t\t");
	if (l.Dispo==1)
		printf("Indisponible\tOccupé par : %d\t",l.IdEtudiant);
	if (l.Adapte==0)
		printf("\tAdapté\t");
	if (l.Adapte==1)
		printf("\tNon Adapté");
	printf("\t%s", l.Nom);
	printf("\n");
	return;
}



void affichageLogementOccupe(Logement *tlog,Etudiant **tetud,int nbLog,int nbEtud)
/*-----------------------//
Fonctionnalité : Affiche un tableau des logements occupés avec pour chaque logement l'étudiant 
			 qui l'occupe. 
Détails paramètres : Id 	=> Stock le numéro Id de l'étudiant qui occupe le logement appelé. 
				 trouve => Stock le résultat de la recherche dichotomique.
				 tetud[]=> Tableau dynamque de pointeur sur les structures etudiant.  
//-----------------------*/

{
	int i,Id,rech,trouve;
	for (i=0;i<nbLog;i++)
	{
		if (tlog[i].Dispo==1)
		{
			Id=tlog[i].IdEtudiant;
			rech=rechDico(tetud,nbEtud,Id,&trouve);
			afficher1Logement(tlog[i]);
			afficher1Etudiant(*tetud[rech]);
			printf("\n");
		}
	}
	return;
}

void affichageLogementTrie(Logement tlog[],int nbLog,int maxLog)
/*-----------------------//
Fonctionnalité : Affiche un tableau de logement trié par citées. 
Détails paramètres : tlog[] => Tableau statique de structure l. 
				 nbLog  => Nombre de structures logements. 
				 maxLog => Taille max du tableau Tlog.  
//-----------------------*/

{
	int i;
	Logement ttri[maxLog];
	for(i=0;i<nbLog;i++)
		ttri[i]=tlog[i];
	trifusion (ttri,nbLog);
	afficherLogement(ttri,nbLog);
}

int rechercherLogement(Logement tlog[],int nb, int val,int *trouve)
/*-----------------------//
Fonctionnalité : Recherche un logment dans le tableau fixe de logement en fonction d'une
			 demande de l'utilisateur. 
Détails paramètres : tlog[] => Tableau fixe de structure logement. 
				 nb 	=> Taille du tableau logement. 
				 val    => Valeur renseignée par l'utilisateur via une autre fonction. 
				 trouve => Stock le resultat de la recherche (1 si trouvée sion 0).
return : Retourne la valeur de trouve par pointeur et le rang i. Sinon retourne -1 et 
	 la valeur de trouve par pointeur.  
//-----------------------*/

{
	int i;
	for (i=0; i < nb; i++ )
	{
		if(tlog[i].IdLogement==val)
		{
			*trouve=1;
			return i;
		}
	}
	*trouve=0;
	return -1;
}

Logement *liberationlogement(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int *nbLog, int *nbDem)
/*-----------------------//
Fonctionnalité : Libère le logement choisi par l'utilisateur.
Détails paramètres : tetud => Tableau dynamique de pointeurs sur structure etudiant. 
				 tlog  => Tableau fixe de structure logement. 
				 l 	   => Liste chaînée linéaire de demande. 
				 nbEtud=> Taille logique du tableau d'etudiant. 
				 nbLog => Taille du tableau de logment. 
				 nbDemande => Taille de la liste de structure demande. 
return : Retourne le tableau tlog avec la modification apportée. 
//-----------------------*/
{
	int Id,rech,trouve;
	afficherLogement(tlog,*nbLog);
	printf("Quel logement est desormais libre ?(tappez IdLogement)\n");
	scanf("%d",&Id);
	rech=rechercherLogement(tlog,*nbLog,Id,&trouve);
	if (tlog[rech].Dispo==0)
	{
		printf("Logement déjà disponible.\n");
		return tlog;
	}
	else
	{
		tlog[rech].Dispo=0;
		tlog[rech].IdEtudiant=0;
	}
	afficherLogement(tlog,*nbLog);
	printf("Logement %d maintenant disponible.\n",Id);
	printf("\n");
	return tlog;
}
void trifusion (Logement tlog[],int n)
/*-----------------------//
Fonctionnalité : Tri par fusion le tableau statique de logement tlog, libère les tableaux
			 auxiliaires r et s à la fin. 
Détails paramètres : tlog[] => Tableau statique de structure l.
				 n => Taille du tableau statique. 
				 r => Tableau dont la taille est alloué par malloc 
				 	  en fonction de la taille de Logement.
				 s => Tableau dont la taille est alloué par malloc 
				 	  en fonction de la taille de Logement.
//-----------------------*/
{

	Logement *r,*s;
	if(n==1)
		return;

	r=(Logement*)malloc((n/2)*sizeof(Logement));
	s=(Logement*)malloc((n-n/2)*sizeof(Logement));
	if(r==NULL || s==NULL)
	{
		printf("Problème malloc dans trifusion\n");
		return;
	}
	copie(tlog,0,n/2,r);
	copie(tlog,n/2,n,s);
	trifusion(r,n/2);
	trifusion(s,(n-n/2));
	fusion(r,n/2,s,n-n/2,tlog);
	free(r);
	free(s);
}


void copie(Logement tlog[], int i,int j, Logement r[])
/*-----------------------//
Fonctionnalité : Copie les élément du tableau tlog dans un tableau statique r. 
Détails paramètres : tlog[] => Tableau statique de structure l. 
				 r[]    => Copie du tableau statique de structure l. 
//-----------------------*/
{
	int k=0;
	while(i<j)
	{
		r[k]=tlog[i];
		i=i+1;
		k=k+1;
	}
}

void fusion (Logement r[],int n, Logement s[], int m, Logement tlog[])
{
	int i,j,k;
	i=0;
	j=0;
	k=0;
	while(i<n && j<m)
	{
		if (strcmp(r[i].Nom,s[j].Nom)<0)
		{
			tlog[k]=r[i];
			i=i+1;
			k=k+1;
		}
		else
		{
			tlog[k]=s[j];
			k=k+1;
			j=j+1;
		}
	}
	while(i<n)
	{
		tlog[k]=r[i];
		i=i+1;
		k=k+1;
	}
	while(j<m)
	{
		tlog[k]=s[j];
		j=j+1;
		k=k+1;
	}
}


//Sauvegarde logement//

void sauveTablogement(Logement tlog[], int nb)
/*-----------------------//
Fonctionnalité : Sauvegarde le tableau fixe de structure logement dans un fichier texte. 
Détails paramètres : tlog => Tableau fixe de structure logement.
				 nb => Nombre de structures contenues par le tableau tlog. 
//-----------------------*/
{

	FILE *flot;
	int i;
	flot=fopen("logements.txt","w");
	if(flot==NULL)
	{
		printf("Erreur d'ouverture de fichier !\n");
		return ;
	}
	fprintf(flot,"%d\n",nb);
	for(i=0;i<nb;i++)
	{
		fprintf(flot,"%d\t%d\t%d\t%d",tlog[i].IdLogement,tlog[i].Type,tlog[i].Dispo,tlog[i].Adapte);
		if(tlog[i].Dispo==1)
			fprintf(flot,"\t%d",tlog[i].IdEtudiant);
		fprintf(flot,"\n");
		fprintf(flot," %s\n",tlog[i].Nom);

	}


	fclose(flot);
	return ;
}

ListeDemande chargerFdemande(int *nb)
/*-----------------------//
Fonctionnalité : Charge le fichier texte demande dans une liste chainée linéaire de structure demande.  
Détails paramètres :  nb => Nombre de demande dans la liste. 
return : Retourne la liste remplie. 
//-----------------------*/
{
	ListeDemande l;
	Demande d;
	FILE *flot;
	flot=fopen("demandesEnAttente.txt","r");
	*nb=0;
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier : demandesEnAttente.txt.\n");
		exit(1);
	}
	l=listeNouv();
	d=lireDem(flot);
	while(!feof(flot))
	{

		l=insertion(l,d);
		*nb=*nb+1;
		d=lireDem(flot);
	}
	fclose(flot);
	return l;
}

ListeDemande listeNouv(void)
/*-----------------------//
Fonctionnalité : Créer une nouvelle liste vide. 
return : Retourne la liste vide. 
//-----------------------*/
{
	ListeDemande l;
	l=NULL;
	return l;
}

Demande lireDem(FILE *flot)
/*-----------------------//
Fonctionnalité : Lis une demande. 
Détails paramètres : flot=> Fichier texte demande. 
return : Retourne la structure demande d lu. 
//-----------------------*/
{
	Demande d;
	fscanf(flot,"%d%d%d%d\n",&d.IdDemande,&d.IdEtudiant,&d.Echelon,&d.Type);
	fgets(d.Nom,22,flot);
	d.Nom[strlen(d.Nom)-1]='\0';
	return d;
}

ListeDemande insertion(ListeDemande l,Demande d)
/*-----------------------//
Fonctionnalité : Tri par echelon les demandes et appel la fonction InsertionEnTete. 
Détails paramètres : l => Liste chainée linéaire des demandes. 
				 d => Structure demande.
return : Retourne la liste l avec a nouvelle demande. 
//-----------------------*/
{
	if(vide(l))
		return insertionEnTete(l,d);
	if(d.Echelon<l->demande.Echelon)
		return insertionEnTete(l,d);
	l->suiv=insertion(l->suiv,d);
	return l;
}

ListeDemande insertionEnTete(ListeDemande l, Demande d)
/*-----------------------//
Fonctionnalité : Insert en tête de liste la nouvelle demande. 
Détails paramètres : l => Liste chainée linéaire.
				 d => Structure demande.  
return : Retourne la position d'insertion de la nouvelle demande. 
//-----------------------*/
{
	MaillonDemande *m;
	m=(MaillonDemande*)malloc(sizeof(MaillonDemande));
	if(m==NULL)
	{
		printf("Problème malloc étudiant.\n");
		exit(1);
	}
	m->demande=d;
	m->suiv=l;
	return m;
}

Booleen vide (ListeDemande l)
{
	if(l==NULL)
		return vrai;
	return faux;
}

ListeDemande chargerFdemandeBin(int *nb)
/*-----------------------//
Fonctionnalité : Charger le fichier binaire demande dans une liste chainée linéaire. 
Détails paramètres : nb => Le nombre de demande.  
return : Retourne la liste chargée des demandes.
//-----------------------*/
{
	ListeDemande l;
	l=listeNouv();
	Demande d;
	int i;
	FILE *flot;
	flot=fopen("demande.bin","rb");
	*nb=0;
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier : demandesEnAttente.txt.\n");
		exit(1);
	}
	fread(nb,sizeof(int),1,flot);
	for(i=0;i<*nb;i++)
	{
		fread(&d,sizeof(Demande),1,flot);
		l=insertionEnTete(l,d);
	}
	fclose(flot);
	return l;
}

void creationDemande(Logement tlog[],Etudiant **tetud,ListeDemande l, int *nbDem,int *nbEtud, int *nbLog,int *maxEtud)
/*-----------------------//
Fonctionnalité : Créer une nouvelle demande avec les informations passées en paramètre. 
Détails paramètres : tlog => Tableau de logement. 
				 tetud => Tableau d'étudiant. 
				 l => Liste de demande. 
				 nbDem => Nombre de demande. 
				 nbEtud => Nombre d'étudiant. 
				 nbLog => Nombre de logement.
				 maxEtud => Nombre max d'étudiant. 
//-----------------------*/
{
	Demande d;
	int i,j,IdE,IdD,TypeS,EchelonN,rech,c,trouve,trouveD;
	char Nom[20];
	afficherDemandes(l);
	printf("Information à renseigner sur la nouvelle demande.\n");
	printf("Veuillez indiquez l'Id de l'étudiant (0 si nouveau).\n");
	scanf("%d%*c",&IdE);
	rech=rechDico(tetud,*nbEtud,IdE,&trouve);
	if (IdE==0 || rech==*nbEtud)
	{
		printf("Etudiant inexistant création d'un Etudiant :\n");
		tetud=creationEtudiant(tetud,nbEtud,maxEtud,&IdE,&EchelonN);
	}
	printf("Veuillez indiquer l'Id de la demande\n");
	scanf("%d%*c",&d.IdDemande);
	trouveD=rechercherDemande(l,d.IdDemande);
	while(trouveD==1)
	{
		printf("IdDemande déjà existant veuillez saisir autre Id\n");
		scanf("%d%*c",&d.IdDemande);
		trouveD=rechercherDemande(l,d.IdDemande);
	}
	d.IdEtudiant=IdE;
	d.Echelon=EchelonN;
	if (!(d.Echelon>=0 && d.Echelon<=7))
	{
		printf("Veuillez indiquer l'échelon de l'étudiant :\n");
		scanf("%d%*c",&d.Echelon);
	}
	while(d.Echelon<=0 && d.Echelon>=7)
	{
		printf("Veuillez saisir un échelon valide (entre 0 et 7 ) :\n");
		printf("Veuillez indiquer l'échelon de l'étudiant :\n");
		scanf("%d%*c",&d.Echelon);
	}
	printf("Veuillez indiquer le nom de cité voulu :\n");
	fgets(d.Nom,22,stdin);
	d.Nom[strlen(d.Nom)-1]='\0';
	while(strlen(d.Nom)==0)
	{
		printf("Veuillez renseigner un nom\n");
		fgets(d.Nom,22,stdin);
		d.Nom[strlen(d.Nom)-1]='\0';
	}
	printf("Veuillez indiquer le type de logement voulu (0 pour chambre,1 pour studio,2 pour T1,3 pour T2) : \n");
	scanf("%d",&d.Type);
	while(d.Type!=0 && d.Type!=1 && d.Type!=2 && d.Type!=3)
	{
		printf("Veuillez indiquer un type de logement correct (0 pour chambre,1 pour studio,2 pour T1,3 pour T2) : \n");
		scanf("%d",&d.Type);
	}
	insertion(l,d);
	*nbDem=*nbDem+1;
	afficherDemandes(l);
	return;
}

void afficherDemandes(ListeDemande l)
/*-----------------------//
Fonctionnalité : Afficher un tableau des demandes. 
Détails paramètres : l => Liste de demandes. 
//-----------------------*/
{
	if(l==NULL)
	{
		printf("\n");
		return;
	}
	while(l!=NULL)
	{
		afficher1Demande(l->demande);
		l=l->suiv;
	}

}

void afficher1Demande(Demande d)
/*-----------------------//
Fonctionnalité : Affiche une demande. 
Détails paramètres : d => Structure demande. 
//-----------------------*/
{
	printf("%d\t%d\t%d\t",d.IdDemande,d.IdEtudiant,d.Echelon);
	if (d.Type==0)
		printf("Chambre\t");
	if (d.Type==1)
		printf("Studio\t");
	if (d.Type==2)
		printf("T1\t");
	if (d.Type==3)
		printf("T2\t");
	printf("%s\n",d.Nom);
	return;
}

int rechercherDemande(ListeDemande l,int val)
/*-----------------------//
Fonctionnalité : Rechercher une demande. 
Détails paramètres : l => Liste de demande. 
				 val => Valeur cherchée entrée en paramètre. 
return : Retourne 0 si pas trouvée sinon 1. 
//-----------------------*/
{
	if(l==NULL)
		return 0;
	if(l->demande.IdDemande==val)
		return 1;
	return rechercherDemande(l->suiv,val);
}

ListeDemande suppression(ListeDemande l,int val,int *nb)
/*-----------------------//
Fonctionnalité : Supprime une demande. 
Détails paramètres : l => Liste demande. 
				 val => L'id de demande à supprimer. 
				 nb => Nombre de demandes. 
return : Retourne la liste l actualisée. 
//-----------------------*/
{
	Demande d;
	d=l->demande;
	if(vide(l))
		return l;
	if(val==d.IdDemande)
	{
		*nb=*nb-1;
		return suppressionEnTete(l);
	}
	l->suiv=suppression(l->suiv,val,nb);
	return l;
}


ListeDemande suppressionEnTete(ListeDemande l)
/*-----------------------//
Fonctionnalité : Libère un maillon, et fais pointer le précédent sur le suivant.  
Détails paramètres : l => Liste des demande. 
return : Retourne la liste l. 
//-----------------------*/
{
	ListeDemande d;
	if(vide(l))
	{
		printf("opération interdite\n");
		exit (1);
	}
	d=l;
	l=l->suiv;
	free(d);
	return l;
}

ListeDemande annulationDemande(int *nb,ListeDemande l)
/*-----------------------//
Fonctionnalité : Annule une demande. 
Détails paramètres : nb => Nombre de demandes.
				 l => Liste de demande. 
//-----------------------*/
{
	int IdDemande;
	afficherDemandes(l);
	printf("Quel demande en attente voulez-vous supprimer? (Tappez l'Id de la demande) \n");
	scanf("%d%*c",&IdDemande);
	l=suppression(l,IdDemande,nb);
	afficherDemandes(l);
	printf("Demande %d annulé.\n",IdDemande);
}

ListeDemande traitementDemandes(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int nbLog, int *nbDem)
/*-----------------------//
Fonctionnalité : Affiche les logement qui ont été attribué à un étudiant. 
Détails paramètres : tetud => Tableau d'étudiant. 
				 tlog => Tableau de logement. 
				 l => Liste de demande. 
				 nbEtud => Nombre d'étudiant. 
				 nbLog => Nombre de logement.
				 nbDem => Nombre de demande. 
				
return : Retourne la liste actualisée. 
//-----------------------*/
{

	afficherLogement(tlog,nbLog);
	printf("-----------------------------------------------------------------------------\n\n");
	afficherDemandes(l);
	printf("\n\n-----------------------------------------------------------------------------\n\n");
	l=traitementDem(tetud,tlog,l,nbEtud,nbLog,nbDem);
	printf("\n\n-----------------------------------------------------------------------------\n\n");
	afficherLogement(tlog,nbLog);
	printf("\n\n-----------------------------------------------------------------------------\n\n");
	afficherDemandes(l);
	printf("\n");
	return l;
}

ListeDemande traitementDem(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int nbLog, int *nbDem)
/*-----------------------//
Fonctionnalité : Attribue les logements en fonction des priorités des demandes. 
Détails paramètres : tetud => Tableau d'étudiant. 
				 tlog => Tableau de logement. 
				 l => Liste de demande. 
				 nbEtud => Nombre d'étudiant. 
				 nbLog => Nombre de logement.
				 nbDem => Nombre de demande. 
return : Retourne la liste actualisée. 
//-----------------------*/
{
	Demande d;
	int j,IdE,IdD,TypeS,handi,rech,trouve;
	char Nom[20];
	if(l==NULL)
	{
		return l;
	}
	d=l->demande;
	IdD=d.IdDemande;
	IdE=d.IdEtudiant;
	TypeS=d.Type;
	strcpy(Nom,d.Nom);
	rech=rechDico(tetud,nbEtud,IdE,&trouve);
	handi=tetud[rech]->Handicap;
	if(handi==0)
	{
		for (j=0;j<nbLog;j++)
		{
			if (tlog[j].Dispo==0 && strcmp(Nom,d.Nom)==0 && tlog[j].Adapte==1 && tlog[j].Type==TypeS)
			{
				tlog[j].Dispo=1;
				tlog[j].IdEtudiant=IdE;
				l=suppression(l,IdD,nbDem);
				break;
			}
		}
	}
	if(handi==1)
	{
		for (j=0;j<nbLog;j++)
		{
			if (tlog[j].Dispo==0 && strcmp(Nom,d.Nom)==0 && tlog[j].Adapte==0     && tlog[j].Type==TypeS)
			{
				tlog[j].Dispo=1;
				tlog[j].IdEtudiant=IdE;
				l=suppression(l,IdD,nbDem);
				break;
			}
		}
	}
	l->suiv=traitementDem(tetud,tlog,l->suiv,nbEtud,nbLog,nbDem);
	return l;
}

void sauveDem(ListeDemande l,int nb)
/*-----------------------//
Fonctionnalité : Sauvegarde la liste demande dans un fichier texte. 
Détails paramètres : l => Liste de demande.
				 nb => Nombre de demande. 
//-----------------------*/
{

	FILE *flot;
	int i;
	Demande d;
	flot=fopen("demandesEnAttente.txt","w");
	if(flot==NULL)
	{
		printf("Erreur d'ouverture de fichier !\n");
		return ;
	}

	for(i=0;i<nb;i++)
	{
		d=l->demande;
		fprintf(flot,"%d\t%d\t%d\t%d\n%s\n",d.IdDemande,d.IdEtudiant,d.Echelon,d.Type,d.Nom);
		l=l->suiv;
	}


	fclose(flot);
	return ;
}

void sauveDemBin(ListeDemande l,int nb)
/*-----------------------//
Fonctionnalité : Sauvegarde en binaire dans un fichier. 
Détails paramètres : l => Liste de demande.
				 nb => Nombre de demande.  
//-----------------------*/
{
	FILE *flot;
	Demande d;
	int i;
	flot=fopen("demande.bin","wb");
	if (flot==NULL)
	{
		printf("Erreur ouverture du fichier\n");
		return; 
	}
	fwrite(&nb,sizeof(int),1,flot);
	for(i=0;i<nb;i++)
	{
		d=l->demande;
		fwrite(&d,sizeof(Demande),1,flot);
		l=l->suiv;
	}
	fclose(flot);
}

//---------MENU----------//

void initialisationMenu(void)
{	
	int nbEtud,nbLog,nbDem,maxLog=50,maxEtud;
	Etudiant **tetud;
	Logement tlog[50];
	ListeDemande l;
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	l=chargerFdemandeBin(&nbDem);
	ExecGestionCrous(tetud,tlog,l,&nbLog,&nbDem,&nbEtud,&maxLog,&maxEtud);
}

void sauvegardeAuto(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud)
{
	sauveTabEtudiant(tetud,*nbEtud);
	sauveTablogement(tlog,*nbLog);
	sauveDem(l,*nbDem);
	sauveDemBin(l,*nbDem);
	printf("Sauvegarde automatique effectué.\n");
	return;
}
void AffichageMenu(void)
// Affiche le menu principal 
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃               MENU PRINCIPAL                  ┃\n");
	printf("┃                                               ┃\n");
	printf("┃       Gestion des logements du Crous          ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   1   Charger les Fichiers                    ┃\n");
	printf("┃   2   Afficher les différents fichiers        ┃\n");
	printf("┃   3   Fonctions de traitement                 ┃\n");
	printf("┃   4.  Sauvegardes dans fichier                ┃\n");
	printf("┃                                               ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   9   Quitter                                 ┃\n");
	printf("┃                                               ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\n");
}

int choixMenu(void)
// Permet d'effectuer un chois dans le menu principal
// Retrourne le choix fait par l'uttilisateur
{
	int choixMenu,i; 
	printf("Votre Choix?\n");
	i=scanf("%d",&choixMenu); 

	while(choixMenu<1 || choixMenu>4&&choixMenu!=9 || i != 1)
	{
		printf("ERREUR SAISIE, veuillez réessayer.\n");

		AffichageMenu();
		printf("Choix : ");
		i=scanf("%*c%d",&choixMenu);
	}
	return choixMenu;
}

void ExecGestionCrous(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxLog)
// Execute le Menu principal qui en fonction de la valeur de choixM va executer différentes fonctions.
{
	int choixM;
	AffichageMenu();
	choixM=choixMenu();
	if (choixM==1)
		ExecMenuChar(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	if (choixM==2)
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	if (choixM==3)
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	if (choixM==4)
		ExecMenuSauv(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	if (choixM==9)
		sauvegardeAuto(tetud,tlog,l,nbLog,nbDem,nbEtud);
	exit(1);
	choixM=0;
}

void AffichageMenuChargment(void)
// Affiche le menu de chargement
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                               ┃\n");
	printf("┃                 MENU CHARGEMENT               ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   1   Etudiants                               ┃\n");
	printf("┃   2   Logements                               ┃\n");
	printf("┃   3   Demandes                                ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   9   Retour                                  ┃\n");
	printf("┃                                               ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\n");
}

int choixMenuChargement(void)
// Permet à l'uttilisateur de choisir dans le menu de chargement et retourne le choix.
// Si le choix n'est pas compris entre 1 et 3 ou n'est pas 9, relance la fonction.  
{
	int choixChar, i; 
	printf("Votre Choix?\n");
	i=scanf("%d",&choixChar); 

	while((choixChar<1 || choixChar>3)&&choixChar!=9 | i != 1)
	{
		printf("ERREUR SAISIE, veuillez réessayer.\n");

		AffichageMenuChargment();
		printf("Choix : ");
		i=scanf("%*c%d",&choixChar);
	}
	return choixChar;
}

void ExecMenuChar(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxLog)
//Execute les fonctions de chargements choisies par l'utilisateur.
// Si le choix de l'utilisateur est 9, relance l'execution du menu principal.  
{
	int choixChar;
	AffichageMenuChargment();
	choixChar=choixMenuChargement();

	if (choixChar==1)
	{
		tetud=chargerFetudiant(nbEtud,maxEtud);
		printf("CHARGEMENT REUSSI\n");
		afficherEtudiants(tetud,*nbEtud);
		ExecMenuChar(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixChar==2)
	{
		*nbLog=chargerFlogement(tlog,*maxLog);
		printf("CHARGEMENT REUSSI\n");
		afficherLogement(tlog,*nbLog);
		ExecMenuChar(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixChar==3)
	{
		l=chargerFdemande(nbDem);
		printf("CHARGEMENT REUSSI\n");
		afficherDemandes(l);
		ExecMenuChar(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixChar==9)
		ExecGestionCrous(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
}

void AffichageMenuAffichage(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                               ┃\n");
	printf("┃            MENU DES AFFICHAGES                ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   1   Etudiants                               ┃\n");
	printf("┃   2   Logements                               ┃\n");
	printf("┃   3   Logements Occupés                       ┃\n");
	printf("┃   4   Logements triés par citées              ┃\n");
	printf("┃   5   Demandes                                ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   9   Retour                                  ┃\n");
	printf("┃                                               ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\n");
}

int choixMenuAffichage(void)
// Permet à l'uttilisateur de choisir dans le menu s'affichage et retourne le choix.
// Si le choix n'est pas compris entre 1 et 5 ou n'est pas 9, relance la fonction. 
{
	int choixAff, i; 
	printf("Votre Choix?\n");
	i=scanf("%d",&choixAff); 

	while((choixAff<1 || choixAff>5)&&choixAff!=9 || i != 1)
	{
		printf("ERREUR SAISIE, veuillez réessayer.\n");

		AffichageMenuAffichage();
		printf("Choix : ");
		i=scanf("%*c%d",&choixAff);
	}
	return choixAff;
}

void ExecMenuAff(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxLog)
//Execute différentes fonctions de chargement et d'affichage selon le choix de l'utilisateur.
// Si le choix de l'utilisateur est 9, relance l'execution du menu principal.
{
	int choixAff;
	AffichageMenuAffichage();
	choixAff=choixMenuAffichage();

	if (choixAff==1)
	{
		afficherEtudiants(tetud,*nbEtud);
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixAff==2)
	{
		afficherLogement(tlog,*nbLog);
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixAff==3)
	{
		affichageLogementOccupe(tlog,tetud,*nbLog,*nbEtud);
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixAff==4)
	{
		affichageLogementTrie(tlog,*nbLog,*maxLog);
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixAff==5)
	{
		afficherDemandes(l);
		ExecMenuAff(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixAff==9)
	{
		ExecGestionCrous(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}

}

void AffichageMenuFonction(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                               ┃\n");
	printf("┃            MENU DES FONCTIONS                 ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   1   Traitement des demandes                 ┃\n");
	printf("┃   2   Créer une demande de logement           ┃\n");
	printf("┃   3   Création d'un étudiant                  ┃\n");
	printf("┃   4   Annulation d'une demande                ┃\n");
	printf("┃   5	Libération d'un logement                ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   9   Retour                                  ┃\n");
	printf("┃                                               ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\n");
}

int choixMenuFonction(void)
// Permet à l'uttilisateur de choisir dans le menu d'affichage et retourne le choix.
// Si le choix n'est pas compris entre 1 et 4 ou n'est pas 9, relance la fonction. 

{
	int choixFonc, i; 
	printf("Votre Choix?\n");
	i=scanf("%d",&choixFonc); 

	while((choixFonc<1 || choixFonc>5)&&choixFonc!=9 || i != 1)
	{
		printf("ERREUR SAISIE, veuillez réessayer.\n");

		AffichageMenuFonction();
		printf("Choix : ");
		i=scanf("%*c%d",&choixFonc);
	}
	return choixFonc;
}

void ExecMenuFonc(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxLog)
//Execute différentes fonctions selon le choix de l'utilisateur.
// Pour chaque fonction appelé, le fichier ect chargé avant.
// Si le choix de l'utilisateur est 9, relance l'execution du menu principal.
{
	int IdE,EchelonN, choixFonc, max;
	AffichageMenuFonction();
	choixFonc=choixMenuFonction();

	if (choixFonc==1)
	{
		l=traitementDemandes(tetud,tlog,l,*nbEtud,*nbLog,nbDem);
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxEtud,maxLog);
	}
	if (choixFonc==2)
	{
		creationDemande(tlog,tetud,l,nbDem,nbEtud,nbLog,maxEtud);
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxEtud,maxLog);
	}
	if (choixFonc==3)
	{
		tetud=creationEtudiant(tetud,nbEtud,maxEtud,&IdE,&EchelonN);
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxEtud,maxLog);
	}
	if (choixFonc==4)
	{
		annulationDemande(nbDem,l);
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxEtud,maxLog);
	}
	if (choixFonc==5)
	{
		tlog=liberationlogement(tetud,tlog,l,*nbEtud,nbLog,nbDem);
		l=traitementDemandes(tetud,tlog,l,*nbEtud,*nbLog,nbDem);
		ExecMenuFonc(tetud,tlog,l,nbLog,nbDem,nbEtud,maxEtud,maxLog);
	}
	if (choixFonc==9)
	{
		ExecGestionCrous(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
}

void AffichageMenuSauvegarde(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                               ┃\n");
	printf("┃            MENU DE SAUVEGARDE                 ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   1   Etudiants                               ┃\n");
	printf("┃   2   Logements                               ┃\n");
	printf("┃   3   Demandes                                ┃\n");
	printf("┃   4   Demandes en binaire                     ┃\n");
	printf("┃                                               ┃\n");
	printf("┃   9   Retour                                  ┃\n");
	printf("┃                                               ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("\n");
}

int choixMenuSauv(void)
// Permet à l'utilisateur de choisir dans le menu de sauvegarde et retourne le choix.
// Si le choix n'est pas compris entre 1 et 3 ou n'est pas 9, relance la fonction. 

{
	int choixSauv, i; 
	printf("Votre Choix?\n");
	i=scanf("%d",&choixSauv); 

	while((choixSauv<1 || choixSauv>4)&&choixSauv!=9 || i != 1)
	{
		printf("ERREUR SAISIE, veuillez réessayer.\n");

		AffichageMenuSauvegarde();
		printf("Choix : ");
		i=scanf("%*c%d",&choixSauv);
	}
	return choixSauv;
}
void ExecMenuSauv(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxLog)
// Execute différentes sauvegarde selon le choix de l'utilisateur. 
// Si le choix de l'utilisateur est 9, relance l'execution du menu principal.
{
	int choixSauv;
	AffichageMenuSauvegarde();
	choixSauv=choixMenuSauv();
	if (choixSauv==1)
	{
		printf("Vous allez sauvegarder ce fichier dans un fichier texte:\n");
		afficherEtudiants(tetud,*nbEtud);
		sauveTabEtudiant(tetud,*nbEtud);
		ExecMenuSauv(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixSauv==2)
	{
		printf("Vous allez sauvegarder ce fichier dans un fichier texte:\n");
		afficherLogement(tlog,*nbLog);
		sauveTablogement(tlog,*nbLog);
		ExecMenuSauv(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixSauv==3)
	{
		printf("Vous allez sauvegarder ce fichier dans un fichier texte:\n");
		afficherDemandes(l);
		sauveDem(l,*nbDem);
		ExecMenuSauv(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixSauv==4)
	{
		printf("Vous allez sauvegarder ce fichier dans un fichier binaire:\n");
		afficherDemandes(l);
		sauveDemBin(l,*nbDem);
		ExecMenuSauv(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
	if (choixSauv==9)
	{
		ExecGestionCrous(tetud,tlog,l,nbLog,nbDem,nbEtud,maxLog,maxEtud);
	}
}