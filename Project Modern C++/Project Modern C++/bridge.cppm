module;

export module bridge;
import pylon;

namespace twixt {
	export class Bridge {

	private:
		twixt::Pylon* m_start;
		twixt::Pylon* m_end;
	public:
		Bridge(twixt::Pylon* m_start = nullptr, twixt::Pylon* m_end = nullptr);

	};
}