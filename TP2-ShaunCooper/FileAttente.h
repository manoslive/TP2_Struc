//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	FileAttente.h															//
//	Déclaration d'une file d'attente qui sert à gérer plusieurs 			//
//  ClientEnAttente															//
//----------------------------------------------------------------------------//
// À faire : - Mettre des commentaires détaillés

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
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	void	Ajouter(ClientEnAttente clientAMettreEnFile);
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	ClientEnAttente::Client Retirer(int nbPlacesDeLaTable, int sectionDeLaTable, FileAttente & maFile);
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
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
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	bool	EstVide();
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	int		ObtenirNbGroupes();
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	int		ObtenirNbPersonnes();
	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants:			
	//  Extrants:
	//	Description: 
	/////////////////////////////////////////////////////////////////
	bool    Quitter();
};