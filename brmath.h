#ifndef _BRMATH_H_
#define _BRMATH_H_

#include <cmath>

// Comments for definitions
// {type} {Name}
// generic = template && abstract classes

// BitRapture 2020
namespace br
{
	// double Vector 2D
	struct v2d
	{
		// 2-Tuple
		double x, y;

		// Calculate and return the magnitude of v2d
		double magnitude()
		{
			return sqrt((x * x) + (y * y));
		}

		// Output v2d unit vector
		v2d normalize()
		{
			double m = 1 / magnitude();
			return v2d(x * m, y * m);
		}

		// Normalize v2d to a unit vector
		void normalizeSelf()
		{
			double m = 1 / magnitude();
			x *= m;
			y *= m;
		}

		// Operator overloading
		v2d operator+(v2d& _v)
		{
			return v2d(x + _v.x, y + _v.y);
		}
		v2d operator-(v2d& _v)
		{
			return v2d(x - _v.x, y - _v.y);
		}
		void operator+=(v2d& _v)
		{
			x += _v.x;
			y += _v.y;
		}
		void operator-=(v2d& _v)
		{
			x -= _v.x;
			y -= _v.y;
		}
		v2d operator*(double _x)
		{
			return v2d(x * _x, y * _x);
		}
		void operator*=(double _x)
		{
			x *= _x;
			y *= _x;
		}
		// Dot product
		double operator*(v2d& _v)
		{
			return (x * _v.x) + (y * _v.y);
		}

		// Instantiate v2d with values
		v2d(double _x, double _y) : x{ _x }, y{ _y } {}
		// Default construction
		v2d() : x{ 0 }, y{ 0 } {}
	};

	// double Vector 3D
	struct v3d
	{
		// 3-Tuple
		double x, y, z;

		// Calculate and return the magnitude of v3d
		double magnitude()
		{
			return sqrt((x * x) + (y * y) + (z * z));
		}

		// Output v3d unit vector
		v3d normalize()
		{
			double m = 1 / magnitude();
			return v3d(x * m, y * m, z * m);
		}

		// Normalize v3d to a unit vector
		void normalizeSelf()
		{
			double m = 1 / magnitude();
			x *= m;
			y *= m;
			z *= m;
		}

		// Output cross product of v3dA x v3dB
		v3d crossProduct(v3d& _v)
		{
			return v3d((y * _v.z) - (z * _v.y), (z * _v.x) - (x * _v.z), (x * _v.y) - (y * _v.y));
		}

		// Save the cross product of
		// v3dA = v3dA x v3dB
		void crossProductSelf(v3d& _v)
		{
			double tx = (y * _v.z) - (z * _v.y), ty = (z * _v.x) - (x * _v.z),
				tz = (x * _v.y) - (y * _v.x);
			x = tx;
			y = ty;
			z = tz;
		}

		// Operator overloading
		v3d operator+(v3d& _v)
		{
			return v3d(x + _v.x, y + _v.y, z + _v.z);
		}
		v3d operator-(v3d& _v)
		{
			return v3d(x - _v.x, y - _v.y, z - _v.z);
		}
		void operator+=(v3d& _v)
		{
			x += _v.x;
			y += _v.y;
			z += _v.z;
		}
		void operator-=(v3d& _v)
		{
			x -= _v.x;
			y -= _v.y;
			z -= _v.z;
		}
		v3d operator*(double _x)
		{
			return v3d(x * _x, y * _x, z * _x);
		}
		void operator*=(double _x)
		{
			x *= _x;
			y *= _x;
			z *= _x;
		}
		// Dot product
		double operator*(v3d& _v)
		{
			return (x * _v.x) + (y * _v.y) + (z * _v.z);
		}


		// Instantiate v3d with values
		v3d(double _x, double _y, double _z) : x{ _x }, y{ _y }, z{ _z } {}
		// Default construction
		v3d() : x{ 0 }, y{ 0 }, z{ 0 } {}
	};

	// generic Tree Node
	// Deprecated, not much use
	// TO-DO: update code for bt, then remove
	template<class T>
	struct node
	{
		// Node parent
		node<T>* parent;

		// Node children
		node<T>* children;
		// Children size
		int childrenSize;

		// Data
		T data;

		// Create children
		void createChildren(int _amount)
		{
			if (children == nullptr)
			{
				children = new node<T>[_amount];
				for (int i = 0; i < _amount; ++i)
					children[i].parent = this;
				childrenSize = _amount;
			}
		}

		// Instantiate node with values
		node(T _data) : data{ _data }, parent{ nullptr }, children{ nullptr }, childrenSize{ 0 } {}
		node(node& _parent) : data{ T() }, parent{ _parent }, children{ nullptr }, childrenSize{ 0 } {}
		// Default construction
		node() : data{ T() }, parent{ nullptr }, children{ nullptr }, childrenSize{ 0 } {}
		// Destruction
		~node()
		{
			delete[] children;
			children = nullptr;
		}
	};

	// generic Binary Tree Node
	// TO-DO: optimize for bt functions
	template<class T>
	class btNode
	{
	private:
		// Left and right children
		btNode<T>* left, *right;

		// Parent of node
		btNode<T>* parent;

	public:

		// Node data
		T data;

		// Create a new node
		// _side = 0; left
		// _side = 1; right
		void createNode(bool _side, T _data = T())
		{
			if (!_side)
			{
				if (left == nullptr)
					left = new btNode(_data, this);
			}
			else
			{
				if (right == nullptr)
					right = new btNode(_data, this);
			}
		}

		// Get a node
		// _side = 0; left
		// _side = 1; right
		btNode<T>* getNode(bool _side)
		{
			return (!_side ? left : right);
		}

		// Instantiate btNode with values
		btNode(T _data) : data{ _data }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}
		btNode(btNode<T>* _parent) : data{ T() }, left{ nullptr }, right{ nullptr }, parent{ _parent } {}
		btNode(T _data, btNode<T>* _parent) : data{ _data }, left{ nullptr }, right{ nullptr }, parent{ _parent } {}
		// Default construction
		btNode() : data{ T() }, left{ nullptr }, right{ nullptr }, parent{ nullptr } {}
		// Destruction
		~btNode()
		{
			delete left;
			left = nullptr;
			delete right;
			right = nullptr;
		}
	};

	// generic Binary Tree
	// TO-DO: Finish up traversal/search functions
	template<class T>
	class bt
	{
	public:
		// Start of tree
		btNode<T> root;

	private:
		// Size of the tree
		int size, rSize;

	public:

		// Preorder traversal of tree via depth
		void traDepthPO(btNode<T>* _node)
		{
			if (_node == nullptr)
				return;

			++rSize;
			if (size < rSize)
				size = rSize;

			traDepthPO(_node->getNode(0));
			traDepthPO(_node->getNode(1));
		}

		// Get size of tree
		int getSize()
		{
			return size;
		}
		

		// Instantiate bt with values
		bt(T _data) : root(_data), size{ 0 }, rSize{ 0 } {}
		// Default construction
		bt() : size{ 0 }, rSize{ 0 } {}
	};
}

#endif