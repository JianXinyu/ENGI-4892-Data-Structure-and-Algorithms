#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip> // std::setw
#include <algorithm> // std::min_element
#include <set>
#include <queue>

//! Exercises for 15 Jul 2020 Adjacency Matrix
/*
template<typename V, typename E>
class Graph
{
public:
    using VertexID = size_t;

    Graph(int num) : numVert_{num}
    {
        edges_ = new E* [numVert_];
        for (VertexID i = 0; i < numVert_; i++)
        {
            edges_[i] = new E [numVert_];
            for (VertexID j = 0; j < numVert_; j++)
            {
                edges_[i][j] = 0;
            }
        }
    }

    */
/*
     * Add a vertex and return its ID, which is used in representing the edge
     *//*

    VertexID addVertex(V value)
    {
        VertexID id = vertices_.size();
        std::cout << "ID of Vertex " << value << " is " << id << std::endl;
        vertices_.push_back(std::move(value));
        return id;
    };

    */
/*
     * Add an edge between two vertices, representing by their ID
     *//*

    Graph& addEdge(VertexID from, VertexID to, E value)
    {
        if(from > numVert_-1 || to > numVert_-1 || from < 0 || to < 0)
            std::cout << "Invalid edge index! \n";
        else
            edges_[from][to] = value;

        return *this;
    };

    */
/*
     * Print the graph
     *//*

    void display()
    {
        std::cout << "  ";
        for(int i = 0; i < numVert_; i++)
        {
            std::cout << vertices_.at(i) << " ";
        }
        std::cout << '\n';

        for (int i = 0; i < numVert_; i++)
        {
            std::cout << vertices_.at(i) << " ";
            for (int j = 0; j < numVert_; j++)
            {
                std::cout << edges_[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
private:
    int numVert_; // number of vertices
    std::vector<V> vertices_;
    E** edges_;
};
*/

//! Exercises for 15 Jul 2020 Adjacency List
//! Exercises for 20 Jul 2020 Shortest Paths
//! Exercises for 24 Jul 2020 Unweighted graphs
template <typename V, typename E>
class Graph
{
public:
    using VertexID = size_t;

    VertexID addVertex(V value)
    {
        VertexID id = vertices_.size();
        Vertex v = { .id = id, .name = std::move(value)};
        vertices_.push_back(std::move(v));
        return id;
    }

    Graph &addEdge(VertexID from, VertexID to, E value)
    {
        Edge e = { .from = from, .to = to, .data = std::move(value) };
        edges_.push_back(std::move(e));
        return *this;
    }

    void display()
    {
        std::cout << "\n"
                     "    Vertx    ©¦ID©¦ Edge(value)           \n"
                     "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";
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
     * weighted shortest path
     * calculate via Dijkstra's algorithm
     * @param source vertex
     * @return a vector contains the shortest distance from a source vertex
     *          to all other vertices.
     */
    std::vector<E> Dijkstra(VertexID source)
    {
        const size_t N = vertices_.size();
        const E INF = std::numeric_limits<E>::max();
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
                    }
                }
            }
            done[v] = true;
        }

        return distances;
    }

    /**
     * unweighted shortest path
     * Calculate the shortest distances from a source vertex to
     * all other vertices.
     *
     * This assumes that all edges are equally-weighted for the purposes
     * of comparing distances
     */
     std::vector<size_t> shortestDistances(VertexID source)
    {
        const size_t N = vertices_.size();
        const size_t INF = std::numeric_limits<size_t>::max(); // the largest possible value for type size_t
        std::vector<size_t> distances(N, INF);
        std::vector<VertexID> path(N, -1);
        std::vector<bool> done(N, false);

        distances[source] = 0;

        for (size_t dist = 0; dist < N; dist++)
        {
            for (VertexID v = 0; v < N; v++)
            {
                if (done[v] or distances[v] != dist)
                {
                    continue;
                }

                for (VertexID n : adjacencies(v))
                {
                    if (distances[n] == INF)
                    {
                        distances[n] = dist + 1;
                        path[n] = v;
                    }
                }

                done[v] = true;
            }
        }

        return distances;
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

//! a class specially for unweighted shortest path problem
template <typename V>
class UnweightedGraph
{
public:
    using VertexID = size_t;
    VertexID addVertex(V value)
    {
        VertexID id = vertices_.size();
        vertices_.push_back(std::move(value));
        adjacencies_.emplace_back();

        return id;
    }

    UnweightedGraph& addEdge(VertexID from, VertexID to)
    {
        adjacencies_[from].insert(to);
        adjacencies_[to].insert(from);

        return *this;
    }

    const V& operator[] (size_t index) const
    {
        return vertices_[index];
    }

    /*
     * calculate the unweighted shortest path from a source
     * vertex to all other vertices.
     * using worklist algorithm.
     */

    std::vector<VertexID> shortestDistances(VertexID source)
    {
        int N = vertices_.size();
        const size_t INF = std::numeric_limits<size_t>::max();
        std::vector<size_t> distances(N, INF);
        std::vector<VertexID> path(N, -1);
        std::queue<VertexID> worklist;

        distances[source] = 0;
        worklist.push(source);

        while (not worklist.empty())
        {
            VertexID v = worklist.front();
            worklist.pop();

            for (VertexID n : adjacencies_[v])
            {
                if(distances[n] == INF)
                {
                    distances[n] = distances[v] + 1;
                    path[n] = v;
                    worklist.push(n);
                }
            }
        }
        return distances;
    }
private:
    std::vector<V> vertices_;
    std::vector<std::set< VertexID >> adjacencies_;
};
#endif //GRAPH_GRAPH_H
