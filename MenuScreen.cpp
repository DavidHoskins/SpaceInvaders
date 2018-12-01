#include "MenuScreen.h"

//Constructor. 
MenuScreen:: MenuScreen()
{
	m_BackGround.setFillColor(sf::Color::Black);
	m_BackGround.setSize(sf::Vector2f(800.0f, 800.0f));

	m_spaceInvaderTexture = new sf::Texture();
	if(!m_spaceInvaderTexture->loadFromFile("Sprites/Space-Invaders-PNG-HD.png"))
	{
		std::cerr << "Error could not load spaceInvaderTexture" << std::endl;
	}

	m_spaceInvaderSprite = new sf::Sprite(*m_spaceInvaderTexture);
	m_spaceInvaderSprite->setPosition(800.0f, 400.0f);

	m_gameFont = new sf::Font();
	if(!m_gameFont->loadFromFile("Fonts/sansation.ttf"))
	{
		std::cerr << "Error could not load font file" << std::endl;
	}

	for (int i = 0; i < m_numberOfButtons; i++)
	{
		sf::Vector2f buttonPosition = sf::Vector2f(200.0f, 100.0f + (i * 150.0f));
		sf::Vector2f buttonSize = sf::Vector2f(300.0f, 100.0f);
		m_ScreenButtons[i] = new Button(m_gameFont, buttonTexts[i], m_characterSize, buttonPosition, buttonSize, sf::Color::Transparent);
	}
}

//Destructor.
MenuScreen::~MenuScreen()
{
	for(int i = 0; i < m_numberOfButtons; i++)
	{
		delete m_ScreenButtons[i];
	}
	delete m_gameFont;
	delete m_spaceInvaderSprite;
	delete m_spaceInvaderTexture;
}


//Main render update method. Rendering goes here.
void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(m_BackGround);
	for (int i = 0; i < 4; i++)
	{
		m_ScreenButtons[i]->render(window);
	}
	window.draw(*m_spaceInvaderSprite);
}

//Main update method. Logic goes here.
int MenuScreen::update(InputHandler& currentHandler, sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		if (currentHandler.mouseWithinBounds(m_ScreenButtons[i]->getPosition(), m_ScreenButtons[i]->getSize(), window))
		{
			m_ScreenButtons[i]->setHighlighted(true);
			if (currentHandler.mouseSelected(sf::Mouse::Left)) 
			{
				return i;
			}
		}
		else
		{
			m_ScreenButtons[i]->setHighlighted(false);
		}
		m_ScreenButtons[i]->update();
	}
	return -1;
}