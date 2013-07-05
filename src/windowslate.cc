// Licence see COPYING


#include "windowslate.h"

windowslate::windowslate(string programpath,slatearea *parentt, master *parent_mastert) : slateareascreen(parentt, parent_mastert)
{

}

windowslate::~windowslate()
{

}

char windowslate::TYPE()
{
	return TYPE_filled;
}

