# Algorithms & Data Structures (ADS)

Repository for C++ excercises for practicing algorithms & data strcutures at the University of Vienna

---

- [Algorithms & Data Structures (ADS)](#algorithms--data-structures-ads)
  - [Files](#files)
  - [Rubberducking](#rubberducking)
    - [Element](#element)
    - [Add](#add)

---

## Files

- `Clean.h` : initial base C++ header file with declarations to be implemented
- `ADS_set.h` : Linear Hashing infrastructure
- `QA.md` : C++ questions I came up with in the process
  Repository for C++ excercises for practicing algorithms & data strcutures at the University of Vienna

## Rubberducking

I am programming a data structure that stores elements and manages them using a hashing collision technique _Linear Hashing_.

The hashing is carried out by means of the key stored as part of element. It is observed and used for determining the index on which the element should be stored. This process of figuring out an index from an arbitrary value is called hashing. When 2 different keys produce the same hash value (index), we call it a collision.

In linear hashing the collision is handled in a way that whenever a collision occurs, a linked list is created on the element array. To make the process as efficient as possible, new element that caused collision is put as the first element in the linked list (head).

The data structure `ADS_Set` represents the container in which elements are stored. This data structure tracks multiple values (members):

- `table`: a pointer to the array of element pointers
- `table_size`: how many slots are there in the table (array length)
- `inserted_elements`: how many elements have been inserted so far
- `max_load_factor` : max utilizable percentage of the capacity of the table calculated as $\frac{inserted\_elements}{table\_size}$

### Element

`Element` is an interesting member. The element is defined as `Struct`. Struct is C++ construction that is just like a public class. It tends to be used for simpler data structures.

`Element` has 2 member types, a `key` of type `key_type` (a non-negative `int`) and pointer to the next `Element` type `nextPtr` which by default points to nothing `nullptr`.

Although Element suggests it just hold some value, the key part to the linear hashing approach is `nextPtr`. Thanks to this member we are able to create Linked List (just one way) without any need to declare a special structure.

### Add 


