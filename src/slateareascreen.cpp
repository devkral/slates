// Licence see COPYING


#include "slateareascreen.h"

#include "master.h"
#include "slatearea.h"


#include <iostream>

using namespace std;

slateareascreen::slateareascreen(slatearea *parentt, master *parent_mastert)
{
	parent_master=parent_mastert;
	parent=parentt;
}

slateareascreen::~slateareascreen()
{
	//get_viewport()->remove_renderob (get_renderid());
}

master *slateareascreen::get_master()
{
	return parent_master;
}

viewport *slateareascreen::get_viewport()
{
	return get_slatearea ()->get_viewport ();
}

void slateareascreen::handle_event(void *event)
{

}


void slateareascreen::setlock(uint8_t _lockstate)
{
	curlockstate=_lockstate;
}

bool slateareascreen::islocked()
{
	if (curlockstate>0)
		return true;
	return false;
}

slatearea *slateareascreen::get_slatearea ()
{
	return parent;
}

/**
void slateareascreen::swap_slatearea (slatearea *newparent)
{
	int32_t oldid=get_slatearea ()->get_renderid();
	int32_t newid=newparent->get_renderid();
	slatearea *oldparent=get_slatearea();
	parent->set_screen (newparent->get_screen());
	if (oldid==-1 && newid!=-1)
	{
		get_viewport()->add_renderob (newparent);
		newparent->get_viewport()->remove_renderob (newid);
	}
	if (oldid!=-1 && newid==-1)
	{
		get_viewport()->remove_renderob (oldid);
		newparent->get_viewport()->add_renderob (oldparent);
	}
	newparent->set_screen(this);
}*/