/**
 * Author: Xinyu Jian
 */

//! ExerciseS for 27 Jul 2020 betweenness centrality
#ifndef GRAPH_BCENTRALITY_H
#define GRAPH_BCENTRALITY_H
#include <vector>

template <typename V, typename E>
class bcGraph
{
public:
    using VertexID = size_t;
    const E INF = std::numeric_limits<E>::max();

    VertexID addVertex(V value)
    {
        VertexID id = vertices_.size();
        Vertex v = { .id = id, .name = std::move(value), .count = 0};
        vertices_.push_back(std::move(v));
        return id;
    }

    bcGraph &addEdge(VertexID from, VertexID to, E value)
    {
        Edge e = { .from = from, .to = to, .data = std::move(value) };
        edges_.push_back(std::move(e));
        return *this;
    }

    void display()
    {
        std::cout << "\n"
                     "    Vertx    │ID│ Edge(value)           \n"
                     "─────────────┼──┼───────────────────────\n";
        for(auto & v : vertices_)
        {
            std::cout << std::left << std::setw( 13 ) << v.name << "|" << v.id << " | ";
            for(auto & e : edges_)
            {
                if(e.from == v.id)
                    std::cout <<  e.to << "(" << e.data << "), ";
            }
            std::cout << '\n';
        }
    }

    /**
     * weighted shortest path & the number of times that interest vertex is passed
     * calculate via Dijkstra's algorithm
     * @param source vertex
     * @param interest vertex
     * @return a vector contains the shortest distance from a source vertex
     *          to all other vertices.
     */
    std::vector<E> Dijkstra(VertexID source, VertexID interest)
    {
        const size_t N = vertices_.size();
        std::vector<E> distances(N, INF);
        std::vector<VertexID> path(N);
        std::vector<bool> done(N, false);
        //The distance from the source vertex (s) to itself is 0
        distances[source] = 0;

        // while there is a vertex remains not done
        while (std::count(done.begin(), done.end(), false))
        {
            // find the vertex that is not done with the smallest distance
            VertexID v = minDistance(distances, done);

            // for each vertex w adjacent to v
            for (VertexID w : adjacencies(v))
            {
                if(!done[w])
                {
                    E cvw = costv2w(v, w); // cost of edge from v to w

                    if(distances[w] > distances[v] + cvw)
                    {
                        distances[w] = distances[v] + cvw;
                        path[w] = v;
                        if(v == interest & v != source)
                        {
                            vertices_[interest].count++;
                        }
                    }
                }
            }
            done[v] = true;
        }

        return distances;
    }

    /**
     * calculate the betweenness centrality of a vertex in the graph.
     * we assume that the shortest path from vertex s to vertex t is unique,
     * which means that sigma_{st} = 1,sigma_{st}(v)=1 or 0.
     * @param interest vertex
     * @return betweenness centrality
     */
    int betweenness_centrality(VertexID interest)
    {
        std::vector<E> tmp; // temporary vector to store the shortest distances from a vertex to other vertices
        int count = 0; // count of how many shortest path
        // iterate to calculate shortest path for every vertex
        for(VertexID id = 0; id < vertices_.size(); id++)
        {
            tmp = Dijkstra(id, interest);
        }
        return vertices_[interest].count;
    }

private:
    /**
     * a helper function to find all vertices adjacent to a vertex v
     * note that adjacent relationship is directed
     * @param v
     * @return a vector contains the vertices adjacent to v
     */
    std::vector<VertexID> adjacencies(VertexID v)
    {
        std::vector<VertexID> adjacencies;

        for (const Edge &e : edges_)
        {
            if (e.from == v)
            {
                adjacencies.push_back(e.to);
            }
        }
        return adjacencies;
    };

    /**
     * A helper function to return the weight from vertex v to vertex w
     */
    E costv2w(VertexID v, VertexID w)
    {
        E weight = 0;
        for(Edge &edge : edges_)
        {
            if(edge.from == v and edge.to == w)
                weight = edge.data;
        }
        return weight;
    }

    /**
     * A helper function to find the vertex that is not done with minimum distance
     * @param distances
     * @param done
     * @return vertex id
     */
    VertexID minDistance(std::vector<E> distances, std::vector<bool> done)
    {
        VertexID idx;
        // Initialize min value
        E min = std::numeric_limits<E>::max();

        for (VertexID w = 0; w < distances.size(); w++)
            if (done[w] == false && distances[w] <= min)
                min = distances[w], idx = w;

        return idx;
    }

    struct Vertex
    {
        VertexID    id;
        V           name;
        int         count; // number of times that this vertex is passed through
    };
    struct Edge
    {
        VertexID    from;
        VertexID    to;
        E           data;
    };

    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
};

#endif //GRAPH_BCENTRALITY_H
