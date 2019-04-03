#include "CentralnySklad.h"

using namespace std;

CentralnySklad::CentralnySklad()
{
	arrayListZasielok_ = new structures::ArrayList<Zasielka*>();
}

CentralnySklad::~CentralnySklad()
{
	delete arrayListZasielok_;
}

void CentralnySklad::prijmiZasielky(Vozidlo * vozidlo)
{
	vozidlo->aktualizujCelkoveNaklady();

	for (Zasielka* zasielka : vozidlo->getArrayListZasielok())
	{
		//zmením smer
		zasielka->setRegion(zasielka->getObjednavka()->getAdresat()->getRegion());
		zasielka->setVzdialenost(zasielka->getObjednavka()->getAdresat()->getVzdialenostOdPrekladiska());
		arrayListZasielok_->add(zasielka);
	}
	vozidlo->getArrayListZasielok().clear();
}

void CentralnySklad::vypisZoznamZasielok() {
	cout << endl << "*******************************************************************" << endl;
	cout << "*************** Zoznam zasielok v centralnom sklade ***************" << endl;
	cout << "*******************************************************************" << endl << endl;
	for (Zasielka* zasielka : *arrayListZasielok_)
	{
		zasielka->toString();
	}
}

ostream & operator<<(ostream & os, CentralnySklad & centralnySklad)
{
	for (Zasielka* zasielka : *centralnySklad.arrayListZasielok_)
	{
		os << *zasielka;
	}
	return os;
}

istream & operator>>(istream & is, CentralnySklad & centralnySklad)
{
	// TODO: insert return statement here
	throw std::exception("operator>>: Not implemented yet.");
	return is;
}
