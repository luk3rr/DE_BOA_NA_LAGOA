/*
* Filename: edge.h
* Created on: September 17, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef EDGE_H_
#define EDGE_H_

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <iostream>

#include "definitions.h"

namespace geom
{
    class Edge
    {
        private:
            std::pair<std::size_t, std::size_t> m_vertices; // Store vertices ID
            uint32_t m_constructionYear; // Year in which the edge construction was completed
            uint32_t m_crossingTime; // Traversal time (cost) of the edge
            uint32_t m_buildCost; // Construction cost of the edge

        public:
            Edge(uint32_t sideA, uint32_t sideB);
            Edge(uint32_t sideA, uint32_t sideB, uint32_t constructionYear,
                 uint32_t crossingTime, uint32_t buildCost);
            ~Edge();

            /**
             * @brief Overload operator <
             **/
            bool operator<(const Edge &other);

            /**
             * @brief Set a new year in which the edge construction was completed
             **/
            void SetConstructionYear(uint32_t newYear);

            /**
             * @brief Set a new traversal time (cost) of the edge
             **/
            void SetCrossingTime(uint32_t newCrossingTime);

            /**
             * @return Set a new construction cost of the edge
             **/
            void SetBuildCost(uint32_t newBuildCost);

            /**
             * @return Year in which the edge construction was completed
             **/
            uint32_t GetConstructionYear();

            /**
             * @return Traversal time (cost) of the edge
             **/
            uint32_t GetCrossingTime();

            /**
             * @return Construction cost of the edge
             **/
            uint32_t GetBuildCost();

            /**
             * @param info Type of the info
             * @return A specified cost, according the info parameter
             **/
            uint32_t GetSpecifiedCost(Defs::EDGE_INFO info);

            /**
             * @return std::pair<a, b>, where a, b are the vertices ID
             **/
            std::pair<std::size_t, std::size_t> GetVertices();
    };
}

#endif // EDGE_H_
