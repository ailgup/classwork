/*
Christopher Puglia
pug/-5b
11/17/2015

Compiled on MS Visual Studio 

*/



#include "maze.h"
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
using namespace boost;
using namespace std;

ostream &operator<<(ostream &ostr, const Graph &g)
// Print all information about the graph.
{

	Graph::vertex_iterator vertexIt, vertexEnd;
	Graph::adjacency_iterator neighbourIt, neighbourEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		ostr << "[" << g[*vertexIt].cell.first << "," << g[*vertexIt].cell.second << "]" << " is connected to  ";
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
		{
			cout << "[" << g[*neighbourIt].cell.first << "," << g[*neighbourIt].cell.second << "] ";

		}
		ostr << "||   Visited:" << g[*vertexIt].visited << "   Marked:" << g[*vertexIt].marked << "   Weight:" << g[*vertexIt].weight<<endl;
	}

	Graph::edge_iterator edgeIt, edgeEnd;
	Graph::adjacency_iterator eneighbourIt, eneighbourEnd;
	tie(edgeIt, edgeEnd) = edges(g);
	for (; edgeIt != edgeEnd; ++edgeIt)
	{
		ostr << "Edge " << *edgeIt << endl;
		Graph::vertex_descriptor x = target(*edgeIt, g);
		Graph::vertex_descriptor y = source(*edgeIt, g);
		ostr << "    Target = [" << g[x].cell.first << "," << g[x].cell.second << "]" << " Source = [" << g[y].cell.first << "," << g[y].cell.second << "]";
		ostr << "    Visited:" << g[*edgeIt].visited << "   Marked:" << g[*edgeIt].marked << "   Weight:" << g[*edgeIt].weight << endl;
	}

	return ostr;
}



int main()
{

		ifstream fin;

		// Read the maze from the file.
		string fileName; //= "maze-files/maze2.txt";
		cout << "Enter Filename: " << endl;
		cin >> fileName;
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		maze m(fin);
		fin.close();

		m.print(m.numRows() - 1, m.numCols() - 1, 0, 0);

		Graph g;
		m.mapMazeToGraph(g);

		cout << "\nfindPathDFSRecursive" << endl;
		m.clearVisited(g);
		m.findPathDFSRecursive(g, m.numRows() - 1, m.numCols() - 1, 0, 0);
		m.printPath(g,m.getPath());
		m.clearPath();

		cout << "\nfindPathDFSStack" << endl;
		m.clearVisited(g);
		m.findPathDFSStack(g, m.numRows() - 1, m.numCols() - 1, 0, 0);
		m.printPath(g,m.getPath());
		m.clearPath();

		cout << "\nfindShortestPathDFS" << endl;
		m.clearVisited(g);
		m.findShortestPathDFS(g, m.numRows() - 1, m.numCols() - 1, 0, 0);
		m.printPath(g, m.getPath());
		m.clearPath();

		cout << "\nfindShortestPathBFS" << endl;
		m.clearVisited(g);
		cout << m.numRows() - 1 << " " << m.numCols() - 1 << endl;
		m.findShortestPathBFS(g, m.numRows() - 1, m.numCols() - 1, 0, 0);
		m.printPath(g, m.getPath());
		m.clearPath();

		
		//cout << g << endl;
		cin.get(); //to pause the program after completion
		cin.get();
		
}