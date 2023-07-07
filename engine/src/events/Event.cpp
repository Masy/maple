//
// Created by masy on 01.07.2023.
//

#include <stdexcept>
#include "maple/events/Event.hpp"
#include "maple/widgets/Widget.hpp"
#include "maple/widgets/Window.hpp"
#include "maple/Application.hpp"

using namespace maple::events;

std::unordered_map<maple::widgets::Widget*, std::multimap<std::type_index, std::function<void(maple::widgets::Widget *, const std::shared_ptr<maple::events::Event> &)>>> Event::eventHandlers{};

void Event::emit(widgets::Widget *widget) {
	if (widget == nullptr)
		throw std::invalid_argument("Failed to emit event: Widget can't be a nullptr!");

	auto *app = maple::Application::getInstance();

	if (GetCurrentThreadId() == app->getThreadId()) {
		std::pair<handlerMultiMap_t::iterator, handlerMultiMap_t::iterator> range;
		try {
			range = eventHandlers.at(widget).equal_range(std::type_index(typeid(*this)));;
		} catch (const std::exception &) {
			return;
		}

		for (auto &handler = range.first; handler != range.second; handler++) {
			if (this->cancelled())
				break;

			handler->second(widget, shared_from_this());
		}
	} else {
		std::mutex mutex;
		std::condition_variable cv;
		bool finished = false;

		auto *winEvent = new maple::events::WinEvent();
		winEvent->event = shared_from_this();
		winEvent->widget = widget;
		winEvent->cv = &cv;
		winEvent->finished = &finished;

		try {
			winEvent->handlers = eventHandlers.at(widget).equal_range(std::type_index(typeid(*this)));
		} catch (const std::exception &ex) {
			return;
		}

		PostThreadMessageW(app->getThreadId(), app->getEventMessageId(), 0, (LPARAM) winEvent);

		while (!finished) {
			std::unique_lock lock(mutex);
			cv.wait(lock);
		}
	}
}

void Event::emitAsync(widgets::Widget *widget) {
	if (widget == nullptr)
		throw std::invalid_argument("Failed to asynchronously emit event: Widget can't be a nullptr!");

	auto *winEvent = new maple::events::WinEvent();
	winEvent->event = shared_from_this();
	winEvent->widget = widget;

	try {
		winEvent->handlers = eventHandlers.at(widget).equal_range(std::type_index(typeid(*this)));
	} catch (const std::exception &ex) {
		return;
	}

	auto *app = maple::Application::getInstance();
	PostThreadMessageW(app->getThreadId(), app->getEventMessageId(), 0, (LPARAM) winEvent);
}

bool Event::cancelled() const {
	return m_cancelled;
}

void Event::cancelled(const bool _cancelled) {
	m_cancelled = _cancelled;
}

void maple::events::disconnect(widgets::Widget *widget) {
	Event::eventHandlers.erase(widget);
}
