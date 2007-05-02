/***************************************************************************
                          loadobj.cpp  -  OBJ file loader
                             -------------------
    begin                : wo feb 1 2006
    copyright            : (C) 2006 by CJP
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
 
#include "datafile.h"

#include "loadobj.h"

bool loadOBJ(const CString &filename, CEditGraphObj &obj)
{
	CDataFile f(filename);

	obj.clear();

	vector<CVector> v_arr, vn_arr, vt_arr;

	//describes per-vertex which v[n|t]_arr element it uses
	vector<unsigned int> v_index, vn_index, vt_index;

	while(true)
	{
		CString line = f.readl();
		if(line == "\n") break;

		if(line.length() < 2) continue;
		if(line[0] == '#') continue;

		int pos = line.inStr(' ');
		if(pos < 0) continue;
		CString lhs = line.mid(0, pos), rhs = line.mid(pos+1);

		if(lhs == "g" || lhs == "o") //I don't know the difference
		{
			obj.m_Primitives.push_back(CPrimitive());
			CPrimitive &pr = obj.m_Primitives.back();

			pr.m_Name = rhs;
			pr.m_Type = CPrimitive::VertexArray;
			pr.m_Material.LODs = "1234c";
			pr.m_Material.emissivity = 0.0;
			pr.m_Material.opacity = 1.0;
			pr.m_Material.reflectance = 0.0;
			pr.m_Material.modulationColor = CVector(1,1,1);
			pr.m_Material.texture = -1;
			pr.m_Material.replacementColor = pr.m_Material.modulationColor;

			v_index.clear();
			vn_index.clear();
		}
		else if(lhs == "v")
		{
			CVector v;
			int pos = rhs.inStr(' ');
			if(pos < 0)
				{v.x = rhs.toFloat();}
			else
			{
				v.x = rhs.mid(0, pos).toFloat();
				rhs = rhs.mid(pos+1);

				pos = rhs.inStr(' ');
				if(pos < 0)
					{v.y = rhs.toFloat();}
				else
				{
					v.y = rhs.mid(0, pos).toFloat();
					rhs = rhs.mid(pos+1);

					v.z = rhs.toFloat();
				}
			}

			v_arr.push_back(v);
		}
		else if(lhs == "vn")
		{
			CVector v;
			int pos = rhs.inStr(' ');
			if(pos < 0)
				{v.x = rhs.toFloat();}
			else
			{
				v.x = rhs.mid(0, pos).toFloat();
				rhs = rhs.mid(pos+1);

				pos = rhs.inStr(' ');
				if(pos < 0)
					{v.y = rhs.toFloat();}
				else
				{
					v.y = rhs.mid(0, pos).toFloat();
					rhs = rhs.mid(pos+1);

					v.z = rhs.toFloat();
				}
			}

			vn_arr.push_back(v);
		}
		else if(lhs == "vt")
		{
			CVector v;
			int pos = rhs.inStr(' ');
			if(pos < 0)
				{v.x = rhs.toFloat();}
			else
			{
				v.x = rhs.mid(0, pos).toFloat();
				rhs = rhs.mid(pos+1);

				pos = rhs.inStr(' ');
				if(pos < 0)
					{v.y = rhs.toFloat();}
				else
				{
					v.y = rhs.mid(0, pos).toFloat();
					rhs = rhs.mid(pos+1);

					v.z = rhs.toFloat();
				}
			}

			vt_arr.push_back(v);
		}
		else if(lhs == "f")
		{
			CPrimitive &pr = obj.m_Primitives.back();

			unsigned int i=0;
			while(true)
			{
				int pos = rhs.inStr("/");
				if(pos < 0)
				{
					if(i < 3)
						printf("Error in line \"%s\": less than 3 points\n", line.c_str());

					break;
				}

				unsigned int vi = rhs.mid(0, pos).toInt() - 1;
				rhs = rhs.mid(pos+1);

				pos = rhs.inStr("/");
				if(pos < 0)
				{
					printf("Error in line \"%s\": not an even number of slashes\n", line.c_str());
					break;
				}

				unsigned int ti = rhs.mid(0, pos).toInt() - 1;
				if(pos == 0) ti = 0; //handle missing texture coordinate
				rhs = rhs.mid(pos+1);

				unsigned int ni = 0;
				pos = rhs.inStr(' ');
				if(pos < 0)
				{
					ni = rhs.toInt() - 1;
				}
				else
				{
					ni = rhs.mid(0, pos).toInt() - 1;
					rhs = rhs.mid(pos+1);
				}

				if(vi >= v_arr.size())
				{
					printf("In line \"%s\":\n", line.c_str());
					printf("Error: vertex index %d exceeds array size %d\n", vi+1, v_arr.size());
					return false;
				}

				if(ni >= vn_arr.size())
				{
					printf("In line \"%s\":\n", line.c_str());
					printf("Error: normal index %d exceeds array size %d\n", ni+1, v_arr.size());
					return false;
				}

				if(pr.m_Vertex.size() != v_index.size() || pr.m_Vertex.size() != vn_index.size())
				{
					printf("Error: array sizes %d, %d and %d do not match\n",
						pr.m_Vertex.size(), v_index.size(), vn_index.size());
					return false;
				}

				int vti = -1; //vertex array index, -1 = not found
				for(unsigned int j=0; j < pr.m_Vertex.size(); j++)
					if(v_index[j] == vi && vn_index[j] == ni && vt_index[j] == ti)
						{vti = j; break;}

				if(vti < 0) //then create a new array element
				{
					CVertex vt;
					vt.pos = v_arr[vi];
					vt.nor = vn_arr[ni];
					if(ti < vt_arr.size()) vt.tex = vt_arr[ti];
					pr.m_Vertex.push_back(vt);
					v_index.push_back(vi);
					vn_index.push_back(ni);
					vt_index.push_back(ti);
					vti = pr.m_Vertex.size()-1;
				}

				//For polygons with >3 vertices:
				if(i >= 3)
				{
					unsigned int vt0 = pr.m_Index[pr.m_Index.size()-i];
					unsigned int vt1 = pr.m_Index[pr.m_Index.size()-1];
					pr.m_Index.push_back(vt0);
					pr.m_Index.push_back(vt1);
				}

				pr.m_Index.push_back(vti);

				i++;
			}
		}
	}

	printf("Loading was succesful\n");
	return true;
}
