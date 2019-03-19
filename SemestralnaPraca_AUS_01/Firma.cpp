#include "Firma.h"
#include "Prekladisko.h"

Firma::Firma()
{
	arrayVozidiel = new structures::ArrayList<evidenciaVozidla*>();
	arrayPrekladisk = new structures::ArrayList<Prekladisko*>();
}


Firma::~Firma()
{
}
void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayPrekladisk->add(novePrekladisko);
}

// TODO: vklada vozidlá poporade -> pod¾a èasu a porovnáva 
// FIXME vklada vozidlá na základe dátumu 
void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	evidenciaVozidla * noveEvidovaneVozidlo = new evidenciaVozidla(noveVozidlo, Datum::getAktualnyDatum());
	//int index = 0;
	//for (evidenciaVozidla* var : *arrayVozidiel) {
	//	if (noveEvidovaneVozidlo->getDatum <= var->getDatum()) {
	//		arrayVozidiel->insert(noveEvidovaneVozidlo, index);
	//		return;
	//	}
	//	index++;
	//}
	arrayVozidiel->add(noveEvidovaneVozidlo);

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