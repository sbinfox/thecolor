#include "theColor.h"
#include "seal.xpm"

#define BUFW 800
#define BUFH 600

#define REDCTX 345
#define REDCTY 30

#define GREENCTX 193
#define GREENCTY 560

#define BLUECTX 496
#define BLUECTY 560

theColor::theColor(int X,int Y,int W,int H): Fl_Widget(X,Y,W,H)
{
    mybuf=fl_create_offscreen(BUFW,BUFH);
    mousex=0;       mousey=0;
    redv=100;     greenv=100;   bluev=100;
    isred=FALSE;  isgreen=FALSE;  isblue=FALSE;
    myrgb=NOTHING;

    fl_font(FL_TIMES,14);
}

theColor::~theColor()
{
    fl_delete_offscreen(mybuf);
}

void theColor::draw()
{
    int x,y;

    fl_begin_offscreen(mybuf);
        fl_color(FL_WHITE);
        fl_rectf(0,0,BUFW,BUFH);

        fl_color(FL_BLACK);

        fl_rect(REDCTX,REDCTY,110,10);
        fl_rectf(redv+REDCTX,REDCTY-5,10,20);

        fl_rect(GREENCTX,GREENCTY,110,10);
        fl_rectf(greenv+GREENCTX,GREENCTY-5,10,20);

        fl_rect(BLUECTX,BLUECTY,110,10);
        fl_rectf(bluev+BLUECTX,BLUECTY-5,10,20);

         for(x=250;x<550;x++)
        {
            for(y=157;y<443;y++)
            {
                if( (x-400)*(x-400)+(y-257)*(y-257)<10000  ) isred=TRUE;
                else isred=FALSE;
                if( (x-350)*(x-350)+(y-343)*(y-343)<10000  ) isgreen=TRUE;
                else isgreen=FALSE;
                if( (x-450)*(x-450)+(y-343)*(y-343)<10000  ) isblue=TRUE;
                else isblue=FALSE;

                if( isred&&(!isgreen)&&(!isblue) )
                {
                    fl_color(redv*51/20,0,0);
                    fl_point(x,y);
                }
                if(  isgreen&&(!isred)&&(!isblue)  )
                {
                    fl_color(0,greenv*51/20,0);
                    fl_point(x,y);
                }
                if(  isblue&&(!isred)&&(!isgreen)  )
                {
                    fl_color(0,0,bluev*51/20);
                    fl_point(x,y);
                }
                if(  isred&&isgreen&&(!isblue)  )
                {
                    fl_color(redv*51/20,greenv*51/20,0);
                    fl_point(x,y);
                }
                if(  isgreen&&isblue&&(!isred)  )
                {
                    fl_color(0,greenv*51/20,bluev*51/20);
                    fl_point(x,y);
                }
                if(  isred&&isblue&&(!isgreen)  )
                {
                    fl_color(redv*51/20,0,bluev*51/20);
                    fl_point(x,y);
                }
                if(isred&&isgreen&&isblue)
                {
                    fl_color(redv*51/20,greenv*51/20,bluev*51/20);
                    fl_point(x,y);
                }
            }
        }

        fl_draw_pixmap(dummy,700,450);
        fl_color(FL_BLACK);
        fl_draw("金 刚 手",708,530);

    fl_end_offscreen();
    fl_copy_offscreen(0,0,BUFW,BUFH,mybuf,0,0);
}

int theColor::handle(int event)
{
    mousex=Fl::event_x();   mousey=Fl::event_y();
    if(event==FL_PUSH)
    {
        if( mousex>=redv+REDCTX && mousex<=redv+REDCTX+10 && mousey>=REDCTY-5 && mousey<=REDCTY+5  ) myrgb=REDSLIDE;
        else if ( mousex>=greenv+GREENCTX && mousex<=greenv+GREENCTX+10 && mousey>=GREENCTY-5 && mousey<=GREENCTY+5  ) myrgb=GREENSLIDE;
        else if ( mousex>=bluev+BLUECTX && mousex<=bluev+BLUECTX+10 && mousey>=BLUECTY-5 && mousey<=BLUECTY+5  ) myrgb=BLUESLIDE;
        else myrgb=NOTHING;
    }

    if(event==FL_DRAG)
    {
        if(myrgb==REDSLIDE)
        {
            if(mousex<=REDCTX) redv=0;
            else if(mousex>=REDCTX+100) redv=100;
            else redv=mousex-REDCTX;
        }
        if(myrgb==GREENSLIDE)
        {
            if(mousex<=GREENCTX) greenv=0;
            else if(mousex>=GREENCTX+100) greenv=100;
            else greenv=mousex-GREENCTX;
        }
        if(myrgb==BLUESLIDE)
        {
            if(mousex<=BLUECTX) bluev=0;
            else if(mousex>=BLUECTX+100) bluev=100;
            else bluev=mousex-BLUECTX;
        }
    }

    if(event==FL_RELEASE)
    {
        myrgb=NOTHING;
    }

    redraw();

    return TRUE;
}
