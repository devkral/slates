// Licence see COPYING

#ifndef _EMPTYSLATEO_H_
#define _EMPTYSLATEO_H_
#include "slatetype.h"
class slatetype;

#include "constdef.h"

class emptyslate : public slateareascreen 
{
public:
	emptyslate(master *parent_mastert);
	~emptyslate();
	
	//int fillslate(string progname); //own content
	//int fillsysslate();
	char TYPE();
	
protected:

private:
	//virtual slatetype *create_windowslatetype()=0;
	//virtual slatetype *create_sysslatetype()=0;
};



#endif // _EMPTYSLATEO_H_

