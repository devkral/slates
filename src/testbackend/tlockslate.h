// license: none

#ifndef _TLOCKSLATE_H_
#define _TLOCKSLATE_H_

#include "lockslate.h"
class lockslate;


class tlockslate: public lockslate 
{
public:
	tlockslate(slateareascreen *oldchild,slatearea *parentt, master *parent_mastert);
	~tlockslate();
	void update();
	bool isdirty();
protected:

private:
	void unlock();
};

#endif // _TLOCKSLATE_H_

