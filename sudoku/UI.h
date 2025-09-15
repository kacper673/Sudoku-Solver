#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "sudoku.h"
#include <string>
#include <thread>
#include <chrono>



class graphics {
public:


	sf::Font font;
	sf::Text text;
	sf::FloatRect textBounds; 
	//siatka planszy
	sf::RectangleShape box; 
	std::vector<sf::RectangleShape> boxes;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	
	graphics();

};

void UI(graphics& graphics);

#endif