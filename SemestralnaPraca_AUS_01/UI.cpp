#include "UI.h"

using namespace std;
UI::UI()
{
	firma = new Firma("AoE");
	pridajVsetkyPrekladiska();
}


UI::~UI()
{
	delete firma;
}

void UI::hlavneMenu()
{
	system("cls");
	cout << "++++++++++ Vitajte v Informacnom systeme firmy " << firma->getNazovFirmy() << " ++++++++++" << endl;
	//cout << "Date: " << Datum::getAktualnyDatum() << endl;
	cout <<
		"1. Sprava Vozidiel\n" <<
		"2. Sprava Prekladísk\n" <<
		"3. Sprava Objednavok\n\n" <<
		"4. Posun hodinu\n" <<
		"5. Koniec\n" <<
		"6. Test\n\n" <<
		"7. Uloz\n" <<
		"8. Nacitaj\n" <<
		endl;

	switch (getInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 1:
		menuVozidla();
		break;
	case 2:
		menuPrekladiska();
		break;
	case 3:
		menuObjednavky();
		break;
	case 4:
		menuVozidla();
		break;
	case 5:
		break;
	case 6:
		firma->pridajVozidlo(new Vozidlo(10, 100, "ZA232DB"));
		firma->pridajVozidlo(new Vozidlo(14560, 1045550, "ZA222BA"));
		firma->vypisZoznamVozidiel();
		pridajVsetkyPrekladiska();

		//pridám jeden extra dron prekladisku v regióne 
		firma->dajPrekladiskoPodlaRegionu("MA")->pridajDron(new Dron(eDrony::JEDEN));

		firma->dajPrekladiskoPodlaRegionu("MA")->vypisZoznamDronov();
		// ↓↓ memory leak ↓↓
		//firma->vytvorObjednavku(2.75, new Odosielatel("BA", 10), new Adresat("MA", 15));

		break;
	case 7:
		menuVozidla();
		break;
	case 8:
		menuVozidla();
		break;
	}

}

int UI::getInputFromUser(std::string consoleOutput)
{
	int userInput;
	std::cout << consoleOutput << ": " << std::endl;
	std::cin >> userInput;

	return userInput;
}

void UI::pridajVsetkyPrekladiska()
{
	firma->pridajPrekladisko(new Prekladisko("MA"));
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
	firma->pridajPrekladisko(new Prekladisko("MI"));
}

void UI::menuVozidla()
{
	system("cls");
	cout << "++++++++++ Sprava Vozidiel ++++++++++" << endl;
	cout <<
		"1. Pridaj Vozidlo\n" <<
		"2. Vypis zoznam Vozidiel firmy \n" <<
		"3. Hlavne Menu" <<
		endl;

	switch (getInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 3:
		hlavneMenu();
		break;
	}
}

void UI::menuPrekladiska()
{
	system("cls");
	cout << "++++++++++ Sprava Prekladisk ++++++++++" << endl;
	cout <<
		"1. Pridaj Prekladisko\n" <<
		"2. Vypis zoznam Vozidiel firmy \n" <<
		"3. Hlavne Menu" <<
		endl;

	switch (getInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 3:
		hlavneMenu();
		break;
	}
}

void UI::menuObjednavky()
{
	system("cls");
	cout << "++++++++++ Sprava Objednavok ++++++++++" << endl;
	cout <<
		"1. Pridaj Vozidlo\n" <<
		"2. Vypis zoznam Vozidiel firmy \n" <<
		"3. Hlavne Menu" <<
		endl;

	switch (getInputFromUser("Zvolte si moznost zo zoznamu"))
	{
	case 3:
		hlavneMenu();
		break;
	}
}
