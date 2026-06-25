#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

// Comparator returns true when the first item has higher priority.
template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  std::vector<T> m_items;
  int m_arity;
  PComparator m_comp;

  void trickleUp(size_t index);
  void heapify(size_t index);
  size_t parent(size_t index) const;
  size_t kthChild(size_t index, int k) const;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_items(), m_arity(m), m_comp(c)
{
  if(m_arity < 2) {
    m_arity = 2;
  }
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return m_items.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return m_items.size();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::parent(size_t index) const
{
  return (index - 1) / m_arity;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::kthChild(size_t index, int k) const
{
  return m_arity * index + k;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  m_items.push_back(item);
  trickleUp(m_items.size() - 1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t index)
{
  if(index == 0) {
    return;
  }

  size_t p = parent(index);
  if(m_comp(m_items[index], m_items[p])) {
    std::swap(m_items[index], m_items[p]);
    trickleUp(p);
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return m_items[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }

  m_items[0] = m_items[m_items.size() - 1];
  m_items.pop_back();

  if(!empty()) {
    heapify(0);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index)
{
  size_t best = index;

  for(int k = 1; k <= m_arity; k++) {
    size_t child = kthChild(index, k);
    if(child < m_items.size() && m_comp(m_items[child], m_items[best])) {
      best = child;
    }
  }

  if(best != index) {
    std::swap(m_items[index], m_items[best]);
    heapify(best);
  }
}

#endif
