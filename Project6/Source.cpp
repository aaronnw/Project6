#include <iostream>
using namespace std;

//Performs a sequential search to return all array indices that will result in the given value
int* getIndicesWithValue(int* inputArray, int searchValue, int arraySize) {
	int* solutionIndices = new int[arraySize];
	int i = 0;
	int j = 0;
	while (i < arraySize) {
		if (inputArray[i] == searchValue) {
			solutionIndices[j] = i;
			j++;
		}
		i++;
	}
	return solutionIndices;
}

template <class DT>
class ParentBinaryTree {
	template<class T>
	friend ostream& operator<< (ostream& s, ParentBinaryTree<T>& pbt); //Overloaded ostream operator
protected:


	int numNodes; //Number of nodes in the tree
	bool firstRoot = true;
public:
	int* ChildPositionArray; //Array indexed by each position with a value of 0 for left nodes and 1 for right nodes
	DT* ParentArray; //Array indexed by each position with a value of each position's parent

	ParentBinaryTree(); //Default constructor
	ParentBinaryTree(int size); //Initializer
	~ParentBinaryTree(); //Destructor
	ParentBinaryTree(ParentBinaryTree& pbt); //Copy constructor
	void operator=(ParentBinaryTree<DT>& pbt); //Overloaded assignment operator
	void insert(DT & root, DT* childArray, int numChildren); //Inserts the values to create the tree
	int getSize(); //Returns the number of nodes in the tree
	int getHeight(); //Returns the height of the tree
	int* getChildren(int parent);
	bool isLeaf(int x);  //Checks if the position given is a leaf node
	void preorderTraversal();
	void preorderTraversal(int x);
	void levelOrderTraversal();
};

///Overloaded ostream operator
template<class T>
ostream& operator<< (ostream& s, ParentBinaryTree<T>& tree) {
	//Print out the preorder traversal
	tree.preorderTraversal();
	s << endl;
	return s;
}

///Default Constructor
template<class DT>
ParentBinaryTree<DT>::ParentBinaryTree() {
	DT* ParentArray = NULL;
	DT* ChildPositionArray = NULL;
	numNodes = 0;
}
///Initializer
template<class DT>
ParentBinaryTree<DT>::ParentBinaryTree(int size) {
	ParentArray = new DT[size];
	ChildPositionArray = new int[size];
	numNodes = size;
}
///Destructor
template<class DT>
ParentBinaryTree<DT>::~ParentBinaryTree() {

}
///Copy constructor
template<class DT>
ParentBinaryTree<DT>::ParentBinaryTree(ParentBinaryTree<DT> & pbt) {
	numNodes = pbt.numNodes;
	ParentArray = new DT[numNodes];
	ChildPositionArray = new int[numNodes];
	//Copy the parent array and the child position array
	for (int i = 0; i < pbt.getSize(); i++) {
		ParentArray[i] = pbt.ParentArray[i];
		ChildPositionArray[i] = pbt.ChildPositionArray[i];
	}

}
///Overloaded assignment operator
template<class DT>
void ParentBinaryTree<DT>::operator=(ParentBinaryTree<DT>& pbt) {
	numNodes = pbt.numNodes;
	ParentArray = new DT[numNodes];
	ChildPositionArray = new int[numNodes];
	//Copy the parent array
	for (int i = 0; i < pbt.getSize(); i++) {
		ParentArray[i] = pbt.ParentArray[i];
		ChildPositionArray[i] = pbt.ChildPositionArray[i];
	}
}
//TODO
template<class DT>
void ParentBinaryTree<DT>::insert(DT & root, DT* childArray, int numChildren) {
	//Only for the highest level node
	if (firstRoot) {
		ParentArray[root] = -1;
		ChildPositionArray[root] = -1;
		firstRoot = false;
	}
	for (int i = 0; i < numChildren; i++) {
		ParentArray[childArray[i]] = root;
		ChildPositionArray[childArray[i]] = i;
	};
}
///Returns number of nodes in the tree
template<class DT>
int ParentBinaryTree<DT>::getSize() {
	return numNodes;
}
//Returns the height of the tree
template<class DT>
int ParentBinaryTree<DT>::getHeight() {
	int maxHeight = 1;
	int height = 1;
	//Loop through all the nodes
	for (int i = 0; i < numNodes; i++) {
		//Only look at leaf nodes to find the max height
		if (isLeaf(i)) {
			int k = i;
			//Bubble up to the parent, counting levels
			while (ParentArray[k] != -1) {
				k = ParentArray[k];
				height++;
			}
			//Keep only the greatest height found
			if (height > maxHeight) {
				maxHeight = height;
			}
			height = 0;
		}
	}
	return maxHeight;
}
//TODO
template<class DT>
int* ParentBinaryTree<DT>::getChildren(int parent) {
	//Make an array in case all of the child nodes are children
	int* children = new int[numNodes - 1];
	int j = 0;
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == parent) {
			children[j] = i;
			j++;
			cout << i;
		}
	}
	int* trimmedChildList = new int[j];
	for (int k = 0; k < j; k++) {
		trimmedChildList[k] = children[k];
	}
	delete children;
	return trimmedChildList;
}
///Returns a boolean true if the position is a leaf node
template<class DT>
bool ParentBinaryTree<DT>::isLeaf(int x) {
	//Check if the position has children
	if ((getLeft(x) == -1) && (getRight(x) == -1)) {
		return true;
	}
	else {
		return false;
	}
}
///Prints the node values in preorder format
template<class DT>
void ParentBinaryTree<DT>::preorderTraversal(int x) {
	//Root, left, right
	cout << x;
	if (getLeft(x) != -1) {
		preorderTraversal(getLeft(x));
	}
	if (getRight(x) != -1) {
		preorderTraversal(getRight(x));
	}
}
///Finds the root node then prints the node values in preorder format
template<class DT>
void ParentBinaryTree<DT>::preorderTraversal() {
	//Root, left, right
	//Find root node
	int root = 0;
	while (ParentArray[root] != -1 && root < numNodes) {
		root++;
	}
	//Start the traversal at the root node
	preorderTraversal(root);
}
template<class DT>
void ParentBinaryTree<DT>::levelOrderTraversal() {};

int main() {
	int numNodes = 0;
	int root;
	int numChildren = 0;
	int i;
	int nextChild;
	//Keeps track of number of lines to avoid crash if too many are read
	int numLines = 0;
	//Reads the number of nodes
	cin >> numNodes;
	cout << numNodes << endl;
	//Initializer
	ParentBinaryTree<int>* tree = new ParentBinaryTree<int>(numNodes);
	//Reads the rest of the file
	while (!cin.eof()) {
		//For each line add the info to the tree
		cin >> root;
		cin >> numChildren;
		int* children = new int[numChildren];
		i = 0;
		while (i < numChildren) {
			cin >> nextChild;
			children[i] = nextChild;
			i++;
		}
		numLines++;
		if (numLines <= numNodes) {
			tree->insert(root, children, numChildren);
		}
		else {
			cout << "Wrong number of nodes given. Using given number. Some input may be ignored. " << endl;
			break;
		}
	}
	for (int z = 0; z < numNodes; z++) {
		cout << z << " " << tree->ParentArray[z] << endl;
	}
	return 0;
}