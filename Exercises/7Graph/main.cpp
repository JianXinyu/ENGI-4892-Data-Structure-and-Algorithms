#include <iostream>
#include "graph.h"
#include "parse_csv.h"

int main() {

    //! Exercises for 15 Jul 2020 Adjacency Matrix
//    Graph<std::string, bool> g(4);
//    g.addVertex("A");
//    g.addVertex("B");
//    g.addVertex("C");
//    g.addVertex("D");
//    g.addEdge(0,1, true);
//    g.addEdge(1,2, true);
//    g.display();

    Graph<std::string, float> g;
    csvParser cfile("road-distances.csv");
    g = cfile.parse();
    g.display();
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
