/***************************************************************************
                          usmacros.h  -  ultimate stunts macros
                             -------------------
    copyright            : (C) 2002 by bones
    email                : boesemar@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#if defined(_WIN32) // && !defined(_WINGDI_) && !defined(MESA)
#define CALLBACKFUN __cdecl
#else
#define CALLBACKFUN
#endif

#ifndef _USENDIAN_H
#define _USENDIAN_H

#include "SDL_endian.h"
#include "SDL.h"

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define ENDIANFIX16(X)    (X)
#define ENDIANFIX32(X)    (X)
#else
#define ENDIANFIX16(X)    SDL_Swap16(X)
#define ENDIANFIX32(X)    SDL_Swap32(X)
#endif

#define LOBYTE(w)           ((Uint8)(w))
#define HIBYTE(w)           ((Uint8)(((Uint16)(w) >> 8) & 0xFF))

#define TILESIZE 40 //40 meter horizontal
#define VERTSIZE 12  //12 meter vertical
/*

             /--------------/    N
            /              /|    |  12 meter
           /              / |    V
          /              / /  N
         /--------------/ /  /  40 meter
         |              |/  /
         |--------------/  V

         <------------->
               40 meter
*/

#endif

#ifndef __CYGWIN__
#ifdef __CYGWIN32__
#define __CYGWIN__ __CYGWIN32__
#endif
#endif

#ifdef __CYGWIN__

#define NETTYPE char
#undef UNIX_TREE
#define DEBUGMSG

#else

#define NETTYPE void
#define UNIX_TREE //expect and use $HOME, /etc etc.
#define DEBUGMSG

#endif
