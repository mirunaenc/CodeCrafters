export module utility;
import <iostream>;

namespace twixt {
	export class Utility{
	public:
		template <typename T>
		static void swap(T* &current , T* &opponent);
	};
	export enum class EColor : uint8_t
	{
		RED,
		BLACK,
		NONE
	};

}