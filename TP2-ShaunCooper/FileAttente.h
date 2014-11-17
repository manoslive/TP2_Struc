//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Cr�� le : 10-11-14													    //
//	Derni�re modification : 13-11-14									        //
//	FileAttente.h															//
//	D�claration d'une file d'attente qui sert � g�rer plusieurs 			//
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

	//--- M�thodes

	/////////////////////////////////////////////////////////////////
	//	Ajouter
	//	Intrants: ClientEnAttente clientAMettreEnFile	
	//  Extrants: Aucun(void)
	//	Description: Permet d'ajouter un client re�u en param�tre � la file d'attente 
	/////////////////////////////////////////////////////////////////
	void	Ajouter(ClientEnAttente clientAMettreEnFile);
	/////////////////////////////////////////////////////////////////
	//	Retirer
	//	Intrants: nbPlacesDeLaTable(int), sectionDeLaTable(int), maFile(FileAttente &)		
	//  Extrants: Client(ClientEnAttente::Client)
	//	Description: Permet de retirer un client de la file qui est assign� � une table
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
	//	Afficher
	//	Intrants: out(ostream &), maFile(FileAttente &)		
	//  Extrants: void
	//	Description: Permet d'afficher touts les �l�ments de la file � la console
	/////////////////////////////////////////////////////////////////
	void	Afficher(ostream & out, FileAttente & maFile);
	/////////////////////////////////////////////////////////////////
	//	AfficherClient
	//	Intrants: maFile(FileAttente&)		
	//  Extrants: void
	//	Description: Permet d'afficher touts les �l�ments de un Client en file d'attente
	/////////////////////////////////////////////////////////////////
	void	AfficherClient(FileAttente& maFile) const;
	/////////////////////////////////////////////////////////////////
	//	GetClient
	//	Intrants: indice(int)		
	//  Extrants: string
	//	Description: Renvoie le nom d'un client plac� � l'indice dans la file d'attente
	/////////////////////////////////////////////////////////////////
	string	GetClient(int indice);
	/////////////////////////////////////////////////////////////////
	//	SectionEnString
	//	Intrants: section(int)
	//  Extrants: string
	//	Description: Permet de dissocier la section(int) � la section en string
	/////////////////////////////////////////////////////////////////
	string  SectionEnString(int section);
	/////////////////////////////////////////////////////////////////
	//	EstVide
	//	Intrants:	Aucun		
	//  Extrants:	Nous renvoie true s'il est bel et bien vide
	//	Description: V�rifie si la file d'attente est vide
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
	//				 nous demandons � l'usager s'il veut bel et bien
	//				 quitter
	/////////////////////////////////////////////////////////////////
	bool    Quitter();
	/////////////////////////////////////////////////////////////////
	//	VerificationSection
	//	Intrants:	 la section � v�rifier (int)		
	//  Extrants:	 un bool qui nous dit le client peut �tre assign�
	//				 � la table
	//	Description: V�rifie si le client peut �tre affect� � la 
	//				 table
	/////////////////////////////////////////////////////////////////
	bool VerificationSection(int laSection, ClientEnAttente * clientAEnlever);
	/////////////////////////////////////////////////////////////////
	//	AjusterPointeurs
	//	Intrants:	 le pointeur sur le client (ClientEnAttente*)		
	//  Extrants:	 Aucun
	//	Description: Ajuste les pointeurs apr�s le retrait du client
	/////////////////////////////////////////////////////////////////
	void AjusterPointeurs(ClientEnAttente * clientAEnlever)
};