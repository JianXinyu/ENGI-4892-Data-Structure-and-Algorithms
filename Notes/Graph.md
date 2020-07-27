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

# 2. Topological Sort

an ordering of vertices in a DAG, such that if there is a path from $v_i$ to $v_j$, then $v_j$ appears after $v_i$ in the ordering. It contains all vertices. Perhaps there is no path between two vertices, it's OK as long as they fulfill the ordering requirement to other vertices. Thus, it makes the topological sort not unique. or example, in the following DAG, v1, v2, v5, v4, v3, v7, v6 and v1, v2, v5, v4, v7, v3, v6 are both topological orderings. Although there is no path from v3 to v7.

![image-20200724221551375](.\figures\DAG)

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
            distance[n] = dist + 1
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

![unnamed](A:\MUN\Course\2020Spring\Data Structures\ENGI-4892-Data-Structure-and-Algorithms\Notes\figures\unnamed.jpg)



