/***************************************************************************
                          shape.h  -  Vertex-based collision model
                             -------------------
    begin                : vr jan 24 2003
    copyright            : (C) 2003 by CJP
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

#ifndef SHAPE_H
#define SHAPE_H

#include <vector> //STL vector template
namespace std {}
using namespace std;

#include "material.h"
#include "cstring.h"

/**
  *@author CJP
  */

class CShapeFace {
public:
	CVector p1, p2, p3;
};

class CShape {
public: 
	CShape();
	~CShape();

	bool loadFromFile(CString filename, CString subset, CMaterial ** matarray);

	float m_BSphere_r;
	CVector m_BBox_min, m_BBox_max;

	vector<CShapeFace> m_Faces;

	CString m_Filename;
	CString m_Subset;
};

#endif
