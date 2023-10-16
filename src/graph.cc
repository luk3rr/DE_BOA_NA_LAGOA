/*
* Filename: graph.cc
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "graph.h"

namespace geom {
    Graph::Graph(std::size_t numVertices, std::size_t numEdges)
    {
        // Resizes the adjacency list and matrix according to the number of vertices in the
        // graph
        this->m_vertices.resize(numVertices);
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
        // Create a shared_ptr for the edge
        std::shared_ptr<Edge> edge = std::make_shared<Edge>(vertexID, neighborID, constructionYear, crossingTime, buildCost);

        // Add the edge to the neighbor list of vertexID
        this->m_vertices[vertexID].GetAdjacencyList()->push_back(edge);

        // Add the same edge to the neighbor list of neighborID
        this->m_vertices[neighborID].GetAdjacencyList()->push_back(edge);
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
        std::priority_queue<Vertex*, std::vector<Vertex*>, std::greater<Vertex*>> minPQueue;

        // Initialize all vertex costs to infinity
        // Add all vertices to the priority queue
        for (std::size_t i = 0; i < this->m_vertices.size(); i++)
        {
            if (i != source)
                this->m_vertices[i].SetCost(Defs::INFINITY_VALUE);

            this->m_vertices[i].SetEdge2Father(nullptr);
            minPQueue.push(&this->m_vertices[i]);
        }

        this->m_vertices[source].SetCost(0);

        // Auxiliar variables to make code most legible
        Vertex* u = nullptr;
        Vertex* v = nullptr;
        uint32_t maxEdgeConstructionYear = 0;
        std::pair<std::size_t, std::size_t> uv;
        std::vector<std::shared_ptr<Edge>>* uAdjList = nullptr;

        while (not minPQueue.empty())
        {
            u = minPQueue.top();
            minPQueue.pop();

            uAdjList = u->GetAdjacencyList();

            for (std::size_t i = 0; i < uAdjList->size(); i++)
            {
                uv = uAdjList->at(i)->GetVertices(); // Edge uv (or vu, is non-directed)

                // Get the pointer do neighbor vertex, since one end of the edge is vertex u,
                // and the other end is vertex v
                uv.first == u->GetID() ? v = &this->m_vertices[uv.second]
                                       : v = &this->m_vertices[uv.first];

                if (this->Relax(u, v, uAdjList->at(i), edgeInfo))
                {
                    // If the neighbor's cost is updated, then add again to queue to
                    // update all neighbors with new cost
                    minPQueue.push(v);
                }
            }
        }

        for (std::size_t i = 0; i < this->m_vertices.size(); i++)
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
        std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>,
                            CompareEdges> minPQueue((CompareEdges(edgeInfo)));

        // Auxiliar variables to make code most legible
        std::shared_ptr<Edge> u = nullptr;
        std::shared_ptr<Edge> v = nullptr;
        std::pair<std::size_t, std::size_t> uv;
        uint32_t maxEdgeConstructionYear = 0;
        std::vector<std::shared_ptr<Edge>>* uAdjList = nullptr;
        std::size_t tmp;

        // Initialize all vertex costs to infinity
        // Add all vertices to the priority queue
        for (std::size_t i = 0; i < this->m_vertices.size(); i++)
        {
            this->m_vertices[i].SetEdge2Father(nullptr);
            this->m_vertices[i].SetVisited(false);
            uAdjList = this->m_vertices[i].GetAdjacencyList();

            for (std::size_t j = 0; j < uAdjList->size(); j++)
            {

                uv = uAdjList->at(j)->GetVertices(); // Edge uv (or vu, is non-directed)

                // Get the pointer do neighbor vertex, since one end of the edge is vertex u,
                // and the other end is vertex v
                uv.first == i ? tmp = uv.second
                              : tmp = uv.first;

                if (tmp < i)
                    continue;

                minPQueue.push(uAdjList->at(j));
            }
        }

        this->m_vertices[source].SetVisited(true);

        std::vector<std::shared_ptr<Edge>> MST;
        std::queue<std::shared_ptr<Edge>> tempQueue;

        while (not minPQueue.empty())
        {
            u = minPQueue.top();
            minPQueue.pop();
            uv = u->GetVertices();

            bool u_in_MST = this->m_vertices[uv.first].WasVisited();
            bool v_in_MST = this->m_vertices[uv.second].WasVisited();

            if (u_in_MST != v_in_MST)
            {
                // Pelo menos um vértice está na MST, e o outro não está
                this->m_vertices[uv.first].SetVisited(true);
                this->m_vertices[uv.second].SetVisited(true);
                MST.push_back(u);

                while (not tempQueue.empty())
                {
                    minPQueue.push(tempQueue.front());
                    tempQueue.pop();
                }
            }
            else if (not u_in_MST and not v_in_MST)
            {
                tempQueue.push(u);
            }
        }

       // std::cout << "MST" << std::endl;
       // for (auto edge : MST)
       // {
       //     uv = edge->GetVertices();
       //     std::cout << "E(" << uv.first + 1 << ", " << uv.second + 1 << ")" << " COST " << edge->GetSpecifiedCost(edgeInfo) << std::endl;
       // }

        if (edgeInfo == Defs::YEAR)
        {
            for (auto edge : MST)
            {
                if (edge->GetConstructionYear() > maxEdgeConstructionYear)
                    maxEdgeConstructionYear = edge->GetConstructionYear();

                //uv = edge->GetVertices();
                //std::cout << "E(" << uv.first + 1 << ", " << uv.second + 1 << ")" << " COST " << edge->GetSpecifiedCost(edgeInfo) << std::endl;
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
