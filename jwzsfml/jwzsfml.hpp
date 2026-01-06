#ifndef jwzsfml_hpp
#define jwzsfml_hpp


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "jwz.hpp"

using namespace sf;

#define ikp(k) if (sf::Keyboard::isKeyPressed(sf::Keyboard::k))
#define iKP(k) sf::Keyboard::isKeyPressed(sf::Keyboard::k)
#define iBP sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define vecU Vector2u
#define vecI Vector2i
#define vecF Vector2f
#define vecf Vector2f
#define vec3u Vector3u
#define vec3i Vector3i
#define vec3f Vector3f
#define gP getPosition
#define sP setPosition
#define gRot getRotation
#define sRot setRotation
#define gLB getLocalBounds
#define gGB getGlobalBounds
#define gTR getTextureRect
#define gVC getVertexCount
#define cO centerOrigin
#define VX(X, Y) Vertex(Vector2f(X, Y), Color::Black)
#define VXC(X, Y, C) Vertex(Vector2f(X, Y), C)
#define VTX(pt) Vertex(pt, Color::Black)
#define VTXC(pt, C) Vertex(pt, C)
#define appendPt(pt) append(Vertex(pt, Color::Black))
#define appendPtC(pt, C) append(Vertex(pt, C))
#define appendCoords(X, Y) append(Vertex(Vector2f(X, Y), Color::Black))
#define appendCoordsC(X, Y, C) append(Vertex(Vector2f(X, Y), C))

#define adjustVal(key, prop, inc, min, max) \
	ikp(key){ \
		if (iKP(LShift)) prop = decm(prop, inc, min); \
		else prop = incm(prop, inc, max); \
		PAUSE1; \
	}


    /* These values were hardcoded into many hours of my early work,
     * specific to the laptop screen size I had at the time. Leave them
     * stand while this file acts as a shared header.
     */
constexpr int       ScrW = 1440;
constexpr int       ScrH = 900;
constexpr float     ScrCX = ScrW / 2;
constexpr float     ScrCY = ScrH / 2;

#define scrw SCRW()
#define scrh SCRH()
#define scrcx SCRCX()
#define scrcy SCRCY()

inline bool isCmdPressed () { return iKP(LSystem) || iKP(RSystem); }

inline bool isShiftPressed () { return iKP(LShift) || iKP(RShift); }

inline bool isOptionPressed () { return iKP(LAlt) || iKP(RAlt); }

inline string vecfStr (vecF v, string tag = "")
{
    string ret = "{" + fS(v.x) + ", " + fS(v.y) + "}";
    return tag.length() ? tag + ": " + ret : ret;
}

inline string rectStr (const FloatRect& rect)
{
	stringstream ss;
	ss << "{TL: " << rect.left << ", " << rect.top << "; " <<
	rect.width << " x " << rect.height << '}';
	return ss.str();
}

inline string rectStr (const IntRect& rect)
{
	stringstream ss;
	ss << "{TL: " << rect.left << ", " << rect.top << "; " <<
	rect.width << " x " << rect.height << '}';
	return ss.str();
}

inline Vector2i toVecI (const Vector2f& vec)
{
	return Vector2i(vec.x, vec.y);
}

inline Vector2f toVecF (const Vector2i& vec)
{
	return Vector2f(vec.x, vec.y);
}

inline Vector2f toVecF (const Vector2u& vec)
{
	return Vector2f(vec.x, vec.y);
}


inline void centerOrigin (Shape& obj)
{
    obj.setOrigin( 	obj.getLocalBounds().width / 2,
    				obj.getLocalBounds().height / 2 );
}

inline void centerOrigin (Sprite& obj)
{
    obj.setOrigin( 	obj.getLocalBounds().width / 2,
    				obj.getLocalBounds().height / 2 );
}

inline void centerOrigin (Text& obj) {
	
    obj.setOrigin( 	obj.getLocalBounds().width / 2,
    				obj.getLocalBounds().height / 2 );
}

//inline void centerOn (& obj, & target)    //TEMPLATE FUNCTION
//{
//	auto saveOgn = obj.getOrigin();
//	cO(obj);
//	//
//	obj.setOrigin(saveOgn);
//}

inline bool ptHasValidNumbers(const vecf& pt)
{
	return !(isnan(pt.x)
			 || isnan(pt.y)
			 || isinf(pt.x)
			 || isinf(pt.y));
}

inline bool epsEquals (vecf& v1, vecf& v2, float eps = floatEps)
{
	return epsEquals(v1.x, v2.x, eps) && epsEquals(v1.y, v2.y, eps);
}

inline bool epsEquals (vec3f& v1, vec3f& v2, float eps = floatEps)
{
	return epsEquals(v1.x, v2.x, eps) && epsEquals(v1.y, v2.y, eps)
			&& epsEquals(v1.z, v2.z, eps);
}

inline vecf mean (vecf v1, vecf v2)
{
	return v1 + (v2 - v1) / 2.f;
}

inline vec3f mean (vec3f v1, vec3f v2)
{
	return v1 + (v2 - v1) / 2.f;
}

inline float hyp (vecF& v1, vecF& v2) {
	
    auto X = v2.x - v1.x;
    auto Y = v2.y - v1.y;
    return abs(sqrt(X * X + Y * Y));
}

inline float hyp (const vecF& v1, const vecF& v2) {
	
	auto X = v2.x - v1.x;
	auto Y = v2.y - v1.y;
	return abs(sqrt(X * X + Y * Y));
}


inline float hyp (vecF& v) {
	
    return abs(sqrt( (v.x * v.x) + (v.y * v.y) ));
}

inline float hyp (Vector3f v1, Vector3f v2)
{
	float x = v2.x = v1.x;
	float y = v2.y = v1.y;
	float z = v2.z = v1.z;
	return abs(sqrt(x * x + y * y + z * z));
}

inline float hyp (Vector3f v)
{
	return abs(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float hyp (float x, float y, float z)
{
	return abs(sqrt(x * x + y * y + z * z));
}


inline vecF toRect (vecF& vec) {
	
    vecF ret(cos(toRad(vec.y)) * vec.x, sin(toRad(vec.y)) * vec.x);
    if (abs(vec.y) == 90 || abs(vec.y) == 270)  
    	ret.x = 0;
    if (abs(vec.y) == 0 || abs(vec.y) == 180)  
    	ret.y = 0;
    if (epsEquals(vec.x,0)) {
    	ret.x = 0;
    	ret.y = 0; 
    }
    return ret;
}

inline vecF toRect (float mag, float direc) {
	
    vecF ret(cosd(direc) * mag, sind(direc) * mag);
    if (abs(direc) == 90 || abs(direc) == 270)
        ret.x = 0;
    else if (abs(direc) == 0 || abs(direc) == 180)
        ret.y = 0;
	if (epsEquals(mag, 0)) {
        ret.x = 0;
        ret.y = 0;
    }
    return ret;
}

    // to rectangular coordinates given a vector in radians
inline vecF toRectFromRads (float mag, float direc) {
	
    vecF ret(cos(direc) * mag, sin(direc) * mag);
    if (epsEquals(mag, 0)) {
        ret.x = 0;
        ret.y = 0;
    }
    return ret;
}
#define toRRect toRectFromRads

inline vecF toPolar (vecF& vec) {
	
    double x = double(vec.x);
    double y = double(vec.y);
    double mag = hyp(x, y);
    double ang = atan2(y, x);
    float direc = float(toDeg(ang));
    if (direc < 0)
        direc += 360;
    return vecF(float(mag), direc);
}

inline vecF toPolar (const vecF& vec) {   //////
	
	double x = double(vec.x);
	double y = double(vec.y);
	double mag = hyp(x, y);
	double ang = atan2(y, x);
	float direc = float(toDeg(ang));
	if (direc < 0)
		direc += 360;
	return vecF(float(mag), direc);
}

inline vecF toPolar (float xx, float yy) {
	
    double x = double(xx);
    double y = double(yy);
    double mag = hyp(x, y);
    double ang = atan2(y, x);
    float direc = float(toDeg(ang));
    if (direc < 0)
        direc += 360;
    return vecF(float(mag), direc);
}

inline vecF toPolarWithRads (vecF& vec)
{
    double x = double(vec.x);
    double y = double(vec.y);
    double mag = hyp(x, y);
    double direc = atan2(y, x);
    return vecF(float(mag), float(direc));
}
#define toRPolar toPolarWithRads

inline vecF pVec (float mag, float dir)
{
	return toRect(mag, dir);
}

inline vec3f crossProd (vec3f v1, vec3f v2)
{
	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

inline float dotProd (vec3f v1, vec3f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float angleBetween (vec3f v1, vec3f v2)
{
	return toDeg(acos(dotProd(v1, v2) / (hyp(v1) * hyp(v2)) ));
}




inline void setVPos (Vertex& v, vecF pos) {
	
    v.position = pos;
}

inline void simpleOutline (Shape& s, Color c=Color::Black)
{
	s.setOutlineThickness(1);
	s.setOutlineColor(c);
}

inline void simpleOutline (Text& t, Color c=Color::Black)
{
	t.setOutlineThickness(1);
	t.setOutlineColor(c);
}

inline vecf rectCenter (const FloatRect& rect)
{
	return vecf(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

inline vecf rectCenter (const RectangleShape& rect)
{
	return rectCenter(rect.getGlobalBounds());
}

inline FloatRect rectWithAddedMarginOf (const FloatRect& rect, float margin)
{
	return FloatRect(rect.left - margin, rect.top - margin, rect.width + margin * 2, rect.height + margin * 2);
}

inline float triangleArea (const vecf& p1, const vecf& p2, const vecf& p3)
{
	float base = hyp(p1, p2);
	float ht = sind(angleBetween(toPolar(p2 - p1).y, toPolar(p3 - p1).y)) * hyp(p1, p3);
	return (base * ht) / 2;
}

/* To use vecF as key to a multimap */
class VecfMM
{
public:
	VecfMM(vecf v) : vec(v) {}
	vecf vec;
	bool operator<(const VecfMM& other) const
	{
		if (vec.x == other.vec.x)
			return vec.y < other.vec.y;
		return vec.x < other.vec.x;
	}
};





class Textbox : public Drawable
{
public:
	Textbox() { }
	Textbox(Font& font, vecf pos = {0, 0}, uint charSize = 12)
	{
		tbox.setSize({200, 20});
		tbox.setOutlineThickness(1);
		tbox.setOutlineColor(Color(165, 149, 130));
		tbox.setFillColor(Color(255, 255, 255, 60));
		highlight.setSize(tbox.getSize() + vecf{8, 8});
		highlight.setFillColor(Color(255, 218, 169, 90));
		setPosition(pos);
		boxTxt.setFont(font);
		boxTxt.setCharacterSize(charSize);
		boxTxt.setFillColor(Color(57, 65, 111));
		cursor.setSize(vecf(1, tbox.getSize().y - borderOffset.y * 2));
		cursor.setFillColor(Color::Red);
		moveCursorToTxtEnd();
	}
	
	void draw(RenderTarget& w, RenderStates st) const override
	{
		if (!onlyShowText)
			w.draw(tbox);
		if (isActive)
			w.draw(highlight);
		w.draw(boxTxt);
		w.draw(cursor);
	}
	
	void clear()
	{
		boxTxt.setString("");
		moveCursorToTxtEnd();
	}
	
	void setText(String text)
	{
		boxTxt.setString(text);
		moveCursorToTxtEnd();
	}
	
	void appendText(String text)  //sf::String to receive event unicode
	{
		boxTxt.setString(boxTxt.getString() + text);
		moveCursorToTxtEnd();
	}
	
	void deleteLastChar()
	{
		string str = boxTxt.getString();
		if (!str.empty())
			str.pop_back();
		boxTxt.setString(str);
	}
	
	void setPosition(vecf pos)
	{
		tbox.setPosition(pos);
		highlight.setPosition(pos - vecf{4, 4});
		boxTxt.setPosition(tbox.gP() + borderOffset);
		moveCursorToTxtEnd();
	}
	
	void setActive(bool stat) { isActive = stat; }
	
	RectangleShape		tbox;
	RectangleShape		cursor;
	RectangleShape		highlight;
	Text				boxTxt;
	vecf				borderOffset {2, 2};
	bool				isActive;
	bool				onlyShowText = false;
	string				name;
	
private:
	void moveCursorToTxtEnd() {
		cursor.setPosition(boxTxt.getPosition().x + boxTxt.getLocalBounds().width + 1, tbox.getPosition().y + borderOffset.y);
	}
};

/*
 CURSOR ISN'T STAYING AT END OF CHARS AFTER BACKSPACE
 
 -keep textboxes in map or vector, set name to map key
 
 -if single textbox is member of the State, assign to it w args in onCreate
 
 
	// EVENT HANDLING  (in pollEvent)
 if (state.filenameTbox.isActive && event.type == Event::TextEntered) {
	 if (event.text.unicode == 8)
		 state.filenameTbox.deleteLastChar();
	 else state.filenameTbox.appendText(event.text.unicode);
 }
 else {
	 switch(event.type) {
 ======= EXPANDED FORM ========
 if (state.activeTbox
		 && (event.type == Event::TextEntered
			 || event.type == Event::KeyPressed
			 || event.type == Event::KeyReleased)) {
	 if (event.type == Event::TextEntered) {
		 if (event.text.unicode == 8)
			 if (iKP(LShift))
				 state.activeTbox->clear();
			 else state.activeTbox->deleteLastChar();
		 else if (event.text.unicode == 9) ; // Don't write the \t
		 else state.activeTbox->appendText(event.text.unicode);
	 }
	 if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter)) {
		 state.activeTbox->setActive(false);
		 state.activeTbox = nullptr;
	 }
 }
 else {
	 switch(event.type) {
 
 
 
onClick() { setActive(true); } //else deactivate if click not in gLB
 
draw()
 
 - SFML TextEntered: event.text.unicode: 8 = Backspace, 13 = Enter, 9 = Tab
 - When letter key or Enter/Backspace/Tab (other?) are pressed, SFML receives both a KeyPressed and a TextEntered event. Shift/Command/Escape etc. are only KeyPressed events. To handle text input without triggering effects of hotkeys, must put if conditions and separate blocks in the event polling part of the application based on whether a text input field is active.
 */




class IDraggable
{
public:
	virtual bool respondsToClick(int x, int y) { return false; }
	virtual void startDrag() { } //(e.g. textBox setActive)
	// set ≈State.curDragged
	virtual void dragTo(int x, int y) { } //(move logic in update or mouseMoved)
	virtual void endDrag(int x, int y) { } //onMouseUp
};



struct LineSegment;
struct Arc;

struct Line
{
	Line ()
	{
		Line(vecf{0, 0}, vecf{1000, 0});
	}
	
	Line (const Line& l) : Line(l.pt1, l.pt2) {	}
	
	Line (const vecf& p1, const vecf& p2)
		: pt1(p1)
		, pt2(p2)
	{
		setValuesFromTwoPoints(pt1, pt2);
	}
	
	Line (float sl, const vecf p1)
		: slope(sl)
		, pt1(p1)
	{
		if (std::isinf(slope))
			pt2 = vecf(pt1.x, pt1.y + 1000);
		else pt2 = pt1 + vecf(1000, 1000 * slope);
		setValuesFromTwoPoints(pt1, pt2);
	}
	
	bool yIsLessThan (vecf pt) const
	{
		if (isVertical())
			return false; ///// ??
		return pt.y > slope * pt.x + yIcpt;
	}
	
	bool xIsLessThan (vecf pt) const
	{
		if (isHorizontal())
			return false; //// ??
		return pt.x > invSlope * pt.y + xIcpt;
	}
	
	bool yIsGreaterThan (vecf pt) const
	{
		return !yIsLessThan(pt);
	}
	
	bool xIsGreaterThan (vecf pt) const
	{
		return !xIsLessThan(pt);
	}
	
	bool isVertical () const
	{
		return std::isinf(slope);
	}
	
	bool isHorizontal () const
	{
		return epsEquals(slope, 0);
	}
	
	bool isRectilinear () const
	{
		return isVertical() || isHorizontal();
	}
	
	virtual bool containsPoint (vecf pt) const
	{
		if (isVertical())
			return epsEquals(pt.x, xIcpt);
		else if (isHorizontal())
			return epsEquals(pt.y, yIcpt);
		return epsEquals(pt.y, slope * pt.x + yIcpt);
	}
	
	float getYWhenX (float x) const
	{
		if (isVertical()) {
			if (!epsEquals(x, xIcpt))
				return NAN;
			return 0; ///// another approach? callers check vertical first
		}
		return slope * x + yIcpt;
	}
	
	float getXWhenY (float y) const
	{
		if (isHorizontal()) {
			if (!epsEquals(y, yIcpt))
				return NAN;
			return 0; ///// another approach?
		}
		return invSlope * y + xIcpt;
	}
	
	vecf getPtWhenX (float x) const
	{
		if (isVertical() && !epsEquals(x, xIcpt))
				return {NAN, NAN};
		return vecf {x, getYWhenX(x)};
	}
	
	vecf getPtWhenY (float y) const
	{
		if (isHorizontal() && !epsEquals(y, yIcpt))
				return {NAN, NAN};
		return vecf {getXWhenY(y), y};
	}

	bool isParallelWith (const Line& l) const
	{
		/* Use the "disregard infinity sign" parameter so that all vertical
		 * lines will register as parallel.
		 */
		if (isVertical())
			return l.isVertical();
		else if (isHorizontal())
			return l.isHorizontal();
		else return epsEquals(slope, l.slope, floatEps, true);
	}
	
	bool isPerpendicularTo (const Line& l) const
	{
		if (isVertical())
			return l.isHorizontal();
		else if (isHorizontal())
			return l.isVertical();
		else return epsEquals(-invSlope, l.slope, floatEps, true);
	}
	
	vecf intersectionPointWith (const Line& l) const
	{
		//RETURN WHAT FOR COLLINEARITY
		if (isVertical()) {
			if (l.isVertical()) {
				if (epsEquals(xIcpt, l.xIcpt))
					return vecf(INFINITY, INFINITY);
				return vecf{NAN, NAN};
			}
			return l.getPtWhenX(xIcpt);
		}
		else if (l.isVertical())
			return getPtWhenX(l.xIcpt);
		
		float denom = slope - l.slope;
		if (epsEquals(denom, 0)) {
			/* Lines are parallel. */
			if (epsEquals(xIcpt, l.xIcpt))
				return vecf(INFINITY, INFINITY);
			return vecf{NAN, NAN};   // throw error
		}
		float x = (l.yIcpt - yIcpt) / denom;
		float y = (slope * l.yIcpt - l.slope * yIcpt) / denom;
		return vecf {x, y};
	}
	
	Line perpendicularLineThrough (const vecf& pt) const
	{
		if (isVertical())
			return Line(0.f, pt);
		else if (isHorizontal())
			return Line(INFINITY, pt);
		else return Line(-invSlope, pt);
	}
	
	Line parallelLineThrough (const vecf& pt) const
	{
		return Line(slope, pt);
	}
	
	Line parallelLineOffsetBy (float offs) const
	{
		return Line(slope, pt1 + pVec(offs, normal));
	}
	
	vecf pointPerpendicularTo (const vecf& pt) const
	{
		auto line_ { perpendicularLineThrough(pt) };
		return intersectionPointWith(line_);
	}
	
	float perpDistanceTo (const vecf& pt) const
	{
		return hyp(pt, pointPerpendicularTo(pt));
	}
	
		/* confirm that self.containsPoint(pt) before using */
	vecf pointPlusDistance (const vecf& pt, float dist) const
	{
		if (!containsPoint(pt))
			return {NAN, NAN};
		return pt + toRect(abs(dist), dist < 0 ? oppAngle : angle);
	}
	
	LineSegment getSegmentFromXs (float minx, float maxx) const;
	
	LineSegment getSegmentFromYs (float miny, float maxy) const;
	

private:
	void setValuesFromTwoPoints (vecf p1, vecf p2)
	{
		float xDif = p2.x - p1.x;
		float yDif = p2.y - p1.y;
		angle = atand(yDif, xDif);
		normal = czdg(angle + 90);
		oppAngle = czdg(angle + 180);
		oppNormal = czdg(angle + 270);
		if (epsEquals(xDif, 0)) {
			 slope = pt1.y < pt2.y ? INFINITY : -INFINITY;
			invSlope = 0;
			yIcpt = NAN;
			xIcpt = p1.x;
		}
		else if (epsEquals(yDif, 0)) {
			slope = 0;
			invSlope = pt1.x < pt2.x ? INFINITY : -INFINITY;
			yIcpt = p1.y;
			xIcpt = NAN;
		}
		else {
			slope = yDif / xDif;
			invSlope = xDif / yDif;
			yIcpt = p1.y - slope * p1.x;
			xIcpt = p1.x - invSlope * p1.y;
		}
	}

public:
	vecf 		pt1,
				pt2
	;
	float		slope,
				invSlope,
				yIcpt,
				xIcpt,
				angle
				, oppAngle
				, normal
				, oppNormal
	;
	float 		errorMargin = floatEps;

};






struct LineSegment : public Line
{
	LineSegment (vecF& s, vecF& e)
		: Line(s, e)
		, line(s, e)
	{
		ctorBody(s, e);
	}
	
	LineSegment (const vecf& s, const vecf& e)
		: Line(s, e)
		, line(s, e)
	{
		ctorBody(s, e);
	}
	
	LineSegment () : LineSegment({0,0}, {1,0}) { }
	
	void ctorBody (const vecf& s, const vecf& e)
	{
		mid = s + (e - s) / 2.f;
		length = hyp(s, e);

		minx = min(s.x, e.x);
		maxx = max(s.x, e.x);
		miny = min(s.y, e.y);
		maxy = max(s.y, e.y);
		bounds = FloatRect(minx, miny,
						   max(maxx - minx, 1.f),	// 1.f for vertical/horizontal segs
						   max(maxy - miny, 1.f));
	}
	
	bool containsPoint (vecf pt) const override
	{
		if (!isOrBetween(pt.x, minx, maxx)
			|| !isOrBetween(pt.y, miny, maxy))
			return false;
		if (isVertical())
			return epsEquals(pt.x, xIcpt);
		return epsEquals(pt.y, slope * pt.x + yIcpt);
	}
	
	bool intersectsWith (const Line& other, vecf* isctPt = nullptr) const
	{
		auto pt = line.intersectionPointWith(other);
		if (isctPt)
			*isctPt = pt;
		return epsLTE(minx, pt.x) && epsGTE(maxx, pt.x)
			&& epsLTE(miny, pt.y) && epsGTE(maxy, pt.y);
//		return containsPoint(pt);
		// HAD TO DIAL FLOATEPS ALL THE WAY UP TO .006 IN ORDER FOR CONTAINSPOINT TO
		// WORK
	}
	
	bool intersectsWith (const LineSegment& other, vecf* isctPt = nullptr) const
	{
		auto pt = line.intersectionPointWith(other.line);
		if (isctPt)
			*isctPt = pt;
		return epsLTE(minx, pt.x) && epsGTE(maxx, pt.x)
			&& epsLTE(miny, pt.y) && epsGTE(maxy, pt.y)
			&& epsLTE(other.minx, pt.x) && epsGTE(other.maxx, pt.x)
			&& epsLTE(other.miny, pt.y) && epsGTE(other.maxy, pt.y);
//		return containsPoint(pt) && other.containsPoint(pt);
	}
	
	bool intersectsWith (const FloatRect& rect) const
	{
		//add param for returning isctPts
		vecf tl {rect.left, rect.top};
		vecf tr {rect.left + rect.width - 1, rect.top};
		vecf br {rect.left + rect.width - 1, rect.top + rect.height - 1};
		vecf bl {rect.left, rect.top + rect.height - 1};
		return intersectsWith(LineSegment(tl, tr))
			|| intersectsWith(LineSegment(tr, br))
			|| intersectsWith(LineSegment(br, bl))
			|| intersectsWith(LineSegment(bl, tl));
	}
	
	//CREATE AND OVERRIDE FROM LINE VERSION
	bool intersectsWith (const Arc& arc, vector<vecf>* isctPts = nullptr) const
	{
		auto pts = intersectionPointsWith(arc);
		if (isctPts)
			*isctPts = pts;
		return pts.size();
	}
	
	//CREATE AND OVERRIDE FROM LINE VERSION
	//REDO after study and own implementation
	vector<vecf> intersectionPointsWith (const Arc& arc) const ;
	
	bool isPerpendicularToPt (const vecf& pt) const
	{
		auto perpPt = pointPerpendicularTo(pt);
		return minx <= perpPt.x && maxx >= perpPt.x
			&& miny <= perpPt.y && maxy >= perpPt.y;
//		return containsPoint(pointPerpendicularTo(pt));
	}
	
	bool isCollinearWith (const Line& l) const
	{
		if (isVertical())
			return l.isVertical() && epsEquals(xIcpt, l.xIcpt);
		else if (isHorizontal())
			return l.isHorizontal() && epsEquals(yIcpt, l.yIcpt);
		else return epsEquals(slope, l.slope) && epsEquals(line.yIcpt, l.yIcpt);
	}
	
	bool isCollinearWith (const LineSegment& other) const
	{
		return isCollinearWith(other.line);
	}
	
	LineSegment alterLength (float len)
	{
		auto newPt = pt2 + pVec(len, angle);
		return LineSegment(pt1, newPt);
	}
	
	/* extend or retract pt1 while keeping pt2 */
	LineSegment alterLengthPt1 (float len)
	{
		auto newPt = pt1 + pVec(len, oppAngle);
		return LineSegment(newPt, pt2);
	}
	
	Line			line;
	FloatRect 		bounds;
	vecF 			mid;
	float 			length
	;
	float 			minx
					, maxx
					, miny
					, maxy
	;
};

/* DON'T CALL FOR VERTICAL LINES */
inline LineSegment Line::getSegmentFromXs (float minx, float maxx) const
{
	return LineSegment(getPtWhenX(minx), getPtWhenX(maxx));
}

/* DON'T CALL FOR HORIZONTAL LINES */
inline LineSegment Line::getSegmentFromYs (float miny, float maxy) const
{
	return LineSegment(getPtWhenY(miny), getPtWhenY(maxy));
}

struct Arc
{
	Arc () : center(vecf(0, 0)), radius(10), startAng(0), endAng(INFINITY) {}
	Arc (const vecf& ctr, float rad, float start = 0, float end = INFINITY)
	: center(ctr), radius(rad), startAng(start), endAng(end) { }
	
	vecf center;
	float 	radius
			, startAng
			, endAng
	;
};

inline vector<vecf> LineSegment::intersectionPointsWith (const Arc& arc) const
{
	   std::vector<vecf> results;

	   // Vector from seg_a to seg_b
	   float dx = pt2.x - pt1.x;
	   float dy = pt2.y - pt1.y;

	   // Quadratic coefficients: (x - xc)^2 + (y - yc)^2 = r^2
	   float A = dx * dx + dy * dy;
	   float B = 2 * (dx * (pt1.x - arc.center.x) + dy * (pt1.y - arc.center.y));
	   float C = (pt1.x - arc.center.x) * (pt1.x - arc.center.x) +
				  (pt1.y - arc.center.y) * (pt1.y - arc.center.y) - arc.radius * arc.radius;

	   float discriminant = B * B - 4 * A * C;
	   if (discriminant < 0)
		   return results; // No intersection

	   // Up to two intersection t values
	   for (int sign = -1; sign <= 1; sign += 2) {
		   if (discriminant == 0 && sign == 1)
			   break; // Don't repeat if only one root
		   float t = (-B + sign * std::sqrt(discriminant)) / (2 * A);
		   if (t < 0 || t > 1) continue; // Not on the segment

		   // Intersection point
		   vecf p = { pt1.x + t * dx, pt1.y + t * dy };
		   bool in_arc = false;
		   if (std::isinf(arc.endAng))
			   in_arc = true;
		   else {
			   float theta = czdg(atand(p.y - arc.center.y, p.x - arc.center.x));

			   // Normalize arc range for checking
			   float norm_start = czdg(arc.startAng);
			   float norm_end = czdg(arc.endAng);

			   if (norm_start < norm_end)
				   in_arc = (theta >= norm_start && theta <= norm_end);
			   else // Arc crosses 2π
				   in_arc = (theta >= norm_start || theta <= norm_end);
		   }
		   if (in_arc)
			   results.push_back(p);
	   }
	   return results;
   }
   


inline pair<Vector2f, float> circleFrom3Pts (vecf pt1, vecf pt2, vecf pt3)
{
	LineSegment seg1 {pt1, pt2};
	LineSegment seg2 {pt1, pt3};
	Line midline1 = seg1.perpendicularLineThrough(seg1.mid);
	Line midline2 = seg2.perpendicularLineThrough(seg2.mid);
	vecf center = midline1.intersectionPointWith(midline2);
	return make_pair(center, hyp(center, pt1));
}








inline bool rotatedContains (RectangleShape& r, float x, float y)
{
   vecf pt {x, y};
   float oldRot = r.getRotation();
	   /*
		* If the sprite is rectilinear, just return the
		* result of the normal contains() algorithm
		*/
   if (		epsEquals(oldRot, 0) ||
			epsEquals(oldRot, 90) ||
			epsEquals(oldRot, 270) ||
			epsEquals(oldRot, 180))
	   return r.getGlobalBounds().contains(x, y);
   
	   /*
		* Temporarily rectify the sprite so we can figure out
		* where the corners of the bounding rectangle would be
		* in relation to the origin
		*/
   r.setRotation(0);
   FloatRect rect = r.getGlobalBounds();
	   /* Return the sprite to its proper rotation */
   r.setRotation(oldRot);
   
   vecf topL { rect.left, rect.top },
		   topR { rect.left + rect.width, rect.top },
		   botR { rect.left + rect.width, rect.top + rect.height },
		   botL { rect.left, rect.top + rect.height };
   auto ogn = r.getPosition();
	   /*
		* Store the polar vectors from the origin to each (rectified)
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
	   /*
		* Compute where the rotated corners of the original bounding
		* box are now located
		*/
   vecf rotTl = ogn + toRect(tlDif.x, czdg(tlDif.y + oldRot)),
		   rotTr = ogn + toRect(trDif.x, czdg(trDif.y + oldRot)),
		   rotBr = ogn + toRect(brDif.x, czdg(brDif.y + oldRot)),
		   rotBl = ogn + toRect(blDif.x, czdg(blDif.y + oldRot));
	   /*
		* Make lines connecting the rotated bounding corners, and
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
}
  



class VxShape : public Drawable
{
public:
	VxShape ()
	{
		setup(Color::Black);
	}
	
	VxShape (const vecF& pos)
	{
		setup(Color::Black);
		sP(pos);
	}
	
	VxShape (const vecf& pos, Color c)
	{
		setup(c);
		sP(pos);
	}

	void setup (Color c)
	{
		vx.setRadius(4);
		cO(vx);
		vx.setFillColor(c);
		
		hl.setRadius(10);
		cO(hl);
		hl.sP(vx.gP());
		hl.setFillColor(Color(0, 0, 0, 40));
	}
	
	void draw (RenderTarget& target, RenderStates st) const override
	{
		if (isHighlighted)
			target.draw(hl);
		target.draw(vx);
	}
	
	void move (float x, float y)
	{
		vx.move(x, y);
		hl.move(x, y);
	}

	void move (vecf dif)
	{
		vx.move(dif);
		hl.move(dif);
	}
	
	void setPosition (float x, float y)
	{
		vx.setPosition(x, y);
		hl.setPosition(x, y);
	}

	void setPosition (vecf pos)
	{
		vx.setPosition(pos);
		hl.setPosition(pos);
	}
	
	vecf getPosition () { return vx.getPosition(); }

	CircleShape     	vx
						, hl	// highlight
	;
	bool				isHighlighted = false
	;
	VxShape*           	prev {nullptr};
	VxShape*			next {nullptr};
	;
};


//class SplineVxShape (change zgolf)

//		(setup) controls.clear();
// Point1 to Control1, Control1 to Control2, Control2 to Point2
//	VertexArray     P1C1 {Lines}, C1C2 {Lines}, C2P2 {Lines};
//	vector<VxShape>    controls {};
//		isControl = false,




	/* This class has to be located in a permanent position; then
	 * call congifure(). Moving this object or an enclosing object
	 * will invalidate the pointers to vertices
	 */
class TransformableVxArray : public VertexArray
{
public:

	TransformableVxArray (PrimitiveType p)
	{
		setPrimitiveType(p);
	}
	
	void storeOrigin ()
	{
		FloatRect bounds = getBounds();
		vecf center { bounds.left + bounds.width / 2,
			bounds.top + bounds.height / 2};
		origin = center;
	}

	virtual void configure ()
	{
		storeOrigin();
		originalDifs.clear();
		scale_ = vecf(1, 1);
		rotation_ = 0;
		forNum (getVertexCount()) {
			auto& vx = (*this)[i];
			originalDifs.insert({&vx, getPolarFromOrigin(vx)});
		}
	}

	void rotate (float deg)
	{
		rotation_ += deg;
		executeTransform_();
	}
	
	void setRotation (float deg)
	{
		rotation_ = deg;
		executeTransform_();
	}
	
	void setScale (float fx, float fy)
	{
		scale_ = vecf(fx, fy);
		executeTransform_();
	}
	
	void setPosition (vecf pos)
	{
		origin = pos;
		executeTransform_();
	}
	
	void move (vecf dif)
	{
		origin += dif;
		executeTransform_();
	}
	
	void move (float x, float y)
	{
		origin.x += x;
		origin.y += y;
		executeTransform_();
	}
	
	
	bool rotatedContains (float x, float y)
	{
		vecf pt {x, y};
		float oldRot = rotation_;
			/*
			 * If the sprite is rectilinear, just return the
			 * result of the normal contains() algorithm
			 */
		if (	oldRot == 0 ||
				oldRot == 90 ||
				oldRot == 270 ||
				oldRot == 180)
			return getBounds().contains(x, y);
		
			/*
			 * Temporarily rectify the VA so we can figure out
			 * where the corners of the bounding rectangle would be
			 * in relation to the origin
			 */
		setRotation(0);
		FloatRect rect = getBounds();
			/* Return the VA to its proper rotation */
		setRotation(oldRot);
		
		vecf 	topL { rect.left, rect.top },
				topR { rect.left + rect.width, rect.top },
				botR { rect.left + rect.width, rect.top + rect.height },
				botL { rect.left, rect.top + rect.height };
		auto ogn = origin;
			/*
			 * Store the polar vectors from the origin to each (rectified)
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
			/*
			 * Compute where the rotated corners of the original bounding
			 * box are now located
			 */
		vecf 	rotTl = ogn + toRect(tlDif.x, czdg(tlDif.y + oldRot)),
				rotTr = ogn + toRect(trDif.x, czdg(trDif.y + oldRot)),
				rotBr = ogn + toRect(brDif.x, czdg(brDif.y + oldRot)),
				rotBl = ogn + toRect(blDif.x, czdg(blDif.y + oldRot));
			/*
			 * Make lines connecting the rotated bounding corners, and
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
	}

	void executeTransform_ ()
	{
		forNum (getVertexCount()) {
			auto& pt = (*this)[i];
			auto dif = originalDifs[&pt];
			dif.y = czdg(dif.y + rotation_);
			dif = toRect(dif);
			dif.x *= scale_.x;
			dif.y *= scale_.y;
			pt.position = origin + dif;
		}
	}

	vecf getPolarFromOrigin (Vertex& v)
	{
		auto dif = v.position - origin;
		return toPolar(dif);
	}

	vecf 				origin;
	vecf				scale_;
	float				rotation_;
	map<Vertex*, vecf>	originalDifs;
	
};






class VxShapeArray : public TransformableVxArray
{
public:
	
	void draw(RenderTarget& target, RenderStates st) const
	{
		if (drawVa)
			target.draw(*this);
		if (drawDots)
			for (auto& d : dots)
				target.draw(d);
	}
	
	void append (vecf pos, Color vxColor=Color::Black, Color shapeColor=Color::Black)
	{
		Vertex vx {pos, vxColor};
		VertexArray::append(vx);
		VxShape sh {pos, shapeColor};
		dots.push_back(sh);
	}
	
	void moveVx (VxShape& sh, vecf dif)
	{
		forNum(getVertexCount()) {
			if (&dots[i] == &sh) {
				sh.sP(sh.gP().x + dif.x, sh.gP().y + dif.y);
				(*this)[i].position = sh.gP();
			}
		}
	}
	
	void moveVx (int i, vecf dif)
	{
		dots[i].sP(dots[i].gP().x + dif.x, dots[i].gP().y + dif.y);
		(*this)[i].position = dots[i].gP();

	}
	
	void setVxPos (VxShape& sh, vecf pos)
	{
		forNum(getVertexCount()) {
			if (&dots[i] == &sh) {
				sh.sP(pos);
				(*this)[i].position = pos;
			}
		}
	}

	void setVxPos (int i, vecf pos)
	{
		dots[i].sP(pos);
		(*this)[i].position = pos;
	}

	void deleteVx (VxShape& sh)
	{
		forNum(getVertexCount()) {
			if (&dots[i] == &sh) {
				eraseIndex(dots, i);
				eraseVertexAt(i);
			}
		}
	}
	
	void deleteVx (int i)
	{
		eraseIndex(dots, i);
		eraseVertexAt(i);
	}
	
	void insertVxBefore (VxShape& sh, vecf pos, Color vxColor=Color::Black, Color shapeColor=Color::Black)
	{
		forNum(getVertexCount()) {
			if (&dots[i] == &sh) {
				VxShape sh {pos, shapeColor};
				dots.insert(dots.begin() + i, sh);
				insertVertexAt(i, pos, vxColor);
			}
		}
	}
	
	void insertVxAt (size_t idx, vecf pos, Color vxColor=Color::Black, Color shapeColor=Color::Black)
	{
		VxShape sh {pos, shapeColor};
		dots.insert(dots.begin() + idx, sh);
		insertVertexAt(idx, pos, vxColor);
	}
	
	void insertVertexAt (size_t idx, vecf pos, Color vxColor=Color::Black)
	{
		VertexArray::append(Vertex());
		for (size_t i = getVertexCount() - 1; i >= idx; --i) {
			if (i == idx) {
				(*this)[i].position = pos;
				(*this)[i].color = vxColor;
			}
			else if (i > 0) {
				(*this)[i] = (*this)[i - 1];
			}
		}
	}
	
	void eraseVertexAt (size_t idx)
	{
		for (size_t i = idx; i < getVertexCount(); ++i) {
			if (i + 1 < getVertexCount()) {
				(*this)[i] = (*this)[i + 1];
			}
			resize(getVertexCount() - 1);
		}
	}
	
	vector<VxShape>				dots;
	vector<VxShape*>			selectedDots;
	bool						drawVa = true
								, drawDots = true
	;

};




// FINISH
class HexagonShape: public Shape {
public:
	HexagonShape () {}
	
	HexagonShape (vecF sz)
		: m_size(sz)
	{
		update();
	}
	
	void setSize (const vecF sz)
	{
		m_size = sz;
		update();
	}
	
	virtual size_t getPointCount () const
	{
		return 6;
	}
	
	virtual vecF getPoint (size_t i) const
	{
		float side = m_size.x / 2;
		float hfside = side / 2;
		float sinComp = sind(60) * side;
		switch(i) {
			case 0: return vecF(-side, 0);
			case 1: return vecF(-hfside, -sinComp);
			case 2: return vecF(hfside, -sinComp);
			case 3: return vecF(side, 0);
			case 4: return vecF(hfside, sinComp);
			case 5: return vecF(-hfside, sinComp);
			default: return vecF(0, 0);
		}
	}
	
private:
	vecF m_size;
};


class OctagonShape: public Shape {
public:
	OctagonShape () {}
	
	OctagonShape (vecF sz)
		: m_size(sz)
	{
		update();
	}
	
	void setSize (const vecF sz)
	{
		m_size = sz;
		update();
	}
	
	virtual size_t getPointCount () const
	{
		return 8;
	}
	
	virtual vecF getPoint (size_t i) const
	{
		float side = m_size.x / (2 * sind(45) + 1);
		float hfside = side / 2;
		float hfsize = m_size.x / 2;
		switch(i) {
			case 0: return vecF(-hfsize, hfside);
			case 1: return vecF(-hfsize, -hfside);
			case 2: return vecF(-hfside, -hfsize);
			case 3: return vecF(hfside, -hfsize);
			case 4: return vecF(hfsize, -hfside);
			case 5: return vecF(hfsize, hfside);
			case 6: return vecF(hfside, hfsize);
			case 7: return vecF(-hfside, hfsize);
			default: return vecF(0, 0);
		}
	}
	
private:
	vecF m_size;
};

class StarShape: public Shape {
public:
	StarShape () {}
	
	StarShape (vecF sz)
		: m_size(sz)
	{
		update();
	}
	
	void setSize (const vecF sz)
	{
		m_size = sz;
		update();
	}
	
	virtual size_t getPointCount () const
	{
		return 10;
	}
	
	virtual vecF getPoint (size_t i) const
	{
		float outerRad = m_size.x / 2;
		float innerRad = m_size.y / 2;
		switch(i) {
			case 0: return toRect(outerRad, 270);
			case 1: return toRect(innerRad, 306);
			case 2: return toRect(outerRad, 342);
			case 3: return toRect(innerRad, 18);
			case 4: return toRect(outerRad, 54);
			case 5: return toRect(innerRad, 90);
			case 6: return toRect(outerRad, 126);
			case 7: return toRect(innerRad, 162);
			case 8: return toRect(outerRad, 198);
			case 9: return toRect(innerRad, 234);
			default: return vecF(0, 0);
		}
	}
	
private:
	vecF m_size;
};


class TriangleShape: public Shape {
public:
	TriangleShape () {}
	
	TriangleShape (vecF sz)
		: m_size(sz)
	{
		update();
	}
	
	void setSize (const vecF sz)
	{
		m_size = sz;
		update();
	}
	
	virtual size_t getPointCount () const
	{
		return 3;
	}
	
	virtual vecF getPoint (size_t i) const
	{
		switch(i) {
			case 0: return vecF(0, 0);
			case 1: return vecF(m_size.x, 0);
			default: return vecF(m_size.x/2, -m_size.y);
		}
	}
	
private:
	vecF m_size;
};



inline Color colorWithRandDeviation (Color& c, int dev);
inline Color colorDevLockHue (Color& c, int dev);
inline vector<int> rgbToHsb (const Color& c);
inline Color decreaseSaturation (const Color& c, int);

class ZImage : public Image
{
public:
	
	ZImage () {}
	
	ZImage (const Image& img)
	{
		create(img.getSize().x, img.getSize().y, img.getPixelsPtr());
	}
	
	Color getPixel (vecU coords)
	{
		return Image::getPixel(coords.x, coords.y);
	}
	
	Color getPixel (uint x, uint y)
	{
		return Image::getPixel(x, y);
	}
	
	bool isBlank(Color c) { return c.a == 0; }
	
	void fadeByAlphaVal (int val)
	{
		auto szx = getSize().x;
		auto szy = getSize().y;
		forNum(szy) {
			forNumJ(szx) {
				auto curPix = getPixel(j, i);
				if (curPix.a == 0)
					continue;
				else curPix.a = max(0, curPix.a - val);
				setPixel(j, i, curPix);
			}
		}
	}
	
	void colorByAlphaVal (Color c, int alphaVal)
	{
		//ONLY DO NON-TRANSPARENT PIX?
		auto szx = getSize().x;
		auto szy = getSize().y;

		Texture tx;
		tx.loadFromImage(*this);
		Sprite s(tx);
		RenderTexture rt;
		rt.create(szx, szy);
		rt.draw(s);
		RectangleShape r;
		r.setSize({(float)szx, (float)szy});
		r.setFillColor(Color(c.r, c.g, c.b, clamp(alphaVal, 0, 255)));
		rt.draw(r);
		rt.display();
		Image img {rt.getTexture().copyToImage()};
		forNum(szy) {
			forNumJ(szx) {
				if (!isBlank(getPixel(j, i)))
					setPixel(j,  i, img.getPixel(j, i));
			}
		}
	}

	void fillInWithColor (vecU startPt, Color c, int dev = 0)
	{
		if (!_isValidStartForFillIn(startPt))
			return;
		_fillInImpl(startPt,
			[&](uint a, uint b) {
			setPixel(a, b, colorDevLockHue(c, dev));
		});
	}
	

	void fillInFromImage (vecU startPt, string fname)
	{
		if (!_isValidStartForFillIn(startPt))
			return;
		Image img;
		img.loadFromFile(fname);
		auto szx = img.getSize().x;
		auto szy = img.getSize().y;
		
		_fillInImpl(startPt,
			[&](uint a, uint b) {
				setPixel(a, b, img.getPixel(a % szx, b % szy));
		});
	}

	bool _isValidStartForFillIn (vecU startPt)
	{
		int numRows = getSize().y;
		int numCols = getSize().x;
		return isOrBetween(startPt.x, 0, numCols - 1)
				&& isOrBetween(startPt.y, 0, numRows - 1);
	}
	
	void _fillInImpl (vecU startPt, function<void(uint a, uint b)> func)
	{
		int numRows = getSize().y;
		int numCols = getSize().x;
		Color colorToReplace = getPixel(startPt);
	
		int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		queue<pair<int, int>> unresolvedPts;
		unresolvedPts.push({startPt.x, startPt.y});
		func(startPt.x, startPt.y);

		while (!unresolvedPts.empty()) {
			auto [cx, cy] = unresolvedPts.front();
			unresolvedPts.pop();
			
			for (auto [dx, dy] : dirs) {
				int nx = cx + dx;
				int ny = cy + dy;
				if (nx >= 0 && nx < numCols && ny >= 0 && ny < numRows && getPixel(nx, ny) == colorToReplace) {
					func(nx, ny);
					unresolvedPts.push({nx, ny});
				}
			}
		}
	}
	
	void blur (int iterations = 1, bool useDiag = true, bool blendToTransparent = false)
	{
		int wid = getSize().x;
		int ht = getSize().y;
		forNum(iterations) {
			Image tempCopy {*this};
			for (int i = 0; i <  wid ; ++i) {
				for (int j = 0; j <  ht ; ++j) {
					int num = 0;
					int red = 0, green = 0, blue = 0, alpha = 0;
					vector<vecF> v;
					if (useDiag) v = {
						{-1, -1}, {0, -1}, {1, -1},
						{-1, 0}, {0, 0}, {1, 0},
						{-1, 1}, {0, 1}, {1, 1}
						
//						{-2, -2}, {-1, -2}, {0, -2}, {1, -2}, {2, -2},
//						{-2, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1},
//						{-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0},
//						{-2, 1}, {-1, 1}, {0, 1}, {1, 1}, {2, 1},
//						{-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}
					};
					else v = {
								 {0, -1},
						{-1, 0}, {0, 0}, {1, 0},
								 {0, 1},
					};
					for (auto& coord : v) {
						if (	i + coord.x >= 0 && i + coord.x <= wid &&
							j + coord.y >= 0  && j + coord.y  <= ht) {
							Color p = getPixel(i + coord.x, j + coord.y);
							if (!blendToTransparent && isBlank(p))
								continue;
							++num;
							red += p.r;
							green += p.g;
							blue += p.b;
							alpha += p.a;
						}
					}
					Color c = Color(int(floor(red / num)),
									int(floor(green / num)),
									int(floor(blue / num)),
									int(floor(alpha / num)));
					tempCopy.setPixel(i, j, c);
				}
			}
			create(wid, ht, tempCopy.getPixelsPtr());
		}
	}
	
	void fixedDarken(uint val = 1)
	{
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				p.r -= (p.r - val >= 0 ? val : p.r);
				p.g -= (p.g - val >= 0 ? val : p.g);
				p.b -= (p.b - val >= 0 ? val : p.b);
				setPixel(i, j, p);
			}
		}
	}

	void fixedLighten(uint val = 1)
	{
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				p.r += (p.r + val <= 255 ? val : 255 - p.r);
				p.g += (p.g + val <= 255 ? val : 255 - p.g);
				p.b += (p.b + val <= 255 ? val : 255 - p.b);
				setPixel(i, j, p);
			}
		}
	}
		
	void prportLighten (uint val) {
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				if (p.r > p.g && p.r > p.b) {
					float greenRatio = (float)p.g / (float)p.r;
					float blueRatio = (float)p.b / (float)p.r;
					p.r = min(p.r + val, 255u);
					p.g = round((float)p.r * greenRatio);
					p.b = round((float)p.r * blueRatio);
				}
				else if (p.g > p.b && p.g > p.r) {
					float redRatio = (float)p.r / (float)p.g;
					float blueRatio = (float)p.b / (float)p.g;
					p.g = min(p.g + val, 255u);
					p.r = round((float)p.g * redRatio);
					p.b = round((float)p.g * blueRatio);
				}
				else {
					float redRatio = (float)p.r / (float)p.b;
					float greenRatio = (float)p.g / (float)p.b;
					p.b = min(p.b + val, 255u);
					p.r = round((float)p.b * redRatio);
					p.g = round((float)p.b * greenRatio);
				}
				setPixel(i, j, p);
			}
		}
	}
		
	void prportDarken (uint val) {
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				if (p.r > p.g && p.r > p.b) {
					float greenRatio = (float)p.g / (float)p.r;
					float blueRatio = (float)p.b / (float)p.r;
					p.r = max(p.r - val, 0u);
					p.g = max(0u, (uint)round((float)p.r * greenRatio));
					p.b = max(0u, (uint)round((float)p.r * blueRatio));
				}
				else if (p.g > p.b && p.g > p.r) {
					float redRatio = (float)p.r / (float)p.g;
					float blueRatio = (float)p.b / (float)p.g;
					p.g = max(p.g - val, 0u);
					p.r = max(0u, (uint)round((float)p.g * redRatio));
					p.b = max(0u, (uint)round((float)p.g * blueRatio));
				}
				else {
					float redRatio = (float)p.r / (float)p.b;
					float greenRatio = (float)p.g / (float)p.b;
					p.b = max(p.b - val, 0u);
					p.r = max(0u, (uint)round((float)p.b * redRatio));
					p.g = max(0u, (uint)round((float)p.b * greenRatio));
				}
				setPixel(i, j, p);
			}
		}
	}
	

	void unsaturate (int val = 1)
	{
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				if (!isBlank(p)) {
					auto newPix = decreaseSaturation(p, val);
					setPixel(i, j, newPix);
				}
			}
		}
	}
 
	//saturate

	void convertToRetroColor ()
	{
		int wid = getSize().x;
		int ht = getSize().y;
		for (int i = 0; i <  wid ; ++i) {
			for (int j = 0; j <  ht ; ++j) {
				Color p = getPixel(i, j);
				int stepVal = 51;
				// could generate a map rather than iterate every time
				for (int low = 0; low < 256; low += stepVal) {
					int hi = min(low + stepVal, 255);
					if (p.r >= low && p.r < hi) {
						p.r = p.r - low < hi - p.r ? low : hi;
					}
					if (p.g >= low && p.g < hi) {
						p.g = p.g - low < hi - p.g ? low : hi;
					}
					if (p.b >= low && p.b < hi) {
						p.b = p.b - low < hi - p.b ? low : hi;
					}
				}
				setPixel(i, j, p);
			}
		}
	}

};




class DbgPoint : public Drawable
{
public:
	DbgPoint(const vecf& pt, string s = "", Font* font = nullptr)
	{
		c1.setRadius(5);
		c2.setRadius(10);
		centerOrigin(c1);
		centerOrigin(c2);
		c1.setOutlineThickness(1);
		c2.setOutlineThickness(1);
		c1.setOutlineColor(Color::White);
		c2.setOutlineColor(Color::Black);
		c1.setFillColor(Color::Transparent);
		c2.setFillColor(Color::Transparent);
		c1.setPosition(pt);
		c2.setPosition(pt);
		va.append(Vertex(pt + pVec(3, 270), Color::White));
		va.append(Vertex(pt + pVec(3, 90), Color::White));
		va.append(Vertex(pt + pVec(3, 180), Color::White));
		va.append(Vertex(pt + pVec(3, 0), Color::White));
		if (font) {
			drawTxt = true;
			labelStr = s;
			label = Text(labelStr, *font, 13);
			label.setFillColor(Color::Black);
			label.setPosition(pt + pVec(20, 0));
		}
	}
	
	void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(va, states);
		target.draw(c1, states);
		target.draw(c2, states);
		if (drawTxt)
			target.draw(label, states);
	}
	
	VertexArray va {Lines};
	CircleShape c1;
	CircleShape c2;
	Text 		label;
	string		labelStr;
	bool 		drawTxt = false;
};


#if 0
struct Vert
{
	Vert() { setup(); }
	
	Vert(const vecF& pos)
	{
		s.sP(pos);
		setup();
	}
	
	void setup()
	{
		s.setRadius(4);
		s.setFillColor(Color::Black);
		cO(s);
		hl.setRadius(10);
		hl.setFillColor(Color(0, 0, 0, 40));
		cO(hl);
		hl.sP(s.gP());
		controls.clear();
	}
	
	void setPosition(vecf pos, bool moveControls = false)
	{
		auto dif = pos - s.gP();
		s.sP(pos);
		hl.sP(pos);
		if (moveControls)
			for (auto& ctl : controls)
				ctl.s.move(dif);
	}

	CircleShape     s
					, hl	// highlight
	;
		// Point1 to Control1, Control1 to Control2, Control2 to Point2
	VertexArray     P1C1 {Lines}
					, C1C2 {Lines}
					, C2P2 {Lines}
	;
	bool            isControl = false,
					isHighlighted = false;
	vector<Vert>    controls {};
	Vert*           parent = nullptr;
};



vector<vecf> getSplinePts (vector<Vert>& verts, bool connectEnds = true, int divisions = 100)
{
	vector<vecf> pts;
	float divMultiplier = 1.f / (float)divisions;
	auto sz = verts.size();
		// no spline to draw if only one or zero points created
	if (sz < 2)
		return pts;
	
	for (int i = 1; i <= sz; ++i) {
		Vert& v = verts[i - 1];
		auto pos1 = v.s.gP();
			// [i % sz] instead of [i] so that final vert will connect to first vert
		auto pos2 = verts[i % sz].s.gP();
		if (i == 1)
			pts.push_back(pos1);

		if (v.controls.size() == 0) {
			if (i != sz || connectEnds)
				pts.push_back(pos2);
		}
		else if (v.controls.size() == 1) {   // one control point: quadratic curve
			vecf c1 = v.controls[0].s.gP();
			vecf p1c1 = c1 - pos1;
			vecf c2p2 = pos2 - c1;
			vecf inc1 = p1c1 * divMultiplier;
			vecf inc3 = c2p2 * divMultiplier;
			for (float j = 1; j <= divisions; ++j) {
				if (j == divisions) {
					pts.push_back(pos2);
					break;
				}
				vecf pt1 = pos1 + inc1 * j;
				vecf pt3 = c1 + inc3 * j;
				vecf dif1 = pt3 - pt1;
				vecf incd1 = dif1 * divMultiplier;
				vecf pt6 = pt1 + vecf(incd1.x * j, incd1.y * j);
				
				pts.push_back(pt6);
			}
		}
		else if (v.controls.size() == 2) { // two control points: cubic curve
			vecf c1 = v.controls[0].s.gP();
			vecf c2 = v.controls[1].s.gP();
			vecf p1c1 = c1 - pos1;
			vecf c1c2 = c2 - c1;
			vecf c2p2 = pos2 - c2;
			vecf inc1 = p1c1 * divMultiplier;
			vecf inc2 = c1c2 * divMultiplier;
			vecf inc3 = c2p2 * divMultiplier;
			for (float j = 1; j <= divisions; ++j) {
				if (j == divisions) {
					pts.push_back(pos2);
					break;
				}
				vecf pt1 = pos1 + inc1 * j;
				vecf pt2 = c1 + inc2 * j;
				vecf pt3 = c2 + inc3 * j;
				vecf dif1 = pt2 - pt1;
				vecf dif2 = pt3 - pt2;
				vecf incd1 = dif1 * divMultiplier;
				vecf incd2 = dif2 * divMultiplier;
				vecf pt4 = pt1 + incd1 * j;
				vecf pt5 = pt2 + incd2 * j;
				vecf dif3 = pt5 - pt4;
				vecf pt6 = pt4 + vecf(dif3.x * j * divMultiplier, dif3.y * j * divMultiplier);
				pts.push_back(pt6);
			}
		}
	}
	return pts;
}
#endif

























	/* COLORS */


inline Color hsbToRgb (float h, float s, float br)
{
	float r, b, g, hi, lo;
	
	hi = br * 2.55;
	lo = (hi / 100) * (100 - s);
	
	vecF coords = toRect(hi / 100 * s, h);
	auto gm = [&](float ad, float bd) {
		vecF vv = coords - (toRect(hi, ad) + toRect(lo, bd));
		return toPolar(vv).x;
	};
	
	if (h <= 60) {
		r = hi;
		b = lo;
		g = gm(0, 240);
	}
	else if (h <= 120) {
		r = gm(120, 240);
		g = hi;
		b = lo;
	}
	else if (h <= 180) {
		r = lo;
		g = hi;
		b = gm(120, 0);
	}
	else if (h <= 240) {
		r = lo;
		g = gm(240, 0);
		b = hi;
	}
	else if (h <= 300) {
		r = gm(240, 120);
		g = lo;
		b = hi;
	}
	else //if (h <= 360)
	{
		r = hi;
		g = lo;
		b = gm(0, 120);
	}
	
	return Color(round(r), round(g), round(b));
}

inline Color hsbToRgb (intvec iv)
{
	return hsbToRgb(float(iv[0]), float(iv[1]), float(iv[2]));
}


inline vector<int> rgbToHsb (float r, float g, float b) {

	r /= 2.55;
	g /= 2.55;
	b /= 2.55;
 
	flvec vals {r, g, b};
	float hi = *(max_element(vals.begin(), vals.end()));
	float lo = *(min_element(vals.begin(), vals.end()));
	
	float br = hi;
	float s = 100 - lo / (hi / 100);
	
		/* To find the resulting hue, we make vectors representing
		 * the strengths of each primary, and add them. The direction
		 * it points is the degrees of the new hue
		 */
	float h = 0;

	vecF 	rv {r, 0},
			gv {g, 120},
			bv {b, 240},
			comb {toRect(rv) + toRect(gv) + toRect(bv)};
	vecF res = toPolar(comb);
	h = res.y;
	
	intvec v{};
	v.push_back(round(h));
	v.push_back(round(s));
	v.push_back(round(br));
	return v;
}

inline vector<int> rgbToHsb (const Color& c)
{
	return rgbToHsb(float(c.r), float(c.g), float(c.b));
}

inline Color randomColor ()
{
	int r = randRange(1, 255);
	int g = randRange(1, 255);
	int b = randRange(1, 255);
	return Color(r, g, b);
}

inline Color randomRangedHSB (intPair h, intPair s, intPair b)
{
	int hue;
	if (h.first <= h.second)
		hue = randRange(h.first, h.second);
		/* If we want a range that's e.g. 5 degrees either way of red,
		 * we have to pass h as 355, 5 and perform a special
		 * calculation to get the random value
		 */
	else hue = (randRange(0, (360 - h.first + h.second)) + h.first) % 360;
	int sat = randRange(s.first, s.second);
	int bri = randRange(b.first, b.second);
	return hsbToRgb(hue, sat, bri);
}

inline Color colorWithRandDeviation (const Color& c, int dev)
{
	if (dev == 0)
		return c;
	auto hsb = rgbToHsb(c);
	intPair h {(hsb[0] - dev) % 360, (hsb[0] + dev) % 360};
	intPair s {max(0, hsb[1] - dev), min(100, hsb[1] + dev)};
	intPair b {max(0, hsb[2] - dev), min(100, hsb[2] + dev)};
	return randomRangedHSB(h, s, b);
}

inline Color colorDevLockHue (Color&c, int dev)
{
	if (dev == 0)
		return c;
	auto hsb = rgbToHsb(c);
	int hueDev = min(dev, randRange(0,2));
	intPair h {(hsb[0] + 360 - hueDev) % 360, (hsb[0] + hueDev) % 360};
	intPair s {max(0, hsb[1] - dev), min(100, hsb[1] + dev)};
	intPair b {max(0, hsb[2] - dev), min(100, hsb[2] + dev)};
	return randomRangedHSB(h, s, b);
}

inline Color mixColors (const Color& c1, const Color& c2)
{
	return Color( (c1.r + c2.r) / 2,
				  (c1.g + c2.g) / 2,
				  (c1.b + c2.b) / 2,
				  (c1.a + c2.a) / 2 );
}

inline Color addRed (const Color& c, int inc=1)
{
	Color col { c };
	col.r = incm(col.r, inc, 255);
	return col;
}

inline Color addGreen (const Color& c, int inc=1)
{
	Color col { c };
	col.g = incm(col.g, inc, 255);
	return col;
}

inline Color addBlue (const Color& c, int inc=1)
{
	Color col { c };
	col.b = incm(col.b, inc, 255);
	return col;
}

inline Color decreaseRed (const Color& c, int inc=1)
{
	Color col { c };
	col.r = decm(col.r, inc, 0);
	return col;
}

inline Color decreaseGreen (const Color& c, int inc=1)
{
	Color col { c };
	col.g = decm(col.g, inc, 0);
	return col;
}

inline Color decreaseBlue (const Color& c, int inc=1)
{
	Color col { c };
	col.b = decm(col.b, inc, 0);
	return col;
}


inline int getHue (const Color& c)
{
	return rgbToHsb(c)[0];
}

inline int getSaturation (const Color& c)
{
	return rgbToHsb(c)[1];
}

inline int getBrightness (const Color& c)
{
	return rgbToHsb(c)[2];
}

	/* lessening increment doesn't work */
inline Color addHue (const Color& c, int inc=3)
{
	auto col { rgbToHsb(c) };
	col[0] = (col[0] + inc) % 360;
	return hsbToRgb(col);
}

inline Color decreaseHue (const Color& c, int inc=3)
{
	auto col { rgbToHsb(c) };
	col[0] = (col[0] + 360 - inc) % 360;
	return hsbToRgb(col);
}

	/* will tend towards red/0° unless HSB values stored */
inline Color addSaturation (const Color& c, int inc=1)
{
	auto col { rgbToHsb(c) };
	col[1] = incm(col[1], inc, 100);
	return hsbToRgb(col);
}

inline Color decreaseSaturation (const Color& c, int inc=1)
{
	auto col { rgbToHsb(c) };
	col[1] = decm(col[1], inc, 0);
	return hsbToRgb(col);
}

inline Color addBrightness (const Color& c, int inc=1)
{
	auto col { rgbToHsb(c) };
	col[2] = incm(col[2], inc, 100);
	return hsbToRgb(col);
}

inline Color decreaseBrightness (const Color& c, int inc=1)
{
	auto col { rgbToHsb(c) };
	col[2] = decm(col[2], inc, 0);
	return hsbToRgb(col);
}


#define ORANGE Color(255, 127, 0)
#define ORANGE75 Color(255, 159, 63)
#define ORANGE50 Color(255, 191, 127)
#define PEACH Color(255, 191, 127)
#define MEDORANGE Color(191, 95, 0)
#define MEDORANGE75 Color(191, 119, 47)
#define MEDORANGE50 Color(191, 143, 95)
#define DKORANGE Color(127, 63, 0)
#define DKORANGE75 Color(127, 79, 31)
#define DKORANGE50 Color(127, 95, 63)
#define AZURE Color(0, 127, 255)
#define AZURE75 Color(63, 159, 255)
#define AZURE50 Color(127, 191, 255)
#define SKYBLUE Color(127, 191, 255)
#define CORNFLOWER Color(105, 139, 216)
#define MEDAZURE Color(0, 95, 91)
#define MEDAZURE75 Color(47, 119, 191)
#define MEDAZURE50 Color(95, 143, 191)
#define DKAZURE Color(0, 63, 127)
#define DKAZURE75 Color(31, 79, 127)
#define DKAZURE50 Color(63, 95, 127)
#define PURPLE Color(127, 0, 255)
#define PURPLE75 Color(159, 63, 255)
#define PURPLE50 Color(191, 127, 255)
#define RAINYGRAY Color(185, 194, 202)
#define DRABCYAN Color(186, 236, 237)
#define BUTTERSKY Color(255, 255, 150)
#define CHARCOAL Color(20, 20, 24)
#define MUTEDGRASS Color(170, 215, 143)



	/* A convenience method for quick projects and experiments so we don't
	 * have to go through declaring in the header and setting up in onCreate
	 * just for one quick play
	 */
inline void playSoundOnce (const string& file) {
	
	SoundBuffer sb{};
	sb.loadFromFile("resources/" + file);
	Sound snd{};
	snd.setBuffer(sb);
	snd.play();
}


inline void playSoundAtVolPct (Sound& snd, float pct)
{
//	auto oldVal = snd.getVolume();
	snd.setVolume(min(100.f, pct));
	snd.play();
//	snd.setVolume(oldVal);
}




#endif /* jwzsfml_hpp */
