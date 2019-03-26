#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

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
	for (Objednavka * var : *linkedListObjednavok) {
		var->toString();
	}
}

void  Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	pridajRegionyDoTrasyVozidla(noveVozidlo);
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

// TODO 5:Pri vytváraní objednávky je nutné kontrolova, èi nedôjde k jej zamietnutiu zo strany
// AoE.Dokonèená objednávka je zaradená do frontu objednávok èakajúcich na spracovanie.
// TODO //	e) prijatie zásielky v lokálnom prekladisku odosielate¾a by spôsobilo, že toto lokálne
		//	prekladisko nedokáže doruèi niektoré zásielky, ktorých adresáti sa nachádzajú v jeho
		//	regióne, do 18:00 daného dòa.

Vozidlo* Firma::vyberVozidlo(double hmotnostZasielky, Prekladisko* prekladiskoNaPrevzatieZasielky) {
	// TODO pozeraj ešte dopredu an naplánované zásielky toho vozidla 
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		if (vozidlo->prechadzaPrekladiskom(prekladiskoNaPrevzatieZasielky) &&
			vozidlo->dokazeNalozitZasielku(hmotnostZasielky))
		{
			return vozidlo;
		}
	}
	cout << "Vyhovujuce vozidlo sa nenaslo" << endl;
	return NULL;
}

// TODO: Všetko
void Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// vytvorím
	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);
	//zaevidujem do firmy
	this->linkedListObjednavok->add(objednavka);

	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());


	// zistím drona z tohto prekladiska, èi mám nejakého drona, ktorý stihne, unesie a je nabitý 
	// TODO vyber drona ak nie je vo¾ný -> zisti èas, kedy môže
	Dron* dronPreOdosielatela = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska(), objednavka->getDatumaCasVytvorenia());


	// zistím èi mi do prekladiska príde auto ktoré bude ma nosno takú, že zvládne odniest objednavku
	Vozidlo* vozidloPreOdosielatela = this->vyberVozidlo(hmotnostZasielky, prekladiskoOdoslania);

	// TODO: ADRESAT
	Prekladisko* prekladiskoAdresata = this->dajPrekladiskoPodlaRegionu(adresat->getRegion());
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(hmotnostZasielky, prekladiskoAdresata);
	// FIXME toto sa ale pýtaj až neskôr, resp na nejaký èas, kedy tam daná objednávka bude 

	if (dronPreOdosielatela == NULL ||
		vozidloPreOdosielatela == NULL ||
		vozidloPreAdresata == NULL)
	{
		objednavka->setStav(eStavObjednavky::ZAMIETNUTA);
	}
	else
	{
		if (dronPreOdosielatela->vytazenyDo() > Datum::time_t_to_string(Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + 60 * 60)) {
			if (chceUserZrusitObjednavku(dronPreOdosielatela, objednavka)) { return; }
		}
		objednavka->setStav(eStavObjednavky::PRIJATA);
		objednavka->setDatumaCasSpracovania_(dronPreOdosielatela->vytazenyDo());
		dronPreOdosielatela->pridajObjednavku(objednavka);

		dronPreOdosielatela->toString();
		objednavka->toString();


		vozidloPreOdosielatela->pridajZasielku(objednavka->getHmotnostZasielky());
		// prida ?
		//prekladiskoAdresata->pridajObjednavku(objednavka);
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

