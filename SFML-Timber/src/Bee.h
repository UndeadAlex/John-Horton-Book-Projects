#ifndef BEE_H
#define BEE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bee
{
public:
	Bee(sf::RenderWindow& renderWindow, sf::Vector2f position);
	virtual ~Bee();

	void Init();
	void Update(sf::Time& deltaTime);
	void Render();

	sf::Vector2f GetPosition() const { return mSprite.getPosition(); }
	void SetPosition(const sf::Vector2f val) { mSprite.setPosition(val); }

private:
	sf::Sprite mSprite;
	float mMoveSpeed;

	sf::RenderWindow& mRenderWindow;
};

#endif // BEE_H