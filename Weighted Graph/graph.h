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

using namespace std;
class Vertex
{
public:
    Vertex(){}
    ~Vertex(){}
    int id;
    map<int,double> edgesToAdjacent;
    double mPathCost;
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
        while (getline(file,line))
        {
            istringstream lineStream(line);
            int id;
            int edge;
            double weight;
            lineStream >> id;
            lineStream >> edge;
            lineStream >> weight;

            //cout << "id: " << id << endl;
            bool used = false;
            
            for(int x=0; x<vertices.size(); x++)
            {
                if(vertices[x].id == id)
                {
                    used = true;
                    break;
                }
            }
            bool created = false;
            for(auto vertex: vertices)
            {
                if(vertex.id == edge)
                {
                    created = true;
                    break;
                }
            }
            if(created == false)
            {
                Vertex v;
                v.id = edge;
                vertices.push_back(v);
            }
            //already has a vertex created
            if( used )
            {
                //cout << "id: " << id;
                for(int x =0; x<vertices.size(); x++)
                {
                    if(id == vertices[x].id)
                    {
                        vertices[x].edgesToAdjacent[edge] = weight;
                        //cout << "size " << vertices.size() <<  " " << id << "->" << edge << " weight: " << weight << " k,v: " << vertex.edgesToAdjacent[edge] << endl;
                        cout << "vertex: " << vertices[x].id << " has connections to ";
                        typedef std::map<int,double>::iterator it_type;
                        for(it_type iterator = vertices[x].edgesToAdjacent.begin(); iterator != vertices[x].edgesToAdjacent.end(); iterator++) {
                            cout << iterator->first << " weight(" << iterator->second << "), "; /*<< " value: " << iterator->second << " ";*/
                            // iterator->second = value
                            // Repeat if you also want to iterate through the second map.
                        }
                        cout << endl;
                    }
                }
            }
            else
            {
                Vertex v;
                v.id = id;
                
                v.edgesToAdjacent[ edge ] = weight;
                vertices.push_back(v);
                // cout << "size " << vertices.size() <<  " " << id << "->" << edge <<  " weight: " << weight << endl;
                // typedef std::map<int,double>::iterator it_type;
                // cout << "vertex: " << v.id << " has connections to ";
                // for(it_type iterator = v.edgesToAdjacent.begin(); iterator != v.edgesToAdjacent.end(); iterator++) 
                // {
                //     cout << "key: " << iterator->first << " value: " << iterator->second << " ";
                //     // iterator->second = value
                //     // Repeat if you also want to iterate through the second map.
                // }
                // cout << endl;
            }
            numOfNodes++;
        }
    } 
    ~Graph() {}
    void findShortestPath(int source, int destination);
    Vertex findVertex(int node);
    vector<Vertex> sortTraverseList(std::vector<Vertex> v, Vertex source);
    
    
};

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
            if(source.edgesToAdjacent[v[i].id] > source.edgesToAdjacent[v[i+1].id])
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

void Graph::findShortestPath(int s, int dest)
{
    cout << endl;
    cout << endl;
    cout << endl;

    // map<string,double>pathCost;
    vector<Vertex> traverseList;
    vector<Vertex> pathVertex;

    // grab the source vertex
    Vertex source = findVertex(s);
    Vertex destination = findVertex(dest);
    //source should always be in the path if it exists
    pathVertex.push_back(source);
    
    for(int x=0; x<vertices.size(); x++)
    {
        vertices[x].mPathCost = -1;
    }
    source.mPathCost = 0;
    if(source.edgesToAdjacent.empty())
    {
        cout << "NO PATH FOUND" << endl;
        return;
    }
    //std::priority_queue < Vertex, std::vector<Vertex>, Compare > traverseList;
    typedef std::map<int,double>::iterator it_type;
    //add the vertex's that the source points to the traverseList
  
    for(it_type iterator = source.edgesToAdjacent.begin(); iterator != source.edgesToAdjacent.end(); iterator++) 
    {
        for(auto v: vertices)
        {
            if(v.id == iterator->first)
            {  
                traverseList.push_back(v);
            }
        }
    }
    //testing that sorting a list of vertex's works
    // Vertex a;
    // a.id = 4;
    // Vertex b;
    // b.id = 5;
    // source.edgesToAdjacent[a.id] = 7;
    // source.edgesToAdjacent[b.id] = 10;
    // traverseList.push_back(a);
    // traverseList.push_back(b);

    traverseList = sortTraverseList(traverseList,source);

    // for( auto v : traverseList)
    // {
    //     cout << "Vertex: " << v.id << " with weight: " << source.edgesToAdjacent[v.id] << endl;
    // }
    // cout << endl;
    double cost = 0;
    
    
    
    

    while( !traverseList.empty() )
    {

        //MinCost vertex
        traverseList = sortTraverseList(traverseList,source);
        Vertex minCost = traverseList[0];
        //minCost.mPathCost = 0;
        if(minCost.mPathCost <= 0 )
        {
            for(it_type iterator = source.edgesToAdjacent.begin(); iterator != source.edgesToAdjacent.end(); iterator++) 
            {
                for(auto v: vertices)
                {
                    if(v.id == iterator->first)
                    {

                        minCost.mPathCost = iterator->second;
                        //cout << "v.id: " << v.id << " minCosts: " << iterator->first << endl;
                        break;
                    }
                }
                break;
            }
        }
        

        cout << "moving to vertex: " << minCost.id << " which has a cost of: " << minCost.mPathCost << endl;

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
            if(minCost.mPathCost < 0)
            {
                for(it_type iterator = source.edgesToAdjacent.begin(); iterator != source.edgesToAdjacent.end(); iterator++) 
                {
                    if(minCost.id == iterator->first)
                    {
                        minCost.mPathCost = iterator->second;
                    }
                }
            }
            for(int x=0; x<pathVertex.size(); x++)
            {
                if(x < pathVertex.size() -1)
                {
                    cout << pathVertex[x].id << "->";
                }
                else
                {
                    cout << pathVertex[x].id << " " << minCost.mPathCost << endl;
                }
            }
            break;
        }
        else
        {
            //for all adjacent to the MinCost Vertex
            for(it_type iterator = minCost.edgesToAdjacent.begin(); iterator != minCost.edgesToAdjacent.end(); iterator++) 
            {
                for(auto v: vertices)
                {
                    cout << "v.id: " << v.id << " minCosts vertices: " << iterator->first << endl;
                    //cout << "v.id: " << v.id << " adj id: " << iterator->first << endl;
                    if(v.mPathCost == -1 && v.id == iterator->first)
                    {  
                        if(v.id == 5)
                        {
                            cout << "iterC: " << iterator->second << " minC: " << minCost.mPathCost << endl;
                        }
                        v.mPathCost = iterator->second + minCost.mPathCost;
                        cout << "v: " << v.id << " cost: " << v.mPathCost << endl;
                        traverseList.push_back(v);
                    }
                    else
                    {
                        if(v.id == iterator->first)
                        {
                            double newCost = minCost.mPathCost + iterator->second;
                            cout << "v cost:" << v.mPathCost << " newCost: " << newCost << endl;
                            if(v.mPathCost > newCost)
                            {
                                v.mPathCost = newCost;
                                traverseList.push_back(v);
                                cout << "vertex: " << v.id << " cost: " << v.mPathCost << endl;
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

    // for( auto v: traverseList)
    // {

    // }


    // for(map<int,double>::iterator iter = vertex.edgesToAdjacent.begin(); iter != vertex.edgesToAdjacent.end(); iter++)
    // {
    //     adjacents.push_back( iter->second );
    //     cout << "value: " << iter->second << endl;
    // }
    // cout << "got here" << endl;
    

    //std::priority_queue<Vertex, std::vector<Vertex>, std::greater<int> > traverseList(myints,myints+4);


