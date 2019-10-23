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
*
* RLE: An ANSI C Run Length Encoding/Decoding Routines
* Copyright (C) 2004, 2006-2007, 2015 by
*       Michael Dipperstein (mdipperstein@gmail.com)
*
* This file is part of the RLE library.
*
* The RLE library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation; either version 3 of the License, or (at
* your option) any later version.
*
* The RLE library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
* General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

#ifndef _RLE_H_
#define _RLE_H_

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/

/* traditional RLE encodeing/decoding */
int RleEncodeFile(FILE *inFile, FILE *outFile);
int RleDecodeFile(FILE *inFile, FILE *outFile);

/* variant of packbits RLE encodeing/decoding */
int VPackBitsEncodeFile(FILE *inFile, FILE *outFile);
int VPackBitsDecodeFile(FILE *inFile, FILE *outFile);

#endif  /* ndef _RLE_H_ */
