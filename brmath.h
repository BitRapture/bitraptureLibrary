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
				children = new node<T>[_amount](this);
				childrenSize = _amount;
			}
		}

		// Instantiate node with values
		node(T _data) : data{ _data }, parent{ nullptr }, children{ nullptr }, childrenSize{ 0 } {}
		node(node& _parent) : data{ 0 }, parent{ _parent }, children{ nullptr }, childrenSize{ 0 } {}
		// Default construction
		node() : data{ 0 }, parent{ nullptr }, children{ nullptr }, childrenSize{ 0 } {}
		// Destruction
		~node()
		{
			delete[] children;
		}
	};

	// generic Binary Tree
	template<class T>
	class bt
	{
		// Start of tree
		node<T> root;
		// Max depth of tree
		int maxDepth;

	public:

		/*	TODO:
		*	Implement Binary Tree traversal properly,
		*	Depth search & Breadth search (& maybe full generic search too)
		* 
		node<T>& traverseNode(node<T>& _base, int _curDepth, int _depth, int _branch, bool _side)
		{
			if (_base.parent != nullptr && _base.childrenSize == 0)
			{
				_base = _base.parent;
				_side = !_side;
				--_curDepth;
			}
			else
			{
				_base = _base.children[_side];
				++_curDepth;
			}

			if (_curDepth == _depth)
				--_branch;
			if (_branch <= 0)
				return _base;
			traverseNode(_base, _curDepth, _depth, _branch, _side);
		}

		node<T>& getNode(int _depth, int _branch)
		{
			node<T>* stack = root;
			for (int i = 0; i < _depth - 1; ++i)
			{
				stack = stack->children[0];
			}
		}
		*/

		// Instantiate bt with values
		bt(T _data) : root(_data), maxDepth{ 0 } {}
		// Default construction
		bt() : maxDepth{ 0 } {}
	};
}

#endif