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
	cout << "++++++++++ Vytajte v Informacnom systeme firmy " << firma->getNazovFirmy() << "++++++++++" << endl;
	//cout << "Date: " << Datum::getAktualnyDatum() << endl;
	cout <<
		"1. Sprava Vozidiel\n" <<
		"2. Sprava Prekladísk\n" <<
		"4. Objednavky\n\n" <<
		"6. Posun hodinu\n" <<
		"7. Koniec\n" <<
		"8. Test\n\n" <<
		"9. Uloz\n" <<
		"10. Nacitaj\n" <<
		endl;

	getInputFromUser("Zvolte si moznost zo zoznamu");
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
