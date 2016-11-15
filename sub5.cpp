#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

template <class K, class E> class BST; //전방 선언

template <class K, class E>
class TreeNode{
	friend class BST<K, E>;
	public:
	TreeNode(pair<K, E>);
	private:
	pair<K, E> data;
	TreeNode<K, E>* leftChild;
	TreeNode<K, E>* rightChild;
};

template<class K, class E>
TreeNode<K, E>::TreeNode(pair<K, E> thePair){
	data = thePair;
	leftChild = 0;
	rightChild = 0;
}

template<class K, class E>
class BST{//BST 클래스 정의
	public:
		BST();
		~BST();

		bool IsEmpty()const;
		//공백이면 true를 반환
		void Get(const K&);
		//지시한 키 값을 가진 쌍에 대한 포인터를 반환, 쌍이 없으면 0을 반환
		void Insert(pair<K, E>&);
		//쌍을 삽입, 키가 중복되면 관련 원소를 갱신
		void remove(const K&);
		//지시된 키를 가진 쌍을 삭제
	private:
		TreeNode<K, E> *root;
};

template <class K, class E>//생성자
BST<K, E>::BST(){root = 0;}

template <class K, class E>//소멸자
BST<K, E>::~BST(){}

	template <class K, class E> //반복적 탐색
void BST<K, E>::Get(const K& k)//찾아서 출력해줌
{
	TreeNode<K,E>*currentNode = root;
	while(currentNode)
	{
		if(k < currentNode -> data.first)
			currentNode = currentNode -> leftChild;
		else if(k > currentNode -> data.first)
			currentNode = currentNode -> rightChild;
		else if(k == currentNode -> data.first)
		{
			cout<<'|'<< currentNode -> data.first <<","<<  currentNode -> data.second <<"|";//키랑 원소 출력
			return ;
		}
	}
	cout<<"|null|";//키가 없는 경우
	return ;
}

	template <class K, class E>//이원 탐색 트리에 삽입-책 코드 그대로
void BST<K,E>::Insert(pair<K, E> &thePair)
{//thePair를 삽입한다.
	//Pair.first를 탐색, pp는 p의 부모
	TreeNode<K, E> *p = root, *pp = 0;
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
	p = new TreeNode<K, E>(thePair);
	if(root)//트리는 공백이 아님
		if(thePair.first < pp -> data.first)
			pp->leftChild = p;
		else pp -> rightChild = p;
	else
		root = p;
}


	template <class K, class E>//이원 탐색 트리에 삭제
void BST<K, E>::remove(const K& k)
{//currentNode는 삭제해야 할 노드, p는 대체할 노드, pp는 부모노드
	TreeNode<K, E> * currentNode = root, *p = 0, *pp = 0;
if(currentNode == 0) return;//트리가 없다면 그냥 종료
	if(k == root -> data.first )
	{//지우는 노드가 루트노드일 경우
		if(currentNode -> leftChild == 0 && currentNode -> rightChild != 0)
		{//오른쪽자식만 있는 경우
			p = currentNode -> rightChild; // 오른쪽 서브트리에서 가장 작은 값으로 대체
			if(p -> leftChild)
			{//p의 왼쪽자식이 있는 경우
				pp = p;//p의 부모
				while(p -> leftChild){//p의 왼쪽자식이 있는 경우
					p = p-> leftChild;
					if(p->leftChild == 0) break;
					pp = pp -> leftChild;
				}
			currentNode -> data.first = p -> data.first;
			currentNode -> data.second = p -> data.second;//값 대체

			if(p -> rightChild)//p의 오른쪽에 서브트리가 또 있다면
				remove(p -> data.first);//p값 다시 대체
			else{//오른쪽에 서브트리가 없다면
				delete p; 
				pp -> rightChild = 0;
				return;	
				}
			}
			else {
				currentNode -> data.first = p -> data.first;
				currentNode -> data.second = p -> data.second;//값 대체
				pp = p -> rightChild;
				delete p;
				currentNode -> rightChild = pp;
				return;
			}
		}
				
		if(currentNode -> leftChild != 0 || currentNode -> rightChild != 0)
		{//왼쪽자식이 있거나 둘다 있는 경우
			p = currentNode -> leftChild; //왼쪽 서브트리에서 가장 큰 값으로 대체	
			if(p -> rightChild){//p의 오른자식이 있는 경우
			pp = p; 
			while(p -> rightChild){
				p = p -> rightChild;
				if(p -> rightChild == 0) break;
				pp = p -> rightChild;
			}
			currentNode -> data.first = p -> data.first;
			currentNode -> data.second = p -> data.second;//값 대체
			if(p -> leftChild)//p값의 왼쪽에 서브트리가 또 있다면
				remove(p -> data.first);//p값 다시 대체
			else{//왼쪽에 서브트리가 없다면
				delete p;
				pp -> rightChild = 0;
				return;	
				}
			}
			else{
				currentNode -> data.first = p -> data.first;
				currentNode -> data.second = p -> data.second;
				delete p;
				currentNode -> leftChild = 0;
				return;
			}
		}

			else{//루트 하나만 존재할 경우
				delete root;
				root = 0;
				return;
			}
		
		}
	//삭제하는 노드가 루트도드가 아닐 경우
	//여기서의 p는 부모노드임
	p = root;
	while(true){//찾을때까지 돎
		if(k < currentNode -> data.first){
			currentNode = currentNode -> leftChild; 
			if(k == currentNode -> data.first)
				break;
			p = p -> leftChild;
		}
		else if(k > currentNode -> data.first){
			currentNode = currentNode -> rightChild; 
			if(k == currentNode -> data.first)
				break;
			p = p -> rightChild;
		}
	}
	
	if(k == currentNode -> data.first)
		{//원소를 찾음
			//지우는 노드의 서브트리가  존재할 경우
			//p는 currentNode의 부모노드를 가리거나 대체값을 가리킴
			//지우는 노드가 리프 노드일 경우
			if((currentNode -> leftChild == 0) && (currentNode -> rightChild == 0)){
				if((p -> leftChild) -> data.first == currentNode -> data.first)//지우는 노드가 왼쪽일때
				{ 
					delete currentNode;
					p -> leftChild = 0;
					return;
				}
				else//오른쪽일 때
				{
					delete currentNode;
					p -> rightChild = 0;
					return;
				}
			}

			//리프 노드가 아닐 경우
			//지우는 노드의 왼쪽 서브트리만 존재할 경우
			else if((currentNode -> leftChild != 0) && (currentNode -> rightChild == 0)){
				if(p -> leftChild){
				if((p -> leftChild) -> data.first == currentNode -> data.first)//지우는 노드가 왼쪽일때
					{
					p -> leftChild = currentNode -> leftChild;
					delete currentNode;
					return;
					}
				}
				if(p -> rightChild){
				if((p -> rightChild) -> data.first == currentNode -> data.first){//지우는 노드가 오른쪽일 때
					p -> rightChild = currentNode -> leftChild;
					delete currentNode;
					return;
					}	
				}

			}
			//지우는 노드의 오른쪽 서브트리만 존재할 경우
			else if((currentNode -> leftChild == 0) && (currentNode -> rightChild != 0)){
				if(p -> leftChild){
				if((p -> leftChild) -> data.first == currentNode -> data.first)//지우는 노드가 왼쪽일 때
				{
					p -> leftChild = currentNode -> rightChild;
					delete currentNode;
					return;
				}}
				if(p -> rightChild){
					if((p -> rightChild) -> data.first == currentNode -> data.first){//지우는 노드가 오른쪽일 때
						p -> rightChild = currentNode -> rightChild;
					delete currentNode;
					return;
					}
				}
			}
			//지우는 노드의 양쪽 서브트리가 다 존재할 경우
			else if((currentNode -> leftChild != 0) && (currentNode -> rightChild != 0)){
				//찾은 노드에서 왼쪽 서브트리로 이동
				p = currentNode -> leftChild;
				pp = p;
				//왼쪽 서브트리에서 가장 큰 값으로 삭제값 대체
				while(p -> rightChild){//오른쪽 서브트리가 없을때까지
					p = p -> rightChild;//오른쪽 서브트리로 이동
					if(p -> rightChild == 0) break;
					pp = p -> rightChild;
				}
					currentNode -> data.first = p -> data.first;
				currentNode -> data.second = p -> data.second;
				if(p -> leftChild)//왼쪽에 서브트리가 있다면
					remove(p -> data.first);//p값 다시 대체
				else{//왼쪽에 서브트리가 없다면
					delete p;//삭제
				pp -> rightChild = 0;	
				return;
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
	cout<<endl;

	pair<int, int> p2(5, 54);
	b1.Insert(p2);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p3(7, 77);
	b1.Insert(p3);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p4(4, 41);
	b1.Insert(p4);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p5(1, 10);
	b1.Insert(p5);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p6(2, 21);
	b1.Insert(p6);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p7(10, 100);
	b1.Insert(p7);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p8(9, 98);
	b1.Insert(p8);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p9(8, 83);
	b1.Insert(p9);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	pair<int, int> p10(6, 64);
	b1.Insert(p10);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	cout<<endl;
	b1.remove(4);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(3);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(8);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(10);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(2);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(6);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(5);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(1);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;
	
	b1.remove(7);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	b1.remove(9);
	for(int i = 1; i<11; i++)
		b1.Get(i);
	cout<<endl;

	return 0;
}

