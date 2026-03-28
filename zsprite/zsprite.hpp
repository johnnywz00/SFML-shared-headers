#ifndef ZSPRITE_HPP
#define ZSPRITE_HPP


#include "jwzsfml.hpp"

class ZSprite : public Drawable
{
public:
#ifndef SFML_3
    ZSprite () { setup(); }
#endif
	ZSprite (const Texture &texture)
		: s(texture)
	{
		setup();
	}

	ZSprite (const Texture &texture, const IntRect &rectangle)
		: s(texture)
	{
		s.setTextureRect(rectangle);
		setup();
	}

	virtual ~ZSprite () { }
	
	virtual void setup () { }

	virtual void update (const Time& t = Time::Zero) { }

	virtual void draw (RenderTarget& target, RenderStates states) const
	{
		target.draw(s);
	}

//============================================================================//

		/* Get values from hitBox() */
#ifdef SFML_3
	float width () { return hitBox().size.x; }
	
	float height () { return hitBox().size.y; }
	
	float top () { return hitBox().position.y; }
	
	float bottom () { return hitBox().position.y + hitBox().size.y - 1; }
	
	float left () { return hitBox().position.x;}
	
	float right () { return hitBox().position.x + hitBox().size.x - 1; }
#else
	float width () { return hitBox().width; }
	
	float height () { return hitBox().height; }
	
	float top () { return hitBox().top; }
	
	float bottom () { return hitBox().top + hitBox().height - 1; }
	
	float left () { return hitBox().left;}
	
	float right () { return hitBox().left + hitBox().width - 1; }
#endif
	vecF bottomLeft () { return {left(), bottom()}; }
   
	vecF bottomRight() { return {right(), bottom()}; }
   
	vecF topLeft() { return {left(), top()}; }
   
	vecF topRight() { return {right(), top()}; }

	
		/* Set sprite position with reference to an edge of hitBox() */
	void setTop (float y)
	{
		sP(gP().x, y - hbofs() + getOrigin().y);
	}
	
	void setBottom (float y)
	{
		sP(gP().x, y + 1 + hbofs() - (height() - getOrigin().y));
	}
	
	void setLeft (float x)
	{
		sP(x - hbofs() + getOrigin().x, gP().y);
	}
	
	void setRight (float x)
	{
		sP(x + 1 + hbofs() - (width() - getOrigin().x), gP().y);
	}
 
	
		/* Get values from getGlobalBounds() */
#ifdef SFML_3
	float gWidth () { return gGB().size.x; }
	
	float gHeight () { return gGB().size.y; }
	
	float gTop () { return gGB().position.y; }
	
	float gBottom () { return gGB().position.y + gGB().size.y - 1; }
	
	float gLeft () { return gGB().position.x; }
	
	float gRight () { return gGB().position.x + gGB().size.x - 1; }
#else
	float gWidth () { return gGB().width; }

	float gHeight () { return gGB().height; }

	float gTop () { return gGB().top; }

	float gBottom () { return gGB().top + gGB().height - 1; }

	float gLeft () { return gGB().left; }

	float gRight () { return gGB().left + gGB().width - 1; }
#endif
		/* Set sprite position with reference to an edge of getGlobalBounds() */
	void setgTop (float y)
	{
		sP(gP().x, y + getOrigin().y);
	}
	
	void setgBottom (float y)
	{
		sP(gP().x, y + 1 - (height() - getOrigin().y));
	}
	
	void setgLeft (float x)
	{
		sP(x + getOrigin().x, gP().y);
	}
	
	void setgRight (float x)
	{
		sP(x + 1 - (width() - getOrigin().x), gP().y);
	}
 
//============================================================================//
	
	virtual void centerOn (float x, float y)
	{
		auto oldOgn = getOrigin();
		centerOrigin();
		sP(x, y);
		setOrigin(oldOgn);
	}

	virtual void centerOn (vecF pos) { centerOn(pos.x, pos.y); }

	virtual void centerOrigin () { ::centerOrigin(s); }


#ifdef SFML_3
	float getRadRotation() const { return getRotation().asRadians(); }
	
	virtual void setRadRotation (float rot) { s.setRotation(radians(rot)); }
#else
	float getRadRotation() const { return toRad(getRotation()); }
	
	virtual void setRadRotation (float rot) { s.setRotation(toDeg(rot)); }
#endif
	virtual FloatRect clickBox () { return gGB(); }

		/* hitBox() offset, for use when we want the
		 * collision capsule to simply be a certain number
		 * of pixels in from the borders of getGlobalBounds
		 */
	virtual float hbofs () { return hbofs_; }
    
	virtual FloatRect hitBox ()
	{
		FloatRect gb = gGB();
#ifdef SFML_3
		return FloatRect({gb.position.x + hbofs(), gb.position.y + hbofs()},
						 {gb.size.x - 2 * hbofs(), gb.size.y - 2 * hbofs()});
#else
    	return FloatRect(gb.left + hbofs(), gb.top + hbofs(),
						 gb.width - 2 * hbofs(), gb.height - 2 * hbofs());
#endif
	}
	
	FloatRect baseline ()
	{
		FloatRect hb = hitBox();
#ifdef SFML_3
		return FloatRect({hb.position.x, hb.position.y + hb.size.y - 1}, {hb.size.x, 1});
#else
		return FloatRect(hb.left, hb.top + hb.height - 1, hb.width, 1);
#endif
	}
		
		/* based on hitBox(), since collision checking is
		 * primary use. rotatedGContains for getGlobalBounds rect
		 */
	bool rotatedContains (float x, float y)
	{
#ifdef SFML_3
		return false;
#else
		vecf pt {x, y};
		float oldRot = getRotation();
			/*
			 * If the sprite is rectilinear, just return the
			 * result of the normal contains() algorithm
			 */
		if (	oldRot == 0 ||
				oldRot == 90 ||
				oldRot == 270 ||
				oldRot == 180)
			return hitBox().contains(x, y);
		
			/*
			 * Temporarily rectify the sprite so we can figure out
			 * where the corners of the bounding rectangle would be
			 * in relation to the origin
			 */
		setRotation(0);
		FloatRect rect = hitBox();
			/* Return the sprite to its proper rotation */
		setRotation(oldRot);
		
		return _rotatedContainsCommon(rect, pt, oldRot);
#endif
	}
	
	
	bool rotatedGContains (float x, float y)
	{
#ifdef SFML_3
		return false;
#else
		vecf pt {x, y};
		float oldRot = getRotation();
			/*
			 * If the sprite is rectilinear, just return the
			 * result of the normal contains() algorithm
			 */
		if (	oldRot == 0 ||
				oldRot == 90 ||
				oldRot == 270 ||
				oldRot == 180)
			return getGlobalBounds().contains(x, y);
		
			/*
			 * Temporarily rectify the sprite so we can figure out
			 * where the corners of the bounding rectangle would be
			 * in relation to the origin
			 */
		setRotation(0);
		FloatRect rect = getGlobalBounds();
			/* Return the sprite to its proper rotation */
		setRotation(oldRot);
		
		return _rotatedContainsCommon(rect, pt, oldRot);
#endif
	}
	
private:
	bool _rotatedContainsCommon (FloatRect rect, vecf pt, float oldRot) const
	{
#ifdef SFML_3
		return false;
#else
		vecf 	topL { rect.left, rect.top },
				topR { rect.left + rect.width, rect.top },
				botR { rect.left + rect.width, rect.top + rect.height },
				botL { rect.left, rect.top + rect.height };
		auto ogn = getPosition();
		 /* Store the polar vectors from the origin to each (rectified)
		 * corner so we can simply add the degrees of rotation to them
		 */
		vecf 	tlDif = topL - ogn,
				trDif = topR - ogn,
				brDif = botR - ogn,
				blDif = botL - ogn;
		tlDif = toPolar(tlDif);
		trDif = toPolar(trDif);
		brDif = toPolar(brDif);
		blDif = toPolar(blDif);
		 /* Compute where the rotated corners of the original bounding
		 * box are now located
		 */
		vecf 	rotTl = ogn + toRect(tlDif.x, czdg(tlDif.y + oldRot)),
				rotTr = ogn + toRect(trDif.x, czdg(trDif.y + oldRot)),
				rotBr = ogn + toRect(brDif.x, czdg(brDif.y + oldRot)),
				rotBl = ogn + toRect(blDif.x, czdg(blDif.y + oldRot));
		 /* Make lines connecting the rotated bounding corners, and
		 * determine if the xy arguments are inside the area
		 */
		Line 	topSide { rotTl, rotTr },
				rightSide { rotTr, rotBr },
				bottomSide { rotBr, rotBl },
				leftSide { rotBl, rotTl };

		if (clockwiseOf(oldRot, 270)) {
			return 	topSide.yIsLessThan(pt) &&
					rightSide.xIsGreaterThan(pt) &&
					bottomSide.yIsGreaterThan(pt) &&
					leftSide.xIsLessThan(pt)
			;
		}
		else {
			return 	topSide.yIsGreaterThan(pt) &&
					rightSide.xIsLessThan(pt) &&
					bottomSide.yIsLessThan(pt) &&
					leftSide.xIsGreaterThan(pt)
			;
		}
#endif
	}

//============================================================================//

public:
	/* Sprite methods: making them virtual to allow
	 * for the possibility of composite object subclasses that may
	 * want to manipulate more than one sf::Drawable/Transformable
	 */
	
	virtual void setTexture (const Texture& tx, bool resetRect = false)
	{
		s.setTexture(tx, resetRect);
	}
	
	virtual void setTextureRect(const IntRect & r) {
		s.setTextureRect(r);
	}
	
	virtual void setColor (const Color& c)
	{
		s.setColor(c);
	}
#ifdef SFML_3
	virtual const Texture& getTexture () const
#else
	virtual const Texture* getTexture () const
#endif
	{
		return s.getTexture();
	}
	
	virtual const IntRect& getTextureRect () const
	{
		return s.getTextureRect();
	}
#ifdef SFML_3
	virtual Color getColor () const
#else
	virtual const Color& getColor () const
#endif
	{
		return s.getColor();
	}
	
	virtual FloatRect getLocalBounds () const
	{
		return s.getLocalBounds();
	}
	
	virtual FloatRect getGlobalBounds () const
	{
		return s.getGlobalBounds();
	}
	
	virtual void setPosition (float x, float y)
	{
		s.setPosition({x, y});
	}
	
	virtual void setPosition (const Vector2f& pos)
	{
		if (isnan(pos.x) || isnan(pos.y) || isinf(pos.x) || isinf(pos.y)) { // ///////// DEBUG
			setColor(Color::Black);
		}
		s.setPosition(pos);
	}
	
	virtual void setRotation (float ang)
	{
#ifdef SFML_3
		s.setRotation(degrees(ang));
#else
		s.setRotation(ang);
#endif
	}
	
	virtual void setScale (float x, float y)
	{
		s.setScale({x, y});
	}
	
	virtual void setScale (const Vector2f& factors)
	{
		s.setScale(factors);
	}
	
	virtual void setOrigin (float x, float y)
	{
		s.setOrigin({x, y});
	}
	
	virtual void setOrigin (const Vector2f ogn)
	{
		s.setOrigin(ogn);
	}
#ifdef SFML_3
	virtual Vector2f getPosition () const
#else
	virtual const Vector2f& getPosition () const
#endif
	{
		return s.getPosition();
	}
#ifdef SFML_3
	virtual Angle getRotation () const
#else
	virtual float getRotation () const
#endif
	{
		return s.getRotation();
	}
#ifdef SFML_3
	virtual Vector2f getScale () const
#else
	virtual const Vector2f& getScale () const
#endif
	{
		return s.getScale();
	}
#ifdef SFML_3
	virtual Vector2f getOrigin () const
#else
	virtual const Vector2f& getOrigin () const
#endif
	{
		return s.getOrigin();
	}
	
	virtual void move (float x, float y)
	{
		s.move({x, y});
	}
	
	virtual void move (const Vector2f& ofs)
	{
		s.move(ofs);
	}
#ifdef SFML_3
	virtual void rotate (float ang) { s.rotate(degrees(ang)); }
	
	virtual void rotate (Angle ang) { s.rotate(ang); }
#else
	virtual void rotate (float ang)
	{
		s.rotate(ang);
	}
#endif
	
	virtual void scale (float x, float y)
	{
		s.scale({x, y});
	}
	
	virtual void scale (const Vector2f& factors)
	{
		s.scale(factors);
	}
	
	virtual const Transform& getTransform () const
	{
		return s.getTransform();
	}
	
	virtual const Transform& getInverseTransform () const
	{
		return s.getInverseTransform();
	}

	
	Sprite 			s;
	float			hbofs_ = 0;
	unsigned int    id = 0;
	bool    		clickedOn = false;
	
}; //end class ZSprite


//============================================================================//
//	RELATED TOP-LEVEL FUNCTIONS

inline void centerOrigin (ZSprite& obj)
{
	obj.centerOrigin();
}

inline void initSprite (ZSprite& spr, const Texture& tx, const vecF& pos, bool centerOgn=false)
{
	spr.setTexture(tx);
	if (centerOgn)
		centerOrigin(spr);
	spr.setPosition(pos);
}
#ifdef SFML_3
inline bool hitL (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.left(), isct.position.x, isct.position.x + isct.size.x - 1);
}

inline bool hitR (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.right(), isct.position.x, isct.position.x + isct.size.x - 1);
}

inline bool hitTop (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.top(), isct.position.y, isct.position.y + isct.size.y - 1);
}

inline bool hitBot (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.bottom(), isct.position.y, isct.position.y + isct.size.y - 1);
}
#else
inline bool hitL (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.left(), isct.left, isct.left + isct.width - 1);
}

inline bool hitR (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.right(), isct.left, isct.left + isct.width - 1);
}

inline bool hitTop (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.top(), isct.top, isct.top + isct.height - 1);
}

inline bool hitBot (ZSprite& z, FloatRect& isct)
{
	return isOrBetween(z.bottom(), isct.top, isct.top + isct.height - 1);
}
#endif
inline bool hitTopL (ZSprite& z, FloatRect& isct)
{
	return hitTop(z, isct) && hitL(z, isct);
}

inline bool hitTopR (ZSprite& z, FloatRect& isct)
{
	return hitTop(z, isct) && hitR(z, isct);
}

inline bool hitBotR (ZSprite& z, FloatRect& isct)
{
	return hitBot(z, isct) && hitR(z, isct);
}

inline bool hitBotL (ZSprite& z, FloatRect& isct)
{
	return hitBot(z, isct) && hitL(z, isct);
}

#endif  /* ZSPRITE_HPP */

