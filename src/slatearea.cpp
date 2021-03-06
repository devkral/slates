// Licence see COPYING


#include "slatearea.h"

#include "lockslate.h"
class lockslate;
#include <slateareascreen.h>


slatearea::slatearea(slate *parent_slate)
{
	isdestroying=false;
	connectedslates.push_back( deque<slate*>() );
	connectedslates[0].push_back(parent_slate);
	
}

slatearea::~slatearea()
{
	isdestroying=true;
	activerendering=false;
}

void slatearea::cleanup()
{
	isdestroying=true;
	activerendering=false;

	if (child)
	{
		//child->cleanup();
		delete child;
	}
	
	if (get_viewport ()->get_isdestroying ()==false && (get_w()!=1 || get_h()!=1) )
	{
		reposition (get_x(),get_y(),1,1);
	}
}


void slatearea::init()
{
	if (get_isdestroying ())
		return;

	child=create_emptyslate();
	activerendering=true;
}




bool slatearea::isfilled()
{
	if (child->TYPE()!=TYPE_empty)
		return true;
	else
		return false;
}

bool slatearea::isactive ()
{
	return activerendering;
}

bool slatearea::get_isdestroying ()
{
	return isdestroying;
}

slate *slatearea::get_origin()
{
	return connectedslates[0][0];
}

master *slatearea::get_master()
{
	return get_origin()->get_master();
}

viewport *slatearea::get_viewport()
{
	return get_origin()->get_viewport ();
}


void slatearea::handle_event(void  *event)
{
	if (get_isdestroying ())
		return;
	try
	{
		child->handle_event(event);
	}
	catch (slateareascreen *newchild)
	{
		delete child;
		set_screen(newchild);
		update();
	}
}


void slatearea::update()
{
	if (get_isdestroying ())
		return;
	if (get_x()+width<=get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()+height<=get_origin ()->get_viewport()->get_viewport_beg_y() ||
		get_x()>=get_origin ()->get_viewport()->get_viewport_width()+get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()>=get_origin()->get_viewport()->get_viewport_height()+get_origin ()->get_viewport()->get_viewport_beg_y())
	{
		activerendering=false;
	}
	else
	{
		if (child->isdirty() && !child->islocked())
			activerendering=true;
	}
	child->update();
}  
void slatearea::setlock(uint8_t lockstate)
{
	if (get_isdestroying ())
		return;
	//child->setlock(lockstate);
	if (lockstate==1 && child->TYPE ()!=TYPE_locked)
	{
		//get_viewport ()->remove_renderob (get_renderid ());
		child->setlock(lockstate);
		child=create_lockslate ();
		activerendering=true;
	}else if (lockstate==0 && child->TYPE ()==TYPE_locked)
	{
		//get_viewport ()->remove_renderob (get_renderid ());
		slateareascreen *tempchild=child;
		child=((lockslate *)tempchild)->unlock();
		delete tempchild;
		child->setlock(lockstate);
		activerendering=true;
	}
	else
		child->setlock(lockstate);
}

int16_t slatearea::get_x()
{
	return get_origin()->get_x();
}
int16_t slatearea::get_y()
{
	return get_origin()->get_y();
}

int16_t slatearea::get_w()
{
	int16_t temp=get_x()+width-(get_origin ()->get_viewport()->get_viewport_width()+get_origin ()->get_viewport()->get_viewport_beg_x());
	if(temp>0)
		return width-temp;
	return width;
}

int16_t slatearea::get_h()
{
	int16_t temp=get_y()+height-(get_origin ()->get_viewport()->get_viewport_height()+get_origin ()->get_viewport()->get_viewport_beg_y());
	if(temp>0)
		return height-temp;
	return height;
}

void slatearea::set_screen(slateareascreen *replacement)
{
	if (get_isdestroying ())
		return;
	filledold=isfilled();
	child=replacement;
	update_isfilled();
}
slateareascreen *slatearea::get_screen()
{
	return child;
}

void slatearea::update_isfilled()
{
	if (filledold==true && isfilled()==false)
	{
		reposition (get_x(),get_y(),1,1);
	}
	/**if (filledold==false && isfilled()==true)
	{
		//do nothing
	}*/
}


/**void slatearea::move(int16_t x, int16_t y)
{
	get_viewport()->
}*/



int8_t slatearea::reposition_check(int16_t x, int16_t y, int16_t w, int16_t h)
{
	if (get_isdestroying ())
		return -1;
	int16_t old_x=get_x();
	int16_t old_y=get_y();
	int16_t old_w=get_w();
	int16_t old_h=get_h();

	if (x<0 ||  y<0)
	{
		return POS_NEG;
	}
	if (x+get_w()>=connectedslates[0].size() || y>=connectedslates.size())
	{
		return POS_OUT_OF_RANGE;
	}

	for (int16_t county=y;county<old_y;county++)
	{
		for (int16_t countx=0;countx<w;countx++)
		{
			if (get_viewport ()->get_slate (countx,county)->isfilled()==true)
				return SL_NOT_EMPTY;


		}
	}
	for (int16_t countx=x;countx<old_y;countx++)
	{
		for (int16_t county=0;county<h;county++)
		{
			if (get_viewport ()->get_slate (countx,county)->isfilled()==true)
				return SL_NOT_EMPTY;


		}
	}
	for (int16_t countx=old_x+old_w+1;countx<x+w;countx++)
	{
		for (int16_t county=0;county<h;county++)
		{
			if (get_viewport ()->get_slate (countx,county)->isfilled()==true)
				return SL_NOT_EMPTY;

		}
	}

	for (int16_t county=old_y+old_h+1;county<y+h;county++)
	{
		for (int16_t countx=0;countx<w;countx++)
		{
			if (get_viewport ()->get_slate (countx,county)->isfilled()==true)
				return SL_NOT_EMPTY;
		}
	}
	
	
	return OP_SUCCESS;
}

// do reposition_check before!
void slatearea::reposition(int16_t x, int16_t y, int16_t w, int16_t h)
{
	if (get_isdestroying ())
		return;

	int16_t old_x=get_x();
	int16_t old_y=get_y();
	int16_t old_w=get_w();
	int16_t old_h=get_h();


	if (old_y<y)
	{
		for (int16_t county=y;county<old_y;county++)
		{
			for (int16_t countx=0;countx<connectedslates[0].size();countx++)
			{
				get_viewport ()->get_slate (countx,county)->annect_slate (this);
			}
		}
	}
	else
	{
		for (int16_t county=old_y;county<y;county++)
		{
			for (int16_t countx=0;countx<connectedslates[0].size();countx++)
			{
				get_viewport ()->get_slate (countx,county)->free_slate ();
			}
		}
	}
	if (old_x<x)
	{
		for (int16_t countx=x;countx<old_x;countx++)
		{
			for (int16_t county=0;county<connectedslates.size();county++)
			{
				get_viewport ()->get_slate (countx,county)->annect_slate (this);
			}
		}
	}
	else
	{
		for (int16_t countx=old_x;countx<x;countx++)
		{
			for (int16_t county=0;county<connectedslates.size();county++)
			{
				get_viewport ()->get_slate (countx,county)->free_slate ();
			}
		}

	}
	
	if (old_x+old_w<x+w)
	{
		for (int16_t countx=old_x+old_w+1;countx<x+w;countx++)
		{
			for (int16_t county=0;county<connectedslates.size();county++)
			{
				get_viewport ()->get_slate (countx,county)->annect_slate (this);
			}
		}
	}
	else
	{
		for (int16_t countx=x+w+1;countx<old_x+old_w;countx++)
		{
			for (int16_t county=0;county<connectedslates.size();county++)
			{
				get_viewport ()->get_slate (countx,county)->free_slate();
			}
		}
	}

	//fill gap y
	if (old_y+old_h<y+h)
	{
		for (int16_t county=old_y+old_h+1;county<y+h;county++)
		{
			for (int16_t countx=0;countx<connectedslates[0].size();countx++)
			{
				get_viewport ()->get_slate (countx,county)->annect_slate (this);
			}
		}
	}
	else
	{
		for (int16_t county=y+h+1;county<old_y+old_h;county++)
		{
			for (int16_t countx=0;countx<connectedslates[0].size();countx++)
			{
				get_viewport ()->get_slate (countx,county)->free_slate ();
			}
		}
	}
	
}