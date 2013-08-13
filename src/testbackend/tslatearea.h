// license: none

#ifndef _TSLATEAREA_H_
#define _TSLATEAREA_H_

#include "slatearea.h"

using namespace std;

class tslatearea : public slatearea
{
public:
	tslatearea(slate *parent_slate);
	slateareascreen *create_emptyslate();
	void handle_input(void *initializer);
};

#endif // _TSLATEAREA_H_

