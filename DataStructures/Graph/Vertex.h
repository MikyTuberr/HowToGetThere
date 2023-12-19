#ifndef HOWTOGETTHERE_VERTEX_H
#define HOWTOGETTHERE_VERTEX_H

#include "../String.h"
#include "../Queue.h"
#include "Edge.h"

class Vertex {
public:
    Vertex();
    ~Vertex() = default;

    [[nodiscard]] bool is_visited() const;
    void set_visited(bool v);

    [[nodiscard]] String get_name() const;
    Queue<Edge>& get_edges();
    coordinates& get_coordinates();
    [[nodiscard]] int get_cost() const;

    void set_name(String new_name);
    void set_coordinates(coordinates new_dimensions);
    void set_cost(int new_cost);

    void add_edge(Edge edge);

    bool operator==(const Vertex& other) const;
    bool operator!=(const Vertex& other) const;
    bool operator<(const Vertex& other) const;
    bool operator>(const Vertex& other) const;
private:
    String name;
    Queue <Edge> edges;
    coordinates vertex_coordinates;
    int cost;
    bool visited;
};


#endif //HOWTOGETTHERE_VERTEX_H
