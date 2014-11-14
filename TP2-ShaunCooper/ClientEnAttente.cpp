//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	ClientEnAttente.cpp														//
//	Definition d'un ClientEnAttente. Essentiellement des					//
//  mutateurs et accesseurs													//
//----------------------------------------------------------------------------//
// À faire : - Mettre des commentaires

#include "ClientEnAttente.h"

ClientEnAttente::ClientEnAttente()
{
	SetPrecedent(nullptr);   // 0 indique qu'on ne connait pas l'adresse; equivaut à null
	SetSuivant(nullptr);
	SetNom("");
}
ClientEnAttente::ClientEnAttente(string nom, int nbDePersonnes, int sectionsChoisie)
{
	if (sectionsChoisie > 0 && sectionsChoisie < 8) // Le choix est valide
	{
		SetNom(nom);
		SetSection(sectionsChoisie);
		SetNombreDePersonnes(nbDePersonnes);
		SetPrecedent(nullptr);   // 0 indique qu'on ne connait pas l'adresse; equivaut à null
		SetSuivant(nullptr);
	}
	else // Le choix est invalide, on lance une exception
		cout << "La section choisie est invalide. Choix: salle(0), terrasse(1), terrasseFumeur(2)" << endl;
}
void ClientEnAttente::SetPrecedent(ClientEnAttente * p)
{
		pPrecedent_ = p;
}
void ClientEnAttente::SetSuivant(ClientEnAttente *p)
{
		pSuivant_ = p;
}
ClientEnAttente * ClientEnAttente::GetPrecedent() const
{
	return pPrecedent_;
}
ClientEnAttente * ClientEnAttente::GetSuivant() const
{
	return pSuivant_;
}
void ClientEnAttente::SetNom(string nom)
{
	if (nom != "") // Le choix est valide
		InfoClient.nom_ = nom;
	else // Le choix est invalide, on lance une exception
		throw exception("Erreur: nom invalide. Veuillez entrer un nom");
}
string ClientEnAttente::GetNom() const
{
	return InfoClient.nom_;
}
void ClientEnAttente::SetNombreDePersonnes(int nbDePersonnes)
{
	if (nbDePersonnes > 0) // Le choix est valide
		InfoClient.nombreDePersonnes = nbDePersonnes;
	else // Le choix est invalide, on lance une exception
		throw exception("Erreur: nombre de personnes dans le groupe invalide. Le nombre doit être plus grand que 0");
}
void ClientEnAttente::SetSection(int sectionChoisie)
{
	if (sectionChoisie > 0 && sectionChoisie < 8) // Le choix est valide
		InfoClient.section = sectionChoisie;
	else // Le choix est invalide, on lance une exception
		throw exception("Erreur: Section invalide!");
}
int ClientEnAttente::GetNombreDePersonnes() const
{
	return InfoClient.nombreDePersonnes;
}
int ClientEnAttente::GetSection() const
{
	return InfoClient.section;
}