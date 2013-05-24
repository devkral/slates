// Licence see COPYING


#include "emptyslate.h"

emptyslate::emptyslate(master *parent_mastert) : slateareascreen(parent_mastert)
{

}

emptyslate::~emptyslate()
{

}

char emptyslateo::TYPE()
{
	return TYPE_empty;
}
/**

int slate::fillslate(string progname)
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		replace_childobject(create_windowobject(progname));
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}
int slate::fillsysslate()
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		slateobject *verify=create_sysobject();
		assert(verify);
		replace_childobject(verify);
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}

void slate::emptyslate()
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
