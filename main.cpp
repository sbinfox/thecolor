#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "theColor.h"

#define BUFW 800
#define BUFH 600

#define IDI_ICON_MAIN1 10001

int main (int argc, char ** argv)
{
  Fl_Window *window;
  window = new Fl_Window (BUFW, BUFH,"红绿蓝调色板");
  char * myicon=(char *)LoadIcon(fl_display,MAKEINTRESOURCE(IDI_ICON_MAIN1));
  window->icon(myicon);

  theColor myColor(0,0,BUFW,BUFH);

  window->end ();
  window->show (argc, argv);

  return(Fl::run());
}
