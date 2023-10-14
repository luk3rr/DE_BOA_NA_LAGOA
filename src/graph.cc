/*
* Filename: graph.cc
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "graph.h"

namespace geom {
    Graph::Graph(std::size_t numVertices, std::size_t numEdges) {
        // Resizes the adjacency list and matrix according to the number of vertices in the
        // graph
        this->m_vertices.resize(numVertices);
        this->m_numEdges = numEdges;
    }

    Graph::~Graph() { }

    void Graph::AddVertex(Vertex newVertex) {
        this->m_vertices[newVertex.GetID()] = newVertex;
    }

    void Graph::AddEdge(std::size_t vertexID, std::size_t neighborID, uint32_t constructionYear,
                        uint32_t crossingTime, uint32_t buildCost) {

        Vector<Edge>* neighborsList = this->m_vertices[vertexID].GetNeighborsList();
        neighborsList->push_back(geom::Edge(neighborID));
    }
}
