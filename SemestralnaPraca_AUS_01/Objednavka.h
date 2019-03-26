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
		return vzdialenostOdPrekladiska_;
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
	inline double getHmotnostZasielky() {
		return hmotnostZasielky_;
	}
	inline Odosielatel* getOdosielatel() {
		return odosielatel_;
	}
	inline Adresat* getAdresat() {
		return adresat_;
	}
	std::string getDatumaCasVytvorenia() {
		return datumaCasVytvoreniaObjednavky_;
	}
	void setDatumaCasSpracovania_(std::string datum_a_cas) {
		datumaCasSpracovania_ = datum_a_cas;
	}
	void setDatumaCasUkoncenia_(std::string datum_a_cas) {
		datumaCasUkoncenia_ = datum_a_cas;
	}
	std::string getDatumaCasUkoncenia_() {
		return datumaCasUkoncenia_;
	}
	void setStav(eStavObjednavky stav) {
		stav_ = stav;
	}
	eStavObjednavky getStav() {
		return stav_;
	}

private:
	std::string datumaCasVytvoreniaObjednavky_;
	std::string datumaCasSpracovania_;
	std::string datumaCasUkoncenia_;
	std::string stringStav();
	eStavObjednavky stav_;
	double hmotnostZasielky_ = 0.0;
	Odosielatel* odosielatel_;
	Adresat* adresat_;
};
