/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Graph
{
public:

	Graph(char* filename) 
	{
		ifstream file(filename);
		string line;
		int data;
		while (getline(file,line))
		{
			istringstream lineStream(line);
			//lineStream >> v.index;
            vector<int> v;
            lineStream >> data;
            int count = 0;
			while (lineStream >> data)
			{
				v.push_back(data);
			}
            vertexArray.push_back(v);
            count++;
			colorArray.push_back(0);
            
		}
	}
	~Graph() {}
    
    vector<int>colorArray;
	vector<vector<int> > vertexArray;
	// function to determine whether a graph is bipartite
	// start traverse a graph from node u
	// return true if a graph is bipartite. Otherwise, return false
	bool isBipartitePrintTraversePath(int u);
    bool VisitNode(int u, int color);
    std::string Color(int color);
};



bool Graph::VisitNode(int u,int color)
{
    bool isbipart = true;
    int color2 = color == 1 ? 2 : 1;
    for(auto node : vertexArray[u])
    {
        cout << node << " " << Color(u) << endl;
        if(colorArray[node] == 0)
        {
            colorArray[node] = color2;
            isbipart = VisitNode(node,color2);
        }
        else if(colorArray[node] == color)
        {
            cout << "CONFLICT " << node << " " << u << endl;
            return false;
        }
    }
    if(isbipart == false)
    {
        return false;
    }
    return true;
}

// function to determine whether a graph is bipartite
// start traverse a graph from node u
// return true if a graph is bipartite. Otherwise, return false
bool Graph::isBipartitePrintTraversePath(int u) {
    // unvisited color array spot = 0
    // white = 1
    // black = 2
    bool isbipart = true;
    if(u%2 == 0)
    {
        colorArray[u] = 1;
        
        cout << u << " " << Color(u) << endl;
        isbipart = VisitNode(u,1);
    }
    else
    {
        colorArray[u] = 2;
        isbipart = VisitNode(u,2);
    }
    return isbipart;
}

std::string Graph::Color(int color)
{
    if(colorArray[color] == 0)
    {
        return "WRONG!!!";
    }
    return colorArray[color] == 1 ? "WHITE" : "BLACK";
}

