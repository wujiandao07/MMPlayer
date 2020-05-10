#include "MMPlayer.h"

MMPlayerCtr::MMPlayerCtr()
{

}

MMPlayerCtr::~MMPlayerCtr()
{

}

void MMPlayerCtr::run()
{
	MMPlayerReaderThread readerThread("c:/DemoVideo/demo_video.mp4", this);
	readerThread.Start();

	// ��ȡ�߳�����ʱ���ʱ�� start_time
	long long startTime = MMAVTime::GetTime();

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		// ��ȡ��ǰ��ʱ�� now_time
		long long nowTime = MMAVTime::GetTime();

		// ��ȡ����ǰʱ��Ϳ�ʼʱ��Ĳ�ֵ d_time
		long long dTime = nowTime - startTime;

		// printf("DTime: %lld\n", dTime);

		// ����Ƶ��������У���ȡһ֡��Ƶ frame_pts 
		if (videoFrame == nullptr) {
			// ����ȡһ֡����
			videoQueue.Pop(&videoFrame);
		}

		// printf("Video Queue Size: %d\n", videoQueue.Size());
		
		if (videoFrame != nullptr) {
			// ��� frame_pts <= d_time
			if (videoFrame->GetPts() <= dTime) {
				// ��֡��Ƶ��Ӧ���������ų���
				printf("Video Frame: %lld\n", videoFrame->GetPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			// ����
				// ��֡��Ƶ���������ŵ�ʱ��,�����������������ȥ������Ƶ
			else {

			}
		}
		



		// ����Ƶ��������У���ȡһ֡��Ƶ frame_pts 
		if (audioFrame == nullptr) {
			audioQueue.Pop(&audioFrame);
		}

		if (audioFrame != nullptr) {
			// ��� frame_pts <= d_time
			if (audioFrame->GetPts() <= dTime) {
				// ��֡��Ƶ��Ӧ���������ų���
				// printf("Audio Frame\n");
				delete audioFrame;
				audioFrame = nullptr;
			}
			else {
				// ��֡��Ƶ���������ŵ�ʱ��,�������������
			}
		}
	}

	readerThread.Stop();
}

int MMPlayerCtr::GetVideoQueueSize()
{
	return videoQueue.Size();
}

int MMPlayerCtr::GetAudioQueueSize()
{
	return audioQueue.Size();
}

int MMPlayerCtr::PushFrameToVideoQueue(MMAVFrame* frame)
{
	// printf("Vudio Queue Size: %d\n", videoQueue.Size());
	return videoQueue.Push(frame);
}

int MMPlayerCtr::PushFrameToAudioQueue(MMAVFrame* frame)
{
	// printf("Audio Queue Size: %d\n", audioQueue.Size());
	return audioQueue.Push(frame);
}