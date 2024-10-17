#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Node Class
template <typename T> class Node {
private:
    T *data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;

public:
    //contructor
    Node (T *data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }

    // print method
    void print(){
        cout<<parent<<endl;
    }

    //compare method
    int compare(T* data){
        if(this->data < data)
            return -1;
        else if( this->data > data)
            return 1;
        else
            return 0;
    }

    //get methods
    T* getData(){
        return data;}
    Node<T> *getLeftChild(){
        return leftChild;}
    Node<T> *getRightChild(){
        return rightChild;}
    Node<T> *getParent(){
        return parent;}


    //set methods
    void setData(T* data){
        this->data = data;}
    void setLeftChild(Node<T>* leftChild){
        this->leftChild = leftChild;}
    void setRightChild(Node<T>* rightChild){
        this->rightChild = rightChild;}
    void setParent(Node<T>* parent){
        this->parent= parent;}
};

class Data {
private:
    int sourceVertex;
    int destinationVertex;
    int edgeCost;

public:
    Data (int sourceVertex, int destinationVertex, int edgeCost)
    {
        this->sourceVertex = sourceVertex;
        this->destinationVertex = destinationVertex;
        this->edgeCost = edgeCost;

    }
    int getSourceVertex(){
        return sourceVertex;}
    int getDestinationVertex(){
        return destinationVertex;}
    int getEdgeCost(){
        return edgeCost;}

    void setSourceVertex(int sourceVertex){
        this->sourceVertex = sourceVertex;}
    void setDestinationVertex(int destinationVertex){
        this->destinationVertex = destinationVertex;}
    void setEdgeCost(int edgeCost){
        this->edgeCost = edgeCost;}
    void print() const{
        cout<< sourceVertex<< " - " << destinationVertex << " -> " << edgeCost;}

    bool operator<(const Data& other) const {
        return edgeCost < other.edgeCost;
    }
    //compare method
    int compare(int edgeCost){
        if(this->edgeCost < edgeCost)
            return -1;
        else if( this->edgeCost > edgeCost)
            return 1;
        else
            return 0;
    }
};

template <typename T> class BinaryHeap {
private:
    Node<T> *root;
    int numberOfElements;
    int height;
    Node<T> *curr;

public:

    //Constructor
    BinaryHeap() {
        root = nullptr;
        numberOfElements = 0;
        height = 0;
        curr = nullptr;
    }

    //Destructor
    ~BinaryHeap() {
        Node<T> *temp = root;
        while (root) {
            root = root->next;
            delete temp->data;
            delete temp;
            temp = root;
        }
    }

    //get methods
    Node<T> *getRoot() {
        return root;
    }

    int getHeight() {
        return height;
    }

    int getNumberOfElements() {
        return numberOfElements;
    }

    //set methods
    void setRoot(Node<T> *root) {
        this->root = root;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setnumberOfElements(int numElements) {
        this->numberOfElements = numElements;
    }

    void setCurr(Node<T> *pos) {
        this->curr = pos;
    }

    Node<T> *getCurr() const {
        return curr;
    }

    //insert method and heapify
    void insertElement(T *data) {
        Node<T> *newNode = new Node<T>(data);
        if (root == nullptr) {
            root = newNode;
            curr = newNode;
        } else {
            if (curr->getRightChild() == nullptr) {
                curr->setRightChild(newNode);
            } else {
                curr->setLeftChild(newNode);
            }
            newNode->setParent(curr);
            while (newNode->getParent() != nullptr && *newNode->getData() < *newNode->getParent()->getData()) {
                swap(newNode, newNode->getParent());
                newNode = newNode->getParent();
            }
        }
        numberOfElements++;
    }


    T *deleteMin() {


        if (root == nullptr) return nullptr;

        T* minData = root->getData();
        if (numberOfElements == 1) {
            delete root;
            root = nullptr;
            numberOfElements = 0;
            height = -1;
            return minData;
        }

        Node<T>* lastNode = getLastNode();
        root->setData(lastNode->getData());
        if (lastNode->getParent()->getLeftChild() == lastNode) {
            lastNode->getParent()->setLeftChild(nullptr);
        } else {
            lastNode->getParent()->setRightChild(nullptr);
        }
        delete lastNode;
        heapify(root);
        numberOfElements--;

        return minData;
    }

    Node<T>* getLastNode() {
        if (root == nullptr) return nullptr;

        Node<T>* temp = root;
        while (temp->getLeftChild() != nullptr || temp->getRightChild() != nullptr) {
            if (temp->getRightChild() != nullptr) {
                temp = temp->getRightChild();
            } else {
                temp = temp->getLeftChild();
            }
        }
        return temp;
    }
    void heapify(Node<T>* node) {
        bool go = true;
        while (go) {
            Node<T>* minNode = node;
            Node<T>* leftChild = node->getLeftChild();
            Node<T>* rightChild = node->getRightChild();

            if (leftChild != nullptr && *leftChild->getData() < *minNode->getData()) {
                minNode = leftChild;
            }

            if (rightChild != nullptr && *rightChild->getData() < *minNode->getData()) {
                minNode = rightChild;
            }

            if (minNode != node) {
                swap(node, minNode);
                node = minNode;
            } else {
                go=false;
            }
        }
    }

    void swap(Node<T>* node1, Node<T>* node2) {
        T* temp = node1->getData();
        node1->setData(node2->getData());
        node2->setData(temp);
    }

};



// global constant
const int VERTEXCOUNT = 5;

//global method
void runPrims(int G[VERTEXCOUNT][VERTEXCOUNT], BinaryHeap<Data>* binHeap)
{

    bool visited[VERTEXCOUNT]= {true};

    for(int i =0;i<VERTEXCOUNT-1;i++)
    {
        Data * newData = new Data(0, i, G[0][i]);
        if(G[0][i]>0&&i!=0)
        {
            binHeap->insertElement(newData);
        }
    }

    cout<<"Prims MST is Edge -> Cost"<<endl;

    while(binHeap->getNumberOfElements()>0)
    {
        Data * edge = binHeap->deleteMin();

        if(!visited[edge->getDestinationVertex()])
        {
            visited[edge->getDestinationVertex()] = true;
            cout<<edge->getSourceVertex()<<" - "<<edge->getDestinationVertex()<<" -> "<<edge->getEdgeCost()<<endl;

            for(int i = 0; i< VERTEXCOUNT;i++)
            {
                if(!visited[i]&&G[edge->getDestinationVertex()][i]>0)
                {
                    binHeap->insertElement(new Data(edge->getDestinationVertex(),i,G[edge->getDestinationVertex()][i]));
                }
            }

        }
        delete edge;
    }

}




int main() {
    int G[VERTEXCOUNT][VERTEXCOUNT] = {{0, 3, 65, 0, 0},
                  {3, 0, 85, 20, 45},
                  {65, 85, 0, 41, 77},
                  {0, 20, 41, 0, 51},
                  {0, 45, 77, 51, 0}};

    BinaryHeap<Data>* binaryHeap = new BinaryHeap<Data>();
    runPrims(G,binaryHeap);


    return 0;
}
