// license: none

#include "tsysslate.h"

#include <iostream>

using namespace std;

tsysslate::tsysslate(slatearea *parentt, master *parent_mastert) : sysslate(parentt, parent_mastert)
{
	cerr << "Create tsysslate\n";
}

tsysslate::~tsysslate()
{
	cerr << "Destroy tsysslate\n";
}

