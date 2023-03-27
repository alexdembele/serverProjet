#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <vector>
#include <time.h>
#include<sstream>
#include<iostream>
#include"utils.hpp"
#include"piece.hpp"
#include"grille.hpp"
#include"game.hpp"



//TRICKY TOWER
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{int x,y;} a[4], b[4];

int figures[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

// regarde si la pièce peut se déplacer
bool check()
{
   for (int i=0;i<4;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};
sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet <<  game.grille.grille[i][j];
      }
     
    }
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet >>  game.grille.grille[i][j];
      }
     
    }
    
    return packet ;
}

int main()
{
    srand(time(0));     
    //chargement graphisme
    RenderWindow window(VideoMode(1800, 1000), "The Game!");

    Texture t1,t2,t3;
    if(!t1.loadFromFile("../Projet/images/tiles.png"))
      printf("Erreur chargement\n");
    if(!t2.loadFromFile("../Projet/images/background.png"))
      printf("Erreur chargement\n");
    if(!t3.loadFromFile("../Projet/images/frame.png"))
      printf("Erreur chargement\n");
    
    Sprite s(t1), background(t2), frame(t3),fram(t3);
    fram.move(Vector2f(450.f,0));
    scaleToMinSize(background,1900,1100);

    //definition des parametres de jeu
    
    
    sf::Packet packet;
    
    sf::TcpListener listener;
    listener.setBlocking(false);
    // lie l'écouteur à un port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        printf("Erreur port\n");
    }

    // accepte une nouvelle connexion
    sf::TcpSocket client;
    //client.setBlocking(false);
    std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
    while (listener.accept(client) != sf::Socket::Done)
    {
        printf("Wait client\n");
    }
    client.receive(packet);




    Clock clock;

    //TEST
    //definition de la grille
    
    Grille Tertest;
    
    //definition de la piece
   
    Piece piecTest;

    //definition de la partie
    Game myGame(Tertest,piecTest);
    //definition temps
    float temps=0;
    
    //std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        temps+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            
              myGame.commande(e);
        }
      client.receive(packet);
      packet >> myGame;
      /*for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        printf("%d\n",myGame.grille.grille[i][j]) ;
      }
     
    }*/
    
   
    
    
    
        
    if (myGame.updateGame(temps))
    {
      temps=0;
    }
    
    
     

   
    //window.draw(myGame);
    
    window.display();
    }

    return 0;
}
