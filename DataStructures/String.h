#ifndef HOWTOGETTHERE_STRING_H
#define HOWTOGETTHERE_STRING_H

#include <cstdio>
#include <cstring>
#include <iostream>

class String {
public:
    String();
    explicit String(const char* str);
    String(const String& other) noexcept;
    String(String&& other) noexcept;
    ~String();

    void reverse();
    [[nodiscard]] inline size_t length() const { return this->m_Length; }

    String& operator+=(char str);
    String& operator=(const char* str);
    String& operator=(char c);
    String& operator=(const String& other) noexcept;
    String& operator=(String&& other) noexcept;
    const char& operator[](size_t index) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;

    friend std::ostream& operator<<(std::ostream& out, const String& string);
private:
    char* m_Data;
    size_t m_Length;
};


#endif //HOWTOGETTHERE_STRING_H
