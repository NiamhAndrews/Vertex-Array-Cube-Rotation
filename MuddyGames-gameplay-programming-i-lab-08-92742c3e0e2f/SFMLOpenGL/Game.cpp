#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}


// Vertices for one Triangle
float vertices[]
{ 
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
};



// Colors for those vertices
float colors[]
{ 
	1.0f, 0.3f, 0.0f,
	0.6f, 0.0f, 0.0f,
	0.7f, 0.0f, 0.5f,
	0.0f, 9.0f, 9.0f,
	0.0f, 0.5f, 0.5f,
	0.4f, 1.0f, 0.0f,
	0.7f, 0.4f, 0.0f,
	0.1f, 0.6f, 0.3f,
};


// Index to be drawn
unsigned int vertex_index[]
{ 
	0, 1, 2,
	2, 3, 0,
	3, 7, 4,
	4, 0, 3,
	4, 7, 6,
	6, 5, 4,
	6, 2, 1,
	1, 5, 6,
	6, 7, 3,
	3, 2, 6,
	0, 4, 5,
	5, 1, 0
};



void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f / 60.0f)
	{
		clock.restart();




		//Rotate Right
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };
				vector = Matrix3::RotationY(0.8) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
		//Rotate Left
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };
				vector = Matrix3::RotationY(-0.8) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
		//Rotate Up
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };
				vector = Matrix3::RotationX(0.8) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
		//Rotate Down
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };
				vector = Matrix3::RotationX(-0.8) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}



		//Increase Scale
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3  vector{ vertices[i], vertices[i + 1], vertices[i + 2] };

				vector = Matrix3::Scale3D(110.0f) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}
		//Decrease Scale
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };

				vector = Matrix3::Scale3D(90.0f) * vector;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
				vertices[i + 2] = vector.z;
			}
		}



		//Translate +
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Period)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };
				
				float tempZ = vector.z;
				vector.z = 1;
				vector = Matrix3::Translate(0.05f, 0.05f) * vector;
				vector.z = tempZ;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
			}
		}

		//Translate -
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)))
		{
			for (int i = 0; i < 24; i += 3)
			{
				Vector3 vector{ vertices[i], vertices[i + 1], vertices[i + 2] };

				float tempZ = vector.z;
				vector.z = 1;
				vector = Matrix3::Translate(-0.05f, -0.05f) * vector;
				vector.z = tempZ;
				vertices[i] = vector.x;
				vertices[i + 1] = vector.y;
			}
		}







		std::cout << "Update up" << std::endl;
	}

}

void Game::render()
{
	std::cout << "Drawing" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}

