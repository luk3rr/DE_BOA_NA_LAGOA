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
#include <memory>
#include <ostream>
#include <utility>
#include <memory>
#include <vector>

#include "edge.h"

namespace geom
{
    class Vertex
    {
        private:
            bool m_visited; // Mark this vertex as visited
            double_t m_x, m_y; // Coordinates
            std::size_t m_id; // Vertex ID
            std::size_t m_cost; // Cost of this vertex

            std::vector<std::shared_ptr<Edge>> m_adjList; // Adjacency list
            std::shared_ptr<Edge> m_edge2Father; // Edge connecting to the parent vertex

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

            ~Vertex();

            /**
             * @brief Overload of the equality operator. For the purposes of this program,
             *        it is sufficient to consider two vertices equal when their coordinates
             *        are equal. In other cases, the ID and neighbors may be checked to define
             *        this equality.
             * @param other Vertex to be used in the comparison
             * @return True if the coordinates of the two vertices are equal one by one, False
             *         otherwise
             */
            bool operator==(const Vertex &other) const;

            /**
             * @brief Overload of the less operator. Compares two vertices based on their costs (m_cost)
             * @param other Vertex to be used in the comparison
             * @return True if the cost of this vertex is less than the cost of the other vertex, False otherwise
             */
            bool operator<(const Vertex &other) const;

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
             * @brief Set a new value for the cost
             * @param cost New value for the cost
             */
            void SetCost(std::size_t cost);

            /**
             * @brief Defines if this vertex was visited
             * @param isVisited True is this vertex was visited, False otherwise
             */
            void SetVisited(bool isVisited);

            /**
             * @brief Set the edge connecting to the parent vertex.
             * @param edge A shared pointer to the edge connecting this vertex to its parent.
             */
            void SetEdge2Father(std::shared_ptr<Edge> edge);

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
             * @return Value of the cost
             */
            std::size_t GetCost();

            /**
             * @return A shared pointer to the edge connecting this vertex to its parent
             */
            std::shared_ptr<Edge> GetEdge2Father();

            /**
             * @return isVisited True is this vertex was visited, False otherwise
             */
            bool WasVisited();

            /**
             * @return Address of the adjacency list of this vertex
             */
            std::vector<std::shared_ptr<Edge>>* GetAdjacencyList();
    };
}

#endif // VERTEX_H_
