#pragma once

#include "stack.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Explicitny zasobník. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
	template<typename T>
	class ExplicitStack : public Stack<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ExplicitStack();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Explicitny zasobník, z ktoreho sa prevezmu vlastnosti. </param>
		ExplicitStack(const ExplicitStack<T>& other);

		/// <summary> Destruktor. </summary>
		~ExplicitStack();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zasobnika. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zasobniku. </summary>
		/// <returns> Pocet prvkov v zasobniku. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		Stack<T>& operator=(const Stack<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		ExplicitStack<T>& operator=(const ExplicitStack<T>& other);

		/// <summary> Vymaze zasobnik. </summary>
		void clear() override;

		/// <summary> Prida prvok do zasobnika. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		const T peek() const override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany zasobnik. </summary>
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitStack<T>::ExplicitStack() :
		Stack(),
		list_(new LinkedList<T>())
	{
	}

	template<typename T>
	ExplicitStack<T>::ExplicitStack(const ExplicitStack<T>& other) :
		ExplicitStack()
	{
		*this = other;
	}

	template<typename T>
	ExplicitStack<T>::~ExplicitStack()
	{
		// TODO 05: ExplicitStack
	}

	template<typename T>
	inline Stack<T>& ExplicitStack<T>::operator=(const Stack<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ExplicitStack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitStack<T>& ExplicitStack<T>::operator=(const ExplicitStack<T>& other)
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	inline Structure * ExplicitStack<T>::clone() const
	{
		return new ExplicitStack<T>(*this);
	}

	template<typename T>
	size_t ExplicitStack<T>::size() const
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline void ExplicitStack<T>::clear()
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::clear: Not implemented yet.");
	}

	template<typename T>
	inline void ExplicitStack<T>::push(const T& data)
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::push: Not implemented yet.");
	}

	template<typename T>
	inline T ExplicitStack<T>::pop()
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::pop: Not implemented yet.");
	}

	template<typename T>
	inline T& ExplicitStack<T>::peek()
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::peek: Not implemented yet.");
	}

	template<typename T>
	inline const T ExplicitStack<T>::peek() const
	{
		// TODO 05: ExplicitStack
		throw std::exception("ExplicitStack<T>::peek: Not implemented yet.");
	}
}