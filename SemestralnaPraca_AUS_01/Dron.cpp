#include "Dron.h"
using namespace std;

Dron::Dron(const eDrony typDronu, string serioveCislo)
{
	this->typ_ = typDronu;
	this->serioveCislo_ = serioveCislo;
	this->datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem bud˙ce objedn·vky, ktorÈ m· dron vybaviù
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
	// Pretoûe v deötruktore firmy som vymazal väetky objedn·vky -> tu uû nemusÌm
	this->frontZasielok_->clear();
	delete this->frontZasielok_;
}

void Dron::pridajZasielku(Zasielka * novaZasielka)
{
	double vzdialenostObjednavky = novaZasielka->getVzdialenost();
	double trvanieLetuObjednavky = trvanieLetu(novaZasielka);
	time_t pom = Datum::string_to_time_t(vytazenyDo_);

	this->vytazenyDo_ = Datum::time_t_to_string(pom + trvanieLetuObjednavky);
	znizKapacituBaterie(trvanieLetuObjednavky);
	this->celkovyPocetNalietanychHodin_ += trvanieLetuObjednavky / 60 / 60;
	this->celkovyPocetPrepravenychZasielok_++;
	novaZasielka->setDatumaCasUkoncenia(Datum::time_t_to_string(pom + trvanieLetuObjednavky));

	this->frontZasielok_->push(novaZasielka);
}

void Dron::spracujObjednavky()
{
	throw std::exception("Dron::spracujObjednavky: Not implemented yet.");
	//if (frontZasielok_->isEmpty()) { return; }
	////TODO think about this
	//while (frontZasielok_->peek()->getDatumaCasUkoncenia_() < Datum::getAktualnyDatumaCas())
	//{
	//	Objednavka* vybranaObjednavka = frontZasielok_->peek();
	//	vytazeny_ = false;
	//	vybranaObjednavka->setStav(eStavObjednavky::ZREALIZOVANA);
	//	vybranaObjednavka->toString();
	//	frontZasielok_->pop();

	//}

}

double Dron::getCasPotrebnyNaDobitie(double potrebnyPocetPercent)
{
	// FIXME time ?? how much
	if (potrebnyPocetPercent < 0) {
		throw std::exception("fucked");
	}
	if (potrebnyPocetPercent <= this->kapacitaBaterie_) { return 0; }
	double potrebujemNabit = potrebnyPocetPercent - this->kapacitaBaterie_;
	double casNaNabitiePercenta = 10 / casNaNabitie10Percent_ * 60;
	return potrebujemNabit / casNaNabitiePercenta;
}
double Dron::getPocetPercentNaZvladnutieLetu(Zasielka * zasielka)
{
	// toto mam km 
	double potrebujemPreletiet = zasielka->getVzdialenost();
	// toto mam km
	double aktualneDokazePreletiet = maxDobaLetu_ * (kapacitaBaterie_ / 100) * (primernaRychlost_ / 60.0) / 2;

	// potrebujem dobiù baterku na pocet km
	double potrebujemDobit = potrebujemPreletiet - aktualneDokazePreletiet;

	if (potrebujemDobit <= 0) {
		return kapacitaBaterie_;
	}
	// FIXMEEEEEEEEEEEEEEEEEEEEEE
	auto test = potrebujemDobit + trvanieLetu(zasielka);
	return kapacitaBaterie_ + test; // nieËo
}

// TODO: moûnosù vyuûitia s pridanÌm stavu nabitia a n·sledneho poËÌtania
bool Dron::stihnePriletietPreZasielku(Zasielka * zasielka) {
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;

	//TODO try parsing time
	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(zasielka);
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}

void Dron::prepocitajInformacieoDosupnosti()
{
	this->nabiDrona(Datum::string_to_time_t(vytazenyDo_) - Datum::getAktualnyDatumaCasAsTime());
	time_t test = Datum::string_to_time_t(vytazenyDo_);
	time_t test1 = Datum::getAktualnyDatumaCasAsTime();

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
		"Typ - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << endl <<
		"Obsadeny do - " << this->vytazenyDo_ << endl <<
		"Kapacita baterie - " << this->kapacitaBaterie_ << endl <<
		"celkovyPocetNalietanychHodin - " << this->celkovyPocetNalietanychHodin_ << endl <<
		"celkovyPocetPrepravenychZasielok - " << this->celkovyPocetPrepravenychZasielok_ << endl;
	cout << "*******************************************************************" << endl;

}

