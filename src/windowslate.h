// Licence see COPYING


#ifndef _WINDOWSLATE_H_
#define _WINDOWSLATE_H_

#include <string>
#include "slateareascreen.h"
class slateareascreen;

#include "constdef.h"


class windowslate : public slateareascreen
{
public:
	windowslate(string programpath,slatearea parentt, master *parent_mastert);
	~windowslate();
	char TYPE();
protected:

private:
	
};

#endif // _WINDOWSLATE_H_

