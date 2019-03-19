#pragma once

#include "../structure.h"
#include "../list/list.h"
#include "../table/table.h"
#include <stdexcept>

namespace structures
{
	class Graph;

	/// <summary> Vymenovany typ predstavujuci typy dat, ktore mozu byt ulozene v elemente grafu. </summary>
	enum class GraphDataType
	{
		VERTEX_DATA,
		EDGE_DATA
	};

	/// <summary> Abstraktna trieda predstavujuca data ulozene v elemente grafu. </summary>
	class GraphData
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~GraphData();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		virtual GraphData& operator=(const GraphData& other) = 0;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat dat. </summary>
		/// <returns> Ukazovatel na klon dat. </returns>
		virtual GraphData* clone() const = 0;

		/// <summary> Getter vracajuci jedinecny identifikator triedy, z ktorej vznikli prislusne data. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda. </returns>
		virtual const GraphData* getClassKey() const = 0;

	protected:
		/// <summary> Konstruktor. </summary>
		GraphData();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Data, z ktorych sa prevezmu vlastnosti. </param>
		GraphData(const GraphData& other);
	};

	/// <summary> Data ulozene v elemente grafu. Atributom dat je dlzka. </summary>
	class GraphDataLength : public GraphData
	{
	public:
		/// <summary> Konstruktor. </summary>
		GraphDataLength();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Data typu GraphDataLength, z ktorych sa prevezmu vlastnosti. </param>
		GraphDataLength(const GraphDataLength& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu GraphDataLength. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual GraphData & operator=(const GraphData & other) override;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat dat. </summary>
		/// <returns> Ukazovatel na klon dat. </returns>
		virtual GraphData * clone() const override;

		/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataLength. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataLength. </returns>
		virtual const GraphData * getClassKey() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		virtual GraphDataLength & operator=(const GraphDataLength & other);

		/// <summary> Getter vracajuci atribut dlzka. </summary>
		/// <returns> Hodnota atributu dlzka. </returns>
		double getLength() const;

		/// <summary> Setter nastavujuci atribut dlzka. </summary>
		/// <param name = "price"> Hodnota, na ktoru sa nastavi atribut dlzka. </param>
		void setLength(double price);

	private:
		/// <summary> Objekt predstavujuci jednoznacny identifikator triedy GraphDataLength. </summary>
		/// <remarks> Pod jednoznacnym identifikatorom sa rozumie adresa objektu classKey_. </remarks>
		static const GraphDataLength classKey_;

		/// <summary> Atribut dlzka. Obycajne predstavuje dlzku hrany. </summary>
		double length_;
	};

	/// <summary> Trieda predstavujuca element grafu (obycajne vrchol alebo hrana). </summary>
	class GraphElement
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude element grafu nachadzat. </param>
		/// <param name = "dataType"> Typ dat ukladanych v elemente grafu. </param>
		GraphElement(const Graph* graph, const GraphDataType dataType);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Element grafu, z ktoreho sa prevezmu vlastnosti. </param>
		GraphElement(const GraphElement& other);

		/// <summary> Destruktor. </summary>
		virtual ~GraphElement();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Element grafu, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento element grafu nachadza po priradeni. </returns>
		virtual GraphElement& operator=(const GraphElement& other);

		/// <summary> Setter nastavujuci data uchovavane v elemente grafu. </summary>
		/// <param name = "data"> Referencia na data, ktore maju byt uchovavane v elemente grafu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak element grafu neuchovava data s danym klucom. </exception>
		/// <remarks> Kluc sa ziskava priamo z parametra data volanim metody getClassKey().
		/// Samotne data sa ziskavaju z parametra data volanim metody clone().
		///	</remarks>
		void setData(const GraphData& data);

		/// <summary> Odstrani data s danym klucom z elementu grafu. </summary>
		/// <param name = "key"> Jedinecny identifikator odstranovanych dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak element grafu neuchovava data s danym klucom. </exception>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		void removeData(const GraphData * key);

		/// <summary> Odstrani vsetky data z elementu grafu. </summary>
		void removeAllData();

		/// <summary> Spristupni data s danym klucom. </summary>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> Adresa, na ktorej sa nachadzaju data ulozene v elemente. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak element grafu neuchovava data s danym klucom. </exception>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		GraphData& accessData(const GraphData * key);

		/// <summary> Spristupni data s danym klucom. </summary>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> Adresa, na ktorej sa nachadzaju data ulozene v elemente. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak element grafu neuchovava data s danym klucom. </exception>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		const GraphData& accessData(const GraphData * key) const;

		/// <summary> Zisti, ci element grafu uchovava data s danym klucom. </summary>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> true, ak element grafu uchovava data s danym klucom, false inak. </returns>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		bool containsData(const GraphData * key) const;

		/// <summary> Getter vracajuci smernik na graf, v ktorom sa nachadza tento element grafu. </summary>
		/// <returns> Smernik na graf, v ktorom sa nachadza tento element grafu. </returns>
		const Graph* getGraph() const;

	protected:
		/// <summary> Setter nastavujuci smernik na graf, v ktorom sa nachadza tento element grafu. </summary>
		/// <remarks> V ramci metody sa odstrania z tohto elementu grafu vsetky data, ktore nie su registrovane v grafe, na ktory ukazuje prameter graph. </remarks>
		void setGraph(const Graph* graph);

	private:
		/// <summary> Smernik na graf, v ktorom sa nachadza tento element grafu. </summary>
		const Graph* graph_;

		/// <summary> Typ dat uchovavanych v tomto elemente grafu. </summary>
		GraphDataType dataType_;

		/// <summary> Smernik na tabulku, v ktorej sa uchovavaju data ulozene v tomto elemente grafu. </summary>
		/// <remarks>
		/// Klucom je adresa triedy, z ktorej vznikla prislusna instancia dat.
		/// Hodnotou je smernik na prislusnu instanciu dat.
		/// </remarks>
		Table<const GraphData*, GraphData*>* dataTable_;
	};

	/// <summary> Vrchol v grafe. </summary>
	class GraphVertex : public GraphElement
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude vrchol nachadzat. </param>
		/// <param name = "id"> Id vrcholu. </param>
		GraphVertex(const Graph * graph, int id);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol grafu, z ktoreho sa prevezmu vlastnosti. </param>
		GraphVertex(const GraphVertex & other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat vrcholu grafu. </summary>
		/// <param name = "graph"> Smernik na graf, v ktorom sa bude nachadzat vytvoreny klon vrcholu grafu. </param>
		/// <returns> Ukazovatel na klon vrcholu grafu. </returns>
		virtual GraphElement * clone(const Graph * graph) const;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Element grafu, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento element grafu nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je vrchol grafu. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual GraphElement& operator=(const GraphElement& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Vrchol grafu, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento vrchol grafu nachadza po priradeni. </returns>
		virtual GraphVertex& operator=(const GraphVertex& other);

		/// <summary> Getter vracajuci id daneho vrcholu. </summary>
		/// <returns> Id daneho vrcholu. </returns>
		int getId() const;

	private:
		/// <summary> Id daneho vrcholu. </summary>
		int id_;
	};

	/// <summary> Orientovana hrana v grafe. </summary>
	class GraphEdge : public GraphElement
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "beginVertex"> Smernik na pociatocny vrchol. </param>
		/// <param name = "endVertex"> Smernik na koncovy vrchol. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrcholy beginVertex a endVertex patria do roznych grafov. </exception>  
		/// <remarks> Graf, do ktoreho patri vytvarana hrana, sa nastavuje na graf, do ktoreho patri parameter beginVertex. </remarks>
		GraphEdge(GraphVertex* beginVertex, GraphVertex* endVertex);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Hrana grafu, z ktorej sa prevezmu vlastnosti. </param>
		GraphEdge(const GraphEdge & other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat hrany grafu, pricom zmeni smerniky na pociatocny a koncovy vrchol. </summary>
		/// <param name = "newBeginVertex"> Smernik na novy pociatocny vrchol. </param>
		/// <param name = "newEndVertex"> Smernik na novy koncovy vrchol. </param>
		/// <returns> Ukazovatel na klon hrany grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrcholy newBeginVertex a newEndVertex patria do roznych grafov. </exception>  
		/// <remarks> Graf, do ktoreho patri klon hrany, sa nastavuje na graf, do ktoreho patri parameter newBeginVertex. </remarks>
		virtual GraphEdge * clone(GraphVertex* newBeginVertex, GraphVertex* newEndVertex) const;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Element grafu, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento element grafu nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je hrana grafu. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual GraphElement& operator=(const GraphElement& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Hrana grafu, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato hrana grafu nachadza po priradeni. </returns>
		virtual GraphEdge& operator=(const GraphEdge& other);

		/// <summary> Getter vracajuci pociatocny vrchol hrany. </summary>
		/// <returns> Smernik na pociatocny vrchol hrany. </returns>
		GraphVertex* getBeginVertex();

		/// <summary> Getter vracajuci pociatocny vrchol hrany. </summary>
		/// <returns> Smernik na pociatocny vrchol hrany. </returns>
		const GraphVertex* getBeginVertex() const;

		/// <summary> Getter vracajuci koncovy vrchol hrany. </summary>
		/// <returns> Smernik na koncovy vrchol hrany. </returns>
		GraphVertex* getEndVertex();

		/// <summary> Getter vracajuci koncovy vrchol hrany. </summary>
		/// <returns> Smernik na koncovy vrchol hrany. </returns>
		const GraphVertex* getEndVertex() const;

	protected:
		/// <summary> Smernik na pociatocny vrchol. </summary>
		GraphVertex* beginVertex_;

		/// <summary> Smernik na koncovy vrchol. </summary>
		GraphVertex* endVertex_;
	};

	/// <summary> Orientovany graf. </summary>
	class Graph : public Structure
	{
	public:
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury (grafu). </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure * clone() const = 0;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (graf), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je graf. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual Structure & operator=(const Structure & other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Graf, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento graf nachadza po priradeni. </returns>
		virtual Graph & operator=(const Graph & other) = 0;

		/// <summary> Vrati pocet vrcholov v grafe. </summary>
		/// <returns> Pocet vrcholov v grafe. </returns>
		virtual size_t size() const = 0;

		/// <summary> Vymaze obsah grafu, t.j. vrcholy a hrany. Neodstrani zaregistrovane typy dat. </summary>
		virtual void clear() = 0;

		/// <summary> Vytvori vrchol s danym id v grafe. </summary>
		/// <param name = "vertexId"> Id vytvaraneho vrcholu. </param>
		/// <returns> Smernik na vytvoreny vrchol. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id uz existuje. </exception>  
		virtual GraphVertex* createVertex(int vertexId) = 0;

		/// <summary> Odstrani z grafu vrchol s danym id a vsetky hrany s nim incidentne. </summary>
		/// <param name = "vertexId"> Id ruseneho vrcholu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id neexistuje. </exception>  
		virtual void removeVertex(int vertexId) = 0;

		/// <summary> Odstrani z grafu dany vrchol a vsetky hrany s nim incidentne. </summary>
		/// <param name = "vertex"> Smernik na ruseny vrchol. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dany vrchol v grafe neexistuje. </exception>  
		/// <remarks> Ak sa vrchol podari odstranit z grafu, parameter vertex sa stane dangling pointerom. </remarks>
		virtual void removeVertex(GraphVertex* vertex) = 0;

		/// <summary> Vytvori orientovanu hranu v grafe. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <returns> Smernik na vytvorenu hranu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak aspon jeden z vrcholov v grafe neexistuje. </exception>  
		virtual GraphEdge* createEdge(int beginVertexId, int endVertexId) = 0;
		
		/// <summary> Odstrani z grafu hranu. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dana hrana neexistuje. </exception>  
		virtual void removeEdge(int beginVertexId, int endVertexId) = 0;

		/// <summary> Odstrani z grafu danu hranu. </summary>
		/// <param name = "edge"> Smernik na rusenu hranu. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak dana hrana v grafe neexistuje. </exception>  
		/// <remarks> Ak sa hranu podari odstranit z grafu, parameter edge sa stane dangling pointerom. </remarks>
		virtual void removeEdge(GraphEdge* edge) = 0;

		/// <summary> Vrati vrchol s danym id. </summary>
		/// <param name = "vertexId"> Id vrcholu. </param>
		/// <returns> Smernik na vrchol grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vrchol s danym id v grafe neexistuje. </exception>  
		virtual GraphVertex* getVertex(int vertexId) = 0;
		
		/// <summary> Adresou vrati zoznam vsetkych vrcholov grafu. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky vrcholy grafu. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky vrcholy grafu. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphVertex*>& getVertices(List<GraphVertex*>& list) = 0;

		/// <summary> Vrati orientovanu hranu spajajucu vrcholy s danymi id. </summary>
		/// <param name = "beginVertexId"> Id pociatocneho vrcholu. </param>
		/// <param name = "endVertexId"> Id koncoveho vrcholu. </param>
		/// <returns> Smernik na hranu grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak medzi danymi vrcholmi neexistuje orientovana hrana. </exception>  
		virtual GraphEdge* getEdge(int beginVertexId, int endVertexId) = 0;

		/// <summary> Adresou vrati zoznam vsetkych hran grafu. </summary>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na vsetky hrany grafu. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na vsetky hrany grafu. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getEdges(List<GraphEdge*>& list) = 0;

		/// <summary> Adresou vrati zoznam vsetkych hran zacinajucich v danom vrchole. </summary>
		/// <param name = "vertexId"> Id vrcholu, ktoreho nasledovnikov chceme ziskat. </param>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany zacianajuce v danom vrchole. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany zacianajuce v danom vrchole. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getSuccessors(int vertexId, List<GraphEdge*>& list) = 0;

		/// <summary> Adresou vrati zoznam vsetkych hran konciacich v danom vrchole. </summary>
		/// <param name = "vertexId"> Id vrcholu, ktoreho predchodcov chceme ziskat. </param>
		/// <param name = "list"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany konciace v danom vrchole. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany konciace v danom vrchole. </returns>
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument list. </remarks>
		virtual List<GraphEdge*>& getPredecessors(int vertexId, List<GraphEdge*>& list) = 0;

		/// <summary> Zisti, ci v grafe su registrovane data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <returns> true, ak v grafe su registrovane data daneho typu s danym klucom, false inak. </returns>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		virtual bool areDataRegistered(GraphDataType dataType, const GraphData * key) const = 0;

		/// <summary> Zaregistruje v grafe data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak uz je v grafe registrovany dany typ dat s danym klucom. </exception>
		/// <remarks> V ramci metody sa vola nad parametrom key metoda getClassKey(). </remarks>
		virtual void registerData(GraphDataType dataType, const GraphData * key) = 0;

		/// <summary> Odstrani z grafu data daneho typu s danym klucom. </summary>
		/// <param name = "dataType"> Typ dat - data vrcholu alebo data hrany. </param>
		/// <param name = "key"> Jedinecny identifikator dat. Jedna sa u adresu triedy, z ktorej vznikla instancia dat. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak v grafe nie je registrovany dany typ dat s danym klucom. </exception>
		/// <remarks> 
		///	V ramci metody sa vola nad parametrom key metoda getClassKey().
		/// Metoda odstrani dany typ dat s danym klucom zo vsetkych elementov grafu, ktore ich mozu obsahovat.
		///	</remarks>
		virtual void unregisterData(GraphDataType dataType, const GraphData * key) = 0;
	protected:
		/// <summary> Konstruktor. </summary>
		Graph();
	};
}

