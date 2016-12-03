/*
Christopher Puglia
pug/-5a
11/8/2015

Compiled on MS Visual Studio 

*/



#include "maze.h"
#include <boost/graph/adjacency_list.hpp>

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
		string fileName = "maze-files/maze0.txt";

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


		cout << g << endl;
		cin.get(); //to pause the program after completion
		cin.get();
		
}