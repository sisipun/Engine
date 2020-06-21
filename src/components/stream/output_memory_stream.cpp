#include "output_memory_stream.h"
#include <algorithm>

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
    mBuffer = static_cast<char *>(std::realloc(mBuffer, inNewLength));
    mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void *inData, uint32_t inByteCount)
{
    uint32_t resultHead = mHead + inByteCount;
    if (resultHead > mCapacity)
    {
        ReallocBuffer(std::max(mCapacity * 2, resultHead));
    }

    std::memcpy(mBuffer + mHead, inData, inByteCount);

    mHead = resultHead;
}
