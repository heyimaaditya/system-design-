/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
class Player{
public:
    string playerName;
    int id;
    Player(const string &name,int playerId):playerName(name),id(playerId){}
};
class Dice{
public:
    int numofDice;
    Dice(int numDice):numofDice(numDice){}
    int rollDice(){
        return rand()%(6*numofDice)+1;
    }
    
};
class Jumper{
public:
    int startpoint;
    int endpoint;
    Jumper(int start,int end):startpoint(start),endpoint(end){}
};
class GameBoard{
    deque<Player>nextTurn;
    vector<Jumper>snakes;
    vector<Jumper>ladders;
    unordered_map<string,int>playerPositions;
    unique_ptr<Dice>dice;
    int boardSize;
    int getnewPos(int currpos){
        for(auto &snake:snakes){
            if(snake.startpoint==currpos){
                cout<<"Bitten by snake at:"<<currpos<<endl;
                return snake.endpoint;
            }
        }
        for(auto &ladder:ladders){
            if(ladder.startpoint==currpos){
                cout<<"Climbed ladder at:"<<currpos<<endl;
                return ladder.endpoint;
            }
        }
        return currpos;
    }
    public:
    GameBoard(unique_ptr<Dice> diceObj, deque<Player> players, vector<Jumper> snakeList, vector<Jumper> ladderList, int size)
        : dice(move(diceObj)), nextTurn(move(players)), snakes(move(snakeList)), ladders(move(ladderList)), boardSize(size) {
        for (const auto& player : nextTurn) {
            playerPositions[player.playerName] = 0;
        }
    }
    void StartGame(){
        while(nextTurn.size()>1){
            Player currPlayer=nextTurn.front();
            nextTurn.pop_front();
            int currpos=playerPositions[currPlayer.playerName];
            int diceval=dice->rollDice();
            int nextcell=currpos+diceval;
            if(nextcell>boardSize){
                nextTurn.push_back(currPlayer);
            } else if (nextCell == boardSize) {
                cout << currentPlayer.playerName << " won the game!" << endl;
                playerPositions.erase(currentPlayer.playerName);
            } else {
                int newPosition = getNewPosition(nextCell);
                playerPositions[currentPlayer.playerName] = newPosition;
                cout << currentPlayer.playerName << " is at position " << newPosition << endl;
                nextTurn.push_back(currentPlayer);
            }
        
        }
        if (nextTurn.size() == 1) {
            cout << "Game over! " << nextTurn.front().playerName << " is the last player remaining." << endl;
        }
    }
};


