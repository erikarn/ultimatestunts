/***************************************************************************
                          hello.cpp  -  dummy file
                             -------------------
    begin                : Wed Nov 20 2002
    copyright            : (C) 2002 by CJP
    email                : cornware-cjp@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <libintl.h>
#define _(String) gettext (String)

#include <cstdio>

#include "hello.h"

hello::hello(){
}
hello::~hello(){
}
void hello::writeHello()
{
  printf(_("Hello, world!\n"));
}
