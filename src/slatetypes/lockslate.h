// Licence see COPYING


#ifndef _LOCKSLATEO_H_
#define _LOCKSLATEO_H_

#include "slatetype.h"
class slatetype;
//#include "slatearea.h"
class slatearea;

#include "constdef.h"

class lockslateo : public slatetype
{
public:
	lockslateo(master *parent_mastert);
	~lockslateo();
	char TYPE();
	virtual void lock(slatetype *lockedobject)=0;
	virtual slatetype *unlock()=0;
protected:
	slatetype *lockedob;

private:
	void sendunlock();
};

#endif // _LOCKSLATEO_H_

