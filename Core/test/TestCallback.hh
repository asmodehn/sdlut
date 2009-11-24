#ifndef TESTCALLBACK_HH
#define TESTCALLBACK_HH

#include <memory> // for auto_ptr

///defining classes used in both test callback and test adaptor
class Called
{

int m_testval;
public:
Called() : m_testval(1)
{}
    public:
int func0 ( ) { return m_testval; }
int func0 ( ) const { return m_testval; }
int func1 (  int a ) { return m_testval+a; }
int func1 (  int a ) const { return m_testval+a; }
int func2 ( int a, int b) { return m_testval+a+b; }
int func2 ( int a, int b) const { return m_testval+a+b; }
int func3 ( int a, int b, int c ) { return m_testval+a+b+c; }
int func3 ( int a, int b, int c ) const { return m_testval+a+b+c; }

};

///defining data used in both test callback and test adaptor
std::auto_ptr<Core::Callback0Base<int> > cbtest0;
std::auto_ptr<Core::Callback0constBase<int> > cbtest0c;
std::auto_ptr<Core::Callback1Base<int,int> > cbtest1;
std::auto_ptr<Core::Callback1constBase<int,int> > cbtest1c;
std::auto_ptr<Core::Callback2Base<int,int,int> > cbtest2;
std::auto_ptr<Core::Callback2constBase<int,int,int> > cbtest2c;
std::auto_ptr<Core::Callback3Base<int,int,int,int> > cbtest3;
std::auto_ptr<Core::Callback3constBase<int,int,int,int> > cbtest3c;

#endif
