// Licence see COPYING

#ifndef _EMPTYSLATEO_H_
#define _EMPTYSLATEO_H_
#include "slateareascreen.h"
class slateareascreen;
class slatearea;
#include "configbackend.h"

class emptyslate : public slateareascreen 
{
public:
	emptyslate(slatearea *parentt, master *parent_mastert);
	~emptyslate();
	
	//int fillslate(string progname); //own content
	//int fillsysslate();
	char TYPE();
	
protected:

private:
	//virtual slateareascreen *create_windowslate()=0;
	//virtual slateareascreen *create_sysslate()=0;
	//virtual slateareascreen *create_configslate()=0;
	//virtual slateareascreen *create_groupslate()=0;
};



#endif // _EMPTYSLATEO_H_

