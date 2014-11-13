/*
	Shaun Cooper
	TP2 - File d'attente
	FileAttente.cpp
	Définitions des fonctions permettant de gérer plusieurs ClientEnAttente
*/
#include "FileAttente.h"
#include <sstream>

FileAttente::FileAttente()
{
	SetPremier(0);
	SetDernier(0);
	SetNbGroupes(0);
	SetNbPersonnes(0);
}
bool FileAttente::EstVide()
{
	return GetPremier() == nullptr;
}
int FileAttente::ObtenirNbGroupes()
{
	ClientEnAttente *pTemporaire = GetPremier();
	int nbGroupes = 0;

	while (pTemporaire != 0)
	{
		nbGroupes++;
		pTemporaire = pTemporaire->GetSuivant();
	}

	return nbGroupes;
}
void FileAttente::SetPremier(ClientEnAttente *pPremier)
{
	pPremierClient_ = pPremier;
}
void FileAttente::SetDernier(ClientEnAttente *pDernier)
{
	pDernierClient_ = pDernier;
}
ClientEnAttente* FileAttente::GetPremier() const
{
	return pPremierClient_;
}
ClientEnAttente* FileAttente::GetDernier() const
{
	return pDernierClient_;
}
void FileAttente::SetNbGroupes(int nbGroupes)
{
	nbGroupes_ = nbGroupes;
}
void FileAttente::SetNbPersonnes(int nbPersonnes)
{
	nbPersonnes_ = nbPersonnes;
}
int FileAttente::ObtenirNbPersonnes()
{
	ClientEnAttente *pTemporaire = GetPremier();
	int nbPersonnes = 0;

	while (pTemporaire != 0)
	{
		nbPersonnes = nbPersonnes+(pTemporaire->GetNombreDePersonnes());
		pTemporaire = pTemporaire->GetSuivant();
	}

	return nbPersonnes;
}
void FileAttente::Ajouter(ClientEnAttente clientAMettreEnFile)
{
	ClientEnAttente * pNouveau = new ClientEnAttente(clientAMettreEnFile.GetNom(),clientAMettreEnFile.GetNombreDePersonnes(),clientAMettreEnFile.GetSection());
	if (EstVide())
	{
		SetPremier(pNouveau);
		SetDernier(pNouveau);
	}
	else
	{
		pNouveau->SetPrecedent(GetDernier());
		GetDernier()->SetSuivant(pNouveau);
		SetDernier(pNouveau);
	}
}
ClientEnAttente::Client FileAttente::Retirer(int nbPlacesDeLaTable, int sectionDeLaTable)
{
	ClientEnAttente *pTemporaire = GetPremier();
	bool trouver = false;
	if (pTemporaire == 0)
		throw exception("...La liste est vide...");

	for (int i = nbPlacesDeLaTable; i > 0 && trouver != false; i--)
	{
		while (pTemporaire != nullptr && pTemporaire->GetNombreDePersonnes() != i && pTemporaire->GetSection() != sectionDeLaTable)
			pTemporaire = pTemporaire->GetSuivant();

		if (pTemporaire->GetNombreDePersonnes() != i && pTemporaire->GetSection() != sectionDeLaTable)
			trouver = true;
	}

	if (!trouver)
		throw exception("Aucun match");

	ClientEnAttente unClient(pTemporaire->GetNom(), pTemporaire->GetNombreDePersonnes(), pTemporaire->GetSection());
	
	delete pTemporaire;
	SetNbGroupes(ObtenirNbGroupes() - 1);

	return unClient.InfoClient;
}
bool FileAttente::Retirer(string nomClient, int nbPersonnes)
{
	ClientEnAttente *pBalayage = GetPremier();

	while (pBalayage != nullptr && pBalayage->GetNom() != nomClient && pBalayage->GetNombreDePersonnes() != nbPersonnes) 
	{
		pBalayage = pBalayage->GetSuivant();
	}
	if (pBalayage->GetNom() == nomClient && pBalayage->GetNombreDePersonnes() == nbPersonnes)
		delete pBalayage;

	return pBalayage != nullptr;
}
void FileAttente::Afficher(ostream & out)
{
	ClientEnAttente *pTemporaire = GetPremier();

	while (pTemporaire != 0)
	{
		out << "Nom: " + pTemporaire->GetNom() + "   "+ "Nb Personnes: " << (pTemporaire->GetNombreDePersonnes()) << endl;
		pTemporaire = pTemporaire->GetSuivant();
	}
	out << endl;
}
string FileAttente::GetClient(int indice)
{
	ClientEnAttente * pBalayage = GetPremier();
	int rang = 1;
	string Client;
	stringstream ss;

	while (pBalayage != nullptr && rang != indice)
	{
		pBalayage = pBalayage->GetSuivant();
		rang++;
	}
	if (pBalayage == nullptr)
	{
		
	}
	ss << pBalayage->GetNom() << (pBalayage->GetNombreDePersonnes()) <<(pBalayage->GetSection());
	
	return Client;
}