#include "graph.h"
#include <stdexcept>
#include "../table/sorted_sequence_table.h"
#include "../list/linked_list.h"

#pragma region GraphData

structures::GraphData::~GraphData()
{
}

structures::GraphData::GraphData()
{
}

structures::GraphData::GraphData(const GraphData & other)
{
}

#pragma endregion


#pragma region GraphDataLength

const structures::GraphDataLength structures::GraphDataLength::classKey_;

structures::GraphDataLength::GraphDataLength() :
	GraphData(),
	length_(0)
{
}

structures::GraphDataLength::GraphDataLength(const GraphDataLength & other) :
	GraphData(other),
	length_(other.length_)
{
}

structures::GraphData & structures::GraphDataLength::operator=(const GraphData & other)
{
	return *this = dynamic_cast<const GraphDataLength&>(other);
}

structures::GraphData * structures::GraphDataLength::clone() const
{
	return new GraphDataLength(*this);
}

const structures::GraphData * structures::GraphDataLength::getClassKey() const
{
	return &classKey_;
}

structures::GraphDataLength & structures::GraphDataLength::operator=(const GraphDataLength & other)
{
	if (this != &other)
	{
		length_ = other.length_;
	}
	return *this;
}

double structures::GraphDataLength::getLength() const
{
	return length_;
}

void structures::GraphDataLength::setLength(double price)
{
	length_ = price;
}

#pragma endregion


#pragma region GraphElement

structures::GraphElement::GraphElement(const Graph* graph, const GraphDataType dataType) :
	dataType_(dataType),
	graph_(graph),
	dataTable_(new SortedSequenceTable<const GraphData*, GraphData*>())
{
}

structures::GraphElement::GraphElement(const GraphElement & other) :
	GraphElement(other.graph_, other.dataType_)
{
	*this = other;
}

structures::GraphElement::~GraphElement()
{
	// TODO 11: GraphElement
}

structures::GraphElement & structures::GraphElement::operator=(const GraphElement & other)
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::operator=: Not implemented yet.");
}

void structures::GraphElement::setData(const GraphData & data)
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::setData: Not implemented yet.");
}

void structures::GraphElement::removeData(const GraphData * key)
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::removeData: Not implemented yet.");
}

void structures::GraphElement::removeAllData()
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::removeAllData: Not implemented yet.");
}

structures::GraphData & structures::GraphElement::accessData(const GraphData * key)
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::accessData: Not implemented yet.");
}

const structures::GraphData & structures::GraphElement::accessData(const GraphData * key) const
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::accessData: Not implemented yet.");
}

bool structures::GraphElement::containsData(const GraphData * key) const
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::containsData: Not implemented yet.");
}

const structures::Graph * structures::GraphElement::getGraph() const
{
	return graph_;
}

void structures::GraphElement::setGraph(const Graph * graph)
{
	// TODO 11: GraphElement
	throw std::exception("GraphElement::setGraph: Not implemented yet.");
}

#pragma endregion


#pragma region GraphVertex

structures::GraphVertex::GraphVertex(const Graph* graph, int id) :
	GraphElement(graph, GraphDataType::VERTEX_DATA),
	id_(id)
{
}

structures::GraphVertex::GraphVertex(const GraphVertex & other) :
	GraphElement(other),
	id_(other.id_)
{
}

structures::GraphElement * structures::GraphVertex::clone(const Graph* graph) const
{
	// TODO 11: GraphVertex
	throw std::exception("GraphVertex::clone: Not implemented yet.");
}

structures::GraphElement & structures::GraphVertex::operator=(const GraphElement & other)
{
	return *this = dynamic_cast<const GraphVertex&>(other);
}

structures::GraphVertex & structures::GraphVertex::operator=(const GraphVertex & other)
{
	// TODO 11: GraphVertex
	throw std::exception("GraphVertex::operator=: Not implemented yet.");
}

int structures::GraphVertex::getId() const
{
	return id_;
}

#pragma endregion


#pragma region GraphEdge

structures::GraphEdge::GraphEdge(GraphVertex * beginVertex, GraphVertex * endVertex) :
	GraphElement(beginVertex->getGraph(), GraphDataType::EDGE_DATA),
	beginVertex_(beginVertex),
	endVertex_(endVertex)
{
	if (beginVertex_->getGraph() != endVertex_->getGraph())
	{
		throw std::logic_error("GraphEdge::GraphEdge: beginVertex and endVertex belong to different graphs.");
	}
}

structures::GraphEdge::GraphEdge(const GraphEdge & other) :
	GraphElement(other),
	beginVertex_(other.beginVertex_),
	endVertex_(other.endVertex_)
{
}

structures::GraphEdge * structures::GraphEdge::clone(GraphVertex * newBeginVertex, GraphVertex * newEndVertex) const
{
	// TODO 11: GraphEdge
	throw std::exception("GraphEdge::clone: Not implemented yet.");
}

structures::GraphElement & structures::GraphEdge::operator=(const GraphElement & other)
{
	return *this = dynamic_cast<const GraphEdge&>(other);
}

structures::GraphEdge & structures::GraphEdge::operator=(const GraphEdge & other)
{
	// TODO 11: GraphEdge
	throw std::exception("GraphEdge::operator=: Not implemented yet.");
}

structures::GraphVertex * structures::GraphEdge::getBeginVertex()
{
	return beginVertex_;
}

const structures::GraphVertex * structures::GraphEdge::getBeginVertex() const
{
	return beginVertex_;
}

structures::GraphVertex * structures::GraphEdge::getEndVertex()
{
	return endVertex_;
}

const structures::GraphVertex * structures::GraphEdge::getEndVertex() const
{
	return endVertex_;
}

structures::Structure & structures::Graph::operator=(const Structure & other)
{
	return *this = dynamic_cast<const Graph&>(other);
}

#pragma endregion


#pragma region Graph

structures::Graph::Graph()
{
}

#pragma endregion
