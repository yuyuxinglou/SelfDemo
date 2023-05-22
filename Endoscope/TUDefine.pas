unit TUDefine;

// /************************************************************************
// *  Copyright (C) Xintu Photonics Co.,Ltd. 2012-2018. All rights reserved.
// *  @file      TuCamApi.pas
// *  @brief     Tucsen Camera export functions header file
// *  @version	  1.0.0.0
// *  @author    Zhang Ren
// *  @date      2018-08-03
// ************************************************************************/

interface

// /* **************************************************************** *
//    enum defines
// * **************************************************************** */

//  The correct state [0x00000000, 0x7FFFFFFF]
//  The error   state [0x80000000, 0XFFFFFFFF]
//  typedef enum TUCAM status

type
  TUCAMRET = (
    //  success
    TUCAMRET_SUCCESS            = $00000001,       // no error, general success code, app should check the value is positive
    TUCAMRET_FAILURE            = $80000000,       // error

    //  initialization error
    TUCAMRET_NO_MEMORY          = $80000101,       // not enough memory
    TUCAMRET_NO_RESOURCE        = $80000102,       // not enough resource except memory
    TUCAMRET_NO_MODULE          = $80000103,       // no sub module
    TUCAMRET_NO_DRIVER          = $80000104,       // no driver
    TUCAMRET_NO_CAMERA          = $80000105,       // no camera
    TUCAMRET_NO_GRABBER         = $80000106,       // no grabber
    TUCAMRET_NO_PROPERTY        = $80000107,       // there is no alternative or influence id, or no more property id

    TUCAMRET_FAILOPEN_CAMERA    = $80000110,       // fail open the camera
    TUCAMRET_FAILOPEN_BULKIN    = $80000111,       // fail open the bulk in endpoint
    TUCAMRET_FAILOPEN_BULKOUT   = $80000112,       // fail open the bulk out endpoint
    TUCAMRET_FAILOPEN_CONTROL   = $80000113,       // fail open the control endpoint
    TUCAMRET_FAILCLOSE_CAMERA   = $80000114,       // fail close the camera

    TUCAMRET_FAILOPEN_FILE      = $80000115,       // fail open the file
	  TUCAMRET_FAILOPEN_CODEC		  = $80000116,       // fail open the video codec
	  TUCAMRET_FAILOPEN_CONTEXT   = $80000117,       // fail open the video context

    //  status error
    TUCAMRET_INIT               = $80000201,       // API requires has not initialized state.
    TUCAMRET_BUSY               = $80000202,       // API cannot process in busy state.
    TUCAMRET_NOT_INIT           = $80000203,       // API requires has initialized state.
    TUCAMRET_EXCLUDED           = $80000204,       // some resource is exclusive and already used.
    TUCAMRET_NOT_BUSY           = $80000205,       // API requires busy state.
    TUCAMRET_NOT_READY          = $80000206,       // API requires ready state.

    //  wait error
    TUCAMRET_ABORT              = $80000207,       // abort process
    TUCAMRET_TIMEOUT            = $80000208,       // timeout
    TUCAMRET_LOSTFRAME          = $80000209,       // frame data is lost
    TUCAMRET_MISSFRAME          = $8000020A,       // frame is lost but reason is low lever driver's bug
    TUCAMRET_USB_STATUS_ERROR   = $8000020B,       // the USB status error

    // calling error
    TUCAMRET_INVALID_CAMERA     = $80000301,       // invalid camera
    TUCAMRET_INVALID_HANDLE     = $80000302,       // invalid camera handle
    TUCAMRET_INVALID_OPTION     = $80000303,       // invalid the option value of structure
    TUCAMRET_INVALID_IDPROP     = $80000304,       // invalid property id
    TUCAMRET_INVALID_IDCAPA     = $80000305,       // invalid capability id
    TUCAMRET_INVALID_IDPARAM    = $80000306,       // invalid parameter id
    TUCAMRET_INVALID_PARAM      = $80000307,       // invalid parameter
    TUCAMRET_INVALID_FRAMEIDX   = $80000308,       // invalid frame index
    TUCAMRET_INVALID_VALUE      = $80000309,       // invalid property value
    TUCAMRET_INVALID_EQUAL      = $8000030A,       // invalid property value equal
    TUCAMRET_INVALID_CHANNEL    = $8000030B,       // the property id specifies channel but channel is invalid
    TUCAMRET_INVALID_SUBARRAY   = $8000030C,       // the combination of subarray values are invalid. e.g. TUCAM_IDPROP_SUBARRAYHPOS + TUCAM_IDPROP_SUBARRAYHSIZE is greater than the number of horizontal pixel of sensor.
    TUCAMRET_INVALID_VIEW       = $8000030D,       // invalid view window handle
    TUCAMRET_INVALID_PATH       = $8000030E,       // invalid file path
    TUCAMRET_INVALID_IDVPROP    = $8000030F,       // invalid vendor property id

    TUCAMRET_NO_VALUETEXT       = $80000310,       // the property does not have value text
    TUCAMRET_OUT_OF_RANGE       = $80000311,       // value is out of range

    TUCAMRET_NOT_SUPPORT        = $80000312,       // camera does not support the function or property with current settings
    TUCAMRET_NOT_WRITABLE       = $80000313,       // the property is not writable
    TUCAMRET_NOT_READABLE       = $80000314,       // the property is not readable


    TUCAMRET_WRONG_HANDSHAKE    = $80000410,       // this error happens TUCAM get error code from camera unexpectedly
    TUCAMRET_NEWAPI_REQUIRED    = $80000411,       // old API does not support the value because only new API supports the value

    TUCAMRET_ACCESSDENY         = $80000412,       // the property cannot access during this TUCAM status

    TUCAMRET_NO_CORRECTIONDATA  = $80000501,       // not take the dark and shading correction data yet.

    TUCAMRET_INVALID_PRFSETS    = $80000601,       // the profiles set name is invalid

    TUCAMRET_DECODE_FAILURE     = $80000701,       // the image decoding raw data to rgb data failure
    TUCAMRET_COPYDATA_FAILURE   = $80000702,       // the image data copying failure
	  TUCAMRET_ENCODE_FAILURE		  = $80000703,		    // the image encoding data  to video failure
	  TUCAMRET_WRITE_FAILURE		  = $80000704,		    // the write the video frame failure

    //  camera or bus trouble
    TUCAMRET_FAIL_READ_CAMERA   = $83001001,       // fail read from camera
    TUCAMRET_FAIL_WRITE_CAMERA  = $83001002,       // fail write to camera
    TUCAMRET_OPTICS_UNPLUGGED   = $83001003,       // optics part is unplugged so please check it.


	  TUCAMRET_RECEIVE_FINISH     = $00000002        // no error, vendor receive frame message
); // TUCAMRET

//  typedef enum information id
type
  TUCAM_IDINFO = (
    TUIDI_BUS                   = $01,             // the bus type USB2.0/USB3.0
    TUIDI_VENDOR                = $02,             // the vendor id
    TUIDI_PRODUCT               = $03,             // the product id
    TUIDI_VERSION_API           = $04,             // the API version
    TUIDI_VERSION_FRMW          = $05,             // the firmware version
    TUIDI_VERSION_FPGA          = $06,             // the FPGA version
    TUIDI_VERSION_DRIVER        = $07,             // the driver version
    TUIDI_TRANSFER_RATE         = $08,             // the transfer rate
    TUIDI_CAMERA_MODEL          = $09,             // the camera model (string)
    TUIDI_CURRENT_WIDTH         = $0A,             // the camera image data current width(must use TUCAM_Dev_GetInfoEx and after calling TUCAM_Buf_Alloc)
    TUIDI_CURRENT_HEIGHT        = $0B,             // the camera image data current height(must use TUCAM_Dev_GetInfoEx and after calling TUCAM_Buf_Alloc)
    TUIDI_CAMERA_CHANNELS       = $0C,             // the camera image data channels
    TUIDI_BCDDEVICE             = $0D,             // the USB bcdDevice
    TUIDI_ENDINFO               = $0E              // the string id end
);  // TUCAM_IDINFO

// typedef enum capability id
type
  TUCAM_IDCAPA = (
    TUIDC_RESOLUTION            = $00,             // id capability resolution
    TUIDC_PIXELCLOCK            = $01,             // id capability pixel clock
    TUIDC_BITOFDEPTH            = $02,             // id capability bit of depth
    TUIDC_ATEXPOSURE            = $03,             // id capability automatic exposure time
    TUIDC_HORIZONTAL            = $04,             // id capability horizontal
    TUIDC_VERTICAL              = $05,             // id capability vertical
    TUIDC_ATWBALANCE            = $06,             // id capability automatic white balance
    TUIDC_FAN_GEAR              = $07,             // id capability fan gear
    TUIDC_ATLEVELS              = $08,             // id capability automatic levels
    TUIDC_SHIFT                 = $09,             // (The reserved) id capability shift(15~8, 14~7, 13~6, 12~5, 11~4, 10~3, 9~2, 8~1, 7~0) [16bit]
    TUIDC_HISTC                 = $0A,             // id capability histogram statistic
    TUIDC_CHANNELS              = $0B,             // id capability current channels(Only color camera support:0-RGB,1-Red,2-Green,3-Blue. Used in the property levels, see enum TUCHN_SELECT)
    TUIDC_ENHANCE               = $0C,             // id capability enhance
    TUIDC_DFTCORRECTION         = $0D,             // id capability defect correction (0-not correction, 1-calculate, 3-correction)
    TUIDC_ENABLEDENOISE         = $0E,             // id capability enable denoise (TUIDP_NOISELEVEL effective)
    TUIDC_FLTCORRECTION         = $0F,             // id capability flat field correction (0-not correction, 1-grab frame, 2-calculate, 3-correction)
    TUIDC_RESTARTLONGTM         = $10,             // id capability restart long exposure time (only CCD camera support)
    TUIDC_DATAFORMAT            = $11,             // id capability the data format(only YUV format data support 0-YUV 1-RAW)
    TUIDC_DRCORRECTION          = $12,             // (The reserved)id capability dynamic range of correction
    TUIDC_VERCORRECTION         = $13,             // id capability vertical correction(correction the image data show vertical, in windows os the default value is 1)
    TUIDC_MONOCHROME            = $14,             // id capability monochromatic
    TUIDC_BLACKBALANCE          = $15,             // id capability black balance
    TUIDC_IMGMODESELECT         = $16,             // id capability image mode select(CMS mode)
    TUIDC_CAM_MULTIPLE          = $17,             // id capability multiple cameras (how many cameras use at the same time, only SCMOS camera support)
	  TUIDC_ENABLEPOWEEFREQUENCY  = $18,             // id capability enable power frequency (50HZ or 60HZ)
	  TUIDC_ROTATE_R90			      = $19,				     // id capability rotate 90 degree to right
	  TUIDC_ROTATE_L90			      = $1A,				     // id capability rotate 90 degree to left
	  TUIDC_NEGATIVE				      = $1B,				     // id capability negative film enable
	  TUIDC_HDR					          = $1C,				     // id capability HDR enable
    TUIDC_ENDCAPABILITY         = $1D              // id capability end
); // TUCAM_IDCAPA

// typedef enum property id
type
  TUCAM_IDPROP = (
    TUIDP_GLOBALGAIN            = $00,             // id property global gain
    TUIDP_EXPOSURETM            = $01,             // id property exposure time
    TUIDP_BRIGHTNESS            = $02,             // id property brightness (Effective automatic exposure condition)
    TUIDP_BLACKLEVEL            = $03,             // id property black level
    TUIDP_TEMPERATURE           = $04,             // id property temperature control
    TUIDP_SHARPNESS             = $05,             // id property sharpness
    TUIDP_NOISELEVEL            = $06,             // id property the noise level
    TUIDP_HDR_KVALUE            = $07,             // id property the HDR K value

    // image process property
    TUIDP_GAMMA                 = $08,             // id property gamma
    TUIDP_CONTRAST              = $09,             // id property contrast
    TUIDP_LFTLEVELS             = $0A,             // id property left levels
    TUIDP_RGTLEVELS             = $0B,             // id property right levels
    TUIDP_CHNLGAIN              = $0C,             // id property channel gain
    TUIDP_SATURATION            = $0D,             // id property saturation
    TUIDP_CLRTEMPERATURE        = $0E,             // id property color temperature
    TUIDP_CLRMATRIX             = $0F,             // id property color matrix setting
    TUIDP_DPCLEVEL              = $10,             // id property defect points correction level
    TUIDP_BLACKLEVELHG          = $11,             // id property black level high gain
    TUIDP_BLACKLEVELLG          = $12,             // id property black level low gain
	  TUIDP_POWEEFREQUENCY        = $13,             // id property power frequency (50HZ or 60HZ)
	  TUIDP_HUE					          = $14,				     // id property hue
	  TUIDP_LIGHT					        = $15,				     // id property light
    TUIDP_ENDPROPERTY           = $16              // id property end
);  // TUCAM_IDPROP

// typedef enum vendor property id
type
  TUCAM_IDVPROP = (
    TUIDV_ADDR_FLASH            = $00,              // id vendor flash address
    TUIDV_ENDVPROPERTY          = $01               // id vendor end
); // TUCAM_IDVPROP

// typedef enum calculate roi id
type
  TUCAM_IDCROI = (
    TUIDCR_WBALANCE             = $00,              // id calculate roi white balance
    TUIDCR_BBALANCE             = $01,              // id calculate roi black balance
    TUIDCR_END                  = $02               // id calculate roi end
);  // TUCAM_IDCROI

// typedef enum the capture mode
type
  TUCAM_CAPTURE_MODES = (
    TUCCM_SEQUENCE              = $00,              // capture start sequence mode
    TUCCM_TRIGGER_STANDARD      = $01,              // capture start trigger standard mode
    TUCCM_TRIGGER_SYNCHRONOUS   = $02,              // capture start trigger synchronous mode
    TUCCM_TRIGGER_GLOBAL        = $03,              // capture start trigger global
    TUCCM_TRIGGER_SOFTWARE      = $04               // capture start trigger software
);  // TUCAM_CAPTURE_MODES

// typedef enum the image formats
type
  TUIMG_FORMATS = (
    TUFMT_RAW                   = $01,              // The format RAW
    TUFMT_TIF                   = $02,              // The format TIFF
    TUFMT_PNG                   = $04,              // The format PNG
    TUFMT_JPG                   = $08,              // The format JPEG
    TUFMT_BMP                   = $10               // The format BMP
);  // TUIMG_FORMATS

// typedef enum the register types
type
  TUREG_TYPE = (
    TUREG_SN                    = $01,              // The type register SN
    TUREG_DATA                  = $02,              // The type register DATA
    TUREG_BAD_ROW               = $03,              // The type register bad row    (Vendor use)
    TUREG_BAD_COL               = $04,              // The type register bad column (Vendor use)
    TUREG_BGC                   = $05,              // The type register background (Vendor use)
    TUREG_CODE                  = $06               // The type register code       (Vendor use)
);  // TUREG_TYPE

// trigger mode
// typedef enum the trigger exposure time mode
type
  TUCAM_TRIGGER_EXP = (
    TUCTE_EXPTM                 = $00,              // use exposure time
    TUCTE_WIDTH                 = $01               // use width level
);  // TUCAM_TRIGGER_EXP;

// typedef enum the trigger edge mode
type
  TUCAM_TRIGGER_EDGE = (
    TUCTD_RISING                = $01,              // rising edge
    TUCTD_FAILING               = $00               // failing edge
);  // TUCAM_TRIGGER_EDGE

// typedef enum the frame formats
type
  TUFRM_FORMATS = (
    TUFRM_FMT_RAW               = $10,              // The raw data
    TUFRM_FMT_USUAl             = $11,              // The usually data
    TUFRM_FMT_RGB888            = $12               // The RGB888 data for drawing
);  // TUFRM_FORMATS

// typedef enum the SCMOS gain mode
type
  TUGAIN_MODE = (
    TUGAIN_HDR                  = $00,              // The HDR mode
    TUGAIN_HIGH                 = $01,              // The High gain mode
    TUGAIN_LOW                  = $02               // The Low gain mode
);  // TUGAIN_MODE

// typedef enum the vendor config mode
type
  TUVEN_CFG_MODE = (
    TUVCM_BGC                   = $00,              // The background correction
    TUVCM_CODE                  = $01,              // The code
    TUVCM_SN_CHECKING           = $02               // The SN checking
);  // TUVEN_CFG_MODE

// typedef enum drawing mode(only support on windows os)
type
  TUDRAW_MODE = (
    TUDRAW_DFT                  = $00,              // The default mode
    TUDRAW_DIB                  = $01,              // The DIB mode
    TUDRAW_DX9                  = $02               // The DirectX 9.0
);  // TUDRAW_MODE

// The enum of channels
type
  TUCHN_SELECT = (
    TUCHN_SHARE                 = $00,              // The channel shared (Gray or RGB)
    TUCHN_RED                   = $01,              // The channel 1 (Red channel)
    TUCHN_GREEN                 = $02,              // The channel 2 (Green channel)
    TUCHN_BLUE                  = $03               // The channel 3 (Blue channel)
);  // TUCHN_SELECT


// typedef enum the firmware types
type
  TUFW_TYPE = (
    TUFW_IIC                    = $01,              // The type firmware IIC
    TUFW_FPGA                   = $02               // The type firmware FPGA
);  // TUFW_TYPE

// /* **************************************************************** *
//     struct defines
// * **************************************************************** */

// the camera initialize struct
type
  TUCAM_INIT = record
    uiCamCount: WORD;                         // [out]
    pstrConfigPath: PAnsiChar;                // [in] save the path of the camera parameters
  end;
  PTUCAM_INIT = ^TUCAM_INIT;

//  the camera open struct
type
  TUCAM_OPEN = record
    uiIdxOpen: WORD;                          // [in]
    hIdxTUCam: THandle;                       // [out] the handle of the opened camera device
  end;
  PTUCAM_OPEN = ^TUCAM_OPEN;

//  the image open struct
type
  TUIMG_OPEN = record
    pszfileName: PAnsiChar;                   // [in]  the full path of the image file
    hIdxTUImg: THandle;                       // [out] the handle of the opened image file
  end;
  PTUIMG_OPEN = ^TUIMG_OPEN;

// the camera value text struct
type
  TUCAM_VALUE_INFO = record
    nID: Integer;                             // [in] TUCAM_IDINFO
    nValue: Integer;                          // [in] value of information
    pText: PAnsiChar;					                // [in/out] text of the value
    nTextSize: Integer;          			        // [in] text buf size
  end;
  PTUCAM_VALUE_INFO = ^TUCAM_VALUE_INFO;

// the camera value text struct
type
  TUCAM_VALUE_TEXT = record
    nID: Integer;                             // [in] TUCAM_IDPROP / TUCAM_IDCAPA
    dbValue: Double;                          // [in] value of property
    pText: PAnsiChar;					                // [in/out] text of the value
    nTextSize: Integer;          				      // [in] text buf size
  end;
  PTUCAM_VALUE_TEXT = ^TUCAM_VALUE_TEXT;

// the camera capability attribute
type
  TUCAM_CAPA_ATTR = record
    idCapa: Integer;                          // [in] TUCAM_IDCAPA
    nValMin: Integer;                         // [out] minimum value
    nValMax: Integer;                         // [out] maximum value
    nValDft: Integer;                         // [out] default value
    nValStep: Integer;                        // [out] minimum stepping between a value and the next
  end;
  PTUCAM_CAPA_ATTR = ^TUCAM_CAPA_ATTR;

// the camera property attribute
type
  TUCAM_PROP_ATTR = record
    idProp: Integer;                          // [in] TUCAM_IDPROP
    nIdxChn: Integer;                         // [in/out] the index of channel
    dbValMin: Double;                         // [out] minimum value
    dbValMax: Double;                         // [out] maximum value
    dbValDft: Double;                         // [out] default value
    dbValStep: Double;                        // [out] minimum stepping between a value and the next
  end;
  PTUCAM_PROP_ATTR = ^TUCAM_PROP_ATTR;

// the camera vendor property attribute
type
  TUCAM_VPROP_ATTR = record
    idVProp: Integer;                         // [in] TUCAM_IDVPROP
    nIdxChn: Integer;                         // [in/out] the index of channel
    dbValMin: Double;                         // [out] minimum value
    dbValMax: Double;                         // [out] maximum value
    dbValDft: Double;                         // [out] default value
    dbValStep: Double;                        // [out] minimum stepping between a value and the next
  end;
  PTUCAM_VPROP_ATTR = ^TUCAM_VPROP_ATTR;

// the camera roi attribute
type
  TUCAM_ROI_ATTR = record
    bEnable: Boolean;                         // [in/out] The ROI enable
    nHOffset: Integer;                        // [in/out] The horizontal offset
    nVOffset: Integer;                        // [in/out] The vertical offset
    nWidth: Integer;                          // [in/out] The ROI width
    nHeight: Integer;                         // [in/out] The ROI height
  end;
  PTUCAM_ROI_ATTR = ^TUCAM_ROI_ATTR;

// the camera roi calculate attribute
type
  TUCAM_CALC_ROI_ATTR = record
    bEnable: Boolean;                         // [in/out] The ROI enable
    idCalc: Integer;                          // [in] TUCAM_IDCROI
    nHOffset: Integer;                        // [in/out] The horizontal offset
    nVOffset: Integer;                        // [in/out] The vertical offset
    nWidth: Integer;                          // [in/out] The ROI width
    nHeight: Integer;                         // [in/out] The ROI height
  end;
  PTUCAM_CALC_ROI_ATTR = ^TUCAM_CALC_ROI_ATTR;

  // the camera trigger attribute
type
  TUCAM_TRIGGER_ATTR = record
    nTgrMode: Integer;                        // [in/out] The mode of trigger
    nExpMode: Integer;                        // [in/out] The mode of exposure [0, 1] 0:Exposure time   1:Width level
    nEdgeMode: Integer;                       // [in/out] The mode of edge     [0, 1] 0:Falling edge    1:Rising edge
    nDelayTm: Integer;                        // [in/out] The time delay
    nFrames: Integer;                         // [in/out] How many frames per trigger
  end;
  PTUCAM_TRIGGER_ATTR = ^TUCAM_TRIGGER_ATTR;

// the camera frame struct
type
  TUCAM_FRAME = record
    // TUCAM_Buf_WaitForFrame() use this structure. Some members have different direction.
    // [i:o] means, the member is input at TUCAM_Buf_WaitForFrame()
    // [i:i] and [o:o] means always input and output at both function.
    // "input" means application has to set the value before calling.
    // "output" means function fills a value at returning.

    szSignature: array [0 .. 7] of Ansichar;  // [out]Copyright+Version: TU+1.0 ['T', 'U', '1', '\0']

    //  The based information
    usHeader: Word;                           // [out] The frame header size
    usOffset: Word;                           // [out] The frame data offset
    usWidth: Word;                            // [out] The frame width
    usHeight: Word;                           // [out] The frame height
    uiWidthStep: Integer;                     // [out] The frame width step

    ucDepth: Byte;                            // [out] The frame data depth
    ucFormat: Byte;                           // [out] The frame data format
    ucChannels: Byte;                         // [out] The frame data channels
    ucElemBytes: Byte;                        // [out] The frame data bytes per element
    ucFormatGet: Byte;                        // [in]  Which frame data format do you want    see TUFRM_FORMATS

    uiIndex: Cardinal;                        // [in/out] The frame index number
    uiImgSize: Cardinal;                      // [out] The frame size
    uiRsdSize: Cardinal;                      // [in]  The frame reserved size    (how many frames do you want)
    uiHstSize: Cardinal;                      // [out] The frame histogram size

    pBuffer: PByte;                           // [in/out] The frame buffer
  end;
  PTUCAM_FRAME = ^TUCAM_FRAME;
  PPTUCAM_FRAME = ^PTUCAM_FRAME;

// the file save struct
type
  TUCAM_FILE_SAVE = record
    nSaveFmt: Integer;                        // [in] the format of save file     see TUIMG_FORMATS
    pstrSavePath: PAnsiChar;                  // [in] the path of save file
    pFrame: PTUCAM_FRAME ;                    // [in] the struct of camera frame
  end;
  PTUCAM_FILE_SAVE = ^TUCAM_FILE_SAVE;

// the record save struct
type
  TUCAM_REC_SAVE = record
    nCodec: Integer;                          // [in] the coder-decoder type
    pstrSavePath: PAnsiChar;                  // [in] the path of save record file
    fFps: Single;                             // [in] the current FPS
  end;
  PTUCAM_REC_SAVE = ^TUCAM_REC_SAVE;

// the register read/write struct
type
  TUCAM_REG_RW = record
    nRegType: Integer;                        // [in] the format of register     see TUREG_TYPE
    pBuf: PAnsiChar;					                // [in/out] pointer to the buffer value
    nBufSize: Integer;          	            // [in] the buffer size
  end;
  PTUCAM_REG_RW = ^TUCAM_REG_RW;

//  typedef struct draw initialize
type
  TUCAM_DRAW_RECINIT = record
    hWnd: THandle;                            // [in] Handle the draw window
    nMode: Integer;                           // [in] (The reserved)Whether use hardware acceleration (If the GPU support) default:TUDRAW_DFT
    ucChannels: Byte;                         // [in] The data channels
    nWidth: Integer;                          // [in] The drawing data width
    nHeight: Integer;                         // [in] The drawing data height
  end;
  PTUCAM_DRAW_RECINIT = ^TUCAM_DRAW_RECINIT;

//  typedef struct drawing
type
  TUCAM_DRAW = record
    nSrcX: Integer;                           // [in/out] The x-coordinate, in pixels, of the upper left corner of the source rectangle.
    nSrcY: Integer;                           // [in/out] The y-coordinate, in pixels, of the upper left corner of the source rectangle.
    nSrcWidth: Integer;                       // [in/out] Width,  in pixels, of the source rectangle.
    nSrcHeight: Integer;                      // [in/out] Height, in pixels, of the source rectangle.

    nDstX: Integer;                           // [in/out] The x-coordinate, in MM_TEXT client coordinates, of the upper left corner of the destination rectangle.
    nDstY: Integer;                           // [in/out] The y-coordinate, in MM_TEXT client coordinates, of the upper left corner of the destination rectangle.
    nDstWidth: Integer;                       // [in/out] Width,  in MM_TEXT client coordinates, of the destination rectangle.
    nDstHeight: Integer;                      // [in/out] Height, in MM_TEXT client coordinates, of the destination rectangle.

    pFrame: PTUCAM_FRAME;                     // [in] the struct of camera frame
  end;
  PTUCAM_DRAW = ^TUCAM_DRAW;

// the firmware update
type
  TUCAM_FW_UPDATE = record
    nFwType: Integer;                         // [in] the format of firmware     see TUFW_TYPE
    pstrFwFile: PAnsiChar;                    // [in] the path of firmware file
  end;
  PTUCAM_FW_UPDATE = ^TUCAM_FW_UPDATE;

implementation

end.
