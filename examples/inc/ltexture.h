#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 140;

class LTexture
{
	public:
		LTexture();
		~LTexture();
		void init();
		void close();
		bool loadFromFile( std::string path );
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();
		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();
		TTF_Font *getFont();
		void setWindow(SDL_Window* window);
		void setRenderer(SDL_Renderer* renderer);
		void setFont(TTF_Font* font);
		void loadText( std::string textureText );


	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		TTF_Font* gFont;
};

#endif // LTEXTURE_H
