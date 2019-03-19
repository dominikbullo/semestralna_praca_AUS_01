#pragma once

#include <string>
#include <vector>
#include "ds_structure_types.h"

namespace structures
{
	/// <summary> 
	/// Kniznicna trieda obsahujuca rutinne metody pre pracu so strukturami.
	/// </summary>
	class DSRoutines
	{
	public:
		/// <summary> Prekonvertuje ADS do ADT. </summary>
		/// <param name = "ads"> Typ abstraktnej datovej struktury. </param>
		/// <returns> Abstraktny datovy typ, do ktoreho patri ADS. </returns>
		/// <exception cref="std::invalid_argument"> Vyhodena, ak ADS nepatri do ziadneho ADT. </exception>  
		static StructureADT convertADStoADT(const StructureADS& ads);

		/// <summary> Skontroluje, ci index patri do intervalu [0, size). </summary>
		/// <param name = "index"> Testovaný index. </param>
		/// <param name = "size"> Pocet prvkov v kolekcii. </param>
		/// <returns> true, ak index patri do intervalu [0, size), false inak. </returns>
		static bool rangeCheck(const int index, const size_t size);

		/// <summary> Skontroluje, ci index patri do intervalu [baseIndex, baseIndex + size). </summary>
		/// <param name = "index"> Testovaný index. </param>
		/// <param name = "baseIndex"> Najnizsi platny index. </param>
		/// <param name = "size"> Pocet prvkov v kolekcii. </param>
		/// <returns> true, ak index patri do intervalu [baseIndex, baseIndex + size), false inak. </returns>
		static bool rangeCheck(const int index, const int baseIndex, const size_t size);

		/// <summary> Skontroluje, ci index patri do intervalu [0, size). Ak nie, vyhodi vynimku std::out_of_range. </summary>
		/// <param name = "index"> Testovaný index. </param>
		/// <param name = "size"> Pocet prvkov v kolekcii. </param>
		/// <param name = "exceptionMessage"> Text vynimky, ktora je vyhodena v pripade chyby. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do intervalu [0, size). </exception>  
		static void rangeCheckExcept(const int index, const size_t size, const std::string exceptionMessage);

		/// <summary> Skontroluje, ci index patri do intervalu [baseIndex, baseIndex + size). Ak nie, vyhodi vynimku std::out_of_range. </summary>
		/// <param name = "index"> Testovaný index. </param>
		/// <param name = "baseIndex"> Najnizsi platny index. </param>
		/// <param name = "size"> Pocet prvkov v kolekcii. </param>
		/// <param name = "exceptionMessage"> Text vynimky, ktora je vyhodena v pripade chyby. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do intervalu [baseIndex, baseIndex + size). </exception> 
		static void rangeCheckExcept(const int index, const int baseIndex, const size_t size, const std::string exceptionMessage);
		
		/// <summary> Vymeni obsah dvoch premennych rovnakeho typu. </summary>
		/// <param name = "a"> Prva premenna. </param>
		/// <param name = "b"> Druha premenna. </param>
		template<typename T>
		static void swap(T& a, T& b) ; 

		/// <summary> Vrati index prvku v kolekcii std::vector. </summary>
		/// <param name = "vector"> vector, v ktorom sa hlada index. </param>
		/// <param name = "item"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku vo vector-e. Ak sa v nom nenachadza, vrati -1. </returns>
		template<typename T>
		static int indexInVector(std::vector<T>&vector, const T& item);

		/// <summary> Vrati hodnotu predstavujucu kladne nekonecno. </summary>
		/// <returns> Hodnota nekonecna. </returns>
		static double getInfinity();
	private:
		/// <summary> Sukromny konstruktor znemoznuje vytvorenie instancie kniznicnej triedy. </summary>
		DSRoutines();

	};

	template<typename T>
	void DSRoutines::swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	inline int DSRoutines::indexInVector(std::vector<T>& vector, const T & item)
	{
		int result = 0;
		for (std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
		{
			if (*it == item)
			{
				return result;
			}
			else
			{
				result++;
			}
		}
		
		return -1;
	}

}
