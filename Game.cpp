#include "Game.h"

void Game::initVarible() {
  this->window = nullptr;
  this->ball_velocity = sf::Vector2f(3.f, 5.f);
  this->gameState = true;
  this->wait = false;
}

void Game::initWindow() {
  this->video_mode.height = 700;
  this->video_mode.width = 700;

  this->window = new sf::RenderWindow(this->video_mode, "Ping-Pong");
  this->window->setFramerateLimit(60);
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

void Game::textInit() {
  if(!(this->font.loadFromFile("operius-mono.ttf"))) {
    std::cout << "Font not loaded" << std::endl;
  }
  this->gameText.setFont(this->font);
  this->gameText.setString("Game Over");
  this->gameText.setCharacterSize(40);
  this->gameText.setFillColor(sf::Color::White);

  this->float_rect = this->gameText.getLocalBounds();
  this->gameText.setOrigin(this->float_rect.width/2.f, this->float_rect.height/2.f);
  this->gameText.setPosition(this->video_mode.width/2.f, this->video_mode.height/2.f);

  this->pause.setFont(this->font);
  this->pause.setString("Paused");
  this->pause.setCharacterSize(40);
  this->pause.setFillColor(sf::Color::White);
  this->pause.setPosition(250.f, 350.f);
}

Game::Game() {
  this->initVarible();
  this->initWindow();
  this->shapeInit();
  this->textInit();
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

    if (this->event.type == sf::Event::KeyPressed) {
      if (this->event.key.code == sf::Keyboard::Escape) {
        if(!this->gameState) {
          this->gameState = true;

          this->ball.setPosition(
            (this->video_mode.width)/2.0f, 
            (this->video_mode.height)/2.0f
          );
          this->ball_velocity = sf::Vector2f(3.f, 5.f);
        } else {
          this->wait = !(this->wait);
        }
      }
    } 
  }
}

void Game::bar_update() {

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->top_bar.getPosition().x > 0.f) {
    this->top_bar.move(-7.f, 0.f);
    this->bottom_bar.move(-7.f, 0.f);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->top_bar.getPosition().x < (this->window->getSize().x - this->top_bar.getSize().x)) {
    this->top_bar.move(7.f, 0.f);
    this->bottom_bar.move(7.f, 0.f);
  }
}

void Game::ball_update() {
  this->ball.move(this->ball_velocity.x, this->ball_velocity.y);

  if(this->ball.getGlobalBounds().intersects(this->top_bar.getGlobalBounds())) {
    this->ball_velocity.y = std::abs(this->ball_velocity.y);
  }
  if(this->ball.getGlobalBounds().intersects(this->bottom_bar.getGlobalBounds())) {
    this->ball_velocity.y = -std::abs(this->ball_velocity.y);
  } 
  if(this->ball.getPosition().x <= 0.f) {
    this->ball_velocity.x = std::abs(this->ball_velocity.x);
  }
  if(this->ball.getPosition().x >= this->window->getSize().x - this->ball.getRadius()) {
    this->ball_velocity.x = -std::abs(this->ball_velocity.x);
  }
  if(this->ball.getPosition().y > this->window->getSize().y - this->ball.getRadius() || this->ball.getPosition().y < 0.f) {
    this->gameState = false;
  }

}

void Game::obj_update() {
  if(!this->wait) {
    this->bar_update();
    this->ball_update();
  }
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
  if(this->gameState) {
    if(!this->wait) {
      this->render_obj();
    } else {
      this->window->draw(this->pause);
    }
  } else {
    this->window->draw(this->gameText);
  }
  this->window->display();
}