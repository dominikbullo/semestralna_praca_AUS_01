#pragma once

#include "structure.h"
#include "ds_structure_types.h"
#include <vector>

namespace structures {

	/// <summary> 
	/// Tovaren na tvorbu instancii udajovych struktur.
	/// Pracuje s vyuzitim vzorov Factory a Prototype.
	/// </summary>
	class ADSFactory
	{
	private:
		/// <summary> Aku ADS vytvara. </summary>
		StructureADS ads_;
		/// <summary> Prototyp vsetkych ADS. </summary>
		Structure* prototype_;
		/// <summary> Vytvorene klony prototypu. </summary>
		std::vector<Structure*>* clones_;
		/// <summary> Celkovy pocet vytvorenych klonov. </summary>
		int totalCreated_;
	public:
		/// <summary> 
		/// Konstruktor vytvori instanciu.
		/// Prevezme prototyp vsetkych struktur, ktore su vytvarane touto triedou.
		/// </summary>
		/// <param name = "ads"> Typ ADS, ktoru tato tovaren vytvara. </param>
		/// <param name = "prototype"> Prototyp pre vytvarane struktury. </param>
		/// <remarks>
		/// Trieda sa postara o zrusenie prototypu.
		/// </remarks>
		ADSFactory(StructureADS ads, Structure* prototype);
		/// <summary> Destruktor zrusi vsetky klony a nasledne zrusi prototyp. </summary>
		~ADSFactory();

		/// <summary> Getter atributu ads_. </summary>
		/// <returns> Hodnota atributu ads_. </returns>
		StructureADS getADS() const;
		/// <summary> Getter atributu totalCreated_. </summary>
		/// <returns> Hodnota atributu totalCreated_. </returns>
		int getTotalCreated() const;

		/// <summary> Vrati strukturu na danom indexe. Ak je index neplatny, vrati nullptr. </summary>
		/// <param name = "index"> Index vytvorenej struktury. </param>
		/// <returns> Vytvorena struktura na danom indexe. </returns>
		Structure* operator[](const int index) const;

		/// <summary> Vrati strukturu na danom indexe. Ak je index neplatny, vrati nullptr. </summary>
		/// <param name = "index"> Index vytvorenej struktury. </param>
		/// <returns> Vytvorena struktura na danom indexe. </returns>
		Structure* at(const int index) const;

		/// <summary> Vrati aktualny pocet klonov. </summary>
		/// <returns> Aktualny pocet klonov. </returns>
		size_t size() const;

		/// <summary> 
		/// Tovarenska metoda pre ziskanie instancie udajovej struktury.
		/// Struktura vznikne klonovanim prototypu.
		/// Klon je automaticky zaregistrovany do tovarne, ktora sa neskor postara o jeho dealokaciu.
		/// </summary>
		/// <returns> Struktura vytvorena klonovanim prototypu. </returns>
		Structure* getStructureInstance();

		/// <summary> 
		/// Metoda pre ziskanie klonu udajovej struktury.
		/// Struktura vznikne klonovanim originalu.
		/// Klon je automaticky zaregistrovany do tovarne, ktora sa neskor postara o jeho dealokaciu.
		/// </summary>
		/// <param name = "original"> Original struktury </param>
		/// <returns> Struktura vytvorena klonovanim originalu. </returns>
		Structure* cloneStructure(Structure* original);

		/// <summary> Odstrani strukturu. </summary>
		/// <param name = "index"> Index odstranenej struktury. </param>
		void removeStructure(const int index);
		/// <summary> Odstrani strukturu. </summary>
		/// <param name = "structure"> Odkaz na strukturu, ktora sa ma odstranit. </param>
		void removeStructure(Structure* structure);
	};

	/// <summary>
	/// Trieda je zodpovedna za vytvaranie struktur pre pozadovane ADT. 
	/// Manazuje zoznam tovarni ADS, ktore vytvaraju jednotlive struktury.
	/// Uchovava zoznam vsetkych struktur, ktore jednotlive ADS tovarne vytvorili.
	/// </summary>
	class ADTFactoryManager
	{
	private: 
		/// <summary> Prepravka na spojenie struktury s jej ADS tovarnou. </summary>
		struct StructureOrigin
		{
			/// <summary> Struktura. </summary>
			Structure* structure;
			/// <summary> Tovaren. </summary>
			ADSFactory* adsFactory;
		};
	private:
		/// <summary> Aky ADT uchovava. </summary>
		StructureADT adt_;
		/// <summary> Tovarne na tvorbu jednotlivych ADS, ktore patria pod ADT. </summary>
		std::vector<ADSFactory*>* adsFactories_;
		/// <summary> Zoznam vsetkych struktur, ktore boli vyprodukovane ADS tovarnami. </summary>
		std::vector<StructureOrigin>* producedStructures_;
	public:
		/// <summary> Vytvori instanciu ADT manazera. </summary>
		/// <param name = "adt"> Typ ADT, ktory tento manazer spravuje. </param>
		ADTFactoryManager(StructureADT adt);
		/// <summary> Destruktor zrusi vsetky tovarne v manazerovi. </summary>
		~ADTFactoryManager();

		/// <summary> Getter atributu adt_. </summary>
		/// <returns> Hodnota atributu adt_. </returns>
		StructureADT getADT() const;

		/// <summary> Vrati vytvorenu strukturu na danom indexe. Ak je index neplatny, vrati nullptr. </summary>
		/// <param name = "index"> Index vytvorenej struktury. </param>
		/// <returns> Vytvorena struktura na danom indexe. </returns>
		Structure* operator[](const int index) const;

		/// <summary> Vrati vytvorenu strukturu na danom indexe. Ak je index neplatny, vrati nullptr. </summary>
		/// <param name = "index"> Index vytvorenej struktury. </param>
		/// <returns> Vytvorena struktura na danom indexe. </returns>
		Structure* at(const int index) const;

		/// <summary> Vrati aktualny pocet vytvorenych struktur. </summary>
		/// <returns> Aktualny pocet klonov. </returns>
		size_t size() const;

		/// <summary> 
		/// Zaregistruje prototyp do prislusnej ADSFactory.
		/// Ak este nema vytvorenu tovaren pre prototyp konkretneho ads, tak ju vytvori.
		/// V opacnom pripade vyhodi vynimku logic_error.
		/// </summary>
		/// <param name = "ads"> ADS tovarne, do ktorej bude prototyp registrovany. </param>
		/// <param name = "prototype"> Prototyp struktur. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak uz existuje tovaren s tymto ads a zaregistrovanym prototypom. </exception>  
		void registerPrototype(StructureADS ads, Structure* prototype);

		/// <summary> 
		/// Tovarenska metoda pre ziskanie instancie konkrenej ADS pomocou prislusnej tovarne. 
		/// Vytvorenu strukturu zaregistruje do seba.
		/// Ak pre ADS neexistuje tovaren, vyhodi vynimku logic_error.
		/// </summary>
		/// <param name = "ads"> Typ tovarne, z ktorej sa vytvori struktura. </param>
		/// <returns> Vytvorena struktura daneho ADS. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak neexistuje tovaren s tymto ads. </exception>  
		Structure* getStructureInstance(StructureADS ads);
		
		/// <summary> Sklonuje strukturu na indexe. </summary>
		/// <param name = "index"> Index sklonovanej struktury. </param>
		Structure* cloneStructureAtIndex(const int index);

		/// <summary> Odstrani strukturu. </summary>
		/// <param name = "index"> Index odstranenej struktury. </param>
		void removeStructure(const int index);

		/// <summary> Vrati ADSFactory na zaklade typu struktur, ktore vytvara. </summary>
		/// <param name = "ads"> Typ vytvaranych struktur. </param>
		/// <returns> ADSFactory vytvarajuce struktury daneho typu. </returns>
		ADSFactory* getADSFactoryByType(const StructureADS ads) const;
		
		/// <summary> Vrati ADSFactory na zaklade jej indexu v manazerovi. </summary>
		/// <param name = "index"> Index ADSFactory v manazerovi. </param>
		/// <returns> ADSFactory. </returns>
		ADSFactory* getADSFactoryByIndex(const int index) const;

		/// <summary> Vrati pocet tovarni struktur. </summary>
		/// <returns> Pocet tovarni struktur. </returns>
		size_t factoriesSize() const;
	};

	/// <summary>
	/// Trieda spravujuce tovarne na tvorbu struktur. 
	/// Navrhnuta podla vzoru Signleton.
	/// </summary>
	class StructureFactory
	{
	private:
		/// <summary> Premenna triedy obsahujuca odkaz na jedinu instanciu triedy. </summary>
		static StructureFactory* factory_;

		/// <summary> Manazery jednodlivych ADT. </summary>
		std::vector<ADTFactoryManager*>* adtManagers_;

		/// <summary> Skryty konsktruktor. Pre vsetky ADT vytvori ich manazera. </summary>
		StructureFactory();
		/// <summary> Destruktor sa postara o uvolneneio vsetkych ADT manazerov. </summary>
		~StructureFactory();
	public:
		/// <summary> Jednoducha tovarenska metoda pre ziskanie instancie jedinacika. </summary>
		/// <returns> Instancia triedy StructureFactory. </returns>
		/// <remarks> Vyuziva Lazy initialization. </remarks>
		static StructureFactory* getInstance();
		/// <summary ></summary>
		/// <summary> Odstrani instanciu jedinacika. </summary>
		static void finalize();

		/// <summary> Zaregistruje prototyp danej ADS. </summary> 
		/// <param name = "ads"> ADS tovarne, do ktorej bude prototyp registrovany. </param>
		/// <param name = "prototype"> Prototyp struktur. </param>
		/// <returns> True, ak registracia prebehla uspesne, false inak.</returns>
		bool registerPrototype(StructureADS ads, Structure* prototype);

		/// <summary>
		/// Tovarenska metoda pre ziskanie instancie konkrenej ADS pomocou prislusneho manazera ADS tovarni.
		/// </summary>
		/// <param name = "ads"> ADS vytvaranej struktury. </param>
		/// <returns> Vytvorena struktura daneho ADS. Ak prislusny ADT manzer neexistuje alebo nebude schopny vytvorit instanciu, vrati nullptr.</returns>
		Structure* getStructureInstance(StructureADS ads);
		
		/// <summary> Vrati ADTManager na zaklade typu struktur, ktore spravuje. </summary>
		/// <param name = "adt"> ADT spravovanych struktur. </param>
		/// <returns> ADTManager na zaklade typu struktur, ktore spravuje. </returns>
		ADTFactoryManager* getADTManagerByType(const StructureADT adt) const;

	};

}

