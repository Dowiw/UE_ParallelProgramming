#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

// Linked List for managing to-do tasks
struct TaskNode {
    string task;
    TaskNode* next;
    TaskNode(string t) : task(t), next(nullptr) {}
};

// Binary Tree for a simple decision tree (yes/no questions)
struct TreeNode {
    string question;
    TreeNode* yes;
    TreeNode* no;
    TreeNode(string q) : question(q), yes(nullptr), no(nullptr) {}
};

// Graph for representing a social network (friends)
class Graph {
    int V;
    vector<list<int>> adj;
public:
    Graph(int v) : V(v), adj(v) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "User " << i << " is connected to: ";
            for (int v : adj[i])
                cout << v << " ";
            cout << endl;
        }
    }
};

int main() {
    // Static vs. Dynamic Array: storing daily temperatures
    cout << "=== Static vs Dynamic Array: Temperatures ===" << endl;
    int staticTemps[5] = {20, 21, 19, 22, 24}; // known ahead
    cout << "Static Array: ";
    for (int t : staticTemps) cout << t << " ";
    cout << endl;

    vector<int> dynamicTemps; // dynamic input
    for (int i = 25; i <= 28; i++) dynamicTemps.push_back(i);
    cout << "Dynamic Array: ";
    for (int t : dynamicTemps) cout << t << " ";
    cout << endl << endl;

    // Linked List: to-do list
    cout << "=== Linked List: To-Do Tasks ===" << endl;
    TaskNode* head = new TaskNode("Write report");
    head->next = new TaskNode("Email professor");
    head->next->next = new TaskNode("Submit assignment");

    TaskNode* temp = head;
    while (temp) {
        cout << "- " << temp->task << endl;
        temp = temp->next;
    }
    cout << endl;

    // Set: unique user IDs
    cout << "=== Set: Unique User IDs ===" << endl;
    set<int> userIDs = {101, 102, 103, 101, 104};
    for (int id : userIDs) cout << "User ID: " << id << endl;
    cout << endl;

    // Hash Table: phone book
    cout << "=== Hash Table: Phone Book ===" << endl;
    unordered_map<string, string> phoneBook;
    phoneBook["Alice"] = "123-456";
    phoneBook["Bob"] = "987-654";
    phoneBook["Charlie"] = "555-000";
    for (auto& entry : phoneBook)
        cout << entry.first << ": " << entry.second << endl;
    cout << endl;

    // Stack: website back button history
    cout << "=== Stack: Browser History ===" << endl;
    stack<string> history;
    history.push("Home");
    history.push("About");
    history.push("Contact");
    while (!history.empty()) {
        cout << "Back to: " << history.top() << endl;
        history.pop();
    }
    cout << endl;

    // Queue: print jobs
    cout << "=== Queue: Print Queue ===" << endl;
    queue<string> printQueue;
    printQueue.push("Doc1.pdf");
    printQueue.push("Image.png");
    printQueue.push("Report.docx");
    while (!printQueue.empty()) {
        cout << "Printing: " << printQueue.front() << endl;
        printQueue.pop();
    }
    cout << endl;

    // Binary Tree: decision-making
    cout << "=== Binary Tree: Decision Tree ===" << endl;
    TreeNode* root = new TreeNode("Is it raining?");
    root->yes = new TreeNode("Take an umbrella.");
    root->no = new TreeNode("Enjoy the sunshine!");

    cout << root->question << endl;
    string answer;
    cout << "Answer (yes/no): ";
    cin >> answer;
    if (answer == "yes")
        cout << root->yes->question << endl;
    else if (answer == "no")
        cout << root->no->question << endl;
    else
        cout << "Invalid response." << endl;
    cout << endl;

    // Graph: social network
    cout << "=== Graph: Social Network ===" << endl;
    Graph g(4); // 4 users
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.printGraph();

    return 0;
}
