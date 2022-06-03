template <
    typename Key,
    size_t N = /* implementation-defined */
    >
class ADS_set;

using value_type = Key;
using key_type = Key;
using reference = value_type &;
using const_reference = const value_type &;
using size_type = size_t;
using difference_type = std::ptrdiff_t;
using const_iterator = /* constant ForwardIterator */
using iterator = const_iterator;
using key_compare = std::less<key_type>;   // B+-Tree
using key_equal = std::equal_to<key_type>; // Hashing
using hasher = std::hash<key_type>;        // Hashing

ADS_set();

// Default constructor. Creates an empty container. Complexity: O(1)
ADS_set(std::initializer_list<key_type> ilist);

// initializer list constructor. Creates a container containing the elements from ilist. The elements are inserted in the order specified in ilist.
template <typename InputIt>
ADS_set(InputIt first, InputIt last);

ADS_set(const ADS_set &other);

// Destructor: The destructors of the stored elements are called and the used memory space is completely freed. Complexity: O(size)
~ADS_set();

// Assignment operators
ADS_set &operator=(const ADS_set &other);

// Copy assignment operator. The contents of the container will be replaced by the contents of other. Return value: reference to *this  Complexity: hashing: O(size + other_size)
ADS_set &operator=(std::initializer_list<key_type> ilist)

    // Return value: Number of elements stored in the container.Complexity: O(1)
    size_type size() const;

// Return value: true if size()==0, false otherwise.  Complexity: O(1)
bool empty() const;

// Inserts the elements from ilist. The elements are inserted in the order specified in ilist.
// Complexity: B+ tree: O(ilist_size * log (ilist_size + size)), Hashing: O(ilist_size)

void insert(std::initializer_list<key_type> ilist);

// Inserts key.  Return value: A std::pair consisting of an iterator and a bool.
// iterator: points to the inserted element if an element was inserted, or to the existing element with the same key if no element was inserted.
// bool: true if an element was inserted, false otherwise.
// Complexity:  hashing O(1)
std::pair<iterator, bool> insert(const key_type &key);

// Inserts the elements from the range [first, last[ in the given order (starting with first).
// Complexity: Hashing: O(range_size)
template <typename InputIt>
void insert(InputIt first, InputIt last);

// Removes all elements from the container.
// Complexity: O(size)
void clear();

// Removes the element key. 
// Return value: number of deleted elements (0 or 1). 
// Complexity: B+ tree: O(log size), hashing: O(1) 

// For the dynamic hash procedures, it is permissible to remove only the respective affected values from the buckets for simplification (no merging etc. necessary). The data structure must of course remain functional. With the static hash procedures, it is not necessary to reduce an enlarged table again. 
size_type erase(const key_type &key);

// Swaps the elements of the container with the elements of the container other. 
// Complexity: O(1) 
void swap(ADS_set &other);

// Return value: The number of elements in the container with key key (0 or 1). 
// Complexity: B+ tree O(log size)), hashing O(1) 
size_type count(const key_type &key) const;