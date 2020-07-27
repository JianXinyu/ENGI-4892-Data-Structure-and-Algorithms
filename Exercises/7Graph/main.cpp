#include <iostream>
#include "graph.h"
#include "parse_csv.h"

//! Reload operator << to print std::vector type data
template <typename T>
std::ostream& operator << ( std::ostream& outs, const std::vector<T> &vec)
{
    std::size_t n = 0;
    for(const auto& entry : vec){
        outs << (n++? " " : "") << entry;
    }
    return outs;
}

int main() {

    //! Exercises for 15 Jul 2020
////    Graph<std::string, bool> g(4); //Adjacency Matrix
//    Graph<std::string, bool> g; //Adjacency list
//    g.addVertex("A");
//    g.addVertex("B");
//    g.addVertex("C");
//    g.addVertex("D");
//    g.addEdge(0,1, true);
//    g.addEdge(1,2, true);
//    g.display();

    //! Exercises for 17 Jul 2020
    Graph<std::string, float> g;
    csvParser cfile("road-distances.csv");
    g = cfile.parse();
    g.display();

    std::vector<float> distances = g.Dijkstra(5);
    std::cout << "Distance from Portugal Cove: [ ";
    std::cout << distances;
    std::cout << " ]\n";

 /*   Graph<int, int> g;
    for (int i : { 0, 1, 2, 3, 4 })
    {
        g.addVertex(i);
    }
    for (int from : { 0, 1, 2, 3, 4 })
    {
        size_t to = (3 * from) % 5;
        int value = (4 * from) % 5;

        g.addEdge(static_cast<size_t>(from), to, value);
    }

    std::cout << "Distance from 2: [";
    for (size_t d : g.shortestDistances(2))
    {
        std::cout << " " << d;
    }
    std::cout << " ]\n";*/

    return 0;
}
