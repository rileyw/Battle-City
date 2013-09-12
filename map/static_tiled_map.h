#pragma once
#ifndef _STATIC_TILED
#define _STATIC_TILED
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class TileLoader;//forward declaration for pointer
class StaticTiledMap : public sf::Drawable
{
private:
	enum {tilesize=144,chunksize=144};//change values of these to match your needs and improve performance
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;
	sf::Texture m_texture;
	int map_x,map_y,chunks_x,chunks_y;//map x and y - dimensions of map in tiles, chunks x and y - amount of chunks
	std::vector<std::vector<sf::VertexArray> > m_chunks;
public:
	StaticTiledMap(void);
	virtual ~StaticTiledMap(void){};
	void LoadFrom(TileLoader* gloader);
};

#endif