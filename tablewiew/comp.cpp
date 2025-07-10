#include "comp.h"
#include <QTextStream>
#include <QFile>
#include <QRegularExpression>
#include <algorithm>
#include <stdexcept>

using namespace std;
using namespace Qt;

//-------------------------------Comp

Comp::Comp() : name("noname"), sect("unknown"), price(0) {}
Comp::Comp(const Comp& x)
{
    name = x.name;
    sect = x.sect;
    price = x.price;
}
bool Comp::operator<(const Comp& x) const
{
    return name < x.name;
}
bool Comp::operator>(const Comp& x) const
{
    return name > x.name;
}
bool Comp::operator==(const Comp& x) const
{
    return name == x.name;
}
Comp& Comp::operator = (const Comp& x)
{
    if (this != &x)
    {
        name = x.name;
        sect = x.sect;
        price = x.price;
    }
    return *this;
}
QTextStream& operator<<(QTextStream& out, const Comp &x)
{
    out << x.name << " " << x.sect << " " << x.price << endl;
    return out;
}
QTextStream& operator>>(QTextStream& in, Comp& x)
{
    x.name.clear();
    x.sect.clear();
    QString word;
    bool isFirstWord = true;

    while (!in.atEnd())
    {
        in >> word;
        if (word.isEmpty()) continue;
        if (isFirstWord)
        {
            x.name = word;
            isFirstWord = false;
            continue;
        }
        qint64 pos = in.pos();
        QString nextWord;
        in >> nextWord;
        if (nextWord.isEmpty())
        {
            if (!x.name.isEmpty()) x.name += " ";
            x.name += word;
            break;
        }
        bool ok;
        nextWord.toDouble(&ok);
        if (ok)
        {
            x.sect = word;
            in.seek(pos);
            break;
        }
        else
        {
            if (!x.name.isEmpty()) x.name += " ";
            x.name += word;
            qint64 pos2 = in.pos();
            QString nextNextWord;
            in >> nextNextWord;
            if (nextNextWord.isEmpty())
            {
                if (!x.name.isEmpty()) x.name += " ";
                x.name += nextWord;
                break;
            }
            nextNextWord.toDouble(&ok);
            if (ok)
            {
                x.sect = nextWord;
                in.seek(pos2);
                break;
            }
            else
            {
                if (!x.name.isEmpty()) x.name += " ";
                x.name += nextWord;
                in.seek(pos2);
            }
        }
    }
    in >> x.price;
    return in;
}

//-------------------------------Bag

Bag::Bag() : name("noname"), count(0), sect("unknown") {}
Bag::Bag(const Bag& x)
{
    name = x.name;
    count = x.count;
    sect = x.sect;
}
bool Bag::operator<(const Bag& x) const
{
    return name < x.name;
}
bool Bag::operator>(const Bag& x) const
{
    return name > x.name;
}
bool Bag::operator==(const Bag& x) const
{
    return name == x.name;
}
Bag& Bag::operator = (const Bag& x)
{
    if (this != &x)
    {
        name = x.name;
        count = x.count;
        sect = x.sect;
    }
    return *this;
}
QTextStream& operator<<(QTextStream& out, const Bag& x)
{
    out << x.name << " " << x.count << " " << x.sect << " " << endl;
    return out;
}
QTextStream& operator>>(QTextStream& in, Bag& x)
{
    x.name.clear();
    QString word;
    bool numFound = false;
    bool sectionFound = false;

    while (!in.atEnd())
    {
        in >> word;
        if (word.isEmpty()) continue;
        if (!numFound)
        {
            bool ok;
            word.toInt(&ok);
            if (ok)
            {
                x.count = word.toInt();
                numFound = true;
                continue;
            }
        }
        else if (!sectionFound)
        {
            x.sect = word;
            //sectionFound = true;--------tut mb mistake--------------
            break;
        }
        if (!x.name.isEmpty())
        {
            x.name += " ";
        }
        x.name += word;
    }

    return in;
}

//----------------------------COMP

template <typename T>
COMP<T>::COMP() : a(nullptr), n(0) {}
template <typename T>
COMP<T>::~COMP()
{
    delete[] a;
}
template <typename T>
COMP<T>::COMP(int n_) : a(new T[n_]), n(n_) {}
template <typename T>
COMP<T>::COMP(const COMP<T>& x) : a(new T[x.n]), n(x.n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = x.a[i];
    }
}
template <typename T>
COMP<T>::COMP(COMP<T>&& x) : a(x.a), n(x.n)
{
    x.a = nullptr;
    x.n = 0;
}
template <typename T>
COMP<T>& COMP<T>::operator=(const COMP<T>& x)
{
    if (this != &x)
    {
        delete[] a;
        n = x.n;
        a = new T[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = x.a[i];
        }
    }
    return *this;
}
template <typename T>
COMP<T>& COMP<T>::operator=(COMP<T>&& x)
{
    if (this != &x)
    {
        delete[] a;
        a = x.a;
        n = x.n;
        x.a = nullptr;
        x.n = 0;
    }
    return *this;
}

template <typename T>
const T& COMP<T>::operator[](int ind) const
{
    if (ind < 0 || ind >= n)
        throw out_of_range("Index out of range");
    return a[ind];
}
template <typename T>
T& COMP<T>::operator[](int ind)
{
    if (ind < 0 || ind >= n)
        throw out_of_range("Index out of range");
    return a[ind];
}

template <typename T>
int COMP<T>::getcount () const
{
    return n;
}
template <typename T>
void COMP<T>::chcount (int x)
{
    if (x == n) return;

    T* new_a = new T[x];
    int copy_size = qMin(n, x);

    for (int i = 0; i < copy_size; ++i)
    {
        new_a[i] = a[i];
    }

    delete[] a;
    a = new_a;
    n = x;
}
template <typename T>
void COMP<T>::getdata(const QString& fname)
{
    QFile inf(fname);
    inf.open(QIODevice::ReadOnly);
    QTextStream in(&inf);
    in >> *this;
    inf.close();

    sort(a, a + n, [](const T& x, const T& y) { return x.name < y.name; });
}
template <typename T>
void COMP<T>::writedata (const QString& fname) const
{
    QFile outf(fname);
    outf.open(QIODevice::WriteOnly);
    QTextStream out(&outf);
    out << *this;
    outf.close();
}

template <typename T>
QTextStream& operator>>(QTextStream& in, COMP<T>& x)
{
    in >> x.n;
    in.readLine();
    delete[] x.a;
    x.a = new T[x.n];
    for (int i = 0; i < x.n; i++)
    {
        in >> x.a[i];
    }
    sort(x.a, x.a + x.n, [](const T& a, const T& b) { return a.name < b.name; });
    return in;
}
template <typename T>
QTextStream& operator<<(QTextStream& out, const COMP<T>& x)
{
    out << x.n << endl;
    for (int i = 0; i < x.n; i++)
    {
        out << x.a[i];
    }
    return out;
}

template <typename T>
COMP<T> operator+(const COMP<T>& x, const COMP<T>& y)
{
    int i = 0, j = 0, k = 0;
    COMP<T> z(x.n + y.n);
    while(i < x.n && j < y.n)
    {
        if(x[i] < y[j])
            z[k++] = x[i++];
        else if(x[i] == y[j])
        {
            z[k++] = x[i++];
            j++;
        }
        else
        {
            z[k++] = y[j++];
        }
    }
    while(i < x.n)
    {
        z[k++] = x[i++];
    }
    while(j < y.n)
    {
        z[k++] = y[j++];
    }
    z.chcount(k);

    sort(z.a, z.a + z.n, [](const T& a, const T& b) { return a.name > b.name; });

    return z;
}

template <typename T>
COMP<T> COMP<T>::search(QString tov) const
{
    COMP<T> res;
    if (n == 0)
        return res;

    T temp;
    temp.name = tov;
    T* found = lower_bound(a, a + n, temp, [](const T& a, const T& b) {return a > b;});

    if (found != a + n && *found == temp)
    {
        res.chcount(1);
        res[0] = *found;
    }

    return res;
}

template class COMP<Comp>;
template class COMP<Bag>;

template QTextStream& operator>>(QTextStream&, COMP<Comp>&);
template QTextStream& operator>>(QTextStream&, COMP<Bag>&);

template QTextStream& operator<<(QTextStream&, const COMP<Comp>&);
template QTextStream& operator<<(QTextStream&, const COMP<Bag>&);

template COMP<Comp> operator+(const COMP<Comp>&, const COMP<Comp>&);
template COMP<Bag> operator+(const COMP<Bag>&, const COMP<Bag>&);
