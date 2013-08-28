// Licence see COPYING


#ifndef _SYSSLATEO_H_
#define _SYSSLATEO_H_

#include "slateareascreen.h"
class slateareascreen;


#include "configbackend.h"


class sysslate: public slateareascreen 
{
public:
	sysslate(slatearea *parentt,master *parent_mastert);
	~sysslate();
	uint8_t TYPE();
protected:

private:

};

#endif // _SYSSLATEO_H_

