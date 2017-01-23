/*
  event.cpp - ForceFusion VizTact touch event functions implementation.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#include "event.h"

static unsigned int seq = 0;

void EventList::updateList(TouchEvent* e) {

  seq++;
}
