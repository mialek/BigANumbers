#include "Liczba.h"

Liczba::Node::Node(unsigned int c, Node* p, Node* n)
{
    cyfra=c;prev=p;next=n;
}

Liczba::~Liczba()
{
    Node* walker=head,*killer;
    while(walker)
    {
        killer=walker;
        walker=walker->next;
        delete killer;
    }
    head=nullptr;
    tail=nullptr;
    cyfry=0;
}

Liczba::Liczba(Node* n,unsigned int p)
{
    if (n)
        cyfry = 1;
    else
        cyfry = 0;
    znak = false;
    podstawa = p;
    head = n;
    tail = n;
}

void Liczba::conc()
{
    if (head && !tail || !head && tail)
        throw runtime_error("Niespojna instancja");
    Node* killer=nullptr;
    while (head != tail && head->cyfra == 0)
    {
        killer = head;
        head = head->next;
        head->prev = nullptr;
        delete killer;
        cyfry--;
    }
}

Liczba::Liczba(const Liczba& l)
{
    podstawa=l.podstawa;
    cyfry=l.cyfry;
    znak=l.znak;
    Node* walker=l.head;
    Node* prev=nullptr;
    head = nullptr;
    tail = nullptr;
    if (walker)
    {
        head = new Node(walker->cyfra,nullptr,nullptr);
        tail = head;
        walker = walker->next;
        prev = head;
    }
    while (walker)
    {
        tail = new Node(walker->cyfra, prev, nullptr);
        prev->next = tail;
        prev = tail;
        walker = walker->next;
    }
}

Liczba::Liczba(int l, unsigned int p)
{
    znak = false;
    cyfry = 0;
    if (p == 0)
        throw logic_error("Nieprawidlowa podstawa");
    if (p == 1)
        throw runtime_error("Nie zaimplementowano podstawy 1");
    podstawa = p;
    if (l < 0)
    {
        l = -l;
        znak = true;
    }
    int modul=0;
    Node* temp = nullptr;
    modul = l % p;
    head = new Node(modul, nullptr, nullptr);
    cyfry++;
    tail = head;
    l /= p;
    while (l > 0)
    {
        modul = l % p;
        l /= p;
        temp = head;
        head = new Node(modul, nullptr, temp);
        if (!tail)
            tail = head;
        temp->prev = head;
        cyfry++;
    }
}

void Liczba::testWypisz()
{
    Node* walker = head;
    if (znak)
        cout << "-";
    while (walker)
    {
        cout<<" "<< walker->cyfra;
        walker = walker->next;
    }
    cout << "cyfry: " << cyfry<<endl;
}

void Liczba::testWypiszBw()
{
    Node* walker = tail;
    while (walker)
    {
        cout<<" "<< walker->cyfra;
        walker = walker->prev;
    }
    cout << "cyfry: " << cyfry << endl;
}

Liczba::operator int()const
{
    Node* walker = tail; 
    int ret = 0;
    int indeks = 0;
    while (walker)
    {
        int mnoznik=1;
        for (int i = 0; i < indeks; i++)
            mnoznik = mnoznik * podstawa;
        ret += (walker->cyfra) * mnoznik;
        walker = walker->prev;
        indeks++;
    }
    if (znak)
        ret = -ret;
    return ret;
}

Liczba::operator unsigned int()const
{
    Node* walker = tail;
    unsigned int ret = 0;
    unsigned indeks = 0;
    while (walker)
    {
        unsigned int mnoznik = 1;
        for (int i = 0; i < indeks; i++)
            mnoznik = mnoznik * podstawa;
        ret += (walker->cyfra) * mnoznik;
        walker = walker->prev;
        indeks++;
    }
    return ret;
}

Liczba& Liczba::operator=(const Liczba& l)
{
    if (this == &l)
        return *this;
    {
        Node* walker = head, * killer;
        while (walker)
        {
            killer = walker;
            walker = walker->next;
            delete killer;
        }
        head = nullptr;
        tail = nullptr;
        cyfry = 0;
    }
	podstawa = l.podstawa;
	cyfry = l.cyfry;
	    znak=l.znak;
	Node* walker = l.head;
	Node* prev = nullptr;
	head = nullptr;
	tail = nullptr;
	if (walker)
	{
        head = new Node(walker->cyfra, nullptr, nullptr);
        tail = head;
		walker = walker->next;
		prev = head;
	}
	while (walker)
	{
		tail = new Node(walker->cyfra, prev, nullptr);
        prev->next = tail;
		prev = tail;
		walker = walker->next;
	}
    return *this;

}

void Liczba::zmienPodstawe(unsigned int p)
{
    if (p == 0)
        throw logic_error("Nieprawidlowa podstawa");
    if (p == 1)
        throw runtime_error("Nie zaimplementowano podstawy 1");
    if (p == podstawa)
        return;
    Liczba kopia(*this);
    Liczba nowa(nullptr, p);
    kopia.znak = false;
    Liczba dzielnik(p, podstawa);
    Node* temp = nullptr;
    Liczba limit(0, podstawa);
    while (kopia > limit || nowa.cyfry==0)
    {
        Liczba modul(0, podstawa);
        modul = kopia % dzielnik;
        temp = nowa.head;
        nowa.head = new Node((unsigned int)modul, nullptr, temp);
        if (!nowa.tail)
            nowa.tail = nowa.head;
		if (temp)
			temp->prev = nowa.head;
        nowa.cyfry++;
        kopia = kopia / dzielnik;
    }
    nowa.znak=(*this).znak;
    (*this) = nowa;
}

int Liczba::getCyfry()const
{
    return cyfry;
}

ostream& operator<<(ostream& os, const Liczba& l) //magic number galore!
{
    Liczba::Node* walker = l.head;
    string ret="";
    if (l.znak)
        ret += '-';
    while (walker)
    {
        if (walker->cyfra < 10)
            ret += (char(walker->cyfra + '0'));
        else if (walker->cyfra > 9 && walker->cyfra < 36)
            ret += (char((walker->cyfra) + 'A'-10));
        else
        {
            int over = 0;
            int digit = walker->cyfra-10;
            while (digit > 25)
            {
                over++;
                digit -= 26;
            }
            ret+=(char(digit + 'A'));
            for (over; over > 0; over--)
                ret += '*';
        }
        walker = walker->next;
    }
    os << ret;
    os << " (" << l.podstawa << ")";
    return os;
}
istream& operator>>(istream& is, Liczba& l)
{
    string temp;
    is >> temp;
    int indeks = 0;
    Liczba bufor(nullptr, l.podstawa);
    if (temp.size() && temp[0] == '-')
    {
        bufor.znak = true;
        indeks++;
    }
    Liczba::Node* trailer = nullptr;
    while (indeks < temp.size())
    {
        char cyfra = temp[indeks];
        if (cyfra >= '0' && cyfra <= '9')
        {
            if ((int)(cyfra - '0') >= bufor.podstawa)
                throw logic_error("Nieprawidlowa cyfra");
            bufor.tail = new Liczba::Node((int)(cyfra - '0'), trailer, nullptr);
            if (!bufor.head)
                bufor.head = bufor.tail;
            if (trailer)
                trailer->next = bufor.tail;
            trailer = bufor.tail;
            bufor.cyfry++;
        }
        else if ((cyfra >= 'A' && cyfra <= 'Z') || (cyfra>='a' && cyfra <= 'z'))
        {
            int cyfraF = 0;
            if (cyfra >= 'a' && cyfra <= 'z')
            {
                cyfraF = (int)cyfra - (int)'a' + 10;
            }
            else
            {
                cyfraF = (int)cyfra - (int)'A' + 10;
            }
            
            int offset = 1;
            while (indeks + offset < temp.size() && (temp[indeks + offset] == '*'))
            {
                cyfraF = cyfraF + (int)'Z' - (int)'A'+1;
                offset++;
            }
            
            indeks = indeks + offset - 1;
            if (cyfraF >= bufor.podstawa)
                throw logic_error("Nieprawidlowa cyfra");
            bufor.tail = new Liczba::Node(cyfraF, trailer, nullptr);
            if (!bufor.head)
                bufor.head = bufor.tail;
            if (trailer)
                trailer->next = bufor.tail;
            trailer = bufor.tail;
            bufor.cyfry++;
        }
        else
        {
            throw logic_error("Nieprawidlowa cyfra");
        }
        indeks++;
    }
    bufor.conc();
    l = bufor;
    return is;
}

unsigned int& Liczba::operator[](int indeks)
{
    if (indeks > cyfry)
        throw logic_error("Nie ma takiej cyfry");
    Node* walker = head;
    for (; indeks > 0; indeks--)
        walker = walker->next;
    return walker->cyfra;
}

Liczba& Liczba::operator++()
{
    Liczba p(1, podstawa);
    (*this) = (*this) + p;
    return *this;
}
Liczba& Liczba::operator--()
{
    Liczba p(1, podstawa);
    (*this) = (*this) - p;
    return *this;
}
Liczba Liczba::operator++(int)
{
    Liczba kopia(*this);
    ++(*this);
    return kopia;
}
Liczba Liczba::operator--(int)
{
    Liczba kopia(*this);
    --(*this);
    return kopia;
}

Liczba Liczba::operator+(const Liczba& l) const
{
    unsigned int retP=podstawa;
    Liczba ret(nullptr,retP);
    Liczba kopiaL(l);
    Liczba kopiaT((*this));
    kopiaT.znak = false;
    kopiaL.znak = false;
    kopiaL.zmienPodstawe(retP);
    Node* walker = nullptr, * ranger = nullptr;
    if (znak)
    {
        if (!l.znak)
        {
            return kopiaL - kopiaT;
        }
        else
        {
            walker = kopiaT.tail;
            ranger = kopiaL.tail;
            ret.znak = true;
        }
    }
    else
    {
        if (!l.znak)
        {
            walker = kopiaT.tail;
            ranger = kopiaL.tail;
            ret.znak = false;
        }
        else
        {
            return kopiaT-kopiaL;
        }
    }
    unsigned int carry=0;
    Node* temp = nullptr;
    while (walker || ranger || carry>0)
    {
        if (walker && ranger)
        {
            carry += walker->cyfra + ranger->cyfra;
            walker = walker->prev;
            ranger = ranger->prev;
        }
        else if (walker)
        {
            carry += walker->cyfra;
            walker = walker->prev;
        }
        else if(ranger)
        {
            carry += ranger->cyfra;
            ranger = ranger->prev;
        }
        ret.head = new Node(carry % retP, nullptr, temp);
		if (temp)
			temp->prev = ret.head;
        if (!ret.tail)
            ret.tail = ret.head;
        temp = ret.head;
        carry /= retP;
        ret.cyfry++;
    }
    return ret;
}

Liczba Liczba::operator-(const Liczba& l) const
{
    unsigned int retP = podstawa;
    Liczba kopiaT((*this));
    Liczba kopiaL(l);
    Node* walker = nullptr, * ranger = nullptr;
    Liczba ret(nullptr, retP);
    kopiaL.zmienPodstawe(retP);
    kopiaT.znak = false;
    kopiaL.znak = false;
    if (kopiaT < kopiaL)
    {
        
        if ((*this).znak)
        {
            if (l.znak)
            {
            walker = kopiaL.tail;
            ranger = kopiaT.tail;
            ret.znak = false;
            }
            else
            {
                ret = kopiaT + kopiaL;
                ret.znak = true;
                return ret;
            }
        }
        else
        {
            if (l.znak)
            {
                ret = kopiaT + kopiaL;
                ret.znak = false;
                return ret;
            }
            else
            {
                walker = kopiaL.tail;
                ranger = kopiaT.tail;
                ret.znak = true;
            }
        }
        
    }
    else if (kopiaT > kopiaL)
    {
        if ((*this).znak)
        {
            if (l.znak)
            {
                walker = kopiaT.tail;
                ranger = kopiaL.tail;
                ret.znak = true;
            }
            else
            {
                ret = kopiaT + kopiaL;
                ret.znak = true;
                return ret;
            }
        }
        else
        {
            if (l.znak)
            {
                ret = kopiaT + kopiaL;
                ret.znak = false;
                return ret;
            }
            else
            {
                walker = kopiaT.tail;
                ranger = kopiaL.tail;
                ret.znak = false;
            }
        }
    }
    else
    {
        if ((*this).znak)
        {
            if(l.znak)
                return Liczba(0, retP);
            else
            {
                ret = kopiaT + kopiaT;
                ret.znak = true;
                return ret;
            }
        }
        else
        {
            if (l.znak)
            {
                ret = kopiaT + kopiaT;
                ret.znak = false;
                return ret;
            }
            else
                return Liczba(0, retP);
        }
        
    }
    Node* trailer = nullptr;
    while (ranger)
    {
        if (walker->cyfra < ranger->cyfra)
        {
            Node* pamiec=walker;
            walker = walker->prev;
            while (walker->cyfra == 0)
                walker = walker->prev;
            while (walker != pamiec)
            {
                walker->cyfra--;
                walker = walker->next;
                walker->cyfra += retP;
            }
        }
        
        ret.head = new Node(walker->cyfra - ranger->cyfra,nullptr,trailer);
        if (!ret.tail)
            ret.tail = ret.head;
        if (trailer)
            trailer->prev = ret.head;
        trailer = ret.head;
        walker = walker->prev;
        ranger = ranger->prev;
        ret.cyfry++;
    }
    while (walker)
    {
        ret.head = new Node(walker->cyfra, nullptr, trailer);
        if (!ret.tail)
            ret.tail = ret.head;
        if (trailer)
            trailer->prev = ret.head;
        trailer = ret.head;
        walker = walker->prev;
        ret.cyfry++;
    }
    while (ret.head && ret.head->cyfra == 0)
    {
        Node* killer = ret.head;
        ret.head = ret.head->next;
        ret.head->prev = nullptr;
        delete killer;
        ret.cyfry--;
    }
    if (ret.head == nullptr) //prawdopodbnie niepotrzebne
        ret.tail = nullptr;
    return ret;
}

Liczba Liczba::operator*(const Liczba& l) const 
{
    if (!head || !l.head)
        throw logic_error("Pusta lista w *");
    if (!tail || !l.tail)
        throw runtime_error("Niespojna instancja w *");
    unsigned int retP = podstawa;
    Liczba lKopia(l);
    lKopia.znak = false;
    lKopia.zmienPodstawe(retP);
    Liczba ret(0, retP);
    Liczba wieksza(nullptr, retP);
    Liczba mniejsza(nullptr, retP);
    if (lKopia.cyfry > cyfry)
    {
        wieksza = lKopia;
        mniejsza = *this;
    }
    else
    {
        wieksza = *this;
        mniejsza = lKopia;
    }
    mniejsza.znak = 0;
    wieksza.znak = 0;
    Liczba limit(0, retP); 
	while (mniejsza != limit)
	{
		ret = ret + wieksza;
		mniejsza--;
	}
    ret.znak = !znak != !l.znak; //prowizoryczny logiczny xor
    return ret;
}

Liczba Liczba::operator/(const Liczba& l) const 
{
    if (!head || !l.head)
        throw logic_error("Pusta lista w /");
    if (!tail || !l.tail)
        throw runtime_error("Niespojna instancja w /");
    unsigned int retP = podstawa;
    Liczba ret(0, retP);
    Liczba dzielona(*this);
    dzielona.znak = false;
    Liczba dzielnik(l);
    dzielnik.znak = false;
    dzielnik.zmienPodstawe(retP);
    {
        Liczba zero(0, retP);
        if (dzielnik == zero)
            throw logic_error("Dzielenie przez zero");
    }
    while (dzielona >= dzielnik)
    {
        ++ret;
        dzielona = dzielona - dzielnik;
    }
    ret.znak = !znak != !l.znak;
    return ret;
}

Liczba Liczba::operator%(const Liczba& l)const
{
    if (!head || !l.head)
        throw logic_error("Pusta lista w %");
    if (!tail || !l.tail)
        throw runtime_error("Niespojna instancja w %");
    unsigned int retP = podstawa;
    Liczba dzielona(*this);
    dzielona.znak = false;
    Liczba dzielnik(l);
    dzielnik.znak = false;
    dzielnik.zmienPodstawe(retP);
    while (dzielona >= dzielnik)
    {
        dzielona = dzielona - dzielnik;
    }
    return dzielona;
}

Liczba& Liczba::operator +=(const Liczba& l)
{
    (*this) = (*this) + l;
    return (*this);
}
Liczba& Liczba::operator -=(const Liczba& l)
{
    (*this) = (*this) - l;
    return (*this);
}
Liczba& Liczba::operator /=(const Liczba& l)
{
    (*this) = (*this) / l;
    return (*this);
}
Liczba& Liczba::operator *=(const Liczba& l)
{
    (*this) = (*this) * l;
    return (*this);
}

Liczba Liczba::operator-() const
{
    Liczba r(*this);
    r.znak = !znak;
    return r;
}

bool Liczba::operator==(const Liczba& l) const
{
    Node* walker = head, *ranger;
    Liczba kopia(l);
    if (podstawa != l.podstawa)
        kopia.zmienPodstawe(podstawa);
    if (cyfry != kopia.cyfry)
        return 0;
    ranger = kopia.head;
    if (cyfry == 1 && kopia.cyfry == 1 && walker->cyfra == 0 && ranger->cyfra == 0)
        return 1;
    if (znak != kopia.znak)
        return 0;
    while (walker)
    {
        if (walker->cyfra != ranger->cyfra)
            return 0;
        walker = walker->next;
        ranger = ranger->next;
    }
    return 1;

}

bool Liczba::operator>=(const Liczba& l) const
{
    if ((*this) > l || (*this) == l)
        return 1;
    return 0;
}

bool Liczba::operator<=(const Liczba& l) const
{
    if ((*this) > l)
        return 0;
    return 1;
}

bool Liczba::operator>(const Liczba& l) const
{
    Liczba kopia(l);
    if (podstawa != l.podstawa)
        kopia.zmienPodstawe(podstawa);
    Node* walker = head, * ranger = kopia.head;
    if (cyfry == 1 && (kopia.cyfry) == 1 && (walker->cyfra) == 0 && (ranger->cyfra) == 0)
        return 0;
    if (znak && !l.znak)
        return 0;
    if (!znak && l.znak)
        return 1;
	if (znak)
	{
		if (cyfry > kopia.cyfry)
			return 0;
		if (cyfry < kopia.cyfry)
			return 1;
        walker = kopia.head;
        ranger = head;
	}
	else
	{
		if (cyfry > kopia.cyfry)
			return 1;
		if (cyfry < kopia.cyfry)
			return 0;
	}
    while (walker)
    {
        if (walker->cyfra > ranger->cyfra)
            return 1;
        else if (walker->cyfra < ranger->cyfra)
            return 0;
        walker = walker->next;
        ranger = ranger->next;
    }
    return 0;
}

bool Liczba::operator<(const Liczba& l) const
{
    if ((*this) > l || (*this) == l)
        return 0;
    return 1;
}

bool Liczba::operator!=(const Liczba& l) const
{
    if ((*this) == l)
        return 0;
    return 1;
}
