#include <iostream>
#include <cstring>
using namespace std;

template<class T> class Chain;

template <class T>
class ChainNode{ // chainnode 클래스 정의
	friend class Chain<T>;
	public:
	ChainNode(T element = 0, ChainNode<T>* next = 0)
	{data = element; link = next;}
	private:
	T data;
	ChainNode<T> *link;
};

template <class T>
class Chain{ // chain 클래스 정의
	public:
		Chain(){first=0;};//초기에 공백 체인을 생성하는 생성자
		//체인의 모든 원소를 삭제하는 파괴자
		~Chain()
		{
			while(first)
				DeleteFirst();
		}
		//체인 조작 연산
		//리스트의 처음에 노드 삽입
		void InsertFirst(ChainNode<T>* e)
		{
			if(first){	
				e->link = first;
				first = e;
			}
			else
				first = e;
		}
		//리스트의 끝에 노드 삽입
		void InsertBack(ChainNode<T>* e)
		{
			ChainIterator i(first);
			if(first)
			{
				while(i.Current()->link!=0)
					i++;	
				i.Current()->link = e;
			}
			else
				first = e;
		}

		//체인의 처음에 삭제
		void DeleteFirst()
		{
			ChainNode<T>* tmp;
			tmp = first->link;
			delete first;
			first = tmp;	
		}
		//체인의 맨 뒤에서 삭제하는 함수
		void DeleteBack()
		{
			ChainIterator i(first);
			for(; ;i++)
			{
				if(i.Current()->link->link == 0)
					break;
			}
			delete i.Current()->link;
			i.Current() ->link = 0;
		}
		//리스트의 첫 번째 원소 반환
		T& Front()
		{
			return first->data;
		}
		//리스트의 마지막 원소를 반환
		T& Back()
		{
			ChainIterator i(first);
			for(; ;i++)
			{
				if(i.Current()->link==0)
					break;
			}
			return i.Current()->data;
		}
		//i번째 원소를 반환하는 함수
		T& Get(int i)
		{
			ChainIterator j(first);
			for(int num=0; num<i; num++, j++);
			return j.Current()->data;
		}
		//i번째 원소 뒤에 삽입하는 함수
		void InsertNode(int i, ChainNode<T> * e)
		{
			ChainIterator ci(first);
			for(int j=0; j<i; ci++, j++);
			e->link = ci.Current()->link;
			ci.Current()->link = e;
		}
		//i번째 원소를 삭제하는 함수
		void DeleteI(int i)
		{
			ChainNode<T>* tmp = 0;
			ChainIterator ci(first);
			for(int num=0; num<(i-1) ; num++, ci++);
			tmp = ci.Current()->link;
			ci.Current()->link = tmp->link;
			delete tmp;
		}

		//chain을 위한 전방 반복
		class ChainIterator{
			public:
				//생략된 전방 반복자에 대해 c++은 타입 정의를 요구한다

				//current가 private라서 리턴함수 선언
				ChainNode<T>* Current()
				{return current;}

				//생성자
				ChainIterator(ChainNode <T>* startNode =0)
				{current = startNode;}
				//역참조 연산자
				T&operator*()const{return current -> data;}
				T*operator->()const{return &current->data;}
				//증가
				ChainIterator& operator++()//사전 증가
				{current=current->link;
					return *this;}//반복자 객체 리턴
				ChainIterator operator++(int)//사후 증가
				{
					ChainIterator old = *this;
					current = current->link;
					return old;
				}
				//동등 검사
				bool operator!=(const ChainIterator right)const
				{return current != right.current;}
				bool operator==(const ChainIterator right)const
				{return current == right.current;}
			private:
				ChainNode <T>* current;
		};
		ChainIterator begin(){return ChainIterator(first);}
	private:
		ChainNode<T> *first;
};

//체인의 각 노드들 출력
template <class T>
void pr(Chain<T> &c1)
{
	Chain<int>::ChainIterator yi = c1.begin();
	cout<<"===============all node==========="<<endl;
	for(;yi!=0;yi++)
		cout<<*yi<<" ";
	cout<<endl;
}

int main(){
	Chain<int> chain;
	//아홉 개의  노드를 생성하고 초기화
	chain.InsertFirst(new ChainNode<int>(9));
	chain.InsertFirst(new ChainNode<int>(8));
	chain.InsertFirst(new ChainNode<int>(7));
	chain.InsertFirst(new ChainNode<int>(6));
	chain.InsertFirst(new ChainNode<int>(5));
	chain.InsertFirst(new ChainNode<int>(4));
	chain.InsertFirst(new ChainNode<int>(3));
	chain.InsertFirst(new ChainNode<int>(2));
	chain.InsertFirst(new ChainNode<int>(1));

	//체인 모두 출력
	pr(chain);

	//0을 맨 앞에 삽입
	chain.InsertFirst(new ChainNode<int>(0));

	//체인의 각 노드들을 출력
	pr(chain);
	cout<<"insertfirst :0"<<endl;
	
	//10을 맨 뒤에 삽입한다
	chain.InsertBack(new ChainNode<int>(10));

	//전체 노드 출력
	pr(chain);
	cout<<"insertback :10"<<endl;

	//front호출
	cout<<"Front:" <<chain.Front()<<endl;

	//Back를 호출
	cout<<"Back:"<< chain.Back()<<endl;

	//get(2)호출
	cout<<"get(2):"<< chain.Get(2)<<endl;

	//맨 앞에 있는 0 삭제
	chain.DeleteFirst();

	//전체 노드 출력
	pr(chain);
	cout<<"deletefirst:0"<<endl;

	//맨 뒤의 10 삭제
	chain.DeleteBack();

	//전체 노드 출력
	pr(chain);
	cout<<"deleteback:10"<<endl;

	//3과 4 노드 사이에 100 삽입
	chain.InsertNode(2, new ChainNode<int>(100));
	
	//전체 노드 출력
	pr(chain);
	cout<<"insertnode : 100"<<endl;

	//6을 삭제한다
	chain.DeleteI(6);

	//전체 노드 출력
	pr(chain);
	cout<<"delete: 6"<<endl;
	
	return 0;
}
