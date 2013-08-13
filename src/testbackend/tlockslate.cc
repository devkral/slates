// license: none

#include "tlockslate.h"

#include <iostream>

using namespace std;

tlockslate::tlockslate(slatearea *parentt, master *parent_mastert) : lockslate(parentt,parent_mastert)
{
	cerr << "Create tlockslate\n";
}

tlockslate::~tlockslate()
{
	cerr << "Destroy tlockslate\n";
}


bool tlockslate::isstatic()
{
	return true;
}
bool tlockslate::isdirty()
{
	return true;
}