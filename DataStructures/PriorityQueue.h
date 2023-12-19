#ifndef HOWTOGETTHERE_PRIORITYQUEUE_H
#define HOWTOGETTHERE_PRIORITYQUEUE_H

#include "Vector.h"

template <typename T>
class PriorityQueue {
public:
    PriorityQueue();
    explicit PriorityQueue(const Vector<T>& v);
    ~PriorityQueue() = default;

    [[nodiscard]] T& top() { return heap[0]; }
    [[nodiscard]] int size() const { return this->_size; }
    [[nodiscard]] bool empty() const { return m_Size == 0; }

    void push(const T& val);
    void pop();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<U>& pq);

private:
    Vector<T> heap;
    int m_Size;
    void heapify_down(int i);
};

template<typename T>
void PriorityQueue<T>::heapify_down(int i) {
    int n = m_Size;

    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < n && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < n && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            T tmp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = tmp;
            i = smallest;
        }
        else {
            break;
        }
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const PriorityQueue<T> &pq) {
    PriorityQueue<T> copy_pq = pq;
    int i = 1;
    os << "[ ";
    while (!copy_pq.empty()) {
        os << i << ") " << copy_pq.top() << " ";
        copy_pq.pop();
        i++;
    }
    os << "]";
    return os;
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (m_Size == 1) {
        m_Size--;
        heap.pop_back();
        return;
    }

    heap[0] = heap[m_Size - 1];
    m_Size--;
    heap.pop_back();

    heapify_down(0);
}

template<typename T>
void PriorityQueue<T>::push(const T &val) {
    heap.push_back(val);
    int current = m_Size;
    m_Size++;

    int parent = (current - 1) / 2;
    while (current > 0 && heap[current] < heap[parent]) {
        T tmp = heap[current];
        heap[current] = heap[parent];
        heap[parent] = tmp;
        current = parent;
        parent = (current - 1) / 2;
    }
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const Vector<T> &v) : heap(v), m_Size(v.size())
{
    for (int i = (m_Size - 1) / 2; i >= 0; i--) {
        heapify_down(i);
    }
}

template<typename T>
PriorityQueue<T>::PriorityQueue()  : m_Size(0) {}


#endif //HOWTOGETTHERE_PRIORITYQUEUE_H
