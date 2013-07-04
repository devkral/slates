// Licence see COPYING


#include "emptyslate.h"

emptyslate::emptyslate(slatearea *parentt, master *parent_mastert) : slateareascreen(parentt,parent_mastert)
{

}

emptyslate::~emptyslate()
{

}

char emptyslate::TYPE()
{
	return TYPE_empty;
}




/**
void slate::empty_emptyslate()
{
	if (child_slateo!=0 && child_slateo->TYPE()!=TYPE_emptyslate)
			parent_viewport->emptyslate_intern(slateid);
	if (child_slateo.use_count()==0)
	{
		replace_childobject(create_emptyobject());
		draw();
	}
	else
		emptyslate_nonunique();
}

*/