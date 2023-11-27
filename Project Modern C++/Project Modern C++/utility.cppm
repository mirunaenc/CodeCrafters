export module utility;
import <iostream>;
import player;

namespace twixt {
	export class Utility{
	public:
		template <typename T>
		static void swap(T* &current , T* &opponent);
	};

}