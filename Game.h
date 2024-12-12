#pragma once
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>


class Game {
private:
  sf::RenderWindow* window;
  sf::RectangleShape top_bar;
  sf::RectangleShape bottom_bar;
  sf::CircleShape ball;
  sf::Event event;
  sf::VideoMode video_mode;
  void initVarible();
  void initWindow();
  void shapeInit();

public:
  Game();
  virtual ~Game();
  bool is_window_running();
  void event_Polling();
  void render_obj();
  void obj_update();
  void bar_update();
  void ball_update();
  void game_update();
  void game_render();
};