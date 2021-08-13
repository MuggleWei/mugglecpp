#include "muggle/cpp/muggle_cpp.h"
#include <functional>
#include <thread>

struct Foo
{
	int thread_idx;
	int i;
};

#define NUM_THREAD 4

void run(muggle::Channel *chan)
{
	int cnt_arr[NUM_THREAD];
	memset(cnt_arr, 0, sizeof(cnt_arr));

	std::function<void(int)> producer = [&](int thread_id) {
		for (int i = 0; i < 512; i++)
		{
			Foo *foo = new Foo();
			foo->thread_idx = thread_id;
			foo->i = i;

			int ret = chan->write((void*)foo);
			if (ret != 0)
			{
				LOG_WARNING(
					"failed push data: "
					"thread_id=%d, idx=%d, err=%d",
					foo->thread_idx, foo->i, ret);
			}
		}
	};

	std::function<void()> consumer = [&]() {
		while (1)
		{
			Foo *foo = (Foo*)chan->read();
			if (foo == nullptr)
			{
				break;
			}

			cnt_arr[foo->thread_idx]++;
		}
	};

	std::thread c0(consumer);

	std::thread p0(producer, 0);
	std::thread p1(producer, 1);
	std::thread p2(producer, 2);
	std::thread p3(producer, 3);

	p0.join();
	p1.join();
	p2.join();
	p3.join();

	chan->write(nullptr);
	c0.join();

	for (int i = 0; i < NUM_THREAD; i++)
	{
		LOG_INFO("thread #%d push and recv %d", i, cnt_arr[i]);
	}
}

int main()
{
	muggle::Log::SimpleInit(LOG_LEVEL_WARNING, "log/example_channel.log", LOG_LEVEL_INFO);

	muggle::Channel chan(512, 0);
	LOG_INFO("run channel");
	run(&chan);

	return 0;
}
