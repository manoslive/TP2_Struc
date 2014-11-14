//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	ClientEnAttente.h														//
//	Declaration d'un ClientEnAttente.										//
//----------------------------------------------------------------------------//


// Declaration d'un noeud. En l'occurence, le
// noeud ne contient qu'une string comme element
// d'information
//
// Modifier Noeud à ClientEnAttenete
//
// par Pierre Prud'homme, octobre 2014
// Modifier par Shaun Cooper, novembre 2014
//-------------------------------------------------
#ifndef _CLIENTENATTENTE_H_
#define _CLIENTENATTENTE_H_
#include <iostream>
#include <string>
using namespace std;

class ClientEnAttente
{
	ClientEnAttente * pPrecedent_;  // Chaque noeud retient l'adresse de celui qui le precède
	ClientEnAttente * pSuivant_;    // et de celui qui le suit

public:
	struct Client
	{
		string nom_;          // nom de la personne; c'est notre element d'information
		int nombreDePersonnes;
		int section;
	};
	Client InfoClient;

   //--- Constructeurs
	ClientEnAttente();
	ClientEnAttente(string nom, int nbDePersonnes, int sectionChoisie);

	void SetPrecedent(ClientEnAttente * p);
	void SetSuivant(ClientEnAttente *p);

	ClientEnAttente * GetPrecedent() const;
	ClientEnAttente * GetSuivant() const;

    void SetNom(string nom);
	void SetNombreDePersonnes(int nbDePersonnes);
	void SetSection(int sectionsChoisi);

    string GetNom() const;
	int GetNombreDePersonnes() const;
	int GetSection();
};

#endif
