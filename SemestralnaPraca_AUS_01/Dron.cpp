#include "Dron.h"
using namespace std;

Dron::Dron(const eDrony typDronu, std::string serioveCislo)
{
	typ_ = typDronu;
	serioveCislo_ = serioveCislo;
	datumaCasEvidencie_ = Datum::getAktualnyDatumaCas();

	// evidujem bud˙ce objedn·vky, ktorÈ m· dron vybaviù
	frontObjednavok_ = new structures::ExplicitQueue<Objednavka*>();

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
		std::cout << "Neviem vytvorit takyto dron" << std::endl;
	}
}

Dron::~Dron()
{
	// Pretoûe v deötruktore firmy som vymazal väetky objedn·vky -> tu uû nemusÌm
	frontObjednavok_->clear();
	delete frontObjednavok_;
}

void Dron::pridajObjednavku(Objednavka * novaObjednavka)
{
	double vzdialenostObjednavky = novaObjednavka->getOdosielatel()->getVzdialenostOdPrekladiska();
	double trvanieLetuObjednavky = trvanieLetu(vzdialenostObjednavky);
	time_t pom = Datum::string_to_time_t(vytazenyDo_);

	this->vytazenyDo_ = Datum::time_t_to_string(pom + vzdialenostObjednavky);
	znizKapacituBaterie(vzdialenostObjednavky);
	this->celkovyPocetNalietanychHodin_ += vzdialenostObjednavky;
	this->celkovyPocetPrepravenychZasielok_++;
	novaObjednavka->setDatumaCasUkoncenia_(Datum::time_t_to_string(pom + trvanieLetuObjednavky));
	frontObjednavok_->push(novaObjednavka);
}

void Dron::spracujObjednavky()
{
	// TODO think about this 
	//while (frontObjednavok_->peek()->getDatumaCasUkoncenia_() < Datum::getAktualnyDatumaCas())
	//{
	//	vytazeny_ = false;
	//	frontObjednavok_->peek()->setStav(eStavObjednavky::ZREALIZOVANA);
	//	frontObjednavok_->pop();
	//}
}


bool Dron::stihnePriletietPreZasielku(double vzdialenost) {
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;
	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(vzdialenost);
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}


void Dron::toString()
{
	std::cout <<
		"\t Seriove cislo - " << this->serioveCislo_ << endl <<
		"\t Datum zaradenia do prevadzky - " << this->datumaCasEvidencie_ << endl <<
		"\t TYP - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") <<
		"\t Obsadeny do - " << this->vytazenyDo_ << endl <<
		"\t Kapacita baterie - " << this->kapacitaBaterie_ << endl <<
		"\t celkovyPocetNalietanychHodin - " << this->celkovyPocetNalietanychHodin_ << endl <<
		"\t celkovyPocetPrepravenychZasielok - " << this->celkovyPocetPrepravenychZasielok_ << std::endl;
}

