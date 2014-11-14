//----------------------------------------------------------------------------//
//  TP2 - File d'attente	                                                    //
//	Shaun Cooper & Emmanuel Beloin                                          //
//	Cr�� le : 10-11-14                                                      //
//	Derni�re modification : 13-11-14                                        //
//	Main.cpp                                                                //
//	Programme qui permet de g�rer un file d'attente d'un restaurent         //
//----------------------------------------------------------------------------//
// � faire : - Assigner table (choix #2) ne fonctionne pas

#include "ClientEnAttente.h"
#include "FileAttente.h"
#include <iostream>
using namespace std;

void AfficherMenu()
{
	// AfficherStringLine();
	cout << "-------------------------------" << endl
		 << "�    Restaurant chez Tunak    �" << endl
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
		 << "�    Choisissez la/les section(s) d�sir�e(s)    �" << endl
		 << "--------------------------------------------------" << endl
	     << "1. Salle � manger" << endl
		 << "2. Salle � manger et terrasse non fumeur" << endl
		 << "3. Salle � manger et terrasse fumeur" << endl
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
		 << "�    Ajout de client    �" << endl
		 << "-------------------------" << endl
		 << "Donnez le nom du client: " << endl;
	cin  >> nom;
	cout << "Donnez le nombre de personne dans ce groupe: " << endl;
	cin  >> nbPersonnes;
	system("cls");
	cout << endl;
	AfficherChoixSection();
	cin >> choixSection;
	system("cls");
	ClientEnAttente monClient(nom, nbPersonnes, choixSection);
	maFile.Ajouter(monClient);
}
void AssignerTable(FileAttente& maFile)
{
	int nbPlacesTable = 0;
	int section = 0;

	cout << "-------------------------------------"<< endl
		 << "�  Assigner une table � un client   �"<< endl
		 << "-------------------------------------"<< endl
	     << "Combien de places a cette table? "<< endl;
	cin  >> nbPlacesTable;
	cout << endl << "Dans quelle section est-elle? " << endl;
	AfficherChoixSection();
	cin  >> section;
	system("cls");

	cout << maFile.Retirer(nbPlacesTable, section, maFile).nom_ << " a �t� retir�" << endl;  ////ne fonctionne pas
}
void ClientPart(FileAttente& maFile)
{
	string nomClientRetirer;
	int nbPersonnes = 0;

	cout << "------------------------ " << endl
		 << "�   Retrait de client   �" << endl
		 << "-------------------------" << endl
		 << "Nom du client � retirer: " << endl;
	cin  >> nomClientRetirer;
	cout << "Nombre de personnes?" << endl;
	cin  >> nbPersonnes;
	system("cls");
	
	if (maFile.Retirer(nomClientRetirer, nbPersonnes))
		cout << nomClientRetirer << " a �t� trouv� et retir�" << endl;
	else
		cout << nomClientRetirer << " n'a pas �t� trouv�" << endl;
}

void MessageQuitter(FileAttente & maFile)
{
	system("cls");
	cout << "--------------------------------" << endl
		<< "�   R�capitulatif de session   �" << endl
		<< "--------------------------------" << endl
		<< "Nombre de groupes assign�s � une table: " << maFile.GetNbGroupesAssignes() << endl
		<< "Nombre de personnes assign�es � une table: " << maFile.GetNbPersonnesAssignes() << endl
		<< "Nombre de groupes pr�sents dans la file: " << maFile.GetNbGroupes() << endl;
}

void EffectuerChoix(int choix, FileAttente& maFile, bool& quitter)
{
	switch (choix)
	{
	case 1:
		AjouterClient(maFile);
		break;
	case 2:
		AssignerTable(maFile);
		break;
	case 3:
		ClientPart(maFile);
		break;
	case 4:
		maFile.AfficherClient(maFile);
		break;
	case 5:
		maFile.Afficher(cout, maFile);
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
}

int main()
{
	setlocale(LC_ALL, ""); // Permet d'afficher les accents � la console
	FileAttente maFile;
	int choix = 0;
	bool quitter = false;
	try
	{
		do
		{
			AfficherMenu();
			cin >> choix;
			EffectuerChoix(choix,maFile,quitter);
		} while (!quitter);
		MessageQuitter(maFile);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}