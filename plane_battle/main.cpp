#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <valarray>
#include "prog4.h"
#include <stdlib.h>
#include <time.h>
sf::Sprite& sprite_make(sf::Sprite& s, sf::Texture& t, const sf::Color& color, float x, float y) {

    s.setTexture(t);
    s.setPosition(x, y);
    sf::Vector2f targetSize(50.f, 50.f); //целевой размер
    s.setScale(
            targetSize.x / s.getLocalBounds().width,
            targetSize.y / s.getLocalBounds().height);
    s.setOrigin(s.getLocalBounds().width/2,s.getLocalBounds().height/2);
    s.setColor(color);
    return s;
}

int link_prepareToMove(Link &l, const float& x, const float& y) {
    for (int i = 0; i < l.get_plane_count(); i++) {
        if (l.s[i].getGlobalBounds().contains(x, y)) {
            l.isSelectToMove = true;
        }
    }
    if (l.isSelectToMove == true) {
        for (int i = 0; i < l.get_plane_count(); i++)
            if (l.isSelectToRocket[i] == false && l.isSelectToGun[i] == false) {
                l.s[i].setColor(sf::Color::Green);
            }
    }
    return 0;
}

int link_selectToMove(Link& l, sf::Event& event,  const sf::Color& color, float x, float y) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == sf::Mouse::Right) {
            l.isMove = true;
            l.isSelectToMove = false;
            l.set_x(x);
            l.set_y(y);
            float dX = x - l.s[0].getPosition().x;
            float dY = y - l.s[0].getPosition().y;
            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
            for (int i = 0; i < l.get_plane_count(); i++) {
                l.s[i].setColor(color);
                l.isSelectToRocket[i] = false;
                l.isSelectToGun[i] = false;
                l.s[i].setRotation(90.f + rotation);
            }
        } else if (event.key.code == sf::Mouse::Middle) {
            l.isSelectToMove = false;
            for (int i = 0; i < l.get_plane_count(); i++) {
                l.s[i].setColor(color);
                l.isSelectToRocket[i] = false;
                l.isSelectToGun[i] = false;
            }
        }
    }
    return 0;
}

int link_move(Link& l, const float& time) {
    float x = l.s[0].getPosition().x, y = l.s[0].getPosition().y;
    float distance;
    distance = sqrt((l.get_x() - x) * (l.get_x() - x) +
                    (l.get_y() - y) * (l.get_y() - y));
    if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта
        for (int i = 0; i < l.get_plane_count(); i++) {
            l.s[i].move(0.1 * time * (l.get_x() - x) / distance, 0);//идем по иксу с помощью вектора нормали
            l.s[i].move(0, 0.1 * time * (l.get_y() - y) / distance);//идем по игреку так же
            l.update_healthBar();
            l.update_RocketBar();
        }
        return 0;
    } else {
        l.isMove = false;
        return 1;
    }
}

void planes_moving(int &hod, Mission &m, sf::Sound &soundPlane, sf::Event &event, const sf::Vector2f &pos, float time) {
    if (hod) {
        for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
            if (it->link.isSelectToMove) {//если выбрали объект
                it->link.set_x(pos.x);
                it->link.set_y(pos.y);
                link_selectToMove(it->link, event, sf::Color::Blue, pos.x, pos.y);
                if (it->link.isMove) {
                    soundPlane.play();
                }
            }
            if (it->link.isMove) {
                if (link_move(it->link, time) == 1) {
                    soundPlane.stop();
                    hod = 0;
                    for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                        it->link.isMove = false;
                    }
                }
            }
        }
    } else {
        for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
            if (it->link.isSelectToMove) {//если выбрали объект
                it->link.set_x(pos.x);
                it->link.set_y(pos.y);
                link_selectToMove(it->link, event, sf::Color::Red, pos.x, pos.y);
                if (it->link.isMove) {
                    soundPlane.play();
                }
            }
            if (it->link.isMove) {
                if (link_move(it->link, time) == 1) {
                    soundPlane.stop();
                    hod = 1;
                    for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                        it->link.isMove = false;
                    }
                }
            }
        }
    }
}

struct SpriteAmmo {
    sf::Sprite s;
    float x, y; //целевые координаты
    bool life;
    bool isMove;
    int id, index;
    int status; //1 - если ракета от нас к врагу, 0 - от врага к нам
    float cur_dist;
    float max_dist;
    SpriteAmmo(): isMove(false), life(false), cur_dist(0.f) {}
};

struct SpriteExplosion {
    sf::Sprite s;
    sf::Sound sound;
    bool life;
    sf::Clock clock;
    SpriteExplosion():life(false) {}
};

int link_prepareToRocket(Link &l, const float& x, const float& y) {
    for (int i = 0; i < l.get_plane_count(); i++) {
        if (l.s[i].getGlobalBounds().contains(x, y)) {
            l.isSelectToRocket[i] = true;
            l.isSelectToGun[i] = false;
            l.s[i].setColor(sf::Color::Magenta);
        }
    }
    return 0;
}

int link_prepareToBullet(Link &l, const float& x, const float& y) {
    for (int i = 0; i < l.get_plane_count(); i++) {
        if (l.s[i].getGlobalBounds().contains(x, y)) {
            l.isSelectToGun[i] = true;
            l.isSelectToRocket[i] = false;
            l.s[i].setColor(sf::Color::Cyan);
        }
    }
    return 0;
}

int link_selectToBullet(Link& l, int index, sf::Event& event,  const sf::Color& color, float x, float y) {
    if (event.key.code == sf::Keyboard::Num4) {
        float dX = x - l.s[index].getPosition().x;
        float dY = y - l.s[index].getPosition().y;
        float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
        if (l.isSelectToMove) {
            l.s[index].setColor(sf::Color::Green);
        } else {
            l.s[index].setColor(color);
        }
        l.isSelectToGun[index] = false;
        for (int i = 0; i < l.get_plane_count(); i++) {
            l.s[i].setRotation(90.f + rotation);
        }
        return 1;   //цель выбрана, выпуск ракеты
    } else if (event.key.code == sf::Mouse::Middle) {
        if (l.isSelectToMove) {
            l.s[index].setColor(sf::Color::Green);
        } else {
            l.s[index].setColor(color);
        }
        l.isSelectToGun[index] = false;
        return 0;  //выпуск ракеты отменен
    }
    return 0;
}


int link_selectToRocket(Link& l, int index, sf::Event& event,  const sf::Color& color, float x, float y) {
    if (event.key.code == sf::Keyboard::Num2) {
        float dX = x - l.s[index].getPosition().x;
        float dY = y - l.s[index].getPosition().y;
        float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
        if (l.isSelectToMove) {
            l.s[index].setColor(sf::Color::Green);
        } else {
            l.s[index].setColor(color);
        }
        l.isSelectToRocket[index] = false;
        for (int i = 0; i < l.get_plane_count(); i++) {
            l.s[i].setRotation(90.f + rotation);
        }
        return 1;   //цель выбрана, выпуск ракеты
    } else if (event.key.code == sf::Mouse::Middle) {
        if (l.isSelectToMove) {
            l.s[index].setColor(sf::Color::Green);
        } else {
            l.s[index].setColor(color);
        }
        l.isSelectToRocket[index] = false;
        return 0;  //выпуск ракеты отменен
    }
    return 0;
}

int bullet_move(SpriteAmmo& sr, const float& time) { //0 - пуля в движении, 1 - недолет до цели, 2 - попадание в цель
    if (!(sr.life && sr.isMove)) {
        return 3;
    }
    float x = sr.s.getPosition().x, y = sr.s.getPosition().y;
    float distance;
    distance = sqrt((sr.x - x) * (sr.x - x) +
                    (sr.y - y) * (sr.y - y));
    if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта
        float offsetX = 0.1 * time * (sr.x - x) / distance;
        float offsetY = 0.1 * time * (sr.y - y) / distance;
        sr.s.move(offsetX, 0);//идем по иксу с помощью вектора нормали
        sr.s.move(0, offsetY);//идем по игреку так же
        sr.cur_dist += sqrt(offsetX * offsetX + offsetY * offsetY);
        if (sr.cur_dist >= sr.max_dist) {
            sr.life = false;
            sr.isMove = false;
            return 1;        //взрыв с недолетом
        }
        return 0;        //ракета в движении
    } else {
        sr.life = false;
        sr.isMove = false;
        return 2;  //взрыв с попаданием в цель
    }
}

int rocket_move(SpriteAmmo& sr, const float& time) { //0 - ракета в движении, 1 - взрыв с недолетом, 2 - взрыв с попаданием в цель
    if (!(sr.life && sr.isMove)) {
        return 3;
    }
    float x = sr.s.getPosition().x, y = sr.s.getPosition().y;
    float distance;
    distance = sqrt((sr.x - x) * (sr.x - x) +
                    (sr.y - y) * (sr.y - y));
    if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта
        float offsetX = 0.1 * time * (sr.x - x) / distance;
        float offsetY = 0.1 * time * (sr.y - y) / distance;
        sr.s.move(offsetX, 0);//идем по иксу с помощью вектора нормали
        sr.s.move(0, offsetY);//идем по игреку так же
        sr.cur_dist += sqrt(offsetX * offsetX + offsetY * offsetY);
        if (sr.cur_dist >= sr.max_dist) {
            sr.life = false;
            sr.isMove = false;
            return 1;        //взрыв с недолетом
        }
        return 0;        //ракета в движении
    } else {
        sr.life = false;
        sr.isMove = false;
        return 2;  //взрыв с попаданием в цель
    }
}

void rocket_shoot_and_fly(int hod, Mission &m, sf::Event &event, sf::Sound *soundRocket, SpriteAmmo *sr,  int max_rocket_count, SpriteExplosion *se, int max_explosion_count,const sf::Vector2f &pos, float time) {
    //////////пуск ракеты//////////////
    if (hod) {
        if (event.key.code == sf::Keyboard::Num1) {
            for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                link_prepareToRocket(it->link, pos.x, pos.y);
            }
        }
    } else {
        if (event.key.code == sf::Keyboard::Num1) {
            for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                link_prepareToRocket(it->link, pos.x, pos.y);
            }
        }
    }

    if (hod) {
        for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
            for (int i = 0; i < it->link.get_plane_count(); i++) {
                if (it->link.isSelectToRocket[i] == true) {
                    if (link_selectToRocket(it->link, i, event, sf::Color::Blue, pos.x, pos.y) == 1) {
                        if (it->link.get_plane(i + 1)->get_rocket().get_cur_count() <= 0)
                            continue;
                        int rocket_index = -1;
                        for (int j = 0; j < max_rocket_count; j++) {
                            if (!(sr[j].life || sr[j].isMove)) {
                                rocket_index = j;
                                break;
                            }
                        }
                        if (rocket_index >= 0) {
                            sr[rocket_index].life = true;
                            sr[rocket_index].isMove = true;
                            sr[rocket_index].x = pos.x;
                            sr[rocket_index].y = pos.y;
                            sr[rocket_index].id = it->id;
                            sr[rocket_index].index = i;
                            sr[rocket_index].status = 1;
                            sr[rocket_index].cur_dist = 0.f;
                            sr[rocket_index].s.setPosition(it->link.s[i].getPosition().x,
                                                           it->link.s[i].getPosition().y);
                            float dX = pos.x - it->link.s[i].getPosition().x;
                            float dY = pos.y - it->link.s[i].getPosition().y;
                            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
                            sr[rocket_index].s.setRotation(90.f + rotation);
                            soundRocket[rocket_index].play();
                        }
                    }
                }
            }
        }
    } else {
        for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
            for (int i = 0; i < it->link.get_plane_count(); i++) {
                if (it->link.isSelectToRocket[i] == true) {
                    if (link_selectToRocket(it->link, i, event, sf::Color::Red, pos.x, pos.y) == 1) {
                        if (it->link.get_plane(i + 1)->get_rocket().get_cur_count() <= 0)
                            continue;
                        int rocket_index = -1;
                        for (int j = 0; j < max_rocket_count; j++) {
                            if (!(sr[j].life || sr[j].isMove)) {
                                rocket_index = j;
                                break;
                            }
                        }
                        if (rocket_index >= 0) {
                            sr[rocket_index].life = true;
                            sr[rocket_index].isMove = true;
                            sr[rocket_index].x = pos.x;
                            sr[rocket_index].y = pos.y;
                            sr[rocket_index].id = it->id;
                            sr[rocket_index].index = i;
                            sr[rocket_index].status = 0;
                            sr[rocket_index].cur_dist = 0.f;
                            sr[rocket_index].s.setPosition(it->link.s[i].getPosition().x,
                                                           it->link.s[i].getPosition().y);
                            float dX = pos.x - it->link.s[i].getPosition().x;
                            float dY = pos.y - it->link.s[i].getPosition().y;
                            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
                            sr[rocket_index].s.setRotation(90.f + rotation);
                            soundRocket[rocket_index].play();
                        }
                    }
                }
            }
        }
    }
    ///////////////////
    //////движение ракеты
    for (int i = 0; i < max_rocket_count; i++) {
        if (sr[i].life && sr[i].isMove) {
            int status = rocket_move(sr[i], time);
            if (status == 1)  {
                //взрыв по координатам ракеты с недолетом
                Plane *p;
                if (sr[i].status == 1) {
                    p = m.get_plane_t(sr[i].id, sr[i].index+1);
                } else p = m.get_plane_enemy_t(sr[i].id, sr[i].index+1);
                int rof = p->get_rocket().get_rof();
                int k = p->get_rocket().get_cur_count();
                k -= rof;
                if (k < 0) k = 0;
                p->get_rocket().set_cur_count(k);
                for (int j = 0; j < max_explosion_count; j++) {
                    if (se[j].life == false) {
                        se[j].life = true;
                        se[j].s.setPosition(sr[i].s.getPosition().x, sr[i].s.getPosition().y);
                        se[j].clock.restart();
                        soundRocket[i].stop();
                        se[j].sound.play();
                        break;
                    }
                }
            } else if (status == 2) {
                //взрыв по координатам ракеты с попаданием в цель
                int shoot_plane = false;
                for (int j = 0; j < max_explosion_count; j++) {
                    if (se[j].life == false) {
                        se[j].life = true;
                        se[j].s.setPosition(sr[i].x, sr[i].y);
                        se[j].clock.restart();
                        soundRocket[i].stop();
                        se[j].sound.play();
                        break;
                    }
                }
                if (sr[i].status == 1) {
                    int link_count = m.get_Link_count_enemy_t();
                    for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                        if (link_count > m.get_Link_count_enemy_t())
                            break;
                        for (int j = 0; j < it->link.get_plane_count(); j++) {
                            if (it->link.s[j].getGlobalBounds().contains(sr[i].x, sr[i].y)) {
                                m.rocket_shoot_plane_in_enemy_t(sr[i].id, sr[i].index+1, it->id, j+1, 0);
                                if (link_count == m.get_Link_count_enemy_t())
                                    it->link.update_healthBar();
                                m.get_link_t(sr[i].id).update_RocketBar();
                                shoot_plane = true;
                                break;
                            }
                        }
                    }

                    if (!shoot_plane) {
                        Plane *p = m.get_plane_t(sr[i].id, sr[i].index + 1);
                        int rof = p->get_rocket().get_rof();
                        int k = p->get_rocket().get_cur_count();
                        k -= rof;
                        if (k < 0) k = 0;
                        p->get_rocket().set_cur_count(k);
                        m.get_link_t(sr[i].id).update_RocketBar();
                    }
                } else if (sr[i].status == 0) {
                    int link_count = m.get_Link_count_t();
                    for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                        if (link_count > m.get_Link_count_t())
                            break;
                        for (int j = 0; j < it->link.get_plane_count(); j++) {
                            if (it->link.s[j].getGlobalBounds().contains(sr[i].x, sr[i].y)) {
                                m.rocket_shoot_plane_in_t(sr[i].id, sr[i].index+1, it->id, j+1, 0);
                                if (link_count == m.get_Link_count_t())
                                    it->link.update_healthBar();
                                shoot_plane = true;
                                break;
                            }
                        }
                    }

                    if (!shoot_plane) {
                        Plane *p = m.get_plane_enemy_t(sr[i].id, sr[i].index + 1);
                        int rof = p->get_rocket().get_rof();
                        int k = p->get_rocket().get_cur_count();
                        k -= rof;
                        if (k < 0) k = 0;
                        p->get_rocket().set_cur_count(k);
                    }
                }
            }
        }
    }
}

void bullet_shoot_and_fly(int hod, Mission &m, sf::Event &event, sf::Sound *soundGun, SpriteAmmo *sb, int max_bullet_count, SpriteExplosion *se, int max_explosion_count, const sf::Vector2f &pos, float time) {
    //////////пуск ракеты//////////////
    if (hod) {
        if (event.key.code == sf::Keyboard::Num3) {
            for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                link_prepareToBullet(it->link, pos.x, pos.y);
            }
        }
    } else {
        if (event.key.code == sf::Keyboard::Num3) {
            for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                link_prepareToBullet(it->link, pos.x, pos.y);
            }
        }
    }

    if (hod) {
        for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
            for (int i = 0; i < it->link.get_plane_count(); i++) {
                if (it->link.isSelectToGun[i] == true) {
                    if (link_selectToBullet(it->link, i, event, sf::Color::Blue, pos.x, pos.y) == 1) {
                        int bullet_index = -1;
                        for (int j = 0; j < max_bullet_count; j++) {
                            if (!(sb[j].life || sb[j].isMove)) {
                                bullet_index = j;
                                break;
                            }
                        }
                        if (bullet_index >= 0) {
                            sb[bullet_index].life = true;
                            sb[bullet_index].isMove = true;
                            sb[bullet_index].x = pos.x;
                            sb[bullet_index].y = pos.y;
                            sb[bullet_index].id = it->id;
                            sb[bullet_index].index = i;
                            sb[bullet_index].status = 1;
                            sb[bullet_index].cur_dist = 0.f;
                            sb[bullet_index].s.setPosition(it->link.s[i].getPosition().x,
                                                           it->link.s[i].getPosition().y);
                            float dX = pos.x - it->link.s[i].getPosition().x;
                            float dY = pos.y - it->link.s[i].getPosition().y;
                            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
                            sb[bullet_index].s.setRotation(90.f + rotation);
                            soundGun[bullet_index].play();
                        }
                    }
                }
            }
        }
    } else {
        for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
            for (int i = 0; i < it->link.get_plane_count(); i++) {
                if (it->link.isSelectToGun[i] == true) {
                    if (link_selectToBullet(it->link, i, event, sf::Color::Red, pos.x, pos.y) == 1) {
                        int bullet_index = -1;
                        for (int j = 0; j < max_bullet_count; j++) {
                            if (!(sb[j].life || sb[j].isMove)) {
                                bullet_index = j;
                                break;
                            }
                        }
                        if (bullet_index >= 0) {
                            sb[bullet_index].life = true;
                            sb[bullet_index].isMove = true;
                            sb[bullet_index].x = pos.x;
                            sb[bullet_index].y = pos.y;
                            sb[bullet_index].id = it->id;
                            sb[bullet_index].index = i;
                            sb[bullet_index].status = 0;
                            sb[bullet_index].cur_dist = 0.f;
                            sb[bullet_index].s.setPosition(it->link.s[i].getPosition().x,
                                                           it->link.s[i].getPosition().y);
                            float dX = pos.x - it->link.s[i].getPosition().x;
                            float dY = pos.y - it->link.s[i].getPosition().y;
                            float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
                            sb[bullet_index].s.setRotation(90.f + rotation);
                            soundGun[bullet_index].play();
                        }
                    }
                }
            }
        }
    }
    ///////////////////
    //////движение пули
    for (int i = 0; i < max_bullet_count; i++) {
        if (sb[i].life && sb[i].isMove) {
            int status = bullet_move(sb[i], time);
            if (status == 2) {
                //взрыв по координатам пули с попаданием в цель
                if (sb[i].status == 1) {
                    int link_count = m.get_Link_count_enemy_t();
                    for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                        if (link_count > m.get_Link_count_enemy_t())
                            break;
                        int plane_count = it->link.get_plane_count();
                        for (int j = 0; j < it->link.get_plane_count(); j++) {
                            if (it->link.s[j].getGlobalBounds().contains(sb[i].x, sb[i].y)) {
                                m.gun_shoot_plane_in_enemy_t(sb[i].id, sb[i].index+1, it->id, j+1, 0);
                                if (link_count > m.get_Link_count_enemy_t() || plane_count > it->link.get_plane_count()) {
                                    for (int k = 0; k < max_explosion_count; k++) {
                                        if (se[k].life == false) {
                                            se[k].life = true;
                                            se[k].s.setPosition(sb[i].x, sb[i].y);
                                            se[k].clock.restart();
                                            soundGun[i].stop();
                                            se[k].sound.play();
                                            break;
                                        }
                                    }
                                }
                                if (link_count == m.get_Link_count_enemy_t())
                                    it->link.update_healthBar();
                                break;
                            }
                        }
                    }
                } else if (sb[i].status == 0) {
                    int link_count = m.get_Link_count_t();
                    for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                        if (link_count > m.get_Link_count_t())
                            break;
                        int plane_count = it->link.get_plane_count();
                        for (int j = 0; j < it->link.get_plane_count(); j++) {
                            if (it->link.s[j].getGlobalBounds().contains(sb[i].x, sb[i].y)) {
                                m.gun_shoot_plane_in_t(sb[i].id, sb[i].index+1, it->id, j+1, 0);
                                if (link_count > m.get_Link_count_t() || plane_count > it->link.get_plane_count()) {
                                    for (int k = 0; k < max_explosion_count; k++) {
                                        if (se[k].life == false) {
                                            se[k].life = true;
                                            se[k].s.setPosition(sb[i].x, sb[i].y);
                                            se[k].clock.restart();
                                            soundGun[i].stop();
                                            se[k].sound.play();
                                            break;
                                        }
                                    }
                                }
                                if (link_count == m.get_Link_count_t())
                                    it->link.update_healthBar();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void inserting_planes(Mission &m, sf::Texture *tPlane, sf::Texture &trocket, float windowSizeX, float windowSizeY) {
    PRO pro; Mask mask; Radio radio; REB reb; Scout scout;
    srand(time(nullptr));
    int link_count = rand() % 4 + 1;
    float x, y;
    int type;

    //синяя команда
    for (int i = 0; i < link_count; i++) {
        x = rand() % (int)windowSizeX;
        y = rand() % (int)windowSizeY;
        if (x > windowSizeX - 200.f) {
            x = windowSizeX - 200.f;
        }
        if (y > windowSizeY - 100.f) {
            y = windowSizeY - 100.f;
        }
        for (int j = 0; j < 4; j++) {
            type = rand() % 5;
            if (type == 0) {
                m.insert_plane_t(i + 1, pro);
            } else if (type == 1) {
                m.insert_plane_t(i + 1, mask);
            } else if (type == 2) {
                m.insert_plane_t(i + 1, radio);
            } else if (type == 3) {
                m.insert_plane_t(i + 1, reb);
            } else if (type == 4) {
                m.insert_plane_t(i + 1, scout);
            }
            sprite_make(m.get_link_t(i+1).s[j], tPlane[type], sf::Color::Blue, x, y);
            x += 50; y += 25;
        }
        m.get_link_t(i+1).RocketBarLoadTexture(trocket);
        m.get_link_t(i+1).update_healthBar();
        m.get_link_t(i+1).update_RocketBar();
    }

    //красная команда
    for (int i = 0; i < link_count; i++) {
        x = rand() % (int)windowSizeX;
        y = rand() % (int)windowSizeY;
        if (x > windowSizeX - 200.f) {
            x = windowSizeX - 200.f;
        }
        if (y > windowSizeY - 100.f) {
            y = windowSizeY - 100.f;
        }
        for (int j = 0; j < 4; j++) {
            type = rand() % 5;
            if (type == 0) {
                m.insert_plane_enemy_t(i + 1, pro);
            } else if (type == 1) {
                m.insert_plane_enemy_t(i + 1, mask);
            } else if (type == 2) {
                m.insert_plane_enemy_t(i + 1, radio);
            } else if (type == 3) {
                m.insert_plane_enemy_t(i + 1, reb);
            } else if (type == 4) {
                m.insert_plane_enemy_t(i + 1, scout);
            }
            sprite_make(m.get_link_enemy_t(i+1).s[j], tPlane[type], sf::Color::Red, x, y);
            x += 50; y += 25;
        }
        m.get_link_enemy_t(i+1).RocketBarLoadTexture(trocket);
        m.get_link_enemy_t(i+1).update_healthBar();
        m.get_link_enemy_t(i+1).update_RocketBar();
    }

}

int SomePlanes() {
    unsigned int windowSizeX = 1600, windowSizeY = 900;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY, 32), "Planes battle");
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
            targetSize.x / sExp.getLocalBounds().width,
            targetSize.y / sExp.getLocalBounds().height);

    sf::Texture tPlane[5];
    tPlane[0].loadFromFile("../planes/pro.png");
    tPlane[1].loadFromFile("../planes/mask.png");
    tPlane[2].loadFromFile("../planes/radio.png");
    tPlane[3].loadFromFile("../planes/reb.png");
    tPlane[4].loadFromFile("../planes/scout.png");

    sf::Texture trocket, tbullet;
    trocket.loadFromFile("../planes/rocket.png");
    tbullet.loadFromFile("../planes/bullet.png");

    Mission m;
    //inserting planes///////////////////

    inserting_planes(m, tPlane, trocket, windowSizeX, windowSizeY);

    ///настройка звуков полета истребителей
    sf::Sound soundPlane;
    sf::SoundBuffer planeBuffer;
    planeBuffer.loadFromFile("../planes/plane.ogg");
    soundPlane.setBuffer(planeBuffer);
    soundPlane.setLoop(true);

    /////////////////////////
    //////настройка спрайтов и звуков для боеприпасов
    int max_link_count = my_max(m.get_Link_count_t(),m.get_Link_count_enemy_t());
    Rocket rocket_prototype;
    int max_rocket_count = max_link_count*rocket_prototype.get_max_count()*4;
    sf::Sound *soundRocket = new sf::Sound[max_rocket_count];
    sf::SoundBuffer rocketBuffer;
    rocketBuffer.loadFromFile("../planes/rocket.ogg");
    SpriteAmmo* sr = new SpriteAmmo[max_rocket_count];
    for (int i = 0; i < max_rocket_count; i++) {
        sr[i].s.setTexture(trocket);
        sr[i].s.setScale(
                targetSize.x / sr[i].s.getLocalBounds().width/5,
                targetSize.y / sr[i].s.getLocalBounds().height);
        sr[i].max_dist = rocket_prototype.get_dist();
        soundRocket[i].setBuffer(rocketBuffer);
    }

    Gun gun_prototype;
    PRO pro;
    int max_bullet_count = max_link_count*pro.get_gun_count()*4;
    sf::Sound *soundGun = new sf::Sound[max_bullet_count];
    sf::SoundBuffer gunBuffer;
    gunBuffer.loadFromFile("../planes/gun.ogg");
    SpriteAmmo* sb = new SpriteAmmo[max_bullet_count];
    for (int i = 0; i < max_bullet_count; i++) {
        sb[i].s.setTexture(tbullet);
        sb[i].s.setScale(
                targetSize.x / sb[i].s.getLocalBounds().width/10,
                targetSize.y / sb[i].s.getLocalBounds().height/2);
        sb[i].max_dist = gun_prototype.get_dist();
        soundGun[i].setBuffer(gunBuffer);
    }

    ///////////////////////////
    //////спрайты и звуки для взрывов
    int max_explosion_count = max_rocket_count+max_bullet_count;
    sf::SoundBuffer expBuffer;
    expBuffer.loadFromFile("../planes/explosion.ogg");
    SpriteExplosion *se = new SpriteExplosion[max_explosion_count];
    for (int i = 0; i < max_explosion_count; i++) {
        sprite_make(se[i].s, tExp, sf::Color::White, 0.f, 0.f);
        se[i].s.setScale(targetSize.x / se[i].s.getLocalBounds().width * 1.5,
                targetSize.y / se[i].s.getLocalBounds().height * 1.5);
        se[i].sound.setBuffer(expBuffer);
    }
    ////////////////////////
    sf::Clock clock;
    int hod = 1;
    //прямоугольник и текст со статусом хода
    sf::RectangleShape shape(sf::Vector2f(windowSizeX/8,windowSizeY/18));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(3);
    shape.setPosition(windowSizeX/16*7, 3);

    sf::Font font;
    font.loadFromFile("../arialmt.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);


    //текстуры для победителей
    sf::Texture tWinBlue, tWinRed;
    tWinBlue.loadFromFile("../planes/winnerBlue.png");
    tWinRed.loadFromFile("../planes/winnerRed.png");
    sf::Sprite winnerSprite;

    //музыка на фоне
    sf::Music music;
    music.openFromFile("../planes/musicButtle.ogg");
    music.setLoop(true);
    music.setVolume(20);
    music.play();

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 100;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if (m.get_Link_count_enemy_t() <= 0) {
            sprite_make(winnerSprite, tWinBlue, sf::Color::White, windowSizeX/2, windowSizeY/2);
            winnerSprite.setScale(
                    windowSizeX / winnerSprite.getLocalBounds().width,
                    windowSizeY / winnerSprite.getLocalBounds().height);
            window.draw(winnerSprite);
        } else if (m.get_Link_count_t() <= 0) {
            sprite_make(winnerSprite, tWinRed, sf::Color::White, windowSizeX/2, windowSizeY/2);
            winnerSprite.setScale(
                    windowSizeX / winnerSprite.getLocalBounds().width,
                    windowSizeY / winnerSprite.getLocalBounds().height);
            window.draw(winnerSprite);
        } else {
            if (event.type == sf::Event::MouseButtonPressed) {//если нажата клавиша мыши
                if (event.key.code == sf::Mouse::Left) {//а именно левая
                    if (hod) {
                        for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                            link_prepareToMove(it->link, pos.x, pos.y);
                        }
                    } else {
                        for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                            link_prepareToMove(it->link, pos.x, pos.y);
                        }
                    }
                }
            }

            //стрельба ракетами и их полет
            rocket_shoot_and_fly(hod, m, event, soundRocket, sr, max_rocket_count, se, max_explosion_count, pos, time);
            //стрельба пулями и их полет
            bullet_shoot_and_fly(hod, m, event, soundGun, sb, max_bullet_count, se, max_explosion_count, pos, time);
            //перемещение истребителей
            planes_moving(hod, m, soundPlane, event, pos, time);

            window.draw(sBack);

            if (hod == 1) {
                shape.setOutlineColor(sf::Color::Blue);
                text.setString("Blue team's move");
                text.setFillColor(sf::Color::Blue);
                text.setPosition(windowSizeX / 16 * 7 + 3, 12);
            } else {
                shape.setOutlineColor(sf::Color::Red);
                text.setString("Red team's move");
                text.setFillColor(sf::Color::Red);
                text.setPosition(windowSizeX / 16 * 7 + 5, 12);
            }
            window.draw(shape);
            window.draw(text);

            for (int i = 0; i < max_rocket_count; i++) {
                if (sr[i].life) {
                    window.draw(sr[i].s);
                }
            }
            for (int i = 0; i < max_bullet_count; i++) {
                if (sb[i].life) {
                    window.draw(sb[i].s);
                    //soundGun[i].play();
                }
            }

            for (It it = m.get_begin_t(); it != m.get_end_t(); it++) {
                for (int i = 0; i < it->link.get_plane_count(); i++) {
                    window.draw(it->link.s[i]);
                    window.draw(it->link.healthBar[i].green);
                    window.draw(it->link.healthBar[i].red);
                    for (int j = 0; j < it->link.get_plane(i + 1)->get_rocket().get_cur_count(); j++) {
                        window.draw(it->link.rocketBar[i].rocket[j]);
                    }

                    if (it->link.isSelectToRocket[i] == true) {
                        sf::CircleShape circle(rocket_prototype.get_dist(), 100);
                        circle.setPosition(it->link.s[i].getPosition());
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        circle.setOutlineColor(sf::Color::Magenta);
                        circle.setOutlineThickness(5);
                        circle.setFillColor(sf::Color::Transparent);
                        window.draw(circle);
                    }
                    if (it->link.isSelectToGun[i] == true) {
                        sf::CircleShape circle(gun_prototype.get_dist(), 100);
                        circle.setPosition(it->link.s[i].getPosition());
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        circle.setOutlineColor(sf::Color::Cyan);
                        circle.setOutlineThickness(5);
                        circle.setFillColor(sf::Color::Transparent);
                        window.draw(circle);
                    }
                }
            }

            for (It it = m.get_begin_enemy_t(); it != m.get_end_enemy_t(); it++) {
                for (int i = 0; i < it->link.get_plane_count(); i++) {
                    window.draw(it->link.s[i]);
                    window.draw(it->link.healthBar[i].green);
                    window.draw(it->link.healthBar[i].red);
                    for (int j = 0; j < it->link.get_plane(i + 1)->get_rocket().get_cur_count(); j++) {
                        window.draw(it->link.rocketBar[i].rocket[j]);
                    }

                    if (it->link.isSelectToRocket[i] == true) {
                        sf::CircleShape circle(rocket_prototype.get_dist(), 100);
                        circle.setPosition(it->link.s[i].getPosition());
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        circle.setOutlineColor(sf::Color::Magenta);
                        circle.setOutlineThickness(5);
                        circle.setFillColor(sf::Color::Transparent);
                        window.draw(circle);
                    }
                    if (it->link.isSelectToGun[i] == true) {
                        sf::CircleShape circle(gun_prototype.get_dist(), 100);
                        circle.setPosition(it->link.s[i].getPosition());
                        circle.setOrigin(circle.getRadius(), circle.getRadius());
                        circle.setOutlineColor(sf::Color::Cyan);
                        circle.setOutlineThickness(5);
                        circle.setFillColor(sf::Color::Transparent);
                        window.draw(circle);
                    }
                }
            }

            for (int i = 0; i < max_explosion_count; i++) {
                if (se[i].life == true) {
                    if (se[i].clock.getElapsedTime().asSeconds() <= 3) {
                        window.draw(se[i].s);
                    } else se[i].life = false;
                }
            }
        }
        window.display();
    }
    delete [] soundGun;
    delete [] soundRocket;
    delete [] sb;
    delete [] sr;
    delete [] se;
    return 0;
}

int main() {
    SomePlanes();
    return 0;
}