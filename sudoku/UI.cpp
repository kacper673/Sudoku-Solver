#include "UI.h"

graphics::graphics() {

    
    if (!font.loadFromFile("C:\\Users\\alber\\Desktop\\Projekty\\sudoku\\sudoku\\assets\\arial.ttf")) {
        std::cout << "Failed to load font" << std::endl;
    }
    else {
        std::cout << "Font has been loaded successfully" << std::endl;
    }
    //ustawianie czcionki
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    //ladowanie tla
    if (!backgroundTexture.loadFromFile("C:\\Users\\alber\\Desktop\\Projekty\\sudoku\\sudoku\\assets\\background.png")) {
        std::cout << "Failed to load background" << std::endl;
    }
    else {
        std::cout << "Background has been loaded successfully" << std::endl;
        background.setTexture(backgroundTexture);
    }
    //ustawianie planszy
    box.setSize(sf::Vector2f(80, 80));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color::Black);
  
}
   
void UI(graphics& graphics){

    sudoku sudoku;
    const int boxSize = 80;
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Sudoku");
    sf::Vector2u windowSize = window.getSize();
    sudoku.functionName = __FUNCTION__;

   
    //tworzenie sudoku
    sudoku.exampleSudoku();
    //generateRand(sudoku);
    findingSpaces(sudoku,sudoku.tab);


   std::thread solver([&sudoku]() {
       solve(sudoku);
       });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(graphics.background);
        graphics.boxes.clear();

        //tworzenie plnaszy z 81 kwadratow 
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sf::RectangleShape box = graphics.box;
                box.setPosition(windowSize.x / 40 + j * boxSize, windowSize.y / 40 + i * boxSize);
                graphics.boxes.push_back(box);
            }
        }
       
        //rysowanie planszy (81 kwadratow)
       
        for (auto& it : graphics.boxes) {
            window.draw(it);
        }
        
        //wektor do zapisywania wartosci tablicy kazdorzowo ustalanie cech dla value i zapisywanie ich do wektora
        std::vector<sf::Text> values;
        sf::FloatRect numberBounds;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sf::Text value;
                value.setFont(graphics.font);
                value.setCharacterSize(boxSize/2);
                value.setFillColor(sf::Color(51,133,255));

                std::lock_guard<std::mutex> lock(sudoku.m);
                int value_num = sudoku.tab[i][j];

                if (value_num == 0) {
                    value.setString(" ");
                }
                else {
                    value.setString(std::to_string(sudoku.tab[i][j]));
                }

                numberBounds = value.getLocalBounds();
                value.setOrigin(numberBounds.left + numberBounds.width / 2, numberBounds.top + numberBounds.height / 2);
                value.setPosition(windowSize.x / 40 + (j * boxSize) + boxSize/2, windowSize.y / 40 + (i * boxSize) + boxSize/2);

                values.push_back(value);
            }
        }
        //rysownaie wartosci na planszy

        for (auto& it : values) {
            window.draw(it);
        }
        window.display();
    }
    solver.join();
}