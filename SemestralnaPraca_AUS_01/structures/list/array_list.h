#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"

namespace structures
{

	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(const ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		ArrayList<T>& operator=(const ArrayList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(const ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			const ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList() :
		// NOTE: prázdny ArrayList
		List(), // konštruktor predka
		array_(new Array<T>(4)), // definovať atribúty - 4 -> ľubovoľné -> podľa účelu zoznamu
		size_(0)
	{
	}

	template<typename T>
	// NOTE: implicitný -> 1 blok -> 1 adresa
	// kopírovací konštruktor
	inline ArrayList<T>::ArrayList(const ArrayList<T>& other) :
		List(),
		array_(new Array<T>(*other.array_)), // kópia poľa druhého arraylistu
		size_(other.size_) //nastavím si veľkosť kópie
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		// nutné
		delete array_;

		// dobrovoľné
		array_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Structure * ArrayList<T>::clone() const
	{
		return new ArrayList<T>(*this);
	}

	template<typename T>
	inline size_t ArrayList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
	{
		if (this != &other)
		{
			delete array_;
			array_ = new Array<T>(*other.array_);
			size_ = other.size_;
		}
		return *this;
	}

	template<typename T>
	inline T & ArrayList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Index out of range in ArrayList");
		return (*array_)[index];
	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Index out of range in ArrayList");
		return (*array_)[index];
	}

	template<typename T>
	inline void ArrayList<T>::add(const T & data)
	{
		// NOTE: pridávam prvky na koniec

		// pridávam do toho istého, až kým nemusím zväčšiť pole
		if (array_->size() == size_)
		{
			enlarge();
		}
		//size nie je in a využívam hranaté zátvorky na poli, kde očakávam int
		(*array_)[static_cast<int>(size_++)] = data;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T & data, const int index)
	{
		// NOTE: kdekoľvek
		if (index == static_cast<int>(size_))
		{
			ArrayList<T>::add(data);
		}
		else
		{
			DSRoutines::rangeCheckExcept(index, size_ + 1, "Index out of range in ArrayList");

			//ak mám pole plné, tak zo zväčším
			if (array_->size() == size_)
			{
				enlarge();
			}
			// kopírujem všetko po index
			// posuniem do prava pole akokeby
			Array<T>::copy((*array_), index, (*array_), index + 1, static_cast<int>(size_) - index);
			// vyplní údaje, ktoré som chcel
			(*array_)[index] = data;
			//zväčším size
			size_++;
		}

	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T & data)
	{
		// NOTE: vymaže prvý výskyt prvku, ak existuje

		int index = getIndexOf(data);
		// ak ho nájdem tak ho vymažem a vŕatim true
		if (index != -1)
		{
			removeAt(index);
			return true;
		}
		// inak vrátim false
		return false;
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index)
	{
		// FIXME: zmenšiť pole ? alebo nie ?
		// NOTE: moŽno ak je veľké množstvo voľného priestoru


		DSRoutines::rangeCheckExcept(index, static_cast<int>(size_), "Index out of range in ArrayList");
		T temp = (*array_)[index];
		// posuniem doľava pole akokeby
		Array<T>::copy(*array_, index + 1, *array_, index, static_cast<int>(size_) - index - 1);
		// zmenším size a vrátim
		size_--;
		// tie ostatné ma nezaujíma -> aj keď tam je bordel
		return temp;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T & data)
	{
		// lineárna zložitosť, prehľadávam všetky prvky, môžem si dovoliť -> rýchle
		for (int index = 0; index < static_cast<int>(size_); index++)
		{
			if ((*array_)[index] == data)
			{
				return index;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const
	{
		return new ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const
	{
		return new ArrayList<T>::ArrayListIterator(this, static_cast<int>(size_));
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		// zväčším pole o dvojnásobok
		Array<T>* newArray = new Array<T>(size_ * 2);
		Array<T>::copy(*array_, 0, *newArray, 0, static_cast<int>(size_));
		delete array_;
		array_ = newArray;

	}
	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		position_ = 0;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other)
	{
		if (this != &other)
		{
			const ArrayList<T>::ArrayListIterator temp = dynamic_cast<const ArrayList<T>::ArrayListIterator &>(other);
			this->arrayList_ = temp.arrayList_;
			this->position_ = temp.position_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T>& other)
	{
		const ArrayList<T>::ArrayListIterator temp = dynamic_cast<const ArrayList<T>::ArrayListIterator &>(other);
		return position_ != temp.position_;
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*()
	{
		return (*arrayList_)[position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		position_++;
		return *this;
	}
}