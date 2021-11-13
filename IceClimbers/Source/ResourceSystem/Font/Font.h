#pragma once
#include "ResourceSystem/Asset.h"
#include <SFML/Graphics.hpp>

class Font final : public Asset
{
public:
	Font(const Font& other)                = delete;
	Font(Font&& other) noexcept            = delete;
	Font& operator=(const Font& other)     = delete;
	Font& operator=(Font&& other) noexcept = delete;
	
	Font(const String& name,
	     const String& filepath);
	~Font() override;
	
	sf::Font& GetData() const;
	
	MAKE_ASSET(Font)
private:
	sf::Font* m_Data;
};