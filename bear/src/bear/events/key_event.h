#pragma once

#include "event.h"

#include "bear/core/key_codes.h"

namespace bear {
	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return key_code_; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode key_code)
			: key_code_(key_code) {}

		KeyCode key_code_;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode key_code, int repeat_count)
			: KeyEvent(key_code), repeat_count_(repeat_count) {}

		uint16_t GetRepeatCount() const { return repeat_count_; }

		/*std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_ << " repeats)";
			return ss.str();
		}*/

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeat_count_;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode key_code)
			: KeyEvent(key_code) {}

		/*std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << key_code_;
			return ss.str();
		}*/

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(KeyCode key_code)
			: KeyEvent(key_code) {}

		/*std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << key_code_;
			return ss.str();
		}*/

		EVENT_CLASS_TYPE(KeyTyped)
	};
}