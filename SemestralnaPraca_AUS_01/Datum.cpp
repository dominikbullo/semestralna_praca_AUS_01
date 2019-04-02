#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include <iostream>
#include <ctime>
#include "Datum.h"

Datum* Datum::instance = 0;
time_t now_ = time(0);
std::string Datum::datum_a_cas_ = time_t_to_string(now_);

void Datum::posunCas(int pocetSekund)
{
	time_t pom = string_to_time_t(datum_a_cas_);
	pom += pocetSekund;
	datum_a_cas_ = time_t_to_string(pom);
}

std::string Datum::time_t_to_string(time_t t)
{
	// TODO posun èasu robí zlobu ? žeby ?
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d/%m/%Y - %H:%M");
	auto str = oss.str();
	return str;
}

time_t Datum::string_to_time_t(std::string s)
{
	int dd, month, yy, hh, mm;
	struct tm when = { 0 };

	sscanf_s(s.c_str(), "%d/%d/%d - %d:%d", &dd, &month, &yy, &hh, &mm);

	when.tm_year = yy - 1900;
	when.tm_mon = month - 1;;
	when.tm_mday = dd;
	when.tm_hour = hh - 1;
	when.tm_min = mm;

	return mktime(&when);
}

void Datum::posunCasNaUrcituHodinu(eOtvoracieHodiny celaHodina)
{
	time_t aktualnyCas = Datum::getAktualnyDatumaCasAsTime();
	tm *ltm = localtime(&aktualnyCas);

	struct tm ziadanyCas = *ltm;
	ziadanyCas.tm_hour = (int)celaHodina; ;
	ziadanyCas.tm_min = 00;

	datum_a_cas_ = time_t_to_string(mktime(&ziadanyCas));

}
Datum::Datum()
{
}
