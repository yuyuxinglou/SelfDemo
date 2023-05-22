unit TUCamApi;

// /************************************************************************
// *  Copyright (C) Xintu Photonics Co.,Ltd. 2012-2018. All rights reserved.
// *  @file      TuCamApi.pas
// *  @brief     Tucsen Camera export functions header file
// *  @version	  1.0.0.0
// *  @author    Zhang Ren
// *  @date      2018-08-03
// ************************************************************************/

interface

uses
  TUDefine;

const
  DllFile = 'TUCam.dll';

//
// Initialize uninitialize and misc.
//
function TUCAM_Api_Init(pInitParam: PTUCAM_INIT): TUCAMRET; cdecl; external DllFile;
function TUCAM_Api_Uninit(): TUCAMRET; cdecl; external DllFile;

function TUCAM_Dev_Open(pOpenParam: PTUCAM_OPEN): TUCAMRET; cdecl; external DllFile;
function TUCAM_Dev_Close(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;

// Get some device information (VID/PID/Version)
function TUCAM_Dev_GetInfo(hTUCam: THandle; pInfo: PTUCAM_VALUE_INFO): TUCAMRET; cdecl; external DllFile;     // PTUCAM_VALUE_INFO  call after TUCAM_Dev_Open()
function TUCAM_Dev_GetInfoEx(uiICam: Cardinal; pInfo: PTUCAM_VALUE_INFO): TUCAMRET; cdecl; external DllFile;  // PTUCAM_VALUE_INFO  call after TUCAM_Api_Init()

//
// Capability control
//
function TUCAM_Capa_GetAttr(hTUCam: THandle; pAttr: PTUCAM_CAPA_ATTR): TUCAMRET; cdecl; external DllFile;           // PTUCAM_CAPA_ATTR
function TUCAM_Capa_GetValue(hTUCam: THandle; nCapa: Integer; pnVal: pInteger): TUCAMRET; cdecl; external DllFile;  // TUCAM_IDCAPA
function TUCAM_Capa_SetValue(hTUCam: THandle; nCapa: Integer; nVal: Integer): TUCAMRET; cdecl; external DllFile;    // TUCAM_IDCAPA
function TUCAM_Capa_GetValueText(hTUCam: THandle; pVal: PTUCAM_VALUE_TEXT): TUCAMRET; cdecl; external DllFile;      // PTUCAM_VALUE_TEXT

//
// Property control
//
function TUCAM_Prop_GetAttr(hTUCam: THandle; pAttr: PTUCAM_PROP_ATTR): TUCAMRET; cdecl; external DllFile;                         // PTUCAM_PROP_ATTR
function TUCAM_Prop_GetValue(hTUCam: THandle; nProp: Integer; pdbVal: pDouble; nChn: Integer): TUCAMRET; cdecl; external DllFile; // TUCAM_IDPROP
function TUCAM_Prop_SetValue(hTUCam: THandle; nProp: Integer; dbVal: Double; nChn: Integer): TUCAMRET; cdecl; external DllFile;   // TUCAM_IDPROP
function TUCAM_Prop_GetValueText(hTUCam: THandle; pVal: PTUCAM_VALUE_TEXT; nChn: Integer): TUCAMRET; cdecl; external DllFile;     // PTUCAM_VALUE_TEXT

//
// Buffer control
//
function TUCAM_Buf_Alloc(hTUCam: THandle; pFrame: PTUCAM_FRAME): TUCAMRET; cdecl; external DllFile;                 // call TUCAM_Buf_Release() to free.
function TUCAM_Buf_Release(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;
function TUCAM_Buf_AbortWait(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;                                   // call after TUCAM_Buf_WaitForFrame()
function TUCAM_Buf_WaitForFrame(hTUCam: THandle; pFrame: PTUCAM_FRAME): TUCAMRET; cdecl; external DllFile;          // call after TUCAM_Cap_Start()
function TUCAM_Buf_CopyFrame(hTUCam: THandle; pFrame: PTUCAM_FRAME): TUCAMRET; cdecl; external DllFile;             // call after TUCAM_Buf_WaitForFrame()


//
// Capturing control
//
// ROI
function TUCAM_Cap_SetROI(hTUCam: THandle; roiAttr: TUCAM_ROI_ATTR): TUCAMRET; cdecl; external DllFile;             // call before TUCAM_Cap_Start()
function TUCAM_Cap_GetROI(hTUCam: THandle; pRoiAttr: PTUCAM_ROI_ATTR): TUCAMRET; cdecl; external DllFile;
// Trigger
function TUCAM_Cap_SetTrigger(hTUCam: THandle; tgrAttr: TUCAM_TRIGGER_ATTR): TUCAMRET; cdecl; external DllFile;     // call before TUCAM_Cap_Start()
function TUCAM_Cap_GetTrigger(hTUCam: THandle; pTgrAttr: PTUCAM_TRIGGER_ATTR): TUCAMRET; cdecl; external DllFile;
function TUCAM_Cap_DoSoftwareTrigger(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;                           // in trigger mode
// Capturing
function TUCAM_Cap_Start(hTUCam: THandle; uiMode: Cardinal): TUCAMRET; cdecl; external DllFile;                     // uiMode see enum TUCAM_CAPTURE_MODES
function TUCAM_Cap_Stop(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;


//
// File control
//
// Image
function TUCAM_File_SaveImage(hTUCam: THandle; fileSave: TUCAM_FILE_SAVE): TUCAMRET; cdecl; external DllFile;
// Profiles
function TUCAM_File_LoadProfiles(hTUCam: THandle; pPrfName: PAnsiChar): TUCAMRET; cdecl; external DllFile;          // call before TUCAM_Cap_Start()  if after called TUCAM_Cap_Start(), must call TUCAM_Cap_Stop() first
function TUCAM_File_SaveProfiles(hTUCam: THandle; pPrfName: PAnsiChar): TUCAMRET; cdecl; external DllFile;
// Video
function TUCAM_Rec_Start(hTUCam: THandle; recSave: TUCAM_REC_SAVE): TUCAMRET; cdecl; external DllFile;
function TUCAM_Rec_AppendFrame(hTUCam: THandle; pFrame: PTUCAM_FRAME): TUCAMRET; cdecl; external DllFile;
function TUCAM_Rec_Stop(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;

//
function TUIMG_File_Open(pOpenParam: PTUIMG_OPEN; pFrame: PPTUCAM_FRAME): TUCAMRET; cdecl; external DllFile;
function TUIMG_File_Close(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;


//
// Extened control
//
function TUCAM_Reg_Read(hTUCam: THandle; regRW: TUCAM_REG_RW): TUCAMRET; cdecl; external DllFile;
function TUCAM_Reg_Write(hTUCam: THandle; regRW: TUCAM_REG_RW): TUCAMRET; cdecl; external DllFile;

// Drawing contorl
function TUCAM_Draw_Init(hTUCam: THandle; drawInit: TUCAM_DRAW_RECINIT): TUCAMRET; cdecl; external DllFile;
function TUCAM_Draw_Frame(hTUCam: THandle; pDrawing: PTUCAM_DRAW): TUCAMRET; cdecl; external DllFile;
function TUCAM_Draw_Uninit(hTUCam: THandle): TUCAMRET; cdecl; external DllFile;

// Calculate roi
function TUCAM_Calc_SetROI(hTUCam: THandle; roiAttr: TUCAM_CALC_ROI_ATTR): TUCAMRET; cdecl; external DllFile;
function TUCAM_Calc_GetROI(hTUCam: THandle; pRoiAttr: PTUCAM_CALC_ROI_ATTR): TUCAMRET; cdecl; external DllFile;

implementation

end.
