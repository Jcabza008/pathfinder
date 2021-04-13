#pragma once

namespace pathfinder { namespace view {

	class AppWindow : public WindowBase, public CompositeComponent
	{
	public:
		AppWindow();
		~AppWindow();

		AppWindow& create();
		void run();
		AppWindow& wait();
		AppWindow& clear();
		AppWindow& draw_window();
		AppWindow& display();

		bool isOpen();

	private:
		std::thread refresh_thread;

		void onClose() override;
		void onClick(sf::Event::MouseButtonEvent event) override;
		void onClickUp(sf::Event::MouseButtonEvent event) override;

		void drawing_loop();
		AppWindow& refresh_wait();
	};

}}