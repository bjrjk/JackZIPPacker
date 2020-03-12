#ifndef JACKREN_PRIORITY_QUEUE
#define JACKREN_PRIORITY_QUEUE

#include "include.hpp"
#include "vector.hpp"
#include "algorithm.hpp"

/*
	Override operator < before using PriorityQueue, default Min-Heap
	请在使用优先级队列前重载<运算符，默认为小根堆
*/

//优先级队列定义
template<typename T>
class PriorityQueue {
private:
	Vector<T> arr; //选用向量作为二叉堆承载容器
	//左儿子
	inline static int lSon(int node) {
		return 2 * node + 1;
	}
	//右儿子
	inline static int rSon(int node) {
		return 2 * node + 2;
	}
	//父亲
	inline static int father(int node) {
		return (node - 1) >> 1;
	}
	//获取堆最后一个节点并删除
	inline T getLastElemAndDelete() {
		T elem = arr[arr.size() - 1];
		arr.pop();
		return elem;
	}
	//上滤秩为node的节点
	void percolateUp(int node) {
		T tmpElem = arr[node];
		while (node > 0) {
			int fa = father(node);
			if (arr[fa] < tmpElem)break;
			arr[node] = arr[fa];
			node = fa;
		}
		arr[node] = tmpElem;
	}
	//下滤秩为node的节点
	void percolateDown(int node) {
		T tmpElem = arr[node];
		while (1) {
			int sonIndex;
			if (lSon(node) >= arr.size())break;
			else if (rSon(node) >= arr.size())sonIndex = lSon(node);
			else sonIndex = arr[lSon(node)] < arr[rSon(node)] ? lSon(node) : rSon(node);
			if (tmpElem < arr[sonIndex])break;
			arr[node] = arr[sonIndex];
			node = sonIndex;
		}
		arr[node] = tmpElem;
	}
public:
	//默认构造函数
	PriorityQueue() {}
	//利用Vector向量初始化建堆
	PriorityQueue(const Vector<T>& initVector) {
		arr = initVector;
		for (int i = (arr.size() >> 1) - 1; i >= 0; i--)percolateDown(i);
	}
	//加入元素
	void push(const T& data) {
		arr.append(data);
		percolateUp(arr.size() - 1);
	}
	//返回优先级最高元素
	T top() {
		return arr[0];
	}
	//判定堆空
	bool empty() const {
		return arr.size() == 0;
	}
	//获得堆大小
	int size() const {
		return arr.size();
	}
	//堆首元素出堆
	bool pop() {
		if (empty())return false;
		if (arr.size() == 1)getLastElemAndDelete();
		else {
			arr[0] = getLastElemAndDelete();
			percolateDown(0);
		}
		return true;
	}
};

#endif