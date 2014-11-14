//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Cr�� le : 10-11-14													    //
//	Derni�re modification : 13-11-14									        //
//	FileAttente.h															//
//	D�claration d'une file d'attente qui sert � g�rer plusieurs 			//
//  ClientEnAttente															//
//----------------------------------------------------------------------------//
// � faire : - Mettre des commentaires d�taill�s

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

public:
	//--- Constructeur
	FileAttente();

	//--- Accesseurs / mutateurs
	void SetNbGroupes(int nbGroupes);
	void SetNbPersonnes(int nbPersonnes);
	int  GetNbGroupes() const { return nbGroupes_; };
	int  GetNbPersonnes() const { return nbPersonnes_; };

	//--- Accesseurs / mutateurs de pointeurs
	ClientEnAttente* GetPremier() const;
	ClientEnAttente* GetDernier() const;
	void SetPremier(ClientEnAttente *pPremier);
	void SetDernier(ClientEnAttente *pDernier);

	//--- M�thodes
	void	Ajouter(ClientEnAttente clientAMettreEnFile);
	ClientEnAttente::Client Retirer(int nbPlacesDeLaTable, int sectionDeLaTable);
	bool	Retirer(string nomClient, int nbPersonnes);
	void	Afficher(ostream & out, FileAttente & maFile);
	void	AfficherClient(FileAttente& maFile) const;
	string	GetClient(int indice);
	string  SectionEnString(int section);
	bool	EstVide();
	int		ObtenirNbGroupes();
	int		ObtenirNbPersonnes();
	bool    Quitter();
};