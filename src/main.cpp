#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <vector>
#include<unistd.h>  
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

//surcharge operateur Packet pour classe Game
sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
    std::int16_t buffer;
    std::int16_t score;
    std::int16_t level;
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        
        buffer=game.grille.grille[i][j];
        packet <<    buffer;
      }
     
    }
    score=game.score;
    level=game.level;
    packet<<score;
    packet<<level;
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
  std::int16_t buffer;
  std::int16_t score;
  std::int16_t level;
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet >> buffer;
        game.grille.grille[i][j]=buffer;
      }
     
    }
    packet<<score;
    packet<<level;
    game.score=score;
    game.level=level;
    return packet ;
}
int main()
{
   // Initialisation connexion
    std::string compteur;
    std::string compteure;
    
    Grille grille1;
    Piece piece1;
    Game game1(grille1,piece1,false);
    Grille grille2;
    Piece piece2;
    Game game2(grille2,piece2,false);
    //definition des parametres de jeu
    
    std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
    sf::Packet packet;
    sf::Packet packet2;

    std::string s ;
    sf::TcpListener listener;
    listener.setBlocking(false);
    // lie l'écouteur à un port
    if (listener.listen(52000) != sf::Socket::Done)
    {
        printf("Erreur port\n");
    }
    std::cout <<"Yousk\n";
    // accepte une nouvelle connexion
    sf::TcpSocket client;
    sf::TcpSocket client2;
    //client.setBlocking(false);
    
    while(listener.accept(client) != sf::Socket::Done)
    {
        printf("Wait client\n");
    }
    while(listener.accept(client2) != sf::Socket::Done)
    {
        printf("Wait client2\n");
    }



    
    //premier echange pour teste connexion
    client.receive(packet);
    client2.receive(packet2);
    if (packet >> s)
    {
      std::cout <<"data:"<< s << "\n" ;
      std::cout <<"you";
    }
    
    else
    {
        std::cout <<"erreur"<< "\n" <<std::endl;
    }
    if (packet2 >> s)
    {
      std::cout <<"data2:"<< s << "\n" ;
      std::cout <<"you2";
    }
    
    else
    {
        std::cout <<"erreur2"<< "\n" <<std::endl;
    }
    //client.setBlocking(false);

    //boucle du serveur
    while (true)
    {
      
      packet.clear();
      packet2.clear();
      //reception grille;
      client.receive(packet);
      client2.receive(packet2);
      
      packet >> game1;
      packet2 >> game2;
      packet.clear();
      packet2.clear();
      std::cout <<"Youskboucle\n";
      packet<<game2;
      packet2 << game1;
      client.send(packet);
      client2.send(packet2);
      packet.clear();
      packet2.clear();
      sleep(1);
      
      
    
    }


    

    return 0;
}
