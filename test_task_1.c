//! Declare standard types
typedef unsigned char           BOOLEAN;//!< type for booleans
typedef unsigned char           U8;     //!< type for 8 bit unsigned integers
typedef signed char             S8;     //!< type for 8 bit signed integers
typedef char                    CHAR;   //!< ASCII-Character (8 bit)
typedef unsigned short          U16;    //!< type for 16 bit unsigned integers
typedef signed short            S16;    //!< type for 16 bit signed integers
typedef unsigned long           U32;    //!< type for 32 bit unsigned integers

//****************************************************************************
//! Structure to define an Event Log's status data
//***************************************************************************
typedef struct
{
        U32 startOffset; //!< Address offset where the first Event Record exists
        U32 endOffset; //!< Address offset where the next Event Record shall be written to
        U32 absoluteStart; //!< Address offset for the lower boundary of the Event Log
        U32 absoluteEnd; //!< Address offset for the upper boundary of the Event Log
        U32 recordSize; //!< Size of a single Event Record
} S_DFM_LOG_STATUS;

// Function dfm_IsOffsetValid **********************************************
//!
//! Checks whether a given offset is within the bounds of the Event Log.
//!
//! @param[in] logStatus  Pointer to the Event Log's status data
//! @param[in] offset    Offset address to validate
//!
//! @return Validation result
//! @retval TRUE    Offset is valid
//! @retval FALSE   Offset is invalid
//***************************************************************************

#include <assert.h>

BOOLEAN TRUE = '1';
BOOLEAN FALSE = '0';

static BOOLEAN dfm_IsOffsetValid( const S_DFM_LOG_STATUS* const logStatus,
    const U32 offset )
{
    BOOLEAN isValid = FALSE;

    if ( ( offset <  logStatus->absoluteStart ) ||
         ( offset >= logStatus->absoluteEnd )    )
    {
        // Offset exists outside of boundaries of event log
        isValid = FALSE;
    }
    else if( ( logStatus->startOffset < logStatus->endOffset ) &&
             ( ( offset < logStatus->startOffset )             ||
             ( offset > logStatus->endOffset ) )                )
    {
        // Offset exists outside of where data exists in event log
        isValid = FALSE;
    }
    else if( ( logStatus->startOffset > logStatus->endOffset ) &&
             ( offset < logStatus->startOffset )               &&
             ( offset > logStatus->endOffset )                  )
    {
        // Offset exists outside of where data exists in event log that has wrapped
        isValid = FALSE;
    }
    else if( ( logStatus->startOffset == logStatus->endOffset ) &&
             ( offset != logStatus->startOffset )                )
    {
        // Log is empty, but markers exist outside this
        isValid = FALSE;
    }
    else
    {
        // Offset exists with all boundaries
        isValid = TRUE;
    }

    return isValid;
}