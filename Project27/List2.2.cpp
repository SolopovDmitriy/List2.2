#include<iostream>
using namespace std;

#define TAB "\t"

class List
{
	class Element
	{
		int data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			data(data),
			pNext(pNext),
			pPrev(pPrev)
		{
			//cout << "E_Constructor " << this << endl;
		}
		~Element()
		{
			//cout << "E_Destructor " << this << endl;
		}
		friend class List;
	};
	Element* head;
	Element* tail;
	int size;
public:
	List()
	{
		head = tail = nullptr;
		size = 0;
		cout << "L_Constructor " << this << endl;
	}
	List(const List& other) :List()
	{
		/*this->size = other.size;*/
		for (Element* Temp = other.head; Temp != nullptr; Temp = Temp->pNext)
		{
			PushBack(Temp->data);
		}
	}
	List(List&& other) :List()
	{
		this->size = other.size;
		for (Element* Temp = other.head; Temp != nullptr; Temp = Temp->pNext)
		{
			PushBack(Temp->data);
		}
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	~List()
	{
		while (head) { PopFront(); }
		cout << "L_Destructor " << this << endl;
	}
	//Overloaded operators
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		this->~List();
		for (Element* Temp = other.head; Temp != nullptr; Temp = Temp->pNext)
		{
			PushBack(Temp->data);
		}
		return *this;
	}
	List& operator=(List&& other)
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
		for (Element* Temp = other.head; Temp != nullptr; Temp = Temp->pNext)
		{
			PushBack(Temp->data);
		}
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
		return *this;
	}
	/*List& operator+=(List& other)
	{
	Element* Temp1 = this->head;
	Element* Temp2 = other.tail;
	for (int i = 0; i < this->size; i++)
	{
	Temp1 = Temp1->pNext;
	}
	for (int i = 0; i < other.size; i++)
	{
	Temp2 = Temp2->pPrev;
	}
	Temp1 = other.head;
	Temp2 = this->tail;
	return *this;
	}*/
	//Adding elements
	void PushFront(int data)
	{
		if (head == nullptr && tail == nullptr)
		{
			head = tail = new Element(data);
		}
		else
		{
			head = head->pPrev = new Element(data, head);
		}
		size++;
	}
	void PushBack(int data)
	{
		if (head == nullptr && tail == nullptr)
		{
			head = tail = new Element(data);
		}
		else
		{
			tail = tail->pNext = new Element(data, nullptr, tail);
		}
		size++;
	}
	void Insert(int data, int index)
	{
		Element* New = new Element(data);
		Element* Temp = head;
		if (index > size) return;
		if (index == 0) {
			PushFront(data);
			return;
		}
		size++;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		if (head == nullptr && tail == nullptr)
		{
			head = tail = New;
		}
		else
		{
			New->pNext = Temp->pNext;
			New->pPrev = Temp;
			Temp->pNext = New;
			Temp = New;
		}
	}
	//Subtracting elements
	void PopFront()
	{
		if (!head && !tail) return;
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			head = head->pNext;
			delete head->pPrev;
			head->pPrev = nullptr;
		}
		size--;
	}
	void PopBack()
	{
		if (!head && !tail) return;
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			tail = tail->pPrev;
			delete tail->pNext;
			tail->pNext = nullptr;
		}
		size--;
	}
	void Erase(int index)
	{
		Element* Temp;
		if (index == 0)
		{
			PopFront();
			return;
		}
		if (index == size - 1)
		{
			PopBack();
			return;
		}
		if (index > size || index < 0) return;
		if (index < size / 2)
		{
			Temp = head;
			for (int i = 0; i < index; i++) { Temp = Temp->pNext; }
		}
		else
		{
			Temp = tail;
			for (int i = 0; i < size - index - 1; i++) { Temp = Temp->pPrev; }
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	void print() const
	{
		for (Element* Temp = head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->data << TAB << Temp->pNext << endl;
		}
		cout << "List size: " << size << endl;
		cout << endl;
	}
	void print_reverse() const
	{
		for (Element* Temp = tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->data << TAB << Temp->pNext << endl;
		}
		cout << "List size: " << size << endl;
		cout << endl;
	}
};

//#define Fundamentals

int main()
{
	List list;
	int n;
	cout << "List size: "; cin >> n;
#ifdef Fundamentals
	for (int i = 0; i < n; i++)
	{
		list.PushBack(rand() % 100);
	}
	list.print();
	list.Erase(-4);
	list.print();
	List list2;
	list2 = list;
	list2.print();
#endif // Fu

	return 0;
}