#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

int main(void){
    cv::TickMeter tm;
	std::vector<double> cpu_times;
	std::vector<double> gpu_times;

	int gpu_frame_count = 0, cpu_frame_count = 0;

	Mat mSrc = imread("cpu.jpg");
	Mat mDst;

	cuda::GpuMat Src;
	cuda::GpuMat Dst;

	Src.upload(mSrc);

	for (int index = 0; index < 1000; index++) {
		tm.reset(); tm.start();
		cvtColor(mSrc, mDst, COLOR_RGB2GRAY);
		tm.stop();
		cpu_times.push_back(tm.getTimeMilli());
		cpu_frame_count++;
	}

	for (int index = 0; index < 1000; index++) {
		tm.reset(); tm.start();
		cuda::cvtColor(Src, Dst, COLOR_RGB2GRAY);
		tm.stop();
		gpu_times.push_back(tm.getTimeMilli());
		gpu_frame_count++;
	}

	std::cout << std::endl << "Results:" << std::endl;

	std::sort(cpu_times.begin(), cpu_times.end());
	std::sort(gpu_times.begin(), gpu_times.end());

	double cpu_avg = std::accumulate(cpu_times.begin(), cpu_times.end(), 0.0) / cpu_times.size();
	double gpu_avg = std::accumulate(gpu_times.begin(), gpu_times.end(), 0.0) / gpu_times.size();

	std::cout << "Convert RGB to Gray Test CPU : Avg : " << cpu_avg << " ms FPS : " << 1000.0 / cpu_avg << " Frames " << cpu_frame_count << std::endl;
	std::cout << "Convert RGB to Gray Test GPU : Avg : " << gpu_avg << " ms FPS : " << 1000.0 / gpu_avg << " Frames " << gpu_frame_count << std::endl;

    return 0;
}