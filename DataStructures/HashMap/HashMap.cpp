#include "HashMap.h"

HashMap::HashMap() : hash_map(), size(0) {}

HashMap::HashMap(size_t size) : hash_map(size), size(size) {};

HashMap::~HashMap() {
    for (size_t i = 0; i < hash_map.size(); i++) {
        HashNode* node = &hash_map[i];
        HashNode* tmp = node->get_next_node();
        while (tmp != nullptr) {
            HashNode* next = tmp->get_next_node();
            delete tmp;
            tmp = next;
        }
    }
}

uint32_t HashMap::hash(const String& s) const {
    const uint32_t fnv_offset_basis = 2166136261;
    const uint32_t fnv_prime = 16777619;
    uint32_t _hash = fnv_offset_basis;
    for (size_t i = 0; i < s.length(); ++i) {
        _hash ^= (uint32_t)s[i];
        _hash *= fnv_prime;
    }
    return _hash % size;
}

int HashMap::hash_coordinates(const coordinates& _coordinates) const {
    return (_coordinates.x * HASH_PRIME_NUMBER_FOR_X + _coordinates.y * HASH_PRIME_NUMBER_FOR_Y) % (int)size;
}

void HashMap::add(Vertex& new_vertex) {
    int index = hash(new_vertex.get_name());
    HashNode* node = new HashNode;
    node->set_vertex(new_vertex);
    node->set_next_node(nullptr);

    if (hash_map[index].get_vertex().get_coordinates() == EMPTY_COORDINATES) {
        hash_map[index] = *node;
    }
    else {
        HashNode* tmp = &hash_map[index];
        while (tmp->get_next_node() != nullptr) {
            tmp = tmp->get_next_node();
        }
        tmp->set_next_node(node);
    }
}

void HashMap::add_c(Vertex& new_vertex) {
    int index = hash_coordinates(new_vertex.get_coordinates());
    HashNode* node = new HashNode;
    node->set_vertex(new_vertex);
    node->set_next_node(nullptr);

    if (hash_map[index].get_vertex().get_coordinates() == EMPTY_COORDINATES) {
        hash_map[index] = *node;
        delete node;
        node = nullptr;
    }
    else {
        HashNode* tmp = &hash_map[index]; //collision of hash
        while (tmp->get_next_node() != nullptr) {
            tmp = tmp->get_next_node();
        }
        tmp->set_next_node(node);
    }
}

HashNode* HashMap::find(const String& key) {
    int index = hash(key);
    HashNode* tmp = &hash_map[index];
    if (tmp != nullptr) {
        while (tmp != nullptr) {
            if (tmp->get_vertex().get_name() == key) {
                return tmp;
            }
            tmp = tmp->get_next_node();
        }
    }
    return nullptr;
}

HashNode* HashMap::find_c(const coordinates& _coordinates) {
    int index = hash_coordinates(_coordinates);
    HashNode* tmp = &hash_map[index];
    if (tmp != nullptr) {
        while (tmp != nullptr) {
            if ((tmp->get_vertex().get_coordinates() == _coordinates)) {
                return tmp;
            }
            tmp = tmp->get_next_node();
        }
    }
    return nullptr;
}

void HashMap::change_c(const coordinates& _coordinates, Vertex& new_vertex) {
    HashNode* node = find_c(_coordinates);
    if (node != nullptr) {
        node->set_vertex(new_vertex);
    }
}

HashNode& HashMap::operator[](const int& id) {
    return hash_map[id];
}