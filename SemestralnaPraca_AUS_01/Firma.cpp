#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayPrekladisk = new structures::ArrayList<Prekladisko*>();
	linkObjednavok = new structures::LinkedList<Objednavka*>();
}

Firma::~Firma()
{
	// treba premazat vsetky objekty ktore som kam naplnil
	for (Vozidlo *vozidlo : *arrayVozidiel) {
		delete vozidlo;
	}
	for (Prekladisko * prekladisko : *arrayPrekladisk) {
		delete prekladisko;
	}
	for (Objednavka * objednavka : *linkObjednavok) {
		delete linkObjednavok;
	}
	delete arrayVozidiel;
	delete arrayPrekladisk;
	delete linkObjednavok;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayPrekladisk->add(novePrekladisko);
}

void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	// vozidlo prid·vam vûdy na koniec, t˝m p·dom viem, ûe vozidl· s˙ zoradenÈ podæa poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayVozidiel) {
		// FIXME pozor na toto porovn·vanie 
		if (vozidlo->getDatumaCasEvidencie() <= noveVozidlo->getDatumaCasEvidencie()) {
			arrayVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayVozidiel->add(noveVozidlo);
}

void Firma::vypisZoznamVozidiel()
{
	for (Vozidlo* var : *arrayVozidiel) {
		var->toString();
	}

}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string okres) {
	// zloûitosù O(n)

	// NOTE osetrenie zlÈho vstupu
	//for (auto & c : okres) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayPrekladisk) {
		if (prekladisko->dajOkres() == okres) {
			return prekladisko;
		}
	}
	// TODO: throw exeption
	throw std::logic_error("Prekladisko v tomto okrese sa nenaslo");
}

// TODO 5:Pri vytv·ranÌ objedn·vky je nutnÈ kontrolovaù, Ëi nedÙjde k jej zamietnutiu zo strany
// AoE.DokonËen· objedn·vka je zaraden· do frontu objedn·vok Ëakaj˙cich na spracovanie.
// TODO 5:PoËas vystavovania objedn·vky, mÙûe byù z·sielka z viacer˝ch dÙvodov zamietnut·:
		//	a) z·sielka by musela byù vyzdvihnut· aû po 20:00;
		//	b) z·sielka je mimo akËn˝ r·dius dronov(dron nestihne dÙjsù k odosielateæovi / adres·tovi
		//	a vr·tiù sa sp‰ù predt˝m, ako sa mu vybije batÈria);
		//	c) z·sielku nie je moûnÈ doruËiù, pretoûe je jej hmotnosù vyööia ako nosnosù dostupn˝ch
		//	dronov v lok·lnom prekladisku odosielateæa, resp.adres·ta;
		//	d) naloûenie z·sielky do vozidla prekroËÌ jeho nosnosù;
		//	e) prijatie z·sielky v lok·lnom prekladisku odosielateæa by spÙsobilo, ûe toto lok·lne
		//	prekladisko nedok·ûe doruËiù niektorÈ z·sielky, ktor˝ch adres·ti sa nach·dzaj˙ v jeho
		//	regiÛne, do 18:00 danÈho dÚa.

Objednavka * Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// TODO pokraËovanie 5ky

	// zistÌm prekladisko, kde sa odosielal dron
	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());
	// zistÌm, Ëi m·m nejakÈho drona, ktor˝ stihne, unesie a je nabit˝ 
	Dron* dron = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska());

	// treba vymazaù !
	return new Objednavka(hmotnostZasielky, odosielatel, adresat);
}

