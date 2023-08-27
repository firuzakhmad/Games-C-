#pragma once

class ISnakePlayer {
public:
	virtual ~ISnakePlayer() {}
	virtual void Start() = 0;
	// virtual void showEndMessage() = 0;
};