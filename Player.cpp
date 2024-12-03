#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    //Puts head in the center of board to start
    objPos headPos{
        mainGameMechsRef->getBoardSizeX()/2,
        mainGameMechsRef->getBoardSizeY()/2,
        '@'
    };

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(headPos);

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        char input = mainGameMechsRef->getInput();

        //Assign characters for direction/movement of the snake/characters
        if(input != 0)  // if not null character
        {
            switch(input)
            {
                case 8:
                    mainGameMechsRef->setExitTrue();
                case 'w':
                    if(myDir != UP && myDir != DOWN)
                        myDir = UP;
                    break;
            
                case 'a':
                    if(myDir != LEFT && myDir != RIGHT)
                        myDir = LEFT;
                    break;

                case 's':
                    if(myDir != UP && myDir != DOWN)
                        myDir = DOWN;
                    break;

                case 'd':
                    if(myDir != LEFT && myDir != RIGHT)
                        myDir = RIGHT;
                    break;

                default:
                    break;
            }   
        }            
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    // Get the current head position
    objPos head = playerPosList->getHeadElement();

    // Determine the new head position based on the direction
    int newX = head.pos->x;
    int newY = head.pos->y;

    //Move head by incrementing/decrementing x-y coords
    switch(myDir)
    {
        case UP:
            newY--;
            break;
        case DOWN:
            newY++;
            break;
        case LEFT:
            newX--;
            break;
        case RIGHT:
            newX++;
            break;
        default:
            return;
    }

    // Wrap around if the player reaches the edges of the board
    if(newX <= 0){
        newX = mainGameMechsRef->getBoardSizeX() - 2;
    }else if (newX >= mainGameMechsRef->getBoardSizeX() - 1){
        newX = 1;
    }

    if(newY <= 0){
        newY = mainGameMechsRef->getBoardSizeY() - 2;
    }else if(newY >= mainGameMechsRef->getBoardSizeY() - 1){
        newY = 1;
    }

    objPos newHead = { newX, newY, '@' };
    playerPosList->insertHead(newHead);
    playerPosList->removeTail();

    //Check for self collision
    int playsize = playerPosList->getSize();
    int headX = playerPosList->getHeadElement().pos->x;
    int headY = playerPosList->getHeadElement().pos->y;

    for(int k = 1; k < playsize;k++){
        objPos tempPos = playerPosList->getElement(k);
        if(headX == tempPos.pos->x && headY ==tempPos.pos->y ){
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    //check for collision with food

    if(headX == mainGameMechsRef->getFoodPosition().pos->x &&
        headY == mainGameMechsRef->getFoodPosition().pos->y){
            //add to the score
            mainGameMechsRef->incrementScore();
            //finds tail elemnet
            objPos newTailPos = playerPosList->getTailElement();
            //replaces tail element
            playerPosList->insertTail(newTailPos);
            //generates food
            mainGameMechsRef->generateFood(playerPosList);
        }
}

// More methods to be added