#include	<cstdlib>
#include	<DxLib.h>

#include	"../h/ErrorMessage.h"
#include	"../h/GraphicData.h"

template<typename T>void Font<T>::Draw(Vector2 pos, const char* font, Color c) {
	DrawString(pos.x, pos.y, font, c.color);
}
template<typename T>void Font<T>::Draw(Vector2 pos, std::string font, Color c) {
	DrawString(pos.x, pos.y, (const TCHAR*)&font, c.color);
}

template<typename T>void Font<T>::FDraw(Vector2 pos, const char* font, Color c, const T data) {
	while (data != nullptr) { DrawFormatString(pos.x, pos.y, c.color, font, data); }
}

template<typename T>void Font<T>::FDraw(Vector2 pos, std::string font, Color c, const T data) {
	while (data != nullptr) { DrawFormatString(pos.x, pos.y, c.color, font, data); }
}

template<typename T>void Font<T>::ExDraw(Vector2 pos, Vector2 size, const char* font, Color c, const T data) {
	while (data != nullptr) { DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, font, data); }
}

template<typename T>void Font<T>::ExDraw(Vector2 pos, Vector2 size, std::string font, Color c, const T data){
	while (data != nullptr) { DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, font, data); }
}

void Sound::operator=(const Sound& other) { this->m_sound = other.m_sound; }

const Sound& Sound::operator=(const Sound&& other) noexcept {
	this->m_sound = other.m_sound;

	return *this;
}

void Sound::SetVolume(double raito){
	ChangeVolumeSoundMem(int(255 * raito / 100), m_sound.GetSoundFile()); //0～255をまでをraito÷100で求めた倍率にする。
}

void Sound::Stop_And_Play() {
	SetFontSize(50);

	if (CheckSoundMem(m_sound.GetSoundFile()) == 0) {
		PlaySoundMem(m_sound.GetSoundFile(), m_type);
		DrawString(0, 0, "再生", 0x00ff00);
	}
	else if (CheckSoundMem(m_sound.GetSoundFile()) == 1 && m_type != NULL) {
		StopSoundMem(m_sound.GetSoundFile());
		DrawString(0, 0, "停止", 0xffffff);
	}

	SetFontSize(20);
}
void Image::operator=(const Image& other){
	this->m_image = other.m_image;

	GetGraphSize(m_image.GetImageFile(), (int*)&m_image_graphSize.x, (int*)&m_image_graphSize.y);
}

const Image& Image::operator=(const Image&& other) noexcept {
	this->m_image = other.m_image;

	GetGraphSize(m_image.GetImageFile(), (int*)&m_image_graphSize.x, (int*)&m_image_graphSize.y);

	return *this;
}

void Image::Draw(const Vector2& pos) {
	if(!m_image.CheckSetImageFile()) throw ErrorMassage("画像が設定されてないため、描画することができませんでした。");

	Vector2 half = m_image_graphSize / 2;
	DrawGraph(int(pos.x) - half.x, int(pos.y) - half.y, m_image.GetImageFile(), TRUE);
}

void Image::ExDraw_Limit(const Vector2& pos, const Vector2 limit) {
	if (!m_image.CheckSetImageFile()) throw ErrorMassage("画像が設定されてないため、描画することができませんでした。");

	DrawExtendGraph(int(pos.x), int(pos.y), int(limit.x), int(limit.y), m_image.GetImageFile(), TRUE);
}

void Image::ExDraw_Scale(const Vector2& pos, const Vector2 scale) {
	if (!m_image.CheckSetImageFile()) throw ErrorMassage("画像が設定されてないため、描画することができませんでした。");

	Vector2 r = { m_image_graphSize.x * scale.x / 2, m_image_graphSize.y * scale.y / 2 }; //倍率に合わせてサイズを変える

	DrawExtendGraph(int(pos.x), int(pos.y), int(pos.x) + int(r.x), int(pos.y) + int(r.y), m_image.GetImageFile(), TRUE);
}

void Image::SetImage(const std::string& file_name) {
	m_image.Destroy();

	m_image.LoadFile(file_name);

	int x = m_image_graphSize.x, y = m_image_graphSize.y;
	GetGraphSize(m_image.GetImageFile(), &x, &y);

	m_image_graphSize = Vector2(x, y);
}

void Movie::operator=(const Movie& other) {
	this->m_movie.operator=(other.m_movie);

	GetGraphSize(m_movie.GetMovieFile(), (int*)&m_movie_graphSize.x, (int*)&m_movie_graphSize.y);
}

const Movie& Movie::operator=(const Movie&& other) noexcept {
	if (this != &other) this->m_movie.operator=(other.m_movie);

	GetGraphSize(m_movie.GetMovieFile(), (int*)&m_movie_graphSize.x, (int*)&m_movie_graphSize.y);

	return *this;
}

void Movie::SetVolume(double raito) {
	SetMovieVolumeToGraph(int(10000 * raito / 100), m_movie.GetMovieFile()); //0～10000までをraito÷100で求めた倍率にする。
}

void Movie::Play(const Vector2& pos) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 p = { pos.x - m_movie_graphSize.x / 2, pos.y - m_movie_graphSize.y / 2 };

	DrawGraph(p.x, p.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::ExPlay_Scale(const Vector2& pos, const Vector2& scale) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 r = { m_movie_graphSize.x * scale.x / 2, m_movie_graphSize.y * scale.y / 2 };

	DrawExtendGraph(int(pos.x) - r.x, int(pos.y) - r.y, int(pos.x) + r.x, int(pos.y) + r.y, m_movie.GetMovieFile(), TRUE);
}
void Movie::ExPlay_Limit(const Vector2& pos, const Vector2& limit_pos) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 halfPos = m_movie_graphSize / 2;

	DrawExtendGraph(int(pos.x) - halfPos.x, int(pos.y) - halfPos.y,
		int(limit_pos.x) + halfPos.x, int(limit_pos.y) + halfPos.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::ExPlay(const Vector2& pos, const Vector2& limit_pos, const Vector2& scale) {
	if (!m_movie.CheckSetMovieFile()) throw ErrorMassage("Error::映像データが見つからないため、再生することができませんでした。");

	int nowFrame = TellMovieToGraphToFrame(m_movie.GetMovieFile());
	if (nowFrame >= m_movie.GetFrame()) { SeekMovieToGraph(m_movie.GetMovieFile(), 0); PlayMovieToGraph(m_movie.GetMovieFile()); } //再生位置を初期位置に戻して再生
	else if (nowFrame == 0) PlayMovieToGraph(m_movie.GetMovieFile()); //再生

	Vector2 r = { m_movie_graphSize.x * scale.x / 2, m_movie_graphSize.y * scale.y / 2 };

	DrawExtendGraph(int(pos.x) - r.x, int(pos.y) - r.y, int(limit_pos.x) + r.x, int(limit_pos.y) + r.y, m_movie.GetMovieFile(), TRUE);
}

void Movie::Stop_And_Play() {
	SetFontSize(50);

	if (GetMovieStateToGraph(m_movie.GetMovieFile()) == 0) {
		PlayMovieToGraph(m_movie.GetMovieFile());
		DrawString(0, 0, "再生", 0x00ff00);
	}

	else if (GetMovieStateToGraph(m_movie.GetMovieFile()) == 1) {
		PauseMovieToGraph(m_movie.GetMovieFile());
		DrawString(0, 0, "停止", 0xffffff);
	}

	SetFontSize(20);
}
