/*
* Filename: vertex.h
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef VERTEX_H_
#define VERTEX_H_

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <utility>
#include <vector>

#include "edge.h"

namespace geom {
    class Vertex {
        private:
            double_t m_x, m_y;
            std::size_t m_id;
            std::vector<Edge> m_neighbors;

        public:
            Vertex();

            /**
             * @brief Constructor overload
             * @param id Vertex ID
             */
            Vertex(std::size_t m_id);

            /**
             * @brief Constructor overload
             * @param x, y Point coordinates
             * @param degree Vertex degree
             * @param id Vertex ID
             */
            Vertex(double_t x, double_t y, std::size_t id);

            /**
             * @brief Overload of the equality operator. For the purposes of this program,
             *        it is sufficient to consider two vertices equal when their coordinates
             *        are equal. In other cases, the ID and neighbors may be checked to define
             *        this equality.
             * @param vertex Vertex to be used in the comparison
             * @return True if the coordinates of the two vertices are equal one by one, False
             *         otherwise
             */
            bool operator==(const Vertex &point) const;

            /**
             * @brief Set a new value for the X-coordinate
             * @param x New value of the X-coordinate
             */
            void SetX(double_t x);

            /**
             * @brief Set a new value for the Y-coordinate
             * @param y New value of the Y-coordinate
             */
            void SetY(double_t y);

            /**
             * @brief Set a new value for the vertex ID
             * @param id New value for the vertex ID
             */
            void SetID(std::size_t id);

            /**
             * @return Value of the X-coordinate
             */
            double_t GetX();

            /**
             * @return Value of the Y-coordinate
             */
            double_t GetY();

            /**
             * @return Value of the vertex degree
             */
            uint32_t GetDegree();

            /**
             * @return Value of the vertex ID
             */
            std::size_t GetID();

            /**
             * @return Address of the vector of neighbors of the current vertex
             */
            std::vector<Edge> *GetNeighborsList();
    };
}

#endif // VERTEX_H_
