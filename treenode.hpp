#pragma once

template <typename T>
struct TreeNode
{
	TreeNode(const T& value) :key(value), left(nullptr), right(nullptr)
	{

	}

	T key;
	TreeNode* left;
	TreeNode* right;
};