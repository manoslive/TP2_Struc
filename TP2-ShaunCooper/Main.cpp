//----------------------------------------------------------------------------//
//  TP2 - File d'attente													  //
//	Shaun Cooper & Emmanuel Beloin										      //
//	Créé le : 10-11-14													      //
//	Dernière modification : 13-11-14									      //
//	Main.cpp															      //
//	Programme qui permet de gérer un file d'attente d'un restaurent           //
//----------------------------------------------------------------------------//
// À faire : - Assigner table (choix #2) ne fonctionne pas

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
	     << "1. Salle à manger" << endl
		 << "2. Salle à manger et terrasse non fumeur" << endl
		 << "3. Salle à manger et terrasse fumeur" << endl
		 << "4. Peu importe la section" << endl
		 << "5. Terrasse non fumeur" << endl
		 << "6. Les terrasses" << endl
		 << "7. Terrasse fumeur" << endl;
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
	cout << "Donnez le nombre de personne dans ce groupe: " << endl;
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
	system("cls");
	cout << "-------------------------------------"<< endl
		 << "¦  Assigner une table à un client   ¦"<< endl
		 << "-------------------------------------"<< endl
	     << "Combien de places a cette table? "<< endl;
	cin  >> nbPlacesTable;
	cout << endl << "Dans quelle section est-elle? " << endl;
	AfficherChoixSection();
	cin  >> section;
	cout << maFile.Retirer(nbPlacesTable, section).nom_ << "à été retiré" << endl;  ////ne fonctionne pas
	maFile.SetNbPersonnes(maFile.GetNbPersonnes() + nbPlacesTable);
	maFile.SetNbGroupes(maFile.GetNbGroupesAssignes() + 1);
}
void ClientPart(FileAttente& maFile)
{
	string nomClientRetirer;
	int nbPersonnes = 0;
	cout << "------------------------ " << endl
		 << "¦   Retrait de client   ¦" << endl
		 << "-------------------------" << endl
		 << "Nom du client à retirer: " << endl;
	cin  >> nomClientRetirer;
	cout << "Nombre de personnes?" << endl;
	cin  >> nbPersonnes;
	
	if (maFile.Retirer(nomClientRetirer, nbPersonnes))
		cout << nomClientRetirer << " a été trouvé et retiré" << endl;
	else
		cout << nomClientRetirer << " n'a pas été trouvé" << endl;
}

void MessageQuitter(FileAttente & maFile)
{
	cout << "--------------------------------" << endl
		<< "¦   Récapitulatif de session   ¦" << endl
		<< "--------------------------------" << endl
		<< "Nombre de groupes assignés à une table: " << maFile.GetNbGroupesAssignes() << endl
		<< "Nombre de personnes assignées à une table: " << maFile.GetNbPersonnesAssignes() << endl
		<< "Nombre de groupes présents dans la file: " << maFile.GetNbGroupes() << endl;
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
				maFile.Afficher(cout, maFile);
				//AfficherStringLine();
				break;
			case 6:
				if (maFile.GetNbGroupes() != 0)
					quitter = maFile.Quitter();
				else
					quitter = true;
				break;
			default:
				cout << "Entrez un des choix suivants.." << endl;
			}
		} while (!quitter);
		MessageQuitter(maFile);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}