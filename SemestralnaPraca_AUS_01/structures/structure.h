#pragma once

#include "heap_monitor.h"

namespace structures {

	/// <summary> Prvok uchovavajuci data. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	/// <remarks> Pouziva sa ako predok pre vnotorne prvky struktur (napr. zretazeny zoznam, tabulka..). </remarks>
	template <typename T>
	class DataItem
	{
	public:
		/// <summary> Spristupni data. </summary>
		/// <returns> Data. </returns>
		T& accessData();
	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DataItem(const T& data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok uchovavajuci data, z ktoreho sa prevezmu vlastnosti. </param>
		DataItem(const DataItem<T>& other);

		/// <summary> Destruktor. </summary>
		virtual ~DataItem();
	private:
		/// <summary> Data. </summary>
		T data_;
	};

	/// <summary> Abstraktny predok kazdej udajovej struktury. </summary>
	class Structure 
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~Structure();

		/// <summary> Priradovaci operator. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		virtual Structure& operator=(const Structure& other) = 0;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0; 
    
		/// <summary> Zisti, ci je struktura prazdna. </summary>
		/// <returns> true, ak je struktura prazdna, false inak. </returns>
		/// <remarks> Vyuziva metodu size(), co moze byt v niektorych strukturach neefektivne. Take struktury by tuto metodu mali predefinovat. </remarks>
		virtual bool isEmpty() const; 

		/// <summary> Vrati velkost udajovej struktury. </summary>
		/// <returns> Velkost udajovej struktury. </returns>
		virtual size_t size() const = 0;
	protected:
		/// <summary> Implicitny konstruktor. </summary>
		Structure();
	};

	template<typename T>
	inline T & DataItem<T>::accessData()
	{
		return data_;
	}

	template<typename T>
	inline DataItem<T>::DataItem(const T& data) :
		data_(data)
	{
	}

	template<typename T>
	inline DataItem<T>::DataItem(const DataItem<T>& other) :
		DataItem(other.data_)
	{
	}

	template<typename T>
	inline DataItem<T>::~DataItem()
	{
	}

}

