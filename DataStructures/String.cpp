#include "String.h"

String::String() : m_Data(nullptr), m_Length(0) {}

String::String(const char *str) : m_Data(nullptr), m_Length(0)
{
    if (str) {
        m_Length = strlen(str);
        m_Data = new char[m_Length + 1];
        strcpy(m_Data, str);
    }
}

String::~String() {
    delete[] m_Data;
    m_Data = nullptr;
}

String::String(const String &other) noexcept : m_Data(nullptr), m_Length(other.m_Length)
{
    if (other.m_Data != nullptr) {
        m_Data = new char[m_Length + 1];
        strcpy(m_Data, other.m_Data);
    }
}

String::String(String &&other) noexcept : m_Data(nullptr), m_Length(0)
{
    std::swap(m_Data, other.m_Data);
    std::swap(m_Length, other.m_Length);
}

void String::reverse() {
    size_t n = length();
    for (size_t i = 0; i < n / 2; i++) {
        char tmp = m_Data[i];
        m_Data[i] = m_Data[n - i - 1];
        m_Data[n - i - 1] = tmp;
    }
}

String &String::operator+=(char str)
{
    char* new_data = new char[m_Length + 2];
    if (m_Data != nullptr) {
        strcpy(new_data, m_Data);
        delete[] m_Data;
        m_Data = nullptr;
    }
    m_Data = new_data;
    m_Data[m_Length] = str;
    m_Data[m_Length + 1] = '\0';
    m_Length += 1;
    return *this;
}

String &String::operator=(const char *str)
{
    size_t new_length = (str != nullptr) ? strlen(str) : 0;
    char* new_data = new char[new_length + 1];

    delete[] m_Data;
    m_Data = new_data;
    m_Length = new_length;

    if (str != nullptr)
        strcpy(m_Data, str);
    else
        m_Data[0] = '\0';



    return *this;
}

String &String::operator=(const String &other) noexcept
{
    if (this == &other) {
        return *this;
    }
    char* new_data = nullptr;
    if (other.m_Data != nullptr) {
        new_data = new char[other.m_Length + 1];
        strcpy(new_data, other.m_Data);
    }
    delete[] m_Data;
    m_Data = new_data;
    m_Length = other.m_Length;
    return *this;
}

String &String::operator=(String &&other) noexcept
{
    if (this != &other) {
        delete[] m_Data;

        m_Data = nullptr;
        m_Length = 0;

        std::swap(m_Data, other.m_Data);
        std::swap(m_Length, other.m_Length);
    }
    return *this;
}

String &String::operator=(char c)
{
    char new_data[2] = { c, '\0' };
    return (*this = new_data);
}

const char &String::operator[](size_t index) const {
    if (index >= m_Length) {
        std::cout << "Wyjscie poza rozmiar stringa" << std::endl;
    }
    return m_Data[index];
}

bool String::operator==(const String &other) const {
    if (this->m_Length != other.m_Length) {
        return false;
    }
    if (this->m_Data == nullptr || other.m_Data == nullptr) {
        return this->m_Data == other.m_Data;
    }
    return strcmp(this->m_Data, other.m_Data) == 0;
}

bool String::operator!=(const String &other) const {
    return !(*this == other);
}

bool String::operator<(const String &other) const {
    return strcmp(m_Data, other.m_Data) < 0;
}

std::ostream &operator<<(std::ostream &out, const String &string) {
    for (size_t i = 0; i < string.m_Length; i++) {
        out << string.m_Data[i];
    }
    return out;
}









