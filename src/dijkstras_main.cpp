#include "dijkstras.h"

int main() {
    Graph g;
    file_to_graph("../src/medium.txt", g);
    vector<int> prev(g.numVertices - 1);
    vector<int> mst = dijkstra_shortest_path(g, 0, prev);
    vector<int> shortestPath = extract_shortest_path(mst, prev, 3);
    print_path(shortestPath, shortestPath.size());
    return 0;

}