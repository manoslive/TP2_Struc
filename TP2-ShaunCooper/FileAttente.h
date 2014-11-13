/*
	Shaun Cooper
	TP2 - File d'attente
	FileAttente.h
	Déclaration d'une file d'attente qui sert à gérer plusieur ClientEnAttente
*/

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
	int ObtenirNbGroupes();
	int ObtenirNbPersonnes();
	void SetNbGroupes(int nbGroupes);
	void SetNbPersonnes(int nbPersonnes);

	ClientEnAttente* GetPremier() const;
	ClientEnAttente* GetDernier() const;
	void SetPremier(ClientEnAttente *pPremier);
	void SetDernier(ClientEnAttente *pDernier);

	void Ajouter(ClientEnAttente clientAMettreEnFile);
	ClientEnAttente::Client Retirer(int nbPlacesDeLaTable, int sectionDeLaTable);
	bool Retirer(string nomClient, int nbPersonnes);
	void Afficher(ostream & out);
	string GetClient(int indice);
};