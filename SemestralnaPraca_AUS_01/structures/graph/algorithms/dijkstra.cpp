#include "dijkstra.h"
#include "../../ds_routines.h"
#include "../../list/array_list.h"
#include "../../stack/explicit_stack.h"

#include <stdexcept>

#pragma region Dijkstra::GraphDataDijkstraVertex

const structures::Dijkstra::GraphDataDijkstraVertex structures::Dijkstra::GraphDataDijkstraVertex::classKey_;

structures::Dijkstra::GraphDataDijkstraVertex::GraphDataDijkstraVertex() :
	GraphData(),
	predecessor_(nullptr),
	distance_(DSRoutines::getInfinity()),
	definitive_(false)
{
}

structures::Dijkstra::GraphDataDijkstraVertex::GraphDataDijkstraVertex(const GraphDataDijkstraVertex & other) :
	GraphData(other),
	predecessor_(other.predecessor_),
	distance_(other.distance_),
	definitive_(other.definitive_)
{
}

structures::GraphData & structures::Dijkstra::GraphDataDijkstraVertex::operator=(const GraphData & other)
{
	return *this = dynamic_cast<const GraphDataDijkstraVertex&>(other);
}

structures::Dijkstra::GraphDataDijkstraVertex & structures::Dijkstra::GraphDataDijkstraVertex::operator=(const GraphDataDijkstraVertex & other)
{
	if (this != &other)
	{
		predecessor_ = other.predecessor_;
		distance_ = other.distance_;
		definitive_ = other.definitive_;
	}
	return *this;
}

structures::GraphData * structures::Dijkstra::GraphDataDijkstraVertex::clone() const
{
	return new GraphDataDijkstraVertex(*this);
}

const structures::GraphData * structures::Dijkstra::GraphDataDijkstraVertex::getClassKey() const
{
	return &classKey_;
}

void structures::Dijkstra::GraphDataDijkstraVertex::reset()
{
	predecessor_ = nullptr;
	distance_ = DSRoutines::getInfinity();
	definitive_ = false;
}

structures::GraphVertex * structures::Dijkstra::GraphDataDijkstraVertex::getPredecessor()
{
	return predecessor_;
}

void structures::Dijkstra::GraphDataDijkstraVertex::setPredecessor(GraphVertex * predecessor)
{
	predecessor_ = predecessor;
}

double structures::Dijkstra::GraphDataDijkstraVertex::getDistance()
{
	return distance_;
}

void structures::Dijkstra::GraphDataDijkstraVertex::setDistance(double distance)
{
	distance_ = distance;
}

bool structures::Dijkstra::GraphDataDijkstraVertex::isDefinitive()
{
	return definitive_;
}

void structures::Dijkstra::GraphDataDijkstraVertex::setDefinitive(bool definitive)
{
	definitive_ = definitive;
}

#pragma endregion


#pragma region Dijkstra

structures::Dijkstra::Dijkstra(Graph* graph, const GraphDataLength* lengthKey) :
	graph_(graph),
	lengthKey_(lengthKey),
	vertices_(new ArrayList<GraphVertex*>()),
	beginVertex_(nullptr),
	endVertex_(nullptr),
	dijkstraDataKey_(GraphDataDijkstraVertex().getClassKey())
{
	// TODO 11: Dijkstra
	throw std::exception("Dijkstra::Dijkstra: Not implemented yet.");
}

structures::Dijkstra::~Dijkstra()
{
	// TODO 11: Dijkstra
}

bool structures::Dijkstra::tryCompute(int startVertexId, int stopVertexId)
{
	// TODO 11: Dijkstra
	throw std::exception("Dijkstra::tryCompute: Not implemented yet.");
}

double structures::Dijkstra::getComputedDistance()
{
	// TODO 11: Dijkstra
	throw std::exception("Dijkstra::getComputedDistance: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::Dijkstra::getComputedPath(List<GraphEdge*>& path)
{
	// TODO 11: Dijkstra
	throw std::exception("Dijkstra::getComputedPath: Not implemented yet.");
}

structures::GraphVertex * structures::Dijkstra::findNewPivot()
{
	// TODO 11: Dijkstra
	throw std::exception("Dijkstra::findNewPivot: Not implemented yet.");
}

structures::Dijkstra::GraphDataDijkstraVertex* structures::Dijkstra::getDijkstraData(GraphVertex * vertex)
{
	return dynamic_cast<GraphDataDijkstraVertex*>(&vertex->accessData(dijkstraDataKey_));
}

double structures::Dijkstra::getEdgeLength(const GraphEdge * edge) const
{
	return dynamic_cast<const GraphDataLength&>(edge->accessData(lengthKey_)).getLength();
}

#pragma endregion