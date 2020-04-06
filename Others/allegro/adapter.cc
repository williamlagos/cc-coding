/*
 * Allegro sample
 */
#include <allegro.h>
#include "adapter.h"

Allegro::Allegro()
{

}

bool Allegro::helloWorld(char* word, int width, int height)
{
	if (allegro_init() != 0)
	    return 1;

	install_keyboard(); 

	if (set_gfx_mode(GFX_AUTODETECT, width, height, 0, 0) != 0) {
	    if (set_gfx_mode(GFX_SAFE, width, height, 0, 0) != 0) {
	  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	  allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
	  return 1;
	    }
	}

	set_palette(desktop_palette);
	clear_to_color(screen, makecol(255, 255, 255));
	acquire_screen();
	textout_centre_ex(screen, font, word, SCREEN_W/2, SCREEN_H/2, makecol(0,0,0), -1);
	release_screen();
	readkey();
}

int main(int argc, char** argv)
{
    Allegro *algr = new Allegro();
	char *sz = new char[12];
	strcpy(sz, "Hello World!");
	if(argc <= 1)
		algr->helloWorld(sz,320,200);
	else
		algr->helloWorld(sz,atoi(argv[1]),atoi(argv[2]));
	delete [] sz;
	return 0;
}
