#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include <SDL_mixer.h>


static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int player3Y = 0;

    int player1X = 0;
    int player2X = 0;
    int player3X = 0;

    int player1score = 0;
    int player2score = 0;
    int player3score = 0;

    std::string soundIdentifier = "";

    std::string jumpSound = "";


} game_data;

class MyGame {

private:
    SDL_Rect player1 = { 200, 0, 40, 40 };
    SDL_Rect player2 = { 580, 0, 40, 40 };
    SDL_Rect player3 = { 500, 0, 40, 40 };

    SDL_Rect block = { 400, 200, 300, 40 };

    SDL_Texture* PlayerTexture;

    //player textures
    SDL_Texture* Player1Texture;
    SDL_Texture* Player2Texture;
    SDL_Texture* Player3Texture;

    SDL_Texture* blockTexture;
    SDL_Texture* spikesTexture;
    SDL_Texture* bgTexture;

    //pickups
    SDL_Texture* strawberryText;
    SDL_Texture* cherriesText;
    SDL_Texture* pineappleText;

    //end
    SDL_Texture* endPoint;
    SDL_Texture* endFlag;

    //
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;

    //
    bool flag = false;
    bool endGame = false;


    //audio
    Mix_Music* bgMusic = NULL;

    // Declare pointers to Mix_Chunk for each sound
    Mix_Chunk* spikeCol = NULL;
    Mix_Chunk* fruitCol = NULL;
    Mix_Chunk* jumpSound = NULL;
    Mix_Chunk* flagSound = NULL;
    Mix_Chunk* winSound = NULL;

    const int TileSize = 28;
    int leveldata[22][25] =
    { { 0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0},
          {0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	1,	0,	0,	0,	3,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	1,	0,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0},
          {1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	2,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	1,	0,	0,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	1,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0},
          {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	2,	2,	2,	2,	1,	0},
          {2,	2,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1},
          {1,	1,	1,	1,	1,	0,	1,	1,	1,	0,	0,	1,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0} };

public:
    ~MyGame();



    std::vector<std::string> messages;
    void Init(SDL_Renderer* renderer);
    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    //
    void handleMessage(std::string message);
    void MyGame::updatePlayerScores(int player1Score, int player2Score, int player3Score);


};

#endif