#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>


class Game {
private:
  sf::RenderWindow* window;
  sf::RectangleShape bar1;
  sf::Event event;
  sf::VideoMode video_mode;
  void initVarible();
  void initWindow();

public:
  Game();
  virtual ~Game();
  bool is_window_running();
  void event_Polling();
  void game_update();
  void game_render();
};