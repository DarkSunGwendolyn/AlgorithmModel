#include "experienceRouting.h"

QVector<int> ExperienceRouting::getNextVertices(
    const Graph &graph,
    const Packet &packet)
{
    const int vertexCount = graph.getVertices().size();

    initializeRoutingTables(vertexCount);

    updateRoutingTables(packet);

    QVector<int> neighbors =
        findNeighbors(
        graph,
        packet.currentVertex
        );


    if (neighbors.isEmpty())
    {
        return {};
    }

    int bestVertex =
        findBestVertex(
        neighbors,
        packet.destination
        );

    if (bestVertex != -1)
    {
        return {bestVertex};
    }

    return {neighbors.first()};
}

void ExperienceRouting::initializeRoutingTables(
    int vertexCount)
{
    if (routingTables.size() == vertexCount)
    {
        return;
    }

    routingTables.clear();

    for (int i = 0; i < vertexCount; ++i)
    {
        RoutingTable table;

        table.vertex = i;
        table.distances.fill(-1, vertexCount);
        table.distances[i] = 0;

        routingTables.append(table);
    }
}

void ExperienceRouting::updateRoutingTables(
    const Packet &packet)
{
    const QVector<int> &route = packet.route;

    for (int i = 0; i < route.size(); ++i)
    {
        int currentVertex = route[i];

        for (int j = i; j < route.size(); ++j)
        {
            int targetVertex = route[j];
            int distance = j - i;

            int &knownDistance =
                routingTables[currentVertex].distances[targetVertex];

            if (knownDistance == -1 ||
                distance < knownDistance)
            {
                knownDistance = distance;
            }
        }
    }
}

QVector<int> ExperienceRouting::findNeighbors(
    const Graph &graph,
    int currentVertex) const
{
    QVector<int> nextVertices;

    for (const Edge &edge : graph.getEdges())
    {
        if (edge.from == currentVertex)
        {
            nextVertices.append(edge.to);
        }
    }

    return nextVertices;
}

int ExperienceRouting::findBestVertex(
    const QVector<int> &neighbors,
    int destination
    ) const
{
    int bestVertex = -1;
    int bestDistance = -1;

    for (int vertex : neighbors)
    {
        int distance =
            routingTables[vertex].distances[destination];

        if (distance != -1)
        {
            if (bestDistance == -1 ||
                distance < bestDistance)
            {
                bestVertex = vertex;
                bestDistance = distance;
            }
        }
    }

    return bestVertex;
}

const QVector<RoutingTable>& ExperienceRouting::getRoutingTables() const
{
    return routingTables;
}

void ExperienceRouting::clearRoutingTables()
{
    routingTables.clear();
}
