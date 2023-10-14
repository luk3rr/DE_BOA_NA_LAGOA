/*
* Filename: graph.h
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <math.h>
#include <cstdint>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <string>

#include "vertex.h"
#include "vector.h"

namespace geom {
    class Graph {
        private:
            Vector<Vertex> m_vertices; // Each vector position is the vertex ID
            size_t m_numEdges; // number of edges in this graph

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
    };
}

#endif // GRAPH_H_
