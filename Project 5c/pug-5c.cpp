/*
Christopher Puglia
Project 5c
11/30/15

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

Graph::edge_descriptor findEdge(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
bool bellmanFord(Graph &g, Graph::vertex_descriptor s);
bool dijkstra(Graph &g, Graph::vertex_descriptor);
void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin);
void clearMarked(Graph &g);
bool relaxDij(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);
bool allReachable(Graph::vertex_descriptor v, Graph &g);
int depthFirst(Graph &g, Graph::vertex_descriptor v);
void clearVisited(Graph &g);
int main();

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
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight)
	{
		g[v].weight = g[findEdge(g, u, v)].weight + g[u].weight;
		g[v].pred = u;
	}
}
bool relaxDij(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight )
	{
		if (g[findEdge(g, u, v)].weight < 0)
			return false;
		
		g[v].weight = g[findEdge(g, u, v)].weight + g[u].weight;
		g[v].pred = u;
	}
	return true;
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
bool dijkstra(Graph &g, Graph::vertex_descriptor s)
{
	//set all distances to inf
	Graph::vertex_iterator vertexIt, vertexEnd;
	Graph::edge_iterator edgeIt, edgeEnd;
	std::stack<Graph::vertex_descriptor> stk;
	heapV <Graph::vertex_descriptor, Graph> q;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		g[*vertexIt].weight = LargeValue;
		g[*vertexIt].pred = -99999;
		q.minHeapInsert(*vertexIt, g);
	}
	g[s].weight = 0;
	
	while (q.size() != 0)
	{
		Graph::vertex_descriptor u = q.extractMinHeapMinimum(g);
		stk.push(u);
		Graph::adjacency_iterator neighbourIt, neighbourEnd;
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(u, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
		{
			if (!relaxDij(g, u, *neighbourIt))
			{
				cout << "Negative Edge in Dijkstra Quiting\n";
				return false;
			}
			q.buildMinHeap(q.size(), g);
		}
	}
	if (allReachable(s,g))
		return true;
	return false;

}
bool bellmanFord(Graph &g, Graph::vertex_descriptor s)
{
	//set all distances to inf
	Graph::vertex_iterator vertexIt, vertexEnd;
	Graph::edge_iterator edgeIt, edgeEnd;

	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		g[*vertexIt].weight = LargeValue;
		g[*vertexIt].pred = -99999;

	}
	g[s].weight = 0;

	tie(vertexIt, vertexEnd) = vertices(g);
	for (size_t i = 1; i < num_vertices(g) - 1; i++)
	{
	tie(edgeIt, edgeEnd) = edges(g);
	for (; edgeIt != edgeEnd; ++edgeIt)
	{
		Graph::vertex_descriptor u = source(*edgeIt, g);
		Graph::vertex_descriptor v = target(*edgeIt, g);

		relax(g, u, v);
	}
}
		tie(edgeIt, edgeEnd) = edges(g);
		for (; edgeIt != edgeEnd; ++edgeIt)
		{
			Graph::vertex_descriptor u = source(*edgeIt, g);
			Graph::vertex_descriptor v = target(*edgeIt, g);
			if (g[v].weight > g[findEdge(g, u, v)].weight + g[u].weight)
				return false;
			
		}
		return true;
}
void initializeGraph(Graph &g,
	Graph::vertex_descriptor &start,
	Graph::vertex_descriptor &end, ifstream &fin)
	// Initialize g using data from fin.  Set start and end equal
	// to the start and end nodes.
{
	EdgeProperties e;

	int n, i, j;
	int startId, endId;
	fin >> n;
	fin >> startId >> endId;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
	{
		
		v = add_vertex(g);
		if (i == startId)
			start = v;
		if (i == endId)
			end = v;
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
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

	}
}


int main()
{
	ifstream fin;
	// Read the maze from the file.
	string fileName;
		cout << "Enter Filename: " << endl;
		cin >> fileName;
		


		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}
		Graph g;
		Graph::vertex_descriptor start, end, currentPos;
		initializeGraph(g, start, end, fin);

		cout << "\nBellman-Ford:\n";
		fin.close();


		if (bellmanFord(g, start))
		{
			cout << "No Negative loops\n";
			cout << "Total Cost = " << g[end].weight << endl;
		}
		else
		{
			cout << "Negative loops found\n";
			cout << "Total Cost = -Infinity"<< endl;
		}
		if (g[end].pred == -99999)
			cout << "End is Unreachable from Start\n";
		else
		{ //print
		currentPos = end;
		clearMarked(g);
		cout << "Start [" << start << "]\n";
		cout << "End [" << end << "]\n";
		while (currentPos != start)
		{
			cout<<"["<<currentPos<< "]  ";
			if (g[currentPos].marked)
			{
				cout << "FOUND LOOP\n";
				break;
			}
			g[currentPos].marked = true;
			currentPos = g[currentPos].pred;
		}
		cout << "[" << currentPos << "] \n";
		}


		

		cout << "\n\nDijkstra:\n";
		Graph g2;
		Graph::vertex_descriptor start2, end2, currentPos2;
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}
		initializeGraph(g2, start2, end2, fin);
		fin.close();


		if (dijkstra(g2, start2))
			cout << "Connected \n";
		else
			cout << "Not Connected\n";
		if (g2[end2].pred == -99999)
			cout << "End is Unreachable from Start\n";
		else
		{ //print
			currentPos2 = end2;
			cout << "Total Cost = " << g2[currentPos2].weight << endl;
			cout << "Start [" << start2 << "]\n";
			cout << "End [" << end2 << "]\n";
			while (currentPos2 != start2)
			{
				cout << "[" << currentPos2 << "]  ";
				currentPos2 = g2[currentPos2].pred;
				
			}
			cout << "[" << currentPos2 << "] \n";
		}

		cout << "\n\n";
	
	
	return 0;
}

