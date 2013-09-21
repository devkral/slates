// Licence see COPYING


#ifndef _WINDOWSLATE_H_
#define _WINDOWSLATE_H_

#include <string>
#include <thread>
#include "slateareascreen.h"
class slateareascreen;

#include "configbackend.h"


class windowslate : public slateareascreen
{
public:
	windowslate(string programpath,slatearea *parentt, master *parent_mastert);
	~windowslate();
	uint8_t TYPE();
	
protected:

private:
	thread programrunning;
};

#endif // _WINDOWSLATE_H_

