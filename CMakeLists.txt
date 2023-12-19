cmake_minimum_required(VERSION 3.25)
project(HowToGetThere)

set(CMAKE_CXX_STANDARD 23)

add_executable(HowToGetThere HowToGetThere/main.cpp HowToGetThere/DataStructures/String.h HowToGetThere/DataStructures/String.cpp
        HowToGetThere/DataStructures/Vector.h HowToGetThere/DataStructures/PriorityQueue.h HowToGetThere/DataStructures/Queue.h
        HowToGetThere/DataStructures/Graph/Edge.h HowToGetThere/Structs/Coordinates.h HowToGetThere/Structs/Dimensions.h 
        HowToGetThere/DataStructures/Graph/Edge.cpp HowToGetThere/DataStructures/Graph/Vertex.h HowToGetThere/DataStructures/Graph/Vertex.cpp 
        HowToGetThere/Structs/Road.h HowToGetThere/DataStructures/HashMap/HashNode.h HowToGetThere/DataStructures/HashMap/HashNode.cpp 
        HowToGetThere/DataStructures/HashMap/HashMap.h HowToGetThere/DataStructures/HashMap/HashMap.cpp)
