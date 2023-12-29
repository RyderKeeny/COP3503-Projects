#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;

class tile {
public:
	int tileCount = 0;
	int mineCount = 0;
	int flagCount = 0;
	int row = 0; // row size
	int col = 0; // column size 
	vector<tile*> adjacent; // set for each tile to count the tiles surrounding it
	int adjacentMines = 0;
	bool isMine = false;
	bool isRevealed = false;
	bool flagged = false;

	tile();
	int getMineCount();
	bool spriteClickedOn(const sf::Sprite& sprite, const sf::RenderWindow& window);
	bool getFlagged(sf::Sprite& sprite, sf::RenderWindow& window, sf::Event& event, tile& T);
	bool Revealed(sf::Sprite& sprite, sf::RenderWindow& window, sf::Event& event, tile& T);
	void setAsMine();
	void adjacentTiles(vector<vector<tile>>& grid);
	int surroundingMines() const ;
	void reset(); // resets all tile values for when restart button is clicked
	sf::Sprite sprite;
	sf::Sprite hiddenSprite;  // Sprite for the hidden tile
	sf::Sprite revealedSprite;  // Sprite for the revealed tile
	sf::Sprite mineSprite;
	sf::Sprite flagSprite;
	sf::Sprite num1, num2, num3, num4, num5, num6, num7, num8;
	sf::Sprite happyFace;
	sf::Sprite winFace, loseFace;
	sf::Sprite leaderboard;
	sf::Sprite minSprites;
	sf::Sprite secSprites;
	sf::Sprite pauseSprite, playSprite, debug;
	sf::Texture texture;
};

tile::tile() {

}

int tile::getMineCount() {
	string tempMine, throwaway1, throwaway2;
	fstream file("../files/config.cfg");
	if (file.is_open()) {
		getline(file, throwaway1);
		getline(file, throwaway2);
		getline(file, tempMine);
		file.close();
	}
	else {
		cout << "Error opening config file for row" << endl;
		return -1;
	}
	int mineCount = stoi(tempMine);
	return mineCount;
}

bool tile::spriteClickedOn(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	bool clicked = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);		// Get the position of the mouse click
		sf::IntRect textureRect = sprite.getTextureRect();		// Get the texture rectangle of the sprite
		sf::FloatRect bounds(sprite.getPosition().x, sprite.getPosition().y, static_cast<float>(textureRect.width), static_cast<float>(textureRect.height));
		if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			clicked = true;
		}
	}
	return clicked;
}

bool tile::getFlagged(sf::Sprite& sprite, sf::RenderWindow& window, sf::Event& event, tile& T) {
	if (isRevealed == false) { // only if not revealed yet
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Right) {
				if (spriteClickedOn(sprite, window)) {
					flagged = !flagged;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
					cout << "flag status is : " << flagged << endl;
				
				}
			}
		}
	}
	return flagged;
}

bool tile::Revealed(sf::Sprite& sprite, sf::RenderWindow& window, sf::Event& event, tile& T) {
	if (!isRevealed) {
		isRevealed = true;
		return true; // Tile revealed
	}
	return false; // Tile was already revealed
}

void tile::setAsMine() {
	isMine = true;
}

void tile::adjacentTiles(vector<vector<tile>>& grid) { // stores the adjacent tiles values within the vector
	int rows = grid.size();
	int cols = grid[0].size();

	adjacent.clear(); // Clear existing adjacent tiles

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int adjRow = row + i;
			int adjCol = col + j;

			// Check if the adjacent position is within the bounds of the grid and not the tile itself
			if (adjRow >= 0 && adjRow < rows && adjCol >= 0 && adjCol < cols && !(i == 0 && j == 0)) {
				adjacent.push_back(&grid[adjRow][adjCol]);
			}
		}
	}
}

int tile::surroundingMines() const { // counts the amount of mines surrounding the current tile 
	int count = 0;
	if (!isMine) {
		for (const auto* adjTile : adjacent) {
			if (adjTile && adjTile->isMine) { // Check if adjTile is not null before dereferencing
				count++;
			}
		}
	}

	return count;
}



void tile::reset() {
	flagged = false;
	isMine = false;
	isRevealed = false;
	

}