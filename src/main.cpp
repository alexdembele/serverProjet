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


sf::Packet& operator <<(sf::Packet& packet, const Game& game)
{
    std::string buffer;
     for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        if (game.grille.grille[i][j]==1)
        {
          buffer="b";
          
        }
        else if (game.grille.grille[i][j]==2)
        {
          buffer="c";
          
        }
        else if (game.grille.grille[i][j]==3)
        {
          buffer="d";
        }
        else if (game.grille.grille[i][j]==4)
        {
          buffer="e";
        }
        else if (game.grille.grille[i][j]==5)
        {
          buffer="f";
        }
        else if (game.grille.grille[i][j]==6)
        {
          buffer="g";
        }
        else if (game.grille.grille[i][j]==7)
        {
          buffer="h";
        }
        else
        {
          buffer="a";
        }
        packet <<    buffer;
      }
     
    }
    return packet ;
}

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
  std::string buffer;
    for (int i=0; i<20; i++)
    {
      for (int j=0;j<10;j++)
      {
        packet >> buffer;
        std::cout <<buffer<<";";
        if (buffer==std::string("b"))
        {
          game.grille.grille[i][j]==1;
        }
        else if (buffer==std::string("c"))
        {
          game.grille.grille[i][j]==2;
        }
        else if (buffer==std::string("d"))
        {
          game.grille.grille[i][j]==3;
        }
        else if (buffer==std::string("e"))
        {
          game.grille.grille[i][j]==4;
        }
        else if (buffer==std::string("f"))
        {
          game.grille.grille[i][j]==5;
        }
        else if (buffer==std::string("g"))
        {
          game.grille.grille[i][j]==6;
        }
        else if (buffer==std::string("h"))
        {
          game.grille.grille[i][j]==7;
        }
        else
        {
          game.grille.grille[i][j]==0;
        }
      }
     
    }
    
    return packet ;
}
int main()
{
  
    std::string compteur;
    std::string compteure;
    
    Grille grille1;
    Piece piece1;
    Game game1(grille1,piece1,false);
    //definition des parametres de jeu
    
    std::cout << sf::IpAddress::getPublicAddress( ) << "\n";
    sf::Packet packet;
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
    //client.setBlocking(false);
    
    while(listener.accept(client) != sf::Socket::Done)
    {
        printf("Wait client\n");
    }



    //sleep(10);
    
    client.receive(packet);
    if (packet >> s)
    {
      std::cout <<"data:"<< s << "\n" ;
      std::cout <<"you";
    }
    
    else
    {
        std::cout <<"erreur"<< "\n" <<std::endl;
    }
    
    //client.setBlocking(false);
    while (true)
    {
      
      packet.clear();
      //reception grille;
      client.receive(packet);
      
      
      packet >> game1;
      packet.clear();
      std::cout <<"Youskboucle\n";
      
     

      
     for (int i=0; i<20; i++)
      {
      for (int j=0;j<10;j++)
      {
        std::cout <<  game1.grille.grille[i][j]<<";";
      }
     
    }
    packet<<game1;
    client.send(packet);
    packet.clear();
    sleep(1);
      
      
    
    }


    

    return 0;
}
