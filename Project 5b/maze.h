/*
Christopher Puglia
pug/-5b
11/17/2015

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
	void printPath(Graph & g, vector<Graph::vertex_descriptor> p);
	int numRows() { return rows; };
	int numCols() { return cols; };
	int getReverseMapI(int n) const;
	int getReverseMapJ(int n) const;
	bool findPathDFSRecursive(Graph &g, int destR, int destC, int currR, int currC);
	void findPathDFSStack(Graph &g, int rd, int cd, int rs, int cs);
	bool findShortestPathDFS(Graph &g, int destR, int destC, int currR, int currC);
	bool findShortestPathBFS(Graph &g, int destR, int destC, int currR, int currC);
	vector<Graph::vertex_descriptor> getPath();
	void clearPath();

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze12
	bool foundPath;
	int shortestPath;
			  // declare "vMap" and somewhere define it to map maze to graph
	matrix<Graph::vertex_descriptor> vMap;

	matrix<bool> value;
	vector<Graph::vertex_descriptor> path;
	vector<Graph::vertex_descriptor> tempPath;
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
	foundPath = false;
}



void maze::printPath(Graph &g, vector<Graph::vertex_descriptor> p)
{
	for (int i = p.size()-1; i >= 0; i--)
	{
		cout << "[" << g[p.at(i)].cell.first << "," << g[p.at(i)].cell.second << "]\n";
		print(rows - 1, cols - 1, g[p.at(i)].cell.first, g[p.at(i)].cell.second);
	}
	cout << "Path length: " << p.size()-1 << endl;
}

int maze::getReverseMapI(int n) const
{
	return 0;
}

int maze::getReverseMapJ(int n) const
{
	return 0;
}

bool maze::findPathDFSRecursive(Graph & g, int destR, int destC, int currR, int currC)
{
	if (destR == currR && destC == currC)
	{
		foundPath = true;
		path.push_back(getMap(currR, currC));
	}
	else
	{
		Graph::vertex_iterator vertexIt, vertexEnd;
		Graph::adjacency_iterator neighbourIt, neighbourEnd;
		tie(vertexIt, vertexEnd) = vertices(g);
		for (; vertexIt != vertexEnd; ++vertexIt)
		{
			if (g[*vertexIt].cell.first == currR && g[*vertexIt].cell.second == currC)
			{
				g[*vertexIt].visited = true;
				tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);
				for (; neighbourIt != neighbourEnd; ++neighbourIt)
				{
					if (!g[*neighbourIt].visited)
					{
						if (findPathDFSRecursive(g, destR, destC, g[*neighbourIt].cell.first, g[*neighbourIt].cell.second)) { return true; }
						//cout << "[" << g[*neighbourIt].cell.first << "," << g[*neighbourIt].cell.second << "] ";
					}
					if (foundPath)
					{
						path.push_back(getMap(g[*vertexIt].cell.first, g[*vertexIt].cell.second));
						break; // nasty, but it works
					}
				}
			}
		}



	} // else
	return false;
}

void maze::findPathDFSStack(Graph & g, int destR, int destC, int currR, int currC)
{
	Graph::adjacency_iterator neighbourIt, neighbourEnd;
	
	Graph::vertex_descriptor currentPos = getMap(currR, currC);
	path.push_back(getMap(g[currentPos].cell.first, g[currentPos].cell.second));
	g[currentPos].visited = true;
	while (getMap(g[currentPos].cell.first, g[currentPos].cell.second) != getMap(destR, destC))
	{
		/*cout << "Curr [" << g[currentPos].cell.first << "," << g[currentPos].cell.second << "]\n";
		cout << "Vector";
		for (int i = 0; i < path.size(); i++)
		{
			cout << "[" << g[path.at(i)].cell.first << "," << g[path.at(i)].cell.second << "]  ";
		}*/
		bool foundEmpty = false;
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(currentPos, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
		{
			if (!g[*neighbourIt].visited) 
			{
				if (path.back() != currentPos) //needed if we backtracked to a popped cell
					path.push_back(currentPos);
				path.push_back(getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second)); //add step
				g[*neighbourIt].visited = true;
				currentPos = getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second); //update current to available neighbor
				foundEmpty = true;
				break;
			}
		}
		//if (foundEmpty)
		//	continue;
		if (path.empty())
		{
			cout << "no path possible" << endl;
			return;
		}
		//print(rows - 1, cols - 1, g[currentPos].cell.first, g[currentPos].cell.second);
		if (!foundEmpty)
		{
		currentPos = path.back();
		path.pop_back();
		}
	}
	std::reverse(path.begin(), path.end()); //fix order to make it compatable with print
}

bool maze::findShortestPathDFS(Graph & g, int destR, int destC, int currR, int currC)
{
	Graph::vertex_descriptor currentPos = getMap(currR, currC);
	g[currentPos].visited = true;
	if(tempPath.empty()) //adds starting node
	tempPath.push_back(getMap(currR, currC));
	if (destR == currR && destC == currC)
	{
		foundPath = true;
		//
		if (shortestPath == 0 || tempPath.size() < (size_t)shortestPath)
		{
			shortestPath = tempPath.size();
			path = tempPath;
			std::reverse(path.begin(), path.end()); //fix order to make it compatable with print
		}
	}
	Graph::adjacency_iterator neighbourIt, neighbourEnd;
	tie(neighbourIt, neighbourEnd) = adjacent_vertices(currentPos, g);
	for (; neighbourIt != neighbourEnd; ++neighbourIt)
	{
		if (!g[*neighbourIt].visited)
		{
			tempPath.push_back(getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second));
			findShortestPathDFS(g, destR, destC, g[*neighbourIt].cell.first, g[*neighbourIt].cell.second);
			tempPath.pop_back();
		}
	}
	g[currentPos].visited = false;

	return foundPath;
}

bool maze::findShortestPathBFS(Graph & g, int destR, int destC, int currR, int currC)
{
	vector<Graph::vertex_descriptor> currentNodes;
	Graph::vertex_descriptor currentPos = getMap(currR, currC);
	g[currentPos].visited = true;
	currentNodes.push_back(currentPos);
	while (currentPos != getMap(destR, destC))
	{
		for (size_t i = 0; i < currentNodes.size(); i++)
		{
			currentPos = currentNodes.at(i);
			bool deadEnd = true;
			Graph::adjacency_iterator neighbourIt, neighbourEnd;
			tie(neighbourIt, neighbourEnd) = adjacent_vertices(currentPos, g);
			for (; neighbourIt != neighbourEnd; ++neighbourIt)
			{
				if (!g[*neighbourIt].visited)
				{	
				//	cout << "Curr [" << g[currentPos].cell.first << "," << g[currentPos].cell.second << "]  Neighbor" << g[*neighbourIt].cell.first << "," << g[*neighbourIt].cell.second << "\n";
				//	cout << "Vector";
				//	for (size_t i = 0; i < currentNodes.size(); i++)
				//	{
				//	cout << "[" << g[currentNodes.at(i)].cell.first << "," << g[currentNodes.at(i)].cell.second << "]  ";
				//	}
				//	cout << endl;
					g[*neighbourIt].visited = true;
					g[*neighbourIt].pred = currentPos;
					currentNodes.push_back(getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second));
					deadEnd = false;
					for (size_t i = 0; i < currentNodes.size(); i++)
					{
						if (currentNodes.at(i) == currentPos)
							currentNodes.erase(currentNodes.begin() + i);
					}
					if (getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second) == getMap(destR, destC))
					{
						currentPos = getMap(g[*neighbourIt].cell.first, g[*neighbourIt].cell.second);
						neighbourIt = neighbourEnd;
						i = currentNodes.size();
						break;
					}
				}
			}
			if (deadEnd)
				currentNodes.erase(currentNodes.begin()+i);
		} //end for
		if (currentNodes.size() == 0)
		{
			cout << "no Solution" << endl;
			return false;
		}
	} //end while
	//solution found, start at end and work backwards to find path
	currentPos = getMap(destR, destC);
	path.push_back(getMap(g[currentPos].cell.first, g[currentPos].cell.second));
	while (currentPos != getMap(currR, currC))
	{
		path.push_back(g[currentPos].pred);
		currentPos = g[currentPos].pred;
	}
	return true;
}

vector<Graph::vertex_descriptor> maze::getPath()
{
	return path;
}

void maze::clearPath() //cleans up stuff post solve
{
	path.clear();
	shortestPath = 0;
	foundPath = false;
	tempPath.clear();
}




