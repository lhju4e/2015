#include <iostream>
#include <cstring>
#include <utility>
using namespace std;
//TreeNode 생성자 정의

template <class K, class E> class BST; //전방 선언

template <class T> 	
class TreeNode{
	template<class K, class E> friend class BST;
	public:
		TreeNode();
	private:
		T data;
		TreeNode<T>* leftChild;
		TreeNode<T>* rightChild;
};

template<class K, class E>
class BST{//BST 클래스 정의
	public:
		BST();
		~BST();
		
		bool IsEmpty()const;
		//공백이면 true를 반환
		void Get(const K&);
		//지시한 키 값을 가진 쌍에 대한 포인터를 반환, 쌍이 없으면 0을 반환
		void Insert(pair<K, E>);
		//쌍을 삽입, 키가 중복되면 관련 원소를 갱신
		void remove(const K&);
		//지시된 키를 가진 쌍을 삭제
	private:
		TreeNode< pair<K, E> > *root;
};

template <class K, class E>//생성자
BST<K, E>::BST(){root = 0;}

template <class K, class E>//소멸자
BST<K, E>::~BST(){}
	
template <class K, class E> //반복적 탐색
void BST<K, E>::Get(const K& k)
{
	TreeNode< pair<K,E> >*currentNode = root;
	while(currentNode){
		if(k < currentNode -> data.first)
			currentNode = currentNode -> leftChild;
		else if(k > currentNode -> data.first)
			currentNode = currentNode -> rightChild;
		else if(k == currentNode -> data.first){
			cout<< currentNode -> data.first << currentNode -> data.second << endl;
			return ;
	}
			cout<<"key don't exist"<<endl;//키가 없는 경우
		return ;
	}
}

//insert에 pair이 아니라 하나씩 넣어야함
//treeNode생성자에 페어값을 못넣음
//정수로 해서 해보기
template <class K, class E>//이원 탐색 트리에 삽입
void BST<K,E>::Insert(pair<K, E> thePair)
{//thePair를 삽입한다.
	//Pair.first를 탐색, pp는 p의 부모
	TreeNode<pair <K, E> > *p = root, *pp = 0;
	while(p) {
		pp = p;
		if(thePair.first < p -> data.first)
			p = p->leftChild;
		else if(thePair.first > p -> data.first)
			p = p->rightChild;
		else // 관련 원소를 복사해서 갱신
			{p -> data.second = thePair.second;
				return;}
	}
		//삽입 수행
		p = new TreeNode<pair<K, E> >;
		if(root)//트리는 공백이 아님
			if(thePair.first < pp -> data.first)
				pp->leftChild = p;
			else pp -> rightChild = p;
		else
			root = p;
}

template <class K, class E>//이원 탐색 트리에 삭제
void BST <K, E>::remove(const K& k)
{//currentNode는 삭제해야 할 노드, p는 대체할 노드
	TreeNode<pair <K, E> >* currentNode = root, *p = 0;
	while(currentNode){
		if(k < currentNode -> data.first)
			currentNode = currentNode -> leftChild;
		else if(k > currentNode -> data.first)
			currentNode = currentNode -> rightChild;
		else if(k == currentNode -> data.first)
		{//원소를 찾음
			p = currentNode -> leftChild;
				//찾은 노드에서 왼쪽 서브트리로 이동
				//왼쪽 서브트리에서 가장 큰 값으로 삭제값 대체
			while(p -> rightChild)//오른쪽 서브트리가 없을때까지
				p = p -> rightChild;//오른쪽 서브트리로 이동
			currentNode -> data.first = p -> data.first;
			currentNode -> data.second = p -> data.second;
			if(p -> leftChild)//왼쪽에 서브트리가 있다면
				remove(p -> data.first);//p값 다시 대체
			else{//왼쪽에 서브트리가 없다면
				p -> data.first = 0;
				p -> data.second = 0;
				delete p;//삭제}
			break;
			}
		}
	}
}

int main(){

	BST<int, int> b1;//BST객체 생성
	
	pair<int, int> p1(3,32);
	b1.Insert(p1);
	for(int i = 1; i<11; i++)
		b1.Get(i);
/*
	pair<int, int> p2(5, 54);
   b1.Insert(p2);
	for(int i = 1; i<11; i++)
		b1.Get(i);

	pair<int, int> p3(7, 77);
		b1.Insert(p3);
	for(int i = 1; i<11; i++)
		b1.Get(i);

		pair<int, int> p4(4, 41);
	b1.Insert(p4);
	for(int i = 1; i<11; i++)
		b1.Get(i);

	pair<int, int> p5(1, 10);
		b1.Insert(p5);
	for(int i = 1; i<11; i++)
		b1.Get(i);

		pair<int, int> p6(2, 21);
	b1.Insert(p6);
	for(int i = 1; i<11; i++)
		b1.Get(i);

		pair<int, int> p7(10, 100);
	b1.Insert(p7);
	for(int i = 1; i<11; i++)
		b1.Get(i);

		pair<int, int> p8(9, 98);
	b1.Insert(p8);
	for(int i = 1; i<11; i++)
		b1.Get(i);

	b1.Insert(8, 83);
	for(int i = 1; i<11; i++)
		Get(i);

	b1.Insert(6, 64);
	for(int i = 1; i<11; i++)
		Get(i);
*/
	return 0;
}

