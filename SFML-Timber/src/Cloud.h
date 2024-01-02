#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Cloud
{
public:
	Cloud(sf::RenderWindow& renderWindow, sf::Vector2f position);
	virtual ~Cloud();

	void Init();
	void Update(sf::Time& deltaTime);
	void Render();

	sf::Vector2f GetPosition() const { return mSprite.getPosition(); }
	void SetPosition(const sf::Vector2f val) { mSprite.setPosition(val); }

private:
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	float mMoveSpeed;

	sf::RenderWindow& mRenderWindow;
};

#endif // CLOUD_H