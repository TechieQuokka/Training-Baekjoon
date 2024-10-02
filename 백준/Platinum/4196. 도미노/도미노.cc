#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct NodeType {
    vector<int> Vertex;
    bool IsVisit;
};

struct GraphType {
    vector<NodeType> Nodes;
    int Size;
};

int Strongly_Connected_Components(GraphType& graph);
GraphType Create_Graph(int size);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int testcase = 0;
    cin >> testcase;
    for (int repeat = 0; repeat < testcase; repeat++) {
        int vertex = 0, edge = 0;
        cin >> vertex >> edge;

        GraphType graph = Create_Graph(vertex);
        for (int repeat = 0; repeat < edge; repeat++) {
            int from = 0, to = 0;
            cin >> from >> to;
            graph.Nodes[from].Vertex.push_back(to);
        }

        auto result = Strongly_Connected_Components(graph);
        cout << result << "\n";
    }

    return 0;
}

GraphType Create_Graph(int size) {
    GraphType graph;
    graph.Size = size;
    graph.Nodes.resize(size + 1);
    return graph;
}

void Depth_First_Search(GraphType& graph, int current, stack<int>& finish_time) {
    graph.Nodes[current].IsVisit = true;

    for (int neighbor : graph.Nodes[current].Vertex) {
        if (!graph.Nodes[neighbor].IsVisit) {
            Depth_First_Search(graph, neighbor, finish_time);
        }
    }

    finish_time.push(current);
}

void Record_DFS(GraphType& graph, int current) {
    stack<int> s;
    s.push(current);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!graph.Nodes[node].IsVisit) {
            graph.Nodes[node].IsVisit = true;

            for (int neighbor : graph.Nodes[node].Vertex) {
                if (!graph.Nodes[neighbor].IsVisit) {
                    s.push(neighbor);
                }
            }
        }
    }
}

int Strongly_Connected_Components(GraphType& graph) {
    stack<int> finish_time;
    for (int i = 1; i <= graph.Size; i++) {
        if (!graph.Nodes[i].IsVisit) {
            Depth_First_Search(graph, i, finish_time);
        }
    }

    for (auto& node : graph.Nodes) {
        node.IsVisit = false;
    }

    int count = 0;
    while (!finish_time.empty()) {
        int node = finish_time.top();
        finish_time.pop();

        if (!graph.Nodes[node].IsVisit) {
            Record_DFS(graph, node);
            count++;
        }
    }

    return count;
}
