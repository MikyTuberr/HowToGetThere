#include "Edge.h"

Edge::Edge() : time_of_travel(0), source_coordinates({ -1,-1 }), destination_coordinates({ -1,-1 }) {}

coordinates Edge::get_destination_coordinates() const {
    return this->destination_coordinates;
}

unsigned int Edge::get_time() const {
    return this->time_of_travel;
}

coordinates Edge::get_source_coordinates() const {
    return this->source_coordinates;
}

void Edge::set_destination_coordinates(coordinates destination) {
    this->destination_coordinates = destination;
}

void Edge::set_source_coordinates(coordinates source) {
    this->source_coordinates = source;
}

void Edge::set_time(unsigned int time) {
    this->time_of_travel = time;
}

bool Edge::operator<(const Edge &other) const {
    return time_of_travel > other.time_of_travel;
}

bool Edge::operator>(const Edge &other) const {
    return time_of_travel < other.time_of_travel;
}

std::ostream &operator<<(std::ostream &out, const Edge &r) {
    out << "Time of travel: " << r.get_time() << ", Source: (" << r.get_source_coordinates().y << "," << r.get_source_coordinates().x << ") " <<
        ", Destination: (" << r.get_destination_coordinates().y << ", " << r.get_destination_coordinates().x << ") " << std::endl;
    return out;
}


