#pragma once
#include <iostream>

namespace twixt {
	 class Utility {
	public:
		template <typename T>
		static void swap(T*& current, T*& opponent);
	};
	 enum class EColor : uint8_t
	{
		RED,
		BLACK,
		NONE
	};

}