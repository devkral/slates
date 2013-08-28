// Licence see COPYING

#include "sysslate.h"

sysslate::sysslate(slatearea *parentt,master *parent_mastert) : slateareascreen(parentt,parent_mastert)
{


}

sysslate::~sysslate()
{


}

uint8_t sysslate::TYPE()
{
	return TYPE_filled;
}

