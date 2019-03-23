#pragma once
#include<string>

#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include "Dron.h"


class Prekladisko
{
public:
	Prekladisko(std::string okres);
	~Prekladisko();
	void pridajDron(Dron * novyDron);
	void vypisZoznamDronov();
	Dron * vyberDrona(double hmotnostZasielky, double vzdialenost);
	void setSerioveCislo();
	std::string dajOkres() {
		return region_;
	}
	inline std::string getSerioveCislo() {
		return serioveCislo_;
	}
private:
	std::string region_;
	std::string serioveCislo_ = region_;
	structures::ArrayList<Dron*> * arrayListDronov;
protected:
	static int unikatneSerioveCislo_;
};

