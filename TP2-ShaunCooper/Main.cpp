//----------------------------------------------------------------------------//
//  TP2 - File d'attente													    //
//	Shaun Cooper & Emmanuel Beloin										    //
//	Créé le : 10-11-14													    //
//	Dernière modification : 13-11-14									        //
//	Main.cpp															    //
//	Programme qui permet de gérer un file d'attente d'un restaurent         //
//----------------------------------------------------------------------------//

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
	// AfficherStringLine();
	cout << "-------------------------------" << endl
		 << "¦    Restaurant chez Tunak    ¦" << endl
		 << "-------------------------------" << endl
		 << "Faites un choix parmi les suivants:" << endl
		 << "-----------------------------------" << endl
		 << "1. Ajouter un client dans la file" << endl
		 << "2. Assigner une table" << endl
		 << "3. Retirer un client qui quitte" << endl
		 << "4. Afficher un client de la file" << endl
		 << "5. Afficher la file d'attente en entier" << endl
		 << "6. Quitter le programme" << endl;
}
void AfficherChoixSection()
{
	cout << "------------------------ -------------------------" << endl
		 << "¦    Choisissez la/les section(s) désirée(s)    ¦" << endl
		 << "--------------------------------------------------" << endl
	     << "1. Salle" << endl
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
	cout << "------------------------ " << endl
		 << "¦    Ajout de client    ¦" << endl
		 << "-------------------------" << endl
		 << "Donnez le nom du client: " << endl;
	cin  >> nom;
	cout << "Donnez le nombre de personne dans ce groupe: ";
	cin  >> nbPersonnes;
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
	cout << "------------------------ ------------"<< endl
		 << "¦  Assigner une table à un client   ¦"<< endl
		 << "-------------------------------------"<< endl
	     << "Combien de places a cette table? "<< endl;
	cin  >> nbPlacesTable;
	cout << endl << "Dans quelle section est-elle? " << endl;
	AfficherChoixSection();
	cin  >> section;
	cout << maFile.Retirer(nbPlacesTable, section).nom_ << "à été retiré" << endl;  ////tester...
}
void ClientPart(FileAttente& maFile)
{
	string nomClientRetirer;
	int nbPersonnes = 0;
	cout << "------------------------ " << endl
		 << "¦   Retrait de client   ¦" << endl
		 << "-------------------------" << endl
	     << "Nom du client à retirer: ";
	cin  >> nomClientRetirer;
	cout << "Nombre de personnes?";
	cin  >> nbPersonnes;
	(maFile.Retirer(nomClientRetirer, nbPersonnes)) ? nomClientRetirer + " a été trouvé et retiré" : nomClientRetirer + " n'a pas été trouvé";
}

int main()
{
	setlocale(LC_ALL, ""); // Permet d'afficher les accents à la console
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
				// AfficherStringLine();
				break;
			case 2:
				AssignerTable(maFile);
				//AfficherStringLine();
				break;
			case 3:
				ClientPart(maFile);
				//AfficherStringLine();
				break;
			case 4:
				maFile.AfficherClient(maFile);
				break;
			case 5:
				maFile.Afficher(cout);
				//AfficherStringLine();
				break;
			case 6:
				quitter = true;
				break;
			default:
				cout << "Entrez un des choix suivants.." << endl;
			}

		} while (!quitter);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}