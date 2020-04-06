#pragma once
//using namespace System;
//using namespace System::Collections::Generic;

namespace Agony::WoWInternals
{
	public ref class LuaEventArgs : System::EventArgs
	{
		System::String^ _eventName;
		array<System::Object^>^ _args;
		System::UInt32 _fireTimeStamp;
	public:
		LuaEventArgs(System::String^ eventName, System::UInt32 fireTimeStamp, array<System::Object^>^ args)
		{
			_eventName = eventName;
			_fireTimeStamp = fireTimeStamp;
			Args = args;
		}

		property System::String^ EventName
		{
			public: System::String^ get() { return _eventName; }
			private: void set(System::String^ value) { _eventName = value; }
		}

		property System::UInt32 FireTimeStamp
		{
			public: System::UInt32 get() { return _fireTimeStamp; }
			private: void set(System::UInt32 value) { _fireTimeStamp = value; }
		}

		property array<System::Object^>^ Args
		{
			public: array<System::Object^>^ get() { return _args; }
			private: void set(array<System::Object^>^ value) { _args = value; }
		}
	};

	public delegate void LuaEventHandlerDelegate(System::Object^ sender, LuaEventArgs^ args);

	public ref class LuaEvents
	{
		static void DomainUnloadEventHandler(System::Object^, System::EventArgs^);
	internal:
		static System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<LuaEventHandlerDelegate^>^>^ RegisteredEvents = gcnew System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<LuaEventHandlerDelegate^>^>();
	public:
		static LuaEvents::LuaEvents();
		static void AttachEvent(System::String^ eventName, LuaEventHandlerDelegate^ handler);
		static void DetachEvent(System::String^ eventName, LuaEventHandlerDelegate^ handler);
	};
}