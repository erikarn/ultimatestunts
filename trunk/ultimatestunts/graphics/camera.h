/***************************************************************************
                          camera.h  -  A basic camera-class
                             -------------------
    begin                : ma feb 3 2003
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

#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "matrix.h"

/**
  *@author CJP
  */

class CCamera {
public: 
	CCamera();
	virtual ~CCamera();

	virtual const CVector &getPosition() const;
	virtual const CMatrix &getOrientation() const;

	virtual void update(){;}

protected:
	CVector m_Position;
	CMatrix m_Orientation;
};

#endif
