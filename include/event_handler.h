#pragma once

class EventHandler {
private:
	bool quit = false;

	void handleKeyDownEvent(const SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE: {
				quit = true; 
				break;
			} default: {
				break;
			}
		}
	}
	
	void handleKeyUpEvent(const SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_W: {
				break;
			} default: {
				break;
			}
		}
	}
public:
	EventHandler() {}
	~EventHandler() {}

	int handleEvent(const SDL_Event &event) {
		switch(event.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			} case SDL_KEYDOWN: {
				handleKeyDownEvent(event.key);
				break;
			} case SDL_KEYUP: {
				handleKeyUpEvent(event.key);
				break;
			}
		}

		if (quit) return 1;

		return 0;
	}
};
