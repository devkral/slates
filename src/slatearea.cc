// Licence see COPYING


#include "slatearea.h"

#include "lockslate.h"
class lockslate;
#include <slateareascreen.h>


slatearea::slatearea(slate *parent_slate)
{
	connectedslates.push_back( deque<slate*>() );
	connectedslates[0].push_back(parent_slate);
	
}

slatearea::~slatearea()
{
	isdestroying=true;
}

void slatearea::init()
{
	child=create_emptyslate();
}

void slatearea::cleanup()
{
	isdestroying=true;
	if (child)
	{
		//child->cleanup();
		delete child;
		child=0;
	}
	while (connectedslates.empty()==false)
	{
		connectedslates.pop_back();
	}
}

bool slatearea::isfilled()
{
	if (child->TYPE()!=TYPE_empty)
		return true;
	else
		return false;
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
	child->handle_event(event);
}


void slatearea::update()
{
	if (get_x()+width<=get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()+height<=get_origin ()->get_viewport()->get_viewport_beg_y() ||
		get_x()>=get_origin ()->get_viewport()->get_viewport_width()+get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()>=get_origin()->get_viewport()->get_viewport_height()+get_origin ()->get_viewport()->get_viewport_beg_y())
	{
		get_viewport()->remove_renderob(child->get_renderid ());
	}
	else
	{
		if (child->get_renderid ()==-1)
			get_viewport()->add_renderob(child);
	}
	child->update();
}
void slatearea::setlock(uint8_t lockstate)
{
	child->setlock(lockstate);
}

int slatearea::get_x()
{
	return get_origin()->get_x();
}
int slatearea::get_y()
{
	return get_origin()->get_y();
}

int slatearea::get_w()
{
	int temp=get_x()+width-(get_origin ()->get_viewport()->get_viewport_width()+get_origin ()->get_viewport()->get_viewport_beg_x());
	if(temp>0)
		return width-temp;
	return width;
}

int slatearea::get_h()
{
	int temp=get_y()+height-(get_origin ()->get_viewport()->get_viewport_height()+get_origin ()->get_viewport()->get_viewport_beg_y());
	if(temp>0)
		return height-temp;
	return height;
}

void slatearea::set_screen(slateareascreen *replacement)
{
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
	if (filledold!=isfilled())
	{
		for (int county=0;county<connectedslates.size();county++)
			for (int countx=0;countx<connectedslates[county].size();countx++)
				connectedslates[county][countx]->update_isfilled(isfilled());
	}
}


/**void slatearea::move(int16_t x, int16_t y)
{
	get_viewport()->
}

void slatearea::resize(int w, int h)
{

}*/