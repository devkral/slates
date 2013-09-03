// Licence see COPYING


#include "slate.h"

slate::slate (viewport *parent,long int id,int position_xtemp,int position_ytemp)
{
	slateid=id;
	parent_viewport=parent;
	position_x=position_xtemp;
	position_y=position_ytemp;
}

slate::~slate()
{
}
void slate::init()
{
	child=get_viewport()->create_area(this);
	child->init();
	isready=true;
}

void slate::cleanup()
{
	isready=false;
	if (child!=0)
	{
		child->cleanup();
		delete child;
		child=0;
	}
}


bool slate::isfilled()
{
	return child->isfilled();
}

master *slate::get_master()
{
	return get_viewport()->get_master();
}

viewport *slate::get_viewport()
{
	return parent_viewport;
}

//fills with default slatearea
//used if resize shrinks area and for init
void slate::free_slate()
{
	init();
	update_isfilled(false);
}

//resize only
//emptyslates shouldn't be resizable
void slate::annect_slate(slatearea *newarea)
{
	if (child)
	{
		child->cleanup();
		delete child;
	}
	child=newarea;
	update_isfilled(true);
}

//newstate filled
void slate::update_isfilled(bool newstate)
{
	if (newstate)
		parent_viewport->fill_slate_intern(slateid);
	else
		parent_viewport->empty_slate_intern(slateid);
}


/**
void slate::emptyslate_nonunique()
{
	shared_ptr<deque< deque<slate*> > > tempconectedslates=child_slateo->connectedslates;
	while (tempconectedslates->empty()==false)
	{
		while (tempconectedslates->back().empty()==false)
		{
			tempconectedslates->back().back()->replace_childobject(create_emptyobject());
			tempconectedslates->back().back()->draw();
			tempconectedslates->back().pop_back();
		}
		tempconectedslates->pop_back();
	}
}*/

void slate::update()
{
	if(isready)
		child->update();
}

void slate::setlock(int lockstate)
{
	child->setlock(lockstate);
}

int16_t slate::get_x()
{
	return position_x;
}

int16_t slate::get_y()
{
	return position_y;
}

bool slate::isorigin()
{
	if (child->get_origin()->get_id()==get_id())
		return true;
	else
		return false;

}
int32_t slate::get_id()
{
	return slateid;
}
slatearea *slate::get_slatearea()
{
	return child;
}


void slate::handle_event(void *event)
{
	if(isready)
		child->handle_event(event);
}