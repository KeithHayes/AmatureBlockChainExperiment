#include "ltexture.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
LTexture::~LTexture() {
	free();
}
SDL_Window* LTexture::getWindow(){ return gWindow; }
SDL_Renderer* LTexture::getRenderer(){ return gRenderer; }
TTF_Font* LTexture::getFont(){ return gFont; }
void LTexture::LTexture::setWindow(SDL_Window* window){ gWindow = window;}
void LTexture::setRenderer(SDL_Renderer* renderer){ gRenderer = renderer;}
void LTexture::setFont(TTF_Font* font){ gFont = font;}
void LTexture::init() {
	SDL_Init( SDL_INIT_VIDEO );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	gWindow = SDL_CreateWindow( "Mining for Block", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	IMG_Init( IMG_INIT_PNG );
	TTF_Init();
	gFont =  TTF_OpenFont( "../../data/OpenSansExtraBold.ttf", 28 );
	SDL_Color textColor = { 0, 0, 0 };
	loadFromRenderedText( "The quick brown fox", textColor );
}
void LTexture::loadText( std::string textureText ) {
	SDL_Color textColor = { 31, 31, 31 };
	loadFromRenderedText( textureText, textColor );
}
void LTexture::close() {
	free();
	TTF_CloseFont( gFont );
	gFont = NULL;
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
bool LTexture::loadFromFile( std::string path ) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}	else	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}		else		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL ) {
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	} else {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}		else		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	return mTexture != NULL;
}
void LTexture::free() {
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}
void LTexture::setBlendMode( SDL_BlendMode blending ) {
	SDL_SetTextureBlendMode( mTexture, blending );
}
void LTexture::setAlpha( Uint8 alpha ) {
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if( clip != NULL ) 	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
int LTexture::getWidth() {
	return mWidth;
}
int LTexture::getHeight() {
	return mHeight;
}
