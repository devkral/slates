// Licence see COPYING


#ifndef _LOCKSLATEO_H_
#define _LOCKSLATEO_H_

#include "slateareascreen.h"
class slateareascreen;
//#include "slatearea.h"
class slatearea;

#include "constdef.h"

class lockslate : public slateareascreen
{
public:
	lockslate(master *parent_mastert);
	~lockslate();
	char TYPE();
	virtual void lock(slateareascreen *lockedobject)=0;
	virtual slateareascreen *unlock()=0;
protected:
	slateareascreen *lockedob=0;

private:
	void sendunlock();
};

#endif // _LOCKSLATEO_H_

