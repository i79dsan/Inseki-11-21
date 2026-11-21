#include	"DxLib.h"
#include	"../h/TitleState.h"
#include	"../h/ErrorMessage.h"
#include "../Window.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//SetGraphMode(720, 720, 32);
	Window window;
	window.Init(Vector2(720.0, 720.0));
	SetGraphMode(
		static_cast<int>(window.GetSize().x),
		static_cast<int>(window.GetSize().y),
		window.GetColorBitDepth()
	);
	
	//SetGraphMode(window.GetWidth(), window.GetHeight(), window.GetColorBitDepth());
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	try {
		StateBase* state = new TitleState;
		state->Enter();

		while (1) {
			ClearDrawScreen();

			StateBase* next = state->Loop();

			if (state != next) {
				state->Exit();
				delete state;

				state = next;
				state->Enter();
			}

			ScreenFlip();
			WaitTimer(16);
			if (CheckHitKey(KEY_INPUT_0) == 1) break;
			if (ProcessMessage() == -1) break;
		}
	}
	catch (ErrorMassage massage) {
		ClearDrawScreen();

		massage.Show();

		ScreenFlip();

		WaitKey();
	}

	DxLib_End();
	return 0;
}