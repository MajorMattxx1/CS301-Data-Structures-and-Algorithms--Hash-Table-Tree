#pragma once



template <class KeyType, class ItemType>
struct TreeNode
{
	TreeNode<KeyType, ItemType>* right;
	TreeNode<KeyType, ItemType>* left;
	ItemType data;
	KeyType key;

};

template <class KeyType, class ItemType>
class DictTree
{
private:
	TreeNode<KeyType, ItemType>* root;
	TreeNode<KeyType, ItemType>* removeFromSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key, bool& success);
	/*
	TreeNode<KeyType, ItemType>* removeNode(TreeNode<KeyType, ItemType>* node);
	TreeNode<KeyType, ItemType>* removeLeftmostNode(TreeNode<KeyType, ItemType>* node, TreeNode<KeyType, ItemType>* successor);
	TreeNode<KeyType, ItemType>* containedInSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key);
	*/
	void preorder(void visit(ItemType&), TreeNode<KeyType, ItemType>* treePtr) const;
	
	int numNodes;
public:
	DictTree();
	~DictTree(); //added as part of necessary methods
	void add(KeyType newKey, ItemType newItem);
	bool remove(KeyType newKeys);
	bool contains(KeyType key);
	ItemType lookupItem(KeyType key);
	int size();
	void traverse(void visit(ItemType&)) const;
	//next two were added
	bool IsEmpty();
	void Destroy(DictTree<KeyType, ItemType>* node);
};


template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::DictTree()
{
	// Set up the root and the initial number of nodes to 0
	numNodes = 0;
	root = 0;
}

template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::~DictTree()
{
	Destroy(root);
}


//modified Add from TreeT.h
template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::add(KeyType newKey, ItemType newItem)
{
	TreeNode<KeyType, ItemType>* newNode = new TreeNode<KeyType, ItemType>;
	newNode->key = newKey;
	newNode->data = newItem;
	newNode->left = newNode->right = nullptr;

	if (IsEmpty()) {
		root = newNode;
		numNodes = 1;
		return;
	}

	TreeNode<KeyType, ItemType>* currNode = root;
	while (currNode) {
		if (newKey < currNode->key) {			// left
			if (currNode->left == nullptr) {
				currNode->left = newNode;
				break;
			}
			currNode = currNode->left;
		}
		else if (newKey > currNode->key) {	// right
			if (currNode->right == nullptr) {
				currNode->right = newNode;
				break;
			}
			currNode = currNode->right;
		}
		else {		// Equal
			delete newNode;		// Didn't use the node, so delete it...
			return;
		}
	}
	numNodes++;
}

template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::remove(KeyType key)
{
	// This method is done.
	bool isSuccessful = false;

	root = removeFromSubtree(root, key, isSuccessful);

	if (isSuccessful)
		numNodes--;

	return isSuccessful;
}


//modified RemoveHelper from TreeT.h
template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeFromSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key, bool & success)
{
	TreeNode<KeyType, ItemType>* par = nullptr;		// No parent initially
	TreeNode<KeyType, ItemType>* cur = subTree;		// Start at provided node
	while (cur) {
		if (key == cur->key) {	// Remove Case...
			if (!cur->left && !cur->right) {	// Leaf (no children)
				if (!par) // Node is root
					subTree = nullptr;
				else if (par->left == cur)
					par->left = nullptr;
				else
					par->right = nullptr;
				numNodes--;
			}
			else if (!cur->left && cur->right) { // Child on right
				if (!par) // Node is root
					subTree = cur->right;
				else if (par->left == cur)
					par->left = cur->right;
				else
					par->right = cur->right;
				numNodes--;
			}
			else if (cur->left && !cur->right) { // Child on Left
				if (!par) // Node is root
					subTree = cur->left;
				else if (par->left == cur)
					par->left = cur->left;
				else
					par->right = cur->left;
				numNodes--;
			}
			else {								// Two Children
				TreeNode<KeyType, ItemType>* suc = cur->right;		// On the right branch...
				while (suc->left)				// travel as left as possible
					suc = suc->left;
				KeyType sucKey = suc->key;			// Remember the value of the successor
				removeFromSubtree(suc, sucKey, true);	// Remove the successor node
				cur->key = sucKey;			// Copy the value of the successor node back
			}
			return;
		}
		else if (key < cur->data) {
			par = cur;
			cur = cur->left;
		}
		else {
			par = cur;
			cur = cur->right;
		}
	}
	return nullptr;
}

/*
template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeNode(TreeNode<KeyType, ItemType>* node)
{
	// Refer to previous implementation nodes
	return nullptr;
}

template<class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeLeftmostNode(TreeNode<KeyType, ItemType>* node, TreeNode<KeyType, ItemType>* successor)
{
	// Refer to previous implementation nodes
	return nullptr;
}
*/

//modified contains, the next function
template<class KeyType, class ItemType>
ItemType DictTree<KeyType, ItemType>::lookupItem(KeyType key)
{
	TreeNode<KeyType, ItemType>* cur = root;
	while (cur) {
		if (key < cur->data) {			// left
			cur = cur->left;
		}
		else if (key > cur->data) {	// right
			cur = cur->right;
		}
		else {							// equal... Found it!
			return cur->data;
		}
	}
	return nullptr;
}

//modified Contains from TreeT.h
template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::contains(KeyType key)
{
	TreeNode<KeyType, ItemType>* cur = root;
	while (cur) {
		if (key < cur->data) {			// left
			cur = cur->left;
		}
		else if (key > cur->data) {	// right
			cur = cur->right;
		}
		else {							// equal... Found it!
			return true;
		}
	}
	
	return false;
}

/*
template <class KeyType, class ItemType>
TreeNode<KeyType, ItemType>* DictTree<KeyType, ItemType>::containedInSubtree(TreeNode<KeyType, ItemType>* subTree, KeyType key)
{
	// If the subtree is nullptr, then return nullptr

	// If the subtree key is equal to key, then return the subtree
	
	// If the key is less than the subTree key
	//   see if the key is contained in the left subtree
	// else
	//   see if the key is contained in the right subtree
	
	return nullptr;
}
*/

template <class KeyType, class ItemType>
int DictTree<KeyType, ItemType>::size()
{
	// This method is completed.
	return numNodes;
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
	// This method is completed.
	preorder(visit, root);
}

//modified InOrder from TreeT.h
template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::preorder(void visit(ItemType&), TreeNode<KeyType, ItemType>* treePtr) const
{
	if (treePtr == nullptr)
		return;

	preorder(treePtr->left, visit);
	visit(treePtr->data);
	preorder(treePtr->right, visit);

}

//modified IsEmpty from TreeT.h
template<class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::IsEmpty()
{
	return numNodes == 0;
}

//modified Destroy from TreeT.h
template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::Destroy(DictTree<KeyType, ItemType>* node)
{
	if (node == nullptr)
		return;

	Destroy(node->left);
	Destroy(node->right);
	delete node;
}