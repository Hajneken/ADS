// macros
#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

/*
-----------------
SEPARATE CHAINING
-----------------
author: Hynek Zemanec
-----------------
Conventions:
* snake_case for member variables
* camelCase for everything else
-----------------
Specs: https://cewebs.cs.univie.ac.at/algodat/ss22/index.php?m=D&t=info&c=show&CEWebS_what=Spezifikation
*/

/* ADS_set is a container for elements (a simplification "std::set" and "std::unordered_set")
Elements are identified by a key. (the entire stored element serves as the key)

insertion of existing values is ignored
N: the initial size of the hash table */
template <typename Key, size_t N = 7>
class ADS_set
{

public:
    class Iterator;
    using value_type = Key; // Key is the type of the key
    using key_type = Key;   // Key is the type of the element
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t; // the size of something (positive ints)
    using difference_type = std::ptrdiff_t;
    using const_iterator = Iterator;
    using iterator = const_iterator;
    using key_equal = std::equal_to<key_type>; // comparse hashes
    using hasher = std::hash<key_type>;        // struct that can hash any data type

private:
    /*
    nextPtr: pointer to the adjecent element (that hashed to the same index)
    */
    struct Element
    {
        key_type key;
        Element *nextPtr{nullptr};
    };

    Element **table{nullptr};       // pointer to the array of pointers
    size_type table_size{0};        // how much room there is
    size_type inserted_elements{0}; // how many elements have been inserted
    float max_load_factor{0.7};     // recommended inserted_elements/table_size

    /*
    Helper function used in insert() method to add element (key) to the table.
    Returns pointer to the added element
    */
    Element *add(const key_type &key);

    /*
    checks if the position is occupied, finds and returns pointer to a searched element based on key_type
    */
    Element *locate(const key_type &key) const;

    /*
    Calculates if the table is large enough to fullfill max load factor 0.7 and enlarges the table and rehashes the values accordingly
    */
    void reserve(size_type n);

    /*
    Hashing function
    */
    size_type hash(const key_type &key) const;

    /*
    Rehash all values from the old table to conform to the new table
    */
    void rehash(size_type n);

public:
    /* ------- CONSTRUCTORS ------- */

    /*
    Default constructor. empty container (an array) of Element pointers, nullptr by default
    */
    ADS_set() : table{new Element *[N] {}}, table_size{N}, inserted_elements{0}
    {
        for (size_t index = 0; index < N; ++index)
        {
            table[index] = nullptr; // there may be otherwise leftover garbage
        }
    };

    /*
    initializer list constructor: Creates a container containing the elements from ilist. The elements are inserted in the order specified in ilist.
    */
    ADS_set(std::initializer_list<key_type> ilist) : ADS_set{}
    {
        insert(ilist);
    }

    /*
    Range constructor. Creates a container containing the elements from the range `[first, last]`. The elements are inserted in the given order (starting with first). e.g. first = 1, last = 5 => [1, 2, 3, 4, 5] Complexity: Hashing: O(range_size)
    */
    template <typename InputIt>
    ADS_set(InputIt first, InputIt last) : ADS_set{}
    {
        insert(first, last);
    }

    /* PH2: copy constructor */
    ADS_set(const ADS_set &other) : ADS_set{}
    {
        reserve(other.inserted_elements);
        for (const auto &key : other)
        {
            add(key);
        }
    };

    /*
    PH2: Destructor: The destructors of the stored elements are called and the used memory space is completely freed. Complexity: O(size)
    */
    ~ADS_set()
    {
        // free up memory from all buckets first
        for (size_type index{0}; index < table_size; ++index)
        {
            if (table[index] != nullptr)
            {
                Element *currentElement = table[index];
                while (currentElement)
                {
                    Element *nextPtr = currentElement->nextPtr;
                    delete (currentElement);
                    currentElement = nextPtr;
                }
                table[index] = nullptr;
            }
        }
        delete[] table;
    };

    /* ------- PUBLIC METHODS ------- */
    /*
    Inserts the elements from ilist. The elements are inserted in the order specified in ilist. Complexity: O(ilist_size)
    */
    void insert(std::initializer_list<key_type> ilist)
    {
        if (!ilist.size())
        {
            return;
        }
        insert(ilist.begin(), ilist.end());
    }

    /*
    PH2: Inserts key.
    Return value: A std::pair consisting of an iterator and a bool.
    iterator: points to the inserted element if an element was inserted, or to the existing element with the same key if no element was inserted.
    bool: true if an element was inserted, false otherwise. hashing O(1)  */
    std::pair<iterator, bool> insert(const key_type &key)
    {
        Element *element{locate(key)};
        if (element) // element exists?
        {
            return {iterator{table, element, hash(key), table_size}, false};
        }

        // check with load factor condition and insert new element
        reserve(inserted_elements + 1);
        return {iterator{table, add(key), hash(key), table_size}, true};
    }

    /*
     Return value: Number of inserted elements that are stored in the container.
    */
    size_type size() const
    {
        return inserted_elements;
    }

    /*
    true if size()==0, false otherwise.
    */
    bool empty() const
    {
        return inserted_elements == 0;
    }

    /*
    Return value: The number of elements in the container with key ( can be either 0 or 1). Complexity: hashing O(1)
    */
    size_type count(const key_type &key) const
    {
        if (locate(key))
        {
            return 1;
        }
        return 0;
    }

    /*
    Inserts the elements from the range [first, last[ in the given order (starting with first).
    Internally uses add() method. Complexity: Hashing: O(range_size)
    */
    template <typename InputIt>
    void insert(InputIt first, InputIt last);

    /*
    PH2: Removes all elements from the container. Complexity: O(size)
    */
    void clear()
    {
        ADS_set temp;
        swap(temp);
    }

    /*
    PH2: Removes the element key.
    Return value: number of deleted elements (0 or 1).
    For static hash procedures, it is not necessary to reduce an enlarged table again.
    */
    size_type erase(const key_type &key)
    {
        Element *elementPtr{table[hash(key)]};
        Element *auxElementPtr{nullptr};

        while (elementPtr)
        {
            if (key_equal{}(elementPtr->key, key))
            {
                if (auxElementPtr)
                {
                    auxElementPtr->nextPtr = elementPtr->nextPtr;
                }
                else
                {
                    table[hash(key)] = elementPtr->nextPtr;
                }

                delete elementPtr;
                --inserted_elements;

                return 1;
            }
            auxElementPtr = elementPtr;
            elementPtr = auxElementPtr->nextPtr;
        }
        return 0;
    }

    /*
    PH2: Return value: an iterator on the element with the key, or the end iterator (see end()) if no such element exists.
    Complexity: hashing O(1)
    */
    iterator find(const key_type &key) const
    {
        if (Element * element{locate(key)})
        {
            return iterator{table, element, hash(key), table_size};
        }
        return end();
    }

    /*
    PH2: Swaps the elements of the container with the elements of the container other.Complexity: O(1)
    */
    void swap(ADS_set &other)
    {
        std::swap(table, other.table);
        std::swap(inserted_elements, other.inserted_elements);
        std::swap(table_size, other.table_size);
        std::swap(max_load_factor, other.max_load_factor);
    }

    /*
    PH2: Return value: Iterator on the first element or the end iterator if the container is empty.
    */
    const_iterator begin() const
    {
        return const_iterator(table, table[0], 0, table_size);
    }

    /*
    PH2: Returns an iterator to the (virtual) element after the last element in the container ("end iterator").
    Return value: End iterator
    */
    const_iterator end() const
    {
        return const_iterator(table, nullptr, table_size, table_size);
    }

    /*
    Output the container contents to the stream o. There is no default for the functionality of dump(), i.e. it is not prescribed what the method writes to the stream. It is also permissible for the method to output nothing. However, it is recommended to output at least all contained elements. With testing it can be helpful beyond that, if the output represents in some form also the condition of the data structure.
    The unit test outputs the contents of the container with the help of this method in the event of errors, in order to facilitate troubleshooting. However, if the output is overly large, the unit test may truncate it. It may be assumed that the container is instantiated during unit testing only with element data types (key_type) that support the output operator (<<).
    */
    void dump(std::ostream &o = std::cerr) const;

    /* ------- OPERATORS ------- */

    /*
    PH2: Checks if the contents of two containers are equal. The contents are equal if the containers are of the same size and for each element in lhs there is an element in rhs with the same key. Return value: true if the container contents are equal, false otherwise. Complexity: O(size).
    */
    friend bool operator==(const ADS_set &lhs, const ADS_set &rhs)
    {
        // same number of inserted elements?
        if (lhs.inserted_elements != rhs.inserted_elements)
        {
            return false;
        }
        for (const auto &key : lhs)
        {
            if (rhs.locate(key) == nullptr)
            {
                return false;
            }
        }
        return true;
    }

    /*
    PH2: Checks if the contents of two containers are not equal.
    Return value: false if the container contents are equal, true otherwise. Complexity: O(size).
    */
    friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs)
    {
        return !(lhs == rhs);
    }

    /*
    PH2: Overload of Assignment Operator, Copy assignment operator -> The contents of the container will be replaced by the contents of other
    */
    ADS_set &operator=(const ADS_set &other)
    {
        // don't swap if the contents are the same
        if (this == &other)
        {
            return *this;
        }

        ADS_set temporary{other};
        swap(temporary);
        return *this;
    }

    /*
    PH2: Copy assignment operator. The contents of the container will be replaced by the contents of other. Return value: reference to *this  Complexity: hashing: O(size + other_size)
    */
    ADS_set &operator=(std::initializer_list<key_type> ilist)
    {
        ADS_set temporary{ilist};
        swap(temporary);
        return *this;
    }
};

/* ------- CONTAINER PRIVATE METHODS IMPLEMENTATION ------- */
template <typename Key, size_t N>
template <typename InputIt>
void ADS_set<Key, N>::insert(InputIt first, InputIt last)
{
    for (auto it{first}; it != last; ++it)
    {
        if (count(*it) == 0) // if el not found
        {
            reserve(inserted_elements + 1);
            add(*it);
        }
    }
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::size_type ADS_set<Key, N>::hash(const key_type &key) const
{
    return hasher{}(key) % table_size;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::Element *ADS_set<Key, N>::add(const key_type &key)
{
    size_type index{hash(key)};

    if (table[index])
    {
        Element *old_element = table[index];
        Element *new_element = new Element{key, old_element};
        table[index] = new_element;
    }
    else
    {
        table[index] = new Element{key, nullptr};
    }
    ++inserted_elements;

    return table[index];
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::Element *ADS_set<Key, N>::locate(const key_type &key) const
{
    Element *currentElementPtr = table[hash(key)];

    while (currentElementPtr)
    {
        if (key_equal{}(currentElementPtr->key, key))
        {
            // return it if exists
            return currentElementPtr;
        }
        currentElementPtr = currentElementPtr->nextPtr;
    }
    return nullptr; // the key not found
}

template <typename Key, size_t N>
void ADS_set<Key, N>::reserve(size_type n)
{
    if ((table_size * max_load_factor) >= n)
    {
        return;
    }

    size_type new_table_size{table_size};

    while (new_table_size * max_load_factor < n)
    {
        ++(new_table_size *= 2); // to make sure we don't start from 0 because 0 * 2 = 0
    }
    rehash(new_table_size);
}

template <typename Key, size_t N>
void ADS_set<Key, N>::rehash(size_type n)
{
    size_type new_table_size{
        std::max(N,
                 std::max(n,
                          size_type(
                              inserted_elements / max_load_factor)))};

    Element **new_table{new Element *[new_table_size] {}};
    Element **old_table{table};
    size_type old_table_size{table_size};

    inserted_elements = 0;
    table = new_table;
    table_size = new_table_size;

    for (size_type index{0}; index < old_table_size; ++index)
    {
        // if slot in the old table is occupied add the key to the new table
        if (old_table[index])
        {
            // loop over old linked list
            Element *currentElementPtr = old_table[index];
            while (currentElementPtr)
            {
                add(currentElementPtr->key);
                // to prevenet memory leak
                Element *auxPtr = currentElementPtr;
                currentElementPtr = auxPtr->nextPtr;
                delete auxPtr;
            }
        }
    }
    delete[] old_table; // not needed anymore
}

template <typename Key, size_t N>
void ADS_set<Key, N>::dump(std::ostream &o) const
{
    Element *current_element_ptr;

    o << "table_size = " << table_size << ", inserted_elements = " << inserted_elements << "\n";
    for (size_type index{0}; index < table_size; ++index)
    {
        o << index << ": ";
        if (table[index] == nullptr)
        {
            o << "--FREE \n";
            continue;
        }

        o << "[";

        current_element_ptr = table[index];

        while (current_element_ptr)
        {
            o << current_element_ptr->key;
            current_element_ptr = current_element_ptr->nextPtr;
            if (current_element_ptr)
            {
                o << " -> ";
            }
        }
        o << "]\n";
    }
    o << "\n";
}

/* ------- ITERATOR ------- */
/*
 PH2 Iterator must implement:
 1. at which element I am in the data structure
 2. how do I get to the next one
 3. how do I recognize the "end"
 */
template <typename Key, size_t N>
class ADS_set<Key, N>::Iterator
{
private:
    Element **table;
    Element *current_element_ptr;
    size_type index;
    size_type table_size;

    /* goes through all the elements and skips empty slots */
    void skip();

public:
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::forward_iterator_tag;

    /* default constructor that performs no conversions is required */
    explicit Iterator(Element **table = nullptr,
                      Element *current_element_ptr = nullptr,
                      size_type index = 0,
                      size_type table_size = 0)
        : table{table}, current_element_ptr{current_element_ptr}, index{index}, table_size{table_size}
    {
        skip(); // do while current position
    };

    /* Pointer generalization */
    reference operator*() const { return current_element_ptr->key; };
    /* Dereferencing operator */
    pointer operator->() const { return &current_element_ptr->key; };

    Iterator &operator++()
    {
        current_element_ptr = current_element_ptr->nextPtr;
        if (current_element_ptr == nullptr)
        {
            skip();
        }
        return *this;
    };

    Iterator operator++(int)
    {
        auto returnCode = *this;
        ++*this;
        return returnCode;
    };

    friend bool operator==(const Iterator &lhs, const Iterator &rhs)
    {
        return lhs.current_element_ptr == rhs.current_element_ptr;
    }
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
    {
        return !(lhs.current_element_ptr == rhs.current_element_ptr);
    }
};

/* ------- ITERATOR PRIVATE METHODS IMPLEMENTATION ------- */
template <typename Key, size_t N>
void ADS_set<Key, N>::Iterator::skip()
{
    while (!current_element_ptr && (index + 1 < table_size))
    {
        current_element_ptr = table[++index];
    }
}

/*
 Non-member-swap() to satisfy the "swappable" concept. Calls lhs.swap(rhs) (see above).
 lhs: left-hand side rhs: right-hand side. Complexity: O(1)
*/
template <typename Key, size_t N>
void swap(ADS_set<Key, N> &lhs, ADS_set<Key, N> &rhs) { lhs.swap(rhs); }

#endif // ADS_SET_H