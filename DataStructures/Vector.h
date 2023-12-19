#ifndef HOWTOGETTHERE_VECTOR_H
#define HOWTOGETTHERE_VECTOR_H

#include <cstdio>
#include <iostream>

template <typename T>
class Vector {
public:
    Vector();
    explicit Vector(size_t size);
    Vector(const Vector& other);
    ~Vector();

    void reserve(size_t new_capacity);
    void push_back(const T& value);
    void pop_back();
    void pop_front();

    const T& back() const;
    const T& front() const;
    void clear();
    [[nodiscard]] bool empty() const { return (m_Size == 0); }
    [[nodiscard]] size_t size() const { return this->m_Size; }
    [[nodiscard]] size_t capacity() const { return this->m_Capacity; }

    Vector<T>& operator=(const Vector<T>& other);
    bool operator==(const Vector& other) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);
private:
    size_t m_Size;
    size_t m_Capacity;
    T* m_Data;
};


template<typename T>
Vector<T>::Vector() : m_Size(0), m_Capacity(0), m_Data(nullptr) {}

template<typename T>
Vector<T>::Vector(size_t size) : m_Size(size), m_Capacity(size), m_Data(new T[size]) {}

template<typename T>
Vector<T>::Vector(const Vector &other)
{
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;
    m_Data = new T[m_Capacity];
    for (size_t i = 0; i < m_Size; ++i) {
        m_Data[i] = other.m_Data[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_Data;
    m_Data = nullptr;
}

template<typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= m_Capacity) {
        std::cout << "Podana pojemnosc vectora jest mniejsza albo rowna aktualnej" << std::endl;
        return;
    }
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < m_Size; i++) {
        new_data[i] = m_Data[i];
    }
    delete[] m_Data;
    m_Data = new_data;
    m_Capacity = new_capacity;
}

template<typename T>
void Vector<T>::push_back(const T &value) {
    if (m_Size == m_Capacity) {
        if (m_Capacity == 0) {
            reserve(1);
        }
        else {
            reserve(m_Capacity * 2);
        }
    }
    m_Data[m_Size] = value;
    m_Size++;
}

template<typename T>
void Vector<T>::pop_front() {
    if (m_Size == 0) {
        std::cout << "Vector is empty! Cannot delete elements";
        return;
    }
    for (size_t i = 0; i < m_Size - 1; ++i) {
        m_Data[i] = m_Data[i + 1];
    }
    m_Size--;
    if (m_Size <= m_Capacity / 4) {
        m_Capacity /= 2;

        T* new_data = new T[m_Capacity + 1];
        for (size_t i = 0; i < m_Size; i++) {
            new_data[i] = m_Data[i];
        }

        delete[] m_Data;
        m_Data = new_data;
    }
}

template<typename T>
void Vector<T>::pop_back() {
    if (m_Size == 0) {
        std::cout << "Vector is empty! Cannot delete elements";
        return;
    }
    m_Size--;
    if (m_Size <= m_Capacity / 4) {
        m_Capacity /= 2;

        T* new_data = new T[m_Capacity + 1];
        for (size_t i = 0; i < m_Size; i++) {
            new_data[i] = m_Data[i];
        }

        delete[] m_Data;
        m_Data = new_data;
    }
}

template<typename T>
const T &Vector<T>::back() const {
    if (m_Size == 0) {
        std::cout << "Vector is empty!";
        return T();
    }
    return m_Data[m_Size - 1];
}

template<typename T>
const T &Vector<T>::front() const {
    if (m_Size == 0) {
        std::cout << "Vector jest pusty!";
        return T();
    }
    return m_Data[0];
}

template<typename T>
void Vector<T>::clear() {
    delete[] m_Data;
    m_Data = nullptr;
    m_Size = 0;
    m_Capacity = 0;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this == &other) {
        return *this;
    }
    if (m_Capacity < other.size()) {
        delete[] m_Data;
        m_Capacity = other.size();
        m_Data = new T[m_Capacity];
    }
    m_Size = other.size();
    for (size_t i = 0; i < m_Size; i++) {
        if (i < m_Capacity) {
            m_Data[i] = other.m_Data[i];
        }
        else {
            break;
        }
    }
    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector &other) const {
    if (m_Size != other.size()) {
        return false;
    }
    for (size_t i = 0; i < m_Size; i++) {
        if (m_Data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
inline T &Vector<T>::operator[](size_t index) {
    if (index >= m_Size) {
        std::cout << "Index overflow" << std::endl;
    }
    return m_Data[index];
}

template<typename T>
inline const T &Vector<T>::operator[](size_t index) const {
    if (index >= m_Size) {
        std::cout << "Index overflow" << std::endl;
    }
    return m_Data[index];
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.m_Size; i++) {
        os << v.m_Data[i];
        if (i < v.m_Size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif //HOWTOGETTHERE_VECTOR_H
