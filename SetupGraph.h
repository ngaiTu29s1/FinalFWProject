#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <string.h>
#include "FloydWarshall.h"


sf::Vector2f rotate(sf::Vector2f old_vec, float angle);
sf::Vector2f after_rotate(sf::Vector2f old_orig, float angle);


typedef struct line{
    sf::Vector2f head, tail;
    sf::VertexArray edge;
    void set_line(sf::Vector2f, sf::Vector2f);

    int weight;
    sf::Font font;
    sf::Text text_w;
    sf::Vector2f weight_coor;
    bool direct;

    // Constructor
    struct line() : edge(sf::Lines, 2), weight(0), direct(false) {
    };
} line;


void set_graph(std::vector<sf::CircleShape> &graph, int num_vertices);
void set_vertices(std::vector<sf::Text> &vertices, std::vector<sf::CircleShape> graph,const sf::Font &font, int num_vertices);
void set_lines(std::vector<std::vector<line>> &line_list, std::vector<sf::CircleShape> graph, int num_vertices, const sf::Font &font, Matrix matrix);
void subrun(sf::Sprite* runner_sprite, sf::Vector2f start, sf::Vector2f end);
void run(sf::Sprite* runner_sprite, std::vector<sf::CircleShape> graph, std::vector<int> path);