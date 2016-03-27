#pragma once
#include <cstdint>
namespace decs
{
	class DiEntityId
	{
		friend class DiWorld;
		friend class DiEntity;
	public:
		DiEntityId() = default;
		auto value() const -> int { return _id; }


		friend bool operator==(const DiEntityId& lhs, const DiEntityId& rhs)
		{
			return lhs._id == rhs._id;
		}

		friend bool operator!=(const DiEntityId& lhs, const DiEntityId& rhs)
		{
			return !(lhs == rhs);
		}

	private:
		DiEntityId(uint32_t id) : _id(id) {};
		uint32_t _id;
		uint32_t _counter = 1;
	};
}