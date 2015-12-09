/*
Christopher Puglia
pug/-5a
11/8/2015

Compiled on MS Visual Studio 

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

//#define LargeValue 99999999;

using namespace std;
using namespace boost;

#define LargeValue 99999999
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


class maze
{
public:
	void clearVisited(Graph & g);
	void setNodeWeights(Graph & g, int w);
	void clearMarked(Graph & g);
	void clearVisitedEdge(Graph & g);
	void setEdgeWeights(Graph & g, int w);
	void clearMarkedEdge(Graph & g);
	int getMap(int i, int j) const;
	maze(ifstream &fin);
	void print(int, int, int, int);
	bool isLegal(int i, int j);
	void mapMazeToGraph(Graph &g);
	void printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g);
	int numRows() { return rows; };
	int numCols() { return cols; };
	int getReverseMapI(int n) const;
	int getReverseMapJ(int n) const;

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze12

			  // declare "vMap" and somewhere define it to map maze to graph
	matrix<Graph::vertex_descriptor> vMap;

	matrix<bool> value;

	vector<pair<Graph::vertex_descriptor, Graph::vertex_descriptor>> nodeVect;
};

void maze::clearVisited(Graph &g)
// Mark all nodes in g as not visited.
{
	Graph::vertex_iterator vertexIt, vertexEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		g[*vertexIt].visited = 0;
	
	}
}
void maze::setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	Graph::vertex_iterator vertexIt, vertexEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		g[*vertexIt].weight = w;

	}
}

void maze::clearMarked(Graph &g)
{
	Graph::vertex_iterator vertexIt, vertexEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		g[*vertexIt].marked = 0;

	}
}
void maze::clearVisitedEdge(Graph &g)
// Mark all nodes in g as not visited.
{
	Graph::edge_iterator ei, ee;
	tie(ei, ee) = edges(g);
	for (; ei != ee; ++ei)
	{
		g[*ei].visited = 0;

	}
}
void maze::setEdgeWeights(Graph &g, int w)
// Set all node weights to w.
{
	Graph::edge_iterator ei, ee;
	tie(ei, ee) = edges(g);
	for (; ei != ee; ++ei)
	{
		g[*ei].weight = w;

	}
}

void maze::clearMarkedEdge(Graph &g)
{
	Graph::edge_iterator ei, ee;
	tie(ei, ee) = edges(g);
	for (; ei != ee; ++ei)
	{
		g[*ei].marked = 0;

	}
}
int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
	return vMap[i][j];
} // getMap

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   
   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
{
	Graph::vertex_descriptor v;
	vMap.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++) {
		for (int j = 0; j <= cols - 1; j++) {
			if (value[i][j]) {
				v = add_vertex(g);
				g[v].cell = pair<int, int>(i, j);
				vMap[i][j] = v;
			}
		}
	}
	for (int i = 0; i <= rows - 1; i++) {
		for (int j = 0; j <= cols - 1; j++) {
			if (value[i][j]) {
				v = vMap[i][j];
				// Check up
				if (i>0 && value[i - 1][j]) {
					add_edge(v, vMap[i - 1][j], g);
				}
				// Check down
				if (i<rows - 1 && value[i + 1][j]) {
					add_edge(v, vMap[i + 1][j], g);
				}
				// Check left
				if (j>0 && value[i][j - 1]) {
					add_edge(v, vMap[i][j - 1], g);
				}
				// Check right
				if (j<cols - 1 && value[i][j + 1]) {
					add_edge(v, vMap[i][j + 1], g);
				}
			}
		}
	}
	//Clear All
	clearMarked(g);
	clearVisited(g);
	setNodeWeights(g,0);
	clearMarkedEdge(g);
	clearVisitedEdge(g);
	setEdgeWeights(g,0);
}

void maze::printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g)
{
	Graph::vertex_descriptor vert;

	if (s.empty())
	{
		cout << "No path exists" << endl;
	}
	while (!s.empty())
	{
		vert = s.top();
		s.pop();
		print(g[end].cell.first, g[end].cell.second, g[vert].cell.first, g[vert].cell.second);
	}
}


