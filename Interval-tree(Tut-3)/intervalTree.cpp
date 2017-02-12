#include <bits/stdc++.h>
using namespace std;

struct Interval{
	int low, high;
};

struct ITNode{
	Interval *i;
	int max;
	ITNode *left, *right, *parent;
};

Interval *newInterval(int low, int high){
	Interval *i = new Interval();
	i->low = low;
	i->high = high;
	return i;
}

class intervalTree{
private :
	ITNode *root;

public:
	intervalTree(Interval *i){
		root = new ITNode();
		root->i = i;
		root->max = max(i->low, i->high);
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	
	ITNode* newNode(Interval *i){
		ITNode *node = new ITNode();
		node->i = i;
		node->max = max(i->low, i->high);
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	void insert(Interval *i){
		ITNode *currentNode = newNode(i);
		insert(root, currentNode);
	}

	void insert(ITNode *root, ITNode *currentNode){
		// If tree is empty
		if (!this->root){
			this->root = currentNode;
			this->root->parent = NULL;
		}else{
			root->max = max(root->max, currentNode->max);     //update max since it is going to be changed after insertion of node
			// Case when we go to left for insertion
			if (currentNode->i->low < root->i->low){
				// if left node is NULL, no need to recurse just insert it
				if (!root->left){
					root->left = currentNode;
					currentNode->parent = root;
				}else{
					insert(root->left, currentNode);
				}
			}else{// Case when we go to right for insertion
				// if right node is NULL, no need to recurse just insert it
				if(!root->right){
					root->right = currentNode;
					currentNode->parent = root;
				}else{
					insert(root->right, currentNode);
				}
			}
		}
	}

	bool doMatch(Interval *a, Interval *b){
		if (a->low == b->low && a->high == b->high)
			return true;
		return false;
	}

	void deleteNode(Interval *i){
		deleteNode(root, i);
	}

	bool isLeftChild(ITNode *t){
		if (t->parent->left == t)
			return true;
		return false;
	}

	void deleteNode(ITNode *root, Interval *i){
		if(!root){
			cout<<"No such interval exists"<<endl;
			return;
		}

		if (doMatch(root->i, i)){
			//ITNode *currentParent = root->parent;
			if (root->right){//if match is FOUND and we can replace some value from right subtree
				ITNode *toBeReplacedWith = root;
				ITNode *temp = root->right;
				while(temp){
					toBeReplacedWith = temp;
					temp = temp->left;
				}
				//delete toBeReplacedWith
				if (isLeftChild(toBeReplacedWith)){
					toBeReplacedWith->parent->left = toBeReplacedWith->right;
					if (toBeReplacedWith->right) toBeReplacedWith->right->parent = toBeReplacedWith->parent;
				}else{
					toBeReplacedWith->parent->right = toBeReplacedWith->right;
					if (toBeReplacedWith->right) toBeReplacedWith->right->parent = toBeReplacedWith->parent;
				} 
				// updating max till root from toBeReplacedWith
				temp = toBeReplacedWith->parent;
				while(temp!=root){
					if (temp->left) temp->max = root->left->max;
					if (temp->right) temp->max = max(root->max, root->right->max);
					temp = temp->parent;
				}
				//replacing MATCh with toBeReplacedWith
				root->i = toBeReplacedWith->i;
				root->max = toBeReplacedWith->max;
				if (root->left) root->max = max(root->max, root->left->max);
				if (root->right) root->max = max(root->max, root->right->max);
			}else{//if right subtree is empty
				if (isLeftChild(root)){
					root->parent->left = root->left;
					if (root->left) root->left->parent = root->parent;
				}else{
					root->parent->right = root->left;
					if (root->left) root->left->parent = root->parent;
				} 
			}

			//Updating max till rootOfTree starting from the MATCH's parent 
			ITNode *temp = root->parent;
			while(temp != NULL){
				temp->max = temp->i->high;
				if (temp->left) temp->max = max(temp->left->max, temp->max);
				if (temp->right) temp->max = max(temp->right->max, temp->max);
				temp = temp->parent;
			}

		}else{
			if (i->low < root->i->low)
				deleteNode(root->left, i);
			else deleteNode(root->right, i);
		}

	}

	bool doOverlap(Interval *a, Interval *b){
		if (a->high < b->low || a->low > b->high)
			return false;
		return true;
	}

	Interval* searchOverlap(Interval *i){
		return searchOverlap(root, i);
	}

	Interval* searchOverlap(ITNode *root, Interval *i){
		if (!root)
			return NULL;

		if (doOverlap(root->i, i))
			return root->i;

		if (root->left && i->low <= root->left->max)
			return searchOverlap(root->left, i);
		else return searchOverlap(root->right, i);
	}

	void traverseTree(){
		traverseTree(root);
	}

	void traverseTree(ITNode *root){
		if (!root)
			return;
		traverseTree(root->left);
		cout<<"("<<root->i->low<<","<<root->i->high<<",["<<root->max<<"]"<<")"<<"  ";
		traverseTree(root->right);
	}
	
};

int main(){
	intervalTree IT(newInterval(15,20));
	Interval ints[] = {{15,20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {16, 40}
    };
    int n = sizeof(ints)/sizeof(ints[0]);
    
    for (int i = 0; i < n; i++)
		IT.insert(newInterval(ints[i].low, ints[i].high));
	//test case 1
	Interval *match = IT.searchOverlap(newInterval(14, 19));
	if(match)
		cout<<"Overlaps with ("<<match->low<<","<<match->high<<")"<<endl;
	else cout<<"No Overlap";
	//test case 2
	match = IT.searchOverlap(newInterval(21, 23));
	if(match)
		cout<<"Overlaps with ("<<match->low<<","<<match->high<<")"<<endl;
	else cout<<"No Overlap";	

	return 0;
}
