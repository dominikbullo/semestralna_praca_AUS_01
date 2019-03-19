#pragma once

#include "../structure.h"

namespace structures
{
	/// <summary> Zasobník. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
	template<typename T>
	class Stack : public Structure
	{
	public:
		/// <summary> Konstruktor. </summary>
		Stack();

		/// <summary> Destruktor. </summary>
		~Stack();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (zasobnik), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je zasobnik. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		virtual Stack<T>& operator=(const Stack<T>& other) = 0;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov v zasobniku. </summary>
		/// <returns> Pocet prvkov v zasobniku. </returns>
		size_t size() const = 0;

		/// <summary> Vymaze zasobnik. </summary>
		virtual void clear() = 0;

		/// <summary> Prida prvok do zasobnika. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		virtual void push(const T& data) = 0;

		/// <summary> Odstrani prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		virtual T pop() = 0;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		virtual T& peek() = 0;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		virtual const T peek() const = 0;
	};

	template<typename T>
	inline Structure & Stack<T>::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Stack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Stack<T>::Stack() :
		Structure()
	{
	}

	template<typename T>
	inline Stack<T>::~Stack()
	{
	}
}