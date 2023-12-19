// Author           : Piotr Lachowicz / MikyTuberr
// Created On       : 2023-05-25
// Last Modified By : Piotr Lachowicz / MikyTuberr
// Last Modified On : 2023-12-19
//
// Licensed under Apache License 2.0
//
// REALIZED WITH NO STL

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdint>

#include "DataStructures/String.h"
#include "DataStructures/Vector.h"
#include "DataStructures/PriorityQueue.h"
#include "DataStructures/Queue.h"

#include "DataStructures/Graph/Edge.h"
#include "DataStructures/Graph/Vertex.h"

#include "DataStructures/HashMap/HashNode.h"
#include "DataStructures/HashMap/HashMap.h"

#include "Structs/Coordinates.h"
#include "Structs/Dimensions.h"
#include "Structs/Road.h"

#define MAX_SIZE 20

int dijkstra(coordinates& start_coordinates, coordinates& end_coordinates, HashMap& coordinates_map, Vector<Vertex>& vertexes, Vector<String>& transit_route) {
	Vertex source_vertex, destination_vertex;
	coordinates tmp_coordinates = { -1, -1 }, source_coordinates = { -1, -1 }, destination_coordinates = { -1, -1 };
	String name;
	HashNode tmp;
	PriorityQueue<HashNode> queue;
	int  time_of_travel = -1, controler = 0;

	for (size_t i = 0; i < vertexes.size(); i++) {
		tmp_coordinates = coordinates_map.find_c(vertexes[i].get_coordinates())->get_vertex().get_coordinates();
		if (tmp_coordinates == start_coordinates) {
			Vertex* tmp_vertex = &coordinates_map.find_c(start_coordinates)->get_vertex();
			tmp_vertex->set_cost(0);
			tmp_vertex->set_visited(false);
			queue.push(*coordinates_map.find_c(start_coordinates));
		}
		else {
			Vertex* tmp_vertex = &coordinates_map.find_c(tmp_coordinates)->get_vertex();
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

String get_city_name(char**& map, const coordinates& letter_coordinates, const dimensions& map_dimensions) {
    String tmp;
	tmp = "";
	if (letter_coordinates.x > 0 && isalnum(map[letter_coordinates.x][letter_coordinates.y - 1])) {
		for (int j = 0; j < map_dimensions.w; j++) {
			if (letter_coordinates.x - j >= 0 && isalnum(map[letter_coordinates.x][letter_coordinates.y - j])) {
				tmp += map[letter_coordinates.x][letter_coordinates.y - j];
			}
			else {
				tmp.reverse();
				return tmp;
			}
		}
	}
	else if (letter_coordinates.x + 1 < map_dimensions.w && isalnum(map[letter_coordinates.x][letter_coordinates.y + 1])) {
		for (int j = 0; j < map_dimensions.w; j++) {
			if (isalnum(map[letter_coordinates.x][letter_coordinates.y + j])) {
				tmp += map[letter_coordinates.x][letter_coordinates.y + j];
			}
			else {
				return tmp;
			}
		}
	}
	else if (isalnum(map[letter_coordinates.x][letter_coordinates.y])) {
		tmp += map[letter_coordinates.x][letter_coordinates.y];
	}
	return tmp;
}

void add_edge_to_vertex(Vertex& vertex, const coordinates& neighbour_coordinates, int tmp_time) {
    Edge tmp_edge;
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

void get_the_edges(char** map, coordinates starting_coordinates, const dimensions map_dimensions, Vertex& _vertex) {
	road tmp_road, to_insert;
	int current_x = tmp_road.current.x = starting_coordinates.x;
	int current_y = tmp_road.current.y = starting_coordinates.y;
    Queue<road> queue;
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
			if (current_x + i >= 0 && current_x + i < map_dimensions.h &&
                !visited[current_x + i][current_y] &&
				map[current_x + i][current_y] == '#' && current_x + i != tmp_road.previous.x) {

				visited[current_x + i][current_y] = true;
				update_to_insert(to_insert, tmp_road);
				to_insert.current.y = current_y;
				to_insert.current.x = current_x + i;
				queue.push(to_insert);
			}
			else if (current_x + i >= 0 && current_x + i < map_dimensions.h &&
                     !visited[current_x + i][current_y] &&
				map[current_x + i][current_y] == '*' && current_x + i != tmp_road.previous.x) {

				visited[current_x + i][current_y] = true;
				to_insert.cost = tmp_road.cost;
				to_insert.cost++;
				add_edge_to_vertex(_vertex, { current_x + i, current_y }, to_insert.cost);
			}
			if (current_y + i >= 0 && current_y + i < map_dimensions.w && map[current_x][current_y + i] == '#' &&
                !visited[current_x][current_y + i] && current_y + i != tmp_road.previous.y) {

				visited[current_x][current_y + i] = true;
				update_to_insert(to_insert, tmp_road);
				to_insert.current.y = current_y + i;
				to_insert.current.x = current_x;
				queue.push(to_insert);
			}
			else if (current_y + i >= 0 && current_y + i < map_dimensions.w && map[current_x][current_y + i] == '*' &&
                     !visited[current_x][current_y + i] && current_y + i != tmp_road.previous.y) {

				visited[current_x][current_y + i] = true;
				to_insert.cost = tmp_road.cost;
				to_insert.cost++;
				add_edge_to_vertex(_vertex, { current_x, current_y + i }, to_insert.cost);
			}
		}

		if (!queue.empty()) {
			tmp_road = queue.top();
			current_x = tmp_road.current.x;
			current_y = tmp_road.current.y;
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
    Vertex tmp_vertex, tmp_vertex_2;
    String tmp_name;
	tmp_name = "";
    Vector<Vertex> vertexes;
    Vector<String> transit_route;
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
			tmp_coordinates = get_position_of_first_or_last_letter(map, vertexes[i].get_coordinates().x, vertexes[i].get_coordinates().y, map_dimensions);
			tmp_name = get_city_name(map, tmp_coordinates, map_dimensions);
			vertexes[i].set_name(tmp_name);
		}
	}
	else {
		for (size_t i = 0; i < vertexes.size(); i++) {
			tmp_coordinates = get_position_of_first_or_last_letter(map, vertexes[i].get_coordinates().x, vertexes[i].get_coordinates().y, map_dimensions);
			tmp_name = get_city_name(map, tmp_coordinates, map_dimensions);
			vertexes[i].set_name(tmp_name);
		}
	}

	//inicjalizacja hash map
    HashMap coordinates_map(vertexes.size());
    HashMap city_map(vertexes.size() * 3);

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
				std::cout << "0" << std::endl;
			}
			else {
				std::cout << dijkstra(tmp_vertex.get_coordinates(), tmp_coordinates, coordinates_map, vertexes, transit_route) << std::endl;
			}
			break;
		case 1:
			if (tmp_vertex.get_coordinates() == tmp_coordinates) {
				std::cout << "0" << std::endl;
			}
			else {
				std::cout << dijkstra(tmp_vertex.get_coordinates(), tmp_coordinates, coordinates_map, vertexes, transit_route);

				if (transit_route.size() > 0) {
					for (size_t k = transit_route.size() - 1; k > 0; k--) {
						std::cout << " " << transit_route[k];
					}
					std::cout << " " << transit_route[0];
				}
			}
			std::cout << std::endl;
			break;
		default:
			break;
		}
	}

	return 0;
}


