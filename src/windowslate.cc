// Licence see COPYING


#include "windowslate.h"



windowslate::windowslate(string programpath,slatearea *parentt, master *parent_mastert) : slateareascreen(parentt, parent_mastert)
{
	//programrunning=thread(startprogram,programpath);
}

windowslate::~windowslate()
{
	//programrunning.join();
}

uint8_t windowslate::TYPE()
{
	return TYPE_filled;
}

