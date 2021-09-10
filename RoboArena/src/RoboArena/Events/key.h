#pragma once

#include "event.h"

class KeyEvent : public Event
{
public:
    inline int get_keycode() const { return m_keycode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(int keycode)
        : m_keycode(keycode) {}

    int m_keycode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode, int repeat_count)
        : KeyEvent(keycode), m_repeat_count(repeat_count) {}

    inline int get_repeat_count() const { return m_repeat_count; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeat_count << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
private:
    int m_repeat_count;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {}

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
