#pragma once

namespace structures
{

	template<typename T>
	class StructureIterator;

	template<typename T>
	class Iterator;

	/// <summary> Abstraktny predok pre iterovatelne udajove struktury. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strukture. </typepram>
	template<typename T>
	class Iterable
	{
	public:
		/// <summary> Vrati iterator na zaciatok struktury. </summary>
		/// <typeparam name = "T"> Typ dat ukladanych v strukture. </typepram>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Je navrhnuta podla vzoru RIII, spolupracuje s metodou getBeginIterator() pre zabezpecenie polymorfizmu. </remarks>
		StructureIterator<T> begin() const;
		
		/// <summary> Vrati iterator na koniec struktury. </summary>
		/// <typeparam name = "T"> Typ dat ukladanych v strukture. </typepram>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Je navrhnuta podla vzoru RIII, spolupracuje s metodou getEndIterator() pre zabezpecenie polymorfizmu. </remarks>
		StructureIterator<T> end() const;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		virtual Iterator<T>* getBeginIterator() const = 0;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		virtual Iterator<T>* getEndIterator() const = 0;
	};

	/// <summary> RIII obalka nad iteratorom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strukture, ktore iterator spristupnuje. </typepram>
	/// <remarks> Trieda je navrhnuta podla vzoru Proxy pre Iterator. Vyuziva RIII. </remarks>
	template<typename T>
	class StructureIterator
	{
	private:
		/// <summary> Spravovany iterator. </summary>
		Iterator<T>* iterator_;
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "iterator"> Iterator, ktory spravuje. </param>
		StructureIterator(Iterator<T>* iterator);

		/// <summary> Destruktor. Postara sa o zrusenie spravovaneho iteratora. </summary>
		virtual ~StructureIterator();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> StructureIterator, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento iterator nachadza po priradeni. </returns>
		StructureIterator<T>& operator=(const StructureIterator<T>& other);

		/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
		/// <param name = "other"> Druhy iterator. </param>
		/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
		/// <remarks> Volanie deleguje na virtualne metody iteratorov spravovanych obomi zucastnenymi RIII obalkami StructureIterator. </remarks>
		bool operator!=(const StructureIterator<T>& other);
		
		/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
		/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
		/// <remarks> Volanie deleguje na virtualnu metodu iteratora spravovaneho touto RIII obalkou StructureIterator. </remarks>
		const T operator*();
		
		/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
		/// <returns> Vrati seba. </returns>
		/// <remarks> 
		/// Volanie deleguje na virtualnu metodu iteratora spravovaneho touto RIII obalkou StructureIterator. 
		/// V pripade potreby upravi hodnotu spravovaneho iteratora.
		/// </remarks>
		const StructureIterator<T>& operator++();
	};

	/// <summary> Iterator nad strukturou. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strukture, ktore iterator spristupnuje. </typepram>
	template<typename T>
	class Iterator
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~Iterator();

		/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
		/// <param name = "other"> Druhy iterator. </param>
		/// <returns> Vrati seba po priradeni. </returns>
		virtual Iterator<T>& operator=(const Iterator<T>& other) = 0;

		/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
		/// <param name = "other"> Druhy iterator. </param>
		/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
		virtual bool operator!=(const Iterator<T>& other) = 0;

		/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
		/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
		virtual const T operator*() = 0;

		/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
		/// <returns> Iterator na dalsi prvok v strukture. </returns>
		/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
		virtual Iterator<T>& operator++() = 0;
	};

	template<typename T>
	inline StructureIterator<T> Iterable<T>::begin() const
	{
		return StructureIterator<T>(getBeginIterator());
	}

	template<typename T>
	inline StructureIterator<T> Iterable<T>::end() const
	{
		return StructureIterator<T>(getEndIterator());
	}

	template<typename T>
	inline StructureIterator<T>::StructureIterator(Iterator<T>* iterator):
		iterator_(iterator)
	{
	}

	template<typename T>
	StructureIterator<T>::~StructureIterator()
	{
		delete iterator_;
	}

	template<typename T>
	inline StructureIterator<T>& StructureIterator<T>::operator=(const StructureIterator<T>& other)
	{
		*iterator_ = *other.iterator_;
		return *this;
	}

	template<typename T>
	inline bool StructureIterator<T>::operator!=(const StructureIterator<T>& other)
	{
		return *iterator_ != *other.iterator_;
	}

	template<typename T>
	inline const T StructureIterator<T>::operator*()
	{
		return **iterator_;
	}

	template<typename T>
	inline const StructureIterator<T>& StructureIterator<T>::operator++()
	{
		Iterator<T>* iterator = &(++*iterator_);
		if (*iterator != *iterator_)
		{
			delete iterator_;
			*iterator_ = *iterator;
		}
		return *this;
	}

	template<typename T>
	inline Iterator<T>::~Iterator()
	{
	}

}