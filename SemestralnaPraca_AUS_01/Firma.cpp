#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayPrekladisk = new structures::ArrayList<Prekladisko*>();
	//linkObjednavok = new structures::LinkedList<Objednavka*>();
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
	delete arrayVozidiel;
	delete arrayPrekladisk;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayPrekladisk->add(novePrekladisko);
}

void Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	// vozidlo pridávam vždy na koniec, tým pádom viem, že vozidlá sú zoradené pod¾a poradia zaevidovania
	arrayVozidiel->add(noveVozidlo);
}

void Firma::vypisZoznamVozidiel()
{
	for (Vozidlo* var : *arrayVozidiel) {
		var->toString();
	}

}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string okres) {
	// zložitos O(n)
	for (Prekladisko * prekladisko : *arrayPrekladisk) {
		if (prekladisko->dajOkres() == okres) {
			return prekladisko;
		}
	}
	// TODO: throw exeption
	throw std::logic_error("Prekladisko v tomto okrese sa nenaslo");
}

// TODO 5:Pri vytváraní objednávky je nutné kontrolova, èi nedôjde k jej zamietnutiu zo strany
// AoE.Dokonèená objednávka je zaradená do frontu objednávok èakajúcich na spracovanie.
// TODO 5:Poèas vystavovania objednávky, môže by zásielka z viacerých dôvodov zamietnutá:
		//	a) zásielka by musela by vyzdvihnutá až po 20:00;
		//	b) zásielka je mimo akèný rádius dronov(dron nestihne dôjs k odosielate¾ovi / adresátovi
		//	a vráti sa spä predtým, ako sa mu vybije batéria);
		//	c) zásielku nie je možné doruèi, pretože je jej hmotnos vyššia ako nosnos dostupných
		//	dronov v lokálnom prekladisku odosielate¾a, resp.adresáta;
		//	d) naloženie zásielky do vozidla prekroèí jeho nosnos;
		//	e) prijatie zásielky v lokálnom prekladisku odosielate¾a by spôsobilo, že toto lokálne
		//	prekladisko nedokáže doruèi niektoré zásielky, ktorých adresáti sa nachádzajú v jeho
		//	regióne, do 18:00 daného dòa.

Objednavka * Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// TODO pokraèovanie 5ky

	// zistím prekladisko, kde sa odosielal dron
	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());
	// zistím, èi mám nejakého drona, ktorý stihne, unesie a je nabitý 
	Dron* dron = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska());




	return new Objednavka(hmotnostZasielky, odosielatel, adresat);
}

