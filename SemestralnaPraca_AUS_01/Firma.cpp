#include "Firma.h"
#include "Vozidlo.h"
#include "Prekladisko.h"

using namespace std;
Firma::Firma(std::string nazovFirmy)
{
	nazovFirmy_ = nazovFirmy;
	arrayListVozidiel = new structures::ArrayList<Vozidlo*>();
	arrayListPrekladisk = new structures::ArrayList<Prekladisko*>();

	// kvÙli ötatistik·m -> koæko zamietnut˝ch, koæko v kraji a pod.
	linkedListObjednavok = new structures::LinkedList<Objednavka*>();
}

Firma::~Firma()
{
	// treba premazat vsetky objekty ktore som kam naplnil
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		delete vozidlo;
	}
	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
		delete prekladisko;
	}
	for (Objednavka * objednavka : *linkedListObjednavok) {
		delete linkedListObjednavok;
	}
	delete arrayListVozidiel;
	delete arrayListPrekladisk;
	delete linkedListObjednavok;
}
Firma * Firma::get()
{
	return this;
}

void Firma::pridajPrekladisko(Prekladisko* novePrekladisko)
{
	arrayListPrekladisk->add(novePrekladisko);
}

void Firma::vypisanieVsetkychObjednavok()
{
	for (Objednavka * var : *linkedListObjednavok) {
		var->toString();
	}
}

void  Firma::pridajVozidlo(Vozidlo* noveVozidlo)
{
	pridajRegionyDoTrasyVozidla(noveVozidlo);
	// vozidlo prid·vam vûdy na koniec, t˝m p·dom viem, ûe vozidl· s˙ zoradenÈ podæa poradia zaevidovania
	int index = 0;
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		// FIXED zaraÔovanie podæa d·tumu aj Ëasu
		if (noveVozidlo->getDatumaCasEvidencie() < vozidlo->getDatumaCasEvidencie()) {
			arrayListVozidiel->insert(noveVozidlo, index);
			return;
		}
		index++;
	}
	arrayListVozidiel->add(noveVozidlo);

}
void Firma::pridajRegionyDoTrasyVozidla(Vozidlo* vozidlo) {
	string userInput;
	while (userInput != "0") {
		cout << "Ktory region chces pridat do trasy vozidla - " << vozidlo->getSPZ() << " " << endl;
		cin >> userInput;
		if (userInput != "0") {
			vozidlo->pridajPrekladiskoDoTrasyVozidla(this->dajPrekladiskoPodlaRegionu(userInput));
		}
	}
	return;
}

Prekladisko* Firma::dajPrekladiskoPodlaRegionu(std::string okres) {
	// zloûitosù O(n)

	// NOTE osetrenie zlÈho vstupu
	//for (auto & c : okres) c = toupper(c);

	for (Prekladisko * prekladisko : *arrayListPrekladisk) {
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

Vozidlo* Firma::vyberVozidlo(double hmotnostZasielky, Prekladisko* prekladiskoNaPrevzatieZasielky) {
	// TODO pozeraj eöte dopredu an napl·novanÈ z·sielky toho vozidla 
	for (Vozidlo *vozidlo : *arrayListVozidiel) {
		if (vozidlo->prechadzaPrekladiskom(prekladiskoNaPrevzatieZasielky) &&
			vozidlo->dokazeNalozitZasielku(hmotnostZasielky))
		{
			return vozidlo;
		}
	}

	std::cout << "Takuto objednavku nezvladne dorucit ziadne vozidlo" << std::endl;
	return NULL;
}

Objednavka * Firma::vytvorObjednavku(double hmotnostZasielky, Odosielatel * odosielatel, Adresat * adresat)
{
	// TODO pokraËovanie 5ky

	Objednavka * objednavka = new Objednavka(hmotnostZasielky, odosielatel, adresat);

	// zistÌm prekladisko, kde sa odosielal dron
	Prekladisko* prekladiskoOdoslania = this->dajPrekladiskoPodlaRegionu(odosielatel->getRegion());

	// zistÌm, Ëi m·m nejakÈho drona, ktor˝ stihne, unesie a je nabit˝ 
	Dron* dronPreOdosielatela = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, odosielatel->getVzdialenostOdPrekladiska());
	// TODO
	//objednavka->pripaDronaPreOdosielatela();

	// zistÌm Ëi mi do prekladiska prÌde auto ktorÈ bude maù nosnoù tak˙, ûe zvl·dne odniest objednavku
	Vozidlo* vozidloPreOdosielatela = this->vyberVozidlo(hmotnostZasielky, prekladiskoOdoslania);
	// TODO
	//objednavka->priradVozidlo();

	Prekladisko* prekladiskoAdresata = this->dajPrekladiskoPodlaRegionu(adresat->getRegion());
	Vozidlo* vozidloPreAdresata = this->vyberVozidlo(hmotnostZasielky, prekladiskoAdresata);
	// TODO
	//objednavka->priradVozidlo();

	// FIXME toto sa ale p˝taj aû neskÙr, resp na nejak˝ Ëas, kedy tam dan· objedn·vka bude 
	Dron* dronPreAdresata = prekladiskoOdoslania->vyberDrona(hmotnostZasielky, adresat->getVzdialenostOdPrekladiska());

	// treba vymazaù !
	//return new Objednavka(hmotnostZasielky, odosielatel, adresat);
	return NULL;
}

