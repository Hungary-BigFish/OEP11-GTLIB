#include <iostream>
#include <cmath>

using namespace std;

class ProgTheorem
{
protected:
    int _m, _n;

    virtual void init() = 0;
    virtual void loop_body(int i) = 0;
    virtual bool extra_loop_cond() const
    {
        return true;
    }

public:
    ProgTheorem(int a, int b):_m(a), _n(b) {}
    void execute();
    virtual ~ProgTheorem() {}
};


void ProgTheorem::execute()
{
    int i = _m;
    init();
    while (extra_loop_cond() && i <= _n)
    {
        this->loop_body(i);
        ++i;
    }
};


class Counting : public ProgTheorem
{
protected:
    int _c;

    void init()   override
    {
        _c = 0;
    }
    void loop_body(int i) override
    {
        if  (cond(i)) ++_c;
    }
    virtual bool cond(int i) const
    {
        return true;
    }
public:
    Counting(int a, int b) : ProgTheorem(a,b) {}
    int getResult() const
    {
        return _c;
    }
};

class OptLinSearch : public ProgTheorem
{
protected:
    bool _l;
    int _ind;
    void init()   override
    {
        _l = true;
    }
    void loop_body(int i) override
    {
        _l = cond(i);
        _ind = i;
    }
    bool extra_loop_cond() const override
    {
        return _l;
    }
    virtual bool cond(int i) const = 0 ;
public:
    OptLinSearch(int a, int b) : ProgTheorem(a,b) {}
    int getInd()    const
    {
        return _ind;
    }
    int getFound() const
    {
        return _l;
    }
};

class MySearch: public OptLinSearch
{
public:
    MySearch(int a) : OptLinSearch(2, sqrt(abs(a))), _x(a) { }
protected:
    int _x;
    bool cond(int i) const override { cout << " oszto: " << i << endl; return 0!=_x%i;}
};

class MyCounting : public Counting
{
public:
    MyCounting(int m, int n) : Counting(m,n) {}
protected:
    bool cond(int i) const override
    {
        MySearch  p(i);
        p.execute();

        return i>1 && p.getFound();
    }
};

int main()
{
    MyCounting  p(1,10);
    p.execute();
    cout << "prímek száma: " << p.getResult() << endl;

    return 0;
}
