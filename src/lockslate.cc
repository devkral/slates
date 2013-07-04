// Licence see COPYING


#include "lockslate.h"

lockslate::lockslate(slatearea *parentt, master *parent_mastert) : slateareascreen(parentt,parent_mastert)
{
	
}

lockslate::~lockslate()
{

}


char lockslate::TYPE()
{
	return TYPE_locked;
}
