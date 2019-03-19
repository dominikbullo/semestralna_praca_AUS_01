#include "forward_star_graph.h"
#include "../table/treap.h"
#include "../list/linked_list.h"

#include <stdexcept>

#pragma region GraphVertexForwardStar

structures::GraphVertexForwardStar::GraphVertexForwardStar(const Graph* graph, int vertexId, Table<GraphVertex*, GraphEdge*>* forwardEdges) :
	GraphVertex(graph, vertexId),
	forwardEdges_(forwardEdges)
{
}

structures::GraphVertexForwardStar::~GraphVertexForwardStar()
{
	// TODO 11: GraphVertexForwardStar
}

structures::GraphElement * structures::GraphVertexForwardStar::clone(const Graph* graph) const
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::clone: Not implemented yet.");
}

structures::GraphVertex & structures::GraphVertexForwardStar::operator=(const GraphVertex & other)
{
	throw std::logic_error("Assignment operator is not defined for forward star.");
}

bool structures::GraphVertexForwardStar::containsForwardEdge(GraphVertex * endVertex)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::containsForwardEdge: Not implemented yet.");
}

bool structures::GraphVertexForwardStar::tryInsertForwardEdge(GraphEdge * edge)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::tryInsertForwardEdge: Not implemented yet.");
}

bool structures::GraphVertexForwardStar::tryRemoveForwardEdge(GraphEdge * edge)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::tryRemoveForwardEdge: Not implemented yet.");
}

structures::GraphEdge * structures::GraphVertexForwardStar::removeForwardEdge(GraphVertex * endVertex)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::removeForwardEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::GraphVertexForwardStar::removeForwardEdges(List<GraphEdge*>& list)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::removeForwardEdges: Not implemented yet.");
}

structures::GraphEdge * structures::GraphVertexForwardStar::getForwardEdge(GraphVertex * endVertex)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::getForwardEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::GraphVertexForwardStar::getForwardEdges(List<GraphEdge*>& list)
{
	// TODO 11: GraphVertexForwardStar
	throw std::exception("GraphVertexForwardStar::getForwardEdges: Not implemented yet.");
}

structures::GraphVertexForwardStar::GraphVertexForwardStar(const GraphVertexForwardStar & other) :
	GraphVertex(other),
	forwardEdges_(dynamic_cast<Table<GraphVertex*, GraphEdge*>*>(other.forwardEdges_->clone()))
{
	forwardEdges_->clear();
}

#pragma endregion


#pragma region ForwardStarGraph

structures::ForwardStarGraph::ForwardStarGraph() :
	GraphWithRegistration(new Treap<const GraphData*, const GraphData*>(), new Treap<const GraphData*, const GraphData*>()),
	vertices_(new Treap<int, GraphVertexForwardStar*>())
{
}

structures::ForwardStarGraph::ForwardStarGraph(const ForwardStarGraph & other) :
	ForwardStarGraph()
{
	*this = other;
}

structures::ForwardStarGraph::~ForwardStarGraph()
{
	// TODO 11: ForwardStarGraph
}

structures::Structure * structures::ForwardStarGraph::clone() const
{
	return new ForwardStarGraph(*this);
}

structures::GraphWithRegistration & structures::ForwardStarGraph::operator=(const GraphWithRegistration & other)
{
	return *this = dynamic_cast<const ForwardStarGraph&>(other);
}

structures::ForwardStarGraph & structures::ForwardStarGraph::operator=(const ForwardStarGraph & other)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::operator=: Not implemented yet.");
}

size_t structures::ForwardStarGraph::size() const
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::size: Not implemented yet.");
}

void structures::ForwardStarGraph::clear()
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::clear: Not implemented yet.");
}

structures::GraphVertex* structures::ForwardStarGraph::createVertex(int vertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::createVertex: Not implemented yet.");
}

void structures::ForwardStarGraph::removeVertex(int vertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::removeVertex: Not implemented yet.");
}

void structures::ForwardStarGraph::removeVertex(GraphVertex * vertex)
{
	removeVertex(vertex->getId());
}

structures::GraphEdge* structures::ForwardStarGraph::createEdge(int beginVertexId, int endVertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::createEdge: Not implemented yet.");
}

void structures::ForwardStarGraph::removeEdge(int beginVertexId, int endVertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::removeEdge: Not implemented yet.");
}

void structures::ForwardStarGraph::removeEdge(GraphEdge * edge)
{
	removeEdge(edge->getBeginVertex()->getId(), edge->getEndVertex()->getId());
}

structures::GraphVertex * structures::ForwardStarGraph::getVertex(int vertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getVertex: Not implemented yet.");
}

structures::List<structures::GraphVertex*>& structures::ForwardStarGraph::getVertices(List<GraphVertex*>& list)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getVertices: Not implemented yet.");
}

structures::GraphEdge * structures::ForwardStarGraph::getEdge(int beginVertexId, int endVertexId)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::ForwardStarGraph::getEdges(List<GraphEdge*>& list)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getEdges: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::ForwardStarGraph::getSuccessors(int vertexId, List<GraphEdge*>& list)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getSuccessors: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::ForwardStarGraph::getPredecessors(int vertexId, List<GraphEdge*>& list)
{
	// TODO 11: ForwardStarGraph
	throw std::exception("ForwardStarGraph::getPredecessors: Not implemented yet.");
}

#pragma endregion