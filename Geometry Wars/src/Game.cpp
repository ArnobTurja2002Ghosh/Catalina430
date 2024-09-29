///\/\/\\\/\/\//\\///\//\\\///////\/\/\\\/\/\//\\///\//\\\//////
//
//  Assignment       COMP4300 - Assignment 2
//  Professor:       David Churchill
//  Year / Term:     2024-09
//  File Name:       Game.cpp
// 
//  Student Name:    Arnob Ghosh
//  Student User:    arnobg
//  Student Email:   arnobg@mun.ca
//  Student ID:      202136073
//  Group Member(s): [enter student name(s)]
//
///\/\/\\\/\/\//\\///\//\\\///////\/\/\\\/\/\//\\///\//\\\//////
        
#include "Game.h"

#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

Game::Game(const std::string & config)
{ 
    init(config);
}

void Game::init(const std::string & path)
{
    // TODO: read in config file here
    //       use the premade PlayerConfig, EnemyConfig, BulletConfig variables

    // set up default window parameters

	//Makes sure to change the rand seed so it doesnt spawn the same as the last games
	srand(time(0)); std::cout << time(0) << '\t' << time << '\t' << RAND_MAX << '\n';

	//To be implemented if I need
	//m_backgroundTexture.loadFromFile("art/ezgif-2-76dec4f055.jpg");
	//m_backgroundSprite.setTexture(m_backgroundTexture);
	//m_backgroundSprite.setPosition(sf::Vector2f(0, 0));

	//Read in the config file 
	std::fstream input{ path };

	if (!input.is_open())
	{
		std::cout << "Failed to open: " << path << '\n';
		exit(-1);
	}



	std::string identifier{};
	while (input >> identifier)
	{
		if (identifier == "Window")
		{
			unsigned int width{};
			input >> width;

			unsigned int height{};
			input >> height;

			int frameLimit{};
			input >> frameLimit;

			int fullScreen{};
			input >> fullScreen;
			if (fullScreen == 0)
			{
				m_window.create(sf::VideoMode(width, height), "Geometry Wars", sf::Style::Close);
				m_window.setFramerateLimit(frameLimit);
			}
			else if (fullScreen == 1)
			{
				auto fullscreenMode{ sf::VideoMode::getFullscreenModes() };
				//fullscreenMode[0] is the most compatible mode for fullscreen on this device
				m_window.create(fullscreenMode[0], "Geometry Wars", sf::Style::Fullscreen);
				m_window.setFramerateLimit(frameLimit);
			}
		}
		else if (identifier == "Font")
		{
			std::string filepath{};
			input >> filepath;
			if (!m_font.loadFromFile(filepath))
			{
				std::cerr << "Failed to load font. Filepath: " << filepath;
			}

			//m_scoreText.setFont(m_font);

			int fontSize{};
			input >> fontSize;
			//m_scoreText.setCharacterSize(fontSize);

			sf::Vector3<sf::Uint16> RGB{};
			input >> RGB.x;
			input >> RGB.y;
			input >> RGB.z;
			//m_scoreText.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
		}
		else if (identifier == "Player")
		{
			int shapeRadius{};
			input >> shapeRadius;
			m_playerConfig.SR = shapeRadius;

			int collisionRadius{};
			input >> collisionRadius;
			m_playerConfig.CR = collisionRadius;

			float speed{};
			input >> speed;
			m_playerConfig.S = speed;

			sf::Vector3<sf::Uint16> fillColor{};
			input >> fillColor.x;
			input >> fillColor.y;
			input >> fillColor.z;
			m_playerConfig.FR = fillColor.x;
			m_playerConfig.FG = fillColor.y;
			m_playerConfig.FB = fillColor.z;

			sf::Vector3<sf::Uint16> outlineColor{};
			input >> outlineColor.x;
			input >> outlineColor.y;
			input >> outlineColor.z;
			m_playerConfig.OR = outlineColor.x;
			m_playerConfig.OG = outlineColor.y;
			m_playerConfig.OB = outlineColor.z;

			int outlineThickness{};
			input >> outlineThickness;
			m_playerConfig.OT = outlineThickness;

			int vertices{};
			input >> vertices;
			m_playerConfig.V = vertices;
		}
		else if (identifier == "Enemy")
		{
			int shapeRadius;
			input >> shapeRadius;
			m_enemyConfig.SR = shapeRadius;

			int collisionRadius;
			input >> collisionRadius;
			m_enemyConfig.CR = collisionRadius;

			float minSpeed;
			input >> minSpeed;
			m_enemyConfig.SMIN = minSpeed;

			float maxSpeed;
			input >> maxSpeed;
			m_enemyConfig.SMAX = maxSpeed;

			sf::Vector3<sf::Uint16> outlineColor;
			input >> outlineColor.x;
			input >> outlineColor.y;
			input >> outlineColor.z;
			m_enemyConfig.OR = outlineColor.x;
			m_enemyConfig.OG = outlineColor.y;
			m_enemyConfig.OB = outlineColor.z;

			int outlineThickness;
			input >> outlineThickness;
			m_enemyConfig.OT = outlineThickness;

			int minVertices;
			input >> minVertices;
			m_enemyConfig.VMIN = minVertices;

			int maxVertices;
			input >> maxVertices;
			m_enemyConfig.VMAX = maxVertices;

			int smallLifespan;
			input >> smallLifespan;
			m_enemyConfig.L = smallLifespan;

			int spawnInterval;
			input >> spawnInterval;
			m_enemyConfig.SI = spawnInterval;
		}
		else if (identifier == "Bullet")
		{
			int shapeRadius{};
			input >> shapeRadius;
			m_bulletConfig.SR = shapeRadius;

			int collisionRadius{};
			input >> collisionRadius;
			m_bulletConfig.CR = collisionRadius;

			float speed{};
			input >> speed;
			m_bulletConfig.S = speed;

			sf::Vector3<sf::Uint16> fillColor{};
			input >> fillColor.x;
			input >> fillColor.y;
			input >> fillColor.z;
			m_bulletConfig.FR = fillColor.x;
			m_bulletConfig.FG = fillColor.y;
			m_bulletConfig.FB = fillColor.z;

			sf::Vector3<sf::Uint16> outlineColor{};
			input >> outlineColor.x;
			input >> outlineColor.y;
			input >> outlineColor.z;
			m_bulletConfig.OR = outlineColor.x;
			m_bulletConfig.OG = outlineColor.y;
			m_bulletConfig.OB = outlineColor.z;

			int outlineThickness{};
			input >> outlineThickness;
			m_bulletConfig.OT = outlineThickness;

			int shapeVertices{};
			input >> shapeVertices;
			m_bulletConfig.V = shapeVertices;

			int lifespan{};
			input >> lifespan;
			m_bulletConfig.L = lifespan;

			//int specialBulletAmount{};
			//input >> specialBulletAmount;
			//m_bulletConfig.SB = specialBulletAmount;
		}
	}

	//m_scoreText.setPosition(0, 0);
	//m_scoreText.setString(std::to_string(m_score));

	spawnPlayer();
	std::cout << m_player->id() << "player id";


        
    ImGui::SFML::Init(m_window);

    // scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

}

std::shared_ptr<Entity> Game::player()
{
    return m_entities.getEntities("player").back();
}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems should function while paused (rendering)
    //       some systems shouldn't (movement / input)
    while (m_running)
    {
        // update the entity manager
        m_entities.update();
        
        // required update call to imgui
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sGUI();
        sRender();
        
        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{
    // TODO
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config
        
    // We create every entity by calling EntityManager.addEntity(tag)
    // This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
    auto entity = m_entities.addEntity("player");

    auto middleWindowPos = Vec2f(m_window.getSize().x * 0.5, m_window.getSize().y * 0.5 );

    entity->add<CTransform>(middleWindowPos, Vec2f(0, 0), 0.0f);

    entity->add<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG,
        m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
    
    //Give the entity an collision component
    entity->add<CCollision>(m_playerConfig.CR);

    //Add an input component to take the player's input
    entity->add<CInput>();

    //This goes slightly against the EntityManagers paradigm, but we use the player so much, it's worth it
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //       the enemy must be spawned completely within the bounds of the window
    //
    
    // record when the most recent enemy was spawned
	auto e = m_entities.addEntity("enemy");

	int minPosX= m_enemyConfig.CR ;
	int maxPosX=static_cast<int>(m_window.getSize().x - m_enemyConfig.CR) ;

	int minPosY= m_enemyConfig.CR ;
	int maxPosY= static_cast<int>(m_window.getSize().y - m_enemyConfig.CR) ;

	Vec2f randPos=Vec2f(static_cast<float>(minPosX + (rand() % (maxPosX - minPosX + 1))),
		static_cast<float>(minPosY + (rand() % (maxPosY - minPosY + 1))));

	////Randomize the speed of the enemy and checks if (0) true->redo
	float randSpeed = static_cast<float>(m_enemyConfig.SMIN + rand() % static_cast<int>((m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1)));
	float randAngle = 2*M_PI * (static_cast<float>(rand())/RAND_MAX);
	auto randVelocity = Vec2f(std::cos(randAngle), std::sin(randAngle)) * randSpeed;

	std::cout << randAngle<<"        " <<rand()<< "           " << RAND_MAX << '\n';
	////Makes sure the velocity is not 0
	while (randSpeed == 0)
	{
		randSpeed = m_enemyConfig.SMIN + rand() % static_cast<int>((m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1));
	}

	////Gives the entity the random position on the screen 
	e->add<CTransform>(randPos, randVelocity, 0.0f);


	int vertices=m_enemyConfig.VMIN + (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1)) ;
	
	sf::Color fillColor=
		sf::Color(static_cast<sf::Uint8>(rand() % (1 + 255)),
		static_cast<sf::Uint8>(rand() % (1 + 255)),
		static_cast<sf::Uint8>(rand() % (1 + 255)));

	sf::Color outlineColor=
	sf::Color(
		static_cast<sf::Uint8>(m_enemyConfig.OR),
		static_cast<sf::Uint8>(m_enemyConfig.OG),
		static_cast<sf::Uint8>(m_enemyConfig.OB)
	);

	int outlineThickness=m_enemyConfig.OT ;

	e->add<CShape>(m_enemyConfig.SR, vertices, fillColor, outlineColor, outlineThickness);

	e->add<CCollision>(m_enemyConfig.CR);

	//Record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

// spawns the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO: spawn small enemies at the location of the input enemy e
        
    // when we create the smaller enemy, we have to read the values of the original enemy
    // - spawn a number of small enemies equal to the vertices of the original enemy
    // - set each small enemy to the same color as the original, half the size
    // - small enemies are worth double points of the original enemy
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f & target)
{
    // TODO: implement the spawning of a bullet which travels toward target
    //       - bullet speed is given as a scalar speed
    //       - you must set the velocity by using formula in notes
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO: implement your own special weapon
}
        
void Game::sMovement()
{
    // TODO: implement all entity movement in this function
    //       you should read the m_player->cInput component to determine if the player is moving

    // Sample movement speed update for the player
	Vec2f playerVelocity;
	if (m_player->get<CInput>().left)
	{
		playerVelocity.x -= m_playerConfig.S;
	}
	if (m_player->get<CInput>().right)
	{
		playerVelocity.x += m_playerConfig.S;
	}
	if (m_player->get<CInput>().up)
	{
		playerVelocity.y -= m_playerConfig.S;
	}
	if (m_player->get<CInput>().down)
	{
		playerVelocity.y += m_playerConfig.S;
	}
	m_player->get<CTransform>().velocity = playerVelocity;
	for (auto e : m_entities.getEntities())
	{
		if (e->has<CTransform>())
		{
			e->get<CTransform>().pos += e->get<CTransform>().velocity;
		}
	}
}
        
void Game::sLifespan()
{
    // TODO: implement all lifespan functionality
    // 
    // for all entities
    //     if entity has no lifespan component, skip it
    //     if entity has > 0 remaining lifespan, subtract 1
    //     if it has lifespan and is alive
    //         scale its alpha channel properly
    //     if it has lifespan and its time is up
    //         destroy the entity
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities
    //       be sure to use the collision radius, NOT the shape radius
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
	if ((m_currentFrame - m_lastEnemySpawnTime) >= m_enemyConfig.SI)
	{
		spawnEnemy();
	}
}

void Game::sGUI()
{
    ImGui::Begin("Geometry Wars");

    ImGui::Text("Stuff Goes Here");

    ImGui::End();
}

void Game::sRender()
{
	m_window.clear();

	//m_window.draw(m_backgroundSprite);

	for (auto e : m_entities.getEntities())
	{
		e->get<CShape>().circle.setPosition(e->get<CTransform>().pos.x, e->get<CTransform>().pos.y);
		e->get<CTransform>().angle += 1.0f;
		e->get<CShape>().circle.setRotation(e->get<CTransform>().angle);
		m_window.draw(e->get<CShape>().circle);
	}
	//m_window.draw(m_scoreText);


	ImGui::SFML::Render(m_window);

	m_window.display();
    
}

void Game::sUserInput()
{
    // TODO: handle user input here
    //       note that you should only be setting the player's input component variables here
    //       you should not implement the player's movement logic here
    //       the movement system will read the variables you set in this function
        
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // pass the event to imgui to be parsed
        ImGui::SFML::ProcessEvent(m_window, event);

        // this event triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        // this event is triggered when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Pressed\n";
                // TODO: set player's input component "up" to true
                break;
            default: break;
            }
        }
        
        // this event is triggered when a key is released
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Released\n";
                // TODO: set player's input component "up" to false
                break;
            default: break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // this line ignores mouse events if ImGui is the thing being clicked
            if (ImGui::GetIO().WantCaptureMouse) { continue; }

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
                // call spawnBullet here
            }
        
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
                // call spawnSpecialWeapon here
            }
        }
    }
}

// Copyright (C) David Churchill - All Rights Reserved
// COMP4300 - 2024-09 - Assignment 2
// Written by David Churchill (dave.churchill@gmail.com)
// Unauthorized copying of these files are strictly prohibited
// Distributed only for course work at Memorial University
// If you see this file online please contact email above
