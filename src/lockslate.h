// Licence see COPYING

#ifndef _LOCKSLATE_H_
#define _LOCKSLATE_H_

#include "slateareascreen.h"
class slateareascreen;
class slatearea;

class lockslate : public slateareascreen
{
public:
	lockslate(slateareascreen *oldchild, slatearea *parentt,master *parent_mastert);
	~lockslate();
	slateareascreen  *unlock();
	uint8_t TYPE();
protected:
	slateareascreen *restore_child=0;
private:
	
};

#endif // _LOCKSLATE_H_

