// Licence see COPYING

#ifndef _EMPTYSLATE_H_
#define _EMPTYSLATE_H_

#include "slateareascreen.h"
class slateareascreen;
class slatearea;
#include "configbackend.h"

class emptyslate : public slateareascreen 
{
public:
	emptyslate(slatearea *parentt, master *parent_mastert);
	~emptyslate();
	virtual string get_label_open_menu();
	
	//int fillslate(string progname); //own content
	//int fillsysslate();
	uint8_t TYPE();
	
protected:

private:
	//virtual slateareascreen *create_windowslate()=0;
	//virtual slateareascreen *create_sysslate()=0;
	//virtual slateareascreen *create_configslate()=0;
	//virtual slateareascreen *create_groupslate()=0;
};



#endif // _EMPTYSLATEO_H_

