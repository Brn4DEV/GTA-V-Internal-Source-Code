void EnableTLSContext();
void DisableTLSContext();

namespace rage
{
	class scrThread
	{
	public:
		virtual ~scrThread() = default;
		virtual void reset(uint32_t script_hash, void* args, uint32_t arg_count) = 0;
		virtual uint32_t run() = 0;
		virtual uint32_t tick(uint32_t ops_to_execute) = 0;
	private:
		char m_padding01[0x118];
	};

//	static_assert(sizeof(scrThread) == 0x120);
}