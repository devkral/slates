// license: none

#include "temptyslate.h"


#include <iostream>

using namespace std;


temptyslate::temptyslate(slatearea *parentt, master *parent_mastert) : emptyslate(parentt, parent_mastert)
{
	cerr << "Create temptyslateo\n";
}

temptyslate::~temptyslate()
{
	cerr << "Destroy temptyslateo\n";
}
void temptyslate::update()
{

}

bool temptyslate::isstatic()
{
	return true;
}
bool temptyslate::isdirty()
{
	return true;
}