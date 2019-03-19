#pragma once

#include "graph.h"

namespace structures
{
	/// <summary> Orientovany graf implementujuci registraciu dat. </summary>
	class GraphWithRegistration : public Graph
	{
	public:
		/// <summary> Destruktor. </summary>
		~GraphWithRegistration();
		
		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu GraphWithRegistration. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual Graph & operator=(const Graph & other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf typu GraphWithRegistration, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		virtual GraphWithRegistration & operator=(const GraphWithRegistration & other);

		/// <summary> Zisti, ci v grafe su registrovane data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> true, ak v grafe su registrovane data daneho typu s danym klucom, false inak. </returns>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		virtual bool areDataRegistered(GraphDataType dataType, const GraphData * key) const override;

		/// <summary> Zaregistruje v grafe data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak uz je v grafe registrovany dany typ dat s danym klucom. </exception>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		virtual void registerData(GraphDataType dataType, const GraphData * key) override;

		/// <summary> Odstrani z grafu data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak v grafe nie je registrovany dany typ dat s danym klucom. </exception>
		/// <remarks> 
		///	V ramci metody sa vola nad parametrom key metoda getClassKey().
		/// Metoda odstrani dany typ dat s danym klucom zo vsetkych elementov grafu, ktore ich mozu obsahovat.
		///	</remarks>
		virtual void unregisterData(GraphDataType dataType, const GraphData * key) override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "tableForVertexDataRegistration"> Tabulka, ktora bude uchovavat kluce dat registrovanych pre vrcholy. </param>
		/// <param name = "tableForEdgeDataRegistration"> Tabulka, ktora bude uchovavat kluce dat registrovanych pre hrany. </param>
		GraphWithRegistration(Table<const GraphData*, const GraphData*>* tableForVertexDataRegistration, Table<const GraphData*, const GraphData*>* tableForEdgeDataRegistration);

	private:
		/// <summary> Odstrani z grafu data s danym klucom, ktore su asociovane s vrcholmi grafu. </summary>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> true, ak sa z grafu podarilo odstranit data s danym klucom, false inak. </returns>
		bool tryUnregisterVertexData(const GraphData * key);

		/// <summary> Odstrani z grafu data s danym klucom, ktore su asociovane s hranami grafu. </summary>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> true, ak sa z grafu podarilo odstranit data s danym klucom, false inak. </returns>
		bool tryUnregisterEdgeData(const GraphData * key);
	
	private:
		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju identifikatory registrovanych dat,
		/// ktore su asociovane s vrcholmi grafu.
		/// </summary>
		/// <remarks>
		/// Klucom aj hodnotu je adresa triedy, z ktorej vznikla prislusna instancia dat.
		/// </remarks>
		Table<const GraphData*, const GraphData*> *registeredVertexData_;

		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju identifikatory registrovanych dat,
		/// ktore su asociovane s hranami grafu.
		/// </summary>
		/// <remarks>
		/// Klucom aj hodnotu je adresa triedy, z ktorej vznikla prislusna instancia dat.
		/// </remarks>
		Table<const GraphData*, const GraphData*> *registeredEdgeData_;
	};
}