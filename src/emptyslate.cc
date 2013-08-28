// Licence see COPYING


#include "emptyslate.h"

emptyslate::emptyslate(slatearea *parentt, master *parent_mastert) : slateareascreen(parentt,parent_mastert)
{

}

emptyslate::~emptyslate()
{

}

uint8_t emptyslate::TYPE()
{
	return TYPE_empty;
}


string emptyslate::get_label_open_menu()
{
	return "Open Menu"; //use new ?? I don't think so
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