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
	get_viewport()->remove_renderob (get_renderid());
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



int32_t slateareascreen::get_renderid()
{
	return renderid;
}
void slateareascreen::set_renderid(int32_t id)
{
	if (renderid!=-1 && id!=-1 )
		std::cerr << "Error: renderid dirty\n";
	renderid=id;
}

void slateareascreen::swap_slatearea (slatearea *newparent)
{
	parent->set_screen (newparent->get_screen());
	if (parent->get_viewport()!=newparent->get_viewport())
	{
		parent->get_viewport()->remove_renderob (renderid);
		int32_t rivalid= newparent->get_screen()->get_renderid();
		if (rivalid!=-1)
			parent->get_viewport()->remove_renderob (rivalid);
		newparent->get_viewport()->add_renderob (this);
		
	}

	parent=newparent;
	newparent->set_screen(this);
}
slatearea *slateareascreen::get_slatearea ()
{
	return parent;
}