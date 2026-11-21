#include	"../h/ResultState.h"
#include	"../h/TitleState.h"

void ResultState::Enter() {
	m_images[0].SetImage("Lose.png"); m_images[1].SetImage("Win.png");
}

StateBase* ResultState::Loop() {
	DrawString(0, 0, "Result", 0xffffff);

	m_images[m_resultFlag].ExDraw_Limit(Vector2(0, 0), Vector2(1080, 720));

	m_player.GetInput().Update();
	if (m_player.GetInput().GetKeyDown(KEY_INPUT_ESCAPE)) return new TitleState;
	return this;
}

void ResultState::Exit() {

}