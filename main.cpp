//REALIZED WITH NO STL


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdint.h>

#define MAX_SIZE 20

using namespace std;

struct dimensions {
	int h;
	int w;
};

struct coordinates {
	int y;
	int x;

	bool operator==(const coordinates& other) const {
		return (x == other.x && y == other.y);
	}

	bool operator!=(const coordinates& other) const {
		return !(operator==(other));
	}

	friend std::ostream& operator<<(std::ostream& out, const coordinates& c) {
		out << "(" << c.x << ", " << c.y << ")";
		return out;
	}
};

struct road {
	int cost = 0;
	coordinates previous = { -1, -1 };
	coordinates current = { -1, -1 };
};

class _string {
private:
	char* data;
	size_t _length;
public:
	_string() : data(nullptr), _length(0) {}

	_string(const _string& other) : _length(other._length), data(nullptr) {
		if (other.data != nullptr) {
			data = new char[_length + 1];
			strcpy(data, other.data);
		}
	}

	void reverse() {
		size_t n = length();
		for (size_t i = 0; i < n / 2; i++) {
			char tmp = data[i];
			data[i] = data[n - i - 1];
			data[n - i - 1] = tmp;
		}
	}

	size_t length() const {
		return this->_length;
	}

	_string& operator+=(char str) {
		char* new_data = new char[_length + 2];
		if (data != nullptr) {
			strcpy(new_data, data);
			delete[] data;
			data = nullptr;
		}
		data = new_data;
		data[_length] = str;
		data[_length + 1] = '\0';
		_length += 1;
		return *this;
	}

	_string& operator=(const char* str) {
		size_t new_length = strlen(str);
		char* new_data = new char[new_length + 1];
		strcpy(new_data, str);
		delete[] data;
		data = new_data;
		_length = new_length;
		return *this;
	}

	_string& operator=(const _string& other) {
		if (this == &other) {
			return *this;
		}
		char* new_data = nullptr;
		if (other.data != nullptr) {
			new_data = new char[other._length + 1];
			strcpy(new_data, other.data);
		}
		delete[] data;
		data = new_data;
		_length = other._length;
		return *this;
	}

	_string& operator=(char c) {
		char new_data[2] = { c, '\0' };
		return (*this = new_data);
	}

	const char& operator[](size_t index) const {
		if (index >= _length) {
			cout << "Wyjscie poza rozmiar stringa" << endl;
		}
		return data[index];
	}

	friend std::ostream& operator<<(std::ostream& out, const _string& string) {
		for (size_t i = 0; i < string._length; i++) {
			out << string.data[i];
		}
		return out;
	}

	bool operator==(const _string& other) const {
		if (this->_length != other._length) {
			return false;
		}
		if (this->data == nullptr || other.data == nullptr) {
			return this->data == other.data;
		}
		return strcmp(this->data, other.data) == 0;
	}

	bool operator!=(const _string& other) const {
		return !(*this == other);
	}

	bool operator<(const _string& other) const {
		return strcmp(data, other.data) < 0;
	}

	~_string() {
		delete[] data;
		data = nullptr;
	}
};

template <typename T>
class _vector {
private:
	size_t _size;
	size_t _capacity;
	T* data;
public:
	_vector() : _size(0), _capacity(0), data(nullptr) {}

	explicit _vector(size_t size) : _size(size), _capacity(size), data(new T[size]) {}

	_vector(const _vector& other) {
		_size = other._size;
		_capacity = other._capacity;
		data = new T[_capacity];
		for (size_t i = 0; i < _size; ++i) {
			data[i] = other.data[i];
		}
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) {
			cout << "Podana pojemnosc vectora jest mniejsza albo rowna aktualnej" << endl;
			return;
		}
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		_capacity = new_capacity;
	}

	void push_back(const T& value) {
		if (_size == _capacity) {
			if (_capacity == 0) {
				reserve(1);
			}
			else {
				reserve(_capacity * 2);
			}
		}
		data[_size] = value;
		_size++;
	}

	void pop_back() {
		if (_size == 0) {
			cout << "Vector jest pusty! Nie mozna usunac elementow";
			return;
		}
		_size--;
		if (_size <= _capacity / 4) {
			_capacity /= 2;

			T* new_data = new T[_capacity + 1];
			for (size_t i = 0; i < _size; i++) {
				new_data[i] = data[i];
			}

			delete[] data;
			data = new_data;
		}
	}

	void pop_front() {
		if (_size == 0) {
			cout << "Vector jest pusty! Nie mozna usunac elementow";
			return;
		}
		for (size_t i = 0; i < _size - 1; ++i) {
			data[i] = data[i + 1];
		}
		_size--;
		if (_size <= _capacity / 4) {
			_capacity /= 2;

			T* new_data = new T[_capacity + 1];
			for (size_t i = 0; i < _size; i++) {
				new_data[i] = data[i];
			}

			delete[] data;
			data = new_data;
		}
	}

	/*const T& back() const {
		/*if (_size == 0) {
		cout << "Vector jest pusty!";
		return T();
		}*/
		//return data[_size - 1];
	//}

	const T& front() const {
		/*if (_size == 0) {
		cout << "Vector jest pusty!";
		return T();
		}*/
		return data[0];
	}

	void clear() {
		delete[] data;
		data = nullptr;
		_size = 0;
		_capacity = 0;
	}

	bool empty() const {
		return (_size == 0);
	}

	size_t size() const {
		return this->_size;
	}

	/*size_t capacity() const {
		return this->_capacity;
	}*/

	_vector<T>& operator=(const _vector<T>& other) {
		if (this == &other) {
			return *this;
		}
		if (_capacity < other.size()) {
			delete[] data;
			_capacity = other.size();
			data = new T[_capacity];
		}
		_size = other.size();
		for (size_t i = 0; i < _size; i++) {
			if (i < _capacity) {
				data[i] = other.data[i];
			}
			else {
				break;
			}
		}
		return *this;
	}

	bool operator==(const _vector& other) const {
		if (_size != other.size()) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (data[i] != other.data[i]) {
				return false;
			}
		}
		return true;
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			//cout << "Wyjscie poza rozmiar vectora" << endl;
		}
		return data[index];
	}

	const T& operator[](size_t index) const {
		if (index >= _size) {
			//cout << "Wyjscie poza rozmiar vectora" << endl;
		}
		return data[index];
	}

	friend std::ostream& operator<<(std::ostream& os, const _vector<T>& v) {
		os << "[";
		for (size_t i = 0; i < v._size; i++) {
			os << v.data[i];
			if (i < v._size - 1) {
				os << ", ";
			}
		}
		os << "]";
		return os;
	}

	~_vector() {
		delete[] data;
		data = nullptr;
	}
};

template <typename T>
class _priority_queue {
private:
	_vector<T> heap;
	int _size;
public:
	_priority_queue() : _size(0) {}

	explicit _priority_queue(const _vector<T>& v) : heap(v), _size(v.size()) {
		for (int i = (_size - 1) / 2; i >= 0; i--) {
			heapify_down(i);
		}
	}

	T& top() {
		return heap[0];
	}

	int size() const {
		return this->_size;
	}

	bool empty() const {
		return _size == 0;
	}

	void push(const T& val) {
		heap.push_back(val);
		int current = _size;
		_size++;

		int parent = (current - 1) / 2;
		while (current > 0 && heap[current] < heap[parent]) {
			T tmp = heap[current];
			heap[current] = heap[parent];
			heap[parent] = tmp;
			current = parent;
			parent = (current - 1) / 2;
		}
	}

	void pop() {
		if (_size == 1) {
			_size--;
			heap.pop_back();
			return;
		}

		heap[0] = heap[_size - 1];
		_size--;
		heap.pop_back();

		heapify_down(0);
	}

	friend std::ostream& operator<<(std::ostream& os, const _priority_queue<T>& pq) {
		_priority_queue<T> copy_pq = pq;
		int i = 1;
		os << "[ ";
		while (!copy_pq.empty()) {
			os << i << ") " << copy_pq.top() << " ";
			copy_pq.pop();
			i++;
		}
		os << "]";
		return os;
	}

	~_priority_queue() = default;

private:
	void heapify_down(int i) {
		int n = _size;

		while (true) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int smallest = i;

			if (left < n && heap[left] < heap[smallest]) {
				smallest = left;
			}

			if (right < n && heap[right] < heap[smallest]) {
				smallest = right;
			}

			if (smallest != i) {
				T tmp = heap[i];
				heap[i] = heap[smallest];
				heap[smallest] = tmp;
				i = smallest;
			}
			else {
				break;
			}
		}
	}
};

template <typename T>
class _queue {
private:
	_vector<T> queue;

public:
	_queue() = default;

	bool empty() const {
		return queue.empty();
	}

	void push(T& val) {
		queue.push_back(val);
	}

	void pop() {
		//if (empty()) {
			//cout << "queue jest pusta!" << endl;
			//return;
		//}
		queue.pop_front();
	}

	const T& top() const {
		return queue.front();
	}

	~_queue() = default;
};

class edge {
private:
	int time_of_travel;
	coordinates source_coordinates;
	coordinates destination_coordinates;
public:
	edge() : time_of_travel(0), source_coordinates({ -1,-1 }), destination_coordinates({ -1,-1 }) {}

	int get_time() const {
		return this->time_of_travel;
	}

	coordinates get_destination_coordinates() const {
		return this->destination_coordinates;

	}

	coordinates get_source_coordinates() const {
		return this->source_coordinates;
	}


	void set_destination_coordinates(coordinates destination) {
		this->destination_coordinates = destination;

	}

	void set_source_coordinates(coordinates source) {
		this->source_coordinates = source;
	}

	void set_time(int& time) {
		this->time_of_travel = time;
	}

	bool operator<(const edge& other) const {
		return time_of_travel > other.time_of_travel;
	}

	bool operator>(const edge& other) const {
		return time_of_travel < other.time_of_travel;
	}

	friend std::ostream& operator<<(std::ostream& out, const edge& r) {
		out << "Time of travel: " << r.get_time() << ", Source: (" << r.get_source_coordinates().y << "," << r.get_source_coordinates().x << ") " <<
			", Destination: (" << r.get_destination_coordinates().y << ", " << r.get_destination_coordinates().x << ") " << endl;
		return out;
	}

	~edge() = default;
};

class vertex {
private:
	_string name;
	_queue <edge> edges;
	coordinates vertex_coordinates;
	int cost;
	bool visited;
public:

	vertex() : name(), vertex_coordinates({ -1, -1 }), cost(0), visited(false) {}

	const bool is_visited() const {
		return this->visited;
	}

	void set_visited(bool v) {
		this->visited = v;
	}

	_string& get_name() {
		return this->name;
	}

	_queue<edge>& get_edges() {
		return this->edges;
	}

	coordinates& get_coordinates() {
		return this->vertex_coordinates;
	}

	int get_cost() const {
		return this->cost;
	}


	void set_name(_string& new_name) {
		this->name = new_name;
	}

	void set_coordinates(coordinates new_dimensions) {
		this->vertex_coordinates = new_dimensions;
	}

	void set_cost(int new_cost) {
		this->cost = new_cost;
	}

	/*bool is_queue_empty() const {
		return edges.empty();
	}*/

	void add_edge(edge& edge) {
		this->edges.push(edge);
	}

	bool operator==(const vertex& other) const {
		return (this->name == other.name);
	}

	bool operator!=(const vertex& other) const {
		return (this->name != other.name);
	}

	bool operator<(const vertex& other) const {
		return this->cost < other.cost;
	}

	bool operator>(const vertex& other) const {
		return this->cost > other.cost;
	}

	friend std::ostream& operator <<(std::ostream& out, const vertex& v) {
		//std::cout << v.name << " (" << v.vertex_coordinates.x << "," << v.vertex_coordinates.y << ")" << " COST: " << v.cost << " TOP: " << v.edges << "\n\n\n";
		return out;
	}

	~vertex() = default;
};

class hash_node {
private:
	vertex _vertex;
	hash_node* next;
	hash_node* previous_visited;
public:
	hash_node() : _vertex(), next(nullptr), previous_visited(nullptr) {}

	vertex& get_vertex() {
		return this->_vertex;
	}

	hash_node* get_next_node() const {
		return this->next;
	}

	hash_node* get_previous_visited() const {
		return this->previous_visited;
	}
	void set_next_node(hash_node* _next) {
		this->next = _next;
	}

	void set_vertex(const vertex& new_vertex) {
		this->_vertex = new_vertex;
	}

	void set_previous_visited(hash_node* _previous) {
		this->previous_visited = _previous;
	}

	bool operator==(const hash_node& other) const {
		return (this->_vertex == other._vertex);
	}

	bool operator!=(const hash_node& other) const {
		return !(this->_vertex == other._vertex);
	}

	bool operator<(const hash_node& other) const {
		return (this->_vertex.get_cost() < other._vertex.get_cost());
	}

	bool operator>(const hash_node& other) const {
		return (this->_vertex.get_cost() > other._vertex.get_cost());
	}

	friend std::ostream& operator <<(std::ostream& out, const hash_node& h) {
		std::cout << "[[[HASH NODE]]] " << h._vertex;
		return out;
	}

	~hash_node() = default;
};

class hash_map {
private:
	const int _HASH_PRIME_NUMBER_FOR_X = 31;
	const int _HASH_PRIME_NUMBER_FOR_Y = 17;
	const coordinates EMPTY_COORDINATES = { -1, -1 };
	_vector<hash_node> _hash_map;
	size_t size;
public:
	hash_map() : _hash_map(), size(0) {}

	explicit hash_map(size_t size) : _hash_map(size), size(size) {};

	uint32_t hash(const _string& s) const {
		const uint32_t fnv_offset_basis = 2166136261;
		const uint32_t fnv_prime = 16777619;
		uint32_t _hash = fnv_offset_basis;
		for (size_t i = 0; i < s.length(); ++i) {
			_hash ^= (uint32_t)s[i];
			_hash *= fnv_prime;
		}
		return _hash % size;
	}

	int hash_coordinates(const coordinates& _coordinates) const {
		return (_coordinates.x * _HASH_PRIME_NUMBER_FOR_X + _coordinates.y * _HASH_PRIME_NUMBER_FOR_Y) % (int)size;
	}

	void add(vertex& new_vertex) {
		int index = hash(new_vertex.get_name());
		hash_node* node = new hash_node;
		node->set_vertex(new_vertex);
		node->set_next_node(nullptr);

		if (_hash_map[index].get_vertex().get_coordinates() == EMPTY_COORDINATES) {
			_hash_map[index] = *node;
		}
		else {
			hash_node* tmp = &_hash_map[index];
			while (tmp->get_next_node() != nullptr) {
				tmp = tmp->get_next_node();
			}
			tmp->set_next_node(node);
		}
	}

	void add_c(vertex& new_vertex) {
		int index = hash_coordinates(new_vertex.get_coordinates());
		hash_node* node = new hash_node;
		node->set_vertex(new_vertex);
		node->set_next_node(nullptr);

		if (_hash_map[index].get_vertex().get_coordinates() == EMPTY_COORDINATES) {
			_hash_map[index] = *node;
			delete node;
			node = nullptr;
		}
		else {
			hash_node* tmp = &_hash_map[index]; //collision of hash
			while (tmp->get_next_node() != nullptr) {
				tmp = tmp->get_next_node();
			}
			tmp->set_next_node(node);
		}
	}

	hash_node* find(const _string& key) {
		int index = hash(key);
		hash_node* tmp = &_hash_map[index];
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

	hash_node* find_c(const coordinates& _coordinates) {
		int index = hash_coordinates(_coordinates);
		hash_node* tmp = &_hash_map[index];
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

	void change_c(const coordinates& _coordinates, vertex& new_vertex) {
		hash_node* node = find_c(_coordinates);
		if (node != nullptr) {
			node->set_vertex(new_vertex);
		}
	}

	hash_node& operator[](const int& id) {
		return _hash_map[id];
	}

	friend std::ostream& operator <<(std::ostream& out, const hash_map& h) {
		std::cout << "HASH MAP:   " << h._hash_map;
		return out;
	}

	~hash_map() {
		for (size_t i = 0; i < _hash_map.size(); i++) {
			hash_node* node = &_hash_map[i];
			hash_node* tmp = node->get_next_node();
			while (tmp != nullptr) {
				hash_node* next = tmp->get_next_node();
				delete tmp;
				tmp = next;
			}
		}
	}

};

int dijkstra(coordinates& start_coordinates, coordinates& end_coordinates, hash_map& coordinates_map, _vector<vertex>& vertexes, _vector<_string>& transit_route) {
	vertex source_vertex, destination_vertex;
	coordinates tmp_coordinates = { -1, -1 }, source_coordinates = { -1, -1 }, destination_coordinates = { -1, -1 };
	_string name;
	hash_node tmp;
	_priority_queue<hash_node> queue;
	int  time_of_travel = -1, controler = 0;

	for (size_t i = 0; i < vertexes.size(); i++) {
		tmp_coordinates = coordinates_map.find_c(vertexes[i].get_coordinates())->get_vertex().get_coordinates();
		if (tmp_coordinates == start_coordinates) {
			vertex* tmp_vertex = &coordinates_map.find_c(start_coordinates)->get_vertex();
			tmp_vertex->set_cost(0);
			tmp_vertex->set_visited(false);
			queue.push(*coordinates_map.find_c(start_coordinates));
		}
		else {
			vertex* tmp_vertex = &coordinates_map.find_c(tmp_coordinates)->get_vertex();
			tmp_vertex->set_cost(INT_MAX);
			tmp_vertex->set_visited(false);
		}
	}

	while ((!queue.empty())) {
		tmp = queue.top();
		queue.pop();
		if (!tmp.get_vertex().get_edges().empty()) {
			source_coordinates = tmp.get_vertex().get_edges().top().get_source_coordinates();
			source_vertex = coordinates_map.find_c(source_coordinates)->get_vertex();
			while (!source_vertex.get_edges().empty()) {
				destination_coordinates = source_vertex.get_edges().top().get_destination_coordinates();
				destination_vertex = coordinates_map.find_c(destination_coordinates)->get_vertex();
				time_of_travel = source_vertex.get_edges().top().get_time();

				if (!destination_vertex.is_visited()) {
					if (source_vertex.get_cost() + time_of_travel < destination_vertex.get_cost()) {
						coordinates_map.find_c(destination_coordinates)->get_vertex().set_cost(source_vertex.get_cost() + time_of_travel);
						queue.push(*coordinates_map.find_c(destination_coordinates));
						coordinates_map.find_c(destination_coordinates)->set_previous_visited(coordinates_map.find_c(source_coordinates));

						if (destination_coordinates == end_coordinates) {
							controler++;
						}

					}
				}

				source_vertex.get_edges().pop();
			}
			coordinates_map.find_c(source_coordinates)->get_vertex().set_visited(true);
		}

	}

	transit_route.clear();
	if (controler > 0) {
		destination_coordinates = coordinates_map.find_c(coordinates_map.find_c(end_coordinates)->get_previous_visited()->get_vertex().get_coordinates())->get_vertex().get_coordinates();
		while (destination_coordinates != start_coordinates) {
			name = coordinates_map.find_c(destination_coordinates)->get_vertex().get_name();
			if (name.length() != 0) {
				transit_route.push_back(name);
			}
			destination_coordinates = coordinates_map.find_c(coordinates_map.find_c(destination_coordinates)->get_previous_visited()->get_vertex().get_coordinates())->get_vertex().get_coordinates();
		}
	}

	return coordinates_map.find_c(end_coordinates)->get_vertex().get_cost();
}

coordinates get_position_of_first_or_last_letter(char**& map, const int& i, const int& j, const dimensions& map_dimensions) {
	int shifts[8][2] = { {-1,-1}, {1,-1},{-1,1}, {1,1},  {-1,0}, {0,-1}, {0,1}, {1,0} };
	for (int k = 0; k < 8; k++) {
		int shifted_i = i + shifts[k][0];
		int shifted_j = j + shifts[k][1];
		if (shifted_i >= 0 && shifted_i < map_dimensions.h && shifted_j >= 0 && shifted_j < map_dimensions.w && isalnum(map[shifted_i][shifted_j]) != 0) {
			if ((k <= 1) && shifted_j > 0 && shifted_j + 1 < map_dimensions.w && isalnum(map[shifted_i][shifted_j - 1]) != 0 && isalnum(map[shifted_i][shifted_j + 1]) != 0) {
				continue;
			}
			else if ((k <= 3 && k > 1) && shifted_j && shifted_j + 1 < map_dimensions.w && isalnum(map[shifted_i][shifted_j + 1]) != 0 && isalnum(map[shifted_i][shifted_j - 1]) != 0) {
				continue;
			}
			return { shifted_i, shifted_j };
		}
	}
	return { -1, -1 };
}

_string get_city_name(char**& map, const coordinates& letter_coordinates, const dimensions& map_dimensions) {
	_string tmp;
	tmp = "";
	if (letter_coordinates.x > 0 && isalnum(map[letter_coordinates.y][letter_coordinates.x - 1])) {
		for (int j = 0; j < map_dimensions.w; j++) {
			if (letter_coordinates.x - j >= 0 && isalnum(map[letter_coordinates.y][letter_coordinates.x - j])) {
				tmp += map[letter_coordinates.y][letter_coordinates.x - j];
			}
			else {
				tmp.reverse();
				return tmp;
			}
		}
	}
	else if (letter_coordinates.x + 1 < map_dimensions.w && isalnum(map[letter_coordinates.y][letter_coordinates.x + 1])) {
		for (int j = 0; j < map_dimensions.w; j++) {
			if (isalnum(map[letter_coordinates.y][letter_coordinates.x + j])) {
				tmp += map[letter_coordinates.y][letter_coordinates.x + j];
			}
			else {
				return tmp;
			}
		}
	}
	else if (isalnum(map[letter_coordinates.y][letter_coordinates.x])) {
		tmp += map[letter_coordinates.y][letter_coordinates.x];
	}
	return tmp;
}

void add_edge_to_vertex(vertex& vertex, const coordinates& neighbour_coordinates, int tmp_time) {
	edge tmp_edge;
	tmp_edge.set_time(tmp_time);
	tmp_edge.set_source_coordinates(vertex.get_coordinates());
	tmp_edge.set_destination_coordinates(neighbour_coordinates);
	vertex.add_edge(tmp_edge);
}

void update_to_insert(road& to_insert, road& tmp_road) {
	to_insert.cost = tmp_road.cost;
	to_insert.cost++;
	to_insert.previous.y = tmp_road.current.y;
	to_insert.previous.x = tmp_road.current.x;
}

void get_the_edges(char** map, coordinates& starting_coordinates, const dimensions& map_dimensions, vertex& _vertex) {
	road tmp_road, to_insert;
	tmp_road.current.x = starting_coordinates.x;
	tmp_road.current.y = starting_coordinates.y;
	_queue<road> queue;
	int controler = 0;
	bool** visited = new bool* [map_dimensions.h];
	for (int i = 0; i < map_dimensions.h; ++i) {
		visited[i] = new bool[map_dimensions.w];
		memset(visited[i], false, map_dimensions.w);
	}
	do {
		if (controler == 1) {
			queue.pop();
		}
		for (int i = -1; i <= 1; i += 2) {
			if (tmp_road.current.y + i >= 0 && tmp_road.current.y + i < map_dimensions.h && visited[tmp_road.current.y + i][tmp_road.current.x] != true &&
				map[tmp_road.current.y + i][tmp_road.current.x] == '#' && tmp_road.current.y + i != tmp_road.previous.y) {

				visited[tmp_road.current.y + i][tmp_road.current.x] = true;
				update_to_insert(to_insert, tmp_road);
				to_insert.current.x = tmp_road.current.x;
				to_insert.current.y = tmp_road.current.y + i;
				queue.push(to_insert);
			}
			else if (tmp_road.current.y + i >= 0 && tmp_road.current.y + i < map_dimensions.h && visited[tmp_road.current.y + i][tmp_road.current.x] != true &&
				map[tmp_road.current.y + i][tmp_road.current.x] == '*' && tmp_road.current.y + i != tmp_road.previous.y) {

				visited[tmp_road.current.y + i][tmp_road.current.x] = true;
				to_insert.cost = tmp_road.cost;
				to_insert.cost++;
				add_edge_to_vertex(_vertex, { tmp_road.current.y + i, tmp_road.current.x }, to_insert.cost);
			}
			if (tmp_road.current.x + i >= 0 && tmp_road.current.x + i < map_dimensions.w && map[tmp_road.current.y][tmp_road.current.x + i] == '#' &&
				visited[tmp_road.current.y][tmp_road.current.x + i] != true && tmp_road.current.x + i != tmp_road.previous.x) {

				visited[tmp_road.current.y][tmp_road.current.x + i] = true;
				update_to_insert(to_insert, tmp_road);
				to_insert.current.x = tmp_road.current.x + i;
				to_insert.current.y = tmp_road.current.y;
				queue.push(to_insert);
			}
			else if (tmp_road.current.x + i >= 0 && tmp_road.current.x + i < map_dimensions.w && map[tmp_road.current.y][tmp_road.current.x + i] == '*' &&
				visited[tmp_road.current.y][tmp_road.current.x + i] != true && tmp_road.current.x + i != tmp_road.previous.x) {

				visited[tmp_road.current.y][tmp_road.current.x + i] = true;
				to_insert.cost = tmp_road.cost;
				to_insert.cost++;
				add_edge_to_vertex(_vertex, { tmp_road.current.y, tmp_road.current.x + i }, to_insert.cost);
			}
		}

		if (!queue.empty()) {
			tmp_road = queue.top();
			controler = 1;
		}
	} while (!queue.empty());

	for (int i = 0; i < map_dimensions.h; ++i) {
		delete visited[i];
		visited[i] = nullptr;
	}
	delete[] visited;
	visited = nullptr;
}

int main() {
	dimensions map_dimensions = { -1, -1 };
	coordinates tmp_coordinates = { -1, -1 }, tmp_city_coordinates = { -1,-1 };
	vertex tmp_vertex, tmp_vertex_2;
	_string tmp_name;
	tmp_name = "";
	_vector<vertex> vertexes;
	_vector<_string> transit_route;
	int number_of_airlines = 0, number_of_questions = 0;
	size_t road_counter = 0;
	char data[MAX_SIZE];

	//wczytywanie wymiarow mapy
	std::cin >> map_dimensions.w >> map_dimensions.h;

	char** map = new char* [map_dimensions.h];

	for (int i = 0; i < map_dimensions.h; i++) {
		map[i] = new char[map_dimensions.w + 1];
	}

	(void)getchar();

	//wczytywanie mapy
	for (int i = 0; i < map_dimensions.h; i++) {
		for (int j = 0; j < map_dimensions.w + 1; j++) {
			map[i][j] = (char)getchar();
			if (map[i][j] == '*') {
				tmp_vertex.set_coordinates({ i,j });
				vertexes.push_back(tmp_vertex);
			}
			else if (map[i][j] == '#') {
				road_counter++;
			}
		}
		map[i][map_dimensions.w] = '\0';
	}

	//budowanie grafu
	if (road_counter > 0) {
		for (size_t i = 0; i < vertexes.size(); i++) {
			get_the_edges(map, vertexes[i].get_coordinates(), map_dimensions, vertexes[i]);
			tmp_coordinates = get_position_of_first_or_last_letter(map, vertexes[i].get_coordinates().y, vertexes[i].get_coordinates().x, map_dimensions);
			tmp_name = get_city_name(map, tmp_coordinates, map_dimensions);
			vertexes[i].set_name(tmp_name);
		}
	}
	else {
		for (size_t i = 0; i < vertexes.size(); i++) {
			tmp_coordinates = get_position_of_first_or_last_letter(map, vertexes[i].get_coordinates().y, vertexes[i].get_coordinates().x, map_dimensions);
			tmp_name = get_city_name(map, tmp_coordinates, map_dimensions);
			vertexes[i].set_name(tmp_name);
		}
	}

	//inicjalizacja hash map
	hash_map coordinates_map(vertexes.size());
	hash_map city_map(vertexes.size() * 3);

	//budowanie hash map
	for (size_t i = 0; i < vertexes.size(); i++) {
		tmp_vertex = vertexes[i];
		coordinates_map.add_c(vertexes[i]);
		city_map.add(vertexes[i]);
	}

	//zwalnianie pamieci mapy
	for (int k = 0; k < map_dimensions.h; k++) {
		delete[] map[k];
		map[k] = nullptr;
	}

	delete[] map;
	map = nullptr;

	//wczytywanie liczby polaczen lotniczych
	std::cin >> number_of_airlines;
	tmp_name = "";

	(void)getchar();
	char* token;
	const char delimiter[3] = " \n";
	int time_of_travel = 0;

	//wczytywanie polaczen lotniczych, dodawanie ich do grafu
	for (int i = 0; i < number_of_airlines; i++) {
		fgets(data, MAX_SIZE, stdin);

		token = strtok(data, delimiter);
		tmp_name = token;

		tmp_vertex = coordinates_map.find_c(city_map.find(tmp_name)->get_vertex().get_coordinates())->get_vertex();

		token = strtok(NULL, delimiter);
		tmp_name = token;
		tmp_coordinates = city_map.find(tmp_name)->get_vertex().get_coordinates();

		token = strtok(NULL, delimiter);
		tmp_name = token;

		time_of_travel = atoi(token);
		add_edge_to_vertex(tmp_vertex, tmp_coordinates, time_of_travel);
		coordinates_map.change_c(tmp_vertex.get_coordinates(), tmp_vertex);
	}

	std::cin >> number_of_questions;
	(void)getchar();
	int type_of_action = -1;

	//realizowanie zapytan o droge
	for (int i = 0; i < number_of_questions; i++) {
		fgets(data, MAX_SIZE, stdin);

		token = strtok(data, delimiter);
		tmp_name = token;
		tmp_vertex = city_map.find(tmp_name)->get_vertex();

		token = strtok(NULL, delimiter);
		tmp_name = token;
		tmp_coordinates = city_map.find(tmp_name)->get_vertex().get_coordinates();

		token = strtok(NULL, delimiter);
		type_of_action = atoi(token);

		switch (type_of_action) {
		case 0:
			if (tmp_vertex.get_coordinates() == tmp_coordinates) {
				cout << "0" << endl;
			}
			else {
				cout << dijkstra(tmp_vertex.get_coordinates(), tmp_coordinates, coordinates_map, vertexes, transit_route) << endl;
			}
			break;
		case 1:
			if (tmp_vertex.get_coordinates() == tmp_coordinates) {
				cout << "0" << endl;
			}
			else {
				cout << dijkstra(tmp_vertex.get_coordinates(), tmp_coordinates, coordinates_map, vertexes, transit_route);

				if (transit_route.size() > 0) {
					for (size_t k = transit_route.size() - 1; k > 0; k--) {
						cout << " " << transit_route[k];
					}
					cout << " " << transit_route[0];
				}
			}
			cout << endl;
			break;
		default:
			break;
		}
	}

	return 0;
}


