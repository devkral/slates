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
	lockslate(slatearea parentt,master *parent_mastert);
	~lockslate();
	char TYPE();
protected:

private:
};

#endif // _LOCKSLATEO_H_

