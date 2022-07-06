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

// Function dfm_CalculateRecordCount ****************************************
//!
//! Calculates the number of records based on positioning of start & end markers.
//!
//! @param[in] start             The address of where the records start
//! @param[in] end               The address of where the records end
//! @param[in] absoluteStart     The address of the start of the log
//! @param[in] absoluteEnd       The address of the start of the log
//! @param[in] recordSize        Record Size
//!
//! @return Record count
//***************************************************************************

#include <assert.h>

BOOLEAN TRUE = '1';
BOOLEAN FALSE = '0';

static U32 dfm_CalculateRecordCount( const U32 start,
                                     const U32 end,
                                     const U32 absoluteStart,
                                     const U32 absoluteEnd,
                                     const U32 recordSize )
{
    U32 recordCount = 0uL;
    U32 blockSizeStart = 0uL;
    U32 blockSizeEnd = 0uL;

    if( end >= start )
    {
        recordCount = ( end - start ) / recordSize;
    }
    else
    {
        blockSizeStart = end - absoluteStart;
        blockSizeEnd = absoluteEnd - start;
        recordCount = ( blockSizeStart + blockSizeEnd ) / recordSize;
    }

    return recordCount;
}