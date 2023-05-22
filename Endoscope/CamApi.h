///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// AUTHOR:        jorgo(wuhua@tsdt.net) 
//				  Ezio(jorgo@163.com) on 2012-5-11
// COPYRIGHT:     Tucsen Imaging Technology Co.,ltd
//                (www.tsdt.net). All rights reserved.
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAMAPI_H
#define __CAMAPI_H

#include "CamShare.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if defined(__APPLE__)
	#define CAM_API
    
#elif defined(__linux)
    #if defined(CAMCORE_LIBRARY)
    #define CAM_API __attribute__((visibility("default")))
    #else
    #define CAM_API __attribute__((visibility("default")))
    #endif
    
#elif defined(_WIN32) || defined(__CYGWIN__)
    #ifdef CAMCORE_EXPORTS
    #define CAM_API __declspec(dllexport)
    #else
    #define CAM_API __declspec(dllimport)
    #endif

#endif
	/*************************
	//   firmware interface
	*************************/
	CAM_API int  InitDevice(const char *pathInstance);
	CAM_API void ExitDevice();

	CAM_API int DeviceCount();
	CAM_API int DeviceDescriptor(struct _DESCRIPTOR *object, int index);

	CAM_API int ResumeDevice(const char *devName);
	CAM_API int SuspendDevice(const char *devName);
	
	CAM_API int SetElement(struct _ELEMENT *object, const char *devName);
	CAM_API int GetElement(struct _ELEMENT *object, const char *devName);

	CAM_API int SetAttribute(int elementID, int value, const char *devName);
	CAM_API void *GetAttribute(int elementID, int AttributeID, int index, const char *devName);

	CAM_API int GetRawDataPtr(uchar **ppBufPointer, int *plen, const char *devName);//for C/C++
	CAM_API int GetRawData(uchar *bufArray, int *plen, const char *devName);

	CAM_API float GetExposureUnit(const char *devName);
	CAM_API int GetRawSize(int *pWid, int *pHei, const char *devName);
	CAM_API int DecodeRaw2Image(uchar *pRaw, uchar *pImg, const char *devName);

	CAM_API int GetCurrentConfiguration(const char *devName);
	CAM_API int SaveConfiguration(int index, const char *devName);
	CAM_API int LoadConfiguration(int index, const char *devName);

	CAM_API int WriteInf(char *pWrite, int size, const char *devName);
	CAM_API int ReadInf(char *pRead, int size, const char *devName);

	/*************************
	// independence algorithms
	*************************/
	CAM_API int ConvertRect(struct ez_rect *prt, int flip, int width, int height);
    CAM_API int ConvertScale(uchar *image, int scale);
    CAM_API int ConvertXto8(uchar *image, uchar *display);
	CAM_API int SaveFile(uchar *image, const char *path, int saveType);

	CAM_API int *OpenVideo(const char *path, int width, int height, int channels, int rate, int codec);
	CAM_API int WriteVideo(int *handle, unsigned char *data);
	CAM_API int CloseVideo(int *handle);

#if defined(_WIN32) || defined(__CYGWIN__)
	CAM_API int UpdateFirmware(const char *, const char *);
	CAM_API int WriteImageErrorPos(ushort pos[], const int, const int, const int, const char *);
	CAM_API int *OpenDisplay(int format, int width, int height, void *wnd);
	CAM_API int DrawDisplay(int *handle, struct ez_rect rt, unsigned char *data);
	CAM_API int CloseDisplay(int *handle);

	CAM_API int lvGetRequest(int dev, void *handle);
	CAM_API int lvGetImgData(void *dev, char *LVImagePtr, uint width, uint height);

#elif defined(__linux) || defined(__APPLE__)
#endif

#ifdef __cplusplus
}
#endif
#endif // __CAMAPI_H
