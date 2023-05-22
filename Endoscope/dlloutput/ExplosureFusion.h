// 1.0.1-R
#ifdef EXPLOSUREFUSION_EXPORTS
#define EXPLOSUREFUSION_API __declspec(dllexport)
#else
#define EXPLOSUREFUSION_API __declspec(dllimport)
#endif

#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
// 此类是从 dll 导出的
class EXPLOSUREFUSION_API CExplosureFusion {
public:
	CExplosureFusion(void);

	// api test
	std::string apiTest();

	// setter
	void setInputImages(std::string inputFileNames[], int imagesLen);

	// 重载 直接读buffer
	void setInputImages(std::vector<Mat> buffer);

	// 处理的主函数
	void process(Mat& outputImage);
	
	// 获取图像的饱和度图
	void processImageSaturation(std::vector<Mat> splitted, Mat& saturation);

	// 获取图像的Well-exposedness
	void processImageWellExp(std::vector<Mat> splitted, Mat& wellexp);

	// getter and setter
	float getWsat() const;
	void setWsat(float newWsat);

	float getWcon() const;
	void setWcon(float newWcon);

	float getWexp() const;
	void setWexp(float newWexp);

private:
	// member
	std::vector<Mat> inputImages;
	// input的属性
	Size size;
	int channels;

	Mat outputImages;

	float wcon;
	float wsat;
	float wexp;
};