#pragma once

#include "treenode.hpp"
#include <iostream>
#include <algorithm>

template <typename T>
class BSTree
{
public:

	BSTree();
	~BSTree();

	void insert(const T& value);

	void remove(const T& elem);

	//Accessors
	bool empty() const;

	size_t size() const;

	size_t height() const;

	bool find(const T& elem) const;

	void inorder() const;

	void preorder() const;

	void postorder() const;

	//service methods
	void inorder(TreeNode<T>* node) const;

	void preorder(TreeNode<T>* node) const;

	void postorder(TreeNode<T>* node) const;

private:

	static TreeNode<T>* insert(TreeNode<T>* node, const T& value);

	static bool find(TreeNode<T>* node, const T& elem);

	static TreeNode<T>* findMin(TreeNode<T>* node);

	static TreeNode<T>* remove(TreeNode<T>* node, const T& elem);

	static void clear(TreeNode<T>* node);

	static size_t height(TreeNode<T>* node);


	TreeNode<T>* m_root;
	size_t m_size;
};

template <typename T>
BSTree<T>::BSTree() :m_root(nullptr), m_size(0u)
{

}

template <typename T>
BSTree<T>::~BSTree()
{
	clear(m_root);
}

template <typename T>
bool BSTree<T>::empty() const
{
	return (m_size == 0);
}

template <typename T>
size_t BSTree<T>::size() const
{
	return m_size;
}

template <typename T>
size_t BSTree<T>::height() const
{
	return height(m_root);
}

template <typename T>
bool BSTree<T>::find(const T& elem) const
{
	return find(m_root, elem);
}


template <typename T>
void BSTree<T>::insert(const T& value)
{
	m_root = insert(m_root, value);
	++m_size;
}

template <typename T>
void BSTree<T>::remove(const T& elem)
{
	if (empty())
	{
		return;
	}
	m_root = remove(m_root, elem);
	--m_size;
}

template <typename T>
void BSTree<T>::inorder() const
{
	if (m_root == nullptr)
	{
		return;
	}

	inorder(m_root);

	std::cout << std::endl;
}

template <typename T>
void BSTree<T>::preorder() const
{
	if (m_root == nullptr)
	{
		return;
	}

	preorder(m_root);

	std::cout << std::endl;
}

template <typename T>
void BSTree<T>::postorder() const
{
	if (m_root == nullptr)
	{
		return;
	}

	postorder(m_root);

	std::cout << std::endl;
}

template <typename T>
TreeNode<T>* BSTree<T>::insert(TreeNode<T>* node, const T& value)
{
	if (node == nullptr)
	{
		return new TreeNode<T>(value);
	}

	if (value < node->key)
	{
		node->left = insert(node->left, value);
	}

	else
	{
		node->right = insert(node->right, value);
	}

	return node;
}

template <typename T>
TreeNode<T>* BSTree<T>::remove(TreeNode<T>* node, const T& elem)
{
	if (elem < node->key)
	{
		node->left = remove(node->left, elem);
	}

	else if (elem > node->key)
	{
		node->right = remove(node->right, elem);
	}

	else
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			delete node;
			node = nullptr;
		}

		else if (node->left == nullptr)
		{
			TreeNode<T>* temp = node;
			node = node->right;

			delete temp;
			temp = nullptr;
		}

		else if (node->right == nullptr)
		{
			TreeNode<T>* temp = node;
			node = node->left;

			delete temp;
			temp = nullptr;
		}

		else
		{
			node->key = findMin(node->right)->key;
			node->right = remove(node->right, findMin(node->right)->key);
		}
	}

	return node;
}

template <typename T>
void BSTree<T>::inorder(TreeNode<T>* node) const
{
	if (node->left != nullptr)
	{
		inorder(node->left);
		
	}


	std::cout << node->key << "  ";

	if (node->right != nullptr)
	{
		inorder(node->right);
	}
}

template <typename T>
void BSTree<T>::preorder(TreeNode<T>* node) const
{
	std::cout << node->key << "  ";

	if (node->left != nullptr)
	{
		preorder(node->left);
	}

	if (node->right != nullptr)
	{
		preorder(node->right);
	}
}

template <typename T>
void BSTree<T>::postorder(TreeNode<T>* node) const
{
	if (node->left != nullptr)
	{
		postorder(node->left);
	}

	if (node->right != nullptr)
	{
		postorder(node->right);
	}

	std::cout << node->key << "  ";
}

template <typename T>
bool BSTree<T>::find(TreeNode<T>* node, const T& elem)
{
	if (node == nullptr)
	{
		return false;
	}

	if (elem == node->key)
	{
		return true;
	}

	if (elem < node->key)
	{
		return find(node->left, elem);
	}

	else
	{
		return find(node->right, elem);
	}
}

template <typename T>
TreeNode<T>* BSTree<T>::findMin(TreeNode<T>* node)
{
	if (node == nullptr || node->left == nullptr)
	{
		return node;
	}

	return findMin(node->left);
}

template <typename T>
void BSTree<T>::clear(TreeNode<T>* node)
{
	if (node != nullptr)
	{
		clear(node->left);
		clear(node->right);
	}

	delete node;
	node = nullptr;
}

template <typename T>
size_t BSTree<T>::height(TreeNode<T>* node)
{
	if (node == nullptr)
	{
		return 0u;
	}

	return std::max(height(node->left), height(node->right)) + 1;
}