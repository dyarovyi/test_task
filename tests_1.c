#include "test_task_1.c"

const U32 absoluteStart = 0x00E00000;
const U32 absoluteEnd = 0x00FFFFFF;

void test_invalid_offset_outside_of_event_log()
{
    // Tests whether offset exists outside of boundaries of event log

    S_DFM_LOG_STATUS LogStatus = {
        .absoluteStart = absoluteStart,
        .absoluteEnd = absoluteEnd,
        .startOffset = 0x00E00000,
        .endOffset = 0x00FFFFFF,
        .recordSize = 0x00200000
    };

    U32 test_offset = 0x00000000;
    BOOLEAN expected_result = FALSE;
    BOOLEAN actual_result = dfm_IsOffsetValid(&LogStatus, test_offset);
    assert(expected_result == actual_result);
}

void test_invalid_offset_outside_of_data()
{
    // Tests whether offset exists outside of where data exists in event log

    S_DFM_LOG_STATUS LogStatus = {
        .absoluteStart = absoluteStart,
        .absoluteEnd = absoluteEnd,
        .startOffset = 0x00E00FFF,
        .endOffset = 0x00DDFFFF,
        .recordSize = 0x00200000
    };

    U32 test_offset = 0x00E0000F;
    BOOLEAN expected_result = FALSE;
    BOOLEAN actual_result = dfm_IsOffsetValid(&LogStatus, test_offset);
    assert(expected_result == actual_result);
}

void test_invalid_offset_outside_of_data_wrapped()
{
    // Tests whether offset exists outside of where data exists in event log that has wrapped

    S_DFM_LOG_STATUS LogStatus = {
        .absoluteStart = absoluteStart,
        .absoluteEnd = absoluteEnd,
        .startOffset = 0x00EDFFFF,
        .endOffset = 0x00D00FFF,
        .recordSize = 0x00200000
    };

    U32 test_offset = 0x00E0000F;
    BOOLEAN expected_result = FALSE;
    BOOLEAN actual_result = dfm_IsOffsetValid(&LogStatus, test_offset);
    assert(expected_result == actual_result);
}

void test_invalid_event_log_empty()
{
    // Tests whether log is empty, but markers exist outside this

    S_DFM_LOG_STATUS LogStatus = {
        .absoluteStart = absoluteStart,
        .absoluteEnd = absoluteEnd,
        .startOffset = 0x00D00FFF,
        .endOffset = 0x00D00FFF,
        .recordSize = 0x00200000
    };

    U32 test_offset = 0x00EDDDDF;
    BOOLEAN expected_result = FALSE;
    BOOLEAN actual_result = dfm_IsOffsetValid(&LogStatus, test_offset);
    assert(expected_result == actual_result);
}

void test_valid()
{
    // Tests whether offset exists with all boundaries

    S_DFM_LOG_STATUS LogStatus = {
        .absoluteStart = absoluteStart,
        .absoluteEnd = absoluteEnd,
        .startOffset = 0x00E00000,
        .endOffset = 0x00FFFFFF,
        .recordSize = 0x00200000
    };

    U32 test_offset = 0x00E00000;
    BOOLEAN expected_result = TRUE;
    BOOLEAN actual_result = dfm_IsOffsetValid(&LogStatus, test_offset);
    assert(expected_result == actual_result);
}

int main()
{
    test_invalid_offset_outside_of_event_log();
    test_invalid_offset_outside_of_data();
    test_invalid_offset_outside_of_data_wrapped();
    test_invalid_event_log_empty();
    test_valid();
    return 0;
}