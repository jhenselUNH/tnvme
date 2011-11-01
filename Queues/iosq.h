#ifndef _IOSQ_H_
#define _IOSQ_H_

#include "sq.h"

class IOSQ;    // forward definition
typedef boost::shared_ptr<IOSQ>        SharedIOSQPtr;
#define CAST_TO_IOSQP(shared_trackable_ptr)  \
        boost::shared_polymorphic_downcast<IOSQ>(shared_trackable_ptr)


/**
* This class is meant to be instantiated and represents an IOSQ. After
* instantiation the Init() methods must be called to attain something useful.
*
* @note This class may throw exceptions.
*/
class IOSQ : public SQ
{
public:
    /**
     * @param fd Pass the opened file descriptor for the device under test
     */
    IOSQ(int fd);
    virtual ~IOSQ();

    /// Used to compare for NULL pointers being returned by allocations
    static SharedIOSQPtr NullIOSQPtr;

    uint8_t GetPriority() { return mPriority; }

    /**
     * Initialize this object and allocates contiguous Q content memory.
     * @param qId Pass the queue's ID
     * @param numEntries Pass the number of elements within the Q
     * @param cqId Pass the assoc CQ ID to which this SQ will be associated
     * @param priority Pass this Q's priority value, must be a 2 bit value
     */
    void Init(uint16_t qId, uint16_t numEntries, uint16_t cqId,
        uint8_t priority);

    /**
     * Initialize this object and allocates discontiguous Q content memory.
     * @param qId Pass the queue's ID
     * @param numEntries Pass the number of elements within the Q
     * @param memBuffer Hand off this Q's memory. It must satisfy
     *      MemBuffer.GetBufSize()>=(numEntries * entrySize). It must only ever
     *      be accessed as RO. Writing to this buffer will have unpredictable
     *      results. It will also become owned by this object, it won't have to
     *      be explicitly deleted when this object goes out of scope.
     * @param cqId Pass the assoc CQ ID to which this SQ will be associated
     * @param priority Pass this Q's priority value, must be a 2 bit value
     */
    void Init(uint16_t qId, uint16_t numEntries, SharedMemBufferPtr memBuffer,
        uint16_t cqId, uint8_t priority);


private:
    IOSQ();

    uint8_t mPriority;
};


#endif