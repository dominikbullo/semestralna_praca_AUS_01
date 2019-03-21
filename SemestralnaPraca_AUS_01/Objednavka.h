#pragma once

#include <string>
#include "Konstatnty.h"

class Odosielatel
{
public:
	Odosielatel(std::string region, double vzdialenostOdPrekladiska);
	~Odosielatel();
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
	~Adresat();
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
	inline double getHmotnostZasielky() {
		return hmotnostZasielky_;
	}
	inline Odosielatel* getOdosielatel() {
		return odosielatel_;
	}
	inline Adresat* getAdresat() {
		return adresat_;
	}


private:
	std::string stringStav();
	eStavObjednavky stav_;
	double hmotnostZasielky_ = 0.0;
	Odosielatel* odosielatel_;
	Adresat* adresat_;
};
