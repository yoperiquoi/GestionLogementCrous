#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Crous.h"


void testChargerEtudiant(void)
{
	int nb,max,i;
	Etudiant **tetud;
	tetud=chargerFetudiant(&nb,&max);
	afficherEtudiants(tetud,nb);
	return;
}

void testChargerLogement(void)
{
	Logement tlog[50];
	int max=50,nb,i;	
	nb=chargerFlogement(tlog,max);
	afficherLogement(tlog,nb);
	return;
}

void testChargerDemandes(void)
{
	ListeDemande l;
	int nb;
	l=chargerFdemande(&nb);
	afficherDemandes(l);
	return;
}


void testAffichageLogementTrie(void)
{
	Logement tlog[50];
	int max=50,nb;	
	nb=chargerFlogement(tlog,max);
	trifusion(tlog,nb);
	afficherLogement(tlog,nb);
	return;
}


void testAffichageLogementOccupe(void)
{
	Logement tlog[50];
	int nbEtud,maxEtud,maxLog=50,nbLog;
	Etudiant **tetud;
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	affichageLogementOccupe(tlog,tetud,nbLog,nbEtud);
	return;
}

void testAfficherDemandes(void)
{
	ListeDemande l;
	int nb;
	l=chargerFdemande(&nb);
	afficherDemandes(l);
	return;
}

void testTraitementDemande(void)
{
	Etudiant **tetud;
	ListeDemande l;
	Logement tlog[50];
	int nbEtud,maxEtud,maxLog=50,nbLog,nbDem;
	l=chargerFdemande(&nbDem);
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	traitementDemandes(tetud,tlog,l,nbEtud,nbLog,&nbDem);
}

void testAnnulationDemande(void)
{
    int nb;
    ListeDemande l;
    l=chargerFdemande(&nb);
    annulationDemande(&nb,l);
    printf("\n");
    return;
}

void testrecherchelogement(void)
{
    Logement tlog[50];
    int tmax=50,nb,trouve,val,rech;    
    nb=chargerFlogement(tlog,tmax);
    afficherLogement(tlog,nb);
    printf("Indiquez quel logement afficher\n");
    scanf("%d",&val);
    rech=rechercherLogement(tlog,nb,val,&trouve);
    if (trouve==0)
    {
        printf("Logement inexistant.\n");
        return;
    }
    else
    {
        afficher1Logement(tlog[rech]);
        return;
    }
}

void testCreationEtudiant(void)
{
	Etudiant **tetud;
	ListeDemande l;
	Logement tlog[50];
	int nbEtud,maxEtud,maxLog=50,nbLog,nbDem,IdE,EchelonN;
	l=chargerFdemande(&nbDem);
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	tetud=creationEtudiant(tetud,&nbEtud,&maxEtud,&IdE,&EchelonN);
}

void testCreationDemande(void)
{
	Etudiant **tetud;
	ListeDemande l;
	Logement tlog[50];
	int nbEtud,maxEtud,maxLog=50,nbLog,nbDem,IdE,EchelonN;
	l=chargerFdemande(&nbDem);
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	creationDemande(tlog,tetud,l,&nbDem,&nbEtud,&nbLog,&maxEtud);
}

void testliberationLogement(void)
{
	Etudiant **tetud;
	ListeDemande l;
	Logement tlog[50];
	int nbEtud,maxEtud,maxLog=50,nbLog,nbDem,IdE,EchelonN;
	l=chargerFdemande(&nbDem);
	tetud=chargerFetudiant(&nbEtud,&maxEtud);
	nbLog=chargerFlogement(tlog,maxLog);
	liberationlogement(tetud,tlog,l,nbEtud,&nbLog,&nbDem);
}
void testsauvtabLog(void)
{	
	int max=50,nb,i;
	Logement tlog[50];	
	nb=chargerFlogement(tlog,max);
	sauveTablogement(tlog,nb);
	return;

}

void testsauvtabEtu(void)
{	
	int nb,max,i;
	Etudiant **tetud;
	tetud=chargerFetudiant(&nb,&max);
	triEchangeEtu(tetud,nb);
	sauveTabEtudiant(tetud,nb);
	return;
}

void testsauvtabDem(void)
{	
	ListeDemande l;
	int nb;
	l=chargerFdemande(&nb);
	sauveDem(l,nb);
	return;
}

void testsauvtabDemBin(void)
{	
	ListeDemande l;
	int nb;
	l=chargerFdemande(&nb);
	afficherDemandes(l);
	sauveDemBin(l,nb);
	return;
}

void testtriechange(void)
{
    int nb,max,i;
    Etudiant **tetud;
    tetud=chargerFetudiant(&nb,&max);
    triEchangeEtu(tetud,nb);
    afficherEtudiants(tetud,nb);
}

void testChargerDemandesBin(void)
{
	ListeDemande l,b;
	int nb,nbBin;
	l=chargerFdemande(&nb);
	afficherDemandes(l);
	sauveDemBin(l,nb);
	b=chargerFdemandeBin(&nbBin);
	printf("\n");
	afficherDemandes(b);
	return;
}

void global(void)
{
	initialisationMenu();
}

int main(void)
{
	//testChargerEtudiant();
	//testChargerLogement(); 	
	//testChargerDemandes();
	//testAffichageLogementTrie();
	//testAffichageLogementOccupe();
	//testAfficherDemandes();
	//testTraitementDemande();
	//testAnnulationDemande();
	//testrecherchelogement();
	//testCreationEtudiant();
	//testCreationDemande();
	//testsauvtabEtu();
	//testsauvtabLog();
	//testsauvtabDem();
	//testsauvtabDemBin();
	testliberationLogement();
	//testquicksort();
	//testtriechange();
	//testChargerDemandesBin();
	//global();
	return 0;
}
 