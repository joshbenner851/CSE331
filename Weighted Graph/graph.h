/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;
class Vertex
{
public:
    Vertex(){}
    ~Vertex(){}
    int id;
    map<int,double> edgesToAdjacent;
    double mPathCost;
    vector<int> mPath;
    //bool mVisited = false;
};


class Graph
{
public:
    int numOfNodes; 
    vector<Vertex>vertices;
    Graph(char* filename) 
    {
        ifstream file(filename);
        string line;
        //create vector of Vertex's
        while (getline(file,line))
        {
            istringstream lineStream(line);
            int id;
            int edge;
            double weight;
            lineStream >> id;
            lineStream >> edge;
            lineStream >> weight;
            //bool to see if a vertex has already been created from the source
            bool used = false;
            for(int x=0; x<vertices.size(); x++)
            {
                if(vertices[x].id == id)
                {
                    used = true;
                    break;
                }
            }
            //bool that finds if a vertex has been created from the destination
            bool created = false;
            for(auto vertex: vertices)
            {
                if(vertex.id == edge)
                {
                    created = true;
                    break;
                }
            }
            //this vertex hasn't had a connection to it, but we should still make it
            if(created == false)
            {
                Vertex v;
                v.id = edge;
                vertices.push_back(v);
            }
            //already has a vertex created, so just add to it's map
            if( used )
            {
                for(int x =0; x<vertices.size(); x++)
                {
                    if(id == vertices[x].id)
                    {
                        vertices[x].edgesToAdjacent[edge] = weight;
                    }
                }
            }
            //create a new vertex and push to vertices vector
            else
            {
                Vertex v;
                v.id = id;
                
                v.edgesToAdjacent[ edge ] = weight;
                vertices.push_back(v);
            }
            numOfNodes++;
        }
    } 
    ~Graph() {}
    void findShortestPath(int source, int destination);
    Vertex findVertex(int node);
    //bubble sorts the vector of Vertex's
    vector<Vertex> sortTraverseList(std::vector<Vertex> v, Vertex source);
    
};
//Finds a vertex in the vertices vector
Vertex Graph::findVertex(int node)
{
    for( auto vertex : vertices)
    {
        if(vertex.id == node)
        {
            return vertex;
        }
    }
}

//bubble sorts the vector of Vertex's
//small # of edges so it's okay // I was too lazy to use a priority queque in 
//Should at least make this use a linear search since it's O(n) vs O(n^2)
vector<Vertex> Graph::sortTraverseList(vector<Vertex> v, Vertex source)
{
    bool swapped = true;
    int j = 0;
    Vertex tmp;
    while (swapped) 
    {
        swapped = false;
        j++;
        for (int i = 0; i < v.size() - j; i++) {
            //if(source.edgesToAdjacent[v[i].id] > source.edgesToAdjacent[v[i+1].id])
            if(v[i].mPathCost > v[i +1].mPathCost)
            {
                tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
                swapped = true;
            }
        }
    }
    return v;
}

//finds shortest path between a source and destination vertex
//Applying Dijkstra's
void Graph::findShortestPath(int s, int dest)
{

    // map<string,double>pathCost;
    vector<Vertex> traverseList;
    vector<Vertex> pathVertex;

    // grab the source vertex
    Vertex source = findVertex(s);
    source.mPath.push_back(s);
    Vertex destination = findVertex(dest);
    
    //source should always be in the path if it exists
    pathVertex.push_back(source);
    //initialize all vertices to -1(inf)
    for(int x=0; x<vertices.size(); x++)
    {
        vertices[x].mPathCost = -1;
    }
    
    //source costs 0
    source.mPathCost = 0;
    //if the source has no edges, it doesn't point to anything, no path
    if(source.edgesToAdjacent.empty())
    {
        cout << "NO PATH FOUND" << endl;
        return;
    }

    typedef std::map<int,double>::iterator it_type;
    //add the vertex's that the source points to the traverseList
    for(it_type iterator = source.edgesToAdjacent.begin(); iterator != source.edgesToAdjacent.end(); iterator++) 
    {
        for(auto v: vertices)
        {
            if(v.id == iterator->first)
            {  
                v.mPath = source.mPath;
                v.mPathCost = iterator->second;
                traverseList.push_back(v);
            }
        }
    }

    traverseList = sortTraverseList(traverseList,source);

    while( !traverseList.empty() )
    {

        //MinCost vertex
        traverseList = sortTraverseList(traverseList,source);
        
        //possibly when assigning this need to delete from traverse list?
        Vertex minCost = traverseList[0];

        for( int x=0; x < pathVertex.size(); x++ )
        {
            if( minCost.id == pathVertex[x].id )
            {
                pathVertex.erase( pathVertex.begin() + x );
            }
        }

        pathVertex.push_back(minCost);
        //mincost vertex is the destination vertex, aka we're done
        if( minCost.id == destination.id )
        {
            for(auto i: minCost.mPath)
            {
                cout << i << "->";
            }
            cout << minCost.id << " " << setprecision (2) << fixed << minCost.mPathCost << endl;
            traverseList.erase(traverseList.begin());
            break;
        }
        else
        {
            //for all adjacent to the MinCost Vertex
            for(it_type iterator = minCost.edgesToAdjacent.begin(); iterator != minCost.edgesToAdjacent.end(); iterator++) 
            {
                for(auto v: vertices)
                {
                    if(v.id == iterator->first)
                    {
                        //hey it's infinite and if the vertex is adjacent to minCost
                        //lets do shit
                        if(v.mPathCost == -1 )//&& v.id == iterator->first)
                        {  
                            double cost = iterator->second + minCost.mPathCost;
                            v.mPathCost = iterator->second + minCost.mPathCost;

                            bool inTraverse = false;
                            for (auto vertex : traverseList)
                            {
                                if(vertex.id == v.id)
                                {
                                    inTraverse = true;
                                    if( vertex.mPathCost > v.mPathCost)
                                    {
                                        v.mPath = minCost.mPath;
                                        v.mPath.push_back(minCost.id);
                                        vertex.mPathCost = v.mPathCost;
                                        traverseList.push_back(v);
                                    }

                                }
                            }
                            if(!inTraverse)
                            {
                                v.mPath = minCost.mPath;
                                v.mPath.push_back(minCost.id);
                                v.mPathCost = cost;
                                traverseList.push_back(v);
                            }
                        }
                        else
                        {
                            double newCost = minCost.mPathCost + iterator->second;
                            if(v.mPathCost > newCost)
                            {
                                v.mPathCost = newCost;
                            }
                            
                        }
                    }
                }
            }
            traverseList.erase(traverseList.begin());
        }
    }
    if( pathVertex[pathVertex.size()-1].id != destination.id )
    {
        cout << "NO PATH FOUND" << endl;
    }   
}