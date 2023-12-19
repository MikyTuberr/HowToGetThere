#ifndef HOWTOGETTHERE_COORDINATES_H
#define HOWTOGETTHERE_COORDINATES_H

#include <iostream>

struct coordinates {
    int x, y;

    bool operator==(const coordinates& other) const { return (x == other.x && y == other.y); }

    bool operator!=(const coordinates& other) const { return !(operator==(other)); }

    friend std::ostream& operator<<(std::ostream& out, const coordinates& c) {
        out << "(" << c.x << ", " << c.y << ")";
        return out;
    }
};
#endif //HOWTOGETTHERE_COORDINATES_H
