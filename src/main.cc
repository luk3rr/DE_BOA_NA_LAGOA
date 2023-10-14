/*
* Filename: main.cc
* Created on: September 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "graph.h"

int main(int argc, char *argv[]) {
    std::size_t numVertices, numEdges;

    scanf("%zu %zu", &numVertices, &numEdges);

    geom::Graph graph(numVertices, numEdges);

    for (std::size_t i = 0; i < numVertices; i++) {
        // Vertex is created with ID i
        graph.AddVertex(geom::Vertex(i));
    }

    std::size_t u, v; // Vertices u and v
    uint32_t constructionYear, crossingTime, buildCost;

    for (std::size_t i = 0; i < numEdges; i++) {
        scanf("%zu %zu %u %u %u", &u, &v, &constructionYear, &crossingTime, &buildCost);
        graph.AddEdge(u, v, constructionYear, crossingTime, buildCost);
    }

    return EXIT_SUCCESS;
}
