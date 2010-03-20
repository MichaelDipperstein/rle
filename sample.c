/***************************************************************************
*              Sample Program Using Run Length Encoding Library
*
*   File    : sample.c
*   Purpose : Demonstrate usage of run length encoding library
*   Author  : Michael Dipperstein
*   Date    : April 30, 2004
*
****************************************************************************
*   UPDATES
*
*   $Id: sample.c,v 1.2 2006/09/10 05:11:22 michael Exp $
*   $Log: sample.c,v $
*   Revision 1.2  2006/09/10 05:11:22  michael
*   Add sample usage for variant packbits functions.
*
*   Revision 1.1.1.1  2004/05/03 03:56:49  michael
*   Initial version
*
*
****************************************************************************
*
* SAMPLE: Sample usage of Run Length Encoding Library
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

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getopt.h"
#include "rle.h"

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
typedef enum
{
    ENCODE,
    DECODE
} MODES;

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
char *RemovePath(char *fullPath);

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/****************************************************************************
*   Function   : main
*   Description: This is the main function for this program, it validates
*                the command line input and, if valid, it will call
*                functions to encode or decode a file using a run length
*                encoding algorithm.
*   Parameters : argc - number of parameters
*                argv - parameter list
*   Effects    : Encodes/Decodes input file
*   Returned   : EXIT_SUCCESS for success, otherwise EXIT_FAILURE.
****************************************************************************/
int main(int argc, char *argv[])
{
    int opt;
    char *inFile, *outFile;  /* name of input & output files */
    MODES mode;
    unsigned char usePackBits;

    /* initialize data */
    inFile = NULL;
    outFile = NULL;
    mode = ENCODE;
    usePackBits = 0;

    /* parse command line */
    while ((opt = getopt(argc, argv, "cdvi:o:h?")) != -1)
    {
        switch(opt)
        {
            case 'c':       /* compression mode */
                mode = ENCODE;
                break;

            case 'd':       /* decompression mode */
                mode = DECODE;
                break;

            case 'v':       /* use packbits variant */
                usePackBits = 1;
                break;

            case 'i':       /* input file name */
                if (inFile != NULL)
                {
                    fprintf(stderr, "Multiple input files not allowed.\n");
                    free(inFile);

                    if (outFile != NULL)
                    {
                        free(outFile);
                    }

                    exit(EXIT_FAILURE);
                }
                else if ((inFile = (char *)malloc(strlen(optarg) + 1)) == NULL)
                {
                    perror("Memory allocation");

                    if (outFile != NULL)
                    {
                        free(outFile);
                    }

                    exit(EXIT_FAILURE);
                }

                strcpy(inFile, optarg);
                break;

            case 'o':       /* output file name */
                if (outFile != NULL)
                {
                    fprintf(stderr, "Multiple output files not allowed.\n");
                    free(outFile);

                    if (inFile != NULL)
                    {
                        free(inFile);
                    }

                    exit(EXIT_FAILURE);
                }
                else if ((outFile = (char *)malloc(strlen(optarg) + 1)) == NULL)
                {
                    perror("Memory allocation");

                    if (inFile != NULL)
                    {
                        free(inFile);
                    }

                    exit(EXIT_FAILURE);
                }

                strcpy(outFile, optarg);
                break;

            case 'h':
            case '?':
                printf("Usage: %s <options>\n\n", RemovePath(argv[0]));
                printf("options:\n");
                printf("  -c : Encode input file to output file.\n");
                printf("  -d : Decode input file to output file.\n");
                printf("  -v : Use variant of packbits algorithm.\n");
                printf("  -i <filename> : Name of input file.\n");
                printf("  -o <filename> : Name of output file.\n");
                printf("  -h | ?  : Print out command line options.\n\n");
                printf("Default: sample -c\n");
                return(EXIT_SUCCESS);
        }
    }

    /* validate command line */
    if (inFile == NULL)
    {
        fprintf(stderr, "Input file must be provided\n");
        fprintf(stderr, "Enter \"sample -?\" for help.\n");

        if (outFile != NULL)
        {
            free(outFile);
        }

        exit (EXIT_FAILURE);
    }
    else if (outFile == NULL)
    {
        fprintf(stderr, "Output file must be provided\n");
        fprintf(stderr, "Enter \"sample -?\" for help.\n");

        if (inFile != NULL)
        {
            free(inFile);
        }

        exit (EXIT_FAILURE);
    }

    /* we have valid parameters encode or decode */
    if (mode == ENCODE)
    {
        if (usePackBits)
        {
            VPackBitsEncodeFile(inFile, outFile);
        }
        else
        {
            RleEncodeFile(inFile, outFile);
        }
    }
    else
    {
        if (usePackBits)
        {
            VPackBitsDecodeFile(inFile, outFile);
        }
        else
        {
            RleDecodeFile(inFile, outFile);
        }
    }

    free(inFile);
    free(outFile);
    return EXIT_SUCCESS;
}

/****************************************************************************
*   Function   : RemovePath
*   Description: This is function accepts a pointer to the name of a file
*                along with path information and returns a pointer to the
*                character that is not part of the path.
*   Parameters : fullPath - pointer to an array of characters containing
*                           a file name and possible path modifiers.
*   Effects    : None
*   Returned   : Returns a pointer to the first character after any path
*                information.
****************************************************************************/
char *RemovePath(char *fullPath)
{
    int i;
    char *start, *tmp;                          /* start of file name */
    const char delim[3] = {'\\', '/', ':'};     /* path deliminators */

    start = fullPath;

    /* find the first character after all file path delimiters */
    for (i = 0; i < 3; i++)
    {
        tmp = strrchr(start, delim[i]);

        if (tmp != NULL)
        {
            start = tmp + 1;
        }
    }

    return start;
}
