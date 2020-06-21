#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* dereferenciation of iterator to acces values */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.12 - Teil 1)
    else {
        return node->value;
    }
  } //call *it

  /* dereferenciation of iterator to acces values */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.12 - Teil 2)
    else {
        return &node->value;
    }
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 3)
    else {
        node = node->next;
        return *this;
    }
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 4)
    else {

        ListIterator<T> temp = *this;
        ++(*this);
        return temp;
    }
  }


  /* checks if to iterators are equal */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return node == x.node;
  } // call it: == it

  /* checks if to iterators are unequal */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.12 - Teil 6)
    // Reuse operator==
    return !(node == x.node);
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // not fully implemented yet
    // TODO: do not forget about the initialiser list! (Aufgabe 3.2)
    /* default constructor, that initializes an empty list */
    List():
        size_{ 0 },
        first_{nullptr},
        last_{nullptr} {}


    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)
    List(List<T> const& list):
        size_{ 0 },
        first_{ nullptr },
        last_{ nullptr } {
            ListNode<T>* element = list.first_;

            while (nullptr != element) {
                push_back(element->value);
                element = element->next;
            }
        }

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)
    List(List<T>&& rhs) :
        size_(rhs.size_),
        first_(rhs.first_),
        last_(rhs.last_) {
        rhs.size_ = 0;
        rhs.first_ = nullptr;
        rhs.last_ = nullptr;
    }

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* weiﬂt die Werte der rhs-Liste der Liste zu */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)
    void swap(List& rhs) {
        std::swap(first_, rhs.first_);
        std::swap(last_, rhs.last_);
    }

    List& operator=(List rhs) {
        swap(rhs);
        return *this;
    }

    /* checks if list equals rhs, means the lists have the same size and the values are equal */
    // test and implement:
    bool operator==(List const& rhs) const
    {
        if (empty() && rhs.empty()) {
            return true;
        }
        else {
            if (size_ != rhs.size_) {
                return false;
            }
            else {
                ListNode<T>* lhs_element = first_;
                ListNode<T>* rhs_element = rhs.first_;

                while (lhs_element != nullptr) {
                    if (lhs_element->value != rhs_element->value) {
                        return false;
                    }
                    lhs_element = lhs_element->next;
                    rhs_element = rhs_element->next;
                }
                return true;
            }
        }
    }

    /* checks if list and rhs are unequal, means they have a different size, or at least one element value is unequal */
    bool operator!=(List const& rhs) const
    {
        if (*this == rhs) {
            return false;
        }
        else {
            return true;
        }
    }

    /* destructor, that calls the clear function, so all elements are removed from freestore, before list is deleted */
    ~List() {
      //TODO: Implement via clear-Method (Aufgabe 3.4)
        clear();
    } //can not really be tested

    /* returns iterator, that points on first element of list */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.11)
        ListIterator<T> it;
        it.node = first_;
        return it;
    }

    /* returns iterator, that points on element after last element of list */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.11)
        ListIterator<T> it;
        it.node = nullptr;
        return it;
    }

    /* method that removes all elements from list */ 
    // test and implement:
    //TODO: clear()-Method (Aufgabe 3.4)
    void clear() {
        while (size_ > 0) {
            pop_back();
        }
    }


    /* inserts an element in the list in front of the given iterator */
    //TODO: member function insert (Aufgabe 3.13)
    ListIterator<T> insert(T t, ListIterator<T>& it) {
        if (it.node == nullptr && it != end()) {
            throw "iterator does not point to valid node";
        }
        else if (it == begin()) {
            push_front(t);
            return begin();
        }
        else if (it == end()) {
            push_back(t);
            return end();
        }
        else {
            ListNode<T>* new_element = new ListNode<T>{t, it.node->prev, it.node};

            it.node->prev->next = new_element;
            it.node->prev = new_element;
            size_++;
            
            return ListIterator<T>{new_element};
        }
    }

    /* reverses the order of the elements in the list */
    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
        if (empty()) {
            return;
        }
        else {
            ListNode<T>* current_element = first_;
            std::swap(first_, last_);

            while (nullptr != current_element) {
                std::swap(current_element->next, current_element->prev);
                current_element = current_element->prev;
            }
        }
    }


    /* adds element at the front of the list */
    void push_front(T const& element) {
      // TODO: push_front-method (Aufgabe 3.3)
        ListNode<T>* node = new ListNode<T>();
        node->value = element;
        node->prev = nullptr;

        if (empty()) {
            node->next = nullptr;
            first_ = node;
            last_ = node;
        }
        else {
            if (first_ == last_) {
                node->next = last_;
                first_ = node;
                last_->prev = first_;
            }
            else {
                node->next = first_;
                first_->prev = node;
                first_ = node;
            }
        }
        
        ++size_;
    }

    /* adds element at the end of the list */
    void push_back(T const& element) {
      // TODO: push_back-method (Aufgabe 3.3)
        ListNode<T>* node = new ListNode<T>();
        node->value = element;
        node->next = nullptr;

        if (empty()) {
            node->prev = nullptr;
            first_ = node;
            last_ = node;
        }
        else {
            if (first_ == last_) {
                node->prev = first_;
                last_ = node;
                first_->next = last_;
            }
            else {
                node->prev = last_;
                last_->next = node;
                last_ = node;
            }
        }

        ++size_;
    }

    /* removes first element */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      // TODO: remainder of pop_front-method (Aufgabe 3.3)
      else {
          if (first_ == last_) {
              assert(nullptr != first_);
              delete first_;
              first_ = nullptr;
              last_ = nullptr;
          }
          else {
              ListNode<T>* new_first = new ListNode<T>();
              new_first = first_->next;
              new_first->prev = nullptr;

              assert(nullptr != first_);
              delete(first_);
              first_ = new_first;
          }
      }
      --size_;
    }

    /* removes last element */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      // TODO: remainder of pop_back-method (Aufgabe 3.3)
      else {
          if (first_ == last_) {
              assert(nullptr != first_);
              delete first_;
              first_ = nullptr;
              last_ = nullptr;
          }
          else {
              ListNode<T>* new_last = new ListNode<T>();
              new_last = last_->prev;
              new_last->next = nullptr;

              assert(nullptr != last_);
              delete(last_);
              last_ = new_last;
          }
      }
      --size_;
    }

    /* returns reference on value of first element */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      // TODO: remainder of front-method (Aufgabe 3.3)
      else {
          return first_->value;
      }
    }

    /* returns reference on value of last element  */
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      // TODO: remainder of back-method (Aufgabe 3.3)
      else {
          return last_->value;
      }
    }

    /* checks if list is empty */
    bool empty() const {

      // TODO: empty-method (Aufgabe 3.2)
        if (first_ == nullptr && last_ == nullptr) {
            return true;
        }
        return false;
    };


    /* returns size of list */
    std::size_t size() const{
        // TODO: size-method (Aufgabe 3.2)
        return size_;
  };


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* reverses oreder of given list l */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)
template <typename T>
List<T> reverse(List<T> const& l) {
    List<T> list = l;
    list.reverse();
    return list;
}


#endif // # define BUW_LIST_HPP
