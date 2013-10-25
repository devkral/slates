// license: none

#include "tlockslate.h"

#include <iostream>

using namespace std;

tlockslate::tlockslate(slateareascreen *oldchild,slatearea *parentt, master *parent_mastert) : lockslate(oldchild,parentt,parent_mastert)
{
	cerr << "Create tlockslate\n";
}

tlockslate::~tlockslate()
{
	cerr << "Destroy tlockslate\n";
}


void tlockslate::update()
{

}
bool tlockslate::isdirty()
{
	return true;
}