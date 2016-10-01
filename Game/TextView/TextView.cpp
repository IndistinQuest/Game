#include "TextView.h"

TextView::TextView(const String& text, const Point& pos, const int width, const int lines, const Font& font, int IntervalIncrease ,Color color)
	:str_m(text), font_m(font), pos_m(pos), IntervalIncrease_m(IntervalIncrease),
	maxLines_m(lines),lines_m(1),
	PositionToBreak_m(pos.x + width), isAutomaticLineBreak(true),
	color_m(color)
{
	curentAllPlotTime = 0;
	allPlotTime = 0;
}

TextView::~TextView() {};

void TextView::update() {
	if (!isPlotAll() && System::FrameCount() % IntervalIncrease_m == 0) {
		addCharacter();
	}
	if (isPlotAll()) {
		curentAllPlotTime++;
	}
}

void TextView::draw()const {
	font_m.draw(str_m.substr(0, count_m), pos_m,color_m);
}

void TextView::setNewText(const String& text) {
	str_m.clear();
	str_m = text;
	count_m = 0;
	lines_m = 1;
	curentAllPlotTime = 0;
}

bool TextView::isPlotAll()const {
	return str_m.length <= count_m;
}

void TextView::setPlotAll() {
	while (!isPlotAll()) {
		addCharacter();
	}
}

void TextView::setIntervalIncrease(int interval) {
	if (interval > 0) { IntervalIncrease_m = interval; }
	else { IntervalIncrease_m = 1; }
}

void TextView::debugDraw()const {
	Println(Format(L"文字数:"), count_m);
	Println(Format(L"表示間隔:", IntervalIncrease_m));
	Println(Format(L"全部表示しているか:", isPlotAll()));
	Rect(pos_m, PositionToBreak_m - pos_m.x, Window::Height()).draw(Color(Palette::Blue).setAlpha(100));
	font_m.region(str_m.substr(0, count_m), pos_m).draw(Color(Palette::Pink).setAlpha(50));
}

void TextView::addCharacter() {
	try
	{
		if (isAutomaticLineBreak &&  getStrRigthPos() > PositionToBreak_m) {
			str_m.insert(count_m, L"\n");
			count_m++;
			lines_m++;
			if (lines_m > maxLines_m)throw -1;
		}
		count_m++;
	}
	catch(const int e)
	{
		if(e==-1)
		Println(L"文字数が多すぎます\n キーボードのキーを押すと続行");
		WaitKey();
	}
}

int TextView::getStrRigthPos() {
	return (font_m.region(str_m.substr(0, count_m + 1), pos_m)).tr.x;
}

void TextView::setAllPlotTime(unsigned time) {
	allPlotTime = time;
}

bool TextView::isAllPoltAndOverTime() {
	return allPlotTime < curentAllPlotTime;
}
