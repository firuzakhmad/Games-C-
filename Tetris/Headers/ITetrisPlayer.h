#pragma once

class ITetrisPlayer {
public:
	virtual ~ITetrisPlayer() {}
	virtual void play() = 0;
	virtual void showEndMessage() = 0;
};