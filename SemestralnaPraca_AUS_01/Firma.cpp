#include "Firma.h"

bool testingProgram = true;
using namespace std;
Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();

	// kvôli štatistikám -> ko¾ko zamietnutých, ko¾ko v kraji a pod.
	linkedListObjednavok = new structures::LinkedList<Objednavka*>();
}

Firma::~Firma()
{
	// treba premazat vsetky objekty ktore som kam naplnil
	for (Objednavka * objednavka : *linkedListObjednavok) {
		delete objednavka;
	}
	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		delete prekladisko;
	}
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		delete vozidlo;
	}
	delete arrayListVozidiel;
	delete arrayListPrekladisk;
	delete linkedListObjednavok;
}


void Firma::vypisanieVsetkychObjednavok()
{
	for (Objednavka * var : *linkedListObjednavok) { var->toString(); }
}


void  Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	if (testingProgram) { pridajVsetkyRegionyDoTrasyVozidla(noveVozidlo); }
	else { pridajRegionyDoTrasyVozidla(noveVozidlo); }

	// vozidlo pridávam vždy na koniec, tým pádom viem, že vozidlá sú zoradené pod¾a poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		// FIXED zaraïovanie pod¾a dátumu aj èasu
		if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
			arrayListVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayListVozidiel->add(noveVozidlo);

}
void Firma::pridajVsetkyRegionyDoTrasyVozidla(Vozidlo* vozidlo)
{
	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		vozidlo->pridajPrekladiskoDoTrasyVozidla(prekladisko);
	}
}
void Firma::pridajRegionyDoTrasyVozidla(Vozidlo* vozidlo) {
	string userInput;
	while (userInput != "0") {
		cout << "Ktory region chces pridat do trasy vozidla - " << vozidlo->getSPZ() << " " << endl;
		cin >> userInput;
		if (userInput != "0") {
			vozidlo->pridajPrekladiskoDoTrasyVozidla(this->dajPrekladiskoPodlaRegionu(userInput));
		}
	}
	return;
}

void Firma::vratVozidlaDoCentralnehoSkladu()
{
	this->spracujVsetkyObjednavky();
}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string region) {
	// zložitos O(n)

	// NOTE osetrenie zlého vstupu
	//for (auto & c : region) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		if (prekladisko->dajRegion() == region) {
			return prekladisko;
		}
	}
	cout << "Prekladisko v tomto okrese sa nenaslo" << endl;
	return NULL;
}
Vozidlo* Firma::vyberVozidlo(Zasielka* zasielka)
{	// zistím èi mi do prekladiska príde auto ktoré bude ma nosno takú, že zvládne odniest objednavku
	return this->vyberVozidlo(zasielka, this->dajPrekladiskoPodlaRegionu(zasielka->getRegion()));
}

Vozidlo* Firma::vyberVozidlo(Zasielka* zasielka, Prekladisko * prekladisko) {
	// TODO pozeraj ešte dopredu an naplánované zásielky toho vozidla 
	for (Vozidlo * vozidlo : *arrayListVozidiel) {
		if (vozidlo->prechadzaPrekladiskom(prekladisko) &&
			vozidlo->dokazeNalozitZasielku(zasielka))
		{
			return vozidlo;
		}
	}
	cout << "Vyhovujuce vozidlo sa nenaslo" << endl;
	return NULL;
}

void Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// vytvorím objednávku a zaevidujem do firmy
	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);
	this->linkedListObjednavok->add(objednavka);

	// MEMORY LEAK POZOR NA TO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Zasielka * zasielka = new Zasielka(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska(), odosielatel->getRegion());

	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());
	Dron* vhodnyDron = prekladiskoOdoslania->vyberDrona(zasielka);
	Vozidlo* vozidloNaVyzdvihnutie = this->vyberVozidlo(zasielka);

	// preaženým metódy sa pýtam nie na prekladisko, ktoré mu bolo priradené, ale na prekladisko k adresátovi
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(zasielka, this->dajPrekladiskoPodlaRegionu(adresat->getRegion()));

	if (vhodnyDron == NULL ||
		vozidloNaVyzdvihnutie == NULL ||
		vozidloPreAdresata == NULL)
	{
		objednavka->setStav(eStavObjednavky::ZAMIETNUTA);
	}
	else
	{	// TODO stihne dorucit zasielku a spýtam sa na hodinu dopredu, nie na 20:00
		if (vhodnyDron->vytazenyDo() > Datum::time_t_to_string(Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + 60 * 60)) {
			if (chceUserZrusitObjednavku(vhodnyDron, objednavka)) {
				return;
			}
		}
		objednavka->setStav(eStavObjednavky::PRIJATA);

		zasielka->setDatumaCasSpracovania_(vhodnyDron->vytazenyDo());
		vhodnyDron->pridajZasielku(zasielka);

		//objednavka->toString();
		zasielka->toString();

		vozidloNaVyzdvihnutie->pridajZasielku(zasielka);
	}
}

bool Firma::chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Objednavka * objednavka)
{
	int userInput;
	cout << "Vasu zasielku môzeme spracovat o viac ako hodinu a to konkretne " <<
		dronPreOdosielatela->vytazenyDo() << endl <<
		"Prajete si zasielku zrusit?" << endl;
	cout <<
		"1. ANO" << endl <<
		"2. NIE" << endl;
	cin >> userInput;
	if (userInput == 1) {
		objednavka->setStav(eStavObjednavky::ZRUSENA);
		cout << "Vasa objednavka bola zrusena" << endl;
		return true;
	}
	return false;
}

