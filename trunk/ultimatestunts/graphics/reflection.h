/***************************************************************************
                          reflection.h  -  description
                             -------------------
    begin                : ma sep 20 2004
    copyright            : (C) 2004 by CJP
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

#ifndef REFLECTION_H
#define REFLECTION_H

#include "renderer.h"

/**
  *@author CJP
  */

class CReflection  {
public: 
	CReflection(bool smooth, unsigned int size);
	~CReflection();

	void update(CRenderer *renderer, CCamera *cam, int side = -1);
	void draw() const;

protected:
	unsigned int m_Texture; //spheremap texture
	unsigned int m_ReflectionTexture[6]; //side textures
	float m_CentralPixel[4]; //the front color = clear color for the spheremap


	void initialiseReflections();

	unsigned int m_Size;
	bool m_TexSmooth;
};

#endif
