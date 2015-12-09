/*
Christopher Puglia
Project 6b
12/7/15

*/
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>

#include "d_except.h"
#include "d_matrix.h"
#include "heapV.h"

using namespace std;
using namespace boost;

#define LargeValue 99999999;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;


struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef std::pair<Graph::edge_iterator, Graph::edge_iterator> EdgePair;

bool isConnected(Graph &g);
bool isCyclic(Graph &g);
void findSpanningForest(Graph &g1, Graph &sf);
void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);
Graph::edge_descriptor findEdge(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
bool cycleHelper(Graph &g, Graph::vertex_descriptor v);
void clearMarked(Graph &g);
void clearVisited(Graph &g);
void printForest(Graph &g);
void spanningHelper(Graph &g1, Graph &sf, Graph::vertex_descriptor v);
void msfPrim(Graph &g, Graph &sf);
void printminForest(Graph &g);

int main();
void initializeGraph(Graph &g,
	Graph::vertex_descriptor &start,
	Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
//	int startId, endId;
	fin >> n;
//	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{

		v = add_vertex(g);
/*		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
*/
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
		//add_edge(j, i, e, g);
	}
	clearMarked(g);
	clearVisited(g);
}

void clearMarked(Graph &g)
{
	Graph::vertex_iterator ei, ee;
	tie(ei, ee) = vertices(g);
	for (; ei != ee; ++ei)
	{
		g[*ei].marked = 0;

	}
}

void clearVisited(Graph &g)
{
	Graph::vertex_iterator ei, ee;
	tie(ei, ee) = vertices(g);
	for (; ei != ee; ++ei)
	{
		g[*ei].visited = 0;
		g[*ei].pred = -1;
	}
}
int depthFirst(Graph &g, Graph::vertex_descriptor v)
{
	int c = 0;
	if (!g[v].visited)
	{
		g[v].visited = true;
		c = 1;
		Graph::adjacency_iterator neighbourIt, neighbourEnd;
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(v, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
		{
			c += depthFirst(g, *neighbourIt);
		}
	}
	return c;
}
bool allReachable(Graph::vertex_descriptor v, Graph &g)
{
	int numVisited = 0;
	clearVisited(g);
	numVisited = depthFirst(g, v);
	if (numVisited == num_vertices(g))
		return true;
	return false;

}
bool isConnected(Graph &g)
// Returns true if the graph g is connected. Otherwise returns false.
{
	if (allReachable(0, g))
		return true;
	return false;
}
bool isCyclic(Graph &g)
// Returns true if the graph g contains a cycle. Otherwise, returns false.
{
	clearVisited(g);
	Graph::vertex_iterator vertexIt, vertexEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		if (!g[*vertexIt].visited)
		{
			if (cycleHelper(g, *vertexIt))
				return true;
		}
	}
	return false;
}
bool cycleHelper(Graph &g, Graph::vertex_descriptor v)
{
	if (g[v].visited)
	{
		return true;
	}
		
	else
	{
		g[v].visited = true;
		Graph::adjacency_iterator neighbourIt, neighbourEnd;
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(v, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
		{			
			if (*neighbourIt != g[v].pred)
			{
				g[*neighbourIt].pred = v;
				if (cycleHelper(g, *neighbourIt))
					return true;
			}
		}
	}
	return false;
}
Graph::edge_descriptor findEdge(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	EdgePair ep;
	for (ep = edges(g); ep.first != ep.second; ++ep.first)
	{
		// Get the two vertices that are joined by this edge...
		if (source(*ep.first, g) == u && target(*ep.first, g) == v)
		{
			return *ep.first;
		}
	}
	return *ep.first;
}

void findSpanningForest(Graph &g1, Graph &sf)
// Create a graph sf that contains a spanning forest on the graph g.
{
	clearVisited(g1);
	Graph::vertex_descriptor v;


	Graph::vertex_iterator vertexIt, vertexEnd;
	tie(vertexIt, vertexEnd) = vertices(g1);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{

		if (!g1[*vertexIt].visited) //looking for disconnected stuff
		{
			v = *vertexIt;
			g1[v].visited = true;
			v = add_vertex(sf);
			spanningHelper(g1, sf, v);
		}
	}
}
void spanningHelper(Graph &g1, Graph &sf, Graph::vertex_descriptor v)
{
	Graph::adjacency_iterator neighbourIt, neighbourEnd;
	tie(neighbourIt, neighbourEnd) = adjacent_vertices(v, g1);
	for (; neighbourIt != neighbourEnd; ++neighbourIt)
	{
		Graph::vertex_descriptor added;
		EdgeProperties e;
		if (!g1[*neighbourIt].visited)
		{
			added = add_vertex(sf);
			g1[*neighbourIt].visited = true;
			e.weight = g1[findEdge(g1, v, *neighbourIt)].weight;
			add_edge(v, added, e, sf);
			spanningHelper(g1, sf, added);
		}
	}
}
void msfPrim(Graph &g, Graph &sf)
{
	clearVisited(g);
	heapV<Graph::edge_descriptor, Graph> v;
	Graph::edge_iterator edgeIt, edgeEnd;
	Graph::adjacency_iterator eneighbourIt, eneighbourEnd;
	tie(edgeIt, edgeEnd) = edges(g);
	for (; edgeIt != edgeEnd; ++edgeIt)
	{
		v.minHeapInsert(*edgeIt, g);
	}
	Graph::vertex_iterator vIt, vEnd;
	tie(vIt, vEnd) = vertices(g);
	for (; vIt != vEnd; ++vIt)
	{
		Graph::vertex_descriptor vv;
		vv = *vIt;
		vv= add_vertex(sf);
	}

	while (v.size() > 0)
	{
		Graph::edge_descriptor e;
		e = v.extractMinHeapMinimum(g);
		if (!g[target(e, g)].visited)
		{
			g[target(e, g)].visited = true;
			g[source(e, g)].visited = true;
			add_edge(source(e,g), target(e,g), sf);
			add_edge(target(e, g), source(e, g), sf);
			sf[findEdge(sf, source(e, g), target(e, g))].weight = g[e].weight;
			sf[findEdge(sf, target(e, g), source(e, g))].weight = g[e].weight;
		}
		
	}

}
void printForest(Graph &g)
{
	Graph::edge_iterator edgeIt, edgeEnd;
Graph::adjacency_iterator eneighbourIt, eneighbourEnd;
tie(edgeIt, edgeEnd) = edges(g);
int cost = 0;
for (; edgeIt != edgeEnd; ++edgeIt)
{
	//cout << "Edge " << *edgeIt << endl;
	Graph::vertex_descriptor x = target(*edgeIt, g);
	Graph::vertex_descriptor y = source(*edgeIt, g);
	cout << "    Target = [" << x << "]" << " Source = [" << y << "]";
	cout << "   Weight:" << g[*edgeIt].weight << endl;
	cost += g[*edgeIt].weight;
}
cout << "Total Cost = " << cost << endl;
cout << "Connected Components = " << num_vertices(g) << endl;
}
void printminForest(Graph &g)
{
	Graph::edge_iterator edgeIt, edgeEnd;
	Graph::adjacency_iterator eneighbourIt, eneighbourEnd;
	tie(edgeIt, edgeEnd) = edges(g);
	int cost = 0;
	for (; edgeIt != edgeEnd; ++++edgeIt)
	{
		//cout << "Edge " << *edgeIt << endl;
		Graph::vertex_descriptor x = target(*edgeIt, g);
		Graph::vertex_descriptor y = source(*edgeIt, g);
		cout << "    Target = [" << x << "]" << " Source = [" << y << "]";
		cout << "   Weight:" << g[*edgeIt].weight << endl;
		cost += g[*edgeIt].weight;
	}
	cout << "Total Cost = " << cost << endl;
	cout << "Connected Components = " << num_vertices(g) << endl;
}

int main()
{
	ifstream fin;
	// Read the maze from the file.
	string fileName;
	cout << "Enter Filename: ";
	cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}
	Graph g,sf,sf2;
	Graph::vertex_descriptor start, end;
	initializeGraph(g, start, end, fin);
	if (isConnected(g))
		cout << "Graph is connected" << endl;
	else
		cout << "Graph is not connected" << endl;
	if(isCyclic(g) )
		cout << "Graph is cyclic" << endl;
	else
		cout << "Graph is not cyclic" << endl;

	findSpanningForest(g, sf);

	if (isConnected(sf))
		cout << "Spanning Forest is connected" << endl;
	else
		cout << "Spanning Forest is not connected" << endl;
	if (isCyclic(sf))
		cout << "Spanning Forest is cyclic" << endl;
	else
		cout << "Spanning Forest is not cyclic" << endl;
	printForest(sf);

	msfPrim(g, sf2);
	
	if (isConnected(sf2))
		cout << "Min Spanning Forest is connected" << endl;
	else
		cout << "Min Spanning Forest is not connected" << endl;
	if (isCyclic(sf2))
		cout << "Min Spanning Forest is cyclic" << endl;
	else
		cout << "Min Spanning Forest is not cyclic" << endl;
	printminForest(sf2);
	fin.close();
	return 0;
}
