//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Cr�� le : 10-11-14													    //
//	Derni�re modification : 13-11-14									        //
//	FileAttente.cpp														    //
//	D�finitions des fonctions permettant de g�rer plusieurs ClientEnAttente //
//----------------------------------------------------------------------------//
// � faire : - Mettre des commentaires

#include "FileAttente.h"
#include <sstream>

FileAttente::FileAttente()
{
	SetPremier(nullptr); // Le pointeur est initialis� � nul
	SetDernier(nullptr);
	SetNbGroupes(0);  // Initialisation � 0 pour la construction
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
	if (nbGroupesAssignes >= 0) // Si le nombre de groupe assign�es est valide
		nbGroupesAssignes_ = nbGroupesAssignes;
	else
		throw exception("Erreur: Nombre de groupes assign�s invalide!"); // Sinon, on lance une exception
}

void FileAttente::SetNbPersonnesAssignes(int nbPersonnesAssignes)
{
	if (nbPersonnesAssignes >= 0) // Si le nombre de personnes assign�es
		nbPersonnesAssignes_ = nbPersonnesAssignes;
	else
		throw exception("Erreur: Nombre de personnes assign�s invalide!"); // Sinon, on lance une exception
}

int FileAttente::ObtenirNbPersonnes()
{
	ClientEnAttente *leGroupe = GetPremier(); // On pointe sur le premier
	int nbPersonnesDansGroupe = 0;

	while (leGroupe != nullptr) // S'il y a un groupe
	{
		nbPersonnesDansGroupe = nbPersonnesDansGroupe + (leGroupe->GetNombreDePersonnes()); // On ajoute au nombre total de personnes
		leGroupe = leGroupe->GetSuivant(); // On passe au suivant
	}

	return nbPersonnesDansGroupe; // On retourne ce nombre
}

void FileAttente::Ajouter(ClientEnAttente clientAMettreEnFile)
{
	ClientEnAttente * clientAAjouter = new ClientEnAttente(clientAMettreEnFile.GetNom(), clientAMettreEnFile.GetNombreDePersonnes(), clientAMettreEnFile.GetSection()); // On creer un ClientEnAttente dans le tas
	if (EstVide())
	{
		SetPremier(clientAAjouter); // On met le pointeur �gal au pointeur nul
		SetDernier(clientAAjouter); // ici aussi
	}
	else
	{

		clientAAjouter->SetPrecedent(GetDernier()); // S'il n'est pas vide, on affecte le pointeur precedent au dernier 
		GetDernier()->SetSuivant(clientAAjouter);
		SetDernier(clientAAjouter);
	}
	SetNbGroupes(GetNbGroupes() + 1); // On ajoute 1 au nombre de groupe
	SetNbPersonnes(GetNbPersonnes() + clientAMettreEnFile.GetNombreDePersonnes()); // On ajoute le nombre de personnes du groupe au combre total
}

bool FileAttente::VerificationSection(int laSection, ClientEnAttente * clientAEnlever)
{
	bool trouver = false;

	switch (laSection)
	{
	case 1:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 5 || clientAEnlever->GetSection() == 6 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 2:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 4 || clientAEnlever->GetSection() == 5 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 3:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 4 || clientAEnlever->GetSection() == 6 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 4:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 3 || clientAEnlever->GetSection() == 2 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 5:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 1 || clientAEnlever->GetSection() == 2 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 6:
		if (clientAEnlever->GetSection() == laSection || clientAEnlever->GetSection() == 1 || clientAEnlever->GetSection() == 3 || clientAEnlever->GetSection() == 7)
			trouver = true;
		break;
	case 7:
		trouver = true;
		break;
	}
	return trouver;
}

ClientEnAttente::Client FileAttente::Retirer(int nbPlacesDeLaTable, int sectionDeLaTable, FileAttente & maFile)
{
	ClientEnAttente *clientAEnlever = GetPremier();
	ClientEnAttente *meilleurChoix = nullptr;
	bool trouver = false;

	if (clientAEnlever == nullptr) //si le pointeur qui contient le premier est vide.... la file est vide
		throw exception("Erreur: La file d'attente est vide!");

	for (int i = nbPlacesDeLaTable; i > 0 && !trouver; i--) //parcours chaque disponibilit� de nombres de places disponibles jusqua 0 et tant que trouver = false...
	{
		clientAEnlever = GetPremier();
		while (clientAEnlever != nullptr &&  !trouver) //tant que clientAEnlever n'est pas null et que trouver = false...
		{
			if (clientAEnlever->GetNombreDePersonnes() == i) //si le nombres de personnes du Client est �gale � la disponibilit� 
			{												 //et que la section choisi par le cliet est �gale � la section disponible...
				trouver = VerificationSection(sectionDeLaTable, clientAEnlever); // On v�rifie si le client est admissible
				if (trouver)
					meilleurChoix = clientAEnlever;
			}
			clientAEnlever = clientAEnlever->GetSuivant();
		}
	}
	if (!trouver)
		cout << "Aucun match" << endl; // S'il ne trouve pas de match
	else
	{
		ClientEnAttente unClient(meilleurChoix->GetNom(), meilleurChoix->GetNombreDePersonnes(), meilleurChoix->GetSection()); // Copie des informations dans un client qui sera effac� lors de la fermeture de la m�thode

		Retirer(unClient.GetNom(), unClient.GetNombreDePersonnes()); // Ici on appelle la m�thode qui va retirer le client de la file d'attente
		maFile.SetNbPersonnesAssignes(maFile.GetNbPersonnesAssignes() + unClient.GetNombreDePersonnes());
		maFile.SetNbGroupesAssignes(maFile.GetNbGroupesAssignes() + 1);
		return unClient.InfoClient;
	}
	return ClientEnAttente::Client();
}

void FileAttente::AjusterPointeurs(ClientEnAttente * clientAEnlever)
{
	if (clientAEnlever->GetPrecedent() == nullptr && clientAEnlever->GetSuivant() != nullptr)// Cas o� il est le premier
	{
		clientAEnlever->GetSuivant()->SetPrecedent(nullptr);
		SetPremier(clientAEnlever->GetSuivant());
	}
	else if (clientAEnlever->GetSuivant() != nullptr && clientAEnlever->GetPrecedent() != nullptr) // Cas o� il est dans le milieu
	{
		clientAEnlever->GetPrecedent()->SetSuivant(clientAEnlever->GetSuivant());
		clientAEnlever->GetSuivant()->SetPrecedent(clientAEnlever->GetPrecedent());
	}
	else if (clientAEnlever->GetPrecedent() != nullptr && clientAEnlever->GetSuivant() == nullptr) // Cas o� il est le dernier
	{
		clientAEnlever->GetPrecedent()->SetSuivant(nullptr);
		SetDernier(clientAEnlever->GetPrecedent());
	}
	else // Cas o� il est seul dans la file
	{
		SetDernier(nullptr);
		SetPremier(nullptr);
	}
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
			AjusterPointeurs(clientAEnlever);
			delete clientAEnlever; // On retire le client assign� � une table
			SetNbGroupes(GetNbGroupes() - 1); // On diminu le nombre de groupe de 1
		}
		else // Si le nom du client n'est pas le bon et que le nombre non plus, on passe au suivant
			clientAEnlever = clientAEnlever->GetSuivant();
	}
	return clientTrouver; // On retourne le client retir�
}

void FileAttente::Afficher(ostream & out, FileAttente & maFile)
{
	ClientEnAttente *clientAfficher = GetPremier();
	if (clientAfficher != nullptr)
	{
		system("cls");
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
	cout << "Le client #" << rang << ":" << endl << maFile.GetClient(rang) << endl;
}

string FileAttente::SectionEnString(int section)
{
	string sectionString = "";
	switch (section) //switch qui permet d'associer une string d�crivant une section � une section d�crit en num�ro
	{
	case 1:
		sectionString = "Salle � manger";
		break;
	case 2:
		sectionString = "Terrasse non fumeur";
		break;
	case 3:
		sectionString = "Terrasse fumeur";
		break;
	case 4:
		sectionString = "Les terrasses";
		break;
	case 5:
		sectionString = "Salle � manger et terrasse non fumeur";
		break;
	case 6:
		sectionString = "Salle � manger et terrasse fumeur";
		break;
	case 7:
		sectionString = "Toutes les sections";
		break;
	}
	return sectionString;
}

string FileAttente::GetClient(int indice)
{
	ClientEnAttente * clientARetourner = GetPremier();
	int rang = 1; //rang dans la file d'attente initialis� � 1
	string client;
	stringstream ss;

	while (clientARetourner != nullptr && rang != indice) //pendant que clientARetourner est null et que rang n'et pas �gale � l'indice..
	{
		clientARetourner = clientARetourner->GetSuivant(); //on prendd le client suivant en ligne
		rang++; //et on augemente le rang
	}
	if (clientARetourner == nullptr) //si le client associ� � l'indice est vide... la file est vide
		client = "Erreur: L'indice n'est pas associ� � un client!";
	else
	{
		ss << "Nom: " << clientARetourner->GetNom() << endl << "Nombre de personnes dans le groupe: " << (clientARetourner->GetNombreDePersonnes()) << endl << "Section du restaurant: " << (SectionEnString(clientARetourner->GetSection())) << endl;
		client = ss.str();
	}
	return client;
}

bool FileAttente::Quitter()
{
	string quitter = "";
	bool resultat = false;

	cout << "Il reste des clients dans la file d'attente. Etes-vous certain(e) de vouloir quitter? (o/n)" << endl;
	cin >> quitter;

	if (quitter == "o" || quitter == "O")
		resultat = true;

	return resultat;
}