/***************************************************************************
                          datafile.h  -  Files being controlled by filecontrol
                             -------------------
    begin                : do mei 1 2003
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

#ifndef DATAFILE_H
#define DATAFILE_H

#include "cfile.h"

/**
  *@author CJP
  */

class CDataFile : public CFile
{
public:
	CDataFile(CString filename, bool write=false);
	CDataFile();
	virtual ~CDataFile();

	virtual bool open(CString filename, bool write=false);

	CString useExtern();
};

CString getShortName(const CString &longname);

vector<CString> getDataDirContents(const CString &dir, const CString &ext = "");

bool dataFileExists(const CString &filename, bool onlyLocal = false); //may cause automatic download from server
bool deleteDataFile(const CString &filename); //only deletes in save directory
bool copyDataFile(const CString &source, const CString &destination, bool srcIsData=true, bool dstIsData=true);

#endif
