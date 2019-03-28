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
	this->celkovyPocetNalietanychHodin_ += trvanieLetu(novaZasielka) / 60 / 60;
	this->celkovyPocetPrepravenychZasielok_++;
	novaZasielka->setDatumaCasUkoncenia(this->vytazenyDo_);

	this->frontZasielok_->push(novaZasielka);
}

void Dron::spracujZasielky()
{
	if (frontZasielok_->isEmpty()) { return; }
	//TODO think about this	while (frontZasielok_->peek()->getdatumaCasUkoncenia_() < Datum::getAktualnyDatumaCas())
	{
		// TODO test it
		//arrayListZasielok_->add(frontZasielok_->pop());
		frontZasielok_->pop();
	}
	prepocitajInformacieoDosupnosti();

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
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;

	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(zasielka);
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}

void Dron::prepocitajInformacieoDosupnosti()
{
	this->nabiDrona(Datum::string_to_time_t(vytazenyDo_) - Datum::getAktualnyDatumaCasAsTime());
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
	if (kapacitaBaterie_ < 0) { throw std::exception("Neplatny stav nabitia baterie"); }
	cout <<
		"Seriove cislo - " << this->serioveCislo_ << endl <<
		"Datum zaradenia do prevadzky - " << this->datumaCasEvidencie_ << endl <<
		"Typ - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << endl <<
		"Obsadeny do - " << this->vytazenyDo_ << endl <<
		"Kapacita baterie - " << this->kapacitaBaterie_ << endl <<
		"celkovyPocetNalietanychHodin - " << this->celkovyPocetNalietanychHodin_ << endl <<
		"celkovyPocetPrepravenychZasielok - " << this->celkovyPocetPrepravenychZasielok_ << endl;
	cout << "*******************************************************************" << endl;

}

