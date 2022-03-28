#pragma once

namespace POS {
	namespace MENU {
		namespace LOGO {
			const float x = CAMERA_X / 2.0f;
			const float y = (CAMERA_Y / 2.0f) - 150;
		}

		namespace BTN {
			const float y = (CAMERA_Y / 2.0f) - 120;
		}
	}
}

namespace UI_SIZE {
	namespace MENU {
		namespace LOGO {
			const float width = (CAMERA_X * 0.7f);
			const float height = width / 2.16f;
		}

		namespace BTN {
			const float width = 222;
			const float height = 174;

			const float spaceWidth = 20;
		}
	}
}