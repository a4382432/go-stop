
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Bizcard{
    private:
    char *name;
    char *phone;
    public:
    Bizcard(char *name,char*phone)//constructor
    {
        this->name=new char[strlen(name)+1];
        this->phone=new char[strlen(phone)+1];
        strcpy(this->name,name);
        strcpy(this->phone,phone);
    }
    Bizcard()//default constructor
    {}
    /*~Bizcard()//destroyer
    {
        delete []name;
        delete []phone;
    }*/
    Bizcard(Bizcard & copy)//복사생성자
    :name(copy.name), phone(copy.phone)
    {}
    void ShowInfo()
    {
        cout<<"name: "<<this->name<<endl;
        cout<<"phone: "<<this->phone<<endl;
    }
    
    
};
/////////////////////////template 영역//////////////////////////////////
template <class T>
class Bag
{
    private:
    T* array;
    int capacity;
    int top;
    int newSize;
    
    public:
    Bag (int bagCapacity=3);
    ~Bag();
    
    int Size() const;
    bool IsEmpty() const;
    T& Element() const;
    void NewSize();
    void ChangeSize1D(T*&a,int,int);
    void Push(const T&);
    void Pop();
    int ReturnCapacity();
    void ShowBizcard();
    
};
template <class T>
void Bag<T>::ShowBizcard()
{
    for(int i=0;i<top+1;i++)
    array[i].ShowInfo();
}
template <class T>
int Bag<T>::ReturnCapacity()
{
    return capacity;
}
template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity)
{
    if(capacity<1) throw "Capacity must be >0";
    array= new T[capacity];
    top=-1;
}


template <class T>
int Bag<T>::Size() const
{
    cout<<sizeof(array)<<endl;
    int size=sizeof(array);
    
    return size;
}
template <class T>
T& Bag<T>::Element() const
{
    int random=rand()%capacity+0;
    cout<<array[random].ShowInfo()<<endl;
    return array[random];
}
template <class T>
bool Bag<T>::IsEmpty() const
{
    if(top==-1)
    return true;
    else
    return false;
}
template <class T>
Bag<T>::~Bag()
{
    delete []array;
}
template <class T>
void Bag<T>::ChangeSize1D(T*& a, int oldSize,int newSize)
{
    if(newSize<0)
    throw "New length must be >=0";
    T*temp=new T[newSize];
    int number=min(oldSize,newSize);
    copy(a,a+number,temp);
    delete []a;
    a=temp;
    capacity=newSize;
    
    
}
template <class T>
void Bag<T>::Push(const T& x)
{
    if(capacity==top+1)
    {
        ChangeSize1D(array,capacity,2*capacity);
        
    }
    array[++top]=x;
}

template<class T>
void Bag<T>::Pop()
{
    if(IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos=top/2;
    copy(array+deletePos+1,array+top+1,array+deletePos);
    array[top--].~T();
    
}
int ReturnRandom(int capacity)
{
    int randNum;
    srand((unsigned)time(NULL));
    randNum=rand()%capacity+0;
    cout<<randNum<<endl;
    return randNum;
}
int main(int argc, const char * argv[]) {
    Bag<Bizcard> bag;
    
    while(1)
    {
        cout<<"무엇을 할건가요?"<<endl;
        cout<<"1. 객체생성"<<endl<<"2. 임의의 비즈카드제거"<<endl<<"3. 카드보여주기"<<endl<<"4.size(), IsEmpty(), Element() 호출"<<"5.끝내기"<<endl;
        int choice;
        cin>>choice;
        switch (choice) {
            default:
            cout<<"잘못 입력했습니다. 다시 입력하세요"<<endl;
            break;
            
            case 1:
            {
                char name[30];
                char phone[30];
                cout<<"input name: ";
                cin>>name;
                cout<<"input phone number: ";
                cin>>phone;
                Bizcard tmp(name,phone);
                Bizcard permanent(tmp);
                bag.Push(permanent);
                break;
            }
            case 2:
            {
                bag.Pop();
                break;
            }
            case 3:
            {
                bag.ShowBizcard();//ShowBizcard 출력 횟수에 대한 수정 필요 capacity로 하면 안먹음
                break;
            }
            case 4:
            {
                int size=bag.Size();
                cout<<"size is "<<size<<endl;
                if(bag.IsEmpty()==true)
                cout<<"bag is empty"<<endl;
                else
                cout<<"bag is not empty"<<endl;
                Bizcard check=bag.Element();
                
            }
            case 5:
            return 0;
            break;
        }
               
    }
    
    }

