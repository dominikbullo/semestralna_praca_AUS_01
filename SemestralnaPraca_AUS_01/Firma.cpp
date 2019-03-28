#include "Firma.h"

bool testingProgram = true;
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
	this->spracujVsetkyObjednavky();

	for (Vozidlo *vozidlo : *arrayListVozidiel)
	{
		vozidlo->aktualizujCelkoveNaklady();
		vozidlo->toString();
		this->centralnySklad_->prijmiZasielky(vozidlo);
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
		return;
	}
	Dron* vhodnyDron = prekladiskoOdoslania->vyberDrona(zasielka);
	if (vhodnyDron == NULL)
	{
		objednavka->zamietniObjednavku("Nenašiel sa vhodny dron");
		return;
	}
	// preaženým metódy sa pýtam nie na prekladisko, ktoré mu bolo priradené, ale na prekladisko k adresátovi
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(zasielka, this->dajPrekladiskoPodlaRegionu(adresat->getRegion()));
	if (vozidloPreAdresata == NULL)
	{
		objednavka->zamietniObjednavku("Vozidlo ktore bude prechadzat prekladiskom adresata sa nenaslo");
		return;
	}

	if (vhodnyDron->casPriletuPreZasielku(zasielka) > Datum::getAktualnyDatumaCasAsTime() + 60 * 60) {
		if (chceUserZrusitObjednavku(vhodnyDron, zasielka)) {
			objednavka->setStav(eStavObjednavky::ZRUSENA);
			cout << "Vasa objednavka bola zrusena" << endl;
			return;
		}
	}
	vhodnyDron->toString();

	zasielka->setDatumaCasSpracovania(vhodnyDron->vytazenyDo());
	zasielka->setdatumaCasPrevzatia(Datum::time_t_to_string(vhodnyDron->casPriletuPreZasielku(zasielka)));

	objednavka->setStav(eStavObjednavky::PRIJATA);
	objednavka->setDatumaCasSpracovania(zasielka->getDatumaCasSpracovania());

	vhodnyDron->pridajZasielku(zasielka);
	vozidloNaVyzdvihnutie->pridajZasielku(zasielka);

	//zasielka->toString();
}
bool Firma::chceUserZrusitObjednavku(Dron * dronPreOdosielatela, Zasielka * zasielka)
{
	int userInput;
	cout << "Vasu zasielku môzeme spracovat o viac ako hodinu a to konkretne " <<
		Datum::time_t_to_string(dronPreOdosielatela->casPriletuPreZasielku(zasielka)) << endl <<
		"Prajete si zasielku zrusit?" << endl;
	cout << "1. ANO" << endl << "2. NIE" << endl;
	cin >> userInput;
	return (userInput == 1);
}

ostream& operator<< (ostream& os, Firma& firma) {
	// potrebujem 
	//nazovFirmy_ = nazovFirmy;
	//centralnySklad_ = new CentralnySklad();

	//arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	//arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();
	//linkedListObjednavok = new structures::LinkedList<Objednavka*>();

	int pocetVozidiel = firma.arrayListVozidiel->size();
	os << pocetVozidiel << " ";
	for (Vozidlo * var : *firma.arrayListVozidiel) {
		os << *var;
	}

	//int pocetVoz = firma.arrayVozidiel->size();
	//os << pocetVoz << " ";
	//for (evidenciaVozidla * voz : *firma.arrayVozidiel) {
	//	os << (int)voz->getVozidlo().getTyp() << " ";
	//	os << voz->getVozidlo().getPrevazdkoveNaklady() << " ";
	//	os << voz->getVozidlo().getSPZ() << " ";
	//	os << voz->getVozidlo().getNaklady() << " ";
	//	os << voz->getDatum() << "\n";
	//}
	//int pocetZak = firma.linkListZakaznikov->size();
	//os << pocetZak << " ";
	//for (Zakaznik * zak : *firma.linkListZakaznikov)
	//{
	//	os << zak->getMeno() << " " << zak->getAdresa() << "\n";
	//}
	//int pocetObj = firma.linkListObjednavok->size();
	//os << pocetObj << " ";
	//for (evidenciaObjednavky * obj : *firma.linkListObjednavok) {
	//	os << *obj;
	//}
	//os << firma.pocetMraziacichAut_ << " " << firma.pocetLupienkovychAut_ << " " << firma.kapacitaMraziarenskych_ << " " <<
	//	firma.kapacitaLupienkovych_ << " " << firma.skladZemiakov_ << " " << firma.skladOleja_ << " " << firma.skladOchu_ << "\n";

	return os;
}
istream& operator>> (istream& is, Firma& firma) {
	/*int pocetFarm = 0;
	is >> pocetFarm;
	for (size_t i = 0; i < pocetFarm; i++)
	{
		Biofarmar * test = new Biofarmar("", true, true, true);
		is >> *test;
		firma.arrayBiofarmarov->add(test);
	}
	int pocetVoz = 0;
	is >> pocetVoz;
	for (size_t i = 0; i < pocetVoz; i++)
	{
		int pomocna = 0;
		string spz = "";
		string datumEv = "";
		is >> pomocna;
		evidenciaVozidla * pom = new evidenciaVozidla(new Vozidlo((eVozidla)pomocna), "");
		is >> pomocna;
		pom->getVozidlo().setPrevadzkoveNaklady(pomocna);
		is >> spz;
		pom->getVozidlo().setSPZ(spz);
		is >> pomocna;
		pom->getVozidlo().pridajNaklady(pomocna);
		is >> datumEv;
		pom->setDatum(datumEv);
		firma.arrayVozidiel->add(pom);
	}
	int pocetZak = 0;
	is >> pocetZak;
	for (size_t i = 0; i < pocetZak; i++)
	{
		int region = 0;
		string meno = "";
		is >> meno >> region;
		Zakaznik * pom = new Zakaznik(meno, region);
		firma.linkListZakaznikov->add(pom);
	}
	int pocetObj = 0;
	is >> pocetObj;
	for (size_t i = 0; i < pocetObj; i++)
	{
		string menoZakaznika = "";
		is >> menoZakaznika;
		evidenciaObjednavky * prazda = new evidenciaObjednavky(nullptr, "");
		is >> *prazda;
		prazda->getObjednavka()->setZakaznik(firma.najdiZakaznikaPodlaMena(menoZakaznika));
		firma.linkListObjednavok->add(prazda);
	}
	is >> firma.pocetMraziacichAut_ >> firma.pocetLupienkovychAut_ >> firma.kapacitaMraziarenskych_ >> firma.kapacitaLupienkovych_ >>
		firma.skladZemiakov_ >> firma.skladOleja_ >> firma.skladOchu_;

	cout << "Nacitanie prebehlo uspesne \n";*/
	return is;
}
