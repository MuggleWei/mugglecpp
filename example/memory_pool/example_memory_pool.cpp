#include "muggle/cpp/muggle_cpp.h"

struct Foo
{
	unsigned int i;
};
static_assert(std::is_trivial<Foo>::value, "Foo need trivial class");

class Bar
{
public:
	Bar(unsigned int i)
		: i_(i)
	{
		LOG_INFO("contructor #%u", i_);
	}
	virtual ~Bar()
	{
		LOG_INFO("destructor #%u", i_);
	}

	unsigned int Index()
	{
		return i_;
	}

private:
	unsigned int i_;
};
static_assert(std::is_trivial<Bar>::value == false, "Bar need trivial class");

void example_default()
{
	// by default, memory pool use constant capacity
	LOG_INFO("########## default ##########");

	muggle::MemoryPool<Foo> pool;
	unsigned int cap = pool.Capacity();
	unsigned int cnt = 0;
	Foo **arr = (Foo**)malloc(sizeof(Foo*) * cap);
	while (true)
	{
		Foo *foo = (Foo*)pool.Allocate();
		if (foo == nullptr)
		{
			break;
		}
		foo->i = cnt;
		LOG_INFO("memory pool allocate trivial class #%u", cnt);
		arr[cnt++] = foo;
	}

	// recycle all allocated memory space
	for (unsigned int i = 0; i < cnt; i++)
	{
		LOG_INFO("memory recycle memory space #%d", arr[i]->i);
		pool.Recycle(arr[i]);
	}
}

void example_set_cap()
{
	LOG_INFO("########## set cap ##########");

	muggle::MemoryPool<Foo> pool(2);
	unsigned int cap = pool.Capacity();
	unsigned int cnt = 0;
	Foo **arr = (Foo**)malloc(sizeof(Foo*) * cap);
	while (true)
	{
		Foo *foo = (Foo*)pool.Allocate();
		if (foo == nullptr)
		{
			break;
		}
		foo->i = cnt;
		LOG_INFO("memory pool allocate trivial class #%u", cnt);
		arr[cnt++] = foo;
	}

	// recycle all allocated memory space
	for (unsigned int i = 0; i < cnt; i++)
	{
		LOG_INFO("memory recycle memory space #%d", arr[i]->i);
		pool.Recycle(arr[i]);
	}
}

void example_set_var_cap()
{
	LOG_INFO("########## set var cap ##########");

	muggle::MemoryPool<Foo> pool(4, false);
	unsigned int cap = pool.Capacity();
	unsigned int cnt = 0;
	Foo **arr = (Foo**)malloc(sizeof(Foo*) * 4 * cap);
	for (unsigned int i = 0; i < 4 * cap; i++)
	{
		Foo *foo = (Foo*)pool.Allocate();
		if (foo == nullptr)
		{
			break;
		}
		foo->i = cnt;
		LOG_INFO("memory pool allocate trivial class #%u", cnt);
		arr[cnt++] = foo;
	}

	// recycle all allocated memory space
	for (unsigned int i = 0; i < cnt; i++)
	{
		LOG_INFO("memory recycle memory space #%d", arr[i]->i);
		pool.Recycle(arr[i]);
	}
}

void example_new_delete()
{
	// by default, memory pool use constant capacity
	LOG_INFO("########## new&delete ##########");

	muggle::MemoryPool<Bar> pool;
	unsigned int cap = pool.Capacity();
	unsigned int cnt = 0;
	Bar **arr = (Bar**)malloc(sizeof(Bar*) * cap);
	while (true)
	{
		Bar *bar = pool.New(cnt);
		if (bar == nullptr)
		{
			break;
		}
		LOG_INFO("memory pool allocate non-trivial class #%u", cnt);
		arr[cnt++] = bar;
	}

	// recycle all allocated memory space
	for (unsigned int i = 0; i < cnt; i++)
	{
		LOG_INFO("memory delete memory space #%d", arr[i]->Index());
		pool.Erase(arr[i]);
	}
}

int main()
{
	muggle::Log::SimpleInit(LOG_LEVEL_INFO, LOG_LEVEL_DEBUG);

	example_default();
	example_set_cap();
	example_set_var_cap();
	example_new_delete();

	return 0;
}
