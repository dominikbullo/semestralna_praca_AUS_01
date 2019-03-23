#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"

#include "Konstatnty.h"
#include "Datum.h"
#include "Vozidlo.h"


class Vozidlo
{
public:
	Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ);
	~Vozidlo();
	void toString();
	void pridajRegionyDoTrasyVozidla();
	inline int getCelkovaNosnost() {
		return celkovaNosnost_;
	}
	inline int getPrevazdkoveNaklady() {
		return prevadzkoveNaklady_;
	}
	std::string getSPZ() {
		return SPZ_;
	}
	inline int getNaklady() {
		return naklady_;
	}
	std::string getDatumaCasEvidencie() {
		return datumaCasEvidencie_;
	}
	void vypisTrasuvozidla() {
		std::cout << "Trasa vozidlo s SPZ - " << SPZ_ << " je nasledujuca: " << std::endl;
		for (std::string prekladisko : *linkedListTrasaVozidla)
		{
			std::cout << " -> " << prekladisko;
		}
		std::cout << std::endl;
	}

	void pridajZasielku(double hmotnostZasielky) {
		nosnost_ -= hmotnostZasielky;
	}
	bool dokazeNalozitZasielku(double hmotnostZasielky) {
		return celkovaNosnost_ >= nosnost_ + hmotnostZasielky;
	}
	// TODO: e) prijatie zásielky v lokálnom prekladisku odosielateľa by spôsobilo, že toto lokálne
	//			prekladisko nedokáže doručiť niektoré zásielky, ktorých adresáti sa nachádzajú v jeho regióne, do 18:00 daného dňa.

private:
	int prevadzkoveNaklady_;
	int celkovaNosnost_;
	std::string datumaCasEvidencie_;
	std::string SPZ_ = "ZA_";
	int naklady_ = 0;
	double nosnost_ = celkovaNosnost_;
	structures::LinkedList<std::string> * linkedListTrasaVozidla;
};

