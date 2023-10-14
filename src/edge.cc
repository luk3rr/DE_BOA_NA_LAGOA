/*
* Filename: edge.cc
* Created on: September 17, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "edge.h"

namespace geom {
    Edge::Edge(uint32_t dest) {
        this->m_dest = dest;
        this->m_constructionYear = 0;
        this->m_crossingTime = 0;
        this->m_buildCost = 0;
    }

    Edge::~Edge() { }

    bool Edge::operator<(const Edge &other) {
        return false; // TODO: Change this
    }

    void Edge::SetConstructionYear(uint32_t newYear) {
        this->m_constructionYear = newYear;
    }
    void Edge::SetCrossingTime(uint32_t newCrossingTime) {
        this->m_crossingTime = newCrossingTime;
    }

    void Edge::SetBuildCost(uint32_t newBuildCost) {
        this->m_buildCost = newBuildCost;
    }

    uint32_t Edge::GetConstructionYear() {
        return this->m_constructionYear;
    }

    uint32_t Edge::GetCrossingTime() {
        return this->m_crossingTime;
    }

    uint32_t Edge::GetBuildCost() {
        return this->m_buildCost;
    }

    uint32_t Edge::GetDest() {
        return this->m_dest;
    }
}
