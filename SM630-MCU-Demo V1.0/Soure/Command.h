//
//20070801
//Yang
#define C_GET_OK                0x01//
#define C_GET_FAIL              0x02//

#define C_ADD_FINGER            0x40//
#define C_DEL_FINGER            0x42//
#define C_SEARCH_FINGER         0x44//
#define C_EMPTY_FINGER          0x46//
#define C_READ_INFO             0x4B//

#define C_DOWN_TEMPLET          0x50//
#define C_UP_TEMPLET            0x52//

#define C_READ_ID               0x60//
#define C_READ_FLASH            0x62//
#define C_WRITE_FLASH           0x64//


#define C_READ_IDENTIFIER	0x80//


#define C_COMMAND               0x10//
#define C_DATA                  0x20//
#define C_END_DATA              0x21//
#define C_ANSWER                0x30//


#define ANSWER_OK               0x31//
#define ANSWER_DETECT           0x32//
#define ANSWER_OUT_TIME         0x33//
#define ANSWER_FAIL             0x34//
#define ANSWER_NUMBER_E         0x35//
#define ANSWER_NO_SEARCHED      0x36//
#define ANSWER_HAVE_FINGER      0x37//
#define ANSWER_NO_FINGER        0x38//
#define ANSWER_SEARCH_OK        0x39//
#define ANSWER_SEARCH_FAIL      0x3A//