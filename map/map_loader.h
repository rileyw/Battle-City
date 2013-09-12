#include "tile_loader.h"
#include "static_tiled_map.h"

class MapLoader : public TileLoader
{
public:
	MapLoader(void)
	{
		m_mapdata.MapX=512;
		m_mapdata.MapY=512;
		m_mapdata.TextureName="imgGround.bmp";//a simple 32x32 seamless image of brick 
	}
	virtual void AppendTile(int gx,int gy,sf::VertexArray& garr)
	{
		sf::Vertex ver;
		ver.position=sf::Vector2f(gx*144.f,gy*144.f);
		ver.texCoords=sf::Vector2f(0.f,0.f);
		garr.append(ver);

		ver.position=sf::Vector2f(gx*144.f+144.f,gy*144.f);
		ver.texCoords=sf::Vector2f(144.f,0.f);
		garr.append(ver);

		ver.position=sf::Vector2f(gx*144.f+144.f,gy*144.f+144.f);
		ver.texCoords=sf::Vector2f(144.f,144.f);
		garr.append(ver);

		ver.position=sf::Vector2f(gx*144.f,gy*144.f+144.f);
		ver.texCoords=sf::Vector2f(0.f,144.f);
		garr.append(ver);
	}
};