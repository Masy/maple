//
// Created by masy on 01.07.2023.
//

#include <stdexcept>
#include "maple/events/Event.hpp"
#include "maple/widgets/Widget.hpp"
#include "maple/widgets/Window.hpp"

using namespace maple::events;

std::unordered_map<maple::widgets::Widget*, std::multimap<std::type_index, std::function<void(maple::widgets::Widget *, const std::shared_ptr<maple::events::Event> &)>>> Event::eventHandlers{};

Event::Worker::Worker() {
	m_thread = std::thread([this] () {
		while (m_working) {
			std::unique_lock lock(m_mutex);
			if (m_eventQueue.empty()) {
				m_cv.wait(lock);
			}

			if (!m_eventQueue.empty()) {
				auto f_wrapper = m_eventQueue.front();
				m_eventQueue.pop();
				lock.unlock();
				f_wrapper();
			}
		}
	});
}

Event::Worker::~Worker() noexcept {
	m_working = false;
	m_cv.notify_one();

	if (m_thread.joinable()) {
		m_thread.join();
	}
}

void Event::Worker::push_back(const std::function<void()> &wrapper) {
	std::unique_lock lock(m_mutex);

	m_eventQueue.push(wrapper);

	lock.unlock();
	m_cv.notify_one();
}

std::thread::id Event::Worker::threadId() {
	return m_thread.get_id();
}

void Event::emit(widgets::Widget *widget) {
	if (widget == nullptr)
		throw std::invalid_argument("Failed to emit event: Widget can't be a nullptr!");

	auto *window = widget->window();
	if (window == nullptr)
		throw std::runtime_error("Failed to emit event: Widget is not attached to a window!");

	auto *worker = window->eventWorker();

	if (std::this_thread::get_id() == worker->threadId()) {
		auto range = eventHandlers.at(window).equal_range(std::type_index(typeid(*this)));
		for (auto &handler = range.first; handler != range.second; handler++) {
			if (this->cancelled())
				break;

			handler->second(widget, shared_from_this());
		}
	} else {
		bool finished = false;
		std::condition_variable cv;
		std::mutex mutex;
		worker->push_back([&, this] () {
			std::unique_lock lock(mutex);
			auto range = eventHandlers.at(window).equal_range(std::type_index(typeid(*this)));
			for (auto &handler = range.first; handler != range.second; handler++) {
				if (this->cancelled())
					break;

				handler->second(widget, shared_from_this());
			}

			finished = true;
			lock.unlock();
			cv.notify_one();
		});

		while (!finished) {
			std::unique_lock lock(mutex);
			cv.wait(lock);
		}
	}
}

void Event::emitAsync(widgets::Widget *widget) {
	if (widget == nullptr)
		throw std::invalid_argument("Failed to asynchronously emit event: Widget can't be a nullptr!");

	auto *window = widget->window();
	if (window == nullptr)
		throw std::runtime_error("Failed to asynchronously emit event: Widget is not attached to a window!");

	window->eventWorker()->push_back([=, this] () {
		auto range = eventHandlers.at(window).equal_range(std::type_index(typeid(*this)));
		for (auto &handler = range.first; handler != range.second; handler++) {
			if (this->cancelled())
				break;

			handler->second(widget, shared_from_this());
		}
	});
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
