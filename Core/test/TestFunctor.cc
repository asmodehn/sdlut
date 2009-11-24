#include "Functor.hh"


int func0 ( )
{
    return 1;
}
int func1 ( int a )
{
    return 1+a;
}
int func2 ( int a, int b)
{
    return 1+a+b;
}
int func3 ( int a, int b, int c)
{
    return 1+a+b+c;
}
int func4 ( int a, int b, int c, int d)
{
    return 1+a+b+c+d;
}


class Operand
{
int m_testval;

Operand() : m_testval(1)
{}
    public:
int func0 ( ) { return m_testval; }
int func1 ( Operand & o) { return m_testval+o.m_testval; }
int func2 ( Operand & o, int a ) { return m_testval+o.m_testval+a; }
int func3 (Operand& o, int a, int b) { return m_testval+o.m_testval+a+b; }
int func4 (Operand& o, int a, int b, int c ) { return m_testval+o.m_testval+a+b+c; }

};

int main ( int argc, char * argv [] )
{
    //TODO
    return 0;
}
