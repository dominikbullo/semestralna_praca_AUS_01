#pragma once

#include "queue.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Explicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ExplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ExplicitQueue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Explicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ExplicitQueue(const ExplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ExplicitQueue();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat frontu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Queue<T>& operator=(const Queue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		ExplicitQueue<T>& operator=(const ExplicitQueue<T>& other);

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		const T peek() const override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany front. </summary>
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() :
		Queue(),
		list_(new LinkedList<T>())
	{
	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(const ExplicitQueue<T>& other) :
		ExplicitQueue()
	{
		*this = other;
	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue()
	{
		// TODO 05: ExplicitQueue
	}

	template<typename T>
	inline Queue<T>& ExplicitQueue<T>::operator=(const Queue<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ExplicitQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitQueue<T>& ExplicitQueue<T>::operator=(const ExplicitQueue<T>& other)
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	inline Structure * ExplicitQueue<T>::clone() const
	{
		return new ExplicitQueue<T>(*this);
	}

	template<typename T>
	size_t ExplicitQueue<T>::size() const
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline void ExplicitQueue<T>::clear()
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::clear: Not implemented yet.");
	}

	template<typename T>
	inline void ExplicitQueue<T>::push(const T& data)
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::push: Not implemented yet.");
	}

	template<typename T>
	inline T ExplicitQueue<T>::pop()
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::pop: Not implemented yet.");
	}

	template<typename T>
	inline T& ExplicitQueue<T>::peek()
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::peek: Not implemented yet.");
	}

	template<typename T>
	inline const T ExplicitQueue<T>::peek() const
	{
		// TODO 05: ExplicitQueue
		throw std::exception("ExplicitQueue<T>::peek: Not implemented yet.");
	}
}