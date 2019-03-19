#pragma once

#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Notifikacny objekt. </summary>
	class SortNotifier
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "notificationPeriod"> Kolko notifikacii neohlasi? </param>
		SortNotifier(int notificationPeriod);

		/// <summary> Ak moze, vyvola notifikaciu. </summary>
		/// <remarks> Notifikaciu vyvola, ked sa vyziadala notificationPeriod krat. </remarks>
		void notify();
	protected:
		/// <summary> Vyvolanie notifikacie. </summary>
		virtual void doNotify() = 0;
	private:
		int notificationPeriod_;
		int currentNotification_;
	};

	/// <summary> Triedenie NonortedSequenceTable navrhnuté ako funkèný objekt. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Sort
	{
	public:
		/// <summary> Konstruktor. </summary>
		Sort();

		/// <summary> Destruktor. </summary>
		virtual ~Sort();

		/// <summary> Funkèný operátor utriedi tabu¾ku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		/// <remarks> Využíva metódu sort. </remarks>
		void operator()(UnsortedSequenceTable<K, T>& table);

		/// <summary> Utriedi tabu¾ku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		virtual void sort(UnsortedSequenceTable<K, T>& table) = 0;

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "sortNotifier"> Funkcny objekt urceny na notifikaciu pokroku v triediacom algoritme. </param>
		void setNotifier(SortNotifier* sortNotifier);
	protected:
		/// <summary> Ak je nastaveny sortNotifier_, tak ho vyvola. </summary>
		void notify();
	private:
		/// <summary> Funkcny objekt urceny na notifikaciu pokroku v triediacom algoritme. </summary>
		SortNotifier* sortNotifier_;
	};

	template<typename K, typename T>
	inline Sort<K, T>::Sort():
		sortNotifier_(nullptr)
	{
	}

	template<typename K, typename T>
	inline Sort<K, T>::~Sort()
	{
		sortNotifier_ = nullptr;
	}

	template<typename K, typename T>
	inline void Sort<K, T>::operator()(UnsortedSequenceTable<K, T>& table)
	{
		sort(table);
	}

	template<typename K, typename T>
	inline void Sort<K, T>::setNotifier(SortNotifier * sortNotifier)
	{
		sortNotifier_ = sortNotifier;
	}

	template<typename K, typename T>
	inline void Sort<K, T>::notify()
	{
		if (sortNotifier_ != nullptr)
		{
			sortNotifier_->notify();
		}
	}
}