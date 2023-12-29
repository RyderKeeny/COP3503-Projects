#include "gamewindow.h"
#include "tiles.h"
#include "board.h"
#include "welcome.h"
using namespace std;

void gameWindow() {
    int windowRow = getRow();
    windowRow = (windowRow * 32) + 100;
    int windowColumn = getColumn();
    windowColumn = (windowColumn * 32);
    cout << "Window dimensions: " << windowColumn << " x " << windowRow << endl;

    board b;
    tile t;
    b.boardConfig(); // Configure the board 

    sf::RenderWindow window(sf::VideoMode(windowColumn, windowRow), "Minesweeper!");
   
    sf::Texture digits;
    if (!digits.loadFromFile("../files/images/digits.png")) {
        cout << "Error loading digits texture." << endl;
        return;
    }
    else {
        cout << "Digits texture loaded successfully." << endl; // Debug statement
    }
    
    sf::Texture hiddenTexture, revealedTexture, mineTexture,
                num1, num2, num3, num4, num5, num6, num7, num8,
                pause, play, happy, win, lose, debug, leaderboard, flag;
    if (!hiddenTexture.loadFromFile("../files/images/tile_hidden.png") ||
        !revealedTexture.loadFromFile("../files/images/tile_revealed.png") || 
        !mineTexture.loadFromFile("../files/images/mine.png") ||
        !num1.loadFromFile("../files/images/number_1.png") ||
        !num2.loadFromFile("../files/images/number_2.png") ||
        !num3.loadFromFile("../files/images/number_3.png") ||
        !num4.loadFromFile("../files/images/number_4.png") ||
        !num5.loadFromFile("../files/images/number_5.png") ||
        !num6.loadFromFile("../files/images/number_6.png") ||
        !num7.loadFromFile("../files/images/number_7.png") ||
        !num8.loadFromFile("../files/images/number_8.png") ||
        !pause.loadFromFile("../files/images/pause.png") ||
        !play.loadFromFile("../files/images/play.png") ||
        !debug.loadFromFile("../files/images/debug.png") ||
        !happy.loadFromFile("../files/images/face_happy.png") ||
        !lose.loadFromFile("../files/images/face_lose.png") ||
        !win.loadFromFile("../files/images/face_win.png") ||
        !leaderboard.loadFromFile("../files/images/leaderboard.png") ||
        !digits.loadFromFile("../files/images/digits.png") ||
        !flag.loadFromFile("../files/images/flag.png") ){
        cout << "Error loading texture:" << endl;
        return;
    }
    int buttonPos_x = getColumn();
    int buttonPos_y = getRow();
    int happy_x = ((buttonPos_x / 2.0) * 32) - 32;
    int happy_y = ((buttonPos_y + 0.5) * 32);
    int debug_x = ((buttonPos_x * 32) - 304);
    int debug_y = ((buttonPos_y + 0.5)  * 32);
    int pause_x = ((buttonPos_x * 32) - 240);
    int pause_y = ((buttonPos_y + 0.5) * 32);
    int leader_x = ((buttonPos_x * 32) - 176);
    int leader_y = ((buttonPos_y + 0.5) * 32);
    sf::Sprite happyFace(happy);
    sf::Sprite sadFace(lose);
    sf::Sprite coolFace(win);
    sf::Sprite leader(leaderboard);
    sf::Sprite playButton(play);
    sf::Sprite pauseButton(pause);
    sf::Sprite debugButton(debug);
    sf::Sprite secdigit(digits);
    sf::Sprite mindigit(digits);
    happyFace.setPosition(happy_x, happy_y);
    sadFace.setPosition(happy_x, happy_y);
    coolFace.setPosition(happy_x, happy_y); 
    leader.setPosition(leader_x, leader_y);
    playButton.setPosition(pause_x, pause_y);
    pauseButton.setPosition(pause_x, pause_y);
    debugButton.setPosition(debug_x, debug_y);
    t.happyFace = happyFace;
    t.loseFace = sadFace;
    t.winFace = coolFace;
    t.leaderboard = leader;
    t.pauseSprite = pauseButton;
    t.playSprite = playButton;
    t.debug = debugButton;


    for (auto& row : b.gameField) {
        for (auto& tile : row) {
            sf::Sprite hiddenSprite(hiddenTexture);
            sf::Sprite revealedSprite(revealedTexture);
            sf::Sprite flagSprite(flag);
            sf::Sprite num1(num1);
            sf::Sprite num2(num2);
            sf::Sprite num3(num3);
            sf::Sprite num4(num4);
            sf::Sprite num5(num5);
            sf::Sprite num6(num6);
            sf::Sprite num7(num7);
            sf::Sprite num8(num8);
            float y = tile.row * 32;            // Calculate the position for each sprite
            float x = tile.col * 32;
            hiddenSprite.setPosition(x, y);
            revealedSprite.setPosition(x, y);
            flagSprite.setPosition(x, y);
            tile.hiddenSprite = hiddenSprite;
            tile.revealedSprite = revealedSprite;
            tile.flagSprite = flagSprite; // Assign flag sprite to tile
        }
    }
    for (int i = 0; i < 10; ++i) {
        b.digitSprites[i].setTexture(digits);
        b.digitSprites[i].setTextureRect(sf::IntRect(i * 21, 0, 21, 32)); // Set texture rect for each digit
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            b.youWin();
           


            if (t.spriteClickedOn(t.pauseSprite, window) || (t.spriteClickedOn(t.playSprite, window))) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    b.pausePlayButton();
                    cout << "game is paused" << endl;
                }
            
            }

            if (t.spriteClickedOn(t.debug, window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    b.debug();
                    cout << "game is being debugged!" << endl;
                    cout << b.debugMode << endl;
                }
            }
            if (b.isPaused == false) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (t.spriteClickedOn(t.happyFace, window) || t.spriteClickedOn(t.loseFace, window) || t.spriteClickedOn(t.winFace, window)) {
                        b.happyFaceButton();
                    }
                }
                if (b.gameOver == false) {
                    for (auto& row : b.gameField) {
                        for (auto& tile : row) {
                            if (tile.spriteClickedOn(tile.hiddenSprite, window)) {
                                if (event.mouseButton.button == sf::Mouse::Left) {
                                    if (!tile.flagged) {
                                        b.tileDisplayRecurion(window, event, tile);
                                    }
                                    if (tile.isMine) {
                                        b.gameOver = true;
                                    }
                                }
                            }
                            if (tile.spriteClickedOn(tile.hiddenSprite, window)) {
                                if (event.mouseButton.button == sf::Mouse::Right) {
                                    tile.getFlagged(tile.hiddenSprite, window, event, tile); // Update the tile's state
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White); 
        window.draw(t.leaderboard);
        window.draw(t.debug);
        if (!b.isPaused) {
            vector<sf::Sprite> timeSprites = b.gameTime(); // Get the current time sprites

            // Draw each time sprite
            for (const auto& sprite : timeSprites) {
                window.draw(sprite);
            }
        }
        if (b.isPaused) {
            window.draw(t.playSprite);
        }
        else {
            window.draw(t.pauseSprite);
        }

        if (b.gameOver) {
            window.draw(t.loseFace);
        }
        else if (b.gameWin) {  // If the game is won, display the win face
            window.draw(t.winFace);
        }
        else {
            window.draw(t.happyFace);  // Default face when the game is ongoing
        }
        for (const auto& row : b.gameField) {         // where the sprites will be drawn/displayed
            for (const auto& tile : row) { 
                if (!tile.isRevealed) { 
                    window.draw(tile.hiddenSprite); 
                    if (tile.flagged) {
                        window.draw(tile.flagSprite);
                    }
                }
                else {
                    window.draw(tile.revealedSprite); // Ensure this is executed when a tile is revealed
                    if (!tile.isMine) {
                        sf::Sprite spriteToDraw;
                        int surroundingMines = tile.surroundingMines();
                        if (surroundingMines > 0) {
                            switch (surroundingMines) {// case 0: tileRecursion(); break;
                            case 1: spriteToDraw.setTexture(num1); break;
                            case 2: spriteToDraw.setTexture(num2); break;
                            case 3: spriteToDraw.setTexture(num3); break;
                            case 4: spriteToDraw.setTexture(num4); break;
                            case 5: spriteToDraw.setTexture(num5); break;
                            case 6: spriteToDraw.setTexture(num6); break;
                            case 7: spriteToDraw.setTexture(num7); break;
                            case 8: spriteToDraw.setTexture(num8); break;
                            default: break; // No sprite for 0 mines 
                            }
                        }
                        spriteToDraw.setPosition(tile.col * 32, tile.row * 32);
                        window.draw(spriteToDraw);
                    }
                    else {
                        sf::Sprite mineSprite(mineTexture);
                        float y = tile.row * 32; 
                        float x = tile.col * 32;
                        mineSprite.setPosition(x, y);
                        window.draw(mineSprite);
                    }
                }
            }
            if (b.debugMode) {
                for (const auto& row : b.gameField) {
                    for (const auto& tile : row) {
                        if (!tile.isRevealed && tile.isMine) {
                            sf::Sprite mineSprite(mineTexture);
                            float y = tile.row * 32;
                            float x = tile.col * 32;
                            mineSprite.setPosition(x, y);
                            window.draw(mineSprite);
                        }
                    }
                }
            }
        }
        window.display();
    }
}