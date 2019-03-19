#pragma once

#include "forward_star_graph.h"

namespace structures
{
	/// <summary>
	/// Obojsmerna hviezda. Je tvorena vrcholom, zoznamom vsetkych hran, ktore z neho vychadzaju,
	/// a zoznamom vsetkych hran, ktore do neho vchadzaju.
	/// </summary>
	class GraphVertexBiStar : public GraphVertexForwardStar
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude obojsmerna hviezda nachadzat. </param>
		/// <param name = "vertexId"> Id vrcholu hviezdy. </param>
		/// <param name = "forwardEdges"> Tabulka, v ktorej sa budu uchovavat smerniky na hrany vychadzajuce z vrcholu s danym id. </param>
		/// <param name = "backwardEdges"> Tabulka, v ktorej sa budu uchovavat smerniky na hrany vstupujuce do vrcholu s danym id. </param>
		GraphVertexBiStar(const Graph* graph, int vertexId, Table<GraphVertex*, GraphEdge*>* forwardEdges, Table<GraphVertex*, GraphEdge*>* backwardEdges);
		
		/// <summary> Destruktor. </summary>
		virtual ~GraphVertexBiStar() override;

		/// <summary> Operacia klonovania. Vytvori a vrati ciastocny duplikat obojsmernej hviezdy. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude nachadzat vytvoreny klon obojsmernej hviezdy. </param>
		/// <returns> Ukazovatel na klon obojsmernej hviezdy. </returns>
		/// <remarks> Metoda vytvara klon s prazdnymi zoznamami hran. </remarks>
		virtual GraphElement * clone(const Graph* graph) const override;

		/// <summary> Explicitne zakazanie operatora priradenia. </summary>
		/// <remarks> Nad obojsmernou hviezdou nie je mozne definovat operator priradenia. </remarks>
		GraphVertexBiStar & operator=(const GraphVertexBiStar & other) = delete;

		/// <summary> Zisti, ci do vrchola hviezdy vstupuje hrana zacinajuca v danom vrchole. </summary>
		/// <param name = "beginVertex"> Smernik na zaciatocny vrchol hrany. </param>
		/// <returns> true, ak do vrchola hviezdy vstupuje hrana zacinajuca v danom vrchole, false inak. </returns>
		bool containsBackwardEdge(GraphVertex* beginVertex);

		/// <summary> Pokusi sa vlozit do hviezdy orientovanu hranu vstupujucu do vrchola hviezdy. </summary>
		/// <param name = "edge"> Smernik na vkladanu hranu. </param>
		/// <returns> true, ak sa hranu podarilo vlozit, false inak. </returns>
		/// <remarks>
		/// Hranu sa nepodari vlozit v pripade, ak je koncovy vrchol hrany rozny od vrchola tejto hviezdy
		/// alebo ak sa dana hrana uz nachadza v zozname hran vstupujucich do vrchola hviezdy.
		/// </remarks>
		bool tryInsertBackwardEdge(GraphEdge* edge);

		/// <summary> Pokusi sa odstranit z hviezdy orientovanu hranu vstupujucu do vrchola hviezdy. </summary>
		/// <param name = "edge"> Smernik na odstranovanu hranu. </param>
		/// <returns> true, ak sa hranu podarilo odstranit, false inak. </returns>
		/// <remarks>
		/// Hranu sa nepodari odstranit v pripade, ak je koncovy vrchol hrany rozny od vrchola tejto hviezdy
		/// alebo ak sa dana hrana nenachadza v zozname hran vstupujucich do vrchola hviezdy.
		/// </remarks>
		bool tryRemoveBackwardEdge(GraphEdge* edge);

		/// <summary> Odstrani z hviezdy orientovanu hranu vstupujucu do vrchola hviezdy. </summary>
		/// <param name = "beginVertex"> Smernik na pociatocny vrchol odstranovanej hrany. </param>
		/// <returns> Smernik na hranu, ktora zacina v danom vrchole a konci vo vrchole tejto hviezdy. </returns>
		/// <exception cref="std::logic_error">
		/// Vyhodena, ak sa vo hviezde nenachadza hrana zacinajuca
		/// v danom vrchole a konciaca vo vrchole tejto hviezdy.
		/// </exception>  
		GraphEdge* removeBackwardEdge(GraphVertex* beginVertex);

		/// <summary> Odstrani a adresou vrati zoznam vsetkych hran vstupujucich do vrchola hviezdy. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany vstupujuce do vrchola hviezdy. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany vstupujuce do vrchola hviezdy. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		List<GraphEdge*>& removeBackwardEdges(List<GraphEdge*>& list);

		/// <summary> Vrati orientovanu hranu zacinajucu v danom vrchole. </summary>
		/// <param name = "beginVertex"> Smernik na pociatocny vrchol hladanej hrany. </param>
		/// <returns> Smernik na hranu, ktora zacina v danom vrchole a konci vo vrchole tejto hviezdy. </returns>
		/// <exception cref="std::logic_error">
		/// Vyhodena, ak sa vo hviezde nenachadza hrana zacinajuca
		/// v danom vrchole a konciaca vo vrchole tejto hviezdy.
		/// </exception>  
		GraphEdge* getBackwardEdge(GraphVertex* beginVertex);

		/// <summary> Adresou vrati zoznam vsetkych hran vstupujucich do vrchola hviezdy. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany vstupujuce do vrchola hviezdy. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany vstupujuce do vrchola hviezdy. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		List<GraphEdge*>& getBackwardEdges(List<GraphEdge*>& list);

	protected:
		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Obojsmerna hviezda, z ktorej sa prevezmu vlastnosti. </param>
		/// <remarks> Konstruktor vytvara kopiu, ktora ma prazdne zoznamy hran vychadzajucich a vstupujucich do vrchol hviezdy. </remarks>
		GraphVertexBiStar(const GraphVertexBiStar &other);

	protected:
		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju hrany vstupujuce do vrchola hviezdy. </summary>
		/// <remarks>
		/// Klucom je adresa pociatocneho vrchola hrany vstupujucej do vrchola hviezdy.
		/// Hodnotou je smernik na prislusnu hranu.
		/// </remarks>
		Table<GraphVertex*, GraphEdge*> *backwardEdges_;
	};


	/// <summary> Graf implementovany ako zoznam obojsmernych hviezd. </summary>
	class BiStarGraph : public ForwardStarGraph
	{
	public:
		/// <summary> Konstruktor. </summary>
		BiStarGraph();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Graf typu BiStarGraph, z ktoreho sa prevezmu vlastnosti. </param>
		BiStarGraph(const BiStarGraph & other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury (grafu typu BiStarGraph). </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure * clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf typu ForwardStarGraph, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu BiStarGraph. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual ForwardStarGraph & operator=(const ForwardStarGraph & other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf typu BiStarGraph, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		virtual BiStarGraph & operator=(const BiStarGraph & other);

		/// <summary> Vytvori vrchol s danym id v grafe. </summary>
		/// <param name = "vertexId"> Id vytvaraneho vrcholu. </param>
		/// <returns> Smernik na vytvoreny vrchol. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id uz existuje. </exception>  
		virtual GraphVertex* createVertex(int vertexId) override;

		/// <summary> Odstrani z grafu vrchol s danym id a vsetky hrany s nim incidentne. </summary>
		/// <param name = "vertexId"> Id ruseneho vrcholu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id neexistuje. </exception>  
		virtual void removeVertex(int vertexId) override;

		/// <summary> Vytvori orientovanu hranu v grafe. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <returns> Smernik na vytvorenu hranu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak aspon jeden z vrcholov v grafe neexistuje. </exception>  
		virtual GraphEdge* createEdge(int beginVertexId, int endVertexId) override;

		/// <summary> Odstrani z grafu hranu. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dana hrana neexistuje. </exception>  
		virtual void removeEdge(int beginVertexId, int endVertexId) override;

		/// <summary> Adresou vrati zoznam vsetkych hran konciacich v danom vrchole. </summary>
		/// <param name = "vertexId"> Id vrcholu, ktoreho predchodcov chceme ziskat. </param>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany konciace v danom vrchole. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany konciace v danom vrchole. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getPredecessors(int vertexId, List<GraphEdge*>& list) override;
	};
}
