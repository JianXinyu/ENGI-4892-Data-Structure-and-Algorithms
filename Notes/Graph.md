Problems:

1. find a minimum spanning tree in an undirected graph. (for directed graph, more difficult) - greed
2. Euler circuit

# 1. Definition

- A **graph** $G=(V,E)$ consists of a set of **vertices V** and a set of **edges E**. 
  - Edge is a pair $(v, w)\quad v,w\in V$.  Sometimes an edge has a third component **weight/cost**.
    - If the pair is ordered, then the graph is **directed**.
    - **undirected**
  - Vertex $w$ is **adjacent** to $v$ if and only if $(v, w)\in E$. Notice that the order.

- A **path** in a graph is a sequence of vertices $w_1,w_2, ..., w_N$ such that $(w_i, w_{i+1})\in E$ for $1\leq i \lt N$. Its **length=N-1**. If the path contains an edge $(v,v)$ from a vertex to itself, then the path $v,v$ is referred to as a **loop**. Loopless? A **simple path** is path such that all vertices are distinct, except that the first and last could be the same.

- A **cycle** in a directed graph is a path of length at least 1 such that $w_1=w_N$. **simple cycle** if it's a simple path.  For undirected graph, the edges should be distinct. e.g., path $u,v,u$ in an undirected graph isn't a cycle, but it's a cycle in a directed graph.  
  - **Acyclic**: a directed graph has no cycles.
  
  - **DAG**: directed acyclic graph
  
    Problems that cycle causes:
  
    - the longest-path problem:  positive-cost cycles
    - the shortest-path problem: negative-cost cycles
  
- **degree**: the number of edges that a vertex touches.

  ​	For directed graph:

  - **in-degree** of a vertex $v$: the number of edges $(u,v)$ pointing **to** the vertex $v$
  - **out-degree**: the number of edges pointing **away** from the vertex

Connection:

- **connected**: an **undirected** graph is connected if there is a path from every vertex to every other vertex.
- **strongly connected**: a **directed** graph with above property.
- **weakly connected**: a **directed** graph is not strongly connected, but the underlying graph(without direction to the arcs) is connected 

- A **complete graph** is a graph in which there is an edge between every pair of vertices.

Applications:

1. airport system
2. traffic flow

### Representation

How to represent vertices:

use some kind of iterable container, whether that be a linear data structure or something like a binary search tree that can be used to efficiently look up specific vertices by a name.

How to represent edges:

1. **Adjacency matrix**: use a 2D array to represent a graph. For each edge $(u,v)$, set $A[u][v]$ to *true*; otherwise *false*. If the edge has a third component, set $A[u][v]=weight/cost$ and use either a very large or a very small *weight/cost* as a sentinel to indicate nonexistent edges.

   - pros: simplicity 
   - cons: space complexity is $\Theta(|V|^2)$
   - apply: suitable for dense graph

   **dense**: $|E|=\Theta(|V|^2)$

   **sparse**: the graph is not dense

   However, in most applications, the graph is sparse.

2. **Adjacency list**: for each vertex, keep a list of all adjacent vertices. It is the **standard way** to represent graphs. For undirected graphs, each edge $(u,v)$ appears in two lists. 
   
   - space complexity: $O(|E|+|V|)$, linear in the size of the graph. For undirected graph, each edge $(u,v)$ appears in two lists, so the space usage doubles. ( When we speak of linear-time graph algorithms,  $O(|E|+|V|)$, is the running time we require.) 

How to represent graph using adjacency list?

 - for list: 
   	- vectors: for sparse graph, each vector needs to be initialized with a smaller capacity than the default; otherwise, there could be significant wasted space.
      	- lists

- for whole:
  - map: keys are vertices and values are adjacency list. Simpler
  - class: maintain each adjacency list as a data member of a Vertex class. Faster

####  How to measure the importance of a vertex?

1. Degree: not informative

2. **Betweenness centrality**: a measure of how many of the shortest paths through a graph flow through a particular vertex.
   $$
   C_B(v)=\sum_{s\neq w\neq t \in V}\frac{\sigma_{st}(v)}{\sigma_{st}}
   $$
   the ratio of the number of shortest paths in the graph, from all possible starting and ending points, that flow through vertex $v$, to the number of all shortest paths through the graph.

   Time Analysis:  The cost of computing betweenness centrality is dominated by the cost of calculating the shortest paths from all vertices to all other vertices.

   - dense graph: the Floyd–Warshall algorithm can find all such shortest paths in $\Theta(|V|^3)$ time.
   - sparse graph: Johnson’s algorithm do something like running Dijkstra’s algorithm $|V|$ times.
   -  If the graph is unweighted, Brandes' algorithm can compute all shortest paths in just $\Theta(|V||E|)$ time.

3. **Eigenvalue centrality**: model the *influence* of vertices within a graph.

   Application:

   1.  *social network analysis*: Degree and betweenness centrality are critical to *social network analysis*, the study of how people in groups interact with each other at a *systemic* — rather than individual — level. 
   2. *influence modeling*: eigenvector centrality algorithms are important for assessing the importance of linked knowledge artifacts like scientific papers and even Web pages. Google’s PageRank algorithm is a modified version of eigenvector centrality.

# 2. Topological Sort

A **topological sort** is an ordering of vertices in a DAG, such that if there is a path from $v_i$ to $v_j$, then $v_j$ appears after $v_i$ in the ordering. It contains all vertices. Perhaps there is no path between two vertices, it's OK as long as they fulfill the ordering requirement to other vertices. Thus, it makes the topological sort not unique. or example, in the following DAG, v1, v2, v5, v4, v3, v7, v6 and v1, v2, v5, v4, v7, v3, v6 are both topological orderings. Although there is no path from v3 to v7.

![image-20200724221551375](.\figures\DAG)

Topological sort isn't possible if the graph has a cycle.

How to find topological sort?

1.  find any vertex without  incoming edges.
2. print this vertex and remove it, along with its edges, from the graph.
3. apply the same strategy with the rest graph.

asymptotic run-time complexity: 

1. Normal situation: $\Theta(|V|^2)$

2. Using stack or queue: $\Theta(|E|+|V|)$

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
   
   
   
   

# 3. Shortest-Path Algorithms

Using some vertex, s, which is an input parameter, we would like to find the shortest path from s to all other vertices.

**weighted path length**: The input is a weighted graph: Associated with each edge $(v_i, v_j)$ is a cost $c_{i,j}$ to traverse the edge. The cost of a path $v_1v_2 . . . v_N$ is $\sum_{i=1}^{N−1} c_{i,i+1}$.

**unweighted path length**: the numbers of edges on the path, namely, N-1.

## 3.1 Unweighted Shortest Paths 

We are only interested in the number of edges contained on the path, which is a special case of the weighted shortest-path problem.

1. **breadth-first search**: It operates by processing vertices in layers: The vertices closest to the start are evaluated first, and the most distant vertices are evaluated last. This is much the same as a level-order traversal for trees.

```pseudocode
# Set up table of distances and paths
for v in V
    distance[v] = ∞
    done[v] = F

# The distance from the source vertex (s) to itself is 0
distance[source] = 0

# Iterative algorithm (uses "dynamic programming"):
for dist in [0, |V|):
    for each v in vertices:
        if done[v] or distance[v] != dist:
            continue

        for each n in adjacencies[v]:
            if distance[n] == ∞:
                distance[n] = dist + 1
                path[n] = v

        done[v] = T
```

the asymptotic run-time complexity: $\Theta(|V|^2)$

![unnamed (1)](.\figures\unnamed (1).jpg)

2. Here’s an improved algorithm that uses a *work list* to store the vertices that still need to be examined. We can store the remaining vertices in an ordered sequence like a queue because they will be **added in the same order they need to be examined in**. When examining a vertex at distance 0, we will find all of the vertices at distance 1 and add them to the work queue. Then we’ll start examining vertices with distance 1, discovering vertices at distance 2 and adding them **to the back** of the queue. This ensures that we’ll only start examining vertices of distance 2 once we get through all of the vertices with distance 1.

```pseudocode
for v in V
    distance[v] = ∞

distance[source] = 0
q.enqueue(source)

while q is not empty:
    v = q.dequeue()

    for each n in adjacencies[v]:
        if distance[n] == ∞:
            distance[n] = distance[v] + 1
            path[n] = v
            q.enqueue(n)
```

the asymptotic run-time complexity:$\Theta(|E|+|V|)$

![unnamed (2)](.\figures\unnamed (2).jpg)

## 3.2 Dijkstra's Algorithm

a prime example of a greedy algorithm.

Dijkstra’s algorithm proceeds in stages: At each stage, 

1. selects a vertex, $v$, which has the smallest $d_v$ among all the *unknown* vertices and declares that the shortest path from $s$ to $v$ is known. 
2. updates the values of $d_w$. $d_w=d_v+c_{v,w}$. 

the algorithm is the same for either directed graph or undirected graph.

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
    v = vertex that is not done with smallest distance
	
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

Program time complexity analysis:

Depending on data structure used:

- normal ADT, such as vector: $\Theta(|V|^2)$
- AVL, priority heap: $\Theta((|V|+|E|)log|V|)$

![unnamed](A:\MUN\Course\2020Spring\Data Structures\ENGI-4892-Data-Structure-and-Algorithms\Notes\figures\unnamed.jpg)

## 3.4 Acyclic Graphs

Now we can improve Dijkstra's algorithm by changing the order in which vertices are declared *known*, otherwise known as the vertex selection rule.

The new rule is to select the vertex in topological order. when a vertex $v$ is selected, its distance, $d_v$, can
no longer be lowered, since by the topological ordering rule it has no incoming edges emanating from unknown nodes.

Running-time: $\Theta(|E+|V|)$

Applications:

1. model some downhill skiing problem

2. model of (nonreversible) chemical reactions

3. **critical path analysis**

   - activity-node graph 
   - event-node graph
     - Dummy edges and nodes
     - earliest completion time for the project
       - earliest completion time for the node
       - the latest time
       - slack time
       - critical path

# 5. Minimum Spanning Tree

 A **spanning tree** is a partial representation of a graph, which includes all of the vertices of the full graph but only just enough edges — in the shape of a tree — to be able to reach all of the vertices from a root vertex.

- spanning tree: undirected graph is connected
- spanning forest: unconnected, need to repeat the process  

A **minimum spanning tree** of an undirected graph G is a tree formed from graph edges that connects all the vertices of G at lowest total cost. 

The minimum spanning tree is:

	- a tree because it is acyclic
	- spanning because it covers every vertex
	- minimum for the lowest total cost

Properties:

- minimum spanning tree exits if and only if G is connected.
- $|E|=|V|-1$ in minimum spanning tree
- it's usually not unique

Two ways to construct minimum spanning tree: or spanning tree?

1. Greedy ideas: as a spanning tree is created, the edge that is added is the one of minimum cost that avoids creation of a cycle, then the cost of the resulting spanning tree cannot be improved
2. Depth-first search: we perform a depth-first search and, any time we find an edge an an as-yet-unvisited vertex, we add that edge and vertex to our spanning tree.

## 5.1 Prim's Algorithm

 essentially identical to Dijkstra’s algorithm, except that the definition of $d_v(distances)$ and its update rule are different. After a vertex $v$, is selected, for each unknown $w$ adjacent to $v$, $d_w = min(d_w, c_{v,w})$. 

```pseudocode
for each v in Vertices{
    v.distance = ∞
    v.done = False
}
source.dist = 0
while(there is a vertex remains not done){
    v = vertex that is not done with smallest distance
	for each vertex w adjacent to v{
    	if(!w.done){
    	    cvw = cost of edge from v to w
    		if(w.distance > cvw){
    		    w.distance = cvw
                w.path = v
    		}
    	}
	}
	v.done = True
}
```



# 6. Applications of Depth-First Search

DFS is a generalization of preorder traversal. Starting at some vertex $v$, we process $v$ and then **recursively** traverse all vertices adjacent to $v$.

| Depth-First Search                                           | Breadth-First Search                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| recursively visit the neighbors of vertices such that we visit neighbors of one immediate neighbor before we visit the next immediate neighbor. | visit all of a vertex’s immediate neighbors before we visit any neighbors of neighbors |
| looks like an preorder tree traversal                        | looks like expanding concentric rings, level-order tree traversal |

Naive Algorithm:

```pseudocode
void dfs( Vertex v )
{
    v.visited = true;
    for each Vertex w adjacent to v
        if( !w.visited )
            dfs( w );
}
```

- To avoid cycles, a visited flag is used
- implicitly assume that for undirected graphs every edge (v, w) appears
  twice in the adjacency lists: once as (v, w) and once as (w, v).  
- If the graph is undirected and not connected, or directed and not strongly connected, this strategy might fail to visit some nodes. 

##### Time-complexity Analysis: $\Theta(|E|+|V|)$

Prerequisite: use adjacency lists.

1. - we only visit vertices that haven’t been visited before. 

   - we mark the current vertex as visited *before* we have any opportunity for recursion. 

     => Therefore, we can only ever visit $|V|$ vertices (at maximum).

2.  in any connected graph, if we visit a vertex while there are $n$ unvisited vertices, that visitation will cause another $n−1$ visitations to occur.

3. write a recurrence relation for the time it will take to complete a depth-first search. This time is on the order of 1 (for the marking of `v` as visited) plus the time to check out all of our neighbors. Inside this loop we see potentially many recursive depth-first search calls, but we’ve already said that we know what those add up to: the time it takes to visit $n−1$ additional vertices. What’s left of the loop is checking all of the vertex’s neighbors, which is on the order of the number of neighbors, which I’m calling $\Theta(|E_i|)$, where $i$ is the number of the current vertex. So, the total time to visit vertex $i$, with $|V|$ vertices remaining (including $i$), is $1+|E_0|+T(|V|−1)$. We can use the same equation to expand out $T(|V|−1)$ vertices, then $T(|V|−2)$, etc., until we end up with the sum of all of these 1s (one per vertex, for a total of $|V|$), plus the sum over all vertices of each vertex’s edge count, which is just the number of edges in the graph.
   $$
   T(|V|) = 1+|E_0|+T(|V|-1) 
   \\= 1+|E_0|+|E_1|+T(|V|-2)
   \\=|E|+|V|
   $$

## 6.1 spanning trees

- depth-first spanning tree: undirected graph is connected
- depth-first spanning forest: unconnected 

##  6. 3 Euler Circuits

- Euler path/Euler tour: find a path in the graph that visits every edge exactly once. is still possible if exactly two vertices have odd degree and we start at one of them and finish at the other. 
- **Euler circuit**: find a cycle that visits every edge exactly once. is possible only if the graph is connected and each vertex has an even degree

It turns out that the necessary condition is also sufficient. Any connected graph, all of whose vertices have even degree, must have an Euler circuit. 

Steps to find an Euler circuit **using repeated depth-first search**:

1.  pick a vertex (any vertex) and perform a depth-first search until we find an edge that leads back to where we started. This gives us a circuit. But there’s no guarantee that this circuit will go through all of the edges in the graph. 
2. If there are untraversed edges in the graph, at least two of them will have to connect to a vertex that is part of our circuit. We can iterate along our circuit until we find a vertex with untraversed edges and perform another depth-first search. This will give another circuit, which can be spliced into the original.
3. continue repeating this procedure until all of the edges have been traversed. 

##### Time complexity analysis

With the appropriate data structures, the running time of the algorithm is  **linear time**: $\Theta(|V|+|E|)$. 

- To make splicing simple, the path should be maintained as a linked list. 
- To avoid repetitious scanning of adjacency lists, we must maintain, for each adjacency list, a pointer to the last edge scanned. 
- When a path is spliced in, the search for a new vertex from which to perform the next depth-first search must begin at the start of the splice point. 

An analogous problem -- **Hamiltonian cycle problem** is to find a simple cycle, in an undirected graph, that visits every vertex. But it’s much harder than Euler circuit problem. 





cost 