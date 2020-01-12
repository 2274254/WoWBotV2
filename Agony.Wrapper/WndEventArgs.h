#pragma onces
#include <windows.h>

namespace Agony
{
	public ref class WndEventArgs : public System::EventArgs
	{
	private:
		HWND m_hwnd;
		UINT m_msg;
		WPARAM m_wparam;
		LPARAM m_lparam;
		bool m_process;
	public:
		delegate void WndProcEvent(WndEventArgs^ args);

		WndEventArgs(HWND HWnd, UINT message, WPARAM WParam, LPARAM LParam)
		{
			this->m_hwnd = HWnd;
			this->m_msg = message;
			this->m_lparam = LParam;
			this->m_wparam = WParam;
			this->m_process = true;
		}

		property System::UInt32 HWnd
		{
			System::UInt32 get()
			{
				return reinterpret_cast<System::UInt32>(this->m_hwnd);
			}
		}

		property System::UInt32 Msg
		{
			System::UInt32 get()
			{
				return static_cast<System::UInt32>(this->m_msg);
			}
		}

		property System::UInt32 WParam
		{
			System::UInt32 get()
			{
				return static_cast<System::UInt32>(this->m_wparam);
			}
		}

		property long LParam
		{
			long get()
			{
				return static_cast<long>(this->m_lparam);
			}
		}

		property bool Process
		{
			bool get()
			{
				return this->m_process;
			}
			void set(bool value)
			{
				this->m_process = value;
			}
		}
	};
}