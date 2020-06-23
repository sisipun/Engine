#include "input_memory_stream.h"

void InputMemoryStream::Read(void *outData, uint32_t inByteCount) {
    uint32_t readBytesCount = inByteCount;
    if (mHead + inByteCount > mCapacity)
    {
        readBytesCount = mCapacity - mHead;
    }

    std::memcpy(outData, mBuffer + mHead, readBytesCount);

    mHead += readBytesCount;
}