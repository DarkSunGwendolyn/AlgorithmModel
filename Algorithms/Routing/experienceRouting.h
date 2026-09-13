#ifndef EXPERIENCEROUTING_H
#define EXPERIENCEROUTING_H

#include "routingAlgorithm.h"
#include "routingTable.h"

class ExperienceRouting : public RoutingAlgorithm
{
public:
    QVector<int> getNextVertices(
        const Graph &graph,
        const Packet &packet
        ) override;

    const QVector<RoutingTable>& getRoutingTables() const;

    void clearRoutingTables();

private:
    QVector<RoutingTable> routingTables;

    void initializeRoutingTables(
        int vertexCount);

    void updateRoutingTables(
        const Packet &packet);

    QVector<int> findNeighbors(
        const Graph &graph,
        int currentVertex
        ) const;

    int findBestVertex(
        const QVector<int> &neighbors,
        int destination
        ) const;
};

#endif // EXPERIENCEROUTING_H
