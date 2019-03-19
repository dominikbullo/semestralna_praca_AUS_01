#pragma once

#include "../graph.h"
#include "../../list/list.h"

namespace structures
{
	/// <summary> Dijkstrov algoritmus. </summary>
	class Dijkstra
	{
	protected:
		/// <summary> Data ukladane vo vrchole grafu, ktore vyzaduje Dijkstrov algoritmus. </summary>
		class GraphDataDijkstraVertex : public GraphData
		{
		public:
			/// <summary> Konstruktor. </summary>
			GraphDataDijkstraVertex();

			/// <summary> Kopirovaci konstruktor. </summary>
			/// <param name = "other"> Data typu GraphDataDijkstraVertex, z ktorych sa prevezmu vlastnosti. </param>
			GraphDataDijkstraVertex(const GraphDataDijkstraVertex& other);

			/// <summary> Operator priradenia. </summary>
			/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
			/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
			/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu GraphDataDijkstraVertex. </exception>  
			/// <remarks> Vyuziva typovy operator priradenia. </remarks>
			virtual GraphData & operator=(const GraphData & other) override;

			/// <summary> Operacia klonovania. Vytvori a vrati duplikat dat. </summary>
			/// <returns> Ukazovatel na klon dat. </returns>
			virtual GraphData * clone() const override;

			/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataDijkstraVertex. </summary>
			/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataDijkstraVertex. </returns>
			virtual const GraphData * getClassKey() const override;

			/// <summary> Operator priradenia. </summary>
			/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
			/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
			virtual GraphDataDijkstraVertex & operator=(const GraphDataDijkstraVertex & other);

			/// <summary> Resetne data na defaultne hodnoty. </summary>
			void reset();

			/// <summary> Getter vracajuci atribut predchodca. </summary>
			/// <returns> Hodnota atributu predchodca. </returns>
			GraphVertex * getPredecessor();

			/// <summary> Setter nastavujuci atribut predchodca. </summary>
			/// <param name = "predecessor"> Hodnota, na ktoru sa nastavi atribut predchodca. </param>
			void setPredecessor(GraphVertex * predecessor);

			/// <summary> Getter vracajuci atribut vzdialenost. </summary>
			/// <returns> Hodnota atributu vzdialenost. </returns>
			double getDistance();

			/// <summary> Setter nastavujuci atribut vzdialenost. </summary>
			/// <param name = "distance"> Hodnota, na ktoru sa nastavi atribut vzdialenost. </param>
			void setDistance(double distance);

			/// <summary> Getter vracajuci atribut indikujuci, ci bol vrchol oznaceny za definitivny. </summary>
			/// <returns> Hodnota atributu indikujuceho definitivnost. </returns>
			bool isDefinitive();

			/// <summary> Setter nastavujuci atribut indikujici, ci je vrchol definitivny. </summary>
			/// <param name = "definitive"> Hodnota, na ktoru sa nastavi atribut indikujuci definitivnost. </param>
			void setDefinitive(bool definitive);
		private:
			/// <summary> Objekt predstavujuci jednoznacny identifikator triedy GraphDataDijkstraVertex. </summary>
			/// <remarks> Pod jednoznacnym identifikatorom sa rozumie adresa objektu classKey_. </remarks>
			static const GraphDataDijkstraVertex classKey_;

			/// <summary> Smernik na predchodcu. </summary>
			/// <remarks> Sluzi na zrekonstruovanie najkratsej cesty najdenej Dijkstrovym algoritmom. </remarks>
			GraphVertex * predecessor_;

			/// <summary> Vzdialenost daneho vrcholu od vrcholu, z ktoreho hladame najkratsiu cestu. </summary>
			double distance_;

			/// <summary> Priznak indikujuci, ci bol dany vrchol oznaceny za definitivny. </summary>
			/// <remarks> Ak je vrchol oznaceny za definitivny, atributy predecessor_ a distance_ maju konecnu hodnotu. </remarks>
			bool definitive_;
		};

	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "graph"> Graf, nad ktorym bude bezat Dijkstrov algoritmus. </param>
		/// <param name = "lengthKey">
		/// Jednoznacny identifikator dat obsahujucich informaciu o dlzke hrany.
		/// Jedna sa u adresu triedy GraphDataLength alebo triedy z nej odvodenej.
		/// </param>
		Dijkstra(Graph* graph, const GraphDataLength* lengthKey);

		/// <summary> Explicitne zakazanie kopirovacieho konstruktora. </summary>
		Dijkstra(const Dijkstra& other) = delete;

		/// <summary> Destruktor. </summary>
		virtual ~Dijkstra();

		/// <summary> Explicitne zakazanie operatora priradenia. </summary>
		/// <remarks> Nad instanciou triedy Dijkstra nie je mozne definovat operator priradenia. </remarks>
		Dijkstra& operator=(const Dijkstra& other) = delete;

		/// <summary> Metoda vypocita najkratsiu cestu medzi danymi vrcholmi. </summary>
		/// <param name = "startVertexId"> Id zaciatocneho vrcholu. </param>
		/// <param name = "stopVertexId"> Id koncoveho vrcholu. </param>
		/// <returns> true, ak cesta existuje, false inak. </returns>
		bool tryCompute(int startVertexId, int stopVertexId);

		/// <summary> Getter vracajuci dlzku najkratsej cesty vypocitanej metodou tryCompute(). </summary>
		/// <returns> Dlzka najkratsej cety. Ak cesta medzi vrcholmi neexistuje, metoda vrati hodnotu nekonecno. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak metoda tryCompute() este nebola volana. </exception>  
		double getComputedDistance();

		/// <summary> Adresou vrati zoznam (postupnost) hran, ktore tvoria najkratsiu cestu vypocitanu metodou tryCompute(). </summary>
		/// <param name = "path"> Referencia na zoznam, do ktoreho sa vlozia smerniky na hrany tvoriace najkratsiu cestu. </param>
		/// <returns> Adresa, na ktorej sa nachadza zoznam naplneny smernikmi na hrany tvoriace najkratsiu cestue. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak metoda tryCompute() este nebola volana. </exception>  
		/// <remarks> Navratova hodnota sa zhoduje s adresou, na ktorej sa nachadza argument path. </remarks>
		List<GraphEdge*>& getComputedPath(List<GraphEdge*>& path);

	private:
		/// <summary> 
		/// Pomocna metoda Dijkstrovho algoritmu, ktora vyhlada pivota medzi vrcholmi,
		/// ktore este nie su oznacene ako definitivne.
		/// </summary>
		/// <returns> Smernik na vrchol predstavujuci noveho pivota. </returns>
		GraphVertex* findNewPivot();

		/// <summary> Pomocna metoda, ktora vrati pre dany vrchol data potrebne pre cinnost Dijkstrovho algoritmu. </summary>
		/// <param name = "vertex"> Vrchol, pre ktory chceme ziskat data potrebne pre cinnost Dijkstrovho algoritmu. </param>
		/// <returns> Smernik na data potrebne pre cinnost Dijkstrovho algoritmu. </returns>
		GraphDataDijkstraVertex* getDijkstraData(GraphVertex * vertex);

		/// <summary> Pomocna metoda, ktora vrati dlzku danej hrany. </summary>
		/// <param name = "edge"> Hrana, ktorej dlzku chceme zistit. </param>
		/// <returns> Dlzka danej hrany. </returns>
		double getEdgeLength(const GraphEdge * edge) const;

	private:
		/// <summary> Smernik na graf, nad ktorym su spusti Dijkstrov algoritmus. </summary>
		Graph* graph_;

		/// <summary> Jednoznacny identifikator dat obsahujucich informaciu o dlzke hrany. </summary>
		const GraphDataLength* lengthKey_;

		/// <summary> Zonam vrcholov grafu, nad ktorym sa spusti Dijkstrov algoritmus. </summary>
		List<GraphVertex*>* vertices_;

		/// <summary> Smernik na vrchol, z ktoreho hladame najkratsiu cestu. </summary>
		GraphVertex* beginVertex_;

		/// <summary> Smernik na vrchol, do ktoreho hladame najkratsiu cestu. </summary>
		GraphVertex* endVertex_;

		/// <summary> Jednoznacny identifikator dat ukladanych vo vrchole grafu, ktore vyzaduje Dijkstrov algoritmus. </summary>
		const GraphData* dijkstraDataKey_;
	};
}