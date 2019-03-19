#pragma once

#include "priority_queue_list.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueUnsortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueUnsortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueUnsortedArrayList(const PriorityQueueUnsortedArrayList<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je prioritny front implementovany neutriedenym ArrayList-om. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;

		/// <summary> Operator priradenia pre prioritny front implementovany neutriedenym ArrayList-om. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriedenym ArrayList-om, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueueUnsortedArrayList<T>& operator=(const PriorityQueueUnsortedArrayList<T>& other);

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany neutriednym ArrayList-om prazdny. </exception>  
		T pop() override;
	};

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList(const PriorityQueueUnsortedArrayList<T>& other) :
		PriorityQueueUnsortedArrayList<T>()
	{
		*this = other;
	}

	template<typename T>
	Structure* PriorityQueueUnsortedArrayList<T>::clone() const
	{
		return new PriorityQueueUnsortedArrayList<T>(*this);
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueUnsortedArrayList<T>::operator=(const PriorityQueueList<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueUnsortedArrayList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueUnsortedArrayList<T>& PriorityQueueUnsortedArrayList<T>::operator=(const PriorityQueueUnsortedArrayList<T>& other)
	{
		if (this != &other)
		{
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	void PriorityQueueUnsortedArrayList<T>::push(const int priority, const T & data)
	{
		// TODO 06: PriorityQueueUnsortedArrayList
		throw std::exception("PriorityQueueUnsortedArrayList<T>::push: Not implemented yet.");
	}

	template<typename T>
	inline T PriorityQueueUnsortedArrayList<T>::pop()
	{
		// TODO 06: PriorityQueueUnsortedArrayList
		throw std::exception("PriorityQueueUnsortedArrayList<T>::pop: Not implemented yet.");
	}
}