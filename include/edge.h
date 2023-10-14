/*
* Filename: edge.h
* Created on: September 17, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef EDGE_H_
#define EDGE_H_

#include <cmath>
#include <cstdint>

namespace geom {
    class Edge {
        private:
            uint32_t m_dest; // ID of the destination vertex of this edge
            uint32_t m_constructionYear; // Year in which the edge construction was completed
            uint32_t m_crossingTime; // Traversal time (cost) of the edge
            uint32_t m_buildCost; // Construction cost of the edge

        public:
            Edge(uint32_t dest);
            ~Edge();

            /**
             * @brief
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
             * @return ID of the destination vertex of this edge
             **/
            uint32_t GetDest();
    };
}

#endif // EDGE_H_
