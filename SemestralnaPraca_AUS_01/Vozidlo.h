﻿#pragma once
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
	void vypisZasielkyVozidla();
	void pridajPrekladiskoDoTrasyVozidla(Prekladisko * prekladisko);

	inline int getPrevazdkoveNaklady() { return prevadzkoveNaklady_; }
	std::string getSPZ() { return SPZ_; }
	inline int getNaklady() { return naklady_; }
	std::string getDatumaCasEvidencie() { return datumaCasEvidencie_; }
	structures::ArrayList<Zasielka*> getArrayListZasielok() { return *arrayListZasielok_; }

	void aktualizujCelkoveNaklady() { this->naklady_ += 2.0 * prevadzkoveNaklady_ + linkedListTrasaVozidla_->size(); }
	bool dokazeNalozitZasielku(Zasielka* zasielka) { return nosnost_ - zasielka->getHmotnost() >= 0; }

	bool prechadzaPrekladiskom(Prekladisko* prekladiskoKtorymMaPrechadzat) {
		for (Prekladisko * prekladiskoKtorymPrechadza : *linkedListTrasaVozidla_)
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
		for (Prekladisko* prekladisko : *linkedListTrasaVozidla_)
		{
			std::cout << " -> " << prekladisko->dajRegion();
		}
		std::cout << std::endl;
	}

	void pridajZasielku(Zasielka* zasielka) {
		nosnost_ -= zasielka->getHmotnost();
		arrayListZasielok_->add(zasielka);
	}

private:
	int prevadzkoveNaklady_;
	std::string datumaCasEvidencie_;
	std::string SPZ_ = "ZA_";
	double naklady_ = 0;
	double nosnost_;
	structures::LinkedList<Prekladisko *> * linkedListTrasaVozidla_;
	structures::ArrayList<Zasielka *> * arrayListZasielok_;
};

