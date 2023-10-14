/*
* Filename: vertex.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "vertex.h"

namespace geom {
    Vertex::Vertex() {
        this->m_x = this->m_y = this->m_id = 0;
    }

    Vertex::Vertex(std::size_t id) {
        this->m_x = this->m_y = 0;
        this->m_id = id;
    }

    Vertex::Vertex(double_t x, double_t y, std::size_t id) {
        this->m_x = x;
        this->m_y = y;
        this->m_id = id;
    }

    bool Vertex::operator==(const Vertex &vertex) const {
        return (this->m_x == vertex.m_x and this->m_y == vertex.m_y);
    }

    void Vertex::SetX(double_t x) {
        this->m_x = x;
    }

    void Vertex::SetY(double_t y) {
        this->m_y = y;
    }

    void Vertex::SetID(std::size_t id) {
        this->m_id = id;
    }

    double_t Vertex::GetX() {
        return this->m_x;
    }

    double_t Vertex::GetY() {
        return this->m_y;
    }

    uint32_t Vertex::GetDegree() {
        return this->m_neighbors.size();
    }

    std::size_t Vertex::GetID() {
        return this->m_id;
    }

    std::vector<Edge>* Vertex::GetNeighborsList() {
        return &m_neighbors;
    }
}
