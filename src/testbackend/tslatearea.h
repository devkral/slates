// license: none

#ifndef _TSLATEAREA_H_
#define _TSLATEAREA_H_

#include "slatearea.h"
#include "tlockslate.h"

using namespace std;

class tslatearea : public slatearea
{
public:
	tslatearea(slate *parent_slate);
	slateareascreen *create_lockslate();
	slateareascreen *create_emptyslate();
};

#endif // _TSLATEAREA_H_

