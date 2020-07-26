#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip> //std::setw

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
//! Exercises for 20 Jul 2020 [Shortest Paths]
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
        std::vector<VertexID> path(N);
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

                for (VertexID n : neighbours(v))
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

    std::vector<VertexID> neighbours(VertexID v)
    {
         std::vector<VertexID> neighbours;

         for (const Edge &e : edges_)
         {
             if (e.from == v)
             {
                 neighbours.push_back(e.to);
             }
             else if (e.to == v)
             {
                 neighbours.push_back(e.from);
             }
         }
         return neighbours;
    };
private:
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

#endif //GRAPH_GRAPH_H
