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
		delete list_;
		list_ = nullptr;
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
		if (this != &other)
		{
			*this->list_ = *(other.list_);
		}
		return *this;
	}

	template<typename T>
	inline Structure * ExplicitStack<T>::clone() const
	{
		return new ExplicitStack<T>(*this);
	}

	template<typename T>
	size_t ExplicitStack<T>::size() const
	{
		return list_->size();
	}

	template<typename T>
	inline void ExplicitStack<T>::clear()
	{
		list_->clear();
	}

	template<typename T>
	inline void ExplicitStack<T>::push(const T& data)
	{
		list_->insert(data, 0);
	}

	template<typename T>
	inline T ExplicitStack<T>::pop()
	{
		return list_->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitStack<T>::peek()
	{
		return (*list_)[0];
	}

	template<typename T>
	inline const T ExplicitStack<T>::peek() const
	{
		return (*list_)[0];
	}
}
