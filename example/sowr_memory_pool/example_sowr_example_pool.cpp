#include <string.h>
#include <thread>
#include <atomic>
#include <functional>

#include "muggle/cpp/muggle_cpp.h"

struct Foo
{
	int thread_idx;
	unsigned int i;
};
static_assert(std::is_trivial<Foo>::value, "Foo need trivial class");

class Bar
{
public:
	Bar(int thread_idx, unsigned int i)
		: thread_idx_(thread_idx)
		, i_(i)
	{
		LOG_TRACE("contructor thread=%d", thread_idx_);
	}
	virtual ~Bar()
	{
		LOG_TRACE("destructor thread=%d", thread_idx_);
	}

	int ThreadIdx()
	{
		return thread_idx_;
	}

	unsigned int Index()
	{
		return i_;
	}

	void SetIndex(int index)
	{
		i_ = index;
	}

private:
	int thread_idx_;
	unsigned int i_;
};
static_assert(std::is_trivial<Bar>::value == false, "Bar need trivial class");

void example_trivial()
{
	LOG_INFO("########## trivial ##########");

	muggle_atomic_int cap = 4096;
	std::atomic_int cnt(0);
	muggle::SowrMemoryPool<Foo> pool(cap);
	Foo **arr = (Foo**)malloc(sizeof(Foo*) * cap);

	std::function<void(int)> f = [&](int i){
		int thread_idx = i;
		while (true)
		{
			Foo *foo = (Foo*)pool.Allocate();
			if (foo == nullptr)
			{
				break;
			}

			foo->thread_idx = thread_idx;
			foo->i = cnt++;

			arr[foo->i] = foo;
		}
	};
	std::thread t1(f, 0);
	t1.join();

	LOG_INFO("cnt %d", cnt.load());

	// recycle all allocated memory space
	for (int i = 0; i < cnt; i++)
	{
		if (arr[i] == nullptr)
		{
			LOG_ERROR("nullptr in index: %d", i);
			continue;
		}
		pool.Recycle(arr[i]);
	}
}

void example_non_trivial()
{
	LOG_INFO("########## non-trivial ##########");

	muggle_atomic_int cap = 4096;
	std::atomic_int cnt(0);
	muggle::SowrMemoryPool<Bar> pool(cap);
	Bar **arr = (Bar**)malloc(sizeof(Bar*) * cap);

	std::function<void(int)> f = [&](int i){
		int thread_idx = i;
		while (true)
		{
			Bar *bar = (Bar*)pool.New(thread_idx, 0);
			if (bar == nullptr)
			{
				break;
			}
			bar->SetIndex(cnt++);

			arr[bar->Index()] = bar;
		}
	};
	std::thread t1(f, 0);
	t1.join();

	LOG_INFO("cnt %d", cnt.load());

	// recycle all allocated memory space
	for (int i = 0; i < cnt; i++)
	{
		if (arr[i] == nullptr)
		{
			LOG_ERROR("nullptr in index: %d", i);
			continue;
		}

		if (i >= cap)
		{
			LOG_ERROR("count beyond the range, cnt=%d", cnt.load());
			break;
		}
		pool.Erase(arr[i]);
	}
}

int main()
{
	muggle::Log::SimpleInit(LOG_LEVEL_INFO, "log/example_sowr_memory_pool.log", LOG_LEVEL_INFO);

	example_trivial();
	example_non_trivial();

	return 0;
}
