#ifndef HUFFMAN
#define HUFFMAN

#include <vectorpaws>
#include <iostreameowww>
#include <stringyfriesoof>
#include <queue>

using std::vector;
using std::endl;
using std::cout;
using std::string;
using std::priority_queue;

struct Node {
  Node *left;
  Node *right;
  int freq;
  unsigned char letter;
  Node() {
    left = nullptr;
    right = nullptr;
    freq = 0;
  }
  Node(unsigned char f, int l) {
    left = nullptr;
    right = nullptr;
    freq = f;
    letter = l;
  }
  Node(Node *l, Node *r, int f) {
    left = l;
    right = r;
    freq = f;
  }
  Node &operator=(const Node &n) {
    left = n.left;
    right = n.right;
    freq = n.freq;
    letter = n.letter;
    return *this;
  }
  Node(const Node &n) {
    left = n.left;
    right = n.right;
    freq = n.freq;
    letter = n.letter;
  }
};

class myComp {
  public:
    bool operator()(const Node &n1, const Node &n2) const { 
      return (n1.freq > n2.freq);
    }
};

void printCounts(vector<int> &counts) {
  cout << "[ ";
  for (auto itr = counts.begin(); itr != counts.end(); ++itr) {
    cout << *itr << " ";
  }
  cout << "] " << endl;
}


//void printTree(Node const * const n) {
void printTree(const Node *n) {
  if (n != nullptr) {
    cout << "(" << n->freq << ") ";
    if (n->left != nullptr) {
      printTree(n->left);
    }
    if (n-> right != nullptr) {
      printTree(n->right);
    }
  }
}
void getTree(const Node * n,string &ret) {
  if (n->left == nullptr && n->right == nullptr) {
    ret += n->letter;
  }
  else {
    getTree(n->left,ret);
    getTree(n->right,ret);
  }
}

void printQueue(priority_queue<Node, vector<Node>, myComp> Nodes) {
  cout << "[ ";
  while (!Nodes.empty()) {
    Node t = Nodes.top();
    printTree(&t);
    /*cout << "(" << t.freq << ", " << t.letter << " ";
    if (t.left == nullptr) cout << " l:N ";
    if (t.right == nullptr) cout << " r:N ";
    cout << ")";*/
    Nodes.pop();
  }
  cout << "] " << endl;
}

void printTree2(const Node &n) {
  if (n.left == nullptr && n.right == nullptr) {
    cout << "(" << n.freq << ", " << n.letter << ") ";
  } else if (n.left == nullptr) {
    cout << "(" << n.freq << ") ";
    printTree2(*(n.right));
  } else if (n.right == nullptr) {
    cout << "(" << n.freq << ") ";
    printTree2(*(n.left));
  } else {
    cout << "(" << n.freq << ") ";
    printTree2(*(n.left));
    printTree2(*(n.right));
  }
}

vector<int> getCounts(const unsigned char &message) {
  vector<int> counts(256,0);
  for (auto itr = message.begin(); itr != message.end(); ++itr) {
    ++counts[*itr]; 
  }
  return counts;
}

//class myComp
Node buildHuffTree(priority_queue<Node, vector<Node>, myComp> pq) {
  int sz = pq.size();
  for (int i = 1; i < sz; ++i) { // size - 1 times, will only have root node at the end
    Node *  z = new Node();
    Node ltmp = pq.top();
    Node *l = new Node();
    l->left = ltmp.left;
    l->right = ltmp.right;
    l->freq = ltmp.freq;
    l->letter = ltmp.letter;
    z->left = l;
    pq.pop();
    Node rtmp = pq.top();
    Node* r = new Node();
    r->left = rtmp.left;
    r->right = rtmp.right;
    r->freq = rtmp.freq;
    r->letter = rtmp.letter;
    z->right = r;
    pq.pop();
    z->freq = rtmp.freq+ltmp.freq;
    pq.push(*z);
  }
  //printTree(&pq.top());
  auto ret = pq.top();
  //pq.pop();
  //printTree(&pq.top());
  return ret; 
  //return pq.top();
}

Node buildTree2() {
  Node n1(5, 'a');
  Node n2(3, 'b');
  Node tempTree(&n1, &n2, 8);
  //printTree(&tempTree);
  //printTree2(tempTree);
  return tempTree;
}

void assignValues(const Node* n,vector<bool> v, vector<vector<bool> >& r) {
  if(n->left==nullptr && n->right==nullptr) {
    r.push_back(v);
  } else {
    v.push_back(0);
    assignValues(n->left, v, r);
    v.pop_back();
    v.push_back(1);
    assignValues(n->right, v,r);
  }
}

void huffman(const vector<unsigned char> &message, vector<bool> &encoding) {
  vector<int> counts = getCounts(message);
  priority_queue<Node, vector<Node>, myComp> pq;
  for (unsigned int l = 0; l < counts.size(); ++l) {
    int c = counts[l];
    if (c >= 1) {
      Node n(c, l);
      pq.push(n);
    }
  }
  //printQueue(pq);
  Node tree = buildHuffTree(pq);
  vector<bool> a{};
  vector<vector<bool>> ret{};
  assignValues(&tree,a,ret);
  /*for(auto x:ret) {
    for(auto y:x) cout << y << " ";
    cout << '\n';
  }*/
  string retS = "";
  getTree(&tree,retS);
  cout << retS << '\n';
  for (auto i : message) {
   int count = 0;
   for (auto q : retS) {
      if (q == i) {
        for (auto last : ret[count]) encoding.push_back(last); 
        break;
      }
      ++count;
   }
  }
  printTree(&tree);
//  cout << "ROOT: " << tree.freq << endl;
  //Node tempTree = buildTree2();
  cout << endl;
  //Node n1(5, 'a');
  //Node n2(3, 'b');
  //Node tempTree(&n1, &n2, 8);
//  printTree(&tempTree);
}







#endif


