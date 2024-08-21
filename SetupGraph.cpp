#include "SetupGraph.h"


#define sin(x) sin(x*3.141/180)
#define cos(x) cos(x*3.141/180)
#define RADIUS 80.f
#define MINTCONST 300.f

sf::Vector2f rotate(sf::Vector2f old_vec, float angle) {
    sf::Vector2f rotated;
    rotated.x = (old_vec.x) * cos(angle) - (old_vec.y) * sin(angle);
    rotated.y = (old_vec.x) * sin(angle) + (old_vec.y) * cos(angle);
    return rotated;
}

sf::Vector2f after_rotate(sf::Vector2f old_orig, float angle) {
    sf::Vector2f new_orig;
    new_orig = rotate(old_orig, angle);
    return new_orig;
}

void set_graph(std::vector<sf::CircleShape>& graph, int num_vertices) {
    graph.resize(num_vertices);
    double angle = 360.0 / num_vertices;
    sf::Vector2f root;
    for (int i = 0; i < num_vertices; i++) {
        graph[i].setRadius(RADIUS);
        graph[i].setFillColor(sf::Color(223, 228, 235));
        graph[i].setPointCount(num_vertices);
        if (i == 0) {
            graph[i].setPosition(0.f, -300.f);
            root = graph[0].getPosition();
        }
        else {
            graph[i].setPosition(after_rotate(root, i * angle));
        }
    }

    for (int i = 0; i < num_vertices; i++) {
        sf::Vector2f move(760.f, 400.f);
        graph[i].setPosition(graph[i].getPosition() + move);
    }

}

void set_vertices(std::vector<sf::Text>& vertices, std::vector<sf::CircleShape> graph, const sf::Font &font, int num_vertices) {
    vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        vertices[i].setFont(font);
        vertices[i].setFillColor(sf::Color(201, 16, 35));
        vertices[i].setCharacterSize(36);
        vertices[i].setString(std::to_string(i));
        vertices[i].setPosition(graph[i].getPosition() + sf::Vector2f(-15.f, -25.f) + sf::Vector2f(RADIUS, RADIUS));
    }
}


void line::set_line(sf::Vector2f head, sf::Vector2f tail) {
    this->head = head;
    this->tail = tail;
    edge[0].position = this->head;
    edge[1].position = this->tail;
}

void set_lines(std::vector<std::vector<line>> &line_list, std::vector<sf::CircleShape> graph, int num_vertices, const sf::Font &font, Matrix matrix){
    line_list.resize(num_vertices, std::vector<line>(num_vertices));
    for (int i = 0; i < num_vertices; i++) {
        sf::Vector2f head_root = graph[i].getPosition();
        for (int j = 0; j < i /*num_vertices*/; j++) {
            if (matrix.mat[i][j] == 0 || matrix.mat[i][j] == INF) continue;
            sf::Vector2f tail_root = graph[j].getPosition();
            sf::Vector2f head = head_root + sf::Vector2f(RADIUS, RADIUS);
            sf::Vector2f tail = tail_root + /*graph[i].getPoint(i) +*/ sf::Vector2f(RADIUS, RADIUS);
            line_list[i][j].set_line(head, tail);
            line_list[i][j].edge[0].color = sf::Color::Red;
            line_list[i][j].edge[1].color = sf::Color::Red;

            line_list[i][j].weight_coor = sf::Vector2f((head.x + tail.x) / 2, (head.y + tail.y) / 2);
            line_list[i][j].weight = matrix.mat[i][j];
            /*line_list[i][j].direct = true;*/
            line_list[i][j].text_w.setFont(font);
            line_list[i][j].text_w.setFillColor(sf::Color(201, 16, 35));
            line_list[i][j].text_w.setCharacterSize(36);
            line_list[i][j].text_w.setString(std::to_string(line_list[i][j].weight));
            line_list[i][j].text_w.setPosition(line_list[i][j].weight_coor);
        }
    }
}


void subrun(sf::Sprite* runner_sprite, sf::Vector2f start, sf::Vector2f end)
{
	sf::Vector2f move = end - start;
	(*runner_sprite).move(sf::Vector2f((move.x) / MINTCONST, (move.y) / MINTCONST));
}

void run(sf::Sprite* runner_sprite, std::vector<sf::CircleShape> graph, std::vector<int> path) {
    static int i = 0;
    if ((i < path.size() - 1) && (path.size() > 1)) {
        subrun(runner_sprite, graph[path[i]].getPosition(), graph[path[i+1]].getPosition());
        if ((abs((int)((*runner_sprite).getPosition().x) - (int)graph[path[i+1]].getPosition().x)) < 20.f && (abs((int)((*runner_sprite).getPosition().y) - (int)graph[path[i+1]].getPosition().y)) < 20.f)
        {
            i++;
        }
	}
}
