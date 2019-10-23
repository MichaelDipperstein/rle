/***************************************************************************
*              Sample Program Using Run Length Encoding Library
*
*   File    : sample.c
*   Purpose : Demonstrate usage of run length encoding library
*   Author  : Michael Dipperstein
*   Date    : April 30, 2004
*
****************************************************************************
*
* SAMPLE: Sample usage of Run Length Encoding Library
* Copyright (C) 2004, 2006-2007, 2015, 2017 by
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
#include <stdlib.h>
#include <errno.h>
#include "optlist/optlist.h"
#include "rle.h"

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
typedef enum
{
    mode_none = 0,
    mode_encode_normal = 1,
    mode_decode_normal = (1 << 1),
    mode_packbits = (1 << 2),
    mode_encode_packbits = (1 << 2) | 1,
    mode_decode_packbits = (1 << 2) | (1 << 1)
} mode_t;

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
static void ShowUsage(const char *progName);

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : main
*   Description: This is the main function for this program, it validates
*                the command line input and, if valid, it will call
*                functions to encode or decode a file using a run length
*                encoding algorithm.
*   Parameters : argc - number of parameters
*                argv - parameter list
*   Effects    : Encodes/Decodes input file
*   Returned   : 0 for success, errno for failure.
***************************************************************************/
int main(int argc, char *argv[])
{
    option_t *optList;
    option_t *thisOpt;
    FILE *inFile;
    FILE *outFile;
    mode_t mode;
    int result;

    /* initialize data */
    inFile = NULL;
    outFile = NULL;
    mode = mode_none;

    /* parse command line */
    optList = GetOptList(argc, argv, "cdvi:o:h?");
    thisOpt = optList;

    while (thisOpt != NULL)
    {
        switch(thisOpt->option)
        {
            case 'c':       /* compression mode */
                mode |= mode_encode_normal;
                break;

            case 'd':       /* decompression mode */
                mode |= mode_decode_normal;
                break;

            case 'v':       /* use packbits variant */
                mode |= mode_packbits;
                break;

            case 'i':       /* input file name */
                if (inFile != NULL)
                {
                    fprintf(stderr, "Multiple input files not allowed.\n");
                    fclose(inFile);

                    if (outFile != NULL)
                    {
                        fclose(outFile);
                    }

                    FreeOptList(optList);
                    return EINVAL;
                }
                else if ((inFile = fopen(thisOpt->argument, "rb")) == NULL)
                {
                    perror("Opening Input File");

                    if (outFile != NULL)
                    {
                        fclose(outFile);
                    }

                    FreeOptList(optList);
                    return errno;
                }
                break;

            case 'o':       /* output file name */
                if (outFile != NULL)
                {
                    fprintf(stderr, "Multiple output files not allowed.\n");
                    fclose(outFile);

                    if (inFile != NULL)
                    {
                        fclose(inFile);
                    }

                    FreeOptList(optList);
                    return EINVAL;
                }
                else if ((outFile = fopen(thisOpt->argument, "wb")) == NULL)
                {
                    perror("Opening Output File");

                    if (inFile != NULL)
                    {
                        fclose(inFile);
                    }

                    FreeOptList(optList);
                    return errno;
                }
                break;

            case 'h':
            case '?':
                ShowUsage(argv[0]);
                FreeOptList(optList);
                return 0;
        }

        optList = thisOpt->next;
        free(thisOpt);
        thisOpt = optList;
    }

    /* validate command line */
    if (inFile == NULL)
    {
        fprintf(stderr, "Input file must be provided\n");
        ShowUsage(argv[0]);

        if (outFile != NULL)
        {
            free(outFile);
        }

        return EINVAL;
    }
    else if (outFile == NULL)
    {
        fprintf(stderr, "Output file must be provided\n");
        ShowUsage(argv[0]);

        if (inFile != NULL)
        {
            free(inFile);
        }

        return EINVAL;
    }

    /* we have valid parameters encode or decode */
    switch (mode)
    {
        case mode_encode_normal:
            result = RleEncodeFile(inFile, outFile);
            break;

        case mode_decode_normal:
            result = RleDecodeFile(inFile, outFile);
            break;

        case mode_encode_packbits:
            result = VPackBitsEncodeFile(inFile, outFile);
            break;

        case mode_decode_packbits:
            result = VPackBitsDecodeFile(inFile, outFile);
            break;

        default:
            fprintf(stderr, "Illegal encoding/decoding option\n");
            ShowUsage(argv[0]);
            result = EINVAL;
    }

    fclose(inFile);
    fclose(outFile);
    return result;
}

/***************************************************************************
*   Function   : ShowUsage
*   Description: This function sends instructions for using this program to
*                stdout.
*   Parameters : progName - the name of the executable version of this
*                           program.
*   Effects    : Usage instructions are sent to stdout.
*   Returned   : None
***************************************************************************/
static void ShowUsage(const char *progName)
{
    printf("Usage: %s <options>\n\n", FindFileName(progName));
    printf("options:\n");
    printf("  -c : Encode input file to output file.\n");
    printf("  -d : Decode input file to output file.\n");
    printf("  -v : Use variant of packbits algorithm.\n");
    printf("  -i <filename> : Name of input file.\n");
    printf("  -o <filename> : Name of output file.\n");
    printf("  -h | ?  : Print out command line options.\n\n");
    printf("Default: sample -c\n");
}
