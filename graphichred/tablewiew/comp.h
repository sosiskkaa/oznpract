#ifndef COMP_H
#define COMP_H
#include <QTextStream>
#include <QFile>
#include <QObject>

using namespace std;
using namespace Qt;

struct Comp
{
    QString name;
    QString sect;
    int price;

    Comp();
    Comp(const Comp& x);
    bool operator<(const Comp& x) const;
    bool operator>(const Comp& x) const;
    bool operator==(const Comp& x) const;
    Comp&operator = (const Comp& x);
    friend QTextStream& operator<<(QTextStream& out, const Comp& x);
    friend QTextStream& operator>>(QTextStream& in, Comp& x);
};

struct Bag
{
    QString name;
    int count;
    QString sect;

    Bag();
    Bag(const Bag& x);
    bool operator<(const Bag& x) const;
    bool operator>(const Bag& x) const;
    bool operator==(const Bag& x) const;
    Bag&operator = (const Bag& x);
    friend QTextStream& operator<<(QTextStream& out, const Bag& x);
    friend QTextStream& operator>>(QTextStream& in, Bag& x);
};

template <typename T>
class COMP
{
    T* a;
    int n;
    QString table_title;
public:
    COMP();
    ~COMP();
    COMP(int n_);
    COMP(const COMP<T>& x);
    COMP(COMP<T>&& x);

    COMP<T>& operator=(const COMP<T>& x);
    COMP<T>& operator=(COMP<T>&& x);

    const T& operator[](int ind) const;
    T& operator[](int ind);

    int getcount () const;
    void chcount (int x);
    void getdata(const QString& fname);
    void writedata (const QString& fname) const;
    COMP<T> search(QString tov) const;

    template<typename U>
    friend QTextStream& operator>>(QTextStream& in, COMP<U>& x);
    template<typename U>
    friend QTextStream& operator<<(QTextStream& out, const COMP<U>& x);
    template<typename U>
    friend COMP<U> operator+(const COMP<U>& x, const COMP<U>& y);
};

#endif // COMP_H
