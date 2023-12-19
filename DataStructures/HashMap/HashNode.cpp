#include "HashNode.h"

HashNode::HashNode() : m_Vertex(), next(nullptr), previous_visited(nullptr) {}

Vertex& HashNode::get_vertex(){
    return this->m_Vertex;
}

HashNode* HashNode::get_next_node() const {
    return this->next;
}

HashNode* HashNode::get_previous_visited() const {
    return this->previous_visited;
}
void HashNode::set_next_node(HashNode* _next) {
    this->next = _next;
}

void HashNode::set_vertex(Vertex _vertex) {
    this->m_Vertex = _vertex;
}

void HashNode::set_previous_visited(HashNode* _previous) {
    this->previous_visited = _previous;
}

bool HashNode::operator==(const HashNode& other) const {
    return (this->m_Vertex == other.m_Vertex);
}

bool HashNode::operator!=(const HashNode& other) const {
    return !(this->m_Vertex == other.m_Vertex);
}

bool HashNode::operator<(const HashNode& other) const {
    return (this->m_Vertex.get_cost() < other.m_Vertex.get_cost());
}

bool HashNode::operator>(const HashNode& other) const {
    return (this->m_Vertex.get_cost() > other.m_Vertex.get_cost());
}