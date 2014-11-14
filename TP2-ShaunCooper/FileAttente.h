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
	ClientEnAttente *pPremierClient_;
	ClientEnAttente *pDernierClient_;

	int nbGroupes_;
	int nbPersonnes_;

public:
	FileAttente();

	bool EstVide();
	int  ObtenirNbGroupes();
	int  ObtenirNbPersonnes();
	void SetNbGroupes(int nbGroupes);
	void SetNbPersonnes(int nbPersonnes);
	int  GetNbGroupes() const { return nbGroupes_; };
	int  GetNbPersonnes() const { return nbPersonnes_; };

	ClientEnAttente* GetPremier() const;
	ClientEnAttente* GetDernier() const;
	void SetPremier(ClientEnAttente *pPremier);
	void SetDernier(ClientEnAttente *pDernier);

	void	Ajouter(ClientEnAttente clientAMettreEnFile);
	ClientEnAttente::Client Retirer(int nbPlacesDeLaTable, int sectionDeLaTable);
	bool	Retirer(string nomClient, int nbPersonnes);
	void	Afficher(ostream & out);
	void	AfficherClient(FileAttente& maFile) const;
	string	GetClient(int indice);
};