// Licence see COPYING


#ifndef _SYSSLATEO_H_
#define _SYSSLATEO_H_

#include "slateareascreen.h"
class slateareascreen;


#include "constdef.h"


class sysslate: public slateareascreen 
{
public:
	sysslate(slatearea *parentt,master *parent_mastert);
	~sysslate();
	char TYPE();
protected:

private:

};

#endif // _SYSSLATEO_H_

