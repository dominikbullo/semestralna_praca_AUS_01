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

	// vozidlo prid�vam v�dy na koniec, t�m p�dom viem, �e vozidl� s� zoraden� pod�a poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		// FIXED zara�ovanie pod�a d�tumu aj �asu
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
			/*vozidlo->aktualizujCelkoveNaklady();*/
			this->centralnySklad_->prijmiZasielky(vozidlo);
		}
	}
	else {
		std::cout << "Firma je este otvorena. Nemozno vratit vozidla do centralneho skladu" << std::endl;
	}
}

void Firma::naplnVozidla()
{
	for (Zasielka * zasielka : centralnySklad_->getArrayListZasielok())
	{
		this->vyberVozidlo(zasielka)->pridajZasielku(zasielka);
	}
}


Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string region) {

	// NOTE osetrenie zl�ho vstupu
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
{	// zist�m �i mi do prekladiska pr�de auto ktor� bude ma� nosno� tak�, �e zvl�dne odniest objednavku
	return this->vyberVozidlo(zasielka, this->dajPrekladiskoPodlaRegionu(zasielka->getRegion()));
}

Vozidlo* Firma::vyberVozidlo(Zasielka* zasielka, Prekladisko * prekladisko) {
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
		objednavka->zamietniObjednavku("Nena�iel sa vhodny dron");
		delete zasielka;
		return;
	}
	// pre�a�en�m met�dy sa p�tam nie na prekladisko, ktor� mu bolo priraden�, ale na prekladisko k adres�tovi
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
	int max = 0;
	Prekladisko *maxPrekladisko = NULL;

	for (Prekladisko* prekladisko : *this->arrayListPrekladisk)
	{
		int temp = 0;
		for (Objednavka* objednavka : *this->linkedListObjednavok)
		{
			if (prekladisko->dajRegion() == objednavka->getAdresat()->getRegion() &&
				Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia())
				> Datum::string_to_time_t(datumOd) &&
				Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia())
				< Datum::string_to_time_t(datumDo))
			{
				temp++;
			}
		}

		if (temp > max) {
			max = temp;
			maxPrekladisko = prekladisko;
		}
	}
	if (maxPrekladisko != NULL)
	{
		cout << "Najviac zasielok sa dorucilo do regionu " << maxPrekladisko->dajRegion() << endl;
	}
	else
	{
		cout << "Ziadne prekladisko neprijalo zasielku." << endl;
	}
}

void Firma::getRegionsNajvacsimPoctomPrijatychObjednavok(std::string datumOd, std::string datumDo)
{
	int max = 0;
	Prekladisko *maxPrekladisko = NULL;

	for (Prekladisko* prekladisko : *this->arrayListPrekladisk)
	{
		int temp = 0;
		for (Objednavka* objednavka : *this->linkedListObjednavok)
		{
			if (prekladisko->dajRegion() == objednavka->getOdosielatel()->getRegion() &&
				Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia())
				> Datum::string_to_time_t(datumOd) &&
				Datum::string_to_time_t(objednavka->getDatumaCasVytvorenia())
				< Datum::string_to_time_t(datumDo))
			{
				temp++;
			}
		}

		if (temp > max) {
			max = temp;
			maxPrekladisko = prekladisko;
		}
	}
	if (maxPrekladisko != NULL)
	{
		cout << "Najviac zasielok sa odoslalo z regionu " << maxPrekladisko->dajRegion() << endl;
	}
	else
	{
		cout << "Ziadne prekladisko neodoslalo zasielku." << endl;
	}
}


void Firma::vypisZasielkySDovodomZamietnutia(std::string datumOd, std::string datumDo, std::string region)
{
	int pocet = 0;
	for (Objednavka * objednavka : *this->linkedListObjednavok) {
		// zamietnut� -> nie zru�en�
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
		cout << "Ziadna objednavka nebola v regione " << region << " zamietnuta firmou v tento datum" << endl;
	}
}

void Firma::vypisaniePoctuZrusenychObjednavok(std::string datumOd, std::string datumDo)
{
	throw std::exception("vypisaniePoctuZrusenychObjednavok: Not implemented yet!");
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
void Firma::vypisaniePoctuHodinPodlaTypuDrona()
{
	double typJeden = 0;
	double typDva = 0;

	for (Prekladisko * prekladisko : *this->arrayListPrekladisk)
	{
		for (Dron *dron : prekladisko->getZoznamDronov())
		{
			if (dron->getTyp() == eDrony::JEDEN)
			{
				typJeden += dron->getCelkovyPocetNalietanychHodin();
			}
			else {
				typDva += dron->getCelkovyPocetNalietanychHodin();
			}
		}
	}
	cout << "Celkovy pocet hodin dronu typu jeden je " << typJeden << endl;
	cout << "Celkovy pocet hodin dronu typu dva je " << typDva << endl;
}
ostream& operator<< (ostream& os, Firma& firma) {

	os << firma.nazovFirmy_ << "\n";

	os << firma.arrayListPrekladisk->size() << "\n";
	for (Prekladisko * var : *firma.arrayListPrekladisk) {
		os << *var;
	}

	os << firma.arrayListVozidiel->size() << "\n";
	for (Vozidlo * var : *firma.arrayListVozidiel) {
		os << *var;
	}

	os << firma.linkedListObjednavok->size() << "\n";
	for (Objednavka * var : *firma.linkedListObjednavok) {
		os << *var;
	}
	return os;
}
istream& operator>> (istream& is, Firma& firma)
{
	double nosnost, prevadzkoveNaklady, pocetRegionovTrasy;
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
		for (size_t j = 0; j < pocetRegionovTrasy; j++)
		{
			is >> region;
			nacitaneVozidlo->pridajPrekladiskoDoTrasyVozidla(firma.dajPrekladiskoPodlaRegionu(region));

		}
		int pocetZasielokVoVozidle = 0;
		is >> pocetZasielokVoVozidle;
		double hmotnost, odosVzd, adrVzd;
		std::string odosReg, adrReg;

		for (size_t k = 0; k < pocetZasielokVoVozidle; k++)
		{
			is >> hmotnost >> odosReg >> odosVzd >> adrReg >> adrVzd;
			Objednavka* nacitanaObjednavka = new Objednavka(hmotnost, new Odosielatel(odosReg, odosVzd), new Adresat(adrReg, adrVzd));
			is >> *nacitanaObjednavka;

			Zasielka* nacitanaZasielka = new Zasielka(nacitanaObjednavka);
			is >> *nacitanaZasielka;

			nacitaneVozidlo->pridajZasielkuDoVozidla(nacitanaZasielka);
			delete nacitanaObjednavka;
		}
		firma.arrayListVozidiel->add(nacitaneVozidlo);
	}

	int pocetObjednavok = 0;
	is >> pocetObjednavok;
	for (size_t i = 0; i < pocetObjednavok; i++)
	{
		double hmotnost, odosVzd, adrVzd;
		std::string odosReg, adrReg;
		is >> hmotnost >> odosReg >> odosVzd >> adrReg >> adrVzd;
		Objednavka* nacitanaObjednavka = new Objednavka(hmotnost, new Odosielatel(odosReg, odosVzd), new Adresat(adrReg, adrVzd));
		is >> *nacitanaObjednavka;

		firma.linkedListObjednavok->add(nacitanaObjednavka);
	}
	return is;
}
