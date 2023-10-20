/*
* Filename: graph.cc
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "graph.h"

namespace geom
{
    Graph::Graph(std::size_t numVertices, std::size_t numEdges)
    {
        // Resizes the adjacency list and matrix according to the number of vertices in the
        // graph
        this->m_vertices.Resize(numVertices);
        this->m_numEdges = numEdges;
    }

    Graph::~Graph() { }

    void Graph::AddVertex(Vertex newVertex)
    {
        this->m_vertices[newVertex.GetID()] = newVertex;
    }

    void Graph::AddEdge(std::size_t vertexID, std::size_t neighborID, uint32_t constructionYear,
                        uint32_t crossingTime, uint32_t buildCost)
    {
        // Create a ptr for the edge
        std::shared_ptr<Edge> edge = std::make_shared<Edge>(vertexID, neighborID, constructionYear, crossingTime, buildCost);

        // Add the edge to the neighbor list of vertexID
        this->m_vertices[vertexID].GetAdjacencyList()->PushBack(edge);

        // Add the same edge to the neighbor list of neighborID
        this->m_vertices[neighborID].GetAdjacencyList()->PushBack(edge);
    }

    bool Graph::Relax(Vertex *u, Vertex *v, std::shared_ptr<Edge> uv, Defs::EDGE_INFO edgeInfo)
    {
        if (v->GetCost() > (u->GetCost() + uv->GetSpecifiedCost(edgeInfo)))
        {
            v->SetCost(u->GetCost() + uv->GetSpecifiedCost(edgeInfo));
            v->SetEdge2Father(uv); // uv and vu must be the same
            return true;
        }
        return false;
    }

    void Graph::Dijkstra(std::size_t source, Defs::EDGE_INFO edgeInfo)
    {
        heap::PriorityQueue<Vertex*, Vertex::CompareVertex> minPQueue;

        // Initialize all vertex costs to infinity
        // Add all vertices to the priority queue
        for (std::size_t i = 0; i < this->m_vertices.Size(); i++)
        {
            if (i != source)
                this->m_vertices[i].SetCost(Defs::INFINITY_VALUE);

            this->m_vertices[i].SetEdge2Father(nullptr);
        }

        this->m_vertices[source].SetCost(0);
        minPQueue.Enqueue(&this->m_vertices[source]);

        // Auxiliar variables to make code most legible
        Vertex* u = nullptr;
        Vertex* v = nullptr;
        uint32_t maxEdgeConstructionYear = 0;
        std::pair<std::size_t, std::size_t> uv;

        Vector<std::shared_ptr<Edge>>* uAdjList = nullptr;

        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList->Size(); i++)
            {
                uv = uAdjList->At(i)->GetVertices(); // Edge uv (or vu, is non-directed)

                // Get the pointer do neighbor vertex, since one end of the edge is vertex u,
                // and the other end is vertex v
                uv.first == u->GetID() ? v = &this->m_vertices[uv.second]
                                       : v = &this->m_vertices[uv.first];

                if (this->Relax(u, v, uAdjList->At(i), edgeInfo))
                {
                    // If the neighbor's cost is updated, then add again to queue to
                    // update all neighbors with new cost
                    minPQueue.Enqueue(v);
                }
            }
        }

        for (std::size_t i = 0; i < this->m_vertices.Size(); i++)
        {
            printf("%zu\n", this->m_vertices[i].GetCost());

            // Source has not a edge to father
            // Get the max construction year of the edges that are part of the shortest path
            if (i != source and this->m_vertices[i].GetEdge2Father()->GetConstructionYear() > maxEdgeConstructionYear)
                maxEdgeConstructionYear = this->m_vertices[i].GetEdge2Father()->GetConstructionYear();
        }

        printf("%u\n", maxEdgeConstructionYear);
    }

    void Graph::PrimMST(std::size_t source, Defs::EDGE_INFO edgeInfo)
    {
        heap::PriorityQueue<std::shared_ptr<Edge>, Edge::CompareEdges> minPQueue((Edge::CompareEdges(edgeInfo)));

        // Auxiliar variables to make code most legible
        std::shared_ptr<Edge> u = nullptr;
        std::shared_ptr<Edge> v = nullptr;
        std::pair<std::size_t, std::size_t> uv;
        uint32_t maxEdgeConstructionYear = 0;
        bool uInMST, vInMST;
        Vector<std::shared_ptr<Edge>>* uAdjList = nullptr;

        // Initialize all vertex costs to infinity
        // Add all vertices to the priority queue
        for (std::size_t i = 0; i < this->m_vertices.Size(); i++)
        {
            this->m_vertices[i].SetVisited(false);

            uAdjList = this->m_vertices[i].GetAdjacencyList();
            for (std::size_t j = 0; j < uAdjList->Size(); j++)
            {
                uAdjList->At(j)->SetInMST(false);
                minPQueue.Enqueue(uAdjList->At(j));
            }
        }

        this->m_vertices[source].SetVisited(true);
        Vector<std::shared_ptr<Edge>> MST;


        uAdjList = this->m_vertices[source].GetAdjacencyList();
        for (std::size_t i = 0; i < uAdjList->Size(); i++)
        {
            minPQueue.Enqueue(uAdjList->At(i));
        }

        Vector<std::shared_ptr<Edge>> aux;
        while (not minPQueue.IsEmpty())
        {
            u = minPQueue.Dequeue();
            uv = u->GetVertices();

            if (u->IsInMST())
                continue;

            uInMST = this->m_vertices[uv.first].WasVisited();
            vInMST = this->m_vertices[uv.second].WasVisited();

            if (uInMST != vInMST) // If b not in A
            {
                this->m_vertices[uv.second].SetVisited(true);
                this->m_vertices[uv.first].SetVisited(true);
                MST.PushBack(u);
                u->SetInMST(true);

                uAdjList = this->m_vertices[uv.second].GetAdjacencyList();
                for (std::size_t i = 0; i < uAdjList->Size(); i++)
                {
                    if (not uAdjList->At(i)->IsInMST())
                        minPQueue.Enqueue(uAdjList->At(i));
                }

                uAdjList = this->m_vertices[uv.first].GetAdjacencyList();
                for (std::size_t i = 0; i < uAdjList->Size(); i++)
                {
                    if (not uAdjList->At(i)->IsInMST())
                        minPQueue.Enqueue(uAdjList->At(i));
                }
            }
        }

        if (edgeInfo == Defs::YEAR)
        {
            for (auto edge : MST)
            {
                if (edge->GetConstructionYear() > maxEdgeConstructionYear)
                    maxEdgeConstructionYear = edge->GetConstructionYear();
            }

            printf("%u\n", maxEdgeConstructionYear);
        }

        if (edgeInfo == Defs::COST)
        {
            std::size_t mstCost = 0;
            for (auto edge : MST)
            {
                mstCost += edge->GetBuildCost();
            }

            printf("%zu\n", mstCost);
        }
    }
}
