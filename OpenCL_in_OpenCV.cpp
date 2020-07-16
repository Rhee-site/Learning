#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(void){

	if (!ocl::haveOpenCL()) {
		cout << "This system does not support OpenCL" << endl;
		return  -1;
	}

	ocl::Context context;
	if (!context.create(ocl::Device::TYPE_GPU)) {
		cout << "Context cannot be created" << endl;
		return  -1;
	}

	cout << context.ndevices() << " GPU device (s) detected " << endl;
	for (size_t i = 0; i < context.ndevices(); i++) {
		ocl::Device device = context.device(i);
		cout << "Device " << i  << endl;
		cout << "Name : " << device.name() << endl;
		cout << "Availability : " << device.available() << endl;
		cout << "Image Support : " << device.imageSupport() << endl;
		cout << "OpenCL C version : " << device.OpenCL_C_Version() << endl;
	}

	ocl::Device(context.device(0));

	Mat mSrc = imread("CCTV000_20200715_090100_100_Reverse_0_13.jpg", IMREAD_GRAYSCALE);
	UMat src = mSrc.getUMat(ACCESS_READ);

	static int64 start, end;
	static float time;

	ocl::setUseOpenCL(true);
	cout << "Sobel Test : OpenCL Enabled ";

	start = getTickCount();
	for (int i = 0; i < 10000; i++) {
		UMat dst;
		Sobel(src, dst, -1, 1, 0);
	}
	end = getTickCount();
	time = (end - start) / getTickFrequency();
	cout << "Using Gpu(OpenCL On) Result : " << time << " sec." << endl;

	ocl::setUseOpenCL(false);
	cout << "Sobel Test : OpenCL Disabled ";

	start = getTickCount();
	for (int i = 0; i < 10000; i++) {
		UMat dst;
		Sobel(src, dst, -1, 1, 0);
	}
	end = getTickCount();
	time = (end - start) / getTickFrequency();
	cout << "Using Cpu(OpenCL Off) Result : " << time << " sec." << endl;

    return 0;
}