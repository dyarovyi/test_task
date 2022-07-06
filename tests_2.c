#include "test_task_2.c"

const U32 absoluteStart = 0x00A00000;
const U32 absoluteEnd = 0x00DFFFFF;

void test_end_greater_start()
{
    const U32 start = 0x00E000FF;
    const U32 end = 0x00FFEEEE;
    const U32 recordSize = 0x00400000;

    U32 expected_result = 0x00000000;
    U32 actual_result = dfm_CalculateRecordCount(start, end, absoluteStart, absoluteEnd, recordSize);

    assert(expected_result == actual_result);
}

void test_end_equal_start()
{
    const U32 start = 0x00FFEEEE;
    const U32 end = 0x00FFEEEE;
    const U32 recordSize = 0x00400000;

    U32 expected_result = 0x00000000;
    U32 actual_result = dfm_CalculateRecordCount(start, end, absoluteStart, absoluteEnd, recordSize);

    assert(expected_result == actual_result);
}

void test_end_less_start()
{
    const U32 start = 0x00F0AAAA;
    const U32 end = 0x00E0DDAA;
    const U32 recordSize = 0x00400000;

    U32 expected_result = 0x00000000;
    U32 actual_result = dfm_CalculateRecordCount(start, end, absoluteStart, absoluteEnd, recordSize);

    assert(expected_result == actual_result);
}

int main()
{
    test_end_greater_start();
    test_end_equal_start();
    test_end_less_start();
    return 0;
}