/*
Crous.h
Oscar CHAUMUZEAU
Thomas BLANC
Yoann PERIQUOI

Projet de structure de données 
A1 2020

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//----Definitions des structures----// 

typedef enum{faux,vrai}Booleen;

typedef struct
{
	int IdLogement;
	char Nom[30];
	int Type;
	Booleen	Dispo;
	Booleen Adapte;
	int IdEtudiant;
}Logement;

typedef struct
{
	int IdEtudiant;
	char Civilite[4];
	char Nom[20];
	char Prenom[20];
	Booleen Boursier;
	int Echelon;
	Booleen Handicap;
}Etudiant;

typedef struct
{
	int IdDemande;
	int IdEtudiant;
	int Echelon;
	char Nom[20];
	int Type;
}Demande;


typedef struct maillonDemande
{
	Demande demande;
	struct maillonDemande *suiv;
}MaillonDemande,*ListeDemande;

//--------------------------------//


//---------------------------------------Fonction liés aux etudiants--------------------------------------------------//

//--Chargement--//
Etudiant **chargerFetudiant (int *nb,int *max);
Etudiant lireEtud(FILE *fe);
//--------------//

//--Création d'étudiant--//
Etudiant **creationEtudiant(Etudiant **tetud,int *nbEtud,int *maxEtud,int *IdE,int *EchelonN);
//-----------------------//

//--Fonction d'affichage--//
void afficherEtudiants(Etudiant **etud,int nb);
void afficher1Etudiant(Etudiant tetud);
//------------------------//

//--Recherche dichotomique en fonction de l'IdEtudiant--//
int rechDico(Etudiant **tetud, int nb,int val,int *trouve);
//--------------------------//

//--Fonction de tri par IdEtudiant--//
void triEchangeEtu(Etudiant *tetud[], int nb);
int plusGrand(Etudiant *tetud[], int nb);
void echanger(Etudiant *tetud[],int i, int j);
//----------------------------------//

//--Sauvegarde--//
void sauveTabEtudiant(Etudiant *tetud[], int nb);
//--------------//

//-------------------------------------------------------------------------------------------------------------------//






//-----------------------------------------Fonction liés aux logements------------------------------------------------// 

//--Chargement--//
int chargerFlogement(Logement tlog[],int max);
Logement lireLog(FILE *flot);
//--------------//

//--Fonction d'affichage--//
void afficherLogement(Logement *tlog,int nb);
void afficher1Logement(Logement l);
void affichageLogementOccupe(Logement *tlog,Etudiant **tetud,int nbLog,int nbEtud);
void affichageLogementTrie(Logement *tlog, int nb,int maxLog);
//------------------------//


//--Fonction de recherche--//
int rechercherLogement(Logement tlog[],int nb, int val,int *trouve);
//-------------------------//

//--Liberation d'un logement--//
Logement *liberationlogement(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int *nbLog, int *nbDem);
//----------------------------//

//--Le tri par fusion--//
void trifusion (Logement tlog[],int n);
void copie(Logement tlog[], int i,int j, Logement r[]);
void fusion (Logement r[],int n, Logement s[], int m, Logement tlog[]);
//---------------------//

//--Sauvegarde--//
void sauveTablogement(Logement tlog[], int nb);
//--------------//

//-------------------------------------------------------------------------------------------------------------------//



//---------------------------------------Fonction liés aux demandes--------------------------------------------------//

//--Chargement--//
ListeDemande chargerFdemande(int *nb);
ListeDemande listeNouv(void);
Demande lireDem(FILE *flot);
ListeDemande insertion(ListeDemande l,Demande d);
ListeDemande insertionEnTete(ListeDemande l, Demande d);
Booleen vide (ListeDemande l);
//--------------//

//--Chargement binaire--//
ListeDemande chargerFdemandeBin(int *nb);
//----------------------//

//--Création de demandes--//
void creationDemande(Logement tlog[],Etudiant **tetud,ListeDemande l, int *nbDem,int *nbEtud, int *nbLog,int *maxEtud);
//------------------------//

//--Fonction d'affichage--//
void afficherDemandes(ListeDemande l);
void afficher1Demande(Demande d);
//------------------------//

//--Recherche demande en fonction de l'IdDemande--//
int rechercherDemande(ListeDemande l,int val);
//------------------------------------------------//

//--Fonction de suppression--//
ListeDemande suppression(ListeDemande l,int x,int *nb);
ListeDemande suppressionEnTete(ListeDemande l);
//---------------------------//

//--Annulation de demande de logement--//
ListeDemande annulationDemande(int *nb,ListeDemande l);
//-------------------------------------//

//--Traitement des demandes--//
ListeDemande traitementDemandes(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int nbLog, int *nbDem);
ListeDemande traitementDem(Etudiant **tetud,Logement *tlog,ListeDemande l, int nbEtud, int nbLog, int *nbDem);
//---------------------------//

//--Sauvegarde--//
void sauveDem(ListeDemande l,int nb);
//--------------//

//--Sauvegarde Binaire--//
void sauveDemBin(ListeDemande l,int nb);
//----------------------//

//-------------------------------------------------------------------------------------------------------------------//




//-------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------MENU------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

//--Chargement des fichiers--//
void initialisationMenu(void);
//---------------------------//

//--Choix du menu--//
int choixMenu(void);
int choixMenuChargement(void);
int choixMenuFonction(void);
int choixMenuAffichage(void);
int choixMenuSauv(void);
//-----------------//

//--Différentes exécution--//
void ExecGestionCrous(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxDem);
void ExecMenuChar(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxDem);
void ExecMenuAff(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxDem);
void ExecMenuFonc(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxDem);
void ExecMenuSauv(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud,int *maxEtud,int *maxDem);
//-------------------------//

//--Fonction d'affichage--//
void AffichageMenuChargment(void);
void AffichageMenuAffichage(void);
void AffichageMenuFonction(void);
void AffichageMenuSauvegarde(void);
//------------------------//

//--Fonction de sauvegarde--//
void sauvegardeAuto(Etudiant **tetud,Logement tlog[],ListeDemande l,int *nbLog,int *nbDem,int *nbEtud);
//--------------------------//

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
