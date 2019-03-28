#include "CentralnySklad.h"

using namespace std;

CentralnySklad::CentralnySklad()
{
	arrayListZasielok = new structures::ArrayList<Zasielka*>();
}


CentralnySklad::~CentralnySklad()
{
}

void CentralnySklad::prijmiZasielky(Vozidlo * vozidlo)
{

	for (Zasielka* zasielka : vozidlo->getArrayListZasielok())
	{
		arrayListZasielok->add(zasielka);
	}
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