#include<iostream>
#include<string>


using namespace std;

// !! Pointers
// 1. a pointer to an object or function (in which case the pointer is said to point to the object or function)
//    !! A pointer that points to an object represents the address of the first byte in memory occupied by the object


// 2. a pointer past the end of an object
//    !! A pointer past the end of an object represents the address of the first byte in memory after the end of the storage 
//    !! occupied by the object.

struct C
{
    int x,y;
};

// 3. the null pointer value for that type
// 4. an invalid pointer value


// !! Pointers to functions
void f(int);
void (*p1)(int) = &f;
void (*p2)(int) = f;// same as &f

int f(int n)
{
    std::cout << n << '\n';
    return n * n;
}

struct D
{
    void f(int n) { std::cout << n << '\n'; }
};

int main(int argc, char **argv)
{
    int *px = &c.x; // value of px is "pointer to c.x"
    int *pxe= px + 1; // value of pxe is "pointer past the end of c.x"
    int *py = &c.y;   // value of py is "pointer to c.y"
    if(pxe == py)
    {
        cout << " pxe is same as py" << endl;
    }

    int n ;
    int *pn = &n; // pointer to int
    struct S { int n; };
    S s = {1};
    int* sp = &s.n; // pointer to the int that is a member of s

    int a[2];
    int* p1 = a; // pointer to the first element a[0] (an int) of the array a

    int (*p)(int) = f;
    int x = p(7);

    // !! Pointers to members
   // 1. Pointers to data members
   int C:: *p = C::x; // pointer to data member m of class C
   C c = {7,8};
   std::cout << c.*p << '\n';   // prints 7
   C* cp = &c;
   cp->x = 10;
   std::cout << cp->*p << '\n'; // prints 10

   // 2. Pointers to member functions
   void (D::*pf)(int) = &D::f; // pointer to member function f of class D
   D d;
   (d.*pf)(100); // prints 100
   D* cp = &d;
   cp->*p(200); // prints 200


   // !! Constness
//   const T*	pointer to constant object
//   T const*	pointer to constant object
//   T* const	constant pointer to object
//   const T* const	constant pointer to constant object
//   T const* const	constant pointer to constant object


}