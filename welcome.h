#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;

int getRow();
int getColumn();
void setText(sf::Text& text, int x, int y);
void processInput(sf::Text& userName, sf::Event& event);
void welcomeWindow();