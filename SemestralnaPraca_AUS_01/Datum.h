#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
class Datum
{
public:
	//static Datum* getInstance()
	//{
	//	if (instance == 0)
	//	{
	//		instance = new Datum();
	//	}

	//	return instance;
	//}

	void posunCasoHodinu();
	Datum* get();
	static std::string getAktualnyDatum() {
		return datum_;
	}
	static std::string time_t_to_string(time_t t); //kontroloval som to pred zmenou na static
	static time_t string_to_time_t(std::string s);
private:

	static std::string datum_;
	//static Datum * instance;
	Datum();
	Datum(Datum const& copy);
	Datum& operator=(Datum const& copy);
};


