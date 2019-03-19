#pragma once

#include "../list/linked_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Zretazena tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class LinkedTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		LinkedTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedTable, z ktorej sa prevezmu vlastnosti. </param>
		LinkedTable(const LinkedTable<K, T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

	};

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable() :
		SequenceTable<K, T>(new LinkedList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable(const LinkedTable<K, T>& other) :
		LinkedTable()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline Structure * LinkedTable<K, T>::clone() const
	{
		return new LinkedTable<K, T>(*this);
	}

}