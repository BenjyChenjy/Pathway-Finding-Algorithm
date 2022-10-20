// My Dijkstra's Algorithm Implementation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define INF 99999

#include <iostream>
#include<queue>
#include<vector>
#include<list>
#include<iterator>


using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::list;
using std::priority_queue;

class Edge {
public:
    int DestinationVertexID;
    int weight;

    Edge() {

    }

    Edge(int destVID, int w) {
        DestinationVertexID = destVID;
        weight = w;
    }

    void setEdgeValues(int destVID, int w) {
        DestinationVertexID = destVID;
        weight = w;
    }

    void setWeight(int w) {
        weight = w;
    }

    int getDestinationVertexID() {
        return DestinationVertexID;
    }

    int getWeight() {
        return weight;
    }
};

class Vertex {
public:
    int state_id;
    string state_name;
    list<Edge> edgelist;

    Vertex() {
        state_id = 0;
        state_name = "";
    }

    Vertex(int id, string sname) {
        state_id = id;
        state_name = sname;
    }

    int getStateID() {
        return state_id;
    }

    string getStateName() {
        return state_name;
    }

    void setID(int id) {
        state_id = id;
    }

    void setStateName(string sname) {
        state_name = sname;
    }

    list<Edge> getEdgeList() {
        return edgelist;
    }

    void printEdgeList()
    {
        cout << "[";
        for (auto it = edgelist.begin(); it != edgelist.end(); it++)
        {
            cout << it->getDestinationVertexID() << "(" << it->getWeight() << ") ";
        }
        cout << "]" << "\n";
    }
};

class Graph {
public:
    vector<Vertex> vertices;
    int edge_count = 0;

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.getStateID());
        if (check)
        {
            cout << "Vertex with this ID already exists" << "\n";
        }
        else
        {
            vertices.push_back(newVertex);
            cout << "New Vertex Added Successfully" << "\n";
        }
    }

    bool checkIfVertexExistByID(int vid) {

        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).getStateID() == vid)
            {
                return true;
            }
        }
        return false;
    }

    void printNeighbor(int id1)
    {
        cout << "Vertex with " << id1 << " has neighbors : ";
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).state_id == id1)
            {
                for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                {
                    cout << it->DestinationVertexID << " ";
                }
            }
        }
        cout << "\n";
    }

    string getNameByID(int id1)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).state_id == id1)
            {
                return vertices.at(i).state_name;
            }
        }
    }

    void printGraph() {
        for (int i = 0; i < vertices.size(); i++)
        {
            Vertex temp;
            temp = vertices.at(i);
            cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
            if (!temp.edgelist.empty())
            {
                cout << "[";
                for (auto it = temp.edgelist.begin(); it != temp.edgelist.end()--; it++)
                {
                    cout << getNameByID(it->DestinationVertexID) << "(" << it->DestinationVertexID << ")," << it->weight << "     ";
                }
                auto it = temp.edgelist.end();
                advance(it, -1);
                cout << getNameByID(it->DestinationVertexID) << "(" << it->DestinationVertexID << ")," << it->weight << "]"<<"\n";
            }
            else
            {
                cout << "\n";
            }
        }
    }



    void addEdgeByID(int id1, int id2, int w) {
        bool check1, check2, check3;
        check1 = checkIfVertexExistByID(id1);
        check2 = checkIfVertexExistByID(id2);
        if (check1 && check2)
        {
            check3 = checkifEdgeExistByID(id1, id2);
            if (check3) cout << "Edge already exists" << "\n";
            else
            {
                for (int i = 0; i < vertices.size(); i++)
                {
                    if (vertices.at(i).getStateID() == id1)
                    {
                        Edge e(id2, w);
                        vertices.at(i).edgelist.push_back(e);
                        //vertices.at(i).printEdgeList();
                    }
                    else if (vertices.at(i).getStateID() == id2)
                    {
                        Edge e(id1, w);
                        vertices.at(i).edgelist.push_back(e);
                        //vertices.at(i).printEdgeList();
                    }
                }
                edge_count++;
                cout << "Edge Added Successfully" << "\n";
            }
        }
        else
        {
            cout << "Invalid Vertices";
        }
    }

    Vertex getVertexByID(int vid)
    {
        Vertex temp;
        for (int i = 0; i < vertices.size(); i++)
        {
            temp = vertices.at(i);
            if (temp.getStateID() == vid)
            {
                return temp;
            }        
        }
        return temp;
    }

    bool checkifEdgeExistByID(int id1, int id2) {

        Vertex v = getVertexByID(id1);
        list<Edge> e;
        e = v.getEdgeList();
        for (auto it = e.begin(); it != e.end(); it++)
        {
            if (it->getDestinationVertexID() == id2)
            {
                return true;
            }
        }
        return false;
    }

    void UpdateEdgeByID(int id1, int id2, int w)
    {
        bool check = checkifEdgeExistByID(id1, id2);
        if (check)
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).getStateID() == id1)
                {
                    for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                    {
                        if (it->getDestinationVertexID() == id2)
                        {
                            it->setWeight(w);
                            break;
                        }
                    }
                }
                else if (vertices.at(i).getStateID() == id2)
                {
                    for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                    {
                        if (it->getDestinationVertexID() == id1)
                        {
                            it->setWeight(w);
                            break;
                        }
                    }
                }
            }
            cout << "Edge Weight Updated Successfully" << "\n";
        }
        else
            cout << "Edge does not exist" << "\n";

    }

    void deleteEdgeByID(int id1, int id2)
    {
        bool check = checkifEdgeExistByID(id1, id2);
        if (check)
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).state_id == id1)
                {
                    for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                    {
                        if (it->DestinationVertexID == id2)
                        {
                            vertices.at(i).edgelist.erase(it);
                            break;
                        }
                    }
                }
                else if (vertices.at(i).state_id == id2)
                {
                    for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                    {
                        if (it->DestinationVertexID == id1)
                        {
                            vertices.at(i).edgelist.erase(it);
                            break;
                        }
                    }
                }
            }
            cout << "Edge successfully deleted" << "\n";
        }
        else
        {
            cout << "Edge does not exist" << "\n";
        }

    }
    void updateVertexByID(int id1,int id2,string sname)
    {
        bool check1 = checkIfVertexExistByID(id1);
        bool check2 = checkIfVertexExistByID(id2);
        if ((check1&&!check2)||(id1==id2))
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).state_id == id1)
                {
                    vertices.at(i).state_id = id2;
                    vertices.at(i).state_name = sname;
                    break;
                }
            }
            for (int i = 0; i < vertices.size(); i++)
            {
                for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                {
                    if (it->DestinationVertexID == id1)
                    {
                        it->DestinationVertexID = id2;
                        break;
                    }
                }
            }
            cout << "Vertex Successfully Updated" << "\n";
        }
        else if(!check1)
        {
            cout << "Vertex does not exist" << "\n";
        }
        else if (check2)
        {
            cout << "Updated Vertex ID already exists" << "\n";
        }
        else
        {
            cout << "Invalid Vertex" << "\n";
        }
    }

    void deleteVertexByID(int id1)
    {
        bool check = checkIfVertexExistByID(id1);
        if (check)
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).state_id == id1)
                {
                    auto it = vertices.begin();
                    advance(it, i);
                    vertices.erase(it);
                    break;
                }
            }
            for (int i = 0; i < vertices.size(); i++)
            {
                for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++)
                {
                    if (it->DestinationVertexID == id1)
                    {
                        vertices.at(i).edgelist.erase(it);
                        break;
                    }
                }
            }
            cout << "Vertex Successfully Deleted" << "\n";
        }
        else
        {
            cout << "Vertex does not exist" << "\n";
        }
    }

    void deleteVertexByIDTutorial(int id1)
    {
        bool check = checkIfVertexExistByID(id1);
        if (check)
        {
            int vIndex = 0;
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).getStateID() == id1)
                {
                    vIndex = i;
                    break;
                }
            }
            for (auto it = vertices.at(vIndex).edgelist.begin(); it != vertices.at(vIndex).edgelist.end(); it++)
            {
                deleteEdgeByID(it->getDestinationVertexID(), id1);
            }
            vertices.erase(vertices.begin() + vIndex);
            cout << "Vertex Deleted Successfully" << "\n";
        }
        else
        {
            cout << "Vertex does not exist" << "\n";
        }

    }

    int getVertexIndex(int id)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).state_id == id)
            {
                return i;
            }
        }
    }

    void Dijkstra(int S)
    {
        int SourceIndex;
        vector<bool> visited;
        for (int i = 0; i < vertices.size(); i++)
        {
            visited.push_back(false);
        }
        vector<int> distance;
        for(int i = 0; i < vertices.size(); i++)
        {
            distance.push_back(INF);
        }

        for (int i = 0; i < vertices.size();i++)
        {
            if (vertices.at(i).state_id == S)
            {
                SourceIndex = i;
                break;
            }
        }
        distance[SourceIndex] = 0;

        int previous[100];
        

        auto compare = [](Edge a, Edge b)
        {
            return a.weight > b.weight;
        };

        priority_queue<Edge, vector<Edge>, decltype(compare)> Q(compare);
        Edge Source(S, 0);
        //cout << "Edge Destination ID:" << Source.DestinationVertexID << "\n";
        //cout << "Edge Weight: " << Source.weight << "\n";
        Q.push(Source);
        while (!Q.empty())
        {
            Edge next = Q.top();
            Q.pop();
            int nextIndex = getVertexIndex(next.DestinationVertexID);
            visited[nextIndex] = true;
            for (auto it = vertices.at(nextIndex).edgelist.begin(); it != vertices.at(nextIndex).edgelist.end(); it++)
            {
                int edgeDestinationIndex = getVertexIndex(it->DestinationVertexID);
                if (!visited[edgeDestinationIndex])
                {
                    int newDistance = distance[nextIndex] + it->weight;
                    if (newDistance < distance[edgeDestinationIndex])
                    {
                        previous[edgeDestinationIndex] = nextIndex;
                        distance[edgeDestinationIndex] = newDistance;
                    }
                    Q.push(*it);
                }

            }
        }

        for (int i = 0; i < distance.size(); i++)
        {
            if(distance[i]!=99999)
                cout << vertices.at(i).state_name << "(" << vertices.at(i).state_id << "): " << distance[i] <<"\n";
            else
                cout << "No path between " << getNameByID(S) << "(" << S << ")" << " and " << vertices.at(i).state_name << "(" << vertices.at(i).state_id << ")" << "\n";
        }
    }

    void clearGraph()
    {
        vertices.clear();
    }

};

int main()
{
    Graph g;
    string sname;
    int id1, id2, w;
    int option;
    Vertex v1;
    cout << "A Vertex Consists of a Vertex ID and a Vertex Name" << "\n";
    cout << "An Edge consists of a Source Vertex and a Destination Vertex" << "\n";
    do {
        cout << "What operation do you want to perform?" << "\n";
        cout << "Select Option Number" << "\n";
        cout << "1. Add Vertex" << "\n";
        cout << "2. Update Vertex" << "\n";
        cout << "3. Delete Vertex" << "\n";
        cout << "4. Add Edge" << "\n";
        cout << "5. Update Edge" << "\n";
        cout << "6. Delete Edge" << "\n";
        cout << "7. Print All Neighbors of a Vertex" << "\n";
        cout << "8. Print Graph" << "\n";
        cout << "9. Print Number of Vertices" << "\n";
        cout << "10. Print Number of Edges" << "\n";
        cout << "11. Give the shortest path between one Vertex and all other Vertices" << "\n";
        cout << "99. Delete All Vertices and Edges" << "\n";
        cout << "\n";
        cin >> option;
        cout << "\n";

        switch (option)
        {
        case 0:
            break;
        case 1:
            cout << "Add Vertex Operation" << "\n";
            cout << "Enter New Vertex ID: ";
            cin >> id1;
            cout << "Enter New Vertex Name: ";
            cin >> sname;
            v1.setID(id1);
            v1.setStateName(sname);
            g.addVertex(v1);

            break;
        case 2:
            cout << "Update Vertex Operation" << "\n";
            cout << "Enter Vertex ID: ";
            cin >> id1;
            cout << "Enter Updated Vertex ID: " ;
            cin >> id2;
            cout << "Enter Updated Vertex Name: ";
            cin >> sname;
            g.updateVertexByID(id1, id2, sname);
            break;

        case 3:
            cout << "Delete Vertex Operation" << "\n";
            cout << "Enter Vertex ID: ";
            cin >> id1;
            g.deleteVertexByIDTutorial(id1);
            break;

        case 4:
            cout << "Enter ID of Source Vertex: ";
            cin >> id1;
            cout << "Enter ID of Destination Vertex: ";
            cin >> id2;
            cout << "Enter weight of Edge: ";
            cin >> w;
            g.addEdgeByID(id1, id2, w);
            break;

        case 5:
            cout << "Update Edge Operation" << "\n";
            cout << "Enter ID of Source Vertex: ";
            cin >> id1;
            cout << "Enter ID of Destination Vertex: ";
            cin >> id2;
            cout << "Enter new weight of Edge: ";
            cin >> w;
            g.UpdateEdgeByID(id1, id2, w);
            break;

        case 6:
            cout << "Delete Edge Operation" << "\n";
            cout << "Enter ID of Source Vertex: ";
            cin >> id1;
            cout << "Enter ID of Destination Vertex: ";
            cin >> id2;
            g.deleteEdgeByID(id1, id2);
            break;

        case 7:
            cout << "Print Neighbor Operation" << "\n";
            cout << "Enter ID of Vertex: ";
            cin >> id1;
            g.printNeighbor(id1);
            break;

        case 8:
            cout << "Print Graph Operation" << "\n";
            g.printGraph();
            break;

        case 9:
            cout << "Print Number of Vertices Operation" << "\n";
            cout << "Number of Vertices: " << g.vertices.size() << "\n";
            break;
        case 10:
            cout << "Print Number of Edges Operation" << "\n";
            cout << "Number of Edges: " << g.edge_count << "\n";
            break;
        case 11:
            cout << "Enter Source Vertex ID: ";
            cin >> id1;
            g.Dijkstra(id1);
            break;
        case 99:
            g.clearGraph();
            cout << "All Vertices and Edges Deleted" << "\n";
        default:
            cout << "Please Enter Valid Option Number" << "\n";
        }
        cout << "\n";

    } while (option != 0);

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
