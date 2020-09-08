
#include <iostream>
#include <string>
#include <time.h>
//#include <conio.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Player {
private:
    char playerName;
    int playerPosition;
public:
   // Constructor with default values for data members
   Player() {
    playerName = 'A';
    playerPosition = 0;
   }
    void setPlayerName(char pName);
    char getPlayerName();
    int getPlayerPosition();
    void moveForward(int iLoc);
 };
 
 
 void Player::setPlayerName(char pName) // Member function (Setter)
{
    playerName = pName;
}
void Player::moveForward(int iLoc) // Member function (Setter)
{
    playerPosition = iLoc;
}

char Player::getPlayerName() // Member function (Getter)
{
    return playerName;
}
int Player::getPlayerPosition() // Member function (Getter)
{
    return playerPosition;
}


class Game {
private:
    char *board;
    int sizeOfBoard;
    int numberOfPlayers;
    int numberOfObstacles;
    int obstacleMaxPos;
    int numberOfGoAgains;
    Player gamers[6];
    char cardPile[9];
    char playerName;
    char *ptr;

public:
   // Constructor with default values for data members

   Game() {
    board = new char[20];
    sizeOfBoard = 20;
    numberOfPlayers= 6;
    numberOfObstacles = 5;
    obstacleMaxPos = 20;
    numberOfGoAgains = 5;
   }
   ~Game() //destructor
{
    delete [] board;
};
Game(const Game &obj) {
   ptr = new char;
   *ptr = *obj.board; // copy the value
}
     void startGame();
    void restartboard(char *board, int numberOfPlayers, int sizeOfBoard, int numberOfObstacles,int    obstacleMaxPos,int numberOfGoAgains); //Sets all values on board to ' '
    void shuffle(char cardPile[9]);
    void drawboard(char *board, int sizeOfBoard);
    char taketurn(char cardPile[10]);
    void showState(Player gamers[2],int numberOfPlayers);
    template <class T>
    void switchPlaces(char *board,Player gamers[2],T numberOfPlayers);
    void play(char *board,Player gamers[2], int numberOfPlayers,char cardPile[10], int sizeOfBoard);
  };
  
  
 int currentPlayer;

void Game::startGame()
{
    srand(time(NULL));
    cout << "Enter number of players: " ;
    cin >> numberOfPlayers;
    cout << "How large the board should be? " ;
    cin >> sizeOfBoard;
    cout << "How many obstacles? " ;
    cin >> numberOfObstacles;
    cout << "What the largest obstacle should be? " ;
    cin >> obstacleMaxPos;
    cout << "How many GoAgains? ";
    cin >> numberOfGoAgains;

     for (int i = 0; i < numberOfPlayers; i++)
        {
      cout << "Enter Character of Player " << i + 1 << ": " ;    
      cin >> playerName;
      gamers[i].setPlayerName(playerName);
    }
   restartboard(board,numberOfPlayers,sizeOfBoard,numberOfObstacles,obstacleMaxPos,numberOfGoAgains);
    play(board,gamers,numberOfPlayers,cardPile,sizeOfBoard);

}
void Game::restartboard(char *board, int numberOfPlayers, int sizeOfBoard, int numberOfObstacles,int obstacleMaxPos,int numberOfGoAgains) //Sets all values on board to ' '
{
    int o, r;
    for(int g = 0; g < sizeOfBoard; g++)
    {
       *(board + g) = char(177);//Creates board text
     }
          for(int g = 0; g < numberOfObstacles; g++)
        {

            r= rand() % sizeOfBoard + 1;
            if ( r < obstacleMaxPos)
            {
              *(board + r) = 'X' ;
            }

        }
         for(int g = 0; g < numberOfGoAgains; g++)
        {

            o= rand() % sizeOfBoard + 1;

              *(board + o) = 'O' ;


        }
      currentPlayer=0;
}
void Game::shuffle(char cardPile[9])
{
    int val,r,check;
    char cardVal;
    r= rand() % 9 + 1;
    cardPile[r]='S';
     for(int g = 0; g < 10; g++)
    {
        if (g == r) continue;
        val= rand() % 9 + 1;
        cardVal='0' + val;
        check=0;
        for (int k=0; k <g; k++)
        {
            if (cardPile[k] == cardVal )
            {
                g--;
                check=1;
                break;
            }
        }
        if (check ==1) continue;
        cardPile[g]=cardVal;
     }
}
void Game::drawboard(char *board, int sizeOfBoard) //Displays full array, with lines on each side
{

    cout << ' ';
    for(int g = 0; g < sizeOfBoard; g++)
    {
        cout << *(board+g);
        cout << ' ';
    }
    cout << endl;
}
char Game::taketurn(char cardPile[10])
{
    int r;
    shuffle(cardPile);
    r=rand() % 9 +1;
    return cardPile[r];
}
void Game::showState(Player gamers[2],int numberOfPlayers)
{

    for(int i = 0; i < numberOfPlayers; i++)
    {
        cout << "Player " << i+1 << " Position: " << gamers[i].getPlayerPosition() << endl ;
    }
 }
 template <class T>
void Game::switchPlaces(char *board,Player gamers[2],T numberOfPlayers)
{
    int player1Position,player2Position,playerToSwitchWith;
    player1Position = gamers[currentPlayer].getPlayerPosition();
    player2Position = gamers[currentPlayer-1].getPlayerPosition();
    playerToSwitchWith=currentPlayer - 1;
    if (currentPlayer == 0)
    {
        player1Position = gamers[currentPlayer].getPlayerPosition();
        player2Position = gamers[numberOfPlayers-1].getPlayerPosition();
        playerToSwitchWith=numberOfPlayers - 1;
    }
    *(board + gamers[currentPlayer].getPlayerPosition())=gamers[playerToSwitchWith].getPlayerName();
    *(board + gamers[playerToSwitchWith].getPlayerPosition())=gamers[currentPlayer].getPlayerName();
    gamers[currentPlayer].moveForward( player2Position);
    gamers[playerToSwitchWith].moveForward( player1Position);
}
void Game::play(char board[20],Player gamers[2], int numberOfPlayers,char cardPile[10], int sizeOfBoard)
{
    int c = 0, count = 0, maxIndex = (sizeOfBoard - 1);
    char turn,currentBoardElement;
    bool success = false;
    currentPlayer =0;
    for(int i = 0; i < numberOfPlayers; i++)
    {
              cout << "Player "<< i+1 << " is " << gamers[i].getPlayerName() << endl; ;
    }
    //showState(player);
    drawboard(board, sizeOfBoard);
    system("pause");
    while(true)
    {
         turn = taketurn(cardPile);
           gamers[0].setPlayerName('A');
         if (turn == 'S')
        {
        cout << "Player "<< gamers[currentPlayer].getPlayerName() << " selected " << turn << endl;
             switchPlaces(board,gamers,numberOfPlayers);
            if (currentPlayer==numberOfPlayers - 1)
            {
                currentPlayer=0;
            }
            else
            {
                currentPlayer=currentPlayer + 1;
            }
          drawboard(board, sizeOfBoard);
        showState(gamers,numberOfPlayers);
        system("pause");
          continue;
        }
        c= turn - '0';

          cout << "Player "<< gamers[currentPlayer].getPlayerName() << " selected " << c  << endl;

        //cout <<  c <<   endl;
        //system("pause");
        c = c + gamers[currentPlayer].getPlayerPosition();
        currentBoardElement=*(board+c);
              cout << "Player choose "<< currentBoardElement << endl;

        //cout <<  c <<   endl;
        //system("pause");
        if(currentBoardElement == 'X')
        {
            *(board + gamers[currentPlayer].getPlayerPosition())=char(177);
            gamers[currentPlayer].moveForward(0);   //These test if there is an obstacle where the player is trying to move to
            *(board)=gamers[currentPlayer].getPlayerName() ;
        }
        else
        {
            if(c == maxIndex)
            {
                success = true;
                *(board + gamers[currentPlayer].getPlayerPosition())=char(177);
                gamers[currentPlayer].moveForward( maxIndex);
                *(board + (sizeOfBoard - 1)) =gamers[currentPlayer].getPlayerName();
                break;
            }
            else
            {
                if(c > (maxIndex))
                {
                    c = maxIndex - (c-maxIndex);
                }
                if (*(board + c) != char(177))
                {
                    *(board)=*(board + c);
                    for(int j=0; j < numberOfPlayers; j++)
                    {
                        if (gamers[j].getPlayerName() == *(board + c))
                        {
                            gamers[currentPlayer].moveForward(0);
                        }
                    }
                }
                *(board + gamers[currentPlayer].getPlayerPosition())=char(177);
                gamers[currentPlayer].moveForward(c);
                *(board + c)=gamers[currentPlayer].getPlayerName();
            }
        }
        count++;
        // system("cls");
        drawboard(board, sizeOfBoard);
        showState(gamers,numberOfPlayers);
        system("pause");
        if (currentPlayer == numberOfPlayers - 1)
        {
            currentPlayer=0;
        }
        else
        {
            //Player gets another turn. Player can get consecutive GoAgains.
            if (currentBoardElement != 'O'){
            currentPlayer=currentPlayer + 1;
            }
        }
        if(success == true) break;
    }
    system("cls");
    drawboard(board, sizeOfBoard);//Function with Pointer
    showState(gamers,numberOfPlayers);//Function with Pointer
    system("pause");
    cout << "\n|<|Success!|>|\n Winning player: " << gamers[currentPlayer].getPlayerName() << ".\n";
}


int main() //MAIN
{
 Game thisGame;
    thisGame.startGame();

 }
