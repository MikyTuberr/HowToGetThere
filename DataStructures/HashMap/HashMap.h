#ifndef HOWTOGETTHERE_HASHMAP_H
#define HOWTOGETTHERE_HASHMAP_H

#include "HashNode.h"

class HashMap {
public:
    HashMap();
    explicit HashMap(size_t size);
    ~HashMap();

    [[nodiscard]] uint32_t hash(const String& s) const;
    [[nodiscard]] int hash_coordinates(const coordinates& _coordinates) const;

    void add(Vertex& new_vertex);
    void add_c(Vertex& new_vertex);

    HashNode* find(const String& key);
    HashNode* find_c(const coordinates& _coordinates);

    void change_c(const coordinates& _coordinates, Vertex& new_vertex);

    HashNode& operator[](const int& id);
private:
    const int HASH_PRIME_NUMBER_FOR_X = 31;
    const int HASH_PRIME_NUMBER_FOR_Y = 17;
    const coordinates EMPTY_COORDINATES = { -1, -1 };
    Vector<HashNode> hash_map;
    size_t size;
};


#endif //HOWTOGETTHERE_HASHMAP_H
