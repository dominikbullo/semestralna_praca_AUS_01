#pragma once
#include <string>
#include <iostream>
#include <stdio.h>

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"

#include "Datum.h"
#include "Prekladisko.h"
#include "Zasielka.h"
class Vozidlo
{
public:
	Vozidlo(int nostnostVozidla, int prevadzkoveNaklady, std::string SPZ);
	~Vozidlo();
	void toString();
	void pridajPrekladiskoDoTrasyVozidla(Prekladisko * prekladisko);

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
	bool prechadzaPrekladiskom(Prekladisko* prekladiskoKtorymMaPrechadzat) {
		for (Prekladisko * prekladiskoKtorymPrechadza : *linkedListTrasaVozidla)
		{
			if (prekladiskoKtorymPrechadza == prekladiskoKtorymMaPrechadzat) {
				return true;
			}
		}
		std::cout << "Toto auto neprechadza prekladiskom v okrese " << prekladiskoKtorymMaPrechadzat->dajRegion() << std::endl;
		this->vypisTrasuVozidla();
		return false;
	}
	void vypisTrasuVozidla() {
		std::cout << "Trasa vozidlo s SPZ - " << SPZ_ << " je nasledujuca: " << std::endl;
		for (Prekladisko* prekladisko : *linkedListTrasaVozidla)
		{
			std::cout << " -> " << prekladisko->dajRegion();
		}
		std::cout << std::endl;
	}

	void pridajZasielku(Zasielka* zasielka) {
		nosnost_ -= zasielka->getHmotnost();
	}
	bool dokazeNalozitZasielku(Zasielka* zasielka) {
		return nosnost_ - zasielka->getHmotnost() >= 0;
	}

private:
	int prevadzkoveNaklady_;
	std::string datumaCasEvidencie_;
	std::string SPZ_ = "ZA_";
	int naklady_ = 0;
	double nosnost_;
	structures::ArrayList<Prekladisko *> * linkedListTrasaVozidla;
};

