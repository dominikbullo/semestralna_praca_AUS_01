#pragma once

#include "priority_queue_list.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym LinkedList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueLinkedList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym LinkedList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueLinkedList(const PriorityQueueLinkedList<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je prioritny front implementovany neutriednym LinkedList-om. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;

		/// <summary> Operator priradenia pre prioritny front implementovany neutriednym LinkedList-om. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym LinkedList-om, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueueLinkedList<T>& operator=(const PriorityQueueLinkedList<T>& other);

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym LinkedList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(const int priority, const T& data) override;
	};

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList() :
		PriorityQueueList(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList(const PriorityQueueLinkedList<T>& other) :
		PriorityQueueLinkedList<T>()
	{
		*this = other;
	}

	template<typename T>
	inline Structure * PriorityQueueLinkedList<T>::clone() const
	{
		return new PriorityQueueLinkedList(*this);
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueLinkedList<T>::operator=(const PriorityQueueList<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueLinkedList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueLinkedList<T>& PriorityQueueLinkedList<T>::operator=(const PriorityQueueLinkedList<T>& other)
	{
		if (this != &other)
		{
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	inline void PriorityQueueLinkedList<T>::push(const int priority, const T & data)
	{
		// TODO 06: PriorityQueueLinkedList
		throw std::exception("PriorityQueueLimitedSortedArrayList<T>::push: Not implemented yet.");
	}
}