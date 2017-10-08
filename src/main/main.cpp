#include "sig/sigslots.h"

class A
{
public:
  sig::connector m_conn;
  void do_smth (const char *str) {using std::cout; cout << " " << std::endl;}
};

void print_s (int i, const char *str) {using std::cout; cout << i << " " << str << std::endl;}


int main(int argc, char *argv[])
{

      A a;
  using namespace std::placeholders;
    sig::signal</*int, const char *, double*/> changed;


    a.m_conn.connect_to (changed, std::bind (&A::do_smth, &a));
    changed ();
}
