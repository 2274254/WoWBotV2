#pragma once
#include "Macros.h"
#include "Offsets.h"
#include "StaticEnums.h"
#include "vector3.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT ObjectGuid
		{
		public:
			ObjectGuid() = default;
			ObjectGuid(uint64_t low, uint64_t high) : LoWord(low), HiWord(high) {}
			~ObjectGuid() {}

			ObjectGuid(const ObjectGuid&) = default;
			ObjectGuid(ObjectGuid&&) = default;

			ObjectGuid& operator=(const ObjectGuid&) = default;
			ObjectGuid& operator=(ObjectGuid&&) = default;

			bool operator==(const ObjectGuid& rhs)
			{
				if (rhs.LoWord == LoWord && rhs.HiWord == HiWord)
					return true;
				return false;
			}

			bool operator!=(const ObjectGuid& rhs)
			{
				return *this == rhs;
			}

			bool operator!()
			{
				return (!LoWord && !HiWord);
			}

			std::string ToString()
			{
				//return fmt::format("{0:16X}:{1:16X}", LoWord, HiWord);
				return "";//TODO
			}

			GuidType Type()
			{
				return (GuidType)(HiWord >> 58);
			}

			unsigned short RealmId()
			{
				return (unsigned short)((HiWord >> 42) & 0x1FFF);
			}

			unsigned short ServerId()
			{
				return (unsigned short)((LoWord >> 40) & 0x1FFF);
			}

			unsigned short MapId()
			{
				return (unsigned short)((HiWord >> 29) & 0x1FFF);
			}

			unsigned int Id()
			{
				return (unsigned int)(HiWord & 0xFFFFFF) >> 6;
			}

			unsigned long CreationBits()
			{
				return LoWord & 0xFFFFFFFFFF;
			}

			uint64_t LoWord = 0;
			uint64_t HiWord = 0;
		};

		class DLLEXPORT CGObject
		{
		public:
			ObjectGuid GetGuid();
			std::string GetName();
			WoWObjectType GetType();
			Vector3 GetPosition();
		};
	}
}
