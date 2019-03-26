#include "Dron.h"


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
//string Objednavka::getCasDokonceniaObjednavky()
//{
//	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());
//	return Datum::time_t_to_string(aktualnyCas + casLetu);
//}

std::string Dron::pridajObjednavku(Objednavka * novaObjednavka) {
	// Ëo tu treba eöte ???
	vytazeny_ = true;

	//std::string vytazenyDo = novaObjednavka->
	//	getCasDokonceniaObjednavky(novaObjednavka->getOdosielatel()->getVzdialenostOdPrekladiska());

	frontObjednavok_->push(novaObjednavka);
	//novaObjednavka->setDatumaCasUkoncenia_("eöte neviem Ëo")
	//return vytazenyDo;
	return "";
}

void Dron::spracujObjednavky() {

	//while (!frontObjednavok_->isEmpty())
	//{
	//	cout << "Spracovavam objednavku: " << endl;
	//	frontObjednavok_->pop()->toString();
	//}
	std::cout << "metoda spracovania objedfnavok este nie je k dispozicii" << std::endl;
}


bool Dron::stihnePriletietPreZasielku(double vzdialenost) {
	time_t aktualnyCas = Datum::string_to_time_t(Datum::getAktualnyDatumaCas());

	tm *ltm = localtime(&aktualnyCas);
	struct tm casNajneskor = *ltm;
	casNajneskor.tm_hour = 20;
	casNajneskor.tm_min = 00;

	time_t ocakavanyCasPriletu = this->casPriletuPreZasielku(vzdialenost);
	std::cout <<
		(ocakavanyCasPriletu <= mktime(&casNajneskor) ?
			"Predpokladany cas priletu dronu ( " + this->serioveCislo_ + " ) : " + Datum::time_t_to_string(ocakavanyCasPriletu) : "Dron to nestihne") <<
		std::endl;
	return ocakavanyCasPriletu <= mktime(&casNajneskor);
}


void Dron::toString()
{
	std::cout << "Datum zaradenia do prevadzky - " << this->datumaCasEvidencie_ <<
		"\t Seriove cislo - " << this->serioveCislo_ <<
		"\t TYP - " << ((typ_ == eDrony::JEDEN) ? "jeden" : "dva") << "\t celkovyPocetNalietanychHodin - " <<
		this->celkovyPocetNalietanychHodin_ << "\t celkovyPocetPrepravenychZasielok - " <<
		this->celkovyPocetPrepravenychZasielok_ << std::endl;
}

