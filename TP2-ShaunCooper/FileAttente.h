//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	FileAttente.h															//
//	Déclaration d'une file d'attente qui sert à gérer plusieurs 			//
//  ClientEnAttente															//
//----------------------------------------------------------------------------//

#pragma once
#include "ClientEnAttente.h"
#include <iostream>
using namespace std;

class FileAttente
{
	//--- Pointeurs
	ClientEnAttente *pPremierClient_;
	ClientEnAttente *pDernierClient_;

	//--- Attributs
	int nbGroupes_;
	int nbPersonnes_;
	int nbGroupesAssignes_;
	int nbPersonnesAssignes_;

public:
	//--- Constructeur
	FileAttente();

	//--- Accesseurs / mutateurs
	void SetNbGroupes(int nbGroupes);
	void SetNbPersonnes(int nbPersonnes);
	void SetNbGroupesAssignes(int nbGroupesAssignes);
	void SetNbPersonnesAssignes(int nbPersonnesAssignes);
	int  GetNbGroupes() const { return nbGroupes_; };
	int  GetNbPersonnes() const { return nbPersonnes_; };
	int  GetNbGroupesAssignes() const { return nbGroupesAssignes_; };
	int  GetNbPersonnesAssignes() const { return nbPersonnesAssignes_; };

	//--- Accesseurs / mutateurs de pointeurs
	ClientEnAttente* GetPremier() const;
	ClientEnAttente* GetDernier() const;
	void SetPremier(ClientEnAttente *pPremier);
	void SetDernier(ClientEnAttente *pDernier);

	//--- Méthodes

	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants: ClientEnAttente clientAMettreEnFile	
	//  Extrants: Aucun(void)
	//	Description: Permet d'ajouter un client reçu en paramètre à la file d'attente 
	/////////////////////////////////////////////////////////////////
	void	Ajouter(ClientEnAttente clientAMettreEnFile);
	/////////////////////////////////////////////////////////////////
	//	Retirer
	//	Intrants: nbPlacesDeLaTable(int), sectionDeLaTable(int), maFile(FileAttente &)		
	//  Extrants: Client(ClientEnAttente::Client)
	//	Description: Permet de retirer un client de la file qui est assigné à une table
	/////////////////////////////////////////////////////////////////
	ClientEnAttente::Client Retirer(int nbPlacesDeLaTable, int sectionDeLaTable, FileAttente & maFile);
	/////////////////////////////////////////////////////////////////
	//	Retirer
	//	Intrants: nomClient(string), nbPersonnes(int)		
	//  Extrants: bool
	//	Description: Permet de retirer un client qui sort de la file
	/////////////////////////////////////////////////////////////////
	bool	Retirer(string nomClient, int nbPersonnes);
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	void	Afficher(ostream & out, FileAttente & maFile);
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	void	AfficherClient(FileAttente& maFile) const;
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	string	GetClient(int indice);
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	string  SectionEnString(int section);
	/////////////////////////////////////////////////////////////////
	//	EstVide
	//	Intrants:	Aucun		
	//  Extrants:	Nous renvoie true s'il est bel et bien vide
	//	Description: Vérifie si la file d'attente est vide
	/////////////////////////////////////////////////////////////////
	bool	EstVide();
	/////////////////////////////////////////////////////////////////
	//	ObtenirNbGroupes
	//	Intrants:	Aucun		
	//  Extrants:   Le nombre de groupes(int)
	//	Description: Additionne les groupes et retourne ce nombre
	/////////////////////////////////////////////////////////////////
	int		ObtenirNbGroupes();
	/////////////////////////////////////////////////////////////////
	//	ObtenirNbPersonnes
	//	Intrants:	 Aucun		
	//  Extrants:	 le nombre de personnes(int)
	//	Description: Additionne les personnes de tous les groupes
	//				 et retourne ce nombre
	/////////////////////////////////////////////////////////////////
	int		ObtenirNbPersonnes();
	/////////////////////////////////////////////////////////////////
	//	Quitter
	//	Intrants:	 Aucun		
	//  Extrants:	 un bool qui nous dit si on veut quitter ou non
	//	Description: Si la file d'attente contient un groupe
	//				 nous demandons à l'usager s'il veut bel et bien
	//				 quitter
	/////////////////////////////////////////////////////////////////
	bool    Quitter();
};