#include "gtest/gtest.h"

#define NEED_TESTHELPER
#include "Animation.h"

class Animation_TestHelper {
	public:
		static int x(Animation& animation) {
			return animation.x;
		}

		static int y(Animation& animation) {
			return animation.y;
		}

		static int initialX(Animation& animation) {
			return animation.initialX;
		}

		static int initialY(Animation& animation) {
			return animation.initialY;
		}

		static int spriteWidth(Animation& animation) {
			return animation.spriteWidth;
		}

		static int spriteHeight(Animation& animation) {
			return animation.spriteHeight;
		}

		static int numberOfImages(Animation& animation) {
			return animation.numberOfImages;
		}

		static bool loop(Animation& animation) {
			return animation.loop;
		}

		static double totalElapsedTime(Animation& animation) {
			return animation.totalElapsedTime;
		}

		static double totalTime(Animation& animation) {
			return animation.totalTime;
		}

		static int animationCount(Animation& animation) {
			return animation.animationCount;
		}
};

TEST(Animation, ChangeWidthHeight) {
	int sw = 15;
	int sh = 16;
	Animation a{0, 0, sw, sh, 2, true};

	ASSERT_EQ(sw, Animation_TestHelper::spriteWidth(a));
	ASSERT_EQ(sh, Animation_TestHelper::spriteHeight(a));

	sw = 76;
	sh = 77;
	a.changeWidthHeight(sw, sh);

	ASSERT_EQ(sw, Animation_TestHelper::spriteWidth(a));
	ASSERT_EQ(sh, Animation_TestHelper::spriteHeight(a));
}

#undef NEED_TESTHELPER
