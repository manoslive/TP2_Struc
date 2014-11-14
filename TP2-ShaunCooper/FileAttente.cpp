//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	FileAttente.cpp														    //
//	Définitions des fonctions permettant de gérer plusieurs ClientEnAttente //
//----------------------------------------------------------------------------//
// À faire : - Mettre des commentaires

#include "FileAttente.h"
#include <sstream>

FileAttente::FileAttente()
{
	SetPremier(nullptr); // Le pointeur est initialisé à nul
	SetDernier(nullptr);
	SetNbGroupes(0);  // Initialisation à 0 pour la construction
	SetNbPersonnes(0);
	SetNbGroupesAssignes(0);
	SetNbPersonnesAssignes(0);
}

bool FileAttente::EstVide()
{
	return GetPremier() == nullptr;
}

int FileAttente::ObtenirNbGroupes()
{
	ClientEnAttente * leGroupe = GetPremier(); // On pointe sur le premier groupe de la file
	int nbPersonnesDansGroupes = 0;

	while (leGroupe != nullptr) // S'il y a un groupe
	{
		nbPersonnesDansGroupes++; // C'est ici que l'on compte
		leGroupe = leGroupe->GetSuivant(); // On passe au groupe suivant
	}
	return nbPersonnesDansGroupes;
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
	if (nbGroupes >= 0) // Si le nombre de groupe est valide
		nbGroupes_ = nbGroupes;
	else
		throw exception("Erreur: Nombre de groupes invalides!"); // Sinon, on lance une exception

}

void FileAttente::SetNbPersonnes(int nbPersonnes)
{
	if (nbPersonnes >= 0) // Si le nombre de personnes est valide
		nbPersonnes_ = nbPersonnes;
	else
		throw exception("Erreur: Nombre de personnes invalides dans le groupe!"); // Sinon, on lance une exception
}

void FileAttente::SetNbGroupesAssignes(int nbGroupesAssignes)
{
	if (nbGroupesAssignes >= 0) // Si le nombre de groupe assignées est valide
		nbGroupesAssignes_ = nbGroupesAssignes;
	else
		throw exception("Erreur: Nombre de groupes assignés invalide!"); // Sinon, on lance une exception
}

void FileAttente::SetNbPersonnesAssignes(int nbPersonnesAssignes)
{
	if (nbPersonnesAssignes >= 0) // Si le nombre de personnes assignées
		nbPersonnesAssignes_ = nbPersonnesAssignes;
	else
		throw exception("Erreur: Nombre de personnes assignés invalide!"); // Sinon, on lance une exception
}

int FileAttente::ObtenirNbPersonnes()
{
	ClientEnAttente *leGroupe = GetPremier(); // On pointe sur le premier
	int nbPersonnesDansGroupe = 0;

	while (leGroupe != nullptr) // S'il y a un groupe
	{
		nbPersonnesDansGroupe = nbPersonnesDansGroupe + (leGroupe->GetNombreDePersonnes());
		leGroupe = leGroupe->GetSuivant();
	}

	return nbPersonnesDansGroupe;
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
	SetNbGroupes(GetNbGroupes() + 1);
	SetNbPersonnes(GetNbPersonnes() + clientAMettreEnFile.GetNombreDePersonnes());
}

ClientEnAttente::Client FileAttente::Retirer(int nbPlacesDeLaTable, int sectionDeLaTable, FileAttente & maFile)
{
	ClientEnAttente *clientAEnlever = GetPremier();
	ClientEnAttente *meilleurChoix = nullptr;
	bool trouver = false;

	if (clientAEnlever == nullptr)
		throw exception("Erreur: La file d'attente est vide!");

	for (int i = nbPlacesDeLaTable; i > 0 && !trouver; i--)
	{
		while (clientAEnlever != nullptr &&  !trouver)
		{
			if (clientAEnlever->GetNombreDePersonnes() == i && clientAEnlever->GetSection() == sectionDeLaTable)
			{
				trouver = true;
				meilleurChoix = clientAEnlever;
			}
			clientAEnlever = clientAEnlever->GetSuivant();
		}
	}
	if (!trouver)
		throw exception("Aucun match"); // S'il ne trouve pas de match

	ClientEnAttente unClient(meilleurChoix->GetNom(), meilleurChoix->GetNombreDePersonnes(), meilleurChoix->GetSection()); // Copie des informations dans un client qui sera effacé lors de la fermeture de la méthode

	Retirer(unClient.GetNom(), unClient.GetNombreDePersonnes()); // Ici on appelle la méthode qui va retirer le client de la file d'attente
	maFile.SetNbPersonnesAssignes(maFile.GetNbPersonnesAssignes() + nbPlacesDeLaTable);
	maFile.SetNbGroupesAssignes(maFile.GetNbGroupesAssignes() + 1);
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
			if (clientAEnlever->GetPrecedent() != nullptr) // Cas où il y a un client avant lui
				clientAEnlever->GetPrecedent()->SetSuivant(clientAEnlever->GetPrecedent()); // On déplace le pointeur sur le précédent
			else if (clientAEnlever->GetSuivant() != nullptr) // Cas où il y a un client après lui
			{
				clientAEnlever->GetSuivant()->SetPrecedent(nullptr); // On met le précédent à nul
				SetPremier(clientAEnlever->GetSuivant()); // Le client suivant devient le premier client
			}
			else if (clientAEnlever->GetSuivant() != nullptr) // Cas où il y a un client après lui
				clientAEnlever->GetSuivant()->SetPrecedent(clientAEnlever->GetPrecedent());

			else if (clientAEnlever->GetPrecedent() != nullptr) // Cas où il y a un client avant lui
			{
				clientAEnlever->GetPrecedent()->SetSuivant(nullptr);
				SetDernier(clientAEnlever->GetPrecedent()); // On sait qu'on est au bout de la file donc on met le precedent en tant que dernier
			}
			else // Cas où il est seul dans la file
			{
				SetDernier(nullptr);
				SetPremier(nullptr);
			}
			delete clientAEnlever; // On retire le client assigné à une table
			SetNbGroupes(GetNbGroupes() - 1); // On diminu le nombre de groupe de 1
		}
		else // Si le nom du client n'est pas le bon et que le nombre non plus, on passe au suivant
		{
			clientAEnlever = clientAEnlever->GetSuivant();
		}
	}
	return clientTrouver; // On retourne le client retiré
}

void FileAttente::Afficher(ostream & out, FileAttente & maFile)
{
	ClientEnAttente *clientAfficher = GetPremier();
	if (clientAfficher != nullptr)
	{
		system("cls");
		cout << "--------------------------- " << endl
			<< "¦  Voici la file d'attente ¦" << endl
			<< "-----------------------------" << endl;
	}
	else
		cout << "La file d'attente est vide!" << endl;

	while (clientAfficher != nullptr)
	{
		out << "Nom: " + clientAfficher->GetNom() << endl
			<< "Nb Personnes: " << clientAfficher->GetNombreDePersonnes() << endl
			<< "Section: " << SectionEnString(clientAfficher->GetSection()) << endl;
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
	cin >> rang;
	cout << "Le client #" << rang << ":" << endl << maFile.GetClient(rang);
}

string FileAttente::SectionEnString(int section)
{
	string sectionString = "";
	switch (section) //switch qui permet d'associer une string décrivant une section à une section décrit en numéro
	{
	case 1:
		sectionString = "Salle à manger";
		break;
	case 2:
		sectionString = "Salle à manger et terrasse non fumeur";
		break;
	case 3:
		sectionString = "Salle à manger et terrasse fumeur";
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
	int rang = 1; //rang dams la file d'attente initialisé à 1
	string client;
	stringstream ss;

	while (clientARetourner != nullptr && rang != indice) //pendant que clientARetourner est null et que rang n'et pas égale à l'indice..
	{
		clientARetourner = clientARetourner->GetSuivant(); //on prendd le client suivant en ligne
		rang++; //et on augemente le rang
	}
	if (clientARetourner == nullptr) //si le client associé à l'indice est vide... la file est vide
	{
		throw exception("Erreur: La file d'attente est vide!");
	}

	ss << "Nom: " << clientARetourner->GetNom() << endl << "Nombre de personnes dans le groupe: " << (clientARetourner->GetNombreDePersonnes()) << endl << "Section du restaurant: " << (SectionEnString(clientARetourner->GetSection())) << endl;
	client = ss.str();
	return client;
}

bool FileAttente::Quitter()
{
	string quitter = "";
	bool resultat = false;

	cout << "Il reste des clients dans la file d'attente. Etes-vous certains de vouloir quitter? (o/n)" << endl;
	cin >> quitter;

	if (quitter == "o" || quitter == "O")
		resultat = true;

	return resultat;
}