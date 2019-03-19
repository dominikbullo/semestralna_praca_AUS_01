#pragma once

#include "../Structure.h"
#include "../ds_structure_types.h"
#include <stdexcept>

namespace structures {

	/// <summary> Vektor. </summary>
	class Vector : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori vektor o velkosti size bytov. </summary>
		/// <param name = "size"> Pocet bytov vo vytvorenom vektore. </param>
		Vector(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Zdrojovy vektor. </param>
		Vector(const Vector& other);
		Vector(Vector && other); // Domáce zadanie 1 - "move" sémantika pre triedu Vector

		/// <summary> Destruktor. </summary>
		~Vector();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat vektora. </summary>
		/// <returns> Ukazovatel na vytvoreny klon vektora. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet bytov vo vektore. </summary>
		/// <returns> Pocet bytov vo vektore. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (vektor), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento vektor nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je Vector. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Vektor, z ktoreho sa maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento vektor nachadza po priradeni. </returns>
		Vector& operator=(const Vector& other);
		Vector & operator=(Vector && other); // Domáce zadanie 1 - "move" sémantika pre triedu Vector

		/// <summary> Operator porovnania. </summary>
		/// <param name = "other"> Vektor, s ktorym sa ma porovnat. </param>
		/// <returns> true, ak su vektory rovnake, false inak. </returns>
		bool operator==(const Vector& other) const;

		/// <summary> Vrati adresou byte na indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Adresa byte-u na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception>  
		byte& operator[](const int index);

		/// <summary> Vrati hodnotou byte na indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Hodnota byte-u na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception>  
		byte operator[](const int index) const;

		/// <summary> Precita count bytov od daneho indexu do cielovej adresy dest. </summary>
		/// <param name = "index"> Index byte-u vo vektore, od ktoreho sa zacne citat. </param>
		/// <param name = "count"> Pocet bytov, ktore budu skopirovane z vektora od pozicie index do pamate dest. </param>
		/// <param name = "dest"> Pamat, do ktorej sa bude zapisovat. </param>
		/// <returns> dest. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak pociatocny ani cielovy index nepatria do vektora. </exception> 
		byte& readBytes(const int index, const int count, byte& dest);

		/// <summary> Vrati ukazovatel na byte na danom indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Ukazovatel na byte na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception> 
		byte* getBytePointer(const int index) const;

		/// <summary> Skopiruje length bytov z vektora src od pozicie srcStartIndex do vektora dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojovy vektor. </param>
		/// <param name = "srcStartIndex"> Index byte-u vo vektore src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielovy vektor. </param>
		/// <param name = "destStartIndex"> Index byte-u vo vektore dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet bytov, ktore budu skopirovane z vektora src od pozicie srcStartIndex do vektora dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych vektorov. </exception> 
		static void copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length);

	private:
		/// <summary> Ukazovatel na zaciatok pamate patriacej vektoru. </summary>
		void* memory_;
		/// <summary> Pocet bytov vo vektore. </summary>
		size_t size_;
	};

}