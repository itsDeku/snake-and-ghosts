#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<time.h>
#include<cstdlib>

int Gx= 30;
int Gy= 20;
int Size=25;
int food=4,sdir,g1dir,g2dir,g3dir;
int sHelp1,sHelp2,lives=4;
int gamewidth=Gx*Size+200;
int gamehight=Gy*Size;



struct snake
{
    int x,y;
}   s[200];

struct gho
{
    int x1,y1;
    int x2,y2;
    int x3,y3;
    int x4,y4;
}   g1,g2,g3,g4;


void snake()
{


}

void ghost_dir()
{
//ghost 1
    if(g1dir==0)
        g1.y1+=1;
    if(g1dir==1)
        g1.y1-=1;
    if(g1dir==2)
        g1.x1+=1;
    if(g1dir==3)
        g1.x1-=1;


    if (g1.x1>Gx-1) g1.x1=0;  if (g1.x1<0) g1.x1=Gx-1;
    if (g1.y1>Gy-1) g1.y1=0;  if (g1.y1<0) g1.y1=Gy-1;
//ghost 2
    if(g2dir==0)
        g2.y2+=1;
    if(g2dir==1)
        g2.y2-=1;
    if(g2dir==2)
        g2.x2+=1;
    if(g2dir==3)
        g2.x2-=1;

    if (g2.x2>Gx-1) g2.x2=0;  if (g2.x2<0) g2.x2=Gx-1;
    if (g2.y2>Gy-1) g2.y2=0;  if (g2.y2<0) g2.y2=Gy-1;
//ghost 3
    if(g3dir==0)
        g3.y3+=1;
    if(g3dir==1)
        g3.y3-=1;
    if(g3dir==2)
        g3.x3+=1;
    if(g3dir==3)
        g3.x3-=1;

    if (g3.x3>Gx-1) g3.x3=0;  if (g3.x3<0) g3.x3=Gx-1;
    if (g3.y3>Gy-1) g3.y3=0;  if (g3.y3<0) g3.y3=Gy-1;

}



int main()
{

    //bools
    bool game_running=false;
    bool start_UI=true;
    bool end_UI=false;

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(Gx*25+200,Gy*25),"Ghost Busters : snake edition",sf::Style::Default);
    sf::RectangleShape scoreboard(sf::Vector2f(200.f,500.f));
    scoreboard.setPosition(sf::Vector2f(750.f,0.f));
    sf::Vector2f buttonSize(185.f,45.f);
    sf::Vector2f ST_buttonSize(230.f,60.f);
//START_UI
    sf::RectangleShape START_UI(sf::Vector2f(gamewidth,gamehight));
    sf::RectangleShape st_button1(ST_buttonSize);
    st_button1.setPosition(sf::Vector2f(335,275.f));
    st_button1.setFillColor(sf::Color::Transparent);
    sf::RectangleShape st_button2(ST_buttonSize);
    st_button2.setPosition(sf::Vector2f(335.f,375.f));
    st_button2.setFillColor(sf::Color::Transparent);


//END_UI
    sf::RectangleShape END_UI(sf::Vector2f(gamewidth,gamehight));
    sf::RectangleShape en_button1(buttonSize);
    en_button1.setPosition(sf::Vector2f(360.f,275.f));
    en_button1.setFillColor(sf::Color::Transparent);
    sf::RectangleShape en_button2(buttonSize);
    en_button2.setPosition(sf::Vector2f(360.f,350.f));
    en_button2.setFillColor(sf::Color::Transparent);

    sf::Clock clock;
    float timer=0, delay=0.1;
    sf::Clock gclock;
    float gtimer=0, gdelay=0.4;
    sf::Clock sound_clock;
    float sound_timer=0,sound_delay=0.35;
    g1.x1=5;
    g1.y1=0;
    g2.x2=10;
    g2.y2=0;
    g3.x3=15;
    g3.y3=0;
    //SOUND
    //game
    sf::SoundBuffer chomp;
    chomp.loadFromFile("data/sounds/chomp.wav");
    sf::Sound pacChomp(chomp);

    sf::SoundBuffer g_dead;
    g_dead.loadFromFile("data/sounds/eat.wav");
    sf::Sound gosDead(g_dead);
    //button
    sf::SoundBuffer seButton;
    seButton.loadFromFile("data/sounds/button.ogg");
    sf::Sound sButton(seButton);

    //SCOre
        sf::Font font;
        font.loadFromFile("data/font2.ttf");
        sf::Text score1;
        score1.setFont(font);
        score1.setCharacterSize(40);
        score1.setPosition(850.f,90.f);
        score1.setColor(sf::Color::Yellow);
        score1.setString("0");
        sf::Text score2;
        score2.setFont(font);
        score2.setCharacterSize(40);
        score2.setPosition(810.f,90.f);
        score2.setColor(sf::Color::Yellow);
        score2.setString("0");
    //start screen
        sf::Text st_text1,st_text2;
        st_text1.setFont(font);
        st_text1.setCharacterSize(40);
        st_text1.setPosition(360,280.f);
        st_text1.setColor(sf::Color::White);
        st_text1.setString("START");

        st_text2.setFont(font);
        st_text2.setCharacterSize(40);
        st_text2.setPosition(385,380.f);
        st_text2.setColor(sf::Color::White);
        st_text2.setString("EXIT");


    //game over
        sf::Text o_button1,o_button2;
        o_button1.setFont(font);
        o_button1.setCharacterSize(35);
        o_button1.setPosition(382.f,273.f);
        o_button1.setColor(sf::Color::White);
        o_button1.setString("MENU");

        o_button2.setFont(font);
        o_button2.setCharacterSize(35);
        o_button2.setPosition(400.f,352.f);
        o_button2.setColor(sf::Color::White);
        o_button2.setString("EXIT");

    //lives
        sf::Font pac;
        pac.loadFromFile("data/PAC-FONT.ttf");
        sf::Text Live1,Live2,Live3;
        Live1.setFont(pac);
        Live1.setCharacterSize(25);
        Live1.setPosition(810.f,300.f);
        Live1.setColor(sf::Color::Yellow);
        Live1.setString("1");

        Live2.setFont(pac);
        Live2.setCharacterSize(25);
        Live2.setPosition(840.f,300.f);
        Live2.setColor(sf::Color::Yellow);
        Live2.setString("1");

        Live3.setFont(pac);
        Live3.setCharacterSize(25);
        Live3.setPosition(870.f,300.f);
        Live3.setColor(sf::Color::Yellow);
        Live3.setString("1");




    //TEXture
        sf::Texture bac,score;
        score.loadFromFile("data/score.jpg");
        bac.loadFromFile("data/backgd.png");
        sf::Sprite sprite1(bac);
        scoreboard.setTexture(&score);
    //START_UI
        sf::Texture st_UI;
        st_UI.loadFromFile("data/start_back.jpg");
        START_UI.setTexture(&st_UI);
    //END_UI
        sf::Texture en_UI;
        en_UI.loadFromFile("data/end_back.jpg");
        END_UI.setTexture(&en_UI);


    //GHOST TEXTURE
        //ghost 1
        sf::Texture g1up,g1down,g1left,g1right;
        g1up.loadFromFile("data/ghost1/g1up.jpg");
        g1down.loadFromFile("data/ghost1/g1down.jpg");
        g1left.loadFromFile("data/ghost1/g1left.jpg");
        g1right.loadFromFile("data/ghost1/g1right.jpg");

        sf::Sprite spg1up(g1up);
        sf::Sprite spg1down(g1down);
        sf::Sprite spg1left(g1left);
        sf::Sprite spg1right(g1right);
        sf::Sprite ghost1_sprite;

        //ghost 2
        sf::Texture g2up,g2down,g2left,g2right;
        g2up.loadFromFile("data/ghost2/g2up.jpg");
        g2down.loadFromFile("data/ghost2/g2down.jpg");
        g2left.loadFromFile("data/ghost2/g2left.jpg");
        g2right.loadFromFile("data/ghost2/g2right.jpg");

        sf::Sprite spg2up(g2up);
        sf::Sprite spg2down(g2down);
        sf::Sprite spg2left(g2left);
        sf::Sprite spg2right(g2right);
        sf::Sprite ghost2_sprite;

        //ghost 3
        sf::Texture g3up,g3down,g3left,g3right;
        g3up.loadFromFile("data/ghost3/g3up.jpg");
        g3down.loadFromFile("data/ghost3/g3down.jpg");
        g3left.loadFromFile("data/ghost3/g3left.jpg");
        g3right.loadFromFile("data/ghost3/g3right.jpg");

        sf::Sprite spg3up(g3up);
        sf::Sprite spg3down(g3down);
        sf::Sprite spg3left(g3left);
        sf::Sprite spg3right(g3right);
        sf::Sprite ghost3_sprite;

        //snake texture
        sf::Texture sup,sdown,sleft,sright,sbody;
        sup.loadFromFile("data/snake/sup.jpeg");
        sdown.loadFromFile("data/snake/sdown.jpeg");
        sleft.loadFromFile("data/snake/sleft.jpeg");
        sright.loadFromFile("data/snake/sright.jpeg");
        sbody.loadFromFile("data/snake/sbody.jpeg");

        sf::Sprite spup(sup);
        sf::Sprite spdown(sdown);
        sf::Sprite spleft(sleft);
        sf::Sprite spright(sright);
        sf::Sprite spbody(sbody);
        sf::Sprite snake_sprite;




    while (window.isOpen())
    {

        sf::Event event;
        while(window.pollEvent(event))
        {
            if((event.type==event.Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
                window.close();
            if((event.type == sf::Event::KeyPressed) &&(event.key.code == sf::Keyboard::Space))
            {
                start_UI=false;
                end_UI=false;
                game_running=true;
            }
        }
    if(start_UI)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(st_button1.getPosition().x + ST_buttonSize.x > float(mousepos.x) &&
               st_button1.getPosition().x < float(mousepos.x) &&
               st_button1.getPosition().y + ST_buttonSize.y > float(mousepos.y) &&
               st_button1.getPosition().y < float(mousepos.y))
               {
                   sButton.play();
                   sf::sleep(sf::seconds(0.2));
                   lives=4;
                   Live1.setString("1");
                   Live2.setString("1");
                   Live3.setString("1");
                   start_UI=false;
                   game_running=true;
               }
            }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(st_button2.getPosition().x + ST_buttonSize.x > float(mousepos.x) &&
               st_button2.getPosition().x < float(mousepos.x) &&
               st_button2.getPosition().y + ST_buttonSize.y > float(mousepos.y) &&
               st_button2.getPosition().y < float(mousepos.y))
               {
                   sButton.play();
                   sf::sleep(sf::seconds(0.2));
                   window.close();
               }
            }
    }

    if(end_UI)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(en_button1.getPosition().x + buttonSize.x > float(mousepos.x) &&
               en_button1.getPosition().x < float(mousepos.x) &&
               en_button1.getPosition().y + buttonSize.y > float(mousepos.y) &&
               en_button1.getPosition().y < float(mousepos.y))
               {
                   sButton.play();
                   sf::sleep(sf::seconds(0.2));
                   end_UI=false;
                   start_UI=true;
               }
            }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            if(en_button2.getPosition().x + buttonSize.x > float(mousepos.x) &&
               en_button2.getPosition().x < float(mousepos.x) &&
               en_button2.getPosition().y + buttonSize.y > float(mousepos.y) &&
               en_button2.getPosition().y < float(mousepos.y))
               {
                    sButton.play();
                    sf::sleep(sf::seconds(0.2));
                    window.close();
               }
            }

            }

    if(game_running)
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        gclock.restart();
        sound_clock.restart();
        timer+=time;
        gtimer+=time;
        sound_timer+=time;


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            if(sdir!=1)  sdir=0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            if(sdir!=0)  sdir=1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if(sdir!=3)  sdir=2;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if(sdir!=2)  sdir=3;
//ghosts movement
        int g1mov;
	    g1mov=rand()%20;
        int g2mov;
        g2mov=rand()%20;
        int g3mov;
        g3mov=rand()%20;
//for ghost 1
        if(g1mov==0)
            g1dir=0;
        if(g1mov==1)
            g1dir=1;
        if(g1mov==2)
            g1dir=2;
        if(g1mov==3)
            g1dir=3;

//for ghost 2
        if(g2mov==0)
            g2dir=0;
        if(g2mov==1)
            g2dir=1;
        if(g2mov==2)
            g2dir=2;
        if(g2mov==3)
            g2dir=3;
//for ghost 3
        if(g3mov==0)
            g3dir=0;
        if(g3mov==1)
            g3dir=1;
        if(g3mov==2)
            g3dir=2;
        if(g3mov==3)
            g3dir=3;
//sound timer
        if(sound_timer>sound_delay)
        {
            sound_timer=0;
            pacChomp.play();

        }
//snake timer
        if(timer>delay)
        {
            timer=0;
            for(int i=food;i>0;i--)
            {
                s[i].x=s[i-1].x;
                s[i].y=s[i-1].y;
            }
            if(sdir==0)
                s[0].y+=1;
            if(sdir==1)
                s[0].y-=1;
            if(sdir==2)
                s[0].x+=1;
            if(sdir==3)
                s[0].x-=1;
//collision with g1

        if((s[0].x==g1.x1) && (s[0].y==g1.y1))
        {

            gosDead.play();
            food++;
            gdelay-=0.005;
            sHelp1++;
            if(sHelp1>=9)
            {
                sHelp2+=1;
                sHelp1=0;
            }
            g1.x1=30;
            g1.y1=0;
        }
    //snake colision with wall
        if (s[0].x>Gx-1)
        {
            s[0].x=1;
            s[0].y=0;
            lives-=1;
            sdir=0;
        }
        if (s[0].x<0)
        {
            s[0].x=1;
            s[0].y=0;
            lives-=1;
            sdir=0;
        }
        if (s[0].y>Gy-1)
        {
            s[0].x=1;
            s[0].y=0;
            lives-=1;
            sdir=0;
        }
        if (s[0].y<0)
        {
            s[0].x=1;
            s[0].y=0;
            lives-=1;
            sdir=0;
        }
//collision with g2

        if((s[0].x==g2.x2) && (s[0].y==g2.y2))
        {
            gosDead.play();
            food++;
            gdelay-=0.005;
            sHelp1++;
            if(sHelp1>=9)
            {
                sHelp2+=1;
                sHelp1=0;
            }
            g2.x2=10;
            g2.y2=0;
        }
        if (s[0].x>Gx-1) s[0].x=0;  if (s[0].x<0) s[0].x=Gx-1;
        if (s[0].y>Gy-1) s[0].y=0;  if (s[0].y<0) s[0].y=Gy-1;
//collision with g3
        if((s[0].x==g3.x3) && (s[0].y==g3.y3))
        {
            gosDead.play();
            food++;
            gdelay-=0.005;
            sHelp1++;
            if(sHelp1>9)
            {
                sHelp2+=1;
                sHelp1=0;
            }
            g3.x3=20;
            g3.y3=0;
        }
        if (s[0].x>Gx-1) s[0].x=0;  if (s[0].x<0) s[0].x=Gx-1;
        if (s[0].y>Gy-1) s[0].y=0;  if (s[0].y<0) s[0].y=Gy-1;
    }
    //score for 10digit
        if(sHelp1==0)
            score1.setString("0");
        if(sHelp1==1)
            score1.setString("1");
        if(sHelp1==2)
            score1.setString("2");
        if(sHelp1==3)
            score1.setString("3");
        if(sHelp1==4)
            score1.setString("4");
        if(sHelp1==5)
            score1.setString("5");
        if(sHelp1==6)
            score1.setString("6");
        if(sHelp1==7)
            score1.setString("7");
        if(sHelp1==8)
            score1.setString("8");
        if(sHelp1==9)
            score1.setString("9");
    //score2 the 100digits
        if(sHelp2==0)
            score2.setString("0");
        if(sHelp2==1)
            score2.setString("1");
        if(sHelp2==2)
            score2.setString("2");
        if(sHelp2==3)
            score2.setString("3");
        if(sHelp2==4)
            score2.setString("4");
        if(sHelp2==5)
            score2.setString("5");
        if(sHelp2==6)
            score2.setString("6");
        if(sHelp2==7)
            score2.setString("7");
        if(sHelp2==8)
            score2.setString("8");
        if(sHelp2==9)
            score2.setString("9");

    //lives
        if(lives==4)
            Live3.setString("1");
        if(lives==3)
            Live3.setString("0");
        if(lives==2)
            Live2.setString("0");
        if(lives==1)
            Live1.setString("0");
        if(lives==0)
        {
            game_running=false;
            end_UI=true;
        }


//ghost timer
        if(gtimer>gdelay)
        {
            gtimer=0;
            ghost_dir();
        }
    }
    window.clear();
    if(game_running)
    {
//CHANGING Ghosts sprite
    //ghost 1
        if(g1dir==0)
            ghost1_sprite=spg1down;
        if(g1dir==1)
            ghost1_sprite=spg1up;
        if(g1dir==2)
            ghost1_sprite=spg1right;
        if(g1dir==3)
            ghost1_sprite=spg1left;
    //ghost 2
        if(g2dir==0)
            ghost2_sprite=spg2down;
        if(g2dir==1)
            ghost2_sprite=spg2up;
        if(g2dir==2)
            ghost2_sprite=spg2right;
        if(g2dir==3)
            ghost2_sprite=spg2left;
    //ghost 3
        if(g3dir==0)
            ghost3_sprite=spg3down;
        if(g3dir==1)
            ghost3_sprite=spg3up;
        if(g3dir==2)
            ghost3_sprite=spg3right;
        if(g3dir==3)
            ghost3_sprite=spg3left;

//changing snake sprite
        if(sdir==0)
            snake_sprite=spdown;
        if(sdir==1)
            snake_sprite=spup;
        if(sdir==2)
            snake_sprite=spright;
        if(sdir==3)
            snake_sprite=spleft;



        for(int i=0;i<Gx;i++)
            for(int j=0;j<Gy;j++)
            {
                sprite1.setPosition(i*Size,j*Size);
                window.draw(sprite1);
            }
        window.draw(scoreboard);
        window.draw(score1);
        window.draw(score2);
        window.draw(Live1);
        window.draw(Live2);
        window.draw(Live3);
        for(int i=1;i<food;i++)
        {
            spbody.setPosition(s[i].x*Size,s[i].y*Size);
            window.draw(spbody);
        }
        snake_sprite.setPosition(s[0].x*Size,s[0].y*Size);
        window.draw(snake_sprite);
        ghost1_sprite.setPosition(g1.x1*Size,g1.y1*Size);
        window.draw(ghost1_sprite);
        ghost2_sprite.setPosition(g2.x2*Size,g2.y2*Size);
        window.draw(ghost2_sprite);
        ghost3_sprite.setPosition(g3.x3*Size,g3.y3*Size);
        window.draw(ghost3_sprite);

    }
    if(start_UI)
    {
        window.draw(START_UI);
        window.draw(st_button1);
        window.draw(st_button2);
        window.draw(st_text1);
        window.draw(st_text2);
    }
    if(end_UI)
    {
        window.draw(END_UI);
        window.draw(en_button1);
        window.draw(en_button2);
        window.draw(o_button1);
        window.draw(o_button2);

    }
        window.display();
    }

}
