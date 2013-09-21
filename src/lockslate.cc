// Licence see COPYING


#include "lockslate.h"



lockslate::lockslate(slateareascreen *oldchild, slatearea *parentt, master *parent_mastert) : slateareascreen(parentt,parent_mastert)
{
	restore_child=oldchild;
}

lockslate::~lockslate()
{
	delete restore_child;
}
slateareascreen *lockslate::unlock()
{
	return restore_child;
}

uint8_t lockslate::TYPE()
{
	return TYPE_locked;
}
