#include <iostream>
#include <vector>
#include <linked_list.hpp> 
#include <graph.hpp> 
#include <string>
#include <map>
#include <fstream>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

bool testLinkedList() {
    LinkedList<int> linkedList;
    linkedList.insert(10);
    linkedList.insert(100);

    if (linkedList.find(10))
        std::cout << "10 is in the linked list\n";
    else
        return false;

    if (linkedList.find(20))
        return false;
    else
        std::cout << "20 is not in the linked list\n";
    

    if (linkedList.find(100))
        std::cout << "100 is in the linked list\n";
    else
        return false;

    if (linkedList.size() == 2)
        std::cout << "The linked list has 2 nodes\n";
    else
        return false;

    linkedList.remove(100);
    
    if (linkedList.find(100))
        return false;
    else
        std::cout << "100 is not in the linked list\n";

    if (linkedList.size() == 1)
        std::cout << "The linked list has 1 node\n";
    else
        return false;

    return true;
}

bool testStack() {
    Stack<int> stack;

    for (int i = 0; i < 5; ++i)
        stack.push(i);

    if (stack.empty())
        return false;
    else
        std::cout << "Stack is not empty\n";

    for (int i = 4; i >= 0; --i) {
        if (stack.pop() == i)
            std::cout << "Remove tail node in stack successfully\n";
        else
            return false; 
    }
   
    if (stack.empty())
        std::cout << "Stack is empty\n";
    else
        return false;
    
    return true;
}

bool testGraph() {
    Graph G(6);
    G.insertEdge(0, 1);
    G.insertEdge(1, 2);
    G.insertEdge(1, 3);
    G.insertEdge(2, 4);
    G.insertEdge(4, 3);
    G.insertEdge(4, 5);

    std::cout << "Path from 0 to 5: ";
    std::vector<int> path = G.search(0, 5);
    for (int i = 0; i < path.size(); ++i) 
        std::cout << path[i] << " ";
    std::cout << "\n";
    
    return true;
}

void searchOnCampus(std::string start = "BELL", std::string destination = "HAPG") {
    std::ifstream reader("assets/map_info.txt");
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i) {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        G.insertEdge(u, v);
    }

    std::vector<int> path = G.search(name2index[start], name2index[destination]);

    std::cout << "Path from " << start  << " to " << " detination: " << start ;
    for (int i = 1; i < path.size(); ++i)
        std::cout << " -> " << index2name[path[i]];
    
    std::cout << "\n";

#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    
    for (int i = 0; i < n; ++i) {
        cv::circle(image, cv::Point(xs[i], ys[i]), 5, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, index2name[i],  cv::Point(xs[i], ys[i]-10),  cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }

    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) 
            cv::line(image, cv::Point(xs[path[i]], ys[path[i]]), cv::Point(xs[path[i-1]], ys[path[i-1]]), cv::Scalar(0, 255, 0), 4);
    }
    cv::imshow("Path from " + start + " to " + destination, image);
    cv::waitKey(0);

#else
    std::cout << "You have to use OpenCV to visualize your map road\n";
#endif


}
int main() {
    if (testLinkedList()) {
        std::cout << "Your linked list implementation is correct\n";
    } else {
        std::cout << "Your linked list implementation is incorrect\n";
        return -1;
    }
    
    std::cout << "\n\n";
    
    if (testStack()) {
        std::cout << "Your stack implementation is correct\n";
    } else {
        std::cout << "Your stack implementation is incorrect\n";
        return -1;
    }
    
    std::cout << "\n\n";

    if (testGraph()) {
        std::cout << "Your linked list and stack implementation is correct\n";
    } else {
        std::cout << "Your linked list and stack implementation is incorrect\n";
        return -1;
    }

    std::cout << "\n\n";
    
    searchOnCampus("RSWE", "WJWH");

    std::cout << "\n";
    
}
