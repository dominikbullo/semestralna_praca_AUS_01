#pragma once

#include "ds_structure_types.h"

namespace structures {

	/// <summary> 
	/// Kniznicna trieda obsahujuca rutinne metody pre pracu s pamatou.
	/// </summary>
	class MemoryRoutines
	{
	public:
		/// <summary> MAximalna hodnota byte-u. </summary>
		const static byte MAX_BYTE = 255;

		/// <summary> Nastavi vsetky bity v byte na 1. </summary>
		/// <param name = "B"> Byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteSet(byte& B);

		/// <summary> Nastavi vsetky bity v byte na 0. </summary>
		/// <param name = "B"> Byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteReset(byte& B);

		/// <summary> Vykona operaciu XOR nad bytom. </summary>
		/// <param name = "B"> Byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteXOR(byte& B);

		/// <summary> Posunie byte o 1 dolava. </summary>
		/// <param name = "B"> Byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteSHL(byte& B);

		/// <summary> Posunie byte o 1 doprava. </summary>
		/// <param name = "B"> Byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteSHR(byte& B);

		/// <summary> Vrati hodnotu n-teho bitu v byte. </summary>
		/// <param name = "B"> Byte. </param>
		/// <param name = "n"> Poradie bitu v byte. </param>
		/// <returns> Hodnota n-teho bitu v byte. </returns>
		static bool byteNthBitGet(byte& B, int n);

		/// <summary> Nastavi hodnotu n-teho bitu v byte na 0. </summary>
		/// <param name = "B"> Byte. </param>
		/// <param name = "n"> Poradie bitu v byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteNthBitTo0(byte& B, int n);

		/// <summary> Nastavi hodnotu n-teho bitu v na 1. </summary>
		/// <param name = "B"> Byte. </param>
		/// <param name = "n"> Poradie bitu v byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteNthBitTo1(byte& B, int n);

		/// <summary> Prepne hodnotu n-teho bitu v byte (teda z 0 na 1 a opacne). </summary>
		/// <param name = "B"> Byte. </param>
		/// <param name = "n"> Poradie bitu v byte. </param>
		/// <returns> Upraveny byte. </returns>
		static byte& byteNthBitToggle(byte& B, int n);
	private:
		/// <summary> Sukromny konstruktor znemoznuje vytvorenie instancie kniznicnej triedy. </summary>
		MemoryRoutines();
	};

}

