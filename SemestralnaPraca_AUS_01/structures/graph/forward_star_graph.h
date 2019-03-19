#pragma once

#include "graph_with_registration.h"
#include "../table/table.h"
#include "../list/list.h"

namespace structures
{
	/// <summary> Dopredna hviezda. Je tvorena vrcholom a zoznamom vsetkych hran, ktore z neho vychadzaju. </summary>
	class GraphVertexForwardStar : public GraphVertex
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude dopredna hviezda nachadzat. </param>
		/// <param name = "vertexId"> Id vrcholu hviezdy. </param>
		/// <param name = "forwardEdges"> Tabulka, v ktorej sa budu uchovavat smerniky na hrany vychadzajuce z vrcholu s danym id. </param>
		GraphVertexForwardStar(const Graph* graph, int vertexId, Table<GraphVertex*, GraphEdge*>* forwardEdges);
		
		/// <summary> Destruktor. </summary>
		virtual ~GraphVertexForwardStar() override;

		/// <summary> Operacia klonovania. Vytvori a vrati ciastocny duplikat doprednej hviezdy. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude nachadzat vytvoreny klon doprednej hviezdy. </param>
		/// <returns> Ukazovatel na klon doprednej hviezdy. </returns>
		/// <remarks> Metoda vytvara klon s prazdnym zoznamom hran. </remarks>
		virtual GraphElement * clone(const Graph* graph) const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Vrchol grafu, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento element grafu nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena vzdy. </exception>  
		/// <remarks> Nad doprednou hviezdou nie je mozne definovat operator priradenia. </remarks>
		virtual GraphVertex& operator=(const GraphVertex& other);

		/// <summary> Explicitne zakazanie operatora priradenia. </summary>
		/// <remarks> Nad doprednou hviezdou nie je mozne definovat operator priradenia. </remarks>
		GraphVertexForwardStar & operator=(const GraphVertexForwardStar & other) = delete;

		/// <summary> Zisti, ci z vrchola hviezdy vychadza hrana konciaca v danom vrchole. </summary>
		/// <param name = "endVertex"> Smernik na koncovy vrchol hrany. </param>
		/// <returns> true, ak z vrchola hviezdy vychadza hrana konciaca v danom vrchole, false inak. </returns>
		bool containsForwardEdge(GraphVertex* endVertex);

		/// <summary> Pokusi sa vlozit do hviezdy orientovanu hranu vychadzajucu z vrchola hviezdy. </summary>
		/// <param name = "edge"> Smernik na vkladanu hranu. </param>
		/// <returns> true, ak sa hranu podarilo vlozit, false inak. </returns>
		/// <remarks>
		/// Hranu sa nepodari vlozit v pripade, ak je pociatocny vrchol hrany rozny od vrchola tejto hviezdy
		/// alebo ak sa dana hrana uz nachadza v zozname hran vychadzajucich z vrchola hviezdy.
		/// </remarks>
		bool tryInsertForwardEdge(GraphEdge* edge);

		/// <summary> Pokusi sa odstranit z hviezdy orientovanu hranu vychadzajucu z vrchola hviezdy. </summary>
		/// <param name = "edge"> Smernik na odstranovanu hranu. </param>
		/// <returns> true, ak sa hranu podarilo odstranit, false inak. </returns>
		/// <remarks>
		/// Hranu sa nepodari odstranit v pripade, ak je pociatocny vrchol hrany rozny od vrchola tejto hviezdy
		/// alebo ak sa dana hrana nenachadza v zozname hran vychadzajucich z vrchola hviezdy.
		/// </remarks>
		bool tryRemoveForwardEdge(GraphEdge* edge);

		/// <summary> Odstrani z hviezdy orientovanu hranu vychadzajucu z vrchola hviezdy. </summary>
		/// <param name = "endVertex"> Smernik na koncovy vrchol odstranovanej hrany. </param>
		/// <returns> Smernik na hranu, ktora zacina vo vrchole tejto hviezdy a konci v danom vrchole. </returns>
		/// <exception cref="std::logic_error">
		/// Vyhodena, ak sa vo hviezde nenachadza hrana zacinajuca
		/// vo vrchole tejto hviezdy a konciaca v danom vrchole.
		/// </exception>  
		GraphEdge* removeForwardEdge(GraphVertex* endVertex);

		/// <summary> Odstrani a adresou vrati zoznam vsetkych hran vychadzajucich z vrchola hviezdy. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany vychadzajuce z vrchola hviezdy. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany vychadzajuce z vrchola hviezdy. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		List<GraphEdge*>& removeForwardEdges(List<GraphEdge*>& list);

		/// <summary> Vrati orientovanu hranu konciacu v danom vrchole. </summary>
		/// <param name = "endVertex"> Smernik na koncovy vrchol hladanej hrany. </param>
		/// <returns> Smernik na hranu, ktora zacina vo vrchole tejto hviezdy a konci v danom vrchole. </returns>
		/// <exception cref="std::logic_error">
		/// Vyhodena, ak sa vo hviezde nenachadza hrana zacinajuca
		/// vo vrchole tejto hviezdy a konciaca v danom vrchole.
		/// </exception>  
		GraphEdge* getForwardEdge(GraphVertex* endVertex);

		/// <summary> Adresou vrati zoznam vsetkych hran vychadzajucich z vrchola hviezdy. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany vychadzajuce z vrchola hviezdy. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany vychadzajuce z vrchola hviezdy. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		List<GraphEdge*>& getForwardEdges(List<GraphEdge*>& list);

	protected:
		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Dopredna hviezda, z ktorej sa prevezmu vlastnosti. </param>
		/// <remarks> Konstruktor vytvara kopiu, ktora ma prazdny zoznam hran vychadzajucich z vrchola hviezdy. </remarks>
		GraphVertexForwardStar(const GraphVertexForwardStar& other);

	protected:
		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju hrany vychadzajuce z vrchola hviezdy. </summary>
		/// <remarks>
		/// Klucom je adresa koncoveho vrchola hrany vychadzajucej z vrchola hviezdy.
		/// Hodnotou je smernik na prislusnu hranu.
		/// </remarks>
		Table<GraphVertex*, GraphEdge*> *forwardEdges_;
	};


	/// <summary> Graf implementovany ako zoznam doprednych hviezd. </summary>
	class ForwardStarGraph : public GraphWithRegistration
	{
	public:
		/// <summary> Konstruktor. </summary>
		ForwardStarGraph();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Graf typu ForwardStarGraph, z ktoreho sa prevezmu vlastnosti. </param>
		ForwardStarGraph(const ForwardStarGraph & other);

		/// <summary> Destruktor. </summary>
		~ForwardStarGraph();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury (grafu typu ForwardStarGraph). </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure * clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf s podporou registracie, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu ForwardStarGraph. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual GraphWithRegistration & operator=(const GraphWithRegistration & other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf typu ForwardStarGraph, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		virtual ForwardStarGraph & operator=(const ForwardStarGraph & other);

		/// <summary> Vrati pocet vrcholov v grafe. </summary>
		/// <returns> Pocet vrcholov v grafe. </returns>
		virtual size_t size() const override;

		/// <summary> Vymaze obsah grafu, t.j. vrcholy a hrany. Neodstrani zaregistrovane typy dat. </summary>
		virtual void clear() override;

		/// <summary> Vytvori vrchol s danym id v grafe. </summary>
		/// <param name = "vertexId"> Id vytvaraneho vrcholu. </param>
		/// <returns> Smernik na vytvoreny vrchol. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id uz existuje. </exception>  
		virtual GraphVertex* createVertex(int vertexId) override;

		/// <summary> Odstrani z grafu vrchol s danym id a vsetky hrany s nim incidentne. </summary>
		/// <param name = "vertexId"> Id ruseneho vrcholu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id neexistuje. </exception>  
		virtual void removeVertex(int vertexId) override;

		/// <summary> Odstrani z grafu dany vrchol a vsetky hrany s nim incidentne. </summary>
		/// <param name = "vertex"> Smernik na ruseny vrchol. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dany vrchol v grafe neexistuje. </exception>  
		/// <remarks> Ak sa vrchol podari odstranit z grafu, parameter vertex sa stane dangling pointerom. </remarks>
		/// <remarks>
		/// Ak sa vrchol podari odstranit z grafu, parameter vertex sa stane dangling pointerom.
		/// Metoda vyvolava metodu removeVertex(int).
		/// </remarks>
		virtual void removeVertex(GraphVertex* vertex) override;

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

		/// <summary> Odstrani z grafu danu hranu. </summary>
		/// <param name = "edge"> Smernik na rusenu hranu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dana hrana v grafe neexistuje. </exception>  
		/// <remarks>
		/// Ak sa hranu podari odstranit z grafu, parameter edge sa stane dangling pointerom.
		/// Metoda vyvolava metodu removeEdge(int, int).
		/// </remarks>
		virtual void removeEdge(GraphEdge* edge) override;

		/// <summary> Vrati vrchol s danym id. </summary>
		/// <param name = "vertexId"> Id vrcholu. </param>
		/// <returns> Smernik na vrchol grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id v grafe neexistuje. </exception>  
		virtual GraphVertex* getVertex(int vertexId) override;

		/// <summary> Adresou vrati zoznam vsetkych vrcholov grafu. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky vrcholy grafu. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky vrcholy grafu. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphVertex*>& getVertices(List<GraphVertex*>& list) override;

		/// <summary> Vrati orientovanu hranu spajajucu vrcholy s danymi id. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <returns> Smernik na hranu grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak medzi danymi vrcholmi neexistuje orientovana hrana. </exception>  
		virtual GraphEdge* getEdge(int beginVertexId, int endVertexId) override;

		/// <summary> Adresou vrati zoznam vsetkych hran grafu. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany grafu. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany grafu. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getEdges(List<GraphEdge*>& list) override;

		/// <summary> Adresou vrati zoznam vsetkych hran zacinajucich v danom vrchole. </summary>
		/// <param name = "vertexId"> Id vrcholu, ktoreho nasledovnikov chceme ziskat. </param>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany zacianajuce v danom vrchole. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany zacianajuce v danom vrchole. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getSuccessors(int vertexId, List<GraphEdge*>& list) override;

		/// <summary> Adresou vrati zoznam vsetkych hran konciacich v danom vrchole. </summary>
		/// <param name = "vertexId"> Id vrcholu, ktoreho predchodcov chceme ziskat. </param>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany konciace v danom vrchole. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany konciace v danom vrchole. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getPredecessors(int vertexId, List<GraphEdge*>& list) override;

	protected:
		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju vsetky hviezdy grafu. </summary>
		/// <remarks>
		/// Klucom je id vrchola konkretnej hviezdy.
		/// Hodnotou je smernik na prislusnu hviezdu.
		/// </remarks>
		Table<int, GraphVertexForwardStar*> *vertices_;
	};
}