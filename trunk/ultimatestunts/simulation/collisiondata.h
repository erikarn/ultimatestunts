/***************************************************************************
                          collisiondata.h  -  data describing collision events
                             -------------------
    begin                : di sep 23 2003
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

#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H


/**
  *@author CJP
  */

#include <vector> //STL vector template
namespace std {}
using namespace std;

#include "material.h"
#include "vector.h"
#include "collisionmodel.h"

class CWorld;

class CCollision {
public:
	//position relative to body center
	//normal pointing outwards
	//momentum transfer to body
	CVector pos, nor, dp;

	//position correction vector dr = rnew - rold
	CVector dr;

	const CMaterial *mat1, *mat2; //The two materials
	int body; //the body that collided
};

class CColEvents : public vector<CCollision>
{
public:
	bool isHit;
};

class CCollisionData {
public: 
	CCollisionData(const CWorld *w);
	~CCollisionData();

	vector<CColEvents> m_Events; //one per dynamic object

	void calculateCollisions();

protected:
	const CWorld *m_World;
	CVector m_TrackMin, m_TrackMax;
	bool m_FirstUpdate;

	//Object <-> object collisions
	void ObjObjTest(int n1, int n2);

	//Object <-> tile collisions
	void ObjTileTest(int nobj, int xtile, int ztile, int htile);
	CVector tileRotate(CVector v, int rot);
	void cullFace(CCollisionFace &theFace, const CCollisionFace &plane);

	//Object <-> track bound collisions
	void calculateTrackBounds();
	void ObjTrackBoundTest(int n);

	//Generic
	bool sphereTest(const CVector &p1, const CCollisionModel *b1, const CVector &p2, const CCollisionModel *b2);
};

#endif
