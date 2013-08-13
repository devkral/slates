// license: none

#ifndef _TEMPTYSLATE_H_
#define _TEMPTYSLATE_H_
#include "emptyslate.h"
class emptyslate;


class temptyslate : public emptyslate 
{
public:
	temptyslate(slatearea *parentt, master *parent_mastert);
	~temptyslate();
	void update();
	bool isstatic();
	bool isdirty();
protected:

private:

};

#endif // _TEMPTYSLATEO_H_

