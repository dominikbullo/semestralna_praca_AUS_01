#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS -> because of time 
#include "Datum.h"
#include <iostream>
#include <ctime>

std::string Datum::datum_ = "01/01/2000";
//Datum* Datum::instance = 0;
time_t now_ = time(0);
tm *ltm_ = localtime(&now_);

// print various components of tm structure.
int year = 1900 + ltm_->tm_year;
int month = 1 + ltm_->tm_mon;
int day = 1 + ltm_->tm_mday;

//std::stringstream msg;
//msg << day << "/" << month << "/" << year;
//msg.str();

//std::string datum_ = day + "/" + month + "/" + year;


void Datum::posunCasoHodinu()
{
	time_t pom = string_to_time_t(datum_);
	pom += 60 * 60;
	datum_ = time_t_to_string(pom);
}

Datum * Datum::get()
{
	return this;
}

std::string Datum::time_t_to_string(time_t t)
{
	char buff[20];
	strftime(buff, 20, "%d/%m/%Y", localtime(&t));
	std::string s(buff);
	return s;
}

time_t Datum::string_to_time_t(std::string s)
{
	int yy, mm, dd;
	struct tm when;
	time_t tme;

	memset(&when, 0, sizeof(struct tm));
	sscanf(s.c_str(), "%d/%d/%d", &dd, &mm, &yy);

	time(&tme);
	when = *localtime(&tme);
	when.tm_year = yy - 1900;
	when.tm_mon = mm - 1;
	when.tm_mday = dd;

	return mktime(&when);
}

Datum::Datum()
{
}
