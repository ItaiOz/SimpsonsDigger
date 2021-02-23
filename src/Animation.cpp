#include "..\include\Animation.h"

Animation::Animation(sf::Texture texture, sf::Vector2u imageCount, float switchTime)
	:m_imageCount(imageCount), m_switchTime(switchTime)
{
	m_totalTime = 0;
	m_currentImage.x = 0;

	uvRect.width = texture.getSize().x / (float)imageCount.x;
	uvRect.height = texture.getSize().y / (float)imageCount.y;

}

Animation::~Animation()
{
}

void Animation::setAnimation(int row, float deltaTime)
{
		m_currentImage.y = row;

		m_totalTime += deltaTime;

//		animationCounter += clock.restart().asMilliseconds();
		if (m_totalTime >= m_switchTime)
		{
			m_totalTime -= m_switchTime;
			m_currentImage.x++;

			if (m_currentImage.x >= m_imageCount.x)
				m_currentImage.x = 5;
		}

		uvRect.left = m_currentImage.x * uvRect.width;
		uvRect.top = m_currentImage.y * uvRect.height;
		//if (source.x * 48 >= 48 * 3)
		//	source.x = 0;
		//m_image.setTextureRect(sf::IntRect(source.x * 48, source.y * 48, 48, 48));
	
}
