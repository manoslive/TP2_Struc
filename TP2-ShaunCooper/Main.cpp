/*
	Shaun Cooper - Emmanuel Beloin
	TP2 - File d'attente
	dernière modification : 13-11-14
	Main.cpp
	Programme qui permet de gérer un file d'attente d'un restaurent  ASDFGH dfkjgndfjgn
*/

#include "ClientEnAttente.h"
#include "FileAttente.h"
#include <iostream>
using namespace std;

void AfficherStringLine()
{
	cout << string(70, '-') << endl << endl;
}
void AfficherMenu()
{
	AfficherStringLine();
	cout << "1. Ajouter un client dans la file" << endl
		<< "2. Assigner une table" << endl
		<< "3. Retirer un client qui quitte" << endl
		<< "4. Afficher un client de la file" << endl
		<< "5. Afficher la file d'attente en entier" << endl
		<< "6. Quitter le programme" << endl;
}
void AfficherChoixSection()
{
	//Choix de sections
	cout << "1. Salle" << endl
		<< "2. Salle et Terrasse" << endl
		<< "3. Salle et TerrasseFumeur" << endl
		<< "4. Salle, Terrasse et TerrasseFumeur" << endl
		<< "5. Terrasse" << endl
		<< "6. Terrasse et TerrasseFumeur" << endl
		<< "7. TerrasseFumeur" << endl;
}
void AjouterClient(FileAttente& maFile)
{
	int choixSection=0;
	string nom;
	int nbPersonnes = 0;

	cout << "Donnez un nom: ";
	cin >> nom;
	cout << "Combien de personnes? : ";
	cin >> nbPersonnes;
	cout << endl;
	AfficherChoixSection();
	cin >> choixSection;
	ClientEnAttente monClient(nom, nbPersonnes, choixSection);
	maFile.Ajouter(monClient);
}
void AssignerTable(FileAttente& maFile)
{
	int nbPlacesTable = 0;
	int section = 0;
	cout << "Nombre de places à la table?: ";
	cin >> nbPlacesTable;
	cout << endl << "Nombre de personnes?";
	cin >> section;
	cout << maFile.Retirer(nbPlacesTable, section).nom_ << "à été retiré" << endl;  ////tester...
}
void ClientPart(FileAttente& maFile)
{
	string nomClientRetirer;
	int nbPersonnes = 0;
	cout << "Nom du client à retirer: ";
	cin >> nomClientRetirer;
	cout << "Nombre de personnes?";
	cin >> nbPersonnes;
	maFile.Retirer(nomClientRetirer, nbPersonnes);
}

int main()
{
	setlocale(LC_ALL, "");
	FileAttente maFile;
	int choix = 0;
	bool quitter = false;
	try
	{
		do
		{
			AfficherMenu();
			cin >> choix;

			switch (choix)
			{
			case 1:
				AjouterClient(maFile);
				AfficherStringLine();
				break;
			case 2:
				AssignerTable(maFile);
				AfficherStringLine();
				break;
			case 3:
				ClientPart(maFile);
				AfficherStringLine();
				break;
			case 4:
			{

			}
				break;
			case 5:
				maFile.Afficher(cout);
				cout << "Nombres de gorupes: " << maFile.ObtenirNbGroupes() << endl;
				cout << "Nombres de personnes au total: " << maFile.ObtenirNbPersonnes() << endl;
				AfficherStringLine();
				break;
			case 6:
				quitter = true;
				break;
			default:
			{
				cout << "Entrez un des choix suivants.." << endl;
			}
			}
		} while (quitter == false);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}