// license: none

#ifndef _TVIEWPORT_H_
#define _TVIEWPORT_H_
#include "viewport.h"
class viewport;




using namespace std;


class tviewport : public viewport
{
public:
	tviewport(master *masteridd, int ownidd);
	~tviewport();
	slate *create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp);
	void render(slateareascreen *renderob);
	int32_t get_focused_slate_id ();
	slatearea *create_area(slate *parent_slate);
protected:
	void update_slice_info();
	
private:
};

#endif // _TVIEWPORT_H_

