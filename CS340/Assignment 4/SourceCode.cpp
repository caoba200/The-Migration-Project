// Name: BAO CAO
// Student ID: 200363431
// SOURCE CODE FOR QUESTION 9.3 and 9.9
// Note: Each question is implemented as a function (topologicalSort for question 9.3
//   and singlesSourceShortestPath for question 9.9)
// There are 2 function calls in main function (both of them are commented)
// In order to run any of the program, just uncomment the corresponding function and run the program

#include <iostream>
#include <string>
#include <queue>

using namespace std;

// topological sort: the graph used in this function is the one from lecture slide
//  (slide 8 - 14_Chapter9_GraphAlgorithmsTopologicalSort_ShortestPath)
void topologicalSort() {
    int graph[7][7];
    // Inititalize the array
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            graph[i][j] = 0;
    
    // Setup in-degree for each vertex - indegree is stored at graph[x][x]
    // for example, indgree of v3 is stored in graph[2][2]
    graph[1][1] = 1;
    graph[2][2] = 2;
    graph[3][3] = 3;
    graph[4][4] = 1;
    graph[5][5] = 3;
    graph[6][6] = 2;
    
    // Setup out-degree for each vertex. For example, if v1 has 3 out degrees to v2, v3, v4
    // then graph[0][1] = graph[0][2] = graph[0][3] = 1
    graph[0][1] = graph[0][2] = graph[0][3] = 1;
    graph[1][3] = graph[1][4] = 1;
    graph[2][5] = 1;
    graph[3][2] = graph[3][5] = graph[3][6] = 1;
    graph[4][3] = graph[4][6] = 1;
    graph[6][5] = 1;
    
    // queue which will be used in topological sorting
    queue <int> result;
    
    // TOPOLOGICAL SORTING ALGORITHM
    while (result.size() != 7) {
        int vertex;
        for (vertex = 0; vertex < 7; vertex++) {
            // the first encountered vertex with indegree = 0 is pushed to the queue
            if(graph[vertex][vertex] == 0) {
                result.push(vertex);
                break;
            }
        }
        graph[vertex][vertex] = -1; // Mark the vertex as visited
        // Remove the vertex and its outdegree (reduce indegree of vertices that it connects to)
        for (int i = 0; i < 7; i++) {
            if(graph[vertex][i] == 1)
                graph[i][i]--;
        }
    }
    
    // DISPLAY RESULT
    cout << "Topological order: ";
    while (!result.empty()){
        cout << "v" << result.front() + 1 << " ";
        result.pop();
    }
    
    cout << endl;
}

// single-source shortest path problem: the graph used in this function is the one in lecture slides
// (slide 20 - 14_Chapter9_GraphAlgorithmsTopologicalSort_ShortestPath)
// The algorithm in this function is Dijkstra's algorithm
void singleSourceShortestPath() {
    int input;
    cout << "Enter the vertex that you want to start from (1 for v1, 2 for v2, etc.): ";
    cin >> input;
    
    // 2D Array which contain info of the graph
    int GRAPH[7][7];
    // initialize
    for(int i = 0; i< 7; i++)
        for(int j = 0; j < 7; j++)
            GRAPH[i][j] = 0;
    // setup the weights
    GRAPH[0][1] = 2;
    GRAPH[0][3] = 1;
    GRAPH[1][3] = 3;
    GRAPH[1][4] = 10;
    GRAPH[2][0] = 4;
    GRAPH[2][5] = 5;
    GRAPH[3][2] = 2;
    GRAPH[3][4] = 2;
    GRAPH[3][5] = 8;
    GRAPH[3][6] = 4;
    GRAPH[4][6] = 6;
    GRAPH[6][5] = 1;
    
    
    // Table with 7 vertices, each of them has 3 attributes: known, dv and pv
    int graph[7][3];
    // Initialize the graph
    for (int i = 0; i < 7; i++){
        // assign known of all vertices to false(0)
        graph[i][0] = 0;
        // assign dv of the input vertex to 0, the rest to infinity (999999)
        graph[i][1] = (i == input - 1) ? 0 : 999999;
        // assign pv of all vertices to 0
        graph[i][2] = 0;
    }
    
    int knownVertex = 1; // number of known vertices
    
    //BEGIN THE ALGORITH
    while(knownVertex < 7) {
        int smallestVertex = 999999;
        int index = 0;
        for(int i = 0; i< 7; i++) {
            // the current vertex has dv smaller than the smallest one and unknown
            if(graph[i][1] < smallestVertex && graph[i][0] == 0){
                smallestVertex = graph[i][1];
                index = i;
            }
        }
        
        // Mark the selected vertex as known
        graph[index][0] = 1;
        knownVertex++;
        // Update the distances of vertices that connect to index
        for(int i = 0; i < 7; i++) {
            if(GRAPH[index][i] != 0) {
                if(GRAPH[index][i] + graph[index][1] < graph[i][1]){
                    graph[i][1] = GRAPH[index][i] + graph[index][1];
                    graph[i][2] = index + 1;
                }
            }
        }
    }
    
    // THE RESULT IS DISPLAYED AS A SIMPLIFIED TALBE WHICH IS USED IN DIJKSTRA'S ALGORTHM
    // WHICH ONLY SHOW 2 COLUMN V AND Pv
    cout << "The final result as table form: " << endl;
    for(int i = 0; i < 7; i++) {
        if (i == 0)
           cout << "v" << i + 1 << "\t" << graph[i][1] << "\t" << graph[i][2] << endl;
        else
            cout << "v" << i + 1 << "\t" << graph[i][1] << "\t" << "v" << graph[i][2] << endl;
    }
    cout << endl;
    
}

int main() {
    
    //topologicalSort();
    //singleSourceShortestPath();
    
    return 0;
}
