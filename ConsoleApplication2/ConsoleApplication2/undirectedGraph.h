#include"vertex.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class undirectedGraph
{
protected:
	vector<vertex*>vertices;

public:
	vector<vertex*> getVertices()
	{
		return vertices;
	}
	vertex* find(int row, int col)
	{
		for (int x = 0; x < vertices.size(); x++)
			if (vertices[x]->row == row && vertices[x]->col == col)
				return vertices[x];

		return NULL;
	}
	void addVertex(int row, int col)
	{
		vertices.push_back(new vertex(row, col));
	}

	void addEdge(int x1, int y1, int x2, int y2)
	{
		vertex* first = find(x1, y1);
		vertex* second = find(x2, y2);
		if (first == NULL || second == NULL)
			cout << "Error... Wrong name for a vertex." << endl;
		else {
			first->neighbours.push_back(second);
			second->neighbours.push_back(first);
		}
	}
};