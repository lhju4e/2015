#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class Bag //bag클래스 정의
{
	public:
		Bag(int bagCapacity = 3);
		~Bag();

		int Size()const;
		bool IsEmpty() const;
		T& Element() const;

		void Push(const T&);
		void Pop();
		void ChangeSizeID(T*&, const int, const int);

	private:
		T*array;
		int capacity;
		int top;
};


template <class T>	//생성자
Bag<T>::Bag (int bagCapacity):capacity (bagCapacity){
	if(capacity < 1) throw "Capacity must be> 0";
	array = new T[capacity];
	top = -1;

}

template <class T>//소멸자
Bag<T>::~Bag(){delete [] array;}


template <class T>//원소삽입
void Bag<T>::Push(const T&x){
	if(capacity == top + 1)
	{
		ChangeSizeID(array, capacity, 2*capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

	template <class T>//크기증가
void Bag<T>::ChangeSizeID(T*&a, const int oldSize, const int newSize)
{
	if(newSize<0) throw "New length must be>=0";

	T*temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete []a;
	a = temp;
}

template <class T>//원소삭제
void Bag<T>::Pop(){
	if(IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top/2;
	copy(array + deletePos + 1, array + top + 1, array + deletePos);
	array[top--].~T();
}

template <class T>//중간원소 반환
inline T& Bag<T>::Element() const{
	if(IsEmpty()) throw "Bag is empty";
	return array[top/2];
}

template <class T>//크기반환
inline int Bag<T>::Size() const {return top+1;}

template <class T>//비었는지 아닌지
inline bool Bag<T>::IsEmpty() const {return Size() == 0;}

class Bizcard
{
	private:
		char * name;
		char * phone;
	public:
		Bizcard(const char *n, const char *p)
		{
			int len = strlen(n)+1;//동적할당
			name = new char[len];
			strcpy(name, n);
			int leng = strlen(p) + 1;
			phone = new char[leng];
			strcpy(phone, p);
		}
		~Bizcard()
		{
			delete []name;
			delete []phone;
		}
		ShowInfo()
		{
			cout<< "name:" << name << endl;
			cout<< "phone" << phone << endl<<endl;
		}
};

template <class T>
void p(Bag<T> &b1){
	cout<<"bag size :" << b1.Size()<<endl;
	if(b1.IsEmpty())
		cout<<"bag is empty"<<endl;	   
	else
		cout<<"bag is not empty"<<endl;
	try
	{
		cout<<"Element:" <<b1.Element()<<endl<<endl;
	} catch(const char *expn)
	{
		cout<<"bag is empty"<<endl<<endl;}
}

template <class T>
void p2(Bag<T> &b1){
	cout<<"bag size :" << b1.Size()<<endl;
	if(b1.IsEmpty())
		cout<<"bag is empty"<<endl;	   
	else
		cout<<"bag is not empty"<<endl;
	try
	{
		b1.Element()->ShowInfo();
	} catch(const char *expn)
	{
		cout<<"bag is empty"<<endl<<endl;}
}	


int main(){
	Bag<int> b1;//bag객체 생성

	p(b1);
	cout<<"plus 3 elements"<<endl;//원소 3개 추가
	b1.Push(1);
	b1.Push(2);
	b1.Push(3);

	p(b1);

	cout<<"plus 4 elements"<<endl;//원소 4개 추가
	b1.Push(4);
	b1.Push(5);
	b1.Push(6);
	b1.Push(7);
	
	p(b1);

	cout<<"minus 2 elements"<<endl;//원소 2개 삭제
	b1.Pop();
	b1.Pop();

	p(b1);

	cout<<"=======biacard======"<<endl;

	Bag<Bizcard*> b2;//bizcard 객체 생성

	p2(b2);

	cout<<"plus 3 elements"<<endl;//원소 3개 등록 후 출력
	Bizcard * a1 = new Bizcard("LEE", "0111111111");
	Bizcard * a2 = new Bizcard("kim", "2222222222");
	Bizcard * a3 = new Bizcard("han", "33333333323");
	b2.Push(a1);
	b2.Push(a2);
	b2.Push(a3);

	p2(b2);

	cout<<"plus 4 elements"<<endl;//4개 등록 후 출력
	Bizcard * a4 = new Bizcard("park", "44444444");
	Bizcard * a5 = new Bizcard("choi", "5555555");
	Bizcard * a6 = new Bizcard("shin", "666666666");
	Bizcard * a7 = new Bizcard("zoh", "777777777");
	b2.Push(a4);
	b2.Push(a5);
	b2.Push(a6);
	b2.Push(a7);

	p2(b2);
	cout<<"minus 2 elements"<<endl;//2개 삭제 후 출력
	b2.Pop();
	b2.Pop();

	p2(b2);

	return 0;
}
