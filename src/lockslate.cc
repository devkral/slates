// Licence see COPYING


#include "lockslate.h"

lockslate::lockslate(slatearea parentt, master *parent_mastert) : slateareascreen(parentt,parent_mastert)
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


char lockslate::TYPE()
{
	return TYPE_locked;
}
