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

//    //! Exercises for 17 Jul 2020
//    Graph<std::string, float> g;
//    csvParser cfile("road-distances.csv");
//    g = cfile.parse();
//    g.display();
//
//    //! Exercises for 20 Jul 2020
//    std::vector<float> distances = g.Dijkstra(5);
//    std::cout << "Distance from Portugal Cove: [ ";
//    std::cout << distances;
//    std::cout << " ]\n";

////! Exercises for 24 Jul 2020 Unweighted graphs
//    Graph<int, int> g;
//    for (int i : { 0, 1, 2, 3, 4 })
//    {
//        g.addVertex(i);
//    }
//    for (int from : { 0, 1, 2, 3, 4 })
//    {
//        size_t to = (3 * from) % 5;
//        int value = (4 * from) % 5;
//
//        g.addEdge(static_cast<size_t>(from), to, value);
//    }
//
//    std::cout << "Distance from 2: [";
//    std::vector<size_t> distances = g.shortestDistances(2);
//    std::cout << distances;
//    std::cout << " ]\n";

    //! test code for work list algorithm
    UnweightedGraph<std::string> cities;
    const auto StJohns = cities.addVertex("St. John's");
    const auto Gander = cities.addVertex("Gander");
    const auto DeerLake = cities.addVertex("Deer Lake");
    const auto Halifax = cities.addVertex("Halifax");
    const auto Montreal = cities.addVertex("Montreal");
    const auto Ottawa = cities.addVertex("Ottawa");
    const auto Toronto = cities.addVertex("Toronto");

    cities.addEdge(StJohns, Gander);
    cities.addEdge(StJohns, DeerLake);
    cities.addEdge(StJohns, Halifax);

    cities.addEdge(DeerLake, Halifax);
    cities.addEdge(DeerLake, Gander);

    cities.addEdge(Halifax, Montreal);
    cities.addEdge(Halifax, Toronto);

    cities.addEdge(Montreal, Ottawa);

    cities.addEdge(Toronto, Ottawa);

    std::cout << "Distances from St. John's:\n";
    std::vector<size_t> distances = cities.shortestDistances(StJohns);
    for ( size_t i = 0; i < distances.size(); i++)
    {
        std::cout
                << "  It takes " << distances[i]
                << " flights to get to " << cities[i]
                << "\n";
    }
    return 0;
}
