#ifndef SQLBD__INPUTOUTPUTDATA_H_
#define SQLBD__INPUTOUTPUTDATA_H_
#include <string>
#include <iostream>
#include "SQLStatement.h"
#include <SFML/Graphics.hpp>

class InputData {
 public:
  virtual void input(std::string &query) = 0;

};

class OutputData {
 public:
  virtual void output(std::string query) = 0;
};
class GraphicsInput:public InputData{
 private:
  std::string& query;
 public:
  GraphicsInput( std::string string):query(string){
  }
  void input(std::string& enteredString) override {
    // Установка размера окна
    sf::RenderWindow window(sf::VideoMode(900, 700), "Menu");
    window.setSize(sf::Vector2u(900, 700));

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("../times_new_roman.ttf")) {
      std::cerr << "Failed to load font" << std::endl;
      return;
    }

    // Создание текста "Enter bank name:"
    sf::Text labelText;
    labelText.setFont(font);
    labelText.setString(query);
    labelText.setCharacterSize(16);
    labelText.setFillColor(sf::Color::Black);
    labelText.setPosition(100, 210);

    // Создание рамки вокруг текста
    sf::RectangleShape labelBox;
    sf::FloatRect labelBounds = labelText.getLocalBounds();
    labelBox.setSize(sf::Vector2f(labelBounds.width + 10, labelBounds.height + 10));
    labelBox.setFillColor(sf::Color::Transparent);
    labelBox.setOutlineColor(sf::Color::Yellow);
    labelBox.setOutlineThickness(2);
    labelBox.setPosition(labelText.getPosition().x - 5, labelText.getPosition().y - 5);

    // Создание поля ввода
    sf::RectangleShape inputField(sf::Vector2f(200, 50));
    inputField.setFillColor(sf::Color::White);
    inputField.setOutlineColor(sf::Color::Black);
    inputField.setOutlineThickness(2);
    inputField.setPosition(window.getSize().x / 2 - inputField.getSize().x / 2, window.getSize().y / 2 - inputField.getSize().y / 2);

    // Создание текста для ввода
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 25);

    bool typing = true;
    bool cursorVisible = true;
    sf::Clock cursorTimer;

    // Загрузка и установка изображения на задний план
    sf::Texture texture;
    if (!texture.loadFromFile("../background.png")) {
      std::cerr << "Failed to load background image" << std::endl;
      return;
    }
    sf::Sprite background(texture);

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
        if (event.type == sf::Event::TextEntered) {
          if (typing) {
            if (event.text.unicode == '\b' && !enteredString.empty()) { // Backspace
              enteredString.pop_back();
            } else if (event.text.unicode < 128) { // ASCII characters
              enteredString += static_cast<char>(event.text.unicode);
            }
            text.setString(enteredString);
          }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (inputField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
              typing = true;
            } else {
              typing = false;
            }
          }
        }
        // Проверяем нажатие Enter
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
          // Если введено что-то в поле
          if (!enteredString.empty()) {
            // Закрываем окно через 0.1 секунды
            sf::sleep(sf::milliseconds(100));
            window.close();
          }
        }
      }

      if (cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
        cursorVisible = !cursorVisible;
        cursorTimer.restart();
      }

      window.clear();

      // Рисуем задний план
      background.setScale(900.0f / background.getTexture()->getSize().x, 700.0f / background.getTexture()->getSize().y);
      window.draw(background);

      // Рисуем элементы интерфейса
      window.draw(inputField);

      // Рисуем рамку вокруг текста
      window.draw(labelBox);

      // Рисуем текст
      window.draw(labelText);
      window.draw(text);

      // Рисуем курсор, если вводится текст
      if (typing && cursorVisible) {
        sf::Text cursor("|", font, 24);
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition(text.getPosition().x + text.getLocalBounds().width, text.getPosition().y);
        window.draw(cursor);
      }


      window.display();

    }
  }


};

/////////////////////////////////////////////
class SQLOutput : public OutputData {
 public:
  void output(std::string query) override {
    SqlCin(query);
  }
};

class ConsoleOutput : public OutputData {
 public:
  void output(std::string query) override {
    std::cout << query;
  }
};
////////////////////////////////////////////
class ConsoleInput : public InputData {
 public:
  void input(std::string &query) override {
    std::getline(std::cin, query);
  }
};
class SQLInput : public InputData {
 private:
  std::string fieldName_;
  std::string bank_;
  std::string condition_;
 public:
  SQLInput(std::string fieldName, std::string bank, std::string condition)
      : fieldName_(fieldName), bank_(bank), condition_(condition) {}
  void input(std::string &query) override {
    query = GetValueFromDatabase("test.db", fieldName_, bank_, condition_);
  }
};
#endif //SQLBD__INPUTOUTPUTDATA_H_
