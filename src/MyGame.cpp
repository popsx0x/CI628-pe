#include "MyGame.h"
#include <sstream>

#include <SDL.h>
//#include <SDL_mixer.h>

#include <Windows.h>
#include <iostream>
#include <sstream>

#include<vector>


//#include <iostream>
//#include "cout.h"


SDL_Texture* IMG_LoadTexture(SDL_Renderer* renderer, const char* file)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(file);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

void MyGame::Init(SDL_Renderer* renderer)
{

    PlayerTexture = IMG_LoadTexture(renderer, "Textures/carrot.png");
    bgTexture = IMG_LoadTexture(renderer, "Textures/Background/Pink.png");
    blockTexture = IMG_LoadTexture(renderer, "Textures/Terrain/Terrain.png");

    Player1Texture = IMG_LoadTexture(renderer, "Textures/Main Characters/Pink Man/Idle (32x32).png");
    Player2Texture = IMG_LoadTexture(renderer, "Textures/Main Characters/Ninja Frog/Idle (32x32).png");
    Player3Texture = IMG_LoadTexture(renderer, "Textures/Main Characters/Virtual Guy/Idle (32x32).png");

    spikesTexture = IMG_LoadTexture(renderer, "Textures/Traps/Spikes/Idle.png");

    strawberryText = IMG_LoadTexture(renderer, "Textures/Items/Fruits/Strawberry.png");
    cherriesText = IMG_LoadTexture(renderer, "Textures/Items/Fruits/Cherries.png");
    pineappleText = IMG_LoadTexture(renderer, "Textures/Items/Fruits/Pineapple.png");

    endPoint = IMG_LoadTexture(renderer, "Textures/Items/Checkpoints/Checkpoint/Checkpoint (No Flag).png");
    endFlag = IMG_LoadTexture(renderer, "Textures/Items/Checkpoints/Checkpoint/Checkpoint (Flag Idle)(64x64).png");

    bgMusic = Mix_LoadMUS("Sounds/bg.mp3");
    Mix_PlayMusic(bgMusic, -1); // -1 plays the music in a loop indefinitely


    spikeCol = Mix_LoadWAV("Sounds/end.wav");
    fruitCol = Mix_LoadWAV("Sounds/collect.wav");
 
    jumpSound = Mix_LoadWAV("Sounds/jump.wav");
    flagSound = Mix_LoadWAV("Sounds/flag.wav");
    winSound = Mix_LoadWAV("Sounds/win.wav");



}
MyGame::~MyGame()
{
}



void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
 

    if (cmd == "GAME_DATA") {
        if (args.size() == 6) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.player3Y = stoi(args.at(2));
            //
            game_data.player1X = stoi(args.at(3));
            game_data.player2X = stoi(args.at(4));
            game_data.player3X = stoi(args.at(5));

        }

    }
    else if (cmd == "SCORES") {
        if (args.size() == 3) {

            game_data.player1score = std::stoi(args.at(0));
            game_data.player2score = std::stoi(args.at(1));
            game_data.player3score = std::stoi(args.at(2));

            updatePlayerScores(game_data.player1score, game_data.player2score, game_data.player3score);
        }
    }


    else if (cmd == "PLAY_SOUND") {

        // Inside your function for handling messages
        if (args.size() == 1) {
            game_data.soundIdentifier = args.at(0);
            std::cout << game_data.soundIdentifier << "\n";

            // Play sound based on the identifier received
            if (game_data.soundIdentifier == "spikeCollision") {
                Mix_PlayChannel(-1, spikeCol, 0); // Play the spike collision sound
            }
            else if (game_data.soundIdentifier == "fruitCollision") {
                Mix_PlayChannel(-1, fruitCol, 0); // Play the fruit collision sound
            }
            else if (game_data.soundIdentifier == "jump") {
                Mix_PlayChannel(-1, jumpSound, 0); // Play the jump sound
            }
            else if (game_data.soundIdentifier == "playerEnd") {
                Mix_PlayChannel(-1, flagSound, 0); // Play the flag sound
                flag = true;

            }
            else if (game_data.soundIdentifier == "win") {
                Mix_PlayChannel(-1, winSound, 0); // Play the win sound
            }
        }
    }
    else {
 
    }

}

/*
void MyGame::send(std::string message) {
    messages.push_back(message);
}
*/

//

void MyGame::updatePlayerScores(int player1score, int player2score, int player3score) {
    // Update the scores of the players in your game
    // Perform actions based on these scores, like updating UI or game state
    // For example:
    game_data.player1score = player1score;
    game_data.player2score = player2score;
    game_data.player3score = player3score;
}



void MyGame::handleMessage(std::string message) {

};


void MyGame::send(std::string message) {
    messages.push_back(message);
    // Send this message through your network interface
    // networkInterface.send(message);
}






void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
        //left + right
    case SDLK_a:
        send(event.type == SDL_KEYDOWN ? "A_DOWN" : "A_UP");
        break;
    case SDLK_d:
        send(event.type == SDL_KEYDOWN ? "D_DOWN" : "D_UP");
        break;



    }
}


void MyGame::update() {
    player1.y = game_data.player1Y;
    player1.x = game_data.player1X;
    //
    player2.y = game_data.player2Y;
    player2.x = game_data.player2X;
    //
    player3.y = game_data.player3Y;
    player3.x = game_data.player3X;

    score1 = game_data.player1score;
    score2 = game_data.player2score;
    score3 = game_data.player3score;


        //how to replace a tile 
       // Assuming leveldata holds the map state
        if (score1 == 1) {
            // Find and remove the strawberry entity from the map
            for (size_t y = 0; y < 25; y++) {
                for (size_t x = 0; x < 22; x++) {
                    if (leveldata[x][y] == 3) { // Assuming 3 represents a strawberry
                        leveldata[x][y] = 0; // Set the tile to an empty space
                        break; // Stop searching for strawberries after the first one is removed
                    }
                }
            }
        }
        else if (score2 == 1) {
            // Find and remove the cherries entity from the map
            for (size_t y = 0; y < 25; y++) {
                for (size_t x = 0; x < 22; x++) {
                    if (leveldata[x][y] == 4) {
                        leveldata[x][y] = 0;
                        break;
                    }
                }
            }
        }
        else if (score3 == 1) {
            // Find and remove the pineapple entity from the map
            for (size_t y = 0; y < 25; y++) {
                for (size_t x = 0; x < 22; x++) {
                    if (leveldata[x][y] == 5) {
                        leveldata[x][y] = 0;
                        break;
                    }
                }
            }
        }

    
     //change flag
     if (flag == true) {
        for (size_t y = 0; y < 25; y++) {
            for (size_t x = 0; x < 22; x++) {
                if (leveldata[x][y] == 6) {
                    leveldata[x][y] = 7;
                    break;
                }
            }
        }
    }

  

}



//screen text

SDL_Texture* createTextureFromString(SDL_Renderer* renderer, const std::string& text, TTF_Font* _font, SDL_Color color) {
    SDL_Texture* textTexture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Blended(_font, text.c_str(), color);
    if (textSurface != nullptr) {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
    }
    else {
        std::cout << "Failed to create texture from string: " << text << std::endl;
        std::cout << TTF_GetError() << std::endl;
    }

    return textTexture;
}

TTF_Font* font;
void drawText(SDL_Renderer* renderer, const std::string& text, const int& x, const int& y) {
    if (font == nullptr) {
        font = TTF_OpenFont("Fonts/arial.ttf", 20);
    }
    SDL_Texture* textTexture = createTextureFromString(renderer, text, font, { 0xFF, 0xFF, 0xFF });
    int w, h;
    SDL_QueryTexture(textTexture, 0, 0, &w, &h);
    SDL_Rect dst = { x, y, w, h };
    SDL_RenderCopyEx(renderer, textTexture, 0, &dst, 0.0, 0, SDL_FLIP_NONE);

    SDL_DestroyTexture(textTexture);
}

void MyGame::render(SDL_Renderer* renderer) {

    //draw level

    for (size_t y = 0; y < 25; y++)

    {
        for (size_t x = 0; x < 22; x++)
        {
            int Tile = leveldata[x][y];
            SDL_Rect pos{ y * TileSize,x * TileSize ,TileSize ,TileSize };
            //bg
            //SDL_Rect bg{ 96,0,47,47 };
            if (Tile == 0) {
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
            }
            //dirttt
            SDL_Rect slice{ 96,0,47,47 };
            if (Tile == 1) {
                SDL_RenderCopy(renderer, blockTexture, &slice, &pos);
            }
            //spikes
            if (Tile == 2) {
                //placing bg behind spikes texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //spikes text
                SDL_RenderCopy(renderer, spikesTexture, nullptr, &pos);
            }


            //player 1 - pink man, idle, frame 6
            SDL_Rect p1{ 163, 0, 33, 33 };
            SDL_RenderCopy(renderer, Player1Texture, &p1, &player1);

            //player 2 - ninja frog, idle, frame 6
            SDL_Rect p2{ 163, 0, 33, 33 };
            SDL_RenderCopy(renderer, Player2Texture, &p2, &player2);

            //player 3 - virtual guy, idle, frame 6
            SDL_Rect p3{ 163, 0, 33, 33 };
            SDL_RenderCopy(renderer, Player3Texture, &p3, &player3);



            //fruit
            //first frame
            SDL_Rect fruitIdle{ 32, 0, 33, 33 };
            if (Tile == 3) {
                //placing bg behind fruit texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //fruit text
                SDL_RenderCopy(renderer, strawberryText, &fruitIdle, &pos);
            }
            if (Tile == 4) {
                //placing bg behind fruit texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //fruit text
                SDL_RenderCopy(renderer, cherriesText, &fruitIdle, &pos);
            }
            if (Tile == 5) {
                //placing bg behind fruit texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //fruit text
                SDL_RenderCopy(renderer, pineappleText, &fruitIdle, &pos);
            }

            //end
            if (Tile == 6) {
                //placing bg behind flag texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //flag text
                SDL_RenderCopy(renderer, endPoint, nullptr, &pos);
            }
            SDL_Rect flagIdle{ 32, 0, 33, 33 };
            if (Tile == 7) {
                //placing bg behind END flag texture
                SDL_RenderCopy(renderer, bgTexture, nullptr, &pos);
                //flag text
                SDL_RenderCopy(renderer, endFlag, &flagIdle, &pos);
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


            // Render Player Scores
            drawText(renderer, "Player 1: " + std::to_string(score1), 0, 0);
            drawText(renderer, "Player 2: " + std::to_string(score2), 0, 25);
            drawText(renderer, "Player 3: " + std::to_string(score3), 0, 50);

            // drawText(renderer, std::to_string(player1Score), 650, 0);

             // SDL_RenderDrawRect(renderer, &block);

        };
    };


}