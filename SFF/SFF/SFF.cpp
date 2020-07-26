#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Context;

class Menu
{
protected:
    Context* m_context{ nullptr };
    int currentPosition{ 0 };
    std::vector<sf::Text> buttons;
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void clickButton() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
};

class Context
{
private:
    Menu* m_menu;
public:
    Context();
    void setMenu(Menu* menu)
    {
        m_menu = menu;
    }
    void draw(sf::RenderWindow& window)
    {
        m_menu->draw(window);
    }
    void clickButton()
    {
        m_menu->clickButton();
    }
    void moveUp()
    {
        m_menu->moveUp();
    }
    void moveDown()
    {
        m_menu->moveDown();
    }
};

class FirstMenu: public Menu
{
public:
    FirstMenu(Context* context)
    {
        this->m_context = context;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "Error occured. \n";
        }
        sf::Text text;
        sf::Text text1;
        sf::Text text2;
        text.setFont(font);
        text1.setFont(font);
        text2.setFont(font);
        text.setFillColor(sf::Color::Red);
        text.setPosition(250, 150);
        text1.setFillColor(sf::Color::White);
        text1.setPosition(250, 250);
        text2.setFillColor(sf::Color::White);
        text2.setPosition(250, 350);
        this->buttons.push_back(text);
        this->buttons.push_back(text1);
        this->buttons.push_back(text2);

    }
    virtual void moveUp()
    {
        for (int i = 0; i < this->buttons.size(); i++)
        {
            if (i == currentPosition)
            {
                this->buttons[i].setFillColor(sf::Color::White);
                currentPosition--;
                this->buttons[i-1].setFillColor(sf::Color::Red);
                break;
            }
        }
    }
    virtual void moveDown()
    {
        for (int i = 0; i < this->buttons.size(); i++)
        {
            if (i == currentPosition)
            {
                this->buttons[i].setFillColor(sf::Color::White);
                currentPosition++;
                this->buttons[i+1].setFillColor(sf::Color::Red);
                break;
            }
        }
    }
    virtual void draw(sf::RenderWindow& window)
    {
        for (auto i : this->buttons)
        {
            window.draw(i);
        }
    }
    virtual void clickButton()
    {
        std::cout << "Button clicked. \n";
    }

};

class SecondMenu: public Menu
{

};

Context::Context()
{
    this->m_menu = new FirstMenu(this);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    Context context;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    context.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    context.moveDown();
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    context.clickButton();
                }
            }
        }
        window.clear();
        context.draw(window);
        window.display();
    }

    return 0;
}