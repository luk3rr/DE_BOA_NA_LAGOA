/*
* Filename: edge.cc
* Created on: September 17, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "edge.h"

namespace geom {
    Edge::Edge(uint32_t sideA, uint32_t sideB)
    {
        this->m_vertices = std::make_pair(sideA, sideB);
        this->m_constructionYear = 0;
        this->m_crossingTime = 0;
        this->m_buildCost = 0;
    }

    Edge::Edge(uint32_t sideA, uint32_t sideB, uint32_t constructionYear, uint32_t crossingTime, uint32_t buildCost)
    {
        this->m_vertices = std::make_pair(sideA, sideB);
        this->m_constructionYear = constructionYear;
        this->m_crossingTime = crossingTime;
        this->m_buildCost = buildCost;
    }

    Edge::Edge(const Edge &other)
    {
        this->m_vertices = other.m_vertices;
        this->m_constructionYear = other.m_constructionYear;
        this->m_crossingTime = other.m_crossingTime;
        this->m_buildCost = other.m_buildCost;
        this->m_inTree = other.m_inTree;
    }

    Edge::~Edge() { }

    Edge &Edge::operator=(const Edge &other)
    {
        if (this != &other)
        {
            this->m_vertices = other.m_vertices;
            this->m_constructionYear = other.m_constructionYear;
            this->m_crossingTime = other.m_crossingTime;
            this->m_buildCost = other.m_buildCost;
            this->m_inTree = other.m_inTree;
        }

        return *this;
    }

    bool Edge::operator<(const Edge &other)
    {
        // TODO: Implement this
        std::cerr << "Oh no! This function is not implemented. Please do not call it" << std::endl;
        return false;
    }

    void Edge::SetConstructionYear(uint32_t newYear)
    {
        this->m_constructionYear = newYear;
    }
    void Edge::SetCrossingTime(uint32_t newCrossingTime)
    {
        this->m_crossingTime = newCrossingTime;
    }

    void Edge::SetBuildCost(uint32_t newBuildCost)
    {
        this->m_buildCost = newBuildCost;
    }

    void Edge::SetInMST(bool isInTree)
    {
        this->m_inTree = isInTree;
    }

    uint32_t Edge::GetConstructionYear()
    {
        return this->m_constructionYear;
    }

    uint32_t Edge::GetCrossingTime()
    {
        return this->m_crossingTime;
    }

    uint32_t Edge::GetBuildCost()
    {
        return this->m_buildCost;
    }

    uint32_t Edge::GetSpecifiedCost(Defs::EDGE_INFO info) const
    {
        switch (info)
        {
            case Defs::EDGE_INFO::COST:
                return this->m_buildCost;

            case Defs::EDGE_INFO::YEAR:
                return this->m_constructionYear;

            case Defs::EDGE_INFO::TIME:
                return this->m_crossingTime;
            default:
                std::cerr << "Warning... the info is not defined. Don't trust the returned value" << std::endl;
                return 0;
        }
    }

    std::pair<std::size_t, std::size_t> Edge::GetVertices()
    {
        return this->m_vertices;
    }

    bool Edge::IsInMST()
    {
        return this->m_inTree;
    }
}
