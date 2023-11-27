export module utility;
import <iostream>;

namespace twixt {
	export class Utility{
	public:
		template <typename T>
		void swap(T* &current , T* &opponent);
	};

}