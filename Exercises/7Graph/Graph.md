## Exercises for 15 Jul 2020 ([Graph basics](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/basics/))

1. What is a DAG?

   DAG is the acronym of Directed Acyclic Graph.

2. Asymptotically speaking, how does the maximum number of edges |E| in an undirected graph vary with the number of vertices |V|?

   For undirected graph, V*(V-1)/2

3. Implement an adjacency matrix for a graph where the number of vertices is known in advance. Use the following class template:

   ```C++
   template<typename V, typename E>
   class Graph
   {
   public:
   	using VertexID = size_t;
   
   	VertexID addVertex(V);
   	Graph& addEdge(VertexID, VertexID, E);
   
   	/* ... */
   };
   ```

   see "graph.h"

4. [optional] Implement the above using an adjacency list instead of an adjacency matrix.

   see "graph.h"

## Exercises for 17 Jul 2020

Given the following table of road distances between selected locations on the Avalon Peninsula (download as [road-distances.csv](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/exercises/road-distances.csv)):

|               | BAY BULLS | CBS  | GOULDS | HOLYROOD | PARADISE | PORTUGAL COVE | ST. JOHN’S |
| :-----------: | :-------: | :--: | :----: | :------: | :------: | :-----------: | :--------: |
|   Bay Bulls   |     0     |      |  15.3  |   31.9   |          |               |            |
|      CBS      |           |  0   |        |   24.1   |   6.6    |     16.4      |            |
|    Goulds     |           |      |   0    |          |   17.5   |               |    14.3    |
|   Holyrood    |           |      |        |    0     |          |               |            |
|   Paradise    |           |      |        |          |    0     |     12.5      |    18.6    |
| Portugal Cove |           |      |        |          |          |       0       |    14.2    |
|  St. John’s   |           |      |        |          |          |               |     0      |

1. Write a program that will parse [road-distances.csv](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/exercises/road-distances.csv) into a graph representation. You may use either an adjacency matrix or an adjacency list to store this data in memory.

   ***Note:** if you’re not familiar with the CSV (comma-separated value) format, the [Wikipedia article](https://en.wikipedia.org/wiki/Comma-separated_values#Example) is a good place to start. You can ignore any of the complexities about quoting, as our CSV file doesn’t use quotes.*
   
   Adjacency list is used in the graph class. For parse code, please see "parse_csv.h". Note that the input csv file needs to be put in the same directory with .exe
   
   The output is shown as follows.
   
   ![image-20200725231716404](.\image-20200725231716404.png)

## Exercises for 20 Jul 2020 ([Shortest Paths](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/intro/))

1. Using the algorithm in [the Shortest Paths video](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/intro/) and the data from Friday’s exercises, calculate (by hand) the distances from Portugal Cove to all other locations in the table.

   

2. Starting from the code you wrote on Friday, write a method of your graph class that will calculate the total road distance between any two points in the graph.

## Exercises for 24 Jul 2020 ([Unweighted graphs](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/))

1. Write out and analyze the asymptotic run-time complexity of the algorithm we saw for computing shortest paths through graphs with **unweighted edges** in [our introductory video on the topic](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/), ([ also presented here](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/naive/)), as well as [the version that uses a *work list* to store "non-done" vertices](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/worklist/). If necessary, you may find it helpful to refer back to [the analyses we did in class on Wednesday](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/intro/#_analysis).
2. Write a (template) function to calculate the shortest paths through an unweighted graph.
