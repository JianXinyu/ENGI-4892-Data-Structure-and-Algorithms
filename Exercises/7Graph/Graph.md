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

   Dijkstra's algorithm pseudo code:

   ```pseudocode
   for each v in Vertices
   {
       v.distance = ∞
       v.done = False
   }
   
   # The distance from the source vertex (s) to itself is 0
   source.dist = 0
   
   # Iterative algorithm:
   while(there is a vertex remains not done)
   {
       # Pick a vertex to work on:
       v = vertex that is not done with the smallest distance
   	
   	for each vertex w adjacent to v
   	{
       	if(!w.done)
       	{
       	    cvw = cost of edge from v to w
       		if(w.distance > v.distance + cvw)
       		{
       		    w.distance = v.distance + cvw
                   w.path = v
       		}
       	}
   	}
   	v.done = True
   }
   ```

   |               | BAY BULLS | CBS  | GOULDS | HOLYROOD | PARADISE | PORTUGAL COVE | ST. JOHN’S |
   | :-----------: | :-------: | :--: | :----: | :------: | :------: | :-----------: | :--------: |
   | Portugal Cove |   43.8    | 16.4 |  28.5  |   40.5   |   12.5   |       0       |    14.2    |

2. Starting from the code you wrote on Friday, write a method of your graph class that will calculate the total road distance between any two points in the graph.

   see method Dijkstra() in graph.h

   The result is the same with calculation above.

   ![image-20200726213329278](.\image-20200726213329278.png)

## Exercises for 24 Jul 2020 ([Unweighted graphs](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/))

1. Write out and analyze the asymptotic run-time complexity of the algorithm we saw for computing shortest paths through graphs with **unweighted edges** in [our introductory video on the topic](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/), ([ also presented here](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/naive/)), as well as [the version that uses a *work list* to store "non-done" vertices](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/unweighted/worklist/). If necessary, you may find it helpful to refer back to [the analyses we did in class on Wednesday](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/shortest-paths/intro/#_analysis).

   for naive algorithm, the time asymptotic run-time complexity is $\Theta(|V|^2)$.

   ![unnamed (1)](.\unnamed (1).jpg)

   for work list algorithm, the time asymptotic run-time complexity is $\Theta(|E|+|V|)$.

   ![unnamed (2)](.\unnamed (2).jpg)

2. Write a (template) function to calculate the shortest paths through an unweighted graph.

   see method shortestDistances() in graph.h

## Exercises for 27 Jul 2020

(see [acyclic graphs](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/acyclic-graphs/) and [centrality](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/centrality/))

1. Write an algorithm for visiting graph vertices according to *topological order* (i.e., perform a *topological sort*). Show that its run-time complexity is Θ(|V|+|E|).

   ```pseudocode
   Queue<Vertex> q;
   int counter = 0;
   
   q.makeEmpty();
   # this for loop has run-time complexity Θ(|V|)
   for each Vertex v
   	if(v.indegree == 0)
   		q.enqueue(v);
   		
   while(!q.isEmpty())
   {
   	Vertex v = q.dequeue();
   	v.topNum = ++counter;
   	# this for loop is executed at most once per edge
   	# thus it has run-time complexity Θ(|E|)
   	for each Vertex w adjacent to v
   		if(--w.indegree == 0)
   			q.enqueue(w);
   }
   
   if(counter != NUM_VERTICES)
   	throw CycleFoundException();
   ```

   From the analysis in the pseudocode, the run-time complexity is Θ(|V|+|E|)

2. (optional) Write a (template) function to calculate the betweenness centrality of a vertex in the graph, given an already-calculated matrix of shortest paths. Analyze the asymptotic complexity of your code.

   ```c++
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
   ```

   Apparently, this algorithm iterates Dijkstra's algorithm |V| times. Since the time complexity of Dijkstra's algorithm is $\Theta(|V|^2)$, the asymptotic complexity is $O(|V|^3)$.

## Exercises for 29 Jul 2020

(see: [depth-first search](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/modules/graphs/depth-first/))

1. Sketch out the pseudocode for finding an Euler circuit. Include an initial test of whether or not an Euler circuit will be found.

   ```pseudocode
   # check if the graph is connected and each vertex has an even degree
   if(connected() and even_degree())
   {
   	v = random(); # pick any vertex to start
   	circuit = dfs(v); # perform a depth-first search
   	while(there is untraversed edge)
   	{
   		w = find_vertex(circuit);# search the circuit to find a vertex with untraversed edges
   		circuit_new = dfs(w);#perform another depth-first search
   		circuit = splice(circuit_new, circuit);#splice new circuit into the original one
   	}
   }
   ```

2. What steps do you need to take to ensure that your algorithm can run in Θ(|V|+|E|) time?

   With the appropriate data structures, the running time of the algorithm is  **linear time**: $\Theta(|V|+|E|)$. 

   - To make splicing simple, the path should be maintained as a linked list. 
   - To avoid repetitious scanning of adjacency lists, we must maintain, for each adjacency list, a pointer to the last edge scanned. 
   - When a path is spliced in, the search for a new vertex from which to perform the next depth-first search must begin at the start of the splice point. 

3. [optional] Write the C++ code to implement your Euler circuit discovery. Count the number of edges tested and `dfs()` calls — is the total actually Θ(|V|+|E|)?

   didn't finish this problem.