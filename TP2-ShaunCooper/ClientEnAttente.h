//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	ClientEnAttente.h														//
//	Declaration d'un ClientEnAttente.										//
//----------------------------------------------------------------------------//

#ifndef _CLIENTENATTENTE_H_
#define _CLIENTENATTENTE_H_
#include <iostream>
#include <string>
using namespace std;

class ClientEnAttente
{
	//--- Attributs privés
	ClientEnAttente * pPrecedent_;  // Chaque noeud retient l'adresse de celui qui le precède
	ClientEnAttente * pSuivant_;    // et de celui qui le suit

public:
	struct Client
	{
		string nom_;			// nom de la personne; c'est notre élément d'information
		int nombreDePersonnes;	// Nombre de personnes dans le groupe
		int section;			// Nombre représentant la/les section(s) choisie(s)
	};
	//--- 
	Client InfoClient;

   //--- Constructeurs
	ClientEnAttente();
	ClientEnAttente(string nom, int nbDePersonnes, int sectionChoisie);

	//--- Mutateurs de pointeurs
	void SetPrecedent(ClientEnAttente * p);
	void SetSuivant(ClientEnAttente *p);

	//--- Accesseurs de pointeurs
	ClientEnAttente * GetPrecedent() const;
	ClientEnAttente * GetSuivant()   const;

	//--- Mutateurs
    void SetNom(string nom);
	void SetNombreDePersonnes(int nbDePersonnes);
	void SetSection(int sectionsChoisi);

	//--- Accesseurs
    string GetNom() const;
	int    GetNombreDePersonnes() const;
	int    GetSection();

	//--- Méthodes
	void Afficher(ostream & out) const;
};
#endif
