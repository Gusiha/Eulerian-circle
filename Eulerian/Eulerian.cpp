#include <list>
#include <iostream>
#include <string>
#include <iomanip>

class Graph
{
	int vertices; std::list<int>* adj;

public:
	Graph(int size)
	{
		vertices = size;
		adj = new std::list<int>[vertices];
	}
	~Graph();

	void print();
	bool checkUsed(int i, int vertex);
	int getVert();
	void addNode(int a, int b);
	bool eulerian();
	bool connected();
	int traversal(bool* checked, int i);
};

Graph::~Graph()
{
	delete[] adj;
}

void Graph::print()
{
	std::list<int>::iterator i;
	for (int n = 0; n < vertices; n++) {
		for (i = adj[n].begin(); i != adj[n].end(); ++i)
			std::cout << std::setw(2) << *i;
		std::cout << "\n";
	}
}

bool Graph::checkUsed(int i, int vertex)
{
	for (std::list<int>::iterator j = adj[i].begin(); j != adj[i].end(); ++j)
	{
		if (vertex == *j)
			return 1;
	}
	return 0;
}

int Graph::getVert()
{
	return vertices;
}

void Graph::addNode(int a, int b)
{
	adj[a].push_back(b);
	adj[b].push_back(a);
}

bool Graph::eulerian()
{
	if (connected() == false)
		return false;

	int odd = 0;
	for (int i = 0; i < vertices; i++)
	{
		if (adj[i].size() % 2 == 1)
		{
			odd++;
		}
	}

	if (odd > 2)
		return false;

	if (odd == 0)
		return true;
	else
		return false;
}

bool Graph::connected()
{
	bool* checked = new bool[vertices];
	int mark = 0;

	for (mark; mark < vertices; mark++)
	{
		checked = false;
	}

	for (mark = 0; mark < vertices; mark++)
	{
		if (adj[mark].size() != 0)
			break;
	}

	if (mark == vertices)
		return true;

	traversal(checked, mark);

	for (mark = 0; mark < vertices; mark++)
	{
		if (adj[mark].size() > 0 && checked[mark] == false)
			return false;
	}

	return true;
}

int Graph::traversal(bool* checked, int n)
{
	checked[n] = true;
	
	std::list<int>::iterator i = adj[n].begin();
	for (i; i != adj[n].end(); ++i)
	{
		if (checked[*i] == false)
			traversal(checked, *i);
	}
}

void matrixFill(Graph& g)
{
	std::string input;

	for (int i = 0; i < g.getVert(); i++)
	{
		for (int j = 0; j < g.getVert(); j++)
		{
			system("cls");
			if (!g.checkUsed(i, j)) {
				std::cout << "Is vertex " << i << " adjacent with " << j << "?\n1 - Yes.\n2 - No.\nInput: ";
				getline(std::cin, input);
				if (std::stoi(input) == 1)
					g.addNode(i, j);
			}

		}
		system("pause");
	}
}

int main()
{
	std::string input;

	std::cout << "Specify number of vertecies: ";
	getline(std::cin, input);
	Graph myGraph(std::stoi(input));
	system("cls");

	matrixFill(myGraph);
	myGraph.print();

	myGraph.eulerian();

	return 0;
}
