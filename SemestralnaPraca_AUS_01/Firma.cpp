#include "Firma.h"
#include "Dron.h"

Firma::Firma()
{
	arrayVozidiel = new structures::ArrayList<evidenciaVozidla*>();
	arrayPrekladisk = new structures::ArrayList<Dron*>();
}


Firma::~Firma()
{
}

void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	evidenciaVozidla * noveEvidovaneVozidlo = new evidenciaVozidla(noveVozidlo, Datum::getAktualnyDatum());
	arrayVozidiel->add(noveEvidovaneVozidlo);

	// TODO datum evidencie  
	// evidenciaVozidla * pom = new evidenciaVozidla(noveVozidlo, Datum::getAktualnyDatum());
	//int index = 0;
	//for (Vozidlo* var : *arrayVozidiel) {
	//	// TODO: vklada vozidlá poporade -> pod¾a èasu a porovnáva 
	//	if (noveVozidlo->getSPZ() <= var->getSPZ()) {
	//		arrayVozidiel->insert(noveVozidlo, index);
	//		return;
	//	}
	//	index++;
	//}
	//arrayVozidiel->add(noveVozidlo);

}

// EVIDENCIE
//vozidla
evidenciaVozidla::evidenciaVozidla(Vozidlo * novyVoz, string datum) :
	voz_(novyVoz), datumEvidencie_(datum)
{
}

Vozidlo & evidenciaVozidla::getVozidlo()
{
	return *voz_;
}

Vozidlo * evidenciaVozidla::dajVozidlo()
{
	return voz_;
}



string evidenciaVozidla::getDatum()
{
	return datumEvidencie_;
}

evidenciaVozidla::~evidenciaVozidla()
{
	delete voz_;
}