#ifndef HOWTOGETTHERE_EDGE_H
#define HOWTOGETTHERE_EDGE_H

#include "../../Structs/Coordinates.h"

class Edge {
public:
    Edge();
    ~Edge() = default;

    [[nodiscard]] unsigned int get_time() const;
    [[nodiscard]] coordinates get_destination_coordinates() const;
    [[nodiscard]] coordinates get_source_coordinates() const;

    void set_destination_coordinates(coordinates destination);
    void set_source_coordinates(coordinates source);
    void set_time(unsigned int time);

    bool operator<(const Edge& other) const;
    bool operator>(const Edge& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Edge& r);
private:
    unsigned int time_of_travel;
    coordinates source_coordinates;
    coordinates destination_coordinates;
};


#endif //HOWTOGETTHERE_EDGE_H
