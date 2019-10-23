/***************************************************************************
*                 Run Length Encoding and Decoding Library
*
*   File    : rle.c
*   Purpose : Use run length coding to compress/decompress files.  The
*             version of encoding used by this library only provides a run
*             length if the last two symbols are matching.  This method
*             avoids the need to include run lengths for runs of only 1
*             symbol.  It also avoids the need for escape characters.
*   Author  : Michael Dipperstein
*   Date    : April 30, 2004
*
****************************************************************************
*
* RLE: An ANSI C Run Length Encoding/Decoding Routines
* Copyright (C) 2004, 2007, 2015 by
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

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <errno.h>

/***************************************************************************
*                                CONSTANTS
***************************************************************************/

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : RleEncodeFile
*   Description: This routine reads an input file and writes out a run
*                length encoded version of that file.
*   Parameters : inFile - Pointer to the file to encode
*                outFile - Pointer to the file to write encoded output to
*   Effects    : File is encoded using RLE
*   Returned   : 0 for success, -1 for failure.  errno will be set in the
*                event of a failure.  Either way, inFile and outFile will
*                be left open.
***************************************************************************/
int RleEncodeFile(FILE *inFile, FILE *outFile)
{
    int currChar;                       /* current characters */
    int prevChar;                       /* previous characters */
    unsigned char count;                /* number of characters in a run */

    /* validate input and output files */
    if ((NULL == inFile) || (NULL == outFile))
    {
        errno = ENOENT;
        return -1;
    }

    /* encode inFile */
    prevChar = EOF;     /* force next char to be different */
    count = 0;

    /* read input until there's nothing left */
    while ((currChar = fgetc(inFile)) != EOF)
    {
        fputc(currChar, outFile);

        /* check for run */
        if (currChar == prevChar)
        {
            /* we have a run.  count run length */
            count = 0;

            while ((currChar = fgetc(inFile)) != EOF)
            {
                if (currChar == prevChar)
                {
                    count++;

                    if (count == UCHAR_MAX)
                    {
                        /* count is as long as it can get */
                        fputc(count, outFile);

                        /* force next char to be different */
                        prevChar = EOF;
                        break;
                    }
                }
                else
                {
                    /* run ended */
                    fputc(count, outFile);
                    fputc(currChar, outFile);
                    prevChar = currChar;
                    break;
                }
            }
        }
        else
        {
            /* no run */
            prevChar = currChar;
        }

        if (currChar == EOF)
        {
            /* run ended because of EOF */
            fputc(count, outFile);
            break;
        }
    }

    return 0;
}

/***************************************************************************
*   Function   : RleDecodeFile
*   Description: This routine opens a run length encoded file, and decodes
*                it to an output file.
*   Parameters : inFile - Pointer to the file to decode
*                outFile - Pointer to the file to write decoded output to
*   Effects    : Encoded file is decoded
*   Returned   : 0 for success, -1 for failure.  errno will be set in the
*                event of a failure.  Either way, inFile and outFile will
*                be left open.
***************************************************************************/
int RleDecodeFile(FILE *inFile, FILE *outFile)
{
    int currChar;                       /* current characters */
    int prevChar;                       /* previous characters */
    unsigned char count;                /* number of characters in a run */

    /* validate input and output files */
    if ((NULL == inFile) || (NULL == outFile))
    {
        errno = ENOENT;
        return -1;
    }

    /* decode inFile */
    prevChar = EOF;     /* force next char to be different */

    /* read input until there's nothing left */
    while ((currChar = fgetc(inFile)) != EOF)
    {
        fputc(currChar, outFile);

        /* check for run */
        if (currChar == prevChar)
        {
            /* we have a run.  write it out. */
            count = fgetc(inFile);
            while (count > 0)
            {
                fputc(currChar, outFile);
                count--;
            }

            prevChar = EOF;     /* force next char to be different */
        }
        else
        {
            /* no run */
            prevChar = currChar;
        }
    }

    return 0;
}
