//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Cr�� le : 10-11-14													    //
//	Derni�re modification : 13-11-14									        //
//	FileAttente.cpp														    //
//	D�finitions des fonctions permettant de g�rer plusieurs ClientEnAttente //
//----------------------------------------------------------------------------//
// � faire : - Arranger la recherche dans Retirer



#include "FileAttente.h"
#include <sstream>

FileAttente::FileAttente()
{
	SetPremier(nullptr);
	SetDernier(nullptr);
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

	while (pTemporaire != nullptr)
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

	while (pTemporaire != nullptr)
	{
		nbPersonnes = nbPersonnes + (pTemporaire->GetNombreDePersonnes());
		pTemporaire = pTemporaire->GetSuivant();
	}

	return nbPersonnes;
}
void FileAttente::Ajouter(ClientEnAttente clientAMettreEnFile)
{
	ClientEnAttente * pNouveau = new ClientEnAttente(clientAMettreEnFile.GetNom(), clientAMettreEnFile.GetNombreDePersonnes(), clientAMettreEnFile.GetSection());
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
	ClientEnAttente *clientAEnlever = GetPremier();
	 bool trouver = false;

	if (clientAEnlever == 0)
		throw exception("Erreur: La file d'attente est vide!");

	for (int i = nbPlacesDeLaTable; i > 0 && trouver != false; i--)
	{
		clientAEnlever = clientAEnlever->GetSuivant();
		if (clientAEnlever->GetNombreDePersonnes() != i && clientAEnlever->GetSection() != sectionDeLaTable)
			trouver = true;
	}

	if (!trouver)
	throw exception("Aucun match"); // S'il ne trouve pas de match

	ClientEnAttente unClient(clientAEnlever->GetNom(), clientAEnlever->GetNombreDePersonnes(), clientAEnlever->GetSection()); // Copie des informations dans un client qui sera effac� lors de la fermeture de la m�thode

	Retirer(unClient.GetNom(), unClient.GetNombreDePersonnes()); // Ici on appelle la m�thode qui va retirer le client de la file d'attente
	// Je vais tenter d'appeler la m�thode retirer avec bool au lieu de faire le delete et le count de groupe ici - manu
	//delete pTemporaire;
	//SetNbGroupes(ObtenirNbGroupes() - 1);

	return unClient.InfoClient;
}
bool FileAttente::Retirer(string nomDuClient, int nbPersonnes)
{
	ClientEnAttente *clientAEnlever = GetPremier();
	bool clientTrouver = false;

	if (clientAEnlever == nullptr)
		throw exception("Erreur: File d'attente vide!");

	while (!clientTrouver)
	{
		if (clientAEnlever->GetNom() == nomDuClient && clientAEnlever->GetNombreDePersonnes() == nbPersonnes)
		{
			clientTrouver = true;
			if (clientAEnlever->GetPrecedent() != nullptr) // Cas o� il y a un client avant lui
				clientAEnlever->GetPrecedent()->SetSuivant(clientAEnlever->GetPrecedent()); // On d�place le pointeur sur le pr�c�dent
			else if (clientAEnlever->GetSuivant() != nullptr) // Cas o� il y a un client apr�s lui
			{
				clientAEnlever->GetSuivant()->SetPrecedent(nullptr); // On met le pr�c�dent � nul
				SetPremier(clientAEnlever->GetSuivant()); // Le client suivant devient le premier client
			}
			else // Cas o� il est seul dans la file
			{
				SetDernier(nullptr);
				SetPremier(nullptr);
			}

			if (clientAEnlever->GetSuivant() != nullptr) // Cas o� il y a un client apr�s lui
				clientAEnlever->GetSuivant()->SetPrecedent(clientAEnlever->GetPrecedent());

			else if (clientAEnlever->GetPrecedent() != nullptr) // Cas o� il y a un client avant lui
			{
				clientAEnlever->GetPrecedent()->SetSuivant(nullptr);
				SetDernier(clientAEnlever->GetPrecedent()); // On sait qu'on est au bout de la file donc on met le precedent en tant que dernier
			}
			delete clientAEnlever; // On retire le client assign� � une table
			SetNbGroupes(GetNbGroupes() - 1); // On diminu le nombre de groupe de 1
		}
		else // Si le nom du client n'est pas le bon et que le nombre non plus, on passe au suivant
		{
			clientAEnlever = clientAEnlever->GetSuivant();
		}
	}
	return clientTrouver; // On retourne le client retir�


	//while (pBalayage != nullptr && pBalayage->GetNom() != nomClient && pBalayage->GetNombreDePersonnes() != nbPersonnes) 
	//{
	//	pBalayage = pBalayage->GetSuivant();
	//}
	//if (pBalayage->GetNom() == nomClient && pBalayage->GetNombreDePersonnes() == nbPersonnes)
	//	delete pBalayage;

	//return pBalayage != nullptr;

}
void FileAttente::Afficher(ostream & out, FileAttente & maFile)
{
	ClientEnAttente *clientAfficher = GetPremier();
	if (clientAfficher != nullptr)
	{
		cout << "--------------------------- " << endl
			<< "�  Voici la file d'attente �" << endl
			<< "-----------------------------" << endl;
	}
	else
		cout << "La file d'attente est vide!" << endl;

	while (clientAfficher != nullptr)
	{
		out << "Nom: " + clientAfficher->GetNom() << endl
			<< "Nb Personnes: " << clientAfficher->GetNombreDePersonnes() << endl
			<< "Section: " << SectionEnString(clientAfficher->GetSection()) <<  endl;
		clientAfficher = clientAfficher->GetSuivant(); // Ajouter l'affichage de la section
	}
	cout << "--------------------------------" << endl
	     << "Nombres de groupes: " << maFile.ObtenirNbGroupes() << endl
	     << "Nombres de personnes au total: " << maFile.ObtenirNbPersonnes() << endl;
	out << endl;
}

void FileAttente::AfficherClient(FileAttente& maFile) const
{
	int rang = 1; // Le rang dans la file d'attente

	cout << "Donnez la position dans la file du client dont vous voulez de l'information" << endl;
	cin  >> rang;
	cout << "Le client #" << rang << ":" << endl << maFile.GetClient(rang);

}

string FileAttente::SectionEnString(int section)
{
	string sectionString = "";
	switch (section)
	{
	case 1:
		sectionString = "Salle � manger";
		break;
	case 2:
		sectionString = "Salle � manger et terrasse non fumeur";
		break;
	case 3:
		sectionString = "Salle � manger et terrasse fumeur";
		break;
	case 4:
		sectionString = "Peu importe la section";
		break;
	case 5:
		sectionString = "Terrasse non fumeur";
		break;
	case 6:
		sectionString = "Les terrasses";
		break;
	case 7:
		sectionString = "Terrasse fumeur";
		break;
	}
	return sectionString;
}

string FileAttente::GetClient(int indice)
{
	ClientEnAttente * clientARetourner = GetPremier();
	int rang = 1;
	string client;
	stringstream ss;

	while (clientARetourner != nullptr && rang != indice)
	{
		clientARetourner = clientARetourner->GetSuivant();
		rang++;
	}
	if (clientARetourner == nullptr)
	{
		throw exception("Erreur: La file d'attente est vide!");
	}

	ss << "Nom: " << clientARetourner->GetNom() << endl << "Nombre de personnes dans le groupe: " << (clientARetourner->GetNombreDePersonnes()) << endl << "Section du restaurant: " << (SectionEnString(clientARetourner->GetSection())) << endl;
	client = ss.str();
	return client;
}