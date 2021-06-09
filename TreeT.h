#pragma once

template <class T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
};

template <class T>
class TreeT
{
public:
	TreeT();
	~TreeT();

	void Add(T elem);
	void Remove(T elem);
	bool Contains(T elem);
	bool IsEmpty();

	int Size();
	void Traverse(void visit(T& elem));

private:
	Node<T>* root;
	int len;
	void Destroy(Node<T>* node);
	void RemoveHelper(Node<T>* node, T elem);
	void InOrder(Node<T>* node, void visit(T& elem));
};

template<class T>
TreeT<T>::TreeT()
{
	len = 0;
	root = 0;
}

template<class T>
TreeT<T>::~TreeT()
{
	Destroy(root);
}

template<class T>
void TreeT<T>::Add(T elem)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = elem;
	newNode->left = newNode->right = nullptr;

	if (IsEmpty()) {
		root = newNode;
		len = 1;
		return;
	}

	Node<T>* cur = root;
	while (cur) {
		if (elem < cur->data) {			// left
			if (cur->left == nullptr) {
				cur->left = newNode;
				break;
			}
			cur = cur->left;
		}
		else if (elem > cur->data) {	// right
			if (cur->right == nullptr) {
				cur->right = newNode;
				break;
			}
			cur = cur->right;
		}
		else {		// Equal
			delete newNode;		// Didn't use the node, so delete it...
			return;
		}
	}
	len++;
}

template<class T>
void TreeT<T>::Remove(T elem)
{
	RemoveHelper(root, elem);
}

template<class T>
bool TreeT<T>::Contains(T elem)
{
	Node<T>* cur = root;
	while (cur) {
		if (elem < cur->data) {			// left
			cur = cur->left;
		}
		else if (elem > cur->data) {	// right
			cur = cur->right;
		}
		else {							// equal... Found it!
			return true;
		}
	}

	// Only way to get here is cur is nullptr, 
	// which mean we hit a dead end

	return false;
}

template<class T>
bool TreeT<T>::IsEmpty()
{
	return len == 0;
}

template<class T>
int TreeT<T>::Size()
{
	return len;
}

template<class T>
void TreeT<T>::Traverse(void visit(T &elem))
{
	InOrder(root, visit);
}

template<class T>
void TreeT<T>::Destroy(Node<T>* node)
{
	if (node == nullptr)
		return;

	Destroy(node->left);
	Destroy(node->right);
	delete node;
}

template<class T>
void TreeT<T>::RemoveHelper(Node<T>* node, T elem)
{
	Node<T>* par = nullptr;		// No parent initially
	Node<T>* cur = node;		// Start at provided node
	while (cur) {
		if (elem == cur->data) {	// Remove Case...
			if (!cur->left && !cur->right) {	// Leaf (no children)
				if (!par) // Node is root
					node = nullptr;
				else if (par->left == cur)
					par->left = nullptr;
				else
					par->right = nullptr;
				len--;
			}
			else if (!cur->left && cur->right) { // Child on right
				if (!par) // Node is root
					node = cur->right;
				else if (par->left == cur)
					par->left = cur->right;
				else
					par->right = cur->right;
				len--;
			}
			else if (cur->left && !cur->right) { // Child on Left
				if (!par) // Node is root
					node = cur->left;
				else if (par->left == cur)
					par->left = cur->left;
				else
					par->right = cur->left;
				len--;
			}
			else {								// Two Children
				Node<T>* suc = cur->right;		// On the right branch...
				while (suc->left)				// travel as left as possible
					suc = suc->left;
				T sucData = suc->data;			// Remember the value of the successor
				RemoveHelper(node, sucData);	// Remove the successor node
				cur->data = sucData;			// Copy the value of the successor node back
			}
			return;
		}
		else if (elem < cur->data) {
			par = cur;
			cur = cur->left;
		}
		else {
			par = cur;
			cur = cur->right;
		}
	}
}

template<class T>
void TreeT<T>::InOrder(Node<T>* node, void visit(T &elem))
{
	if (node == nullptr)
		return;

	InOrder(node->left, visit);
	visit(node->data);
	InOrder(node->right, visit);
}