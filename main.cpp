#include <iostream>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <list>
#include <vector>

double random(double min, double max)
{
    std::default_random_engine rand_gen = std::default_random_engine (static_cast<double>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> rand_distr = std::uniform_real_distribution<double>(min, static_cast<double>(max));
    return rand_distr(rand_gen);
}

void midpoint(std::vector<double> &vect, int left, int right, int len, double r = 1)
{
    if(right - left < 2)
        return;

    double hl = vect[left],
        hr = vect[right];
    double h = (hl+hr)/2 + random(-r*len, r*len);
    int index = floor(left + (right - left) / 2);
    vect[index]= h;
    midpoint(vect, left, index, len / 2, r);
    midpoint(vect, index, right, len / 2, r);
}

unsigned int SET_WIDTH = 800;
unsigned int SET_HEIGHT = 600;

int main(int argc, char **argv)
{
    double R = 0.6;
    if(argc >= 2)
    {
        R = atof(argv[1]);
    }

    std::cout << R << std::endl;

    int len = 200;//SET_WIDTH / 2;
    double modif = (double)SET_WIDTH/ len;
    std::cout << modif << std::endl;
    std::vector<double> vect(len);
    vect[0] = random(-(float)SET_HEIGHT/4, (float)SET_HEIGHT/4);
    vect[len - 1] = random(-(float)SET_HEIGHT/4, (float)SET_HEIGHT/4);
    midpoint(vect, 0, len - 1, len, R);


    auto *line = new sf::Vertex[len];
    for(int i = 0; i < len; i++)
    {
        std::cout << vect[i] << " ";
        line[i] = sf::Vector2f(i*modif, - vect[i]+SET_HEIGHT/2);
        if((i + 1) % 100 == 0)
            std::cout << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(SET_WIDTH,SET_HEIGHT), "Test");
    sf::RectangleShape rect(sf::Vector2f(SET_WIDTH, 1));
    rect.setPosition(0, SET_HEIGHT / 2);
    rect.setFillColor(sf::Color::Red);

    int Right = len;
    int Left = 0;
    bool Warning = true;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Left:
                            Left -= 10;
                            Right -= 10;

                            if (Left <= 0)
                            {
                                double matchh = random(-(float) SET_HEIGHT / 4, (float) SET_HEIGHT / 4);
                                for (int i = 0; i < 60 - 1; i++)
                                    vect.insert(vect.begin(), 0);
                                vect.insert(vect.begin(), matchh);
                                midpoint(vect, 0, 60, 61, R);
                                Left = 50;
                                Right = Left + len;
                            }

                            if(Warning)
                            {
                                std::cout << "Аларм! это только тестовый вариант не двигайте очень много по оси Х, это только идея такого \"перемещения\" и она затратна по памяти для больших перемещений" << std::endl;
                                Warning = false;
                            }

                            for (int i = Left, j = 0; i < Right; i++, j++)
                            {
                                line[j] = sf::Vector2f(j * modif, -vect[i] + SET_HEIGHT / 2);
                            }
                            break;

                        case sf::Keyboard::Right:
                            Left += 10;
                            Right += 10;

                            if(Right >= vect.size())
                            {
                                double match = random(-(float) SET_HEIGHT / 4, (float) SET_HEIGHT / 4);
                                for (int i = 0; i < 60 - 1; i++)
                                    vect.push_back(0);
                                vect.push_back(match);
                                midpoint(vect,  Right - 1, Right + 60, 61, R);
                            }

                            if(Warning)
                            {
                                std::cout << "Аларм! это только тестовый вариант не двигайте очень много по оси Х, это только идея такого \"перемещения\" и она затратна по памяти для больших перемещений" << std::endl;
                                Warning = false;
                            }

                            for (int i = Left, j = 0; i < Right; i++, j++)
                            {
                                line[j] = sf::Vector2f(j * modif, -vect[i] + SET_HEIGHT / 2);
                            }
                            break;
                    }
                    break;
            }
        }

        window.clear();
        window.draw(rect);
        window.draw(line, len, sf::LineStrip);
        window.display();
        sleep(1);
    }

    return 0;
}

