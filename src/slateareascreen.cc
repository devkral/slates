// Licence see COPYING


#include "slateareascreen.h"

#include <iostream>

using namespace std;

slateareascreen::slateareascreen(master *parent_mastert)
{
	parent_master=parent_mastert;
	dirty=true;
}

slateareascreen::~slateareascreen()
{

}

master *slateareascreen::get_master()
{
	return parent_master;
}

void slateareascreen::handle_event(void *event)
{

}

slatearea *slateareascreen::get_slatearea()
{
	return parent;
}

bool slateareascreen::isstatic()
{
	return true;
}
long int get_renderid()
{
	return renderid;
}
void set_renderid(long int id)
{
	if (renderid!=-1 && id!=-1 )
		std::cerr << "Error: renderid dirty\n";
	renderid=id;
}