#include "Game.h"

void Game::initVarible() {
  this->window = nullptr;
}

void Game::initWindow() {
  this->video_mode.height = 700;
  this->video_mode.width = 700;

  this->window = new sf::RenderWindow(this->video_mode, "Ping-Pong");
}

Game::Game() {
  this->initVarible();
  this->initWindow();
}

Game::~Game() {
  delete this->window;
}

bool Game::is_window_running() {
  return this->window->isOpen();
}

void Game::event_Polling() {
    while(this->window->pollEvent(this->event)) {
      if(this->event.type == sf::Event::Closed) {
        this->window->close();
      }
    }
}

void Game::game_update() {
  this->event_Polling();
}

void Game::game_render() {
  this->window->clear();
  this->window->display();
}