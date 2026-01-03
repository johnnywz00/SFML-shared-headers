//
//  vsprite.hpp
//  Hopscotch
//
//  Created by John Ziegler on 10/29/24.
//  Copyright © 2024 John Ziegler. All rights reserved.
//

#ifndef vsprite_hpp
#define vsprite_hpp

#include "zsprite.hpp"


	/* Sprites that use velocity */

class VSprite : public ZSprite {
public:
	
	void setVelocity (float x, float y) {
		
		velocity = vecF(x, y);
		if (speedClamp && mag() < speedClamp)
			velocity = vecf(0, 0);
	}

	void setVelocity (vecF vec)
	{
		velocity = vec;
		if (speedClamp && mag() < speedClamp)
			velocity = vecf(0, 0);
	}
	
	void setVelocityP (float mag, float direc)
	{
		float magVal = abs(mag);
		if (speedClamp && 0 < magVal && magVal < speedClamp) {
			velocity = vecf(0, 0);
			return;
		}
		if (mag < 0) {
			mag = abs(mag);
			direc += 180;
		}
		auto vp = vecF(mag, czdg(direc));
		velocity = toRect(vp);
	 }

	void setVelocityP (vecF v)
	{
		setVelocityP(v.x, v.y);
	}

	void addVelocity (float x, float y)
	{
		velocity.x += x;
		velocity.y += y;
		if (speedClamp && mag() < speedClamp)
			velocity = vecf(0, 0);
	}
	
	void addVelocity (vecf v)
	{
		velocity += v;
		if (speedClamp && mag() < speedClamp)
			velocity = vecf(0, 0);
	 }

	void addVelocityP (float mag, float direc)
	{
		addVelocity(toRect(abs(mag), czdg(direc + (mag < 0 ? 180 : 0))));
	}
	
	void addVelocityP (vecf v)
	{
		addVelocity(toRect(abs(v.x), czdg(v.y + (v.x < 0 ? 180 : 0))));
	}
	
	void setMag (float mag)
	{
		setVelocityP(mag, pvelocity().y);
	}
	
	void addMag (float q)
	{
		setVelocityP(pvelocity().x + q, pvelocity().y);
	}
	
	void setDirec (float direc)
	{
		setVelocityP(pvelocity().x, direc);
	}
	
	void setDx	(float dx)
	{
		setVelocity(dx, velocity.y);
	}
	
	void setDy (float dy)
	{
		setVelocity(velocity.x, dy);
	}
	
	vecF pvelocity ()
	{
		return toPolar(velocity);
	}
	
	float mag ()
	{
		return pvelocity().x;
	}
	
	float direc ()
	{
		return pvelocity().y;
	}
	
	float oppDirec ()
	{
		return czdg(pvelocity().y + 180);
	}
	
	float dx ()
	{
		return velocity.x;
	}
	
	float dy ()
	{
		return velocity.y;
	}
	
	void backUp (float units)
	{
		vecF v = vecF(units, czdg(direc() + 180));
		s.move(toRect(v));
	}
	
	
	vecF    velocity = vecF(0.f, 0.f);
	float   friction = .13;		// val if friction is subtracted per frame
	float   xfriction = .85;	// val if friction is multiplied per frame
	float	speedClamp = 0;
	float	maxSpeed = 999;

};	// end class





#endif /* vsprite_hpp */
