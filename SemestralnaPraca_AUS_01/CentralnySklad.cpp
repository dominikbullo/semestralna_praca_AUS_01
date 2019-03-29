#include "CentralnySklad.h"

using namespace std;

CentralnySklad::CentralnySklad()
{
	arrayListZasielok = new structures::ArrayList<Zasielka*>();
}

CentralnySklad::~CentralnySklad()
{
	delete arrayListZasielok;
}

void CentralnySklad::prijmiZasielky(Vozidlo * vozidlo)
{

	for (Zasielka* zasielka : vozidlo->getArrayListZasielok())
	{
		arrayListZasielok->add(zasielka);
	}
	// TODO po pridaní, odstraò zasielku z vozidla -> vyber a prelož do iného 
	// TODO otestova 
	vozidlo->getArrayListZasielok().clear();
}

void CentralnySklad::vypisZoznamZasielok() {
	cout << endl << "*******************************************************************" << endl;
	cout << "*************** Zoznam zasielok v centralnom sklade ***************" << endl;
	cout << "*******************************************************************" << endl << endl;
	for (Zasielka* zasielka : *arrayListZasielok)
	{
		zasielka->toString();
	}
}
void CentralnySklad::naplVozidla() {
}

ostream & operator<<(ostream & os, CentralnySklad & centralnySklad)
{
	// TODO: insert return statement here
	for (Zasielka* zasielka : *centralnySklad.arrayListZasielok)
	{
		os << *zasielka;
	}
	return os;
}

istream & operator>>(istream & is, CentralnySklad & centralnySklad)
{
	// TODO: insert return statement here
	return is;
}
