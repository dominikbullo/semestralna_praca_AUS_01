#include "Prekladisko.h"


using namespace std;
int Prekladisko::unikatneSerioveCislo_ = 000000;

Prekladisko::Prekladisko(std::string region)
{
	this->unikatneSerioveCislo_ = 000000;
	std::transform(region.begin(), region.end(), region.begin(), ::toupper);
	this->region_ = region;
	this->arrayListDronov_ = new structures::ArrayList<Dron*>();
	//this->arrayListZasielok_ = new structures::ArrayList<Zasielka*>();

	this->pridajDron(new Dron(eDrony::DVA, set_get_SerioveCislo()));
}

Prekladisko::~Prekladisko()
{
	for (Dron * dron : *this->arrayListDronov_) {
		delete dron;
	}
	delete this->arrayListDronov_;

}

void Prekladisko::pridajDron(Dron * novyDron)
{
	// NOTE: netreba ich ukladať podľa dátumu
	// TODO: priestor na usporiadanie dronov podľa hmotnosti napríklad, následne rýchlejšie sortovanie a vyberanie ? 
	//for (int i = 0; i < arrayListDronov_->size(); i++)
	//{
	//	if (arrayListDronov_->operator[](i)->getDatumaCasEvidencie() > novyDron->getDatumaCasEvidencie())
	//	{
	//		arrayListDronov_->insert(novyDron, i);
	//		return;
	//	}
	//}
	this->arrayListDronov_->add(novyDron);
}


void Prekladisko::vypisZoznamDronov() {
	std::cout << "Vypisujem vsetkych dronov pre prekladisko z okresu - " << region_ << std::endl;
	for (Dron * dron : *this->arrayListDronov_) {
		dron->toString();
	}
}

void Prekladisko::spracujZasielky()
{
	for (Dron * dron : *this->arrayListDronov_) {
		//dron->spracujZasielky(arrayListZasielok_);
		dron->spracujZasielky();
	}
}


Dron * Prekladisko::vyberDrona(Zasielka * zasielka)
{
	// zistím drona z tohto prekladiska, či mám nejakého drona, ktorý stihne, unesie a je nabitý 

	Dron* volnyKandidatNaDrona = nullptr;
	Dron* obsadenyKandidatNaDrona = nullptr;
	Dron* vybityKandidatNaDrona = nullptr;

	for (Dron * dron : *this->arrayListDronov_)
	{
		dron->prepocitajInformacieoDosupnosti();

		if (dron->unesieZasielku(zasielka) &&
			dron->zvladneLet(zasielka) &&
			dron->stihnePriletietPreZasielku(zasielka))
		{

			if (dron->jeVolny()) {
				volnyKandidatNaDrona = dajLepšiehoVolnehoDrona(dron, volnyKandidatNaDrona);
				continue;
			}
			if (volnyKandidatNaDrona == nullptr) {
				obsadenyKandidatNaDrona = dajLelpšiehoObsadenehoDrona(dron, obsadenyKandidatNaDrona);
				continue;
			}
		}

		// TODO better way ? 
		else if (dron->unesieZasielku(zasielka) &&
			dron->stihnePriletietPreZasielku(zasielka))
		{
			vybityKandidatNaDrona = dron;
			continue;
		}

	}

	// TODO: dron, ktorý zvládne najefektívnejšie doručiť objednávku, aj s userovím súhlasom ak to bude neskoro
	if (volnyKandidatNaDrona != nullptr) { return volnyKandidatNaDrona; }
	if (obsadenyKandidatNaDrona != nullptr) { return obsadenyKandidatNaDrona; }
	if (vybityKandidatNaDrona != nullptr)
	{
		std::cout << "Dron je vybity ale bude ososlany hned ako to bude mozne" << std::endl;
		return vybityKandidatNaDrona;
	}
	std::cout << "Firma nema prostriedky, aby dorucila tuto objednavku" << endl;
	return NULL;

}

Dron* Prekladisko::dajLepšiehoVolnehoDrona(Dron* dron1, Dron* dron2) {
	if (dron1 == nullptr) { return dron2; }
	if (dron2 == nullptr) { return dron1; }

	if (dron1->getNosnost() == dron2->getNosnost()) {
		return dron1->getAktualnaKapacitaBaterie() > dron2->getAktualnaKapacitaBaterie() ? dron1 : dron2;
	}
	return dron1->getNosnost() < dron2->getNosnost() ? dron1 : dron2;
}

Dron * Prekladisko::dajLelpšiehoObsadenehoDrona(Dron * dron1, Dron * dron2)
{
	if (dron1 == nullptr) { return dron2; }
	if (dron2 == nullptr) { return dron1; }

	// TODO možno tu, zarátať aj čas, ktorý sa mohol nabíjať
	return dron1->vytazenyDo() < dron2->vytazenyDo() ? dron1 : dron2;

}

std::string Prekladisko::set_get_SerioveCislo()
{
	int pom = ++unikatneSerioveCislo_;
	std::string formated = std::string(6 - std::to_string(pom).length(), '0') + std::to_string(pom);
	// SET
	this->serioveCislo_ = this->region_ + formated;
	// GET
	return serioveCislo_;
}

