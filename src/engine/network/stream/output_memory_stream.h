#ifndef OUTPUT_MEMORY_STREAM_H
#define OUTPUT_MEMORY_STREAM_H

#include <memory>

class OutputMemoryStream
{
public:
    OutputMemoryStream() : mBuffer(nullptr), mHead(0), mCapacity(0)
    {
        ReallocBuffer(32);
    }
    ~OutputMemoryStream()
    {
        std::free(mBuffer);
    }

    const char *GetBufferPtr() const
    {
        return mBuffer;
    }

    void Write(const void *inData, uint32_t inByteCount);
    void Write(uint32_t inData)
    {
        Write(&inData, sizeof(inData));
    }
    void Write(int32_t inData)
    {
        Write(&inData, sizeof(inData));
    }

private:
    void ReallocBuffer(uint32_t inNewLength);

    char *mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;
};

#endif