#include "welcome.h"
using namespace std;


int getColumn() {
    string tempColumn;
    fstream file("../files/config.cfg");
    if (file.is_open()) {
        getline(file, tempColumn);
        file.close();
    }
    else {
        cout << "Error opening config file for row" << endl;
        return -1;
    }
    int row = stoi(tempColumn);
    return row;
}

int getRow() {
    string throwaway, tempRow;
    fstream file("../files/config.cfg");
    if (file.is_open()) {
        getline(file, throwaway);
        getline(file, tempRow);
        file.close();
    }
    else {
        cout << "Error opening config file for column" << endl;
        return -1;
    }
    int row = stoi(tempRow);
    return row;
}

void setText(sf::Text & text, int x, int y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
    
}

void processInput(sf::Text& userName, sf::Event& event) {
    if (event.text.unicode < 128) {
        char enteredChar = static_cast<char>(event.text.unicode);
        string name = userName.getString();
        name = name.substr(0, name.size() - 1);
        if (isalpha(enteredChar) && name.length() < 10) {
            name += tolower(enteredChar);
        }
        else if (enteredChar == '\b' && !name.empty()) {
            name = name.substr(0, name.size() - 1);
        }
        if (!name.empty()) {
            name[0] = toupper(name[0]);
        }

        name += "|";
        userName.setString(name);
    }
}

void welcomeWindow() {
    int windowRow = getRow();
    windowRow = (windowRow * 32) + 100;
    int windowColumn = getColumn();
    windowColumn = (windowColumn * 32) ;
    cout << "Window dimensions: " << windowColumn << " x " << windowRow << endl;

    sf::RenderWindow window(sf::VideoMode(windowColumn, windowRow), "Welcome Window!");
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        cout << "Error loading font.ttf" << std::endl;
    }

    sf::Text welcome("WELCOME TO MINESWEEPER!", font);
    int width = ((windowColumn / 2) );
    int height1 = ((windowRow / 2- 150));
    welcome.setStyle(sf::Text::Underlined);
    welcome.setFillColor(sf::Color::White);
    setText(welcome, width, height1);
    cout << "welcome position: " << width << " x " << height1 << endl;
    sf::Text enterYourName("Enter your name:", font);
    int height2 = ((windowRow / 2) - 75);
    enterYourName.setFillColor(sf::Color::Yellow);
    setText(enterYourName, width, height2);
    cout << "enterYourName position: " << width << " x " << height2 << endl;
    sf::Text userName("|", font);
    int height3 = ((windowRow / 2) - 45);
    setText(userName, width, height3);
    userName.setFillColor(sf::Color::Yellow);

    while (window.isOpen())
    {      
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                processInput(userName, event);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    string name = userName.getString();
                    if (name.size() > 1) {
                        window.close(); // Close the current welcome window
                    }
                }
            }
        }

        window.clear(sf::Color::Blue);    
        window.draw(welcome);
        window.draw(enterYourName);
        window.draw(userName);

        window.display();
    }
}