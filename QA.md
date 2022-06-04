> what does using keyword mean within Class?
we can use the member of different class 
but how? 

> what is a `friend`
friend is a construct that gives access to private members of a different class 

>why use const as argument 
 it means that it cannot be modified in the function.

> `const` at the end of statement
it says "Don't you dare __changing__ a member variable" 
when a member variable of a class is changed -> error  
e.g. can be a getter 

> why do we make 2 void `ADS_set<Key, N>::add(const key_type &key)` ?
we don't notice `add` after `::` that means this is a declaration of add method 

> what does index{h(key)} mean? 

> why not just use regular enums but class enums instead? 
for 2 enums I cannot specify the same members e.g.:
`enum1 = {First, Last }; enum2 = {First, Last } //=> error`
enums are not typesafe 

> how do we access class enums in C++? 
using `::` i.e. e.g. `Mode::used` => because it's class 

> what is assignment with curly braces called and what does it do? e.g. `Vec3 foo = {1,2,3};`
it's called initialization, allowed for aggregate only, POD (Plain Old Data type)

> what is POD (Plain Old Data type)
it's a datatype that DOES NOT have a user defined constructor
```C++
struct vector3D //this struct is NOT an aggregate (non-POD class)
{
   int x;
   int y;
   int z;
   vector3D(int, int, int){} //user-defined constructor!
};

//since vector3D is NOT an aggregate, so we CANNOT initialize it as
vector3D p = {1,2,3}; //error
```
whereas 
```C++
struct point3D //this struct is an aggregate (POD class)
{
   int x;
   int y;
   int z;
};

//since point3D is an aggregate, so we can initialize it as
point3D p = {1,2,3};
```

> `++current_size` vs `current_size++`
the difference is when it will be incremented with respect to processing 
`++current_size` : __before__ processing the current statement (no temporaries)
`current_size++` : __after__ processing the current statement (temp variable made)

> why use `{}` for assignment instead of `=`
to prevent narrowing and it's preferable every time 
otherwise using `int x = 7.9` results in `x=7` 

> what does for(;;){} mean? 
it's an infinite for loop equivalent to `while(true)`

>instantiation with x{}()? 

> in switch statement do we need break after return? 

> what is the meaning of `:` in 
Member Initializer List (only for constructors) -> it initializes it like regular except
* constructor is called once 
* regular constructor creates an object before the code within the brackets is executed
* duuring constructor call the number is already initialized (not true for regular assignment)
"the constructors will be called once and the object will be constructed and initialized in one operation"
vs
```C++
Foo(int num): bar(num) {}; //  Member Initializer List
```
vs. 
```C++
Foo(int num){bar = num;}
```

> where to use Member Initializer List over regular constructor assignment? 
in case that: 
* `const` is used 
* for reference data member
* we use C++11

>what is swap? 
exchanging 2 variables, built in std::swap can only swap the same type e.g. int and int 

> lvalue vs rvalue 
1. simplification: lvalue is on the left of an assignment expression, rvalue is on the right of an expression 
e.g. `int myInt = 23;`  -> `int myInt` := lvalue `23;` := rvalue
2. * lvalue : have some storage attatched to them => `&`
   * rvalue : temporary placeholders => `&&`

> why do we see a lot of `const` in the function parameter signature e.g. `void PrintName(const std::string& name)`
`const` makes it possible to pass both rvalue and lvalue to the an expression 
-> without the `const`, we would only be able to accept lvalues 

> do we have a way to only accept an rvalue as a parameter? 
yes, the _rvalue reference_ which uses `&&` e.g. `void PrintName(std::string&& name)`

>why do we even care aout differentiating between `rvalue` and `lvalue`
we can steal resources from rvalue (temporary) -> performance

```C++

string str1 = "Example1"
string str2 = "Example2"

str1 + str2 // is temporary object, a.k.a. rvalues

```
move semantics (moving pointers around, making shallow copies) -> https://www.youtube.com/watch?v=ehMg6zvXuMY

---
> What is lhs and rhs ? 

assumption: lhs : left-hand side rhs: righ-hand side? 
-> it's true  Left Hand Side and Right Hand Side in this context
source: https://stackoverflow.com/questions/48493496/what-is-lhs-rhs-and-how-is-it-being-used-in-this-program


---
> what does `explicit` mean ? 
C++ may perform implicit conversion of a data type without need to cast it (convert from one data type to another) => but hold on, just 1 conversion is allowed and that's it e.g. "My String" is not a std::string but an array of chars 
-> `explicit` disables the implicit conversion
[watch for refresher](https://www.youtube.com/watch?v=Rr1NX1lH3oE) 

---
> how to instantiate objects in C++ 
[refresher](https://www.youtube.com/watch?v=Ks97R1knQDY)
IN C++ we get to choose where to store variables  

- Stack: controlled by scope in which variable is declared, memory freed as soon as the scope is left
- Heap: using `new` in heap we create and it stays there until we delete it 

if default constructor exists we can instantiate it as `Entity entity`
```CPP
...
public:
   Entity(): name("unkown"){}; // default constructor
...
int main(){
   Entity entity; // valid code
}

```
-> if I can create an object like this, do it like that it's the fastest!
scope can be: if statement, `{}`, function etc.

---
> what happens when you use `new` keywoard? 
`new` is operator -> just like `+` `-` etc.
usually calls C `malloc()` allocating the memory

it's slow because the following steps are taken: 
1. determine how much memory is needed for a type
2. ask for the memory
3. find the block in memory 
4. return pointer to the address 

when we use `new` **pointer** is returned

❗we need to delete it using `delete` (calls C function `free()`)
e.g.: 
```CPP
Entity* entity = new Entity("Hynek");
...
delete entity;

```

note if we call `int* b = new int[]` we need to call `delete[] b`



> what is an operator
symbol we use instead of function like:
`+` `-` `=` `->` `&` `<<` `new` `delete` `,` etc.
[full list of C++ operators](https://en.cppreference.com/w/cpp/language/operators)


> different uses of `const` 
1. as first : can't change contents 
2. after * : can't change pointer 
3. after method: can't change members of class
4. 

```CPP
const int* ptr = new int; // can't change data, but can pointer
int const* ptr2 = new int; // the same thing

int * const ptr3 = new int; // can't change pointer, can change data

const int * const ptr4 = new int; //can't change neither  

int method() const {...} // method can't modify member variable

void Function (const Entity& e){...} // can't reassign the entity value

const int* const getX() const {...} // can't change member variables, or reassign pointer or data 

```

> how to modify a variable within `const` method? 
by marking it `mute` e.g.
```CPP
mutable int x = 23; // mutate the variable within const method
```

> using `&` a reference 
```CPP
int a{3};

int &ref = a; // alias for a, use it as normal value!
int* ptr = &a; // get memory address

void Function(int &x) // pass by value, no problem
{
   doSomething(x); //use it like normal value
} 
```
passing value to function value, it automatically changes to pointer and then dereferences

> how to use valgrind 
use valgrind to check for memory `valgrind --log-file=log.txt ./a.out`

> what values in Valgrind output to consider? 
* "definitely lost"
* "indirectly lost"

> what are some possible mistakes uncovered by Valgrind? 
* uninitialized values on stack 
* use of uninitialized values 
* access to forbidden memory 
* access to forbidden memory on heap 
* incorrect delete 
* use after free

> what is an iterator? 
an object that can iterate through a collection that can be thought of as a the generalization of a pointer 
* `it.begin()` points at the first element 
* `it.end()` points at element after the last (n+1) 
-> $[it.begin(), it.end())$
-> a pointer to value
3 conditions: 
1. dereferencable 
2. reassignable `it1 = it2`
3. comperable `it1 == it2` `it1 != it2`
4. incrementable `it++` `it--`

> what are Member Initializer list and constructor initializer list 
it's 1 of 2 ways to initialize object members 
imagine a class with 2 private variables `member_name` and `member_age`
the regular way to do this:
```CPP
//regular constructor
Entity(const std::string &name, int &age){
   member_name = name
   member_age = age
}
```
or using initializer object member 
```CPP
Entity(): member_name("Hynek"), member_age(24) {}
```
❗members are initialized in the order they have been declared in the class not in the initializer list 

why to use it: to save space, it's more readable, leave the `{}` for some more sofisticated logic

refresher: https://www.youtube.com/watch?v=1nfuYMXjZsA

> what is the copy constructor? 
In C++ if we assign, we copy e.g.:
```CPP
int x = 2;
int y = x; // copy of x is being made
y++ // y == 3, x==2
```
the underlying copy process is managed by Copy constructor 
-> we construct a new object of the same type and same value (we make copy)

e.g.: for string we take a reference of the thing we are copying a.k.a. the `other`
```CPP
String(const String& other): m_stuff(stuff){}
```

if we DON'T want to allow copying do
```CPP
String(const String& other) = delete;
```
