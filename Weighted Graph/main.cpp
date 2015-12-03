// A C++ program to determine the shortest path of a directed graph
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;
 
int main(int argc, char* argv[])
{
    if (argc != 4) 
    {
        cerr << "Incorrect number of command line arguments." << endl;
        cerr << "Usage: "<< argv[0] << " <an input file>" << endl;
        return EXIT_FAILURE;
    }

    // read data from an input file
    ifstream inf(argv[1]);
    if (!inf.is_open()) 
    {
        // check if the file can be opened
        cerr << "Error: cannot open an input file \"" << argv[1] << "\"." << endl;
        return EXIT_FAILURE;
    }

    // read data from file and store in a graph
    Graph graph(argv[1]);
    graph.findShortestPath( atoi(argv[2]), atoi(argv[3]) );
    
    return EXIT_SUCCESS;
}
