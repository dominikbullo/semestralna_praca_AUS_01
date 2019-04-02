#pragma once

#include <string>
#include "Konstatnty.h"
#include "Datum.h"

class Odosielatel
{
public:
	Odosielatel(std::string region, double vzdialenostOdPrekladiska);
	~Odosielatel() {};
	inline std::string getRegion() {
		return region_;
	}
	inline double getVzdialenostOdPrekladiska() {
		return vzdialenostOdPrekladiska_;
	}
private:
	std::string region_;
	double vzdialenostOdPrekladiska_;

};

class Adresat
{
public:
	Adresat(std::string region, double vzdialenostOdPrekladiska);
	~Adresat() {};
	inline std::string getRegion() {
		return region_;
	}
	inline double getVzdialenostOdPrekladiska() {
		return this->vzdialenostOdPrekladiska_;
	}
private:
	std::string region_;
	double vzdialenostOdPrekladiska_;

};

class Objednavka
{
public:
	Objednavka(double hmotnostZasielky, Odosielatel* odosielatel, Adresat* adresat);
	~Objednavka();
	void toString();
	void zamietniObjednavku(std::string dovodZamietnutia);

	void setDatumaCasSpracovania(std::string datum_a_cas) { this->datumaCasSpracovania_ = datum_a_cas; }
	void setStav(eStavObjednavky stav)
	{
		this->stav_ = stav;
		std::cout << "Objednavka bola " << stringStav() << std::endl;
	}

	eStavObjednavky getStav() { return stav_; }
	inline double getHmotnostZasielky() { return hmotnostZasielky_; }
	inline Adresat* getAdresat() { return adresat_; }
	inline Odosielatel* getOdosielatel() { return odosielatel_; }
	std::string getDatumaCasVytvorenia() { return datumaCasVytvoreniaObjednavky_; }
	std::string getDatumaCasSpracovania() { return datumaCasSpracovania_; }

	friend std::ostream& operator<< (std::ostream& os, Objednavka& objednavka);
	friend std::istream& operator>> (std::istream& is, Objednavka& objednavka);
private:
	double hmotnostZasielky_ = 0.0;
	std::string datumaCasVytvoreniaObjednavky_;
	std::string datumaCasSpracovania_;

	std::string stringStav();
	eStavObjednavky stav_;
	std::string dovodZamietnutia_ = "";

	Odosielatel* odosielatel_;
	Adresat* adresat_;
};
