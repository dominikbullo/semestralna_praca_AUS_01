#include "Dron.h"
using namespace std;

Dron::Dron(const eDrony typDronu, string serioveCislo)
{
	this->typ_ = typDronu;
	this->serioveCislo_ = serioveCislo;
	this->datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem budúce objednávky, ktoré má dron vybavi
	this->frontZasielok_ = new structures::ExplicitQueue<Zasielka*>();

	switch (typDronu) {
	case eDrony::JEDEN:
		nosnost_ = (int)dronTypuJeden::NOSNOST;
		primernaRychlost_ = (int)dronTypuJeden::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuJeden::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuJeden::CAS_NABITIE_10_PERCENT;
		break;

	case eDrony::DVA:
		nosnost_ = (int)dronTypuDva::NOSNOST;
		primernaRychlost_ = (int)dronTypuDva::PRIEMERNA_RYCHLOST;
		maxDobaLetu_ = (int)dronTypuDva::MAX_DOBA_LETU;
		casNaNabitie10Percent_ = (int)dronTypuDva::CAS_NABITIE_10_PERCENT;
		break;

	default:
		cout << "Neviem vytvorit takyto dron" << endl;
	}
}

Dron::~Dron()
{
	// Pretože v deštruktore firmy som vymazal vŠetky objednávky -> tu už nemusím
	this->frontZasielok_->clear();
	delete this->frontZasielok_;
}

void Dron::pridajZasielku(Zasielka * novaZasielka)
{
	double cestaSpat = trvanieLetu(novaZasielka) / 2.0;

	this->vytazenyDo_ = Datum::time_t_to_string(casPriletuPreZasielku(novaZasielka) + cestaSpat);

	znizKapacituBaterie(trvanieLetu(novaZasielka));

	this->celkovyPocetNalietanychHodin_ += trvanieLetu(novaZasielka) / 60.0 / 60;
	this->celkovyPocetPrepravenychZasielok_++;
	novaZasielka->setDatumaCasUkoncenia(this->vytazenyDo_);

	this->frontZasielok_->push(novaZasielka);
}

// TODO spracovanie, pod¾a èasu, alebo pod¾a naloženia
void Dron::spracujZasielky(structures::ArrayList<Zasielka*> * arrayListZasielok_)
{
	while (!frontZasielok_->isEmpty()
		&& frontZasielok_->peek()->getdatumaCasUkoncenia_() < Datum::getAktualnyDatumaCas()
		)
	{
		arrayListZasielok_->add(frontZasielok_->pop());
		//frontZasielok_->pop();
	}

}

double Dron::getCasPotrebnyNaDobitie(double potrebnyPocetPercent)
{
	if (potrebnyPocetPercent <= this->kapacitaBaterie_) { return 0; }
	double potrebujemNabit = potrebnyPocetPercent - this->kapacitaBaterie_;
	double casNaNabitiePercenta = ((casNaNabitie10Percent_ * 60) / 10.0);
	return potrebujemNabit * casNaNabitiePercenta;
}

double Dron::getPocetPercentNaZvladnutieLetu(Zasielka * zasielka)
{
	double potrebujemPreletietVzialenost = zasielka->getVzdialenost() * 2;
	double result = 100 / (((primernaRychlost_ / 60.0) * maxDobaLetu_) / potrebujemPreletietVzialenost);
	if (result > 100) { throw std::exception("no way"); }
	return result;

}

bool Dron::stihnePriletietPreZasielku(Zasielka * zasielka) {
	time_t aktualnyCas = Datum::getAktualnyDatumaCasAsTime();

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;

	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(zasielka);
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}

void Dron::prepocitajInformacieoDosupnosti()
{
	this->nabiDrona(Datum::getAktualnyDatumaCasAsTime() - Datum::string_to_time_t(vytazenyDo_));
	//time_t test = Datum::string_to_time_t(vytazenyDo_);
	//time_t test1 = Datum::getAktualnyDatumaCasAsTime();

	if (Datum::string_to_time_t(vytazenyDo_) < Datum::getAktualnyDatumaCasAsTime())
	{
		this->vytazeny_ = false;
	}
}

void Dron::toString()
{
	cout << "******************** Informacie o dronovi **********************" << endl;
	cout <<
		"Seriove cislo - " << this->serioveCislo_ << endl <<
		"Datum zaradenia do prevadzky - " << this->datumaCasEvidencie_ << endl <<
		"Typ - " << ((typ_ == eDrony::JEDEN) ? "JEDEN" : "DVA") << endl <<
		"Obsadeny do - " << this->vytazenyDo_ << endl <<
		"Virtuálna kapacita baterie - " << this->kapacitaBaterie_ << endl <<
		"Celkovy pocet nalietanych hodin - " << this->celkovyPocetNalietanychHodin_ << endl <<
		"Celkovy pocet prepravenych zasielok - " << this->celkovyPocetPrepravenychZasielok_ << endl;
	cout << "*******************************************************************" << endl;

}

ostream & operator<<(ostream & os, Dron & dron)
{
	// Atributy
	//os << "**atributy drona**\n";
	os <<
		(int)dron.typ_ << " " <<
		dron.serioveCislo_ << " " <<

		dron.vytazeny_ << " " <<
		dron.datumaCasEvidencie_ << " " <<
		dron.vytazenyDo_ << " " <<
		dron.nosnost_ << " " << // nosnost aj ostane veci viem podla typu
		dron.celkovyPocetPrepravenychZasielok_ << " " <<
		dron.kapacitaBaterie_ << " " <<
		dron.celkovyPocetNalietanychHodin_ << " " << "\n";

	// Struktury 
	structures::ExplicitQueue<Zasielka*> *kopiaFrontu = new structures::ExplicitQueue<Zasielka*>(*dron.frontZasielok_);

	while (!kopiaFrontu->isEmpty()) {
		os << *kopiaFrontu->pop();
	}
	delete kopiaFrontu;
	return os;
}

istream & operator>>(istream & is, Dron & dron)
{
	// TODO: insert return statement here
	return is;
}
