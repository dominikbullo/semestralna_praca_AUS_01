#include <fstream>
#include "UI.h"

using namespace std;
UI::UI()
{
	running = true;
	datumUI = Datum::getInstance();
	//datumUI->posunCas(-2 * 60 * 60);
	firma = new Firma("AoE");
	pridajVsetkyPrekladiska();
}

UI::~UI()
{
	delete firma;
	delete datumUI;
}

void UI::hlavneMenu()
{
	std::ofstream out;
	std::ifstream in;


	while (running) {
		cout << "++++++++++ Vitajte v Informacnom systeme firmy " << firma->getNazovFirmy() << " ++++++++++" << endl;
		cout << "Aktualny datum: " << Datum::getAktualnyDatumaCas() << endl;
		cout <<
			"1. Sprava vozidiel" << endl <<
			"2. Sprava prekladisk" << endl <<
			"3. Sprava objednavok" << endl <<
			"4. Sumarne statistiky" << endl << endl <<

			"5. Test" << endl << endl <<

			"6. Vypis aktualny cas" << endl <<
			"7. Posun hodinu" << endl << endl <<


			"8. Uloz" << endl <<
			"9. Nacitaj " << endl << endl <<

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
			menuObjednavky("", true);
			break;
		case 4:
			menuStatistiky("", true);
			break;
		case 5:
			//firma->pridajVozidlo(new Vozidlo(14560, 1045550, "ZA222BA"));
			firma->pridajVozidlo(new Vozidlo(3500, 10, "ZA232DB"));
			//firma->pridajVozidlo(new Vozidlo(10000, 10, "ZA214DB"));
			firma->vypisZoznamVozidiel();

			//pridám jeden extra dron prekladisku v regióne 
			//firma->dajPrekladiskoPodlaRegionu("MA")->pridajDron(new Dron(eDrony::JEDEN, firma->dajPrekladiskoPodlaRegionu("MA")->set_get_SerioveCislo()));

			//firma->dajPrekladiskoPodlaRegionu("MA")->vypisZoznamDronov();
			firma->getVozidloBySPZ("ZA232DB")->vypisTrasuVozidla();

			firma->vytvorObjednavku(2.75, new Odosielatel("BA", 2), new Adresat("MA", 15.5));
			//datumUI->posunCas(60 * 60);
			firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
			firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15.5));
			firma->vytvorObjednavku(4, new Odosielatel("BA", 10), new Adresat("MA", 15.5));


			ukonciDen();
			ulozVsetko(out);
			break;
		case 6:
			cout << "Aktualny cas: " << Datum::getAktualnyDatumaCas() << endl;
			break;
		case 7:
			datumUI->posunCas(60 * 60);
			firma->spracujVsetkyObjednavky();
			break;
		case 8:
			ulozVsetko(out);
			break;
		case 9:
			system("cls");
			in.open("ulozenie");
			in >> *firma;
			in.close();

			cout << "****************************" << endl;
			cout << "Vsetko bolo uspesne nacitane" << endl;
			cout << "****************************" << endl;

			break;
		case 111:
			running = false;
			exit(0);
		case 0:
			running = false;
			cout << "Dovidenia." << endl;
			break;
		default:
			system("cls");
			cout << "Nespravna volba. " << endl;

		}
	}
}

void UI::ulozVsetko(std::ofstream &out)
{
	out.open("ulozenie");
	out << *firma;
	out.close();
}

void UI::ukonciDen()
{
	Datum::posunCasNaUrcituHodinu(eOtvoracieHodiny::ZATVORENE);
	firma->vratVozidlaDoCentralnehoSkladu();

	firma->getCentralnySklad()->vypisZoznamZasielok();
	firma->naplnVozidla();

	// TODO prekladisko prime zasielky
	//for (Vozidlo* vozidlo : firma..)
	//prekladsiko->prijmiZasielky(arrayListZasielok)
	//firma->vylozZasielkyvPrekladiskach();
}

int UI::getIntInputFromUser(std::string consoleOutput)
{
	cout << consoleOutput << ": " << endl;
	int pom;
	cin >> pom;
	while (!cin)
	{
		cout << "Nespravna volba. Zadajte volbu: " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');;
		cin >> pom;
	}
	return pom;
}

string UI::getStrInputFromUser(string consoleOutput)
{
	string userInput;
	cout << consoleOutput << ": " << endl;
	cin >> userInput;

	return userInput;
}
string UI::getDateFromUser(string consoleOutput)
{
	struct tm when = { 0 };

	cout << consoleOutput << ": " << endl;
	when.tm_mday = getIntInputFromUser("Zadaj den");
	when.tm_mon = getIntInputFromUser("Zadaj mesiac") - 1;
	when.tm_year = getIntInputFromUser("Zadaj rok") - 1900;
	//auto test = mktime(&when);

	return Datum::time_t_to_string(mktime(&when));
}

void UI::pridajVsetkyPrekladiska()
{
	char * regiony[23] = { "MA", "BA", "TT", "TN", "NR", "KN","PD", "LV", "CA", "MT", "BB", "ZV", "KA", "NO", "LM", "LC", "RA", "SL", "SN", "PO", "KE", "HE", "MI" };
	for each (char* region in regiony)
	{
		firma->pridajPrekladisko(new Prekladisko(region));
	}
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
		"1. Pridaj prekladisko" << endl <<
		"2. Pridaj dron do lokalneho prekladiska" << endl <<
		"3. Vypis zoznam dronov v prekladisku" << endl << endl <<
		"0. Hlavne Menu" <<
		endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{

	case 1:
		firma->pridajPrekladisko(new Prekladisko(getStrInputFromUser("Zadaj skratku regionu prekladiska, ktore chces pridat")));
		menuPrekladiska("Prekladisko bolo uspesne pridane", true);
		break;
	case 2:
	{
		Prekladisko* prekladisko = firma->dajPrekladiskoPodlaRegionu(getStrInputFromUser("Zadaj skratku regionu prekladiska do ktoreho chces pridat drona"));
		Dron * dron = new Dron(getIntInputFromUser("Zadaj typ drona [1/2]") ? eDrony::JEDEN : eDrony::DVA, prekladisko->set_get_SerioveCislo());
		menuPrekladiska("Dron bol uspesne pridany", true);
	}
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

void UI::menuStatistiky(std::string text, bool clearTerminal)
{
	if (clearTerminal) { system("cls"); }
	if (text != "") {
		cout << text << endl;
	}
	cout << "++++++++++ Sprava Prekladisk ++++++++++" << endl;
	cout <<
		"1. Vyhladaj region, do ktoreho bolo v danom casovom obdobi dorucenych najviac objednavok." << endl <<
		"2. Vyhladaj region, z ktoreho bolo v danom casovom obdobi odoslanych najviac objednavok " << endl <<
		"3. Vypisanie vsetkych zasielok v danom regione s dovodom zamietnutia " << endl <<
		"4. Vypisanie poctu zrusenych objednavok za dane casove obdobie v jednotlivych regionoch " << endl <<
		"5. Vypisanie celkoveho poctu dorucenych zasielok " << endl <<
		"6. Vypisanie celkoveho poctu najazdenych kilometrov vsetkych vozidiel " << endl <<
		"7. Vypisanie celkoveho poctu nalietanych hodin jednotlivych typov dronov v jednotlivych regionoch " << endl << endl <<

		"0. Hlavne Menu" << endl;

	string datumOd;
	string datumDo;
	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 1:
		system("cls");
		datumOd = getDateFromUser("Zadaj datum od");
		datumDo = getDateFromUser("Zadaj datum do");
		firma->getRegionsNajvacsimPoctomDorucenychObjednavok(datumOd, datumDo);
		//firma->getRegionsNajvacsimPoctomDorucenychObjednavok(getDateFromUser("Zadaj datum od"), getDateFromUser("Zadaj datum do"));
		menuStatistiky("", false);
		break;
	case 2:
	{
		system("cls");
		datumOd = getDateFromUser("Zadaj datum od");
		datumDo = getDateFromUser("Zadaj datum do");
		firma->getRegionsNajvacsimPoctomPrijatychObjednavok(datumOd, datumDo);
		menuStatistiky("", false);
		break;
	}
	case 3:
	{
		system("cls");
		string region = getStrInputFromUser("Zadaj region z ktoreho chces vypisat zasielky");
		datumOd = getDateFromUser("Zadaj datum od");
		datumDo = getDateFromUser("Zadaj datum do");
		firma->vypisZasielkySDovodomZamietnutia(datumOd, datumDo, region);
		menuStatistiky("", false);
		break;
	}
	case 4:
		system("cls");
		datumOd = getDateFromUser("Zadaj datum od");
		datumDo = getDateFromUser("Zadaj datum do");
		firma->vypisaniePoctuZrusenychObjednavok(datumOd, datumDo);
		menuStatistiky("", false);
		break;
	case 5:
		system("cls");
		firma->vypisanieCelkovehoPoctuDorucenychZasielok();
		menuStatistiky("", false);
		break;
	case 6:
		system("cls");
		firma->vypisaniePoctuKilometrovVsetkychVozidiel();
		menuStatistiky("", false);
		break;
	case 7:
		system("cls");
		firma->vypisaniePoctuHodinPodlaTypuDrona();
		menuStatistiky("", false);
		break;
	case 0:
		system("cls");
		hlavneMenu();
		break;
	default:
		menuStatistiky("Bola zadana neplatna volba", true);
		break;
	}
}

void UI::menuObjednavky(std::string text, bool clearTerminal)
{
	if (clearTerminal) { system("cls"); }
	if (text != "") {
		cout << text << endl;
	}
	cout << "++++++++++ Sprava Objednavok ++++++++++" << endl;
	cout <<
		"1. Vytvor objednavku" << endl <<
		"2. Vypis zoznam vsetkych objednavok firmy" << endl <<
		"2. Vypis zoznam vsetkych objednavok v lokalnom prekladisku" << endl << endl <<

		"0. Hlavne Menu" << endl;

	switch (getIntInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 0:
		hlavneMenu();
		break;
	case 2:
		firma->vypisanieVsetkychObjednavok();
		menuObjednavky("", false);
		break;
	default:
		menuObjednavky("Bola zadana neplatna volba", true);
		break;
	}

}
