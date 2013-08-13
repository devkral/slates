// license: none

#include "tslatearea.h"
#include "temptyslate.h"

tslatearea::tslatearea(slate *parent_slate) : slatearea(parent_slate)
{
	
}


slateareascreen *tslatearea::create_emptyslate()
{
	return new temptyslate(this,get_master());
}

void tslatearea::handle_input(void *initializer)
{
	
	
}