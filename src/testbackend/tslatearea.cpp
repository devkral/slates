// license: none

#include "tslatearea.h"
#include "temptyslate.h"

tslatearea::tslatearea(slate *parent_slate) : slatearea(parent_slate)
{
	
}

slateareascreen *tslatearea::create_lockslate()
{
	return new tlockslate(child,this,get_master());
}

slateareascreen *tslatearea::create_emptyslate()
{
	return new temptyslate(this,get_master());
}