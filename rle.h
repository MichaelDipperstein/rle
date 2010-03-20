/***************************************************************************
*            Header for Run Length Encoding and Decoding Library
*
*   File    : rle.h
*   Purpose : Provides prototypes for functions that use run length coding
*             to encode/decode files.
*   Author  : Michael Dipperstein
*   Date    : April 30, 2004
*
****************************************************************************
*   UPDATES
*
*   $Id: rle.h,v 1.1.1.1 2004/05/03 03:56:49 michael Exp $
*   $Log: rle.h,v $
*   Revision 1.1.1.1  2004/05/03 03:56:49  michael
*   Initial version
*
*
****************************************************************************
*
* RLE: An ANSI C Run Length Encoding/Decoding Routines
* Copyright (C) 2004 by Michael Dipperstein (mdipper@cs.ucsb.edu)
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
***************************************************************************/

#ifndef _RLE_H_
#define _RLE_H_

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
int RleEncodeFile(char *inFile, char *outFile);	/* encode inFile */
int RleDecodeFile(char *inFile, char *outFile);	/* decode inFile*/

#endif  /* ndef _RLE_H_ */
