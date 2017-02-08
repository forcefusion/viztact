/**
* This file is autogenerated by nRFgo Studio 1.21.2RC1.4
*/

#ifndef SETUP_MESSAGES_H__
#define SETUP_MESSAGES_H__

#include "hal_platform.h"
#include "aci.h"

// You have now chosen to upload the configuration to OTP on the device.
// This will result in a device that you can not modify afterwards. If this is your intention,
// remove this comment and the #error below
#error Generating configuration for OTP. Please verify usage by removing this error message from include file.

#define SETUP_ID 1100
#define SETUP_FORMAT 3 /** nRF8001 D */
#define ACI_DYNAMIC_DATA_SIZE 155

/* Service: Gap - Characteristic: Device name - Pipe: SET */
#define PIPE_GAP_DEVICE_NAME_SET          1
#define PIPE_GAP_DEVICE_NAME_SET_MAX_SIZE 12

/* Service: Device Information - Characteristic: Hardware Revision String - Pipe: SET */
#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET          2
#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET_MAX_SIZE 2

/* Service: HID Service - Characteristic: HID Control Point - Pipe: RX */
#define PIPE_HID_SERVICE_HID_CONTROL_POINT_RX          3
#define PIPE_HID_SERVICE_HID_CONTROL_POINT_RX_MAX_SIZE 1

/* Service: HID Service - Characteristic: HID Report - Pipe: TX */
#define PIPE_HID_SERVICE_HID_REPORT_TX          4
#define PIPE_HID_SERVICE_HID_REPORT_TX_MAX_SIZE 16

/* Service: HID Service - Characteristic: HID Report - Pipe: SET */
#define PIPE_HID_SERVICE_HID_REPORT_SET          5
#define PIPE_HID_SERVICE_HID_REPORT_SET_MAX_SIZE 16


#define NUMBER_OF_PIPES 5

#define SERVICES_PIPE_TYPE_MAPPING_CONTENT {\
  {ACI_STORE_LOCAL, ACI_SET},   \
  {ACI_STORE_LOCAL, ACI_SET},   \
  {ACI_STORE_LOCAL, ACI_RX},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_SET},   \
}

#define GAP_PPCP_MAX_CONN_INT 0x10 /**< Maximum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_MIN_CONN_INT  0x6 /**< Minimum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_SLAVE_LATENCY 25
#define GAP_PPCP_CONN_TIMEOUT 0x12c /** Connection Supervision timeout multiplier as a multiple of 10msec, 0xFFFF means no specific value requested */

#define NB_SETUP_MESSAGES 27
#define SETUP_MESSAGES_CONTENT {\
    {0x00,\
        {\
            0x07,0x06,0x00,0x00,0x03,0x02,0x42,0x07,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x00,0x4c,0x04,0x00,0x00,0x02,0x00,0x04,0x00,0x05,0x01,0x01,0x00,0x00,0x06,0x00,0x00,\
            0x81,0x12,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x03,0x99,0x00,0xff,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x38,0xff,0xff,0x02,0x58,0x0a,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x05,0x06,0x10,0x54,0x01,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x00,0x04,0x04,0x02,0x02,0x00,0x01,0x28,0x00,0x01,0x00,0x18,0x04,0x04,0x05,0x05,0x00,\
            0x02,0x28,0x03,0x01,0x0e,0x03,0x00,0x00,0x2a,0x04,0x34,0x0c,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x1c,0x0c,0x00,0x03,0x2a,0x00,0x01,0x46,0x75,0x73,0x69,0x6f,0x6e,0x20,0x42,0x6f,0x61,\
            0x72,0x64,0x04,0x04,0x05,0x05,0x00,0x04,0x28,0x03,0x01,0x02,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x38,0x05,0x00,0x01,0x2a,0x06,0x04,0x03,0x02,0x00,0x05,0x2a,0x01,0x01,0xc0,0x03,0x04,\
            0x04,0x05,0x05,0x00,0x06,0x28,0x03,0x01,0x02,0x07,0x00,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x54,0x2a,0x06,0x04,0x09,0x08,0x00,0x07,0x2a,0x04,0x01,0x06,0x00,0x10,0x00,0x19,0x00,\
            0x2c,0x01,0x04,0x04,0x02,0x02,0x00,0x08,0x28,0x00,0x01,0x01,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x70,0x18,0x04,0x04,0x02,0x02,0x00,0x09,0x28,0x00,0x01,0x0a,0x18,0x04,0x04,0x05,0x05,\
            0x00,0x0a,0x28,0x03,0x01,0x02,0x0b,0x00,0x27,0x2a,0x06,0x0c,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x8c,0x03,0x02,0x00,0x0b,0x2a,0x27,0x01,0x00,0x00,0x04,0x04,0x05,0x05,0x00,0x0c,0x28,\
            0x03,0x01,0x02,0x0d,0x00,0x50,0x2a,0x06,0x0c,0x08,0x07,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xa8,0x0d,0x2a,0x50,0x01,0x2f,0x30,0x54,0x13,0x3d,0x6e,0xed,0x04,0x04,0x02,0x02,0x00,\
            0x0e,0x28,0x00,0x01,0x12,0x18,0x04,0x04,0x05,0x05,0x00,0x0f,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xc4,0x28,0x03,0x01,0x02,0x10,0x00,0x4a,0x2a,0x06,0x0c,0x05,0x04,0x00,0x10,0x2a,0x4a,\
            0x01,0x11,0x01,0x00,0x03,0x04,0x04,0x05,0x05,0x00,0x11,0x28,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xe0,0x03,0x01,0x04,0x12,0x00,0x4c,0x2a,0x46,0x30,0x02,0x01,0x00,0x12,0x2a,0x4c,0x01,\
            0x00,0x04,0x04,0x05,0x05,0x00,0x13,0x28,0x03,0x01,0x02,0x14,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xfc,0x00,0x4b,0x2a,0x06,0x0c,0x9c,0x9b,0x00,0x14,0x2a,0x4b,0x01,0x05,0x0d,0x09,0x04,\
            0xa1,0x01,0x85,0x01,0x09,0x22,0xa1,0x02,0x09,0x42,0x15,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x18,0x25,0x01,0x75,0x01,0x95,0x01,0x81,0x02,0x09,0x32,0x81,0x02,0x09,0x47,0x81,0x02,\
            0x95,0x05,0x81,0x03,0x75,0x08,0x09,0x51,0x95,0x01,0x81,0x02,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x34,0x05,0x01,0x26,0xff,0x7f,0x75,0x10,0x55,0x00,0x65,0x00,0x09,0x30,0x35,0x00,0x46,\
            0x00,0x00,0x81,0x02,0x09,0x31,0x46,0x00,0x00,0x81,0x02,0xc0,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x50,0xa1,0x02,0x05,0x0d,0x09,0x42,0x15,0x00,0x25,0x01,0x75,0x01,0x95,0x01,0x81,0x02,\
            0x09,0x32,0x81,0x02,0x09,0x47,0x81,0x02,0x95,0x05,0x81,0x03,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x6c,0x75,0x08,0x09,0x51,0x95,0x01,0x81,0x02,0x05,0x01,0x26,0xff,0x7f,0x75,0x10,0x55,\
            0x00,0x65,0x00,0x09,0x30,0x35,0x00,0x46,0x00,0x00,0x81,0x02,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x88,0x09,0x31,0x46,0x00,0x00,0x81,0x02,0xc0,0x05,0x0d,0x09,0x54,0x95,0x01,0x75,0x08,\
            0x15,0x00,0x25,0x08,0x81,0x02,0x09,0x55,0xb1,0x02,0xc0,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xa4,0x04,0x05,0x05,0x00,0x15,0x28,0x03,0x01,0x12,0x16,0x00,0x4d,0x2a,0x14,0x0c,0x10,\
            0x00,0x00,0x16,0x2a,0x4d,0x01,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x34,0x03,0x02,0x00,0x17,\
            0x29,0x02,0x01,0x00,0x00,0x06,0x0c,0x03,0x02,0x00,0x18,0x29,\
        },\
    },\
    {0x00,\
        {\
            0x08,0x06,0x21,0xdc,0x08,0x01,0x01,0x01,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x00,0x2a,0x00,0x01,0x00,0x80,0x04,0x00,0x03,0x00,0x00,0x2a,0x27,0x01,0x00,0x80,0x04,\
            0x00,0x0b,0x00,0x00,0x2a,0x4c,0x01,0x00,0x08,0x04,0x00,0x12,\
        },\
    },\
    {0x00,\
        {\
            0x0f,0x06,0x40,0x1c,0x00,0x00,0x2a,0x4d,0x01,0x00,0x82,0x04,0x00,0x16,0x00,0x17,\
        },\
    },\
    {0x00,\
        {\
            0x0f,0x06,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x06,0x06,0xf0,0x00,0x83,0xdf,0xd8,\
        },\
    },\
}

#endif
