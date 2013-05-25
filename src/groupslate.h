// Licence see COPYING

#ifndef _GROUPSLATE_H_
#define _GROUPSLATE_H_
#include <deque>

class slatearea;

class groupslate
{
public:

protected:

private:
	std::deque<slatearea*> slatearea_pool;
};

#endif // _GROUPSLATE_H_

