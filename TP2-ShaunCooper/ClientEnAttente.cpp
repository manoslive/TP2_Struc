// Definition d'un ClientEnAttente. Essentiellement des
// mutateurs et accesseurs
//
// Modifier noeud à ClientEnAttente
// 
// par Pierre Prud'homme, octobre 2014
// modifier par Shaun Cooper, novembre 2014
//-------------------------------------------------
#include "ClientEnAttente.h"

ClientEnAttente::ClientEnAttente()
{
	SetPrecedent(nullptr);   // 0 indique qu'on ne connait pas l'adresse; equivaut à null
	SetSuivant(nullptr);
	SetNom("");
}
ClientEnAttente::ClientEnAttente(string nom, int nbDePersonnes, int sectionsChoisie)
{
	if (sectionsChoisie > 0 && sectionsChoisie < 8)
	{
		SetNom(nom);
		SetSection(sectionsChoisie);
		SetNombreDePersonnes(nbDePersonnes);
		SetPrecedent(0);   // 0 indique qu'on ne connait pas l'adresse; equivaut à null
		SetSuivant(0);
	}
	else
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
	if (nom != "")
		InfoClient.nom_ = nom;
	else
		throw exception("Erreur: nom invalide. Veuillez entrer un nom");
}
string ClientEnAttente::GetNom() const
{
	return InfoClient.nom_;
}
void ClientEnAttente::SetNombreDePersonnes(int nbDePersonnes)
{
	if (nbDePersonnes > 0)
		InfoClient.nombreDePersonnes = nbDePersonnes;
	else
		throw exception("Erreur: nombre de personnes dans le groupe invalide. Le nombre doit être plus grand que 0");
}
void ClientEnAttente::SetSection(int sectionChoisie)
{
	if (sectionChoisie > 0 && sectionChoisie < 8)
		InfoClient.section = sectionChoisie;
	else
		throw exception("Erreur: Section invalide!");
}
int ClientEnAttente::GetNombreDePersonnes() const
{
	return InfoClient.nombreDePersonnes;
}
int ClientEnAttente::GetSection()
{
	return InfoClient.section;
}