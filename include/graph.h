/*
* Filename: graph.h
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <math.h>
#include <memory>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

#include <string>
#include <queue>
#include <utility>
#include <vector>
#include <memory>

#include "edge.h"
#include "vertex.h"

namespace geom
{
    class Graph
    {
        private:
            std::vector<Vertex> m_vertices; // Each vector position is the vertex ID
            std::size_t m_numEdges; // number of edges in this graph

        public:
            /**
             * @param numVertices Number of vertices in the graph
             * @param numEdges Number of edges in the graph
             **/
            Graph(std::size_t numVertices, std::size_t numEdges);

            ~Graph();

            /**
             * @brief Adds a vertex to the graph
             * @param vertex New vertex to be added to the graph
             **/
            void AddVertex(Vertex vertex);

            /**
             * @brief Adds a edge
             * @param vertexID ID of the vertex that will receive a neighbor
             * @param neighborID ID of the neighbor
             * @param constructionYear Year in which the edge construction was completed
             * @param Traversal time (cost) of the edge
             * @param Construction cost of the edge
             **/
            void AddEdge(std::size_t vertexID, std::size_t neighborID, uint32_t constructionYear,
                         uint32_t crossingTime, uint32_t buildCost);

            /**
             * @brief Relax the edge (u, v)
             * @param u, v Vertices of this edge
             * @param uv Pointer to the edge (u, v)
             * @param edgeInfo Type of cost considered in the shortest path calculation
             **/
            bool Relax(Vertex* u, Vertex* v, std::shared_ptr<Edge> uv, Defs::EDGE_INFO edgeInfo);

            /**
             * @brief Run Dijkstra's algorithm to find the shortest paths from a given source vertex
             * @param source The source vertex from which to calculate the shortest paths
             * @param edgeInfo Type of cost considered in the shortest path calculation
             **/
            void Dijkstra(std::size_t source, Defs::EDGE_INFO edgeInfo);

            /**
             * @brief Run Prim's algorithm to find Minimum Spanning Tree starting from a given
             *        source vertex
             * @param source The source vertex from which to begin the MST calculation
             * @param edgeInfo Type of cost considered in the MST calculation
             **/
            void PrimMST(std::size_t source, Defs::EDGE_INFO edgeInfo);
    };
}

#endif // GRAPH_H_
