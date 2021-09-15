#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "crc0x1d0f.h"
#include "results.h"
#include "ltexture.h"

int main( int argc, char *argv[] ) {
	char *ptr;
	uint16_t crc_ccitt_1d0f_val;
	//std::string text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	// "ABCDEFGHIJKLMNOPQRSTUVWXYZ" : CRC-CCITT (0x1d0f) = 0x4430  --  17456 
	//std::string text = "Medicare for All ! test string";
	std::string text = "<@!7he0)bb&>Date 9/15/2021 Account #57398759343607: Groceries -$123.86 Gas -$74.35 Ebay Payment $123.09 (Account BALANCE $762.98) 'Money is a great servant and a bad master'.}<!@#$k78PO*>";
	// The actual block is this prefix | (0x1A)(0x23)(0x__)(0x__)(0x__) |  plus | .....the above quoted string ..... |.
	bool minedstatus;
	bool quit = false;
	SDL_Event e;
	Crc0x1d0f newmessage(text.c_str());
	Results result;
	LTexture gTextTexture;
	gTextTexture.init();
	//newmessage.compute();	
	while( !quit ) {
		do { minedstatus = newmessage.extendedcompute(0x1a24, 0x02);  // parent link with shine
		} while (minedstatus == false);
		result.addblock(newmessage.getshine(), newmessage.getblockkey());
		result.getscreenstring();
		gTextTexture.loadText(result.getscreenstring());
		while( SDL_PollEvent( &e ) != 0 ) { if( e.type == SDL_QUIT ) { quit = true; } }
		SDL_SetRenderDrawColor( gTextTexture.getRenderer(), 0xDA, 0xA5, 0x20, 0xFF );
		SDL_RenderClear( gTextTexture.getRenderer() );
		gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
		SDL_RenderPresent( gTextTexture.getRenderer());
	}
	result.showtable();
	gTextTexture.close();
	return 0;
}
