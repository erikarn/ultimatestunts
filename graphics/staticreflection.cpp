/***************************************************************************
                          staticreflection.cpp  -  A reflection map from a texture file
                             -------------------
    begin                : za mei 14 2005
    copyright            : (C) 2005 by CJP
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

#include <cstdio>

#include "staticreflection.h"

CStaticReflection::CStaticReflection() : CReflection() , CTexture(NULL)
{
}

CStaticReflection::~CStaticReflection()
{
}

bool CStaticReflection::load(const CString &filename, const CParamList &list)
{
	if(!CTexture::load(filename, list)) return false;

	CReflection::m_Texture = CTexture::m_Texture;

	return true;
}
