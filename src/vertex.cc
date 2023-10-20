/*
* Filename: vertex.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "vertex.h"
#include <memory>

namespace geom
{
    Vertex::Vertex()
    {
        this->m_x = this->m_y = this->m_id = 0;
        this->m_visited = false;
        this->m_edge2Father = nullptr;
    }

    Vertex::Vertex(std::size_t id)
    {
        this->m_x = this->m_y = 0;
        this->m_id = id;
        this->m_visited = false;
        this->m_edge2Father = nullptr;
    }

    Vertex::Vertex(double_t x, double_t y, std::size_t id)
    {
        this->m_x = x;
        this->m_y = y;
        this->m_id = id;
        this->m_visited = false;
        this->m_edge2Father = nullptr;
    }

    Vertex::~Vertex() { }

    bool Vertex::operator==(const Vertex &vertex) const
    {
        return (this->m_cost == vertex.m_cost);
    }

    bool Vertex::operator<=(const Vertex &vertex) const
    {
        return (this->m_cost <= vertex.m_cost);
    }

    bool Vertex::operator>=(const Vertex &vertex) const
    {
        return (this->m_cost >= vertex.m_cost);
    }

    bool Vertex::operator<(const Vertex &other) const
    {
        return (this->m_cost < other.m_cost);
    }

    bool Vertex::operator>(const Vertex &other) const
    {
        return (this->m_cost > other.m_cost);
    }

    void Vertex::SetX(double_t x)
    {
        this->m_x = x;
    }

    void Vertex::SetY(double_t y)
    {
        this->m_y = y;
    }

    void Vertex::SetID(std::size_t id)
    {
        this->m_id = id;
    }

    void Vertex::SetCost(std::size_t cost)
    {
        this->m_cost = cost;
    }

    void Vertex::SetVisited(bool isVisited)
    {
        this->m_visited = isVisited;
    }

    void Vertex::SetEdge2Father(std::shared_ptr<Edge> edge)
    {
        this->m_edge2Father = edge;
    }

    double_t Vertex::GetX()
    {
        return this->m_x;
    }

    double_t Vertex::GetY()
    {
        return this->m_y;
    }

    uint32_t Vertex::GetDegree()
    {
        return this->m_adjList.Size();
    }

    std::size_t Vertex::GetID()
    {
        return this->m_id;
    }

    std::size_t Vertex::GetCost() const
    {
        return this->m_cost;
    }

    std::shared_ptr<Edge> Vertex::GetEdge2Father()
    {
        return m_edge2Father;
    }

    bool Vertex::WasVisited()
    {
        return this->m_visited;
    }

    Vector<std::shared_ptr<Edge>>* Vertex::GetAdjacencyList()
    {
        return &m_adjList;
    }
}
