// Licence see COPYING


#ifndef _LOCKSLATE_H_
#define _LOCKSLATE_H_

#include "slateareascreen.h"
class slateareascreen;
//#include "slatearea.h"
class slatearea;

#include "configbackend.h"

class lockslate : public slateareascreen
{
public:
	lockslate(slatearea *parentt,master *parent_mastert);
	~lockslate();
	uint8_t TYPE();
protected:

private:
};

#endif // _LOCKSLATE_H_

