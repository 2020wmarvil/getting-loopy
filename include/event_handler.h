#pragma once

#include "player.h"

class EventHandler {
private:
	Player *player;
	double player_speed = 5.0;

	bool quit = false;

	void handleKeyDownEvent(const SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE: {
				quit = true; 
				break;
			} case SDL_SCANCODE_W : {
				player->setVelocityY(player_speed);
				break;
			} case SDL_SCANCODE_S : {
				player->setVelocityY(-player_speed);
				break;
			} case SDL_SCANCODE_D : {
				player->setVelocityX(player_speed);
				break;
			} case SDL_SCANCODE_A : {
				player->setVelocityX(-player_speed);
				break;
			} default: {
				break;
			}
		}
	}
	
	void handleKeyUpEvent(const SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_W: {
				player->setVelocityY(0);
				break;
			} case SDL_SCANCODE_S : {
				player->setVelocityY(0);
				break;
			} case SDL_SCANCODE_D : {
				player->setVelocityX(0);
				break;
			} case SDL_SCANCODE_A : {
				player->setVelocityX(0);
				break;
			} default: {
				break;
			}
		}
	}
public:
	EventHandler(Player *player) { this->player = player; }
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
