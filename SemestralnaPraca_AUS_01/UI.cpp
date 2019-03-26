#include "UI.h"

using namespace std;
UI::UI()
{
	datumUI = Datum::getInstance();
	firma = new Firma("AoE");
	pridajVsetkyPrekladiska();

	// TODO: pole okresov ? 
	//poleRegionov = new structures::Array<std::string>(23);
}

UI::~UI()
{
	delete firma;
	delete datumUI;
}

void UI::hlavneMenu()
{
	//system("cls");
	cout << "++++++++++ Vitajte v Informacnom systeme firmy " << firma->getNazovFirmy() << " ++++++++++" << endl;
	cout << "Date: " << Datum::getAktualnyDatumaCas() << endl;
	cout <<
		"1. Sprava Vozidiel" << endl <<
		"2. Sprava Prekladísk" << endl <<
		"3. Sprava Objednavok" << endl << endl <<
		"4. Posun hodinu" << endl << endl <<
		"5. Test" << endl << endl <<
		"6. Uloz" << endl <<
		"7. Nacitaj " << endl << endl <<
		"0. Koniec" << endl <<
		endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 1:
		menuVozidla(true);
		break;
	case 2:
		menuPrekladiska(true);
		break;
	case 3:
		menuObjednavky();
		break;
	case 4:
		datumUI->posunCasoHodinu(60 * 60);
		hlavneMenu();
		break;
	case 5:

		//firma->pridajVozidlo(new Vozidlo(14560, 1045550, "ZA222BA"));
		//// aj v prípade, že ho posuniem naspäť
		//datumUI->posunCasoHodinu(-60 * 60);
		firma->pridajVozidlo(new Vozidlo(10000, 100, "ZA232DB"));

		firma->vypisZoznamVozidiel();
		pridajVsetkyPrekladiska();

		//pridám jeden extra dron prekladisku v regióne 
		//firma->dajPrekladiskoPodlaRegionu("MA")->pridajDron(new Dron(eDrony::JEDEN, firma->dajPrekladiskoPodlaRegionu("MA")->set_get_SerioveCislo()));

		firma->dajPrekladiskoPodlaRegionu("MA")->vypisZoznamDronov();
		firma->getVozidloBySPZ("ZA232DB")->vypisTrasuVozidla();

		// ↓↓ memory leak ↓↓
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.5, new Odosielatel("BA", 6), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.51, new Odosielatel("BA", 6.1), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.53, new Odosielatel("BA", 6.2), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.512, new Odosielatel("BA", 6.3), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.535, new Odosielatel("BA", 6), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(1, new Odosielatel("BA", 6), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(1.25, new Odosielatel("BA", 6), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.5, new Odosielatel("BA", 6), new Adresat("MA", 15.5));
		//firma->vytvorObjednavku(2.5, new Odosielatel("BA", 18), new Adresat("MA", 15.5));
		/*firma->vypisanieVsetkychObjednavok();*/
		firma->spracujVsetkyObjednavky();

		hlavneMenu();
		break;
	case 6:
		break;
	case 7:
		break;
	case 111:
		exit(0);
	case 0:
		return;
	default:
		hlavneMenu();
		break;
	}

}

int UI::getIntInputFromUser(std::string consoleOutput)
{
	// TODO: pridaj kontrolu vstupov 
	return std::stoi(getStrInputFromUser(consoleOutput));
}
string UI::getStrInputFromUser(string consoleOutput)
{
	string userInput;
	cout << consoleOutput << ": " << endl;
	cin >> userInput;

	return userInput;
}

void UI::pridajVsetkyPrekladiska()
{
	char * regiony[23] = { "MA", "BA", "TT", "TN", "NR", "KN","PD", "LV", "CA", "MT", "BB", "ZV", "KA", "NO", "LM", "LC", "RA", "SL", "SN", "PO", "KE", "HE", "MI" };
	for each (char* region in regiony)
	{
		firma->pridajPrekladisko(new Prekladisko(region));
	}
	/*firma->pridajPrekladisko(new Prekladisko("MA"));
	firma->pridajPrekladisko(new Prekladisko("BA"));
	firma->pridajPrekladisko(new Prekladisko("TT"));
	firma->pridajPrekladisko(new Prekladisko("TN"));
	firma->pridajPrekladisko(new Prekladisko("NR"));
	firma->pridajPrekladisko(new Prekladisko("KN"));
	firma->pridajPrekladisko(new Prekladisko("PD"));
	firma->pridajPrekladisko(new Prekladisko("LV"));
	firma->pridajPrekladisko(new Prekladisko("CA"));
	firma->pridajPrekladisko(new Prekladisko("MT"));
	firma->pridajPrekladisko(new Prekladisko("BB"));
	firma->pridajPrekladisko(new Prekladisko("ZV"));
	firma->pridajPrekladisko(new Prekladisko("KA"));
	firma->pridajPrekladisko(new Prekladisko("NO"));
	firma->pridajPrekladisko(new Prekladisko("LM"));
	firma->pridajPrekladisko(new Prekladisko("LC"));
	firma->pridajPrekladisko(new Prekladisko("RA"));
	firma->pridajPrekladisko(new Prekladisko("SL"));
	firma->pridajPrekladisko(new Prekladisko("SN"));
	firma->pridajPrekladisko(new Prekladisko("PO"));
	firma->pridajPrekladisko(new Prekladisko("KE"));
	firma->pridajPrekladisko(new Prekladisko("HE"));
	firma->pridajPrekladisko(new Prekladisko("MI"));*/
}

void UI::menuVozidla(std::string text, bool clearTerminal)
{
	if (clearTerminal) { system("cls"); }
	if (text != "") {
		cout << text << endl;
	}

	cout << "++++++++++ Sprava Vozidiel ++++++++++" << endl;
	cout <<
		"1. Pridaj Vozidlo" << endl <<
		"2. Vypis zoznam Vozidiel firmy" << endl <<
		"3. Vypis trasu vozidla" << endl << endl <<
		"0. Hlavne Menu" << endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 1:
		// TODO spýtať sa na trasu ? 
		firma->pridajVozidlo(new Vozidlo(
			getIntInputFromUser("Zadaj nosnost"),
			getIntInputFromUser("Zadaj prevadzkoveNaklady"),
			getStrInputFromUser("Zadaj SPZ")));
		menuVozidla("Vozidlo bolo USPESNE pridane", true);
		break;
	case 2:
		firma->vypisZoznamVozidiel();
		menuVozidla(false);
		break;
	case 3:
		firma->getVozidloBySPZ(getStrInputFromUser("Zadaj SPZ vozidla, ktoremu chces vypiast trasu"))->vypisTrasuVozidla();
		menuVozidla(false);
		break;
	case 0:
		hlavneMenu();
		break;
	default:
		menuVozidla(true);
		break;
	}

}

void UI::menuPrekladiska(std::string text, bool clearTerminal)
{
	if (clearTerminal) { system("cls"); }
	if (text != "") {
		cout << text << endl;
	}
	cout << "++++++++++ Sprava Prekladisk ++++++++++" << endl;
	cout <<
		"1. Pridaj Dron" << endl <<
		"2. Pridaj Prekladisko" << endl <<
		"3. Vypis zoznam dronov v prekladisku" << endl << endl <<
		"0. Hlavne Menu" <<
		endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
		//case 1:
		//	firma->dajPrekladiskoPodlaRegionu(
		//		getStrInputFromUser("Zadaj skratku regionu prekladiska do ktoreho chces pridat drona"))
		//		->pridajDron(new Dron((getIntInputFromUser("Zadaj typ drona [1/2]") ? eDrony::JEDEN : eDrony::DVA)));
		//	menuPrekladiska("Dron bol uspesne pridany", true);
	case 2:
		firma->pridajPrekladisko(new Prekladisko(getStrInputFromUser("Zadaj skratku regionu prekladiska, ktore chces pridat")));
		menuPrekladiska("Prekladisko bolo uspesne pridane", true);
		break;
	case 3:
		firma->dajPrekladiskoPodlaRegionu(
			getStrInputFromUser("Zadaj skratku regionu prekladiska z ktoreho chces vypisat drony"))->vypisZoznamDronov();
		menuPrekladiska(false);
		break;
	case 0:
		hlavneMenu();
		break;
	default:
		menuPrekladiska(true);
		break;
	}
}

void UI::menuObjednavky()
{
	system("cls");
	cout << "++++++++++ Sprava Objednavok ++++++++++" << endl;
	cout <<
		"1. Vytvor OBjednavku" << endl <<
		"2. Vypis zoznam vsetkych objednavok Firmy" << endl <<
		"2. Vypis zoznam vsetkych objednavok v Prekladisku" << endl << endl <<
		"0. Hlavne Menu" <<
		endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 0:
		hlavneMenu();
		break;
	case 2:
		firma->vypisanieVsetkychObjednavok();
		system("pause");
		break;
	default:
		menuObjednavky();
		break;
	}

}
