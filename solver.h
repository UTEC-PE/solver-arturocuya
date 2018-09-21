#include <map>
#include <math.h>
#include "node.h"
using namespace std;
template <typename T>
class Solver
{
private:

  map <string, string> vars;

  map<char, int> precedenceOf = {
    {'+',1},
    {'-',2},
    {'*',3},
    {'/',4},
    {'^',5},
    {'#',9}
  };

  map<string, char> collapsePlusMinusConfiguration = {
    {"+-",'-'},
    {"-+",'-'},
    {"++",'+'},
    {"--",'+'}
  };

  bool checkOperator(string c)
  {
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^")
    {
      return true;
    }
    return false;
  }

public:
  Node<T>* root;
  Node<T>** current;

  Solver() {
    root = nullptr;
  }

  void prepareString(string &str)
  {
    int size = (str.size()/sizeof(str[0]));
    if (str[0] == '(' && str[size-1] == ')')
    {
      str = str.substr(1,size-2);
      size -= 2;
    }
    if (str[0] == '(' && str[size-1] == ')') prepareString(str);
  }

  int findLeastPrecedent(string str)
  {
    int parenthesisCounter = 0;
    int indexOfMinPrecedence = -1;
    char opOfMinPrecedence = '#';

    for(std::string::size_type i = 0; i < str.size(); ++i)
    {
      char &currentChar = str[i];
      if (currentChar == '(') parenthesisCounter++;
      if (currentChar == ')') parenthesisCounter--;
      if (checkOperator(string() + currentChar) && parenthesisCounter == 0)
      {
        if (precedenceOf[currentChar] < precedenceOf[opOfMinPrecedence])
        {
          opOfMinPrecedence = currentChar;
          indexOfMinPrecedence = i;
        }
      }
    }
    return indexOfMinPrecedence;
  }

  void buildTree(string str)
  {
    prepareString(str);
    // Least precedent index
    int lpi = findLeastPrecedent(str);

    if (lpi != -1)
    {
      Node<T>* newNode = new Node<T>(string() + str[lpi]);

      // cout << "NewNode: " << newNode->data << endl;

      if (!root)
      {
        root = newNode;
        current = &root;
      }

      Node<T>* nodeLeft = new Node<T>(string() + str.substr(0,lpi));
      Node<T>* nodeRight = new Node<T>(string() + str.substr(lpi+1,str.size()-lpi+1));

      newNode->left = nodeLeft;
      newNode->right = nodeRight;

      // cout << "NewNode left: " << newNode->left->data << endl;
      // cout << "NewNode right: " << newNode->right->data << endl;
      //
      // cout << "changing " << (*current)->data << " ";
      *current = newNode;
      // cout << "to " << (*current)->data << endl;

      current = &newNode->left;
      buildTree(nodeLeft->data);

      current = &newNode->right;
      buildTree(nodeRight->data);
    }
    else
    {
      prepareString((*current)->data);
      // cout << "found an end at: " << (*current)->data << endl;
    }
  }

  bool checkIfLetter(string str)
  {
    if (str.size() == 1)
    {
      char &c = str[0];
      if (c >= 'a' && c <= 'z') return true;
    }
    return false;
  }

  string operate(string left, string right, string op)
  {
    if (checkIfLetter(left))
    {
      if (vars[left] == "")
      {
        cout << "Enter a value for " << left << ": ";
        string newValue = "";
        cin >> newValue;
        cout << endl;
        vars[left] = string() + newValue;
      }
      left = vars[left];
    }

    if (checkIfLetter(right))
    {
      if (vars[right] == "")
      {
        cout << "Enter a value for " << right << ": ";
        string newValue = "";
        cin >> newValue;
        cout << endl;
        vars[right] = string() + newValue;
      }
      right = vars[right];
    }

    float x = stof(left);
    float y = stof(right);

    if (op == "+") return to_string(x+y);
    if (op == "-") return to_string(x-y);
    if (op == "*") return to_string(x*y);
    if (op == "/") return to_string(x/y);
    if (op == "^") return to_string(pow(x,y));
    else throw runtime_error("Invalid operand");
  }

  void collapseTree(Node<T>* start) // 0
  {
    if (checkOperator(string() + start->data))
    {
      collapseTree(start->left); // 1
      collapseTree(start->right); // 2
      start->data = operate(start->left->data, start->right->data, start->data); // 3
    }
  }

  void collapsePlusMinus(string &str)
  {
    int i = 0;
    while(str[i])
    {
      char &current = str[i];
      if ( (i+1) != str.size() )
      {
        char &next = str[i+1];
        if(checkOperator(string() + current) && checkOperator(string() + next))
        {
            if(
                (current == next && (precedenceOf[current] + precedenceOf[next] == 2 || precedenceOf[current] + precedenceOf[next] == 4)) ||
                (current != next && (precedenceOf[current] + precedenceOf[next] == 3))
              )
            {
              string toCollapse = string() + current + next;
              str = str.substr(0,i) + collapsePlusMinusConfiguration[toCollapse] + str.substr(i+2, str.size()-(i+2));
              i--;
            }
        }
      }
      i++;
    }
  }

  string solve(string str)
  {
    cout << "Solving: " << str << endl;
    collapsePlusMinus(str);
    buildTree(str);
    collapseTree(root);
    return root->data;
  }
};
