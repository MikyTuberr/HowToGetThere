#include "Vertex.h"

Vertex::Vertex() : name(), vertex_coordinates({ -1, -1 }), cost(0), visited(false) {}

bool Vertex::is_visited() const {
    return this->visited;
}

void Vertex::set_visited(bool v) {
    this->visited = v;
}

String Vertex::get_name() const {
    return this->name;
}

Queue<Edge>& Vertex::get_edges(){
    return this->edges;
}
coordinates& Vertex::get_coordinates(){
    return this->vertex_coordinates;
}
int Vertex::get_cost() const {
    return this->cost;
}

void Vertex::set_name(String new_name) {
    this->name = new_name;
}

void Vertex::set_coordinates(coordinates new_dimensions) {
    this->vertex_coordinates = new_dimensions;
}

void Vertex::set_cost(int new_cost) {
    this->cost = new_cost;
}

void Vertex::add_edge(Edge edge) {
    this->edges.push(edge);
}

bool Vertex::operator==(const Vertex &other) const {
    return (this->name == other.name);
}

bool Vertex::operator!=(const Vertex& other) const {
    return (this->name != other.name);
}
bool Vertex::operator<(const Vertex& other) const {
    return this->cost < other.cost;
}
bool Vertex::operator>(const Vertex& other) const {
    return this->cost > other.cost;
}
