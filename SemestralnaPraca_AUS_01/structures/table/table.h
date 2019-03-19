#pragma once

#include "../structure.h"
#include "../structure_iterator.h"

namespace structures
{
	/// <summary> Prvok tabulky. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TableItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TableItem(K key, T data);

		/// <summary> Getter atributu kluc. </summary>
		/// <returns> Kluc. </returns>
		K getKey();
	private:
		/// <summary> Kluc prvku. </summary>
		K key_;
	};

	/// <summary> Tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T> 
	class Table : public Structure, public Iterable<TableItem<K, T>*>
	{
	public:
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		virtual size_t size() const = 0;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (tabulka), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je tabulka. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		virtual Table<K, T>& operator=(const Table<K, T>& other) = 0;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>  
		virtual T& operator[](const K key) = 0;

		/// <summary> Vrati hodnotou data s daynm klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Hodnota dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do zoznamu. </exception>  
		virtual const T operator[](const K key) const = 0;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>  
		virtual void insert(const K& key, const T& data) = 0;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		virtual T remove(const K& key) = 0;
		
		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		virtual bool tryFind(const K& key, T& value) = 0;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		virtual bool containsKey(const K& key) = 0;
		
		/// <summary> Vymaze tabulku. </summary>
		virtual void clear() = 0;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		virtual Iterator<TableItem<K, T>*>* getBeginIterator() const = 0;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		virtual Iterator<TableItem<K, T>*>* getEndIterator() const = 0;
	protected:
		/// <summary> Konstruktor. </summary>
		Table();
	};

	template<typename K, typename T>
	inline TableItem<K, T>::TableItem(K key, T data):
		DataItem<T>(data),
		key_(key)
	{
	}

	template<typename K, typename T>
	inline K TableItem<K, T>::getKey()
	{
		return key_;
	}

	template<typename K, typename T>
	inline Table<K, T>::Table():
		Structure(),
		Iterable<TableItem<K, T>*>()
	{
	}

	template<typename K, typename T>
	inline Structure & Table<K, T>::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Table<K, T>&>(other);
		}
		return *this;
	}

}

