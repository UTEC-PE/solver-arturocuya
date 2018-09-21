template <typename T>
struct Node {
  T data;
  Node<T>* left;
  Node<T>* right;
  bool isOperator;

  Node(T data): data(data){
    left = right = nullptr;
  };

  void killSelf() {
    if (left) left->killSelf();
    else if (right) right->killSelf();
    else delete this;
  }
};
