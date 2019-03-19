#pragma once

#include "../structure.h"

namespace structures
{
	/// <summary> Front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class Queue : public Structure
	{
	public:
		/// <summary> Destruktor. </summary>
		~Queue();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (front), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je front. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		virtual Queue<T>& operator=(const Queue<T>& other) = 0;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		virtual size_t size() const = 0;

		/// <summary> Vymaze front. </summary>
		virtual void clear() = 0;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <remarks> Operacia moze vyhodit vynimku v pripade frontu s pevnou kapacitou. </remarks>
		virtual void push(const T& data) = 0;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		virtual T pop() = 0;

		/// <summary> Vrati prvok frontu. </summary>
		/// <returns> Prvok frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		virtual T& peek() = 0;

		/// <summary> Vrati prvok frontu. </summary>
		/// <returns> Prvok frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		virtual const T peek() const = 0;

	protected:
		/// <summary> Konstruktor. </summary>
		Queue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Front, z ktoreho sa prevezmu vlastnosti. </param>
		Queue(const Queue<T> &other);
	};

	template<typename T>
	inline Queue<T>::~Queue()
	{
	}

	template<typename T>
	inline Structure & Queue<T>::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Queue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Queue<T>::Queue() :
		Structure()
	{
	}

	template<typename T>
	inline Queue<T>::Queue(const Queue<T>& other)
	{
	}
}