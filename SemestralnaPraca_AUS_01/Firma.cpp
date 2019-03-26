#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

using namespace std;
Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();

	// kvÙli ötatistik·m -> koæko zamietnut˝ch, koæko v kraji a pod.
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
	// vozidlo prid·vam vûdy na koniec, t˝m p·dom viem, ûe vozidl· s˙ zoradenÈ podæa poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		// FIXED zaraÔovanie podæa d·tumu aj Ëasu
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
	// zloûitosù O(n)

	// NOTE osetrenie zlÈho vstupu
	//for (auto & c : region) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		if (prekladisko->dajRegion() == region) {
			return prekladisko;
		}
	}
	cout << "Prekladisko v tomto okrese sa nenaslo" << endl;
	return NULL;
}

// TODO 5:Pri vytv·ranÌ objedn·vky je nutnÈ kontrolovaù, Ëi nedÙjde k jej zamietnutiu zo strany
// AoE.DokonËen· objedn·vka je zaraden· do frontu objedn·vok Ëakaj˙cich na spracovanie.
// TODO //	e) prijatie z·sielky v lok·lnom prekladisku odosielateæa by spÙsobilo, ûe toto lok·lne
		//	prekladisko nedok·ûe doruËiù niektorÈ z·sielky, ktor˝ch adres·ti sa nach·dzaj˙ v jeho
		//	regiÛne, do 18:00 danÈho dÚa.

Vozidlo* Firma::vyberVozidlo(double hmotnostZasielky, Prekladisko* prekladiskoNaPrevzatieZasielky) {
	// TODO pozeraj eöte dopredu an napl·novanÈ z·sielky toho vozidla 
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

// TODO: Vöetko
void Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// vytvorÌm
	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);
	//zaevidujem do firmy
	this->linkedListObjednavok->add(objednavka);

	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());


	// zistÌm drona z tohto prekladiska, Ëi m·m nejakÈho drona, ktor˝ stihne, unesie a je nabit˝ 
	// TODO vyber drona ak nie je voæn˝ -> zisti Ëas, kedy mÙûe
	Dron* dronPreOdosielatela = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska(), objednavka->getDatumaCasVytvorenia());


	// zistÌm Ëi mi do prekladiska prÌde auto ktorÈ bude maù nosnoù tak˙, ûe zvl·dne odniest objednavku
	Vozidlo* vozidloPreOdosielatela = this->vyberVozidlo(hmotnostZasielky, prekladiskoOdoslania);

	// TODO: ADRESAT
	Prekladisko* prekladiskoAdresata = this->dajPrekladiskoPodlaRegionu(adresat->getRegion());
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(hmotnostZasielky, prekladiskoAdresata);
	// FIXME toto sa ale p˝taj aû neskÙr, resp na nejak˝ Ëas, kedy tam dan· objedn·vka bude 
	// Dron* dronPreAdresata = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, adresat->getVzdialenostOdPrekladiska());

	//if (dronPreOdosielatela == NULL ||
	// TODO
	if (dronPreOdosielatela == NULL ||
		vozidloPreOdosielatela == NULL ||
		vozidloPreAdresata == NULL)
	{
		objednavka->setStav(eStavObjednavky::ZAMIETNUTA);
	}
	else
	{
		if (dronPreOdosielatela->vytazenyDo() > Datum::time_t_to_string(Datum::string_to_time_t(Datum::getAktualnyDatumaCas()) + 60 * 60)) {
			// TODO if setDatumaCasSpracovania_ > 1 hodina -> moûnosù zruöenia ;
			if (chceUserZrusitObjednavku(dronPreOdosielatela, objednavka)) { return; }
		}
		std::cout << "Predpokladany cas priletu dronu je " << std::endl;
		objednavka->setStav(eStavObjednavky::PRIJATA);
		objednavka->setDatumaCasSpracovania_(dronPreOdosielatela->vytazenyDo());
		dronPreOdosielatela->pridajObjednavku(objednavka);




		vozidloPreOdosielatela->pridajZasielku(objednavka->getHmotnostZasielky());
		// pridaù ?
		//prekladiskoAdresata->pridajObjednavku(objednavka);
	}
}

bool Firma::chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Objednavka * objednavka)
{
	int userInput;
	cout << "Vasu zasielku mÙzeme spracovat o viac ako hodinu a to konkretne " <<
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

