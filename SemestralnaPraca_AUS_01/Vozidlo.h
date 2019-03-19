#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "Konstatnty.h"
#include "structures/heap_monitor.h"


class Vozidlo
{
public:
	Vozidlo(int nostnostVozidla, int prevadzkoveNaklady);
	~Vozidlo();
	void toString();
	inline int getNosnost() {
		return nosnost_;
	}
	inline int getPrevazdkoveNaklady() {
		return prevadzkoveNaklady_;
	}
	inline std::string getSPZ() {
		return SPZ_;
	}
	inline int getNaklady() {
		return naklady_;
	}
	void setPrevadzkoveNaklady(int prevNaklady) {
		prevadzkoveNaklady_ = prevNaklady;
	}
	void setSPZ(std::string spz) {
		SPZ_ = "";
		SPZ_ = spz;
	}
	void pridajNaklady(int naklady) {
		naklady_ = naklady_ + naklady;
	}
private:
	void setSPZ();
	int prevadzkoveNaklady_;
	int nosnost_;  //pis to v tonách
	std::string SPZ_ = "ZA_";
	int naklady_ = 0;
protected:
	static int unikatnostSPZ_;
};

