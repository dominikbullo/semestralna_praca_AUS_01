#pragma once

#include "../structure.h"

namespace structures
{
	/// <summary> Prvok prioritneho frontu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class PriorityQueueItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "priority"> Priorita dat uchovavanych v prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		PriorityQueueItem(int priority, T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok prioritneho frontu, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueItem(const PriorityQueueItem<T>& other);

		/// <summary> Getter vracajuci hodnotu priority daneho prvku. </summary>
		/// <returns> Priorita daneho prvku. </returns>
		int getPriority();

	private:
		/// <summary> Priorita daneho prvku. </summary>
		int priority_;
	};

	/// <summary> Prioritny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueue : public Structure
	{
	public:
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (prioritny front), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je prioritny front. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueue<T>& operator=(const PriorityQueue<T>& other) = 0;

		/// <summary> Vrati pocet prvkov v prioritnom fronte. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte. </returns>
		virtual size_t size() const = 0;

		/// <summary> Vymaze obsah prioritneho frontu. </summary>
		virtual void clear() = 0;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		virtual void push(const int priority, const T& data) = 0;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>  
		virtual T pop() = 0;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>  
		virtual T& peek() = 0;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>  
		virtual const T peek() const = 0;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>  
		virtual int peekPriority() const = 0;
	protected:
		/// <summary> Konstruktor. </summary>
		PriorityQueue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueue(const PriorityQueue<T>& other);
	};

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(int priority, T data) :
		DataItem<T>(data),
		priority_(priority)
	{
	}

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(const PriorityQueueItem<T>& other) :
		DataItem<T>(other),
		priority_(other.priority_)
	{
	}

	template<typename T>
	inline int PriorityQueueItem<T>::getPriority()
	{
		return priority_;
	}

	template<typename T>
	inline Structure & PriorityQueue<T>::operator=(const Structure & other)
	{
		if (this != &other) {
			*this = dynamic_cast<const PriorityQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline PriorityQueue<T>::PriorityQueue() :
		Structure()
	{
	}

	template<typename T>
	inline PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
	{
	}
}
