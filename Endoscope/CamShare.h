///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// AUTHOR:        jorgo(wuhua@tsdt.net) 
//				  Ezio(jorgo@163.com) on 2012-5-11
// COPYRIGHT:     Tucsen Imaging Technology Co.,ltd
//                (www.tsdt.net). All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef __CAM_SHARE_H
#define __CAM_SHARE_H
#define LMOVE(i) (1<<(i))
#define DEPTH_8U     8
#define DEPTH_10U	10
#define DEPTH_12U	12
#define DEPTH_14U	14
#define DEPTH_16U   16
#define IMG_GRAY	1
#define IMG_BGR     3
#define IMG_AYUV	4
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
	
//return code	
enum {
	READ_ONLY		=-9,
	TIME_OUT		=-8,
	NO_MEMORY		=-7,
	NO_PERMISSION   =-6,
	NO_SUPPORT		=-4,
	NO_SUCCEED		=-3,
	NO_RANGE		=-2,
	NO_CAMERA       =-1,
	NO_FAIL         = 0,
	ACTIVE_EXTERNAL = 1,
};	

enum DEV_INTERFACE{
	INTER_USB = 0x1000,		// USB
	INTER_CL = 0x2000,		// Cameralink
	INTER_GIGE = 0x4000,	// GigE
	INTER_CXP = 0x8000,		// Coaxpress
};

struct _DESCRIPTOR {//descriptor
	// hardware
	uint devVersion;
	ushort idVendor;/*  vendor ID */
	ushort idProduct; /* product ID */
	ushort devInterface;
	ushort speed;/** A value of 0x0200 indicates USB 2.0, etc. */
	char *name;
	// software
	uint sdkVersion;
	uchar id;
	uchar format;
	uchar channel;
	uint memSize;
};

enum { //MASK_STATE
	S_DEAD = 0x00,	// close state
	S_LIVE = 0x01,	// active state
};


enum {// element
	// open commend
	SW_CON = 1,		// contrast
	SW_AET,			// target of auto exposure
	SW_FMT,			// format of picture
	SW_LV0,	// deprecated
	SW_LV1,	// deprecated
	SW_LV2,	// deprecated
	SW_GM0,			// gamma of first channel
	SW_GM1,	// deprecated
	SW_GM2,	// deprecated
	SW_SAP = 10,	// sharp
	SW_DNS,			// denoise
	SW_FLP,			// flip
	SW_CTT,			// color temperature
	SW_SAT,			// saturation 
	SW_MON,			// monochrome
	SW_DG0,			// digital gain of first channel
	SW_DG1,			// digital gain of second channel
	SW_DG2,			// digital gain of third channel

	FW_HEX,			// attribute:histogram equalization
	FW_RES = 20,	// Resolution
	FW_CLK,			// pixel clock
	FW_DEP,			// depth bit
	FW_BLK,			// black level
	FW_FST,			// filter state
	FW_FDN,			// filter down
	FW_FUP,			// filter up
	FW_SPE,			// hdr slope(k)
	FW_AGN,			// analog gain
	FW_LTM,			// low(0~15bit) time
	FW_HTM = 30,	// high(16~31bit) time
	FW_AEX,			// auto exposure

	AW_RTL,			// ROI: rect.left
	AW_RTT,			// ROI: rect.top
	AW_RTR,			// ROI: rect.right
	AW_RTB,			// ROI: rect.bottom,
	FW_ROI,			// ROI: apply

	AW_TDM,			// trigger in: data mode
	AW_TEX,			// trigger in: exposure type
	AW_TED,			// trigger in: edge type
	AW_TEP = 40,	// trigger in: endplus cnts
	AW_TDE,			// trigger in: delay ms
	FW_TRI = 43,	// trigger in: apply
	FW_TSS,			// trigger in: software signal
	FW_SER,			// signal out: exp/readout

	FW_HEG,			// histogram-equalization-gamma
	FW_TDX,			// test direct xml file
	AW_ALV,			// usb[firmware]cl[software]:auto level
	AW_LVU,			// usb[firmware]cl[software]:level up
	AW_LVD = 50,	// usb[firmware]cl[software]:level down

	FC_OBJ = 101,	// cameralink: object NO.
	CL_TIS,
	CL_SP  = 110,	// cameralink:stream pattern
	CL_FP  = 111,	// cameralink:fpga pattern
	CL_FF  = 113,	// cameralink:frame frequency
	CL_PGN,			// cameralink:pixel gain
	CL_HDR,			// cameralink:hdr
	CL_FPN,			// cameralink:fpn
	CL_QT,			// cameralink:QueryTemperature
	// internal
	ICL_HDRS = 0xA0,		// internal:cameralink:HDRStretch
	X_CD	= 0xFF,		// X:CmdDirect
};
//element
struct _ELEMENT // 
{	ushort val; // current_value attribute,	[write&read]
	ushort min;	// minimum_value attribute,	[read]
	ushort max; // maximum_value attribute,	[read]
	ushort inc;	// increment attribute,		[read]
	ushort dft;	// default_value attribute,	[read]
	uchar  id;	// index of element			[read]
	ushort old;	// old_value attribute,		[read]
};

enum {// element.attribute
	ATTR_VAL = 0, // unit (ushort)
	ATTR_MIN,		
	ATTR_MAX,
	ATTR_STP,	// step
	ATTR_DFT,	// default
	ATTR_STA,	// state, S_LIVE/S_DEAD
	ATTR_TXT,	// string
};

// picture type
enum {
	SNAP_RAW = 0x01,
	SNAP_TIF = 0x02,
	SNAP_PNG = 0x04,
	SNAP_JPG = 0x08,
	SNAP_BMP = 0x10,
};

// direction
enum {
	FLIP_HORIZONTAL = 0x01,
	FLIP_VERTICAL = 0x02,
	FLIP_TRANSPOSE = 0x04,
};
struct ez_rect {
    ushort left;
	ushort top;
    ushort right;
    ushort bottom;
};

// output signal
enum {
	SIGNAL_EXPOSURE = 0,
	SIGNAL_READOUT = 1,
};
// data mode:stream or frame
enum {
	DEVICE_STREAM = 0x0001,
	DEVICE_HW_STANDARD = 0x0002,
	DEVICE_HW_SYNC = 0x0004,
	DEVICE_HW_GLOBAL = 0x0008,
	DEVICE_SW_TRI = 0x0010, // software trigger
	DEVICE_RESEVER = 0x0020,
};
struct _TRIGGER {   // trigger
	uchar triMode;	// triiger mode
	uchar expType;	// exp type
	uchar sigEdge;	// signal edge
	uchar reserve;//;frames;	//		deprecated				signal counts
	ushort delay;	// ms unit
	uchar cl_src;	// cameralink in source
};

// The Head position of image
enum {
	RAW_OFT_WIDTH = sizeof(char) << 2,
	RAW_OFT_HEIGHT = sizeof(ushort) + RAW_OFT_WIDTH,
	RAW_OFT_DEPTH = sizeof(ushort) + RAW_OFT_HEIGHT,
	RAW_OFT_CHANNELS = sizeof(char) + RAW_OFT_DEPTH,
	RAW_OFT_BAYER = sizeof(char) + RAW_OFT_CHANNELS,
	RAW_OFT_RESERVE1 = sizeof(char) + RAW_OFT_BAYER,
	RAW_OFT_HEAD = sizeof(char) + RAW_OFT_RESERVE1,
};
struct _IMAGE { // iamge head infomation
	uint timestamp;
	ushort width;            
	ushort height;             
	uchar depth;		
	uchar channel;  
	uchar bayer;
	uchar reserve1;  
	ushort offset;   
};

#endif
