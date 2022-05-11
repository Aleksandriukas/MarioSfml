#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


float offsetX = 0, offsetY = 0;


const int H = 26;
const int W = 150;
bool win = false;

String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0                                                                                                                                f                   0",
"0                                                                                                        kkkkkk                                      0",
"0                                                                                                                                                    0",
"0                                                                                    w  kkkkk  kk  kkk              kkkkkk                           0",
"0                   w                                  w                   w                                                        a                0",
"0                                      w                                       kkkkkk                                               a                0",
"0                     c                                                      kk                                                 kkkkkkkk             0",
"0                                                                                                                                                    0", 
"0                                                                       rr                                                                           0",
"0                                                                      rrr                                                                           0",
"0                                                                     rrrr                                                                           0",
"0               k    kkkkk                                           rrrrr                                                                           0",
"0                                      t0                           rrrrrr                                                                           0",
"0G                                     00              t0          rrrrrrr                                                                          r0",
"0           d    g       d             00              00         rrrrrrrr        d               d                  d          d                   r0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP  PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP  PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP  PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777",
};





class baseForObject {
public:

	float dx, dy;
	int x, y;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	bool life;



};



class PLAYER: public baseForObject {

public:
	bool immortal = false;

	PLAYER(Texture& image,int x1,int y1)
	{
		sprite.setTexture(image);
		rect = FloatRect(x1, y1, 16, 16);

		dx = 0.1;
		dy = 0.1;
		currentFrame = 0;
		life = true;
	}


	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);


		if (!onGround)
			dy = dy + 0.0005 * time;

		rect.top += dy * time;
		onGround = false;
		Collision(1);


		currentFrame += time * 0.005;
		if (currentFrame > 3) currentFrame -= 3;


		if (dx > 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		if (dx < 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}


	void Collision(int num)
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't') || (TileMap[i][j] == 'a') || (TileMap[i][j] == 'c') || (TileMap[i][j] == '7'))
				{


					if (TileMap[i][j] == '7')
					{
						life = false;
					}

					if (TileMap[i][j] == 'a') {
						win = true;
					}
					
					if (TileMap[i][j] == 'c') {
						TileMap[i][j] = ' ';
						immortal = true;
						
					}

					
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;   dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
					

				}


				
			}

	}

};



class ENEMY: public baseForObject
{

public:
	

	void set(Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();


		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r'))
				{
					if (dx > 0)
					{
						rect.left = j * 16 - rect.width; dx *= -1;
					}
					 else if (dx < 0)
					{
						rect.left = j * 16 + 16;  dx *= -1;
					}

				}
	}

};



int main()
{
restart:
	offsetX = 0, offsetY = 0;
	win = false;
	RenderWindow window(VideoMode(600, 400), "SFML works!");

	Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");


	PLAYER Mario(tileSet,50,19*16);
	ENEMY  enemy1;
	ENEMY enemy2;
	ENEMY enemy3;
	enemy1.set(tileSet, 54 * 16, 21 * 16);
	enemy2.set(tileSet, 60 * 16, 21 * 16);
	enemy3.set(tileSet, 80 * 16, 21 * 16);
	Sprite tile(tileSet);

	
	int counter = 10;

	CircleShape octagon(20, 4);
	octagon.setPosition(10.f, 30.f);
	octagon.setFillColor(Color::Red);
	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))   
			Mario.dx = -0.1;

		if (Keyboard::isKeyPressed(Keyboard::Right))  
			Mario.dx = 0.1;

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (Mario.onGround)
			{ Mario.dy = -0.27; Mario.onGround = false; }
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) 
			exit(0);
		if (Keyboard::isKeyPressed(Keyboard::R))
			goto restart;
			
		

		
		Mario.update(time);
		enemy1.update(time);
		enemy2.update(time);
		enemy3.update(time);

		if (Mario.rect.intersects(enemy1.rect))
		{
			if (enemy1.life	) {
				if (Mario.dy > 0) { enemy1.dx = 0; Mario.dy = -0.2; enemy1.life = false; }
				else if(!Mario.immortal)
					Mario.life=false;
			}
		}
		if (Mario.rect.intersects(enemy2.rect))
		{
			if (enemy2.life ) {
				if (Mario.dy > 0) { enemy2.dx = 0; Mario.dy = -0.2; enemy2.life = false; }
				else if(!Mario.immortal)
					Mario.life = false;
			}
		}
		if (Mario.rect.intersects(enemy3.rect))
		{
			if (enemy3.life) {
				if (Mario.dy > 0) { enemy3.dx = 0; Mario.dy = -0.2; enemy3.life = false; }
				else if (!Mario.immortal)
					Mario.life = false;
			}
		}


		if (Mario.rect.left > 200) offsetX = Mario.rect.left - 200;           //смещение




		window.clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(95, 112, 16, 16));

				if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(127, 112, 16, 16));

				if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 47, 32, 48));

				if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 139, 48, 37));

				if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(145, 222, 77, 33));

				if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 106, 74, 21));

				if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 41, 31));

				if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(111, 112, 16, 16));

				if (TileMap[i][j] == 'f') tile.setTextureRect(IntRect(94, 6, 107, 106));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'a') ) continue;

				//std::cout << win;
				tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
				window.draw(tile);
			}
		}

		if (Mario.immortal)
			window.draw(octagon);

		
		window.draw(Mario.sprite);
		window.draw(enemy1.sprite);
		window.draw(enemy2.sprite);
		window.draw(enemy3.sprite);

		window.display();

		

		if (win || !Mario.life) 
			break;
		
	}

	Font open_sans;
	open_sans.loadFromFile("arial.ttf");
	Text text;
	text.setFont(open_sans);
	
	text.setCharacterSize(32);
	
	if (win) {
		text.setString("Winner");
		while (true) {
			if (Keyboard::isKeyPressed(Keyboard::Q))
				exit(0);
			if (Keyboard::isKeyPressed(Keyboard::R))
				goto restart;
			window.clear(Color(107, 140, 255));
			window.draw(text);
			window.display();
		}
	}
	if (!Mario.life) {
		text.setString("Looser");
		while (true) {
			if (Keyboard::isKeyPressed(Keyboard::Q))
				exit(0);
			if (Keyboard::isKeyPressed(Keyboard::R))
				goto restart;
			window.clear(Color(107, 140, 255));
			window.draw(text);
			window.display();
		}

	}
	return 0;
}


