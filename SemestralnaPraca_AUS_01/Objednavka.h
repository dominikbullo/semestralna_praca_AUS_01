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

	void setDatumaCasSpracovania(std::string datum_a_cas) { datumaCasSpracovania_ = datum_a_cas; }
	void setStav(eStavObjednavky stav) { stav_ = stav; }

	inline double getHmotnostZasielky() { return hmotnostZasielky_; }
	inline Adresat* getAdresat() { return adresat_; }
	inline Odosielatel* getOdosielatel() { return odosielatel_; }
	std::string getDatumaCasVytvorenia() { return datumaCasVytvoreniaObjednavky_; }
	std::string getDatumaCasSpracovania() { return datumaCasSpracovania_; }

private:
	std::string datumaCasVytvoreniaObjednavky_;
	std::string datumaCasSpracovania_;

	std::string stringStav();
	eStavObjednavky stav_;
	double hmotnostZasielky_ = 0.0;
	Odosielatel* odosielatel_;
	Adresat* adresat_;
};
