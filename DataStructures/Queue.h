#ifndef HOWTOGETTHERE_QUEUE_H
#define HOWTOGETTHERE_QUEUE_H

#include "Vector.h"

template <typename T>
class Queue {
public:
    Queue() = default;
    ~Queue() = default;

    [[nodiscard]] bool empty() const { return queue.empty(); }
    const T& top() const { return queue.front(); }

    void push(T& val) { queue.push_back(val); }
    void pop();
private:
    Vector<T> queue;
};

template <typename T>
void Queue<T>::pop() {
    if (empty()) {
        std::cout << "Queue is Empty!" << std::endl;
        return;
    }
    queue.pop_front();
}

#endif //HOWTOGETTHERE_QUEUE_H
