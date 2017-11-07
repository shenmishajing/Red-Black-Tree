/*文件名 ：RBT.H
 *----------------------------
 *该文件定义了模板类RBT
 *该模板的实现基于红黑树，并运用列表处理节点相同的情况
 *模板实例化时要求使用的类型定义了小于"<"运算符，该要求同时为改变数据排列顺序提供了方法
 */
#ifndef RBT_H_
#define RBT_H_
#include <Windows.h>

template <typename T>
class RBT
{
	enum color{ RED, BLACK};
	static RBT * Root;
	int Num;
	color color;
	RBT * Parent, Right, Left, Back;
	~RBT();
	RBT & Search_back() const;
public:
	bool Is_first() const;
	bool Left_rotate();
	bool Right_rotate();
	bool operator<(T & c);
	bool operator>(T & c);
	bool operator==(T & c);
	T content;
	RBT(T & content);
	RBT & Min() const;								//返回以this为根的子树中的最小元
	RBT & Max() const;								//返回以this为根的子树中的最大元
	RBT * Suc() const;								//返回以this的后继，当有相等元素时，返回本元素
	RBT * Prede() const;							//返回以this的前驱，当有相等元素时，返回本元素
	RBT & operator[](int n) const;					//返回this后面第n个元素
	friend RBT & Min();								//返回整棵树中的最小元
	friend RBT & Max();								//返回整棵树中的最大元
	friend RBT & Insert(T & content);				//向树中插入一个元素
	friend void Delete(RBT * p);					//删除树中的元素*p
	friend void Delete(T & content){ Delete( & Search(content)) }
	friend RBT * Search(T & content);				//查找元素
};

template<typename T>
RBT<T> & RBT<T>::Search_back() const
{
	RBT * p = this;
	while (p->Back != nullptr)
		p = p->Back;
	return *p;
}

template<typename T>
bool RBT<T>::Is_first() const
{
	if (this->Right != nullptr)
		if (this->Right->Parent == this)
			return true;
		return false;
	else
	{
		if (this->Left != nullptr)
			if (this->Left->Parent == this)
				return true;
			return false;
		else
			if (this->Parent != nullptr)
				if ((this->Parent->Right == this) || (this->Parent->Left == this))
					return true;
				return false;
			else
				if (Root == this)
					return ture;
				return false;
	}
}

template<typename T>
bool RBT<T>::Left_rotate()
{
	if (this->Right == nullptr)
		return false;
	this->Right->Parent = this->Parent;
	this->Parent = this->Right;
	this->Right = this->Parent->Left;
	this->Parent->Left = this;
	return true;
}

template<typename T>
bool RBT<T>::Right_rotate()
{
	if (this->Left == nullptr)
		return false;
	this->Left->Parent = this->Parent;
	this->Parent = this->Left;
	this->Left = this->Parent->Right;
	this->Parent->Right = this;
	return true;
}

template<typename T>
inline bool RBT<T>::operator<(T & c)
{
	if (content < c)
		return true;
	return false;
}

template<typename T>
inline bool RBT<T>::operator>(T & c)
{
	if (c < content)
		return true;
	return false;
}

template<typename T>
inline bool RBT<T>::operator==(T & c)
{
	if ((content < c) || (c < content))
		return false;
	return true;
}

template<typename T>
RBT<T>::RBT(T & content)
{
	color = RED;
	Num = 1;
	Parent = nullptr;
	Right = nullptr;
	Left = nullptr;
	Back = nullptr;
}

template<typename T>
RBT<T> & RBT<T>::Min() const
{
	RBT * p = this;
	while (p->Left != nullptr)
		p = p->Left;
	return *p;
}

template<typename T>
RBT<T> & RBT<T>::Max() const
{
	RBT * p = this;
	while (p->Right != nullptr)
		p = p->Right;
	return *p;
}

template<typename T>
RBT<T> * RBT<T>::Suc() const
{
	if (this->Num != 1)
		return this;
	if ((this->Parent != nullptr) && (this->Parent->Left == this) && (this->Right == nullptr))
		return this->Parent;
	if (this->Right != nullptr)
		return &(this->Right->Min());
	return nullptr;
}

template<typename T>
RBT<T> * RBT<T>::Prede() const
{
	if ((this->Parent != nullptr) && (this->Parent->Right == this) && (this->Left == nullptr))
		return this->Parent;
	if (this->Left != nullptr)
		return &(this->Left->Max());
	return nullptr;
}

template<typename T>
RBT<T> & RBT<T>::operator[](int n) const
{
	RBT * p = this;
	if (n < 0)
		return *this;
	while (n > 0)
	{
		n -= p->Num;
		if (n < 0)
			break;
		if ((this->Parent != nullptr) && (this->Parent->Left == this) && (this->Right == nullptr))
			p = this->Parent;
		if (this->Right != nullptr)
			p = &this->Right->Min();
		if (p == this)
			n = 0;
	}
	return *p;
}

template<typename T>
RBT<T> & Min()
{
	RBT * p = RBT::Root;
	while (p->Left != nullptr)
		p = p->Left;
	return *p;
}

template <typename T>
RBT<T> & Max()
{
	RBT * p = RBT::Root;
	while (p->Right != nullptr)
		p = p->Right;
	return *p;
}

template<typename T>
RBT<T> & Insert(T & content)
{
	RBT * p = Search(content), * q;
	while (q = new RBT(content) == nullptr)
		Sleep(1000);
	if (RBT::Root == nullptr)
	{
		RBT::Root = q;
		q->color = RBT::BLACK;
		return q;
	}
	if (p != nullptr)
	{
		p->Num += 1;
		p = &RBT::Search_back();
		p->Back = q;
		q->Parent = p->Parent;
		q->Left = p->Left;
		q->Right = p->Right;
		return *q;
	}
	p = RBT::Root;
	while (((*q < *p) && (p->Left == nullptr)) || ((*q > *p) && (p->Right == nullptr)))
	{
		if (*q < *p)
		{
			p = p->Left;
			continue;
		}
		if (*q > *p)
		{
			p = p->Right;
			continue;
		}
	}
	if (*q < *p)
		p->Left = q;
	else
		p->Right = q;
	q->Parent = p;
	while (q->color == RBT::RED)//********************************************************
	return *(p->Right);
}

#endif // !RBT_H_