#pragma once

class AEMD5Animation {

public:

	AEMD5Animation();
	virtual ~AEMD5Animation();

	//Load an animation from the animation file
	bool loadMD5Animation(const std::string& filename);

	//Update the animation's joint set.
	void update(float deltaTime);

	//Draw the animated skeleton
	void render();

