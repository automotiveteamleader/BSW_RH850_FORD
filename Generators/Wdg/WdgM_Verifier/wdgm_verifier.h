/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  wdgm_verifier.h
 *        \brief  wdgm_verifier header file
 *
 *      \details  This is the header file of WdgMVerifier
 *
 *********************************************************************************************************************/

#ifndef _WDGM_VERIFIER_H_
#define _WDGM_VERIFIER_H_

#include "wdgm_verifier_types.h"
#include "wdgm_verifier_version.h"

/* begin of DLL boilerplate code */
#ifdef __WIN32__
    #ifdef BUILD_DLL
        // the dll exports
        #define EXPORT __declspec(dllexport)
    #else
        // the exe imports
        #define EXPORT __declspec(dllimport)
    #endif
#endif
/* end of DLL boilerplate code */

EXPORT int verify
    ( const WdgM_ConfigType        * main_struct
    , const verifier_main_struct_t * verifier_info
    );

EXPORT void print_WdgMVerifier_version( );


#endif  /* _WDGM_VERIFIER_H_ */

