#include <SFML/Graphics.hpp>
#include <iostream>
#include <valarray>
#include "prog4.h"

sf::Sprite& sprite_make(sf::Sprite& s, sf::Texture& t, float x, float y) {

    s.setTexture(t);
    s.setPosition(x, y);
    sf::Vector2f targetSize(50.f, 50.f); //целевой размер

    s.setScale(
            targetSize.x / s.getLocalBounds().width,
            targetSize.y / s.getLocalBounds().height);
    s.setOrigin(s.getLocalBounds().width/2,s.getLocalBounds().height/2);
    return s;
}

struct SpritePlane {
    sf::Sprite s;
    bool isSelect;
    bool isMove;
    bool life;
    SpritePlane():isSelect(false), isMove(false), life(true){}
};

SpritePlane& plane_select(SpritePlane& p, sf::Event& event, const sf::Color& color, const float& tempX, const float& tempY) {
    if (event.type == sf::Event::MouseButtonPressed) { //если нажата клавиша мыши
        if (event.key.code == sf::Mouse::Right) {//а именно правая
            p.isMove = true;//то начинаем движение
            p.isSelect = false;//объект уже не выбран
            p.s.setColor(color);//возвращаем обычный цвет спрайту
            float dX = tempX - p.s.getPosition().x;//вектор, колинеарный прямой, которая пересекает спрайт и курсор
            float dY = tempY - p.s.getPosition().y;//он же, координата y
            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
            p.s.setRotation(90.f + rotation);//поворачиваем спрайт на эти градусы
        } else if (event.key.code == sf::Mouse::Middle) {
            p.isSelect = false;//объект уже не выбран
            p.s.setColor(color);//возвращаем обычный цвет спрайту
        }
    }
    return p;
}
SpritePlane& plane_move(SpritePlane& p, const float& tempX, const float& tempY, const float& time) {
    float x = p.s.getPosition().x, y = p.s.getPosition().y;
    float distance;
    distance = sqrt((tempX - x) * (tempX - x) +
            (tempY - y) * (tempY - y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

    if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта
        p.s.move(0.1 * time * (tempX - x) / distance, 0);//идем по иксу с помощью вектора нормали
        p.s.move(0, 0.1 * time * (tempY - y) / distance);//идем по игреку так же
    } else {
        p.isMove = false;
    }
    return p;
}
int main() {
    unsigned int windowSizeX = 1600, windowSizeY = 900;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY,2), "SFML works!");
    sf::Texture tBack;
    sf::Sprite sBack;        //задний фон
    tBack.loadFromFile("../planes/sky.png");
    sBack.setTexture(tBack);
    sBack.setScale(
            windowSizeX / sBack.getLocalBounds().width,
            windowSizeY / sBack.getLocalBounds().height);

    sf::Vector2f targetSize(50.f, 50.f);
    sf::Texture tExp;
    sf::Sprite sExp;   //взрыв
    tExp.loadFromFile("../planes/explosion.png");
    sExp.setTexture(tExp);
    sExp.setScale(
            targetSize.x / sExp.getLocalBounds().width*2,
            targetSize.y / sExp.getLocalBounds().height*2);

    sf::Texture tPRO, tMask, tRadio, tREB, tScout;
    tPRO.loadFromFile("../planes/pro.png");
    tMask.loadFromFile("../planes/mask.png");
    tRadio.loadFromFile("../planes/radio.png");
    tREB.loadFromFile("../planes/reb.png");
    tScout.loadFromFile("../planes/scout.png");



    SpritePlane p;
    SpritePlane enemy_p;
    p.s = sprite_make(p.s, tMask, 100, 100);
    p.s.setColor(sf::Color::Blue);
    enemy_p.s = sprite_make(enemy_p.s, tREB,1000, 100);
    enemy_p.s.setColor(sf::Color::Red);

    sf::Clock clock;
    sf::Clock Expclock;

    float tempX, tempY, enemy_tempX, enemy_tempY;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();

        time = time/100;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == sf::Mouse::Left) {//а именно левая
                    if (p.s.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
                    {
                        p.s.setColor(sf::Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он может сделать ход
                        p.isSelect = true;
                    }
                    if (enemy_p.s.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
                    {
                        enemy_p.s.setColor(sf::Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он может сделать ход
                        enemy_p.isSelect = true;
                    }
                }
        }

        if (p.life) {
            if (p.isSelect) {//если выбрали объект
                tempX = pos.x;//забираем координату нажатия курсора Х
                tempY = pos.y;//и Y
                p = plane_select(p, event, sf::Color::Blue, tempX, tempY);
            }
            if (p.isMove) {
                p = plane_move(p, tempX, tempY, time);
            }
        }

        if (enemy_p.life) {
            if (enemy_p.isSelect) {//если выбрали объект
                enemy_tempX = pos.x;//забираем координату нажатия курсора Х
                enemy_tempY = pos.y;//и Y
                enemy_p = plane_select(enemy_p, event, sf::Color::Red, enemy_tempX, enemy_tempY);
            }
            if (enemy_p.isMove) {
                enemy_p = plane_move(enemy_p, enemy_tempX, enemy_tempY, time);
            }
        }

        window.clear();
        window.draw(sBack);

        float x1 = p.s.getPosition().x, y1 = p.s.getPosition().y,
                x2 = enemy_p.s.getPosition().x, y2 = enemy_p.s.getPosition().y;
        float dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if (dist < 15 && p.life) {
            p.life = false;
            enemy_p.life = false;
            Expclock.restart();
        }

        if (p.life && enemy_p.life) {
            window.draw(p.s);
            window.draw(enemy_p.s);
        } else {
            if (Expclock.getElapsedTime().asSeconds() < 3) {
                sExp.setPosition(x1, y1);
                window.draw(sExp);
            }
        }
        window.display();
    }

    return 0;
}