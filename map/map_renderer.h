#pragma once
#include <SFML/Graphics.hpp>

typedef void (*TileProvider)(int,int,int,sf::Color&, sf::IntRect&);

class MapRenderer : public sf::Drawable
{
public:
        MapRenderer(sf::Texture *texture, TileProvider provider, float tileSize=16, int layers=1);
        ~MapRenderer(void);
        float getTileSize() const;
        int getLayers() const;
 
        void refresh();
        void refresh(int x, int y);
        void draw(sf::RenderTarget &rt, sf::RenderStates states) const;
        void update(sf::RenderTarget &rt);
private:
        int width;
        int height;
        float tileSize;
        int layers;
        std::vector<sf::Vertex> vertices;
        sf::Vector2i offset;
        TileProvider provider;
        sf::Texture *texture;
 
        void setSize(sf::Vector2f v);
        void setCorner(sf::Vector2f v);
        sf::Vector2i getTile(sf::Vector2f pos) const;
        void draw(int index, sf::FloatRect rec, sf::IntRect src, sf::Color color);
        void refreshLocal(int left, int top, int right, int bottom);
 
};