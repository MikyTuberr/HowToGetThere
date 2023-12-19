#ifndef HOWTOGETTHERE_HASHNODE_H
#define HOWTOGETTHERE_HASHNODE_H

#include "../Graph/Vertex.h"

class HashNode {
public:
    HashNode();
    ~HashNode() = default;

    Vertex& get_vertex();
    [[nodiscard]] HashNode* get_next_node() const;
    [[nodiscard]] HashNode* get_previous_visited() const;

    void set_next_node(HashNode* _next);
    void set_vertex(Vertex _vertex);
    void set_previous_visited(HashNode* _previous);

    bool operator==(const HashNode& other) const;
    bool operator!=(const HashNode& other) const;
    bool operator<(const HashNode& other) const;
    bool operator>(const HashNode& other) const;
private:
    Vertex m_Vertex;
    HashNode* next;
    HashNode* previous_visited;
};

#endif //HOWTOGETTHERE_HASHNODE_H
