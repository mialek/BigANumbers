#ifndef LICZBA_H_INCLUDED
#define LICZBA_H_INCLUDED

#include<iostream>
#include<stdexcept>
using namespace std;

class Liczba //najmniejsze przy tail
{
    struct Node
    {
        unsigned int cyfra;
        Node* prev;
        Node* next;
        Node(unsigned int c=0,Node* p=nullptr,Node* n=nullptr);
        ~Node()=default;
    };
    bool znak;
	unsigned int podstawa;
    Node* head;
    Node* tail;
    unsigned int cyfry;
    unsigned int& operator[](int indeks);
    Liczba(Node* n,unsigned int p);//tylko do uzycia wewnatrz metod
    void conc(); //do usuwania zer z poczatku
public:
    ~Liczba();
    Liczba(const Liczba& l);
    Liczba(int l=0,unsigned int p=10);
    Liczba& operator=(const Liczba& l);
    friend ostream& operator<<(ostream& os,const Liczba& l);
    friend istream& operator>>(istream& is,Liczba& l);
    void zmienPodstawe(unsigned int p=10);
    int getCyfry()const;
    void testWypisz(); //funkcja do testowania spojnosci head/next
    void testWypiszBw(); //funkcja do testowania spojnosci tail/prev
    explicit operator int()const;
    explicit operator unsigned int()const;
    Liczba operator-()const;
    Liczba& operator++();
    Liczba& operator--();
    Liczba operator++(int);
    Liczba operator--(int);
    Liczba operator+(const Liczba& l)const; 
    Liczba operator-(const Liczba& l)const; 
    Liczba operator*(const Liczba& l)const; 
    Liczba operator/(const Liczba& l)const; 
    Liczba operator%(const Liczba& l)const;
    Liczba& operator +=(const Liczba& l);
    Liczba& operator -=(const Liczba& l);
    Liczba& operator /=(const Liczba& l);
    Liczba& operator *=(const Liczba& l);
    bool operator==(const Liczba& l)const; 
	bool operator>=(const Liczba& l)const; 
    bool operator<=(const Liczba& l)const; 
    bool operator>(const Liczba& l)const; 
    bool operator<(const Liczba& l)const; 
    bool operator!=(const Liczba& l)const; 

};

#endif // LICZBA_H_INCLUDED
