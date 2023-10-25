#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList{
public: 
  struct Node{
    T data;
    Node *next;
    Node *prev;
  };

private:
  int cap;
  Node *head;
  Node *tail;

public:  
  LinkedList(){ // constructor
      cap = 0;
      head = nullptr;
      tail = nullptr;
  }

  LinkedList(const LinkedList<T>& list){ //copy constructor
      cap = 0;
      head = nullptr;
      tail = nullptr;        
      Node *currentNode = list.head; // Start at the head of the source list

      while (currentNode != nullptr) {
          AddTail(currentNode -> data); // Copy each element from the source list
          currentNode = currentNode -> next; // Move to the next node in the source list
      }
  }

  ~LinkedList(){ //destructor
  //will set the temp variable as the current head node of the list
  //and traverse the list deleting them one by one
        while (head != nullptr) { 
          Node *temp = head;
          head = head -> next;
          temp->next = nullptr; 
          temp->prev = nullptr; 
          
          delete temp;
      }
  }

  const T& operator[](unsigned int index) const { //overload subscript operator
      Node *indexNode = head;
      if (index >= cap) {
          throw out_of_range("Index out of range");
      }

      for (int i = 0; i < index; i++) {
          indexNode = indexNode -> next;
      }
      
      return indexNode -> data;
  }

  T& operator[](unsigned int index) { 
      if (index >= cap) {
          throw out_of_range("Index out of range");
      }

      Node *indexNode = head;
      for (int i = 0; i < index; i++) {
          indexNode = indexNode -> next;
      }

      return indexNode -> data;
  }

  LinkedList<T>& operator=(const LinkedList<T>& list){ //copy assignment operator
    if (this == &list) {
      return *this;
    }
    // needs to delete the previous nodes of the first list.
    while (head != nullptr) { 
      Node *temp = head;
      head = head->next;
      temp->next = nullptr;
      temp->prev = nullptr;
      delete temp;
    }
    
    // Initialize cap, head, and tail for the current list
    cap = 0;
    head = nullptr;
    tail = nullptr;

      Node* copyNode = list.head; // this will be used to deep copy the list to this 
      while (copyNode != nullptr) {
        AddTail(copyNode -> data); // Add each element from list to the current list
        copyNode = copyNode -> next; // Move to the next node in list
      }

      return *this;
  }

  bool operator==(const LinkedList<T>& rhs) const { //equality operator
    Node *listA = head;
    Node *listB = rhs.head;

    if (cap != rhs.cap) { //if there capacity is not the same return false
      return false;
    }

    for (unsigned int i = 0; i < cap; i++) { // this will go through each of the nodes for both A & B
      if (listA -> data != listB -> data) { // the data is not the same in the node, return false
        return false;
      }
      // moves the pointers to the next node 
      listA = listA -> next; 
      listB = listB -> next;
    }
    // if all goes well
    return true;
  }

  void AddHead(const T& data) {
      Node *newNode = new Node; //initialize the new node
      newNode -> data = data; //sets the data points of new node
      newNode -> next = nullptr;
      newNode -> prev = nullptr;

      if (head != nullptr) { // for when the list is not empty
          head -> prev = newNode;
          newNode -> next = head;
          head = newNode;

          if (cap == 1) { // for when the list only has 1 node in it
          // meaning that the tails prev will have to point to the new node
              tail -> prev = newNode;
          }
      }

      else { // when the new head is the first node of the list
          head = newNode;
          tail = newNode;
          head -> next = nullptr;
          head -> prev = nullptr;
      }

      cap++;
  }

  void AddTail(const T& data){ // almost copy of AddHead but with variable changes
      Node *newNode = new Node; //initialize the new node
      newNode -> data = data; //sets the data points of new node
      newNode -> next = nullptr;
      newNode -> prev = nullptr;

      if (tail != nullptr) { // for when the list is not empty
          tail -> next = newNode;
          newNode -> prev = tail;
          tail = newNode;

          if (cap == 1) { // for when the list only has 1 node in it
          // meaning that the heads next will have to point to the new node
              head -> next = newNode;
          }
      }

      else { // when the new tail is the first node of the list
          head = newNode;
          tail = newNode;
          head -> next = nullptr;
          head -> prev = nullptr;
      }

      cap++;
  }

  // use the AddHead function to add the multiple nodes to head position
  void AddNodesHead(const T* data, unsigned int count){ 
      for (int i = (count - 1); i >= 0; i--) { // reverse order of new data nodes to print correctly 
          AddHead(data[i]);
          
      }
      cap += count;
  }

  void AddNodesTail(const T* data, unsigned int count){
      for (int i = 0; i < count; i++) {
          AddTail(data[i]);
      }
      cap += count;
  }

  void InsertAfter(Node *node, const T& data){ // use same method as the find() but then include an insert to the next pointer of the data point
    Node *newNode = new Node; // creates new node
    newNode -> data = data; // sets selected datapoint to new node
    newNode -> prev = node; // sets the previous and next pointers of the new node
    newNode -> next = node -> next;
    node -> next = newNode; // sets the target nodes next pointer to the new node

    cap++;
  }

  void InsertBefore(Node *node, const T& data){ 
    Node *newNode = new Node;
    newNode->data = data;
    newNode->prev = node->prev;
    newNode->next = node;

    if (node->prev != nullptr) { // written this way or will generate an endless loop of setting the next and prev
      node -> prev -> next = newNode;
    } 
    else {
      if (node == head) {  
        head = newNode;
      }
    }
    // nodes prev must be set AFTER all of the edge cases or will lead to memory leaks
    node->prev = newNode; 

    cap++;
  }

  void InsertAt(const T& data, unsigned int index){
    if (index > cap) {// edge case for when index is out of range of the cap length
      throw out_of_range("index out of range");
    }
    else if (index == 0) {// edge case for when the index is 0 == adding a head node
      AddHead(data);
    }
    else if (index == cap) { // edge case for when the index is the same as the cap amount
      AddTail(data);
    }
    else {
      Node *newNode = new Node; // generates new node
      newNode -> data = data; // places desired data into new node
      Node *tempNode = GetNode(index - 1); // -1 because this will act as a stepping stone to help assign the correct data points to the new node 
      newNode -> prev = tempNode;
      newNode -> next = tempNode -> next;
      tempNode -> next = newNode;

      cap++;
    }
  }


  unsigned int NodeCount() const{
      return cap;
  }

  void FindAll(vector<Node*>& outData, const T& value) const {
      Node *targetNode = head; // generates temp node to traverse list
      for (int i = 0; i < cap; i++) {
          if (targetNode -> data == value) { // if it finds the value while traversing
              outData.push_back(targetNode); // push node to the outdata vector
          }
          targetNode = targetNode -> next; // move to next node;
      }
  }

  const Node* Find(const T& data) const {
      Node *targetNode = head;
      while (targetNode != nullptr) {
          if (targetNode->data == data) {
              return targetNode;
          }
          else {
              return nullptr; // Return nullptr if not found
          }

          targetNode = targetNode->next;
      }
  }

  Node* Find(const T& data) {
      Node *targetNode = head;
      while (targetNode != nullptr) {
          if (targetNode->data == data) {
              return targetNode;
          }            
        
        targetNode = targetNode->next;

      }
        
      return nullptr; // Return nullptr if not found
  }

  const Node* GetNode(unsigned int index) const {
      Node* targetNode = head;

      if (index < cap) {
          int position = 0;

          while (position != index) {
              targetNode = targetNode->next;
              position++;
          }
      } else {
          throw out_of_range("Index out of range");
      }
      return targetNode;
  }

  Node* GetNode(unsigned int index) {
      Node* targetNode = head;
      if (index < cap) {
          int position = 0;

          while (position != index) {
              targetNode = targetNode->next;
              position++;
          }
      } else {
          throw out_of_range("Index out of range");
      }
      return targetNode;
  }

  const Node* Head() const{
      return head;
  }

  Node* Head(){
      return head;
  }

  const Node* Tail() const{
      return tail;
  }

  Node* Tail(){
      return tail;
  }

  bool RemoveHead(){
    if (cap == 0) {// edge case for empty list
      return false;
    }
    else if (cap == 1) { // edge case for one item list
      delete head;
      head = nullptr;
      tail = nullptr;
      cap--;

      return true;
    }
    else {// for noraml removal of head
      Node *newHead = head -> next; // node label for the second list node 
      newHead -> prev = nullptr; // as new head needs no prev
      head -> prev = nullptr; // start erasing the 
      head -> next = nullptr;

      delete head;
      head = newHead; // sets the next node over to be the new head
      cap--;
    }

    return true;
  }

  bool RemoveTail(){
    if (cap == 0) {// edge case for empty list
      return false;
    }
    else if (cap == 1) { // edge case for one item list
      delete tail;
      head = nullptr;
      tail = nullptr;
      cap--;

      return true;
    }
    else {// for noraml removal of tail
      Node *newTail = tail -> prev; // node label for the second to last node 
      newTail -> next = nullptr; // as new head needs no prev
      tail -> prev = nullptr; // start erasing the 

      delete tail;
      tail = newTail; // sets the next node over to be the new head
      cap--;
    }
  }

  unsigned int Remove(const T& data){
    Node *tempNode = head; // used to revalue the next and prev pointers when deleting the targetNode
    Node *targetNode = head; // set to beginning of the list
    unsigned int instances = 0;
    
    for (int i = 0; i < cap; i++) { // traverses through the list
      if (targetNode -> data == data){ // when finding those with the same data
        tempNode -> prev -> next = tempNode -> next; // this will set the previous nodes next pointer to what is being pointed at by the temp node
        tempNode -> next -> prev = tempNode -> prev;// will change the next nodes previous pointer to the node before the tempNode
        tempNode = tempNode -> next;
      
      delete targetNode;
      targetNode = tempNode;
      instances++;
      }
      else {
        tempNode = tempNode -> next; // moves on to the next node in list
        targetNode = targetNode -> next;
      }
    }

    cap -= instances;
    return instances;
  }

  bool RemoveAt(unsigned int index){
    if (index > cap) { //edge case for unusable index value
      return false;
    }

    else {
      Node *tempNode = GetNode(index); 
      tempNode -> prev -> next = tempNode -> next; // this will set the previous nodes next pointer to what is being pointed at by the temp node
      tempNode -> next -> prev = tempNode -> prev;// will change the next nodes previous pointer to the node before the tempNode
      delete tempNode;
      cap--;
      
      return true;
    }
  }

  void Clear(){
    Node *currentNode = head; // sets this node to equal the tempNode after deleting it

    while (currentNode != nullptr) {
      Node *tempNode = currentNode -> next; // set to the next node for later use
      currentNode -> next = nullptr;
      currentNode -> prev = nullptr;
  
      delete currentNode;

      currentNode = tempNode; // sets current node to be the next node in the list
      cap--;
    }

    head = nullptr;
    tail = nullptr;
  }

  void PrintForward() const{
      Node *placeHolder = head;
      while (placeHolder != nullptr) {
          cout << placeHolder -> data << endl;
          placeHolder = placeHolder -> next;
      }
  }

  void PrintReverse() const{
      Node *placeHolder = tail;
      while (placeHolder != nullptr) {
          cout << placeHolder -> data << endl; 
          placeHolder = placeHolder -> prev;
      }
  }

  void PrintForwardRecursive(const Node* node) const{
    if (node == nullptr) {
      return;
    }
    cout << node -> data << endl;
    PrintForwardRecursive(node -> next);

  }

  void PrintReverseRecursive(const Node* node) const{
    if (node == nullptr) {
      return;
    }
    cout << node -> data << endl;
    PrintReverseRecursive(node -> prev);
  }

};


