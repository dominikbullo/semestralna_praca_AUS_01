#include "bi_star_graph.h"
#include "../table/treap.h"
#include "../list/linked_list.h"

#pragma region GraphVertexBiStar

structures::GraphVertexBiStar::GraphVertexBiStar(const Graph* graph, int vertexId, Table<GraphVertex*, GraphEdge*>* forwardEdges, Table<GraphVertex*, GraphEdge*>* backwardEdges) :
	GraphVertexForwardStar(graph, vertexId, forwardEdges),
	backwardEdges_(backwardEdges)
{
}

structures::GraphVertexBiStar::~GraphVertexBiStar()
{
	// TODO 11: GraphVertexBiStar
}

structures::GraphElement * structures::GraphVertexBiStar::clone(const Graph* graph) const
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::clone: Not implemented yet.");
}

bool structures::GraphVertexBiStar::containsBackwardEdge(GraphVertex * beginVertex)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::containsBackwardEdge: Not implemented yet.");
}

bool structures::GraphVertexBiStar::tryInsertBackwardEdge(GraphEdge * edge)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::tryInsertBackwardEdge: Not implemented yet.");
}

bool structures::GraphVertexBiStar::tryRemoveBackwardEdge(GraphEdge * edge)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::tryRemoveBackwardEdge: Not implemented yet.");
}

structures::GraphEdge * structures::GraphVertexBiStar::removeBackwardEdge(GraphVertex * beginVertex)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::removeBackwardEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::GraphVertexBiStar::removeBackwardEdges(List<GraphEdge*>& list)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::removeBackwardEdges: Not implemented yet.");
}

structures::GraphEdge * structures::GraphVertexBiStar::getBackwardEdge(GraphVertex * beginVertex)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::getBackwardEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::GraphVertexBiStar::getBackwardEdges(List<GraphEdge*>& list)
{
	// TODO 11: GraphVertexBiStar
	throw std::exception("GraphVertexBiStar::getBackwardEdges: Not implemented yet.");
}

structures::GraphVertexBiStar::GraphVertexBiStar(const GraphVertexBiStar & other) :
	GraphVertexForwardStar(other),
	backwardEdges_(dynamic_cast<Table<GraphVertex*, GraphEdge*>*>(other.backwardEdges_->clone()))
{
	backwardEdges_->clear();
}

#pragma endregion


#pragma region BiStarGraph

structures::BiStarGraph::BiStarGraph() :
	ForwardStarGraph()
{
}

structures::BiStarGraph::BiStarGraph(const BiStarGraph & other) :
	BiStarGraph()
{
	*this = other;
}

structures::Structure * structures::BiStarGraph::clone() const
{
	return new BiStarGraph(*this);
}

structures::ForwardStarGraph & structures::BiStarGraph::operator=(const ForwardStarGraph & other)
{
	return *this = dynamic_cast<const BiStarGraph&>(other);
}

structures::BiStarGraph & structures::BiStarGraph::operator=(const BiStarGraph & other)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::operator=: Not implemented yet.");
}

structures::GraphVertex * structures::BiStarGraph::createVertex(int vertexId)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::createVertex: Not implemented yet.");
}

void structures::BiStarGraph::removeVertex(int vertexId)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::removeVertex: Not implemented yet.");
}

structures::GraphEdge* structures::BiStarGraph::createEdge(int beginVertexId, int endVertexId)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::createEdge: Not implemented yet.");
}

void structures::BiStarGraph::removeEdge(int beginVertexId, int endVertexId)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::removeEdge: Not implemented yet.");
}

structures::List<structures::GraphEdge*>& structures::BiStarGraph::getPredecessors(int vertexId, List<GraphEdge*>& list)
{
	// TODO 11: BiStarGraph
	throw std::exception("BiStarGraph::getPredecessors: Not implemented yet.");
}

#pragma endregion
