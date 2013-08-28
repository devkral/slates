// license: none

#include "tviewport.h"

#include "tslatearea.h"
class tslatearea;
#include <iostream>

using namespace std;


tviewport::tviewport(master *masteridd, int ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create tviewport\n";
}

tviewport::~tviewport()
{
	cerr << "Destroy tviewport\n";
}


void tviewport::update_slice_info()
{
	cout << "slice updated\n";
}

void tviewport::render(slateareascreen *renderob)
{
	cout << "renderob updated\n";
}

int32_t tviewport::get_focused_slate()
{
	return 0;
}

slatearea *tviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new tslatearea(parent_slate);
}