#ifndef jwz_hpp
#define jwz_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <utility>	// pair
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <random>
#include <functional>
#include <memory>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <variant>
#include <optional>
#include <cassert>

#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <array>
#include <regex>
#include <list>
#include <deque>

#if __has_include(<version>)
#include <version>
#endif

#ifdef __cpp_lib_format
#include <format>
using std::format;
#endif

#ifdef __cpp_lib_print
#include <print>
using std::print;
#endif

#ifdef __cpp_lib_erase_if
using std::erase_if;
#endif

using std::string;
using std::vector;
using std::array;
using std::list;
using std::deque;
using std::pair;
using std::tuple;
using std::unordered_map;
using std::map;
using std::set;
using std::unordered_set;
using std::multiset;
using std::multimap;
using std::unordered_multimap;
using std::stack;
using std::queue;

using std::function;
using std::bind;
using std::make_pair;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::make_unique;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::optional;
using std::nullopt;
using std::make_optional;
using std::variant;
using std::get;
using std::get_if;
using std::holds_alternative;
using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::filesystem::path;
using std::filesystem::current_path;
using std::runtime_error;
using std::exception;

using std::cos;
using std::sin;
using std::tan;
using std::atan;
using std::acos;
using std::asin;
using std::abs;
using std::sqrt;
using std::floor;
using std::ceil;
using std::min;
using std::max;
using std::clamp;
using std::isnan;
using std::isinf;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::ostringstream;
using std::getline;
using std::ios_base;
using std::stoi;
using std::stof;
using std::smatch;
using std::regex;

using std::sort;
using std::find;
using std::find_if;
using std::remove;
using std::remove_if;
using std::copy;
using std::copy_if;
using std::move;
using std::swap;
using std::transform;
using std::partition;

using strvec = vector<string>;
using intvec = vector<int>;
using flvec = vector<float>;
using dblvec = vector<double>;
using boolvec = vector<bool>;
using intPair = pair<int, int>;
using flPair = pair<float, float>;
using strPair = pair<string, string>;
using HRClock = std::chrono::high_resolution_clock;


#define uint unsigned int
#define lutab unordered_map
#define tS std::to_string
#define fS floatStr
#define iO indexOf
#define iW indexWhich
#define PAUSE sleep(seconds(.2))
#define PAUSE1 sleep(seconds(.1))
#define BF(prop) { prop = !prop; PAUSE; }  // booleanFlip
#define forNum(num) for (int i = 0; i < num; ++i)
#define forNumJ(num) for (int j = 0; j < num; ++j)
#define forFloat(num) for (float i = 0; i < num; ++i)
#define forFloatJ(num) for (float j = 0; j < num; ++j)
#define forItr(cont) for (auto itr = cont.begin(); itr != cont.end(); ++itr)
#define forEachRef(cont) for (auto& obj : cont)
#define forEachCpy(cont) for (auto obj : cont)


constexpr float     pi = 3.141592654;
constexpr float     degsPerRad = 57.2957795;
	/* Not const so that program can globally use a more lenient value */
inline float		floatEps = .00001;

inline bool 	POn = true;		// Show debug printing

/* Debug print */
inline void dp (const string& str, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (string:) " << str;
    if (nl) cout << endl;
}

inline void dp (int str, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (int:) " << str;
    if (nl) cout << endl;
}

inline void dp (unsigned int str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (uint:) " << str;
	if (nl) cout << endl;
}

inline void dp (float str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (float:) " << str;
	if (nl) cout << endl;
}

inline void dp (unsigned long str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (ulong:) " << str;
	if (nl) cout << endl;
}

inline void dp (long str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (long:) " << str;
	if (nl) cout << endl;
}

inline void dp (unsigned long long str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (ulonglong:) " << str;
	if (nl) cout << endl;
}

inline void dp (long long str, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (longlong:) " << str;
	if (nl) cout << endl;
}

inline void dp (double str, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (double:) " << str;
    if (nl) cout << endl;
}

inline void dp (char str, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (char:) " << str;
    if (nl) cout << endl;
}

inline void dp (bool str, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (bool:) " << (str ? "true" : "false");
    if (nl) cout << endl;
}

inline void dp (vector<bool>& v, bool nl=true, string pfx = "")
{
	if (!POn) return;
	cout << pfx << " (bool){";
	for (int i = 0; i < v.size(); ++i) {
		cout << (v[i] ? "true" : "false");
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << "}";
	if (nl) cout << endl;
}

inline void dp (vector<float>& v, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (float){";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<int>& v, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (int){";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<char>& v, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (char){";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<string>& v, bool nl=true, string pfx = "")
{
    if (!POn) return;
	cout << pfx << " (string){";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << "}";
	if (nl) cout << endl;
}

inline void dp (vector<vector<float>>& v, bool nl=true, string pfx = "")
{
	if (POn) {
		cout << pfx << " (vector<vector<float>>:)\n";
		for (auto& vv : v)
            dp(vv, false);
		if (nl) cout << endl;
	}
}

inline void dp (vector<vector<int>>& v, bool nl=true, string pfx = "")
{
    if (POn) {
        cout << pfx << " (vector<vector<int>>:)\n";
        for (auto& vv : v)
            dp(vv, false);
        if (nl) cout << endl;
	}
}

    /* toString used to be a #define but then it clashed with TGUI */
inline string toString (int i) { return std::to_string(i); }

inline string toString (float i) { return std::to_string(i); }

inline string toString (double i) { return std::to_string(i); }

inline string toString (long i) { return std::to_string(i); }

inline string toString (long long i) { return std::to_string(i); }

inline string toString (unsigned int i) { return std::to_string(i); }

inline string toString (char i) { return std::to_string(i); }

/* Control how many decimal places are printed for floats */
inline string floatStr (float f, int decPlaces = 1) {
	if (isnan(f))
		return "NAN";
	else if (isinf(f))
		return "INFINITY";
    string s = toString(f);
	size_t sublen = s.length();
	size_t lastdot = s.find_last_of(".");
	if (lastdot != s.npos) {
		if (decPlaces == 0)
			sublen = lastdot;
		else sublen = lastdot + 1 + decPlaces;
	}
	return s.substr(0, sublen);
}

inline string ptrStr (void* ptr)
{
	ostringstream ss;
	ss << std::hex << ptr;
	return ss.str();
}

inline string smatchStr (const smatch& sm, const string& id="smatch")
{
	if (!sm.ready())
		return id + " not ready.\n";
//	else if (sm.size() == 0)
//		return id + " has no size.\n";
	ostringstream ss;
	ss << "\t" << id << " {\nSize: " << sm.size() << "\nPrefix:~" << sm.prefix()
	<< "~\nSuffix:~" << sm.suffix() << "~\n";
	for (size_t i = 0; i < sm.size(); ++i) {
		ss << '[' << i << "]: ";
		if (sm[i].matched) {
			ss << "Y : " << sm.position(i) << " : " << sm.length(i)
			<< " :~" << sm.str(i) << "~\n";
		}
		else ss << "N\n";
	}
	ss << "}" << endl;
	return ss.str();
}

inline string stripExtension (const string& fname) 
{
	size_t lastdot = fname.find_last_of(".");
	if (lastdot == std::string::npos)
		return fname;
	return fname.substr(0, lastdot);
}

inline string strip (string& str)
{
	auto idx1 = str.find_first_not_of(" \t");
	auto idx2 = str.find_last_not_of(" \t");
	if (idx1 == str.npos)
		return "";
	return str.substr(idx1, idx2 - idx1 + 1);
}

inline string toUpper (const string& str_)
{
	string str {str_};
	for (auto& ch : str)
		ch = toupper(ch);
	return str;
}

inline string toLower (const string& str_)
{
	string str {str_};
	for (auto& ch : str)
		ch = tolower(ch);
	return str;
}

template<class T>
void resetGetline(T& fs)
{
	fs.clear();
	fs.seekg(0, std::ios::beg);
}


/* ========== TIME ============== */

inline HRClock::time_point timestamp ()
{
	return HRClock::now();
}

inline auto timestampUs ()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(HRClock::now().time_since_epoch()).count();
}

inline unsigned long long nanosecondsBetween(HRClock::time_point t1, HRClock::time_point t2)
{
	return abs(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());
}

inline unsigned long long microsecondsBetween(HRClock::time_point t1, HRClock::time_point t2)
{
	return abs(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());
}

inline unsigned long long millisecondsBetween(HRClock::time_point t1, HRClock::time_point t2)
{
	return abs(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
}

inline unsigned long secondsBetween(HRClock::time_point t1, HRClock::time_point t2)
{
	return abs(std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count());
}


struct LocalTime
{
	LocalTime ()
	{
		time_t rawtime;
		time(&rawtime);
		struct tm* timeInfo {localtime(&rawtime)};
		tm_ = *timeInfo;
		seconds = tm_.tm_sec;
		minutes = tm_.tm_min;
		hours = tm_.tm_hour;
		dayNum = tm_.tm_mday;
		month = tm_.tm_mon + 1;
		year = 1900 + tm_.tm_year;
		weekday = tm_.tm_wday;
		dayOfYear = tm_.tm_yday;
		isDST = tm_.tm_isdst;
	}
	
	LocalTime (struct tm info)
		: seconds(info.tm_sec)
		, minutes(info.tm_min)
		, hours(info.tm_hour)
		, dayNum(info.tm_mday)
		, month(info.tm_mon + 1)
		, year(1900 + info.tm_year)
		, weekday(info.tm_wday)
		, dayOfYear(info.tm_yday)
		, isDST(info.tm_isdst)
		, tm_(info)
	{ }
	
	string time12Hr (bool useSeconds = false)
	{
		stringstream ss;
		int hr = hours % 12;
		if (hr == 0)
			hr = 12;
		ss << hr << ':' << minutes;
		if (useSeconds)
			ss << ':' << seconds;
		ss << ' ' << (hours > 11 ? "PM" : "AM");
		return ss.str();
	}
	
	string ascTime ()
	{
		return string(asctime(&tm_));
	}
	
	string slashDate (bool fullYear = false)
	{
		stringstream ss;
		string yr = std::to_string(year);
		if (!fullYear)
			yr = yr.substr(2);
		ss << month << '/' << dayNum << '/' << yr;
		return ss.str();
	}
	
	string weekdayStr (bool abbrev = false)
	{
		string str = weekdayStrs[weekday];
		if (abbrev)
			str = str.substr(0, 3);
		return str;
	}
	
	string monthStr (bool abbrev = false)
	{
		string str = monthStrs[month];
		if (abbrev)
			str = str.substr(0, 3);
		return str;
	}
	
	inline static const string weekdayStrs[7] = {
		"Sunday"
		, "Monday"
		, "Tuesday"
		, "Wednesday"
		, "Thursday"
		, "Friday"
		, "Saturday"
	};
	
	inline static const string monthStrs[12] = {
		"January"
		, "February"
		, "March"
		, "April"
		, "May"
		, "June"
		, "July"
		, "August"
		, "September"
		, "October"
		, "November"
		, "December"
	};
	
	int	seconds
		, minutes
		, hours
		, dayNum
		, month
		, year
		, weekday
		, dayOfYear
		, isDST
	;
	struct tm tm_;
};




/* ========== NUMERIC ============== */

/* `min` and `max` are included */
inline int randRange (int min, int max)
{
    return rand() % (max - min + 1) + min;
}

/* 0 and `max` are included */
inline int randRange (int max)
{
	return randRange (0, max);
}

/* Only for up to 3 decimal places */
inline float randFloat (float min, float max)
{
	return float(randRange(int(min * 1000), int(max * 1000))) / 1000.f;
}

inline bool flipCoin() { return randRange(1); }

inline float incm (float orig, float inc, float max_)
{
    return min(orig + inc, max_);
}

inline float decm (float orig, float inc, float min_ = 0)
{
    return max(orig - inc, min_);
}

	/* Canonicalize degrees: no negatives or greater than 360. Not necessary
	 * to use this if only passing the result to a trigonometric function.
	 */
inline float czdg (float deg) {
	while (deg < 0)
		deg += 360;
	while (deg >= 360)
		deg -= 360;
	return deg;
	
	
	/* This version takes about 2µs for positive deg and 7-9µs for negative
	 * deg. The above version takes 2-3µs for both pos and neg deg until
	 * deg goes from 100k to 1mil then 17+µs */
//	float ret = fmod(deg, 360);
//	if (ret < 0 )
//		ret += 360;
//	return ret;
}

	/* Canonicalize radians: 0 <= rad < 2𝞹 */
inline float czrd (float rad)
{
	float ret = fmod(rad, 2 * pi);
	if (ret < 0)
		ret += 2 * pi;
	return ret;
}

inline float toDeg (float rad) { return czdg(rad * degsPerRad); }

inline float toRad (float deg) { return czdg(deg) / degsPerRad; }

    /* Trigonometric functions using degrees */
inline float cosd (float ang) { return cos(toRad(ang)); }

inline float sind (float ang) { return sin(toRad(ang)); }

inline float tand (float ang) { return tan(toRad(ang)); }

inline float atand (float x, float y) { return toDeg(atan2(x, y)); }

/* Get hypotenuse */
inline float hyp (float x, float y) { return abs(sqrt(x * x + y * y)); }

inline double hyp (double x, double y) { return abs(sqrt(x * x + y * y)); }

/* Check whether value falls within a range: options to equal the limits */
inline bool between (float num, float mn, float mx,
                    bool minweq = false, bool maxweq = false)
{
   if (minweq) {
       if (maxweq)
            return num >= mn && num <= mx;
        else return num >= mn && num < mx;
    }
    else if (maxweq)
        return num > mn && num <= mx;
    else return num > mn && num < mx;
}

inline float mean (float a, float b) { return min(a, b) + abs(b - a) / 2; }

inline float absDif (float a, float b) { return abs(b - a); }

inline float absCos (float deg) { return abs(cosd(deg)); }

inline float absSin (float deg) { return abs(sind(deg)); }

/* Epsilon comparisons for floats */
inline bool epsEquals (float a, float b, float eps = floatEps, bool disregardInfSign = false)
{
	if (std::isnan(a) || std::isnan(b))
		return false;
	if (std::isinf(a)) {
		/* Potentially use for collinearity checks */
		if (disregardInfSign)
			return std::isinf(b);
		else if (a > 0)
			return std::isinf(b) && b > 0;
		else return std::isinf(b) && b < 0;
	}
	else if (std::isinf(b))
		return false;
	
	return absDif(a, b) < eps;
}

inline bool epsGTE (float a, float b, float eps = floatEps, bool disregardInfSign = false)
{
	return a > b || epsEquals(a, b, eps, disregardInfSign);
}

inline bool epsLTE (float a, float b, float eps = floatEps, bool disregardInfSign = false)
{
	return a < b || epsEquals(a, b, eps, disregardInfSign);
}

inline bool epsEquals (vector<float> v1, vector<float> v2)
{
	if (v1.size() != v2.size())
		return false;
	for (int i = 0; i < v1.size(); ++i) {
		if (!epsEquals(v1[i], v2[i]))
			return false;
	}
	return true;
}

inline bool isOrBetween (float arg, float mn, float mx, float eps=floatEps)
{
	return epsGTE(arg, mn, eps) && epsLTE(arg, mx, eps);
}

/* Finds the <= 180 angle between two given angles
 * USE czdg FIRST.
 */
inline float angleBetween (float ang1, float ang2)
{
		/* If the degree values of the two angles have a difference of more than 180,
		 * the solution angle will encompass the 0° mark.
		 */
	float angleDif = abs(ang1 - ang2);
	if (angleDif > 180)
		angleDif = 360 - angleDif;
	return angleDif;
}

/* Make sure that 0 == 359.99999 for epsilon situations
 * USE czdg FIRST.
 */
inline bool angEpsEquals (float ang1, float ang2, float eps=floatEps)
{
	return epsEquals(angleBetween(ang1, ang2), 0, eps);
	/* Old version without angleBetween
	 float redZone = 360 - eps;
	 if (ang1 > redZone && ang2 < ang1 - eps) {
	 return ((360 - ang1) + ang2) < eps;
	 }
	 else if (ang2 >= redZone && ang1 < ang2 - eps) {
	 return ((360 - ang2) + ang1) < eps;
	 }
	 return epsEquals(ang1, ang2, eps);
	 */
}

/* Always returns a positive magnitude */
inline float clockwiseAngleBetween (float fromAng, float toAng)
{
	if (toAng > fromAng)
		return toAng - fromAng;
	else return 360 - fromAng + toAng;
}

inline float counterclockwiseAngleBetween (float fromAng, float toAng)
{
	if (toAng < fromAng)
		return fromAng - toAng;
	else return 360 - toAng + fromAng;
}
#define counterClockwiseAngleBetween counterclockwiseAngleBetween

/* Determine whether testAng would sooner be reached going clockwise from refAng
 * rather than otherwise
 */
inline bool clockwiseOf (float testAng, float refAng)
{
	if (czdg(refAng) < 180)
		return testAng >= refAng && testAng <= czdg(refAng + 180);
	else return testAng >= refAng || testAng <= czdg(refAng + 180);
}

/* Range for inclusion begins at `startAng` and continues *clockwise* to `endAng` */
inline bool angleIsOrFallsBetween (float testAng, float startAng, float endAng, float eps=floatEps)
{
	// COULD THERE ever be a time different eps values wanted for angEps/isOrBetw.
	testAng = czdg(testAng);
	startAng = czdg(startAng);
	endAng = czdg(endAng);
	if (angEpsEquals(startAng, endAng, eps))
		return angEpsEquals(testAng, startAng, eps);
	if (startAng < endAng)
		return isOrBetween(testAng, startAng, endAng, eps);
	else return epsGTE(testAng, startAng)
				|| epsLTE(testAng, endAng);
}

inline bool angleIsOrFallsBetweenRads (float testAng, float startAng, float endAng, float eps=floatEps)
{
	testAng = czrd(testAng);
	startAng = czrd(startAng);
	endAng = czrd(endAng);
	if (epsEquals(startAng, endAng))
		return epsEquals(testAng, startAng);
	if (startAng < endAng)
		return isOrBetween(testAng, startAng, endAng);
	else return testAng >= startAng
		|| testAng <= endAng;
}

inline float bisect (float startAng, float endAng)
{
	return czdg(startAng + angleBetween(startAng, endAng) / 2);
}

inline float bisectSmallest (float ang1, float ang2)
{
	if (clockwiseOf(ang2, ang1))
		return bisect(ang1, ang2);
	else return bisect(ang2, ang1);
}

inline bool isCloserToHorizontal (float testAng, float refAng)
{
	float testDif = angleBetween(angleIsOrFallsBetween(testAng, 90, 270) ? 180 : 0, testAng);
	float refDif = angleBetween(angleIsOrFallsBetween(refAng, 90, 270) ? 180 : 0, refAng);
	return testDif < refDif;
}

inline bool isCloserToVertical (float testAng, float refAng)
{
	float testDif = angleBetween(angleIsOrFallsBetween(testAng, 0, 180) ? 90 : 270, testAng);
	float refDif = angleBetween(angleIsOrFallsBetween(refAng, 0, 180) ? 90 : 270, refAng);
	return testDif < refDif;
}

inline float absCos(float ang1, float ang2)
{
	return abs(cosd(angleBetween(ang1, ang2)));
}

inline float absSin(float ang1, float ang2)
{
	return abs(sind(angleBetween(ang1, ang2)));
}

/* Pass first the side opposite the angle you want */
inline float angleFrom3Sides (float opp, float adj1, float adj2)
{
	return toDeg(acos(
					  (adj1 * adj1 + adj2 * adj2 - opp * opp) /
					  (2 * adj1 * adj2)
					  ));
}



//=================================================


template <class Subclass, class Base>
bool isOfKind (Base* obj)
{
	return dynamic_cast<Subclass*>(obj) != nullptr;
}

template <class Subclass, class Base>
bool isOfKind (shared_ptr<Base>& obj)
{
	return dynamic_pointer_cast<Subclass>(obj) != nullptr;
}

#define valW valWhich

template<typename Cont, typename Pred>
typename Cont::value_type* valWhich (Cont& c, Pred p)
{
	auto itr = find_if(c.begin(), c.end(), p);
	return itr != c.end() ? &(*itr) : nullptr;
}

template<typename Cont>
int indexOfRef (const Cont& cont, typename Cont::value_type& ele)
{
	for (int i = 0; i < cont.size(); ++i) {
		if (&cont[i] == &ele)
            return i;
	}
	return -1;
}

template<typename Cont>
int indexOf (const Cont& cont, typename Cont::value_type ele)
{
	for (int i = 0; i < cont.size(); ++i) {
		if (cont[i] == ele)
			return i;
	}
	return -1;
}

template<typename Cont, typename Pred>
int indexWhich (const Cont& cont, Pred p)
{
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            return i;
	}
	return -1;
}
	
template<typename Cont, typename Pred>
int countWhich (const Cont& cont, Pred p)
{
	int ct = 0;
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            ++ct;
	}
	return ct;
}
	
template<class T, class P>
vector<T> subset (const vector<T>& v, P p)
{
	vector<T> sub;
	copy_if(v.begin(), v.end(), back_inserter(sub), p);
	return sub;
}

/*
 * Cannot properly get a subset vector of references
 * like a TADS3 list: have to subset through pointers
 * or indices instead.
 */

template<class T>
vector<T> vecMinusVec (const vector<T>& v, const vector<T>& v2)
{
	vector<T> ret;
	copy_if(v.begin(), v.end(), back_inserter(ret),
		[&](auto x) {
			return find(v2.begin(), v2.end(), x) == v2.end();
	});
	return ret;
}

template<class T>
vector<T> vecPlusVec(const vector<T>& lhs, const vector<T>& rhs)
{
	vector<T> ret {};
	ret.reserve(lhs.size() + rhs.size());
	ret.insert(ret.end(), lhs.begin(), lhs.end());
	ret.insert(ret.end(), rhs.begin(), rhs.end());
	return ret;
}

template<class T>
vector<T>& vecPlusEqVec(vector<T>& lhs, const vector<T>& rhs)
{
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}

/* Modifies original vector */
template<class T>
vector<T>& appendUnique(vector<T>& lhs, const vector<T>& rhs)
{
	for (auto& ele : rhs)
		if (find(lhs.begin(), lhs.end(), ele) == lhs.end())
			lhs.push_back(ele);
}

template<class C, class P>
void forEachAssoc(C& c, P p)
{
	int i = 0;
	for (auto& ele : c) {
		p(i++, ele);
	}
}

/* Returns copy */
template<class T>
vector<T> getUnique(const vector<T>& c)
{
	unordered_set<T> uoset;
	vector<T> culled;
	culled.reserve(c.size());
	for (auto& ele : c) {
//		if (find(culled.begin(), culled.end(), ele) == culled.end())
		if (uoset.insert(ele).second)
			culled.push_back(ele);
	}
	return culled;
}

template<class T>
int indexOfMax(const vector<T>& c)
{
	if (c.empty())
		return -1;
	return distance(c.begin(), max_element(c.begin(), c.end()));
}

/* Returns elements in the order they appear in the lefthand vector.
 * Only matches pairs of duplicate elements, so intersect {1,2,1,3,1},
 * {3,1,1,3,4} will return {1,1,3}
 */
template<class T>
vector<T> intersect(const vector<T>& lhs, const vector<T>& rhs)
{
	vector<T> ret;
	ret.reserve(lhs.size());
	vector<T> rcopy {rhs};
	for (auto& ele : lhs) {
		auto itr = find(rcopy.begin(), rcopy.end(), ele);
		if (itr != rcopy.end()) {
			ret.push_back(ele);
			rcopy.erase(itr);
		}
	}
	return ret;
}
// make unique val version

template<class T>
string join(const vector<T>& v, string sep = "")
{
	stringstream ss;
	for (size_t i = 0; i < v.size(); ++i) {
		ss << v[i];
		if (sep != "" && i < v.size() - 1)
			ss << sep;
	}
	return ss.str();
}

template<class T>
int lastIndexOf(const vector<T>& v, T val)
{
	auto ritr = find(v.rbegin(), v.rend(), val);
	return (ritr != v.rend() ? distance(ritr, v.rend()) - 1 : -1);
}

	/* Modifies original.
	 * Last element of v can be referred to as index -1,
	 * etc.
	 */
template<class T>
vector<T>& splice(vector<T>& v, int startIdx, int deleteCt, const vector<T>& newElems)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(v.size()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > v.size()
		|| (deleteCt && startIdx + deleteCt > v.size()))
		return v;	// Abort if bad values passed
	auto itr = v.begin() + startIdx;
	if (deleteCt)
		itr = v.erase(itr, v.begin() + startIdx + deleteCt);
	v.insert(itr, newElems.begin(), newElems.end());
	return v;
}

/* Initializer list version */
template<class T>
vector<T>& splice(vector<T>& v, int startIdx, int deleteCt, const std::initializer_list<T>& newElems)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(v.size()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > v.size()
		|| (deleteCt && startIdx + deleteCt > v.size()))
		return v;	// Abort if bad values passed
	auto itr = v.begin() + startIdx;
	if (deleteCt)
		itr = v.erase(itr, v.begin() + startIdx + deleteCt);
	v.insert(itr, newElems.begin(), newElems.end());
	return v;
}

/* If numToIncl isn't passed, it means take from startIdx to end of list */
template<class T>
vector<T> sublist(const vector<T>& v, int startIdx, int numToIncl = 0)
{
	if (startIdx < 0) {
		startIdx = int(v.size()) + startIdx;
	}
	if (startIdx < 0 || startIdx >= v.size())
		return v;	// Abort if bad values passed
	vector<T> sub;
	if (v.empty())
		return sub;
	auto endItr = v.end();  // if numToIncl==0
	if (numToIncl > 0)
		endItr = v.begin() + startIdx + numToIncl;
	else if (numToIncl < 0)
		endItr = v.end() + numToIncl; // not minus
	sub.reserve(distance(v.begin() + startIdx, endItr));
	copy(v.begin() + startIdx, endItr, back_inserter(sub));
	return sub;
}


inline bool endsWith(const string& str, string endStr, bool ignoreCase = false)
{
	string str_ = str;
	if (ignoreCase) {
		str_ = toLower(str);
		endStr = toLower(endStr);
	}
	return endStr == str_.substr(str.size() - endStr.size());
}

inline bool startsWith(const string& str, string startStr, bool ignoreCase = false)
{
	string str_ = str;
	if (ignoreCase) {
		str_ = toLower(str);
		startStr = toLower(startStr);
	}
	return startStr == str_.substr(0, startStr.size());
}

inline vector<string> split(const string& str, string delim="")
{
	vector<string> ret;
	if (delim.empty()) {
		/* Split into one-char strings */
		forNum(str.length())
			ret.push_back(str.substr(i, 1));
	}
	else {
		string str_ {str};
		size_t i = 0;
		while (i < str_.size()) {
			size_t idx = str_.find(delim);
			if (idx == str_.npos) {
				ret.push_back(str_.substr(i));
				break;
			}
			ret.push_back(str_.substr(i, idx - i));
			str_.replace(idx, delim.size(), "");
			i = idx;
		}
	}
	return ret;
}

inline vector<string> split(const string& str, char delim)
{
	string delimStr(1, delim);
	return split(str, delimStr);
}

/* Chunk size is clamped to (1, str.size) */
inline vector<string> split(const string& str, int chunkSize)
{
	vector<string> ret;
	chunkSize = clamp(chunkSize, 1, (int)str.length());
	int i = 0;
	for ( ; i < str.size() - chunkSize; i += chunkSize) {
		ret.push_back(str.substr(i, chunkSize));
	}
		/* Could be shorter than chunkSize at end */
	if (i < str.size())
		ret.push_back(str.substr(i));
	return ret;
}
// TADS3 implements a final optional arg for max # of substrings

inline string& splice(string& str, int startIdx, int deleteCt, const string& insertStr)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(str.length()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > str.length()
		|| (deleteCt && startIdx + deleteCt > str.length()))
		return str;	// Abort if bad values passed
	auto itr = str.begin() + startIdx;
	if (deleteCt)
		itr = str.erase(itr, str.begin() + startIdx + deleteCt);
	str.insert(itr, insertStr.begin(), insertStr.end());
	return str;
}

inline bool match(const string& str, const string& strToFind, int startIdx=0)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(str.length()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > str.length())
		return false;	// Abort if bad values passed
	return strToFind == str.substr(startIdx, strToFind.length());
}

inline string& findReplaceAll(string& str, const string& oldStr, const string& newStr, int startIdx = 0)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(str.length()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > str.length())
		return str;	// Abort if bad values passed
	while ((startIdx = (int)str.find(oldStr, startIdx)) != string::npos) {
		str.replace(startIdx, oldStr.size(), newStr);
		startIdx += newStr.size();
	}
	return str;
}

inline string& findReplaceOnce(string& str, const string& oldStr, const string& newStr, int startIdx = 0)
{
	/* Allow negative indices to be counted from the end */
	if (startIdx < 0) {
		startIdx = int(str.length()) + startIdx;
	}
	if (startIdx < 0
		|| startIdx > str.length())
		return str;	// Abort if bad values passed
	if ((startIdx = (int)str.find(oldStr, startIdx)) != string::npos) {
		str.replace(startIdx, oldStr.size(), newStr);
	}
	return str;
}

template<class M>
vector<typename M::key_type> keysToVec(M& m)
{
	vector<typename M::key_type> keys;
	for (auto& kv : m)
		keys.push_back(kv.first);
	return keys;
}

template<class M>
vector<typename M::mapped_type> valsToVec(M& m)
{
	vector<typename M::mapped_type> vals;
	for (auto& kv : m)
		vals.push_back(kv.second);
	return vals;
}

template<class S>
vector<typename S::value_type> setToVec(S& s)
{
	return {s.begin(), s.end()};
}

template<typename Cont>
Cont& eraseElem (Cont& c, typename Cont::value_type ele)
{
	auto itr = std::find(c.begin(), c.end(), ele);
	if (itr != c.end())
		c.erase(itr);
	return c;
}

template<typename Cont>
Cont& eraseIndex (Cont& c, size_t index)
{
	if (index < c.size())
		c.erase(c.begin() + index);
	return c;
}

template<typename Cont>
typename Cont::value_type vecPopRand (Cont& cont)
{
	int sz = int(cont.size());
	if (sz < 1)
        cerr << "Container size 0";
	int idx = randRange(sz - 1);
	auto ret = cont[idx];
	cont.erase(cont.begin() + idx);
	return ret;
}

template<typename Cont>
typename Cont::value_type* randElemPtr (const Cont& cont)
{
	int sz = int(cont.size());
	if (sz < 1)
        cerr << "Container size 0";
	return &cont[randRange(sz - 1)];
}

template<typename Cont>
typename Cont::value_type& randElemRef (const Cont& cont)
{
	int sz = int(cont.size());
	if (sz < 1)
        cerr << "Container size 0";
	return cont[randRange(sz - 1)];
}

template<typename Cont>
typename Cont::value_type randElemVal (const Cont& cont)
{
	int sz = int(cont.size());
	if (sz < 1)
        cerr << "Container size 0";
	return cont[randRange(sz - 1)];
}

template<typename Cont, typename Pred>
typename Cont::value_type* findFirstWhich (Cont& c, Cont& d, Pred p)
{
    return &(*(find_first_of(c.begin(), c.end(), d.begin(), d.end(), p)));
}

namespace jwz
{

template<typename T>
class Pointer
{
public:
//	template<class... Args>
//	Pointer (Args&&... args)
//		: ptr_(make_unique<PointerUnq>(std::forward<Args>(args)...))
//	{ }
	Pointer (unique_ptr<T>&& unq) : ptr_(make_unique<PointerUnq>(std::move(unq))) { }
	Pointer (const shared_ptr<T>& shd) : ptr_(make_unique<PointerShd>(shd)) { }
	Pointer (shared_ptr<T>&& shd) noexcept : ptr_(make_unique<PointerShd>(std::move(shd))) { }
	Pointer (const weak_ptr<T>& wk) : ptr_(make_unique<PointerWk>(wk)) { }
	Pointer (T* tptr) : ptr_(make_unique<PointerRaw>(tptr)) { }
	Pointer& operator= (Pointer&& p) noexcept
	{
		ptr_ = std::move(p.ptr_);
		return *this;
	}
	Pointer (Pointer&& p) noexcept : ptr_(std::move(p.ptr_)) { }
	Pointer (const Pointer& p) = delete;
	Pointer& operator= (const Pointer& p) = delete;
	
	explicit operator bool () const { return get() != nullptr; }
	
	T* get () const { return ptr_ ? ptr_.get()->get() : nullptr; }
	
	T* operator-> () const { return get(); };
	
	T& operator* () const { return *get(); };
	
private:
	struct _Pointer
	{
		virtual ~_Pointer () = default;
		virtual T* get () = 0;
	};
	
	struct PointerUnq: public _Pointer
	{
//		template<class... Args>
//		PointerUnq (Args&&... args)
//			: ptr(make_unique<T>(std::forward<Args>(args)...))
//		{ }
		PointerUnq (unique_ptr<T>&& unq) : ptr(std::move(unq)) { }

		
		T* get () override { return ptr.get(); }
		
		unique_ptr<T>		ptr;
	};
	
	struct PointerShd: public _Pointer
	{
		PointerShd (const shared_ptr<T>& shd) : ptr(shd) { }
		PointerShd (shared_ptr<T>&& shd) noexcept : ptr(std::move(shd)) { }
		
		T* get () override { return ptr.get(); }
		
		shared_ptr<T>		ptr;
	};
	
	struct PointerWk: public _Pointer
	{
		PointerWk (const weak_ptr<T>& wk) : ptr(wk) { }
		
		T* get () override { return ptr.lock().get(); }
		
		weak_ptr<T>		ptr;
	};
	
	struct PointerRaw: public _Pointer
	{
		PointerRaw (T* ptr_) : ptr(ptr_) { }
		PointerRaw (const T& tref) : ptr(&tref) { }
		
		T* get () override { return ptr; }
		
		T*		ptr;
	};
	
	unique_ptr<_Pointer>	ptr_;
};


} // end namespace jwz

using jwz::Pointer;

#endif  /* jwz_hpp */
