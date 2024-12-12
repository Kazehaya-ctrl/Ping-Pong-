#include "Game.h"

void Game::initVarible() {
  this->window = nullptr;
}

void Game::initWindow() {
  this->video_mode.height = 700;
  this->video_mode.width = 700;

  this->window = new sf::RenderWindow(this->video_mode, "Ping-Pong");
}

void Game::shapeInit() {
  this->top_bar.setFillColor(sf::Color::White);
  this->top_bar.setSize(sf::Vector2f(100.f, 10.f));
  this->top_bar.setPosition(sf::Vector2f(this->window->getSize().x/2, 0.f));

  this->bottom_bar.setFillColor(sf::Color::White);
  this->bottom_bar.setSize(sf::Vector2f(100.f, 10.f));
  this->bottom_bar.setPosition(sf::Vector2f(this->window->getSize().x/2, ((this->window->getSize().y) - (this->bottom_bar.getSize().y))));

  this->ball.setFillColor(sf::Color::Red);
  this->ball.setRadius(10.f);
  this->ball.setPosition((this->video_mode.width)/2.0f, (this->video_mode.height)/2.0f);
}

Game::Game() {
  this->initVarible();
  this->initWindow();
  this->shapeInit();
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

void Game::bar_update() {

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->top_bar.getPosition().x > 0.f) {
    this->top_bar.move(-8.f, 0.f);
    this->bottom_bar.move(-8.f, 0.f);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->top_bar.getPosition().x < (this->window->getSize().x - this->top_bar.getSize().x)) {
    this->top_bar.move(8.f, 0.f);
    this->bottom_bar.move(8.f, 0.f);
  }
}

void Game::ball_update() {
  float randomX = static_cast<float>(rand() % 5);
  this->ball.move(randomX, 10.f);

  if(this->ball.getGlobalBounds().intersects(this->top_bar.getGlobalBounds())) {
    this->ball.move(randomX, 10.f);
  }
  if(this->ball.getGlobalBounds().intersects(this->bottom_bar.getGlobalBounds())) {
    this->ball.move(randomX, -10.f);
  }
}

void Game::obj_update() {
  this->bar_update();
  this->ball_update();
}


void Game::render_obj() {
  this->window->draw(this->top_bar);
  this->window->draw(this->bottom_bar);
  this->window->draw(this->ball);
}

void Game::game_update() {
  this->event_Polling();
  this->obj_update();
}

void Game::game_render() {
  this->window->clear();
  this->render_obj();
  this->window->display();
}