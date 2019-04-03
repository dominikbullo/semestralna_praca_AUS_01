#include "Firma.h"

bool first = true;
using namespace std;
Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	centralnySklad_ = new CentralnySklad();

	arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();
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

	delete centralnySklad_;
}


void Firma::vypisanieVsetkychObjednavok()
{
	for (Objednavka * var : *linkedListObjednavok) { var->toString(); }
}


void  Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	if (first) {
		pridajVsetkyRegionyDoTrasyVozidla(noveVozidlo);
		first = false;
	}
	else {
		pridajRegionyDoTrasyVozidla(noveVozidlo);
	}

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
		//// NOTE: for testing!!
		//if (prekladisko->dajRegion() == "BA") { continue; }
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
	time_t aktualnyCas = Datum::getAktualnyDatumaCasAsTime();
	tm *ltm = localtime(&aktualnyCas);
	struct tm uzatvorenieFirmy = *ltm;
	uzatvorenieFirmy.tm_hour = (int)eOtvoracieHodiny::ZATVORENE;
	uzatvorenieFirmy.tm_min = 00;

	if (mktime(&uzatvorenieFirmy) <= Datum::getAktualnyDatumaCasAsTime())
	{
		this->spracujVsetkyObjednavky();

		for (Vozidlo *vozidlo : *arrayListVozidiel)
		{
			vozidlo->aktualizujCelkoveNaklady();
			this->centralnySklad_->prijmiZasielky(vozidlo);
		}
	}
	else {
		std::cout << "Firma je este otvorena. Nemozno vratit vozidla do centralneho skladu" << std::endl;
	}
}


Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string region) {

	// NOTE osetrenie zlého vstupu
	//for (auto & c : region) c = toupper(c);
	std::transform(region.begin(), region.end(), region.begin(), ::toupper);

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
	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);
	this->linkedListObjednavok->add(objednavka);

	Zasielka * zasielka = new Zasielka(objednavka);

	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());

	Vozidlo* vozidloNaVyzdvihnutie = this->vyberVozidlo(zasielka);
	if (vozidloNaVyzdvihnutie == NULL)
	{
		objednavka->zamietniObjednavku("Vozidlo ktore bude prechadzat prekladiskom odosielatela sa nenaslo");
		delete zasielka;
		return;
	}
	Dron* vhodnyDron = prekladiskoOdoslania->vyberDrona(zasielka);
	if (vhodnyDron == NULL)
	{
		objednavka->zamietniObjednavku("Nenašiel sa vhodny dron");
		delete zasielka;
		return;
	}
	// preaženým metódy sa pýtam nie na prekladisko, ktoré mu bolo priradené, ale na prekladisko k adresátovi
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(zasielka, this->dajPrekladiskoPodlaRegionu(adresat->getRegion()));
	if (vozidloPreAdresata == NULL)
	{
		objednavka->zamietniObjednavku("Vozidlo ktore bude prechadzat prekladiskom adresata sa nenaslo");
		delete zasielka;
		return;
	}
	string test = Datum::time_t_to_string(vhodnyDron->casPriletuPreZasielku(zasielka));
	if (vhodnyDron->casPriletuPreZasielku(zasielka) > Datum::getAktualnyDatumaCasAsTime() + 60 * 60) {
		if (chceUserZrusitObjednavku(vhodnyDron, zasielka)) {
			objednavka->setStav(eStavObjednavky::ZRUSENA);
			delete zasielka;
			return;
		}
	}

	zasielka->setDatumaCasSpracovania(vhodnyDron->vytazenyDo());
	zasielka->setdatumaCasPrevzatia(Datum::time_t_to_string(vhodnyDron->casPriletuPreZasielku(zasielka)));

	objednavka->setStav(eStavObjednavky::PRIJATA);
	objednavka->setDatumaCasSpracovania(zasielka->getDatumaCasSpracovania());

	vhodnyDron->pridajZasielku(zasielka);
	vozidloNaVyzdvihnutie->pridajZasielku(zasielka);
	//vhodnyDron->toString();
}
bool Firma::chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Zasielka * zasielka)
{
	int userInput;
	cout << "Vasu zasielku mozeme spracovat o viac ako hodinu a to konkretne " <<
		Datum::time_t_to_string(dronPreOdosielatela->casPriletuPreZasielku(zasielka)) << endl <<
		"Prajete si zasielku zrusit?" << endl;
	cout << "1. ANO" << endl << "2. NIE" << endl;
	cin >> userInput;
	return (userInput == 1);
}

void Firma::getRegionsNajvacsimPoctomDorucenychObjednavok(std::string datumOd, std::string datumDo)
{
	//string region = "";
	for (Objednavka * objednavka : *this->linkedListObjednavok) {
		string region = objednavka->getAdresat()->getRegion();
	}
}
void Firma::getRegionsNajvacsimPoctomPrijatychObjednavok(std::string datumOd, std::string datumDo)
{
	// TODO  date_range_check;
	throw std::exception("Not implemented yet!");

}
void Firma::vypisZasielkySDovodomZamietnutia(std::string datumOd, std::string datumDo, std::string region)
{
	int pocet = 0;
	for (Objednavka * objednavka : *this->linkedListObjednavok) {
		// zamietnuté -> nie zrušené
		if (objednavka->getStav() == eStavObjednavky::ZAMIETNUTA &&
			objednavka->getOdosielatel()->getRegion() == region &&
			Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia()) >= Datum::string_to_time_t(datumOd) &&
			Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia()) <= Datum::string_to_time_t(datumDo))
		{
			pocet++;
			objednavka->toString();
		}
	}
	if (pocet == 0)
	{
		system("cls");
		cout << "Ziadna objednavka nebola v regione " << region << " zrusena v tento datum" << endl;
	}
}

void Firma::vypisaniePoctuZrusenychObjednavok(std::string datumOd, std::string datumDo)
{
	Prekladisko* prekladisko = NULL;
	int pocet = 0;
	int max = 0;

}
void Firma::vypisanieCelkovehoPoctuDorucenychZasielok()
{
	int pocet = 0;
	for (Objednavka * objednavka : *this->linkedListObjednavok) {
		if (objednavka->getStav() == eStavObjednavky::DORUCENA)
		{
			pocet++;
		}
	}
	cout << "Pocet dorucenych zasielok je " << pocet << endl;
}
void Firma::vypisaniePoctuKilometrovVsetkychVozidiel()
{
	double pocetKm = 0;
	for (Vozidlo *voz : *arrayListVozidiel)
	{
		pocetKm += voz->getPocetNajazdenychKm();
		cout << "Vozidlo -> " << voz->getSPZ() << endl;
		cout << "Pocet najazdenych km: " << voz->getPocetNajazdenychKm() << endl;
	}
	cout << "Celkovy pocet kilometrov vsetkych vozidiel je " << pocetKm << endl;
}
void Firma::vypisaniePoctuKilometrovPodlaTypuDrona()
{
}
ostream& operator<< (ostream& os, Firma& firma) {

	os << firma.nazovFirmy_ << "\n";

	// Najskôr prekladiska firmy
	os << firma.arrayListPrekladisk->size() << "\n";

	for (Prekladisko * var : *firma.arrayListPrekladisk) {
		os << *var;
	}

	os << firma.arrayListVozidiel->size() << "\n";

	for (Vozidlo * var : *firma.arrayListVozidiel) {
		os << *var;
	}

	os << "Size objednavok: " << firma.linkedListObjednavok->size() << "\n";

	for (Objednavka * var : *firma.linkedListObjednavok) {
		os << *var;
	}

	return os;
}
istream& operator>> (istream& is, Firma& firma) {
	double maxNosnost, nosnost, prevadzkoveNaklady, pocetRegionovTrasy;
	std::string SPZ, region;

	is >> firma.nazovFirmy_;

	int pocetPrekladisk = 0;
	is >> pocetPrekladisk;

	for (size_t i = 0; i < pocetPrekladisk; i++)
	{
		is >> region;
		Prekladisko * nacitanePrekladisko = new Prekladisko(region);
		is >> *nacitanePrekladisko;
		firma.arrayListPrekladisk->add(nacitanePrekladisko);
	}



	int pocetVozidiel = 0;
	is >> pocetVozidiel;

	for (size_t i = 0; i < pocetVozidiel; i++)
	{
		is >> nosnost >> prevadzkoveNaklady >> SPZ;
		Vozidlo * nacitaneVozidlo = new Vozidlo(nosnost, prevadzkoveNaklady, SPZ);
		is >> *nacitaneVozidlo;

		is >> pocetRegionovTrasy;
		for (size_t i = 0; i < pocetRegionovTrasy; i++)
		{
			is >> region;

		}
		firma.arrayListVozidiel->add(nacitaneVozidlo);
	}
	return is;
}
