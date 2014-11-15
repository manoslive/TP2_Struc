//----------------------------------------------------------------------------//
//  TP2 - File d'attente	                                                    //
//	Shaun Cooper & Emmanuel Beloin                                          //
//	Créé le : 10-11-14                                                      //
//	Dernière modification : 13-11-14                                        //
//	Main.cpp                                                                //
//	Programme qui permet de gérer un file d'attente d'un restaurent         //
//----------------------------------------------------------------------------//
// À faire : - Bug avec afficher la file d'attente
//			 - Bug lorsqu'on retire ( on avait 2 possibilités dans la même 
//			   et il n'a pas trouvé de match )

#include "ClientEnAttente.h"
#include "FileAttente.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//	IsAlpha
//	Intrants: s(string)
//  Extrants: bool
//	Description: Permet de vérifier si le string entré est constitué de lettres alphabétiques
//////////////////////////////////////////////////////////////////////////////////
bool IsAlpha(string s)
{
	char c;

	// Accéder chaque caractère du string une lettre à la fois
	for (unsigned int i = 0; i < s.length(); i++)
	{
		c = s.at(i);         // Get le char du string

		// Si ce caractère n'est pas entre a et z ou bien A ou Z
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		{
			cout << "Erreur. Entrez des lettres pour le nom du client" << std::endl;
			return false;
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////
//	AfficherMenu
//	Intrants: aucun
//  Extrants: aucun
//	Description: Permet d'afficher le menu principal du programme
//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////
//	AfficherChoixSection
//	Intrants: aucun
//  Extrants: void
//	Description: Permet d'afficher le menu de Choix de sections
//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////
//	AjouterClient
//	Intrants: maFile(FileAttente&)
//  Extrants: void
//	Description: Permet d'effectuer l'ensemble de fonction permettant d'ajouter un Client
//				 à la file d'attente.
//////////////////////////////////////////////////////////////////////////////////
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
	while (!IsAlpha(nom)) //vérifie si le nom entré est constitué de lettres , sinon on redemande..
		cin >> nom;

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
//////////////////////////////////////////////////////////////////////////////////
//	AssignerTable
//	Intrants: maFile(FileAttente&)
//  Extrants: void
//	Description: Enemble de fonctions permettant d'assigner un client à une table
//				 et de le retirer de la file
//////////////////////////////////////////////////////////////////////////////////
void AssignerTable(FileAttente& maFile)
{
	int nbPlacesTable = 0;
	int section = 0;

	cout << "-------------------------------------"<< endl
		 << "¦  Assigner une table à un client   ¦"<< endl
		 << "-------------------------------------"<< endl
	     << "Combien de places a cette table? "<< endl;
	cin  >> nbPlacesTable;
	cout << endl << "Dans quelle section est-elle? " << endl;
	AfficherChoixSection();
	cin  >> section;
	system("cls");

	cout << maFile.Retirer(nbPlacesTable, section, maFile).nom_ << " a été retiré" << endl;  ////ne fonctionne pas
}
//////////////////////////////////////////////////////////////////////////////////
//	ClientPart
//	Intrants: maFile(FileAttente&)
//  Extrants: void
//	Description: Permet de retirer un client de la file d'attente qui part, car il est tanné d'attendre
//////////////////////////////////////////////////////////////////////////////////
void ClientPart(FileAttente& maFile)
{
	string nomClientRetirer;
	int nbPersonnes = 0;

	cout << "------------------------ " << endl
		 << "¦   Retrait de client   ¦" << endl
		 << "-------------------------" << endl
		 << "Nom du client à retirer: " << endl;
	cin  >> nomClientRetirer;
	while(!IsAlpha(nomClientRetirer))
		cin >> nomClientRetirer;
	cout << "Nombre de personnes?" << endl;
	cin  >> nbPersonnes;
	system("cls");
	
	if (maFile.Retirer(nomClientRetirer, nbPersonnes))
		cout << nomClientRetirer << " a été trouvé(e) et retiré(e)" << endl;
	else
		cout << nomClientRetirer << " n'a pas été trouvé(e)" << endl;
}
//////////////////////////////////////////////////////////////////////////////////
//	MessageQuitter
//	Intrants: maFile(FileAttente&)
//  Extrants: void
//	Description: Afficher un message qui résume la file d'attente lorsque l'usager quitte
//////////////////////////////////////////////////////////////////////////////////
void MessageQuitter(FileAttente & maFile)
{
	system("cls");
	cout << "--------------------------------" << endl
		<< "¦   Récapitulatif de session   ¦" << endl
		<< "--------------------------------" << endl
		<< "Nombre de groupes assignés à une table: " << maFile.GetNbGroupesAssignes() << endl
		<< "Nombre de personnes assignées à une table: " << maFile.GetNbPersonnesAssignes() << endl
		<< "Nombre de groupes présents dans la file: " << maFile.GetNbGroupes() << endl;
}
//////////////////////////////////////////////////////////////////////////////////
//	EffectuerChoix
//	Intrants: choix(int), maFile(FileAttente&), quitter(bool&)
//  Extrants: void
//	Description: Permet d'effectuer le choix choisi par l'usager
//////////////////////////////////////////////////////////////////////////////////
void EffectuerChoix(int choix, FileAttente& maFile, bool& quitter)
{
	switch (choix)
	{
	case 1: //Ajouter un client dans la file
		AjouterClient(maFile);
		break;
	case 2: //Assigner une table
		AssignerTable(maFile);
		break;
	case 3: //Retirer un client qui quitte
		ClientPart(maFile);
		break;
	case 4: //Peu importe la section
		maFile.AfficherClient(maFile);
		break;
	case 5: //Terrasse non fumeur
		maFile.Afficher(cout, maFile);
		break;
	case 6: //quitter le programme
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
	setlocale(LC_ALL, ""); // Permet d'afficher les accents à la console
	FileAttente maFile;
	// Ajouts de client pour les tests
	ClientEnAttente a("Arthur", 4, 1);
	maFile.Ajouter(a);

	ClientEnAttente b("Benoit", 6, 7);
	maFile.Ajouter(b);

	ClientEnAttente c("Charles", 2, 3);
	maFile.Ajouter(c);

	ClientEnAttente d("Diane", 3, 7);
	maFile.Ajouter(d);

	ClientEnAttente e("Elise", 4, 6);
	maFile.Ajouter(e);

	ClientEnAttente f("Francis", 2, 5);
	maFile.Ajouter(f);

	ClientEnAttente g("Gaston", 8, 4);
	maFile.Ajouter(g);

	int choix = 0; //choix du menu principale
	bool quitter = false; //bool qui permet de savoir si le choix quitter à été choisi
	try
	{
		do
		{
			AfficherMenu(); //affiche le menu principale
			cin >> choix; 
			while (cin.fail()) //boucle qui permet de gérer le cas du cin qui fail
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Entrez un choix valide : ";
				cin >> choix;
			}
			EffectuerChoix(choix,maFile,quitter); //effectu le choix entré par l'usager
		} while (!quitter); //continu de tourner dans la boulcle tant que quitté==false
		MessageQuitter(maFile); //affiche le message finale qui résume la file d'attente
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}