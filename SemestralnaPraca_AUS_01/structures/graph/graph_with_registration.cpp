#include "graph_with_registration.h"
#include "../list/linked_list.h"

#include <stdexcept>

structures::GraphWithRegistration::~GraphWithRegistration()
{
	delete registeredVertexData_;
	registeredVertexData_ = nullptr;

	delete registeredEdgeData_;
	registeredEdgeData_ = nullptr;
}

structures::Graph & structures::GraphWithRegistration::operator=(const Graph & other)
{
	return *this = dynamic_cast<const GraphWithRegistration&>(other);
}

structures::GraphWithRegistration & structures::GraphWithRegistration::operator=(const GraphWithRegistration & other)
{
	if (this != &other)
	{
		*registeredVertexData_ = *other.registeredVertexData_;
		*registeredEdgeData_ = *other.registeredEdgeData_;
	}
	return *this;
}

structures::GraphWithRegistration::GraphWithRegistration(Table<const GraphData*, const GraphData*>* tableForVertexDataRegistration, Table<const GraphData*, const GraphData*>* tableForEdgeDataRegistration) :
	registeredVertexData_(tableForVertexDataRegistration),
	registeredEdgeData_(tableForEdgeDataRegistration)
{
}

bool structures::GraphWithRegistration::areDataRegistered(GraphDataType dataType, const GraphData * key) const
{
	const GraphData * tmpKey;
	switch (dataType)
	{
	case GraphDataType::VERTEX_DATA:
		return registeredVertexData_->tryFind(key->getClassKey(), tmpKey);
	case GraphDataType::EDGE_DATA:
		return registeredEdgeData_->tryFind(key->getClassKey(), tmpKey);
	default:
		return false;
	}
}

void structures::GraphWithRegistration::registerData(GraphDataType dataType, const GraphData * key)
{
	const GraphData * tmpKey;
	bool error = true;
	switch (dataType)
	{
	case GraphDataType::VERTEX_DATA:
		if (!registeredVertexData_->tryFind(key->getClassKey(), tmpKey))
		{
			registeredVertexData_->insert(key->getClassKey(), key->getClassKey());
			error = false;
		}
		break;
	case GraphDataType::EDGE_DATA:
		if (!registeredEdgeData_->tryFind(key->getClassKey(), tmpKey))
		{
			registeredEdgeData_->insert(key->getClassKey(), key->getClassKey());
			error = false;
		}
		break;
	}

	if (error)
	{
		throw std::logic_error("GraphWithRegistration::registerData: Data with given key are already registered for given dataType.");
	}
}

void structures::GraphWithRegistration::unregisterData(GraphDataType dataType, const GraphData * key)
{
	bool error = true;
	switch (dataType)
	{
	case GraphDataType::VERTEX_DATA:
		error = !tryUnregisterVertexData(key->getClassKey());
		break;
	case GraphDataType::EDGE_DATA:
		error = !tryUnregisterEdgeData(key->getClassKey());
		break;
	}

	if (error)
	{
		throw std::logic_error("GraphWithRegistration::unregisterData: Data with given key are not registered for given dataType.");
	}
}

bool structures::GraphWithRegistration::tryUnregisterVertexData(const GraphData * key)
{
	if (areDataRegistered(GraphDataType::VERTEX_DATA, key))
	{
		LinkedList<GraphVertex*> verticesList;
		getVertices(verticesList);

		for (GraphVertex* item : verticesList)
		{
			if (item->containsData(key))
			{
				item->removeData(key);
			}
		}
		registeredVertexData_->remove(key);
		return true;
	}
	return false;
}

bool structures::GraphWithRegistration::tryUnregisterEdgeData(const GraphData * key)
{
	if (areDataRegistered(GraphDataType::EDGE_DATA, key))
	{
		LinkedList<GraphEdge*> edgeList;
		getEdges(edgeList);

		for (GraphEdge* edge : edgeList)
		{
			if (edge->containsData(key))
			{
				edge->removeData(key);
			}
		}
		registeredEdgeData_->remove(key);
		return true;
	}
	return false;
}
