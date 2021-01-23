#include "Scoreboard.h"
#include <utility>

TextBox::TextBox(sf::Text Text) : m_Text(std::move(Text)) {
	m_NewText = m_Text.getString();
}

void TextBox::draw(sf::RenderTarget& Render, sf::RenderStates States) const {
	if (m_TextChanged) {
		const_cast<TextBox*>(this)->SetText(m_NewText);
		m_TextChanged = false;
	}
	Render.draw(m_Text, States);
}

void TextBox::Event(const sf::Event& event, int &choose) {
	if (event.type == sf::Event::TextEntered) {
		//Text handling
		m_TextChanged = true;
		if (m_Text.getString().getSize() < 12 || event.text.unicode == 0x8) {
			switch (event.text.unicode) {
			case 0x8: //Backspace
				if (!m_NewText.empty()) m_NewText.erase(m_NewText.size() - 1);
				break;
			case 0xD:
				choose = 4;
			default:
				if (event.text.unicode >= L'a' && event.text.unicode <= L'z' || event.text.unicode >= L'A' &&
					event.text.unicode <= L'Z' || event.text.unicode >= L'0' && event.text.unicode <= L'9' ||
					event.text.unicode == L' ') {
					m_NewText += event.text.unicode;
				}
			}
		}
	}
}

void TextBox::SetText(const sf::String& String) const {
	m_Text.setString(String);
}

std::string TextBox::GetText() const {
	std::string name = m_Text.getString();
	while (name.size() < 12) {
		name += " ";
	}
	bool empty = true;
	for (size_t i = 0; i < name.size(); i++) {
		if (name.at(i) != ' ') empty = false;
	}
	if (empty) {
		struct tm itm;
		time_t now = time(0);
		localtime_s(&itm, &now);
		int month = 1 + itm.tm_mon;
		int day = itm.tm_mday;
		int year = itm.tm_year - 100;
		std::string day_str, mon_str, year_str;
		day_str = std::to_string(day);
		mon_str = std::to_string(month);
		if (day < 10)
			day_str = "0" + std::to_string(day);
		if (month < 10)
			mon_str = "0" + std::to_string(month);
		year_str = std::to_string(year);
		name= "Digger" + day_str + mon_str + year_str;
	}
	return name;
}

FocusController::FocusController(FocusObject* Obj) : m_Object(Obj) {
}

void FocusController::SetFocusObject(FocusObject* NewObj) {
	if (m_Object == NewObj)
		return;
	m_Object = NewObj;
}

FocusObject* FocusController::GetFocusObject() const {
	return m_Object;
}
