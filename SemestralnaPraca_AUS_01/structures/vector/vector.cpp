#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {
	// NOTE: void* -> smerník na všetko - všeobecný -> neviem aký je veľký -> veľkosť udržiavam v extra atribúte	
	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)), // preferujem calloc, aby som tam mal len nuly
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		//kopírovací konštruktor
		//skopíruje pamäť na iné miesto
		memcpy(memory_, other.memory_, other.size_);
	}

	// NOTE: Domáce zadanie 1 - "move" sémantika pre triedu Vector
	Vector::Vector(Vector && other)
	{
		this->memory_ = other.memory_;
		this->size_ = other.size_;
		other.memory_ = nullptr;
	}

	Vector::~Vector()
	{
		//deštruktor
		free(memory_); //uvoľním pamäť
		memory_ = NULL; //poupratujem (optional, but good)
		size_ = 0; //poupratujem (optional, but good)
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other) //nikdy nepriraďujem sám sebe
		{
			this->size_ = other.size_;
			this->memory_ = realloc(this->memory_, this->size_);
			memcpy(memory_, other.memory_, other.size_);
		}
		return *this;
	}

	// NOTE: Domáce zadanie 1 - "move" sémantika pre triedu Vector
	Vector & Vector::operator=(Vector && other)
	{
		this->memory_ = other.memory_;
		other.memory_ = nullptr;
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{	//nechcem tam mať ify -> operácia navyše -> takto rovno vatim výsledo niečoho
		return this->size_ == other.size_ && memcmp(this->memory_, other.memory_, this->size_) == 0;
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Invalid index in Vector");
		//nedá sa posúvaď lebo je to smerník na void, takže neviem koľko má
		//poviem smerníku, nech sa tvári ako byte -- pretypujem -- , a potom sa posúvaj ↓

		// ZAPISUJEM takto
		// return *(reinterpret_cast<byte*>(memory_) + index);
		// ale na to už mám metódu
		return *this->getBytePointer(index);
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Invalid index in Vector");
		//nedá sa posúvaď lebo je to smerník na void, takže neviem koľko má
		//poviem smerníku, nech sa tvári ako byte -- pretypujem -- , a potom sa posúvaj ↓

		// ZAPISUJEM takto
		// return *(reinterpret_cast<byte*>(memory_) + index);
		// ale na to už mám metódu
		return *this->getBytePointer(index);
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Invalid index in Vector");
		// nevyhoda void, ze nemozem scitat s indexom, tak reinterpret_cast pretypovanie smernikov
		return (reinterpret_cast<byte*>(memory_) + index); //vráti adresu
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector");
		// Keď je menšie rovné ako koniec -> poriešim size + 1
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid index in Vector");

		if (&dest >= getBytePointer(index) && &dest < getBytePointer(index + count))
		{
			memmove(&dest, getBytePointer(index), count);
		}
		else
		{
			memcpy(&dest, getBytePointer(index), count);
		}
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length > 0)
		{
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index in Vector");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid index in Vector");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid index in Vector");
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid index in Vector");

			if (src.memory_ != dest.memory_)
				memcpy(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
			else
				memmove(reinterpret_cast<byte*>(dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
		}

	}


}
