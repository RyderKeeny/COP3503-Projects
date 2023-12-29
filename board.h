#pragma once
#include "tiles.h"
#include "welcome.h"
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;

class board {
	
public:
	vector<vector<tile>> gameField;
    vector<sf::Texture> textures; // A vector to hold textures
    bool gameOver = false;
    bool gameWin = false;
    bool isPaused = false;
    bool debugMode = false; 

    int elapsedPausedTime = 0;

	board();
	void boardConfig();
    void setMinePositions();
    void tileDisplayRecurion(sf::RenderWindow& window, sf::Event& event, tile& T);
    void happyFaceButton();
    bool youWin();
    void pausePlayButton();
    void debug();
    sf::Clock gameClock;  // Game clock for tracking elapsed time
    sf::Sprite digitSprites[10]; // Array of digit sprites for the clock
    vector<sf::Sprite> gameTime();
};

board::board() {
}

void board::setMinePositions() {
    tile t;
    int mineCount = t.getMineCount();
    int rows = gameField.size();
    int cols = gameField[0].size();
    random_device rd;  // Random number generator
    mt19937 rng(rd());
    uniform_int_distribution<int> uniRow(0, rows - 1);
    uniform_int_distribution<int> uniCol(0, cols - 1);

    int minesPlaced = 0;
    while (minesPlaced < mineCount) {
        int r = uniRow(rng); // Random row
        int c = uniCol(rng); // Random column

        // Place mine if not already a mine
        if (!gameField[r][c].isMine) {
            gameField[r][c].setAsMine();
            minesPlaced++;
        }
    }




}

void board::boardConfig() {
    int rowNum = getRow();
    int colNum = getColumn();
    gameOver = false;
    if (rowNum == -1 || colNum == -1) {
        cout << "Error: Invalid row or column number" << endl;
        return; // Exit if row or column number is invalid
    }

    gameField = vector<vector<tile>>(rowNum, vector<tile>(colNum));    // Initialize the gameField vector
    for (int i = 0; i < rowNum; ++i) {    // Set row and column for each tile
        for (int j = 0; j < colNum; ++j) {
            gameField[i][j].row = i;
            gameField[i][j].col = j;
        }
    }
    for (int i = 0; i < rowNum; ++i) {    // Calculate adjacent gameField for each tile
        for (int j = 0; j < colNum; ++j) {
            gameField[i][j].adjacentTiles(gameField);
        }
    }
    setMinePositions();    // setup for randomly placing mines

}

void board::tileDisplayRecurion(sf::RenderWindow& window, sf::Event& event, tile& T) {
    // Reveal the tile using the existing Revealed() function
    if (!T.Revealed(T.hiddenSprite, window, event, T)) {
        return; // If the tile was already revealed or flagged, return
    }
    if (T.isMine) {
        return;
    }

    int surroundingMines = T.surroundingMines();    // Calculate surrounding mines
    if (surroundingMines == 0) {
        for (auto* adjTile : T.adjacent) {        // If there are no surrounding mines, reveal adjacent tiles recursively
            if (adjTile != nullptr && !adjTile->isRevealed && !adjTile->isMine) {
                tileDisplayRecurion(window, event, *adjTile);
            }
        }
    }
}

void board::happyFaceButton() {
    // Reset each tile on the board
    for (auto& row : gameField) {
        for (auto& tile : row) {
            tile.reset();
        }
    }

    gameOver = false;
    isPaused = false;
    gameWin = false;

    // Randomly place mines again
    setMinePositions();
}

bool board::youWin() {
    for (const auto& row : gameField) {
        for (const auto& tile : row) {
            // If a tile is a mine and not flagged, the player hasn't won
            if (tile.isMine && !tile.flagged) {
                return false; // Return false immediately if an unflagged mine is found
            }
        }
    }

    // If all mines are flagged, then the player has won
    gameWin = true;
    return true;
}

void board::pausePlayButton() {
    isPaused = !isPaused;

}

void board::debug() {
    debugMode = !debugMode; // Toggle the debug mode
}


vector<sf::Sprite> board::gameTime() {
    vector<sf::Sprite> timeSprites;

    // Timer positions and dimensions
    const int digitWidth = 21;
    const int digitHeight = 32; // Assuming height is 32, adjust if different
    int columns = getColumn();
    int rows = getRow();
    sf::Vector2f minPosition((columns * 32) - 97, 32 * (rows + 0.5) + 16);
    sf::Vector2f secPosition((columns * 32) - 54, 32 * (rows + 0.5) + 16);

    sf::Time elapsedTime = gameClock.getElapsedTime();
    int totalSeconds = static_cast<int>(elapsedTime.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    digitSprites[minutes / 10].setPosition(minPosition.x, minPosition.y);
    digitSprites[minutes % 10].setPosition(minPosition.x + digitWidth, minPosition.y);
    digitSprites[seconds / 10].setPosition(secPosition.x, secPosition.y);
    digitSprites[seconds % 10].setPosition(secPosition.x + digitWidth, secPosition.y);

    timeSprites.push_back(digitSprites[minutes / 10]);
    timeSprites.push_back(digitSprites[minutes % 10]);
    timeSprites.push_back(digitSprites[seconds / 10]);
    timeSprites.push_back(digitSprites[seconds % 10]);

    return timeSprites;
}
