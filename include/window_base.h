#pragma once

namespace pathfinder { namespace view {

	class WindowBase : public Clickable
	{
	public:
		WindowBase() {};

		WindowBase& operator=(const WindowBase&) = delete;
		WindowBase(const WindowBase&) = delete;

		virtual ~WindowBase();

		sf::RenderWindow& getWindow();

		WindowBase& create(sf::VideoMode,
			const sf::String&,
			sf::Uint32 = sf::Style::Default,
			const sf::ContextSettings& = sf::ContextSettings());
		WindowBase& create(const sf::String& title);
		void run();
		WindowBase& activate();
		WindowBase& deactivate();

		virtual void onClose();

	protected:
		sf::RenderWindow window;
		std::thread pump_thread;

	private:
		void pump();
		void dispatchEvent(sf::Event);

		void setActive(bool active);

	};

}}