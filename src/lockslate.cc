// Licence see COPYING


#include "lockslate.h"

lockslate::lockslate(master *parent_mastert) : slateareascreen(parent_mastert)
{
	
}

lockslate::~lockslate()
{

}

/**slatetype *lockslateo::unlock(slatearea *)
{
	slatetype *temp=lockedobject;
	assert(lockedobject);
	lockedobject=0;	
	return temp;
}*/




char slateareascreen::TYPE()
{
	return TYPE_locked;
}

