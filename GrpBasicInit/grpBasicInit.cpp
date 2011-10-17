#include "grpBasicInit.h"
#include "disableCompletely_r10b.h"


GrpBasicInit::GrpBasicInit(size_t grpNum, SpecRev specRev, int fd) :
    Group(grpNum, specRev, "Basic Initialization")
{
    // IMPORTANT: Once a test case is assigned a position in the vector, i.e.
    //            a test index/number of the form major.minor, then it should
    //            reside in that position forever so test reference numbers
    //            don't change per release. Future tests can be appended at
    //            either the group level or the test level.
    //            Tests 0.0, 1.0, <next_test_num=2>.0  Major num; group level
    //            Tests x.0, x.1, x.<next_test_num=2>  Minor num; test level
    switch (mSpecRev) {
    case SPECREV_10b:
        APPEND_TEST_AT_GROUP_LEVEL(DisableCompletely_r10b, fd)
        break;

    default:
    case SPECREVTYPE_FENCE:
        LOG_DBG("Object created with an unknown SpecRev=%d", specRev);
        break;
    }
}


GrpBasicInit::~GrpBasicInit()
{
    // mTests deallocated in parent
}