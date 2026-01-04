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
//variant?

#include <set>
#include <unordered_set>
//#include <list>
//#include <regex>
//#include <array>
//#include <deque>
//#include <queue>
//#include <stack>


using std::string;
using std::vector;
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
using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::filesystem::path;
using std::filesystem::parent_path;
using std::filesystem::current_path;


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


#define self (*this)
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


inline const string	cppPath = "/Users/johnwz/Programming/CPP/";
inline const string	headerPath = "/Users/johnwz/Programming/CPP/gameheaders/";
inline const string rscPath = "/usr/local/rsc/";
inline const string imgPath = "/usr/local/rsc/img/";
inline const string sndPath = "/usr/local/rsc/snd/";

constexpr float     pi = 3.141592654;
constexpr float     degsPerRad = 57.2957795;
	/* Not const so that program can globally use a more lenient value */
inline float		floatEps = .00001;

inline bool 	POn = true;	// show debug printing?

inline void dp (const string& str, bool nl=true, string pfx = "") {
    if (POn) cout << str;
    if (nl) cout << endl;
}

inline void dp (int str, bool nl=true, string pfx = "") {
    if (POn) cout << "int: "<< str;
    if (nl) cout << endl;
}

inline void dp (unsigned int str, bool nl=true, string pfx = "") {
	if (POn) cout << "uint: "<< str;
	if (nl) cout << endl;
}

inline void dp (float str, bool nl=true, string pfx = "") {
	if (POn) cout << "float: "<< str;
	if (nl) cout << endl;
}

inline void dp (unsigned long str, bool nl=true, string pfx = "") {
	if (POn) cout << "ulong: "<< str;
	if (nl) cout << endl;
}

inline void dp (long str, bool nl=true, string pfx = "") {
	if (POn) cout << "long: "<< str;
	if (nl) cout << endl;
}

inline void dp (unsigned long long str, bool nl=true, string pfx = "") {
	if (POn) cout << "ulonglong: "<< str;
	if (nl) cout << endl;
}

inline void dp (long long str, bool nl=true, string pfx = "") {
	if (POn) cout << "longlong: "<< str;
	if (nl) cout << endl;
}

inline void dp (double str, bool nl=true, string pfx = "") {
    if (POn) cout << "double: "<< str;
    if (nl) cout << endl;
}

inline void dp (char str, bool nl=true, string pfx = "") {
    if (POn) cout << "char: "<< str;
    if (nl) cout << endl;
}

inline void dp (bool str, bool nl=true, string pfx = "") {
    if (POn) cout << "bool: " << (str ? "true" : "false");
    if (nl) cout << endl;
}

inline void dp (vector<bool>& v, bool nl=true) {
	if (POn) cout << "{";
	for (int i = 0; i < v.size(); ++i) {
		cout << (v[i] ? "true" : "false");
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << "}";
	if (nl) cout << endl;
}

inline void dp (vector<float>& v, bool nl=true) {
    if (POn) cout << "{";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<int>& v, bool nl=true) {
    if (POn) cout << "{";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<char>& v, bool nl=true) {
    if (POn) cout << "{";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
    cout << "}";
    if (nl) cout << endl;
}

inline void dp (vector<string>& v, bool nl=true) {
    if (POn) cout << "{";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
   cout << "}";
	if (nl) cout << endl;
}

inline void dp (vector<vector<float>>& v, bool nl=true) {
	if (POn) {
		cout << "vector<vector>>: \n";
		for (auto& vv:v)
            dp(vv, false);
		if (nl) cout << endl;
		}
	}

inline void dp (vector<vector<int>>& v, bool nl=true) {
    if (POn) {
        cout << "vector<vector>>: \n";
        for (auto& vv:v)
            dp(vv, false);
        if (nl) cout << endl;
        }
    }

    // toString used to be a #define but then it clashed with TGUI
inline string toString (int i) {
    return std::to_string(i);
}

inline string toString (float i) {
    return std::to_string(i);
}

inline string toString (double i) {
    return std::to_string(i);
}

inline string toString (long i) {
    return std::to_string(i);
}

inline string toString (long long i) {
    return std::to_string(i);
}

inline string toString (unsigned int i) {
    return std::to_string(i);
}

inline string toString (char i) {
    return std::to_string(i);
}

	// `erase` sometimes throws errors... substring
inline string floatStr (float f, int decPlaces = 1) {
	if (std::isnan(f))
		return "NAN";
    string s = tS(f);
    return s.erase(!decPlaces || (decPlaces == 1 && s[s.size() - 1] == '0') ?
                   s.size() - (8 - decPlaces) :
                   s.size() - (6 - decPlaces));
}

inline string ptrStr (void* ptr)
{
	ostringstream ss;
	ss << std::hex << ptr;
	return ss.str();
}

inline string stripExtension (const string& fname) 
{
	size_t lastdot = fname.find_last_of(".");
	if (lastdot == std::string::npos)
		return fname;
	return fname.substr(0, lastdot);
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
		year = 1900 + tm_.tm_year; // year = tm_.tm_year;
		weekday = tm_.tm_wday;
		dayOfYear = tm_.tm_yday;
		isDST = tm_.tm_isdst;
	}
	
	LocalTime (struct tm info)
		: seconds(info.tm_sec)
		, minutes(info.tm_min)
		, hours(info.tm_hour)
		, dayNum(info.tm_mday)
//		, month(info.tm_mon)
//		, year(info.tm_year)
		, weekday(info.tm_wday)
		, dayOfYear(info.tm_yday)
		, isDST(info.tm_isdst)
		, tm_(info)
	{
		year = 1900 + info.tm_year;
		month = info.tm_mon + 1;
	}
	
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

inline int randRange (int min, int max)
{
    return rand() % (max - min + 1) + min;
}

inline int randRange (int max)
{
	return randRange (0, max);
}

inline float randFloat (float min, float max)
{
	return float(randRange(int(min * 1000), int(max * 1000))) / 1000.f;
}

inline bool flipCoin() { return randRange(1); }

inline float incm (float orig, float inc, float max_) {
    return min(orig + inc, max_);
}

inline float decm (float orig, float inc, float min_ = 0) {
    return max(orig - inc, min_);
}

	/* Canonicalize degrees: no negatives or greater than 360. Not necessary to use this if
	 * only passing the result to a trigonometric function
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

	/* Canonicalize radians: 0 <= rad < 2𝞹*/
inline float czrd (float rad)
{
	float ret = fmod(rad, 2 * pi);
	if (ret < 0)
		ret += 2 * pi;
	return ret;
}

inline float toDeg (float rad) {
	return czdg(rad * degsPerRad);
}

//inline float toDeg (float rad) {		// old form
//	float conv = rad * degsPerRad;
//	int flr = floor(conv);
//	auto ret = flr % 360 + conv - flr;
//	if (ret < 0)
//		ret += 360;
//	return ret;
//}

inline float toRad (float deg) {
	return czdg(deg) / degsPerRad;
}

//inline float toRad (float deg) {		// old form
//	if (deg < 0)
//		deg += 360;
//	return (deg >= 360 ?
//			int(floor(deg)) % 360 + deg - floor(deg) :
//			deg)
//			/ degsPerRad;
//}

    // trigonometric functions using degrees
inline float cosd (float ang) {
    return cos(toRad(ang));
}

inline float sind (float ang) {
    return sin(toRad(ang));
}

inline float tand (float ang) {
    return tan(toRad(ang));
}

inline float atand (float x, float y) {
	return toDeg(atan2(x, y));
}


inline float hyp (float x, float y) {
    return abs(sqrt(x * x + y * y));
}

inline double hyp (double x, double y) {
    return abs(sqrt(x * x + y * y));
}

inline bool between (float num, float mn, float mx,
                    bool minweq = false, bool maxweq = false) {
   if (minweq) {
       if (maxweq)
            return num >= mn && num <= mx;
        else return num >= mn && num < mx;
    }
    else if (maxweq)
        return num > mn && num <= mx;
    else return num > mn && num < mx;
}

inline float mean (float a, float b)
{
	return min(a, b) + abs(b - a) / 2;
}

inline float absDif (float a, float b)
{
	return abs(b - a);
}

inline bool isOrBetween (float arg, float mn, float mx) {
    return arg >= mn && arg <= mx;
}

inline bool epsEquals (float a, float b, float eps = floatEps, bool disregardInfSign = false)
{
	if (std::isnan(a) || std::isnan(b))
		return false;	//// true?
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

	/* finds the <= 180 angle between two given angles */
inline float angleBetween (float ang1, float ang2)
{
		/* if the degree values of the two angles have a difference of more than 180,
		 * the solution angle will encompass the 0° mark. Instead of merely finding the
		 * difference between angles for a solution, we have to add (360 - larger degree)
		 * to the smaller degree to get the full angle
		 */
	float angleDif = abs(ang1 - ang2);
	if ( angleDif > 180)
		return (360 - max(ang1, ang2)) + min(ang1, ang2);
	else return angleDif;
}

	/* always returns a positive magnitude */
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

	/* determine whether testAng would sooner be reached going clockwise from refAng
	 * rather than otherwise
	 */
inline bool clockwiseOf (float testAng, float refAng)
{
	if (czdg(refAng) < 180)
		return testAng >= refAng && testAng <= czdg(refAng + 180);
	else return testAng >= refAng || testAng <= czdg(refAng + 180);
}

	/* Range for inclusion begins at `startAng` and continues clockwise to `endAng`.
	 */
inline bool angleIsOrFallsBetween (float testAng, float startAng, float endAng)
{
	testAng = czdg(testAng);
	startAng = czdg(startAng);
	endAng = czdg(endAng);
	if (epsEquals(startAng, endAng))
		return epsEquals(testAng, startAng);
	if (startAng < endAng)
		return isOrBetween(testAng, startAng, endAng);
	else return testAng >= startAng
		|| testAng <= endAng;
}

inline bool angleIsOrFallsBetweenRads (float testAng, float startAng, float endAng)
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



struct Matrix {
	float determinant4() {
		if (!isSquare) {
			cout<<"Determinant inapplicable: non-square matrix\n";
			return NAN; }
		if (numRows < 4)
			return determinant();
		if (numRows > 4) { cout<<"Determinant of degree 5 and higher not supported\n"; return NAN; }

		Matrix subm1(3, 3);
		Matrix subm2(3, 3);
		Matrix subm3(3, 3);
		Matrix subm4(3, 3);
		makeSub(subm1, 0);
		makeSub(subm2, 1);
		makeSub(subm3, 2);
		makeSub(subm4, 3);
		return data[0][0] * subm1.determinant() - data[1][0] * subm2.determinant() +
			data[2][0] * subm3.determinant() - data[3][0] * subm4.determinant();
	}
	
	float determinant() {
		if (numRows == 2)  return data[0][0] * data[1][1] - data[1][0] * data[0][1];
		float mnr1, mnr2, mnr3;
		mnr1 = data[1][1] * data[2][2] - data[2][1] * data[1][2];
		mnr2 = data[0][1] * data[2][2] - data[2][1] * data[0][2];
		mnr3 = data[0][1] * data[1][2] - data[1][1] * data[0][2];
		return data[0][0] * mnr1 - data[1][0] * mnr2 + data[2][0] * mnr3;
	}

			int 	numRows,
					numCols;
			bool isSquare = false;
			bool isInvertible = false;
			vector<vector<float>>	data;
		
// 	Matrix subm(int r) {
// 		Matrix m(3, 3);
// 		for (int i = 0, ct0; i < numRows; ++i) {
// 			if (i == r) continue;
// 			for (int j = 1; j < 4; ++j) {
// 				m.data[ct][j] = data[i][j];
// 				++ct;
// 				}
// 			}
// 		return m;
// 		}
	
	void makeSub(Matrix& m, int r) {
		for (int i = 0, ct = 0; i < numRows; ++i) {
			if (i == r) continue;
			for (int j = 0; j < 3; ++j) {
				m.data[ct][j] = data[i][j + 1];
				}
			++ct;
			}
		}
	
	float getCofactor(int r, int c) {
		Matrix m(numRows - 1, numCols - 1);
		for (int i = 0, rct = 0, cct = 0; i <  numRows; ++i) {
			if (i == r)
				continue;
			cct = 0;
			for (int j = 0; j <  numCols; ++j) {
				if (j == c)
					continue;
				m.data[rct][cct] = data[i][j];
				++cct;
			}
			++rct;
		}
		return m.determinant4() * ((r + c) % 2 == 0 ? 1 : -1);
	}
		
	Matrix(vector<vector<float>> v) {
		data = v;
		numRows = (int)v.size();
		numCols = (int)v[0].size();
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
	
	Matrix(const Matrix& m) {
		data = m.data;
		numRows = m.numRows;
		numCols = m.numCols;
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
	
	Matrix(int r, int c) {
		numRows = r;
		numCols = c;
		data = vector<vector<float>> {};
		for (int rr = 0; rr < r; ++rr) {
			vector<float> v{};
			for (int cc = 0; cc < c; ++cc) {
				v.push_back(0.f);
			}
			data.push_back(v);
		}
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
		
	void swapRows(int r1, int r2) {
		auto temp = data[r1];
		data[r1] = data[r2];
		data[r2] = temp;
		///// flip determinant sign
	}

	int countZeros(int r) {
		int sum = 0;
		for (int j = 0; j < numCols; ++j) {
			if (data[r][j] != 0) break;
			else ++sum;
			}
		return sum;
	}

	void checkSwap(int r) {
// 			for (int i = r + 1; i <  numRows; ++i) {
		if (countZeros(r) > r) swapRows(r, countZeros(r));
	}

	void multiplyRow(int r, float k) {
		if (k == 0) {
			cerr << "Can't multiply row by zero"<< endl;
			return;
		}
		for (auto& c : data[r])
			c *= k;
	}

	vector<float> multiplyCopy(int r, float k) {
		vector<float> v = data[r];
		for (auto& c : v)
			c *= k;
		return v;
	}

	vector<float> addRows(vector<float> r1, vector<float> r2) {
		vector<float> v{};
		for (int i = 0; i < r1.size(); ++i)
			v.push_back(r1[i] + r2[i]);
		return v;
	}

	void multiplyAdd(int r1, float k, int r2) {
		auto mr = multiplyCopy(r1, k);
		data[r2] = addRows(mr, data[r2]);
	}

	int findRow(int r, int c) {
		for (int i = 0; i < numRows; ++i) {
			if (i != r && data[i][c] != 0) {
				bool ret = true;
				for (int j = 0; j < c; ++j)
					if (data[r][j] == 0 && data[i][j] != 0) { ret = false; break; }
				if (ret)  return i;
				}
			}
		return 0;
	}

	void echelon() {
		//Matrix copy = *this;
		for (int i = 1; i <  numRows; ++i) {
			if (data[0][0] == 0)
				swapRows(0, i);
			else break;
		}
		if (data[0][0] == 0) {
			cout << "Not handling all-zero first column";
			return;
		}
		for (int j = 0; j < numRows - 1; ++j) {
			for (int i = j + 1; i < numRows; ++i) {
// 	cout<<"row "<<i<<", col "<<j<<": "<<data[i][j]<<"\n";	p(*this);
				float cell = data[i][j];
				if (cell != 0) {
					auto fr = findRow(i, j);
// 	if (i == 2 && j == 1) dp(fr);
					multiplyRow(i, data[fr][j]);
// 	p(*this);
					multiplyAdd(fr, -cell, i);
// 	p(*this);
					checkSwap(i);
// 	cout<<"changed:"<<endl; p(*this);
					}
				}
			}
		
		}
	
	void transpose() {
		Matrix t{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				t.data[c][r] = data[r][c];   //CHECK?
			}
		}
		numRows = t.numRows;
		numCols = t.numCols;
		data = t.data;
	}
	
	Matrix transposeCopy() {
		Matrix t{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				t.data[c][r] = data[r][c];
			}
		}
		return t;
	}
		
	Matrix invertCopy() {
// 		if (!isInvertible) { cout<<"Not invertible\n"; return Matrix({{0}}); }
		float det = determinant4();
		if (!det) {
			cout << "Determinant zero: not invertible\n";
			return Matrix({{0}});
		}
		Matrix m{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				m.data[r][c] = getCofactor(r, c);
			}
		}
		m.transpose();
		return m * (1 / det);
	}
		
	void invert() {
// 		if (!isInvertible) { cout<<"Not invertible\n"; return; }
		float det = determinant4();
		if (det == 0) {
			cout << "Determinant zero: not invertible\n";
			return;
		}
		Matrix m{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				m.data[r][c] = getCofactor(r, c);
			}
		}
		m.transpose();
		Matrix prod = m * (1 / det);	// make operator *=
		data = prod.data;
	}
		
	Matrix operator*(const Matrix& b) {
		if (numCols != b.numRows) {
			cerr << "Incompatible matrix sizes for multiplication\n";
			return Matrix({{0.f}});
		}
		Matrix C{numRows, b.numCols};
		for (int r = 0; r < C.numRows; ++r) {
			for (int c = 0; c < C.numCols; ++c) {
				float sum = 0;
				for (int ac = 0; ac < numCols; ++ac) {
					sum += data[r][ac] * b.data[ac][c];
				}
				C.data[r][c] = sum;
			}
		}
		return C;
	}
	
	Matrix operator*(float k) {
		Matrix m = *this;
		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numCols; ++j) {
				m.data[i][j] *= k;
			}
		}
		return m;
	}
		
	Matrix I() {		//identity matrix
		Matrix mm(numRows, numCols);
		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numCols; ++j) {
				if (i == j)
					mm.data[i][j] = 1;
			}
		}
		return mm;
	}
	
	Matrix cramer(Matrix& b) {
		if (numRows != 3 && numRows != 2) {
			cerr << "Not 3x3 or 2x2\n";
			return Matrix({{0}});
		}
		if (b.numRows != numCols || b.numCols != 1) {
			cerr << "b must be colNum x 1\n";
			return Matrix({{0}});
		}
		if (numRows == 2)
			return cramer2(b);
		float det = determinant();
		if (det == 0) {
			cerr << "Cannot solve: determinant zero\n";
			return Matrix({{0}});
		}
		Matrix xmat {*this};
		Matrix ymat {*this};
		Matrix zmat {*this};
		for (int i = 0; i < 3; ++i) {
			xmat.data[i][0] = b.data[i][0];
			ymat.data[i][1] = b.data[i][0];
			zmat.data[i][2] = b.data[i][0];
		}
		Matrix solution{3, 1};
		solution.data[0][0] = xmat.determinant() / det;
		solution.data[1][0] = ymat.determinant() / det;
		solution.data[2][0] = zmat.determinant() / det;
	
		return solution;
	}

	Matrix cramer2(Matrix& b) {
		if (numRows != 3 && numRows != 2) {
			cerr << "Not 3x3 or 2x2\n";
			return Matrix({{0}});
		}
		if (b.numRows != numCols || b.numCols != 1) {
			cerr << "b must be colNum x 1\n";
			return Matrix({{0}});
		}
		float det = determinant();
		if (det == 0) {
			cerr << "Cannot solve: determinant zero\n";
			return Matrix({{0}});
		}
		Matrix xmat{*this};
		Matrix ymat{*this};
		for (int i = 0; i < 2; ++i) {
			xmat.data[i][0] = b.data[i][0];
			ymat.data[i][1] = b.data[i][0];
		}
		Matrix solution{2, 1};
		solution.data[0][0] = xmat.determinant() / det;
		solution.data[1][0] = ymat.determinant() / det;
		return solution;
	}
	
	Matrix crossProd(Matrix& b) {
		Matrix m(3, 1);
		m.data[0][0] = data[1][0] * b.data[2][0] - data[2][0] * b.data[1][0];
		m.data[1][0] = data[2][0] * b.data[0][0] - data[0][0] * b.data[2][0];
		m.data[2][0] = data[0][0] * b.data[1][0] - data[1][0] * b.data[0][0];
		return m;
	}
		
	float dotProd(Matrix& b) {
		return 	data[0][0] * b.data[0][0] +
				data[0][1] * b.data[1][0] +
				data[0][2] * b.data[2][0];
	}
};	//end Matrix














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

template <class Subclass, class Base>
bool isOfKind (unique_ptr<Base>& obj)
{
	return dynamic_pointer_cast<Subclass>(obj) != nullptr;
}

#define valW valWhich

template<typename Cont, typename Pred>
typename Cont::value_type*
valWhich (Cont& c, Pred p) {
	auto itr = find_if(c.begin(), c.end(), p);
	return itr != c.end() ? &(*itr) : nullptr;
}

template<typename Cont>
int indexOfRef (const Cont& cont, typename Cont::value_type& ele) {
	for (int i = 0; i < cont.size(); ++i) {
		if (&cont[i] == &ele)
            return i;
		}
	return -1;
}

template<typename Cont>
int indexOf (const Cont& cont, typename Cont::value_type ele) {
	for (int i = 0; i < cont.size(); ++i) {
		if (cont[i] == ele)
			return i;
		}
	return -1;
	
	// BETTER IMPLEMENTATION?
//	auto itr = std::find(v.begin(), v.end(), val);
//	return itr != v.end() ? distance(v.begin(), itr) : -1;
}

	
template<typename Cont, typename Pred>
int indexWhich (const Cont& cont, Pred p) {
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            return i;
		}
	return -1;
}
	
	template<typename Cont, typename Pred>
  int  
countWhich (const Cont& cont, Pred p) {
	int ct = 0;
	for (int i = 0; i < cont.size(); ++i) {
		if (p(cont[i]))
            ++ct;
		}
	return ct;
}
	
template<class T, class P> vector<T>
subset (const vector<T>& v, P p) {
	vector<T> sub {};
	copy_if(v.begin(), v.end(), back_inserter(sub), p);
	return sub;
}

template<class T, class P> vector<T>
subsetRef (const vector<T>& v, P p) {
	vector<T&> sub {};
	for (size_t i = 0; i < sub.size(); i++) {
		if (p(v[i]))
			sub.push_back(std::ref(v[i]));
	}
	return sub;
}

template<typename Cont, typename Pred> Cont
subsetOld (const Cont& cont, Pred p) {
	Cont sub {};
	int sz = int(cont.size());
	for (int i = 0; i < sz; i++) {
		if (p(cont[i]))
			sub.push_back(cont[i]);
	}
	return sub;
}

template<class T> vector<T>
vecMinusVec (const vector<T>& v, const vector<T>& v2) {
	vector<T> ret;
	copy_if(v.begin(), v.end(), back_inserter(ret),
		[&](auto x) {
		return find(v2.begin(), v2.end(), x) == v2.end();
	});
	return ret;
}

	template<typename Cont>
  Cont  
vecMinusVecOld (Cont& cont, const Cont& cont2) {
	for (auto e:cont2) {
		auto itr = std::find(cont.begin(), cont.end(), e);
		if (itr != cont.end())
            cont.erase(itr);
	}
	return cont;
}


template<class T> vector<T>
vecPlusVec(const vector<T>& lhs, const vector<T>& rhs) {
	vector<T> ret {};
	ret.reserve(lhs.size() + rhs.size());
	ret.insert(ret.end(), lhs.begin(), lhs.end());
	ret.insert(ret.end(), rhs.begin(), rhs.end());
	return ret;
}

template<class T> vector<T>&
vecPlusEqVec(vector<T>& lhs, const vector<T>& rhs) {
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}

	/* Modifies original vector */
template<class T> vector<T>&
appendUnique(vector<T>& lhs, const vector<T>& rhs) {
	for (auto& ele : rhs)
		if (find(lhs.begin(), lhs.end(), ele) == lhs.end())
			lhs.push_back(ele);
}

template<class C, class P> void
forEachAssoc(C& c, P p) {
	int i = 0;
	for (auto& ele : c) {
		p(i++, ele);
	}
}
	/* Returns copy */
template<class T> vector<T>
getUnique(const vector<T>& c) {
	vector<T> culled {};
	culled.reserve(c.size());
	for (auto& ele : c)
		if (find(culled.begin(), culled.end(), ele) == culled.end())
			culled.push_back(ele);
	return culled;
}
// NOTE: for large vectors, more efficient if implementation uses an unordered set,
// and checks to see if the new insertion was successful. Faster than std::find

template<class T> int
indexOfMax(const vector<T>& c) {
	if (c.empty())
		return -1; // ?
	return distance(c.begin(), max_element(c.begin(), c.end()));
}

	/* Returns elements in the order they appear in the lefthand vector.
	 * Only matches pairs of duplicate elements, so intersect {1,2,1,3,1},
	 * {3,1,1,3,4} will return {1,1,3} */
template<class T> vector<T>
intersect(const vector<T>& lhs, const vector<T>& rhs) {
	vector<T> ret {};
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
// Make unique val version

template<class T>
string join(const vector<T>& v, string sep = "") {
	stringstream ss;
	for (size_t i = 0; i < v.size(); ++i) {
		ss << v[i];
		if (sep != "" && i < v.size() - 1)
			ss << sep;
	}
	return ss.str();
}

template<class T> int
lastIndexOf(const vector<T>& v, T val) {
	auto ritr = find(v.rbegin(), v.rend(), val);
	return (ritr != v.rend() ? distance(ritr, v.rend()) - 1 : -1);
}

	/* Modifies original. Does nothing if no deleteCt */
//template<class T> vector<T>&
//splice(vector<T>& v, int startIdx, int deleteCt, const vector<T>& newElems) {
//	//MORE ERROR HANDLING, NEGATIVE INDICES
//	if (deleteCt && startIdx + deleteCt <= v.size()) {
//		auto itr = v.erase(v.begin() + startIdx, v.begin() + startIdx + deleteCt);
//		v.insert(itr, newElems.begin(), newElems.end());
//	}
//	return v;
//}

	/* Initializer list version */
//template<class T> vector<T>&
//splice(vector<T>& v, int startIdx, int deleteCt, std::initializer_list<T> newElems) {
//	//MORE ERROR HANDLING, NEGATIVE INDICES
//	if (deleteCt && startIdx + deleteCt <= v.size()) {
//		auto itr = v.erase(v.begin() + startIdx, v.begin() + startIdx + deleteCt);
//		v.insert(itr, newElems.begin(), newElems.end());
//	}
//	return v;
//}

template<class T> vector<T>
sublist(const vector<T>& v, int startIdx, int numToIncl = 0) {
	//HANDLE BAD INDICES;CLAMP
	vector<T> sub;
	if (v.empty())
		return sub;
	if (startIdx < 0)
		startIdx = v.size() + startIdx;
	auto endItr = v.end();  // if numToIncl==0
	if (numToIncl > 0)
		endItr = v.begin() + startIdx + numToIncl;
	else if (numToIncl < 0)
		endItr = v.end() + numToIncl; // not minus
	sub.reserve(distance(v.begin() + startIdx, endItr));
	copy(v.begin() + startIdx, endItr, back_inserter(sub));
	return sub;
}


//string& toLower(string& str) {
//	transform(str.begin(), str.end(), str.begin(),
//			  [&](char c){ return tolower(c); });
//	return str;
//}

//CREATE zstring CLASS TO INCLUDE ALL TADSLIKE METHODS?
//bool endsWith(string& str, string endStr, bool ignoreCase = false) {
//	if (ignoreCase) {
//		toLower(str);
//		toLower(endStr);
//	}
//	return endStr == str.substr(str.size() - endStr.size());
//}
//
//bool startsWith(string& str, string startStr, bool ignoreCase = false) {
//	if (ignoreCase) {
//		toLower(str);
//		toLower(startStr);
//	}
//	return startStr == str.substr(0, startStr.size());
//}

//vector<string> split(string& str, string delim) {
//	vector<string> ret;
//	int i = 0;
//	while (i < str.size()) {
//		int idx = (int)str.find(delim);
//		if (idx == str.npos) {
//			ret.push_back(str.substr(i));
//			break;
//		}
//		ret.push_back(str.substr(i,idx - i));
//		str.replace(idx, delim.size(), "");
//		i = idx;
//	}
//	return ret;
//}
//
//vector<string> split(string& str, char delim) {
//	string delimStr(1, delim);
//	return split(str, delimStr);
//}
//
//vector<string> split(string& str, int chunkSize) {
//	vector<string> ret;
//	int i = 0;
//	for ( ; i < str.size() - chunkSize; i += chunkSize) {
//		ret.push_back(str.substr(i, chunkSize));
//	}
//		/* Could be shorter than chunkSize at end */
//	if (i < str.size())
//		ret.push_back(str.substr(i));
//	return ret;
//}
// TADS implements a final optional arg for max # of substrings

//string& splice(string& str, int startIdx, int deleteCt, string insertStr) {
//	//MORE ERROR HANDLING
//	if (startIdx < 0)
//		startIdx = max(0, (int)str.length() + startIdx);
//	if (deleteCt && startIdx + deleteCt <= str.size()) {
//		auto itr = str.erase(str.begin() + startIdx, str.begin() + startIdx + deleteCt);
//		str.insert(itr, insertStr.begin(), insertStr.end());
//	}
//	return str;
//}
//
//bool match(string& str, string strToFind, int startIdx) {
//	if (startIdx < 0)
//		startIdx = max(0, (int)str.length() + startIdx);
//	return strToFind == str.substr(startIdx, strToFind.length());
//}
//
//string& findReplaceAll(string& str, string oldStr, string newStr, int startIdx = 0) {
//	if (startIdx < 0)
//		startIdx = max(0, (int)str.length() + startIdx);
//	while ((startIdx = (int)str.find(oldStr, startIdx)) != string::npos) {
//		str.replace(startIdx, oldStr.size(), newStr);
//		startIdx += newStr.size();
//	}
//	return str;
//}

template<class M> vector<typename M::key_type>
keysToVec(M& m) {
	vector<typename M::key_type> keys;
	for (auto& kv : m)
		keys.push_back(kv.first);
	return keys;
}

template<class M> vector<typename M::mapped_type>
valsToVec(M& m) {
	vector<typename M::mapped_type> vals;
	for (auto& kv : m)
		vals.push_back(kv.second);
	return vals;
}

template<class S> vector<typename S::value_type>
setToVec(S& s) {
	return {s.begin(), s.end()};
}


  // this was probably spawned from thinking of TADS object references,
  // but probably has no meaning in c++: why pass the T reference and
  // have it returned?
template<typename Cont>
typename Cont::value_type
vecPopVal (Cont& c, typename Cont::value_type ele) {
auto it = std::find(c.begin(), c.end(), ele);
// if ele isn't found?
auto ret = *it;
c.erase(it);
return ret;
}

		template<typename Cont>
	Cont&
eraseElem (Cont& c, typename Cont::value_type ele)
{
	auto itr = std::find(c.begin(), c.end(), ele);
	if (itr != c.end())
		c.erase(itr);
	return c;
}

		template<typename Cont>
	Cont&
eraseIndex (Cont& c, size_t index)
{
	if (index < c.size())
		c.erase(c.begin() + index);
	return c;
}

	template<typename Cont>
  typename Cont::value_type
vecPopRand (Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr << "Container size 0";
	int idx = randRange(1, sz);
	auto ret = cont[idx-1];
	cont.erase(cont.begin() + idx - 1);
	return ret;
}

	template<typename Cont>
  typename Cont::value_type*
randElemPtr (const Cont& cont) {
	int sz = int(cont.size());
	if (sz<1)
        cerr<<"Container size 0";
	int idx = randRange(1, sz);
	return &cont[idx];
}

	template<typename Cont>
  typename Cont::value_type&
randElemRef (const Cont& cont) {
	int sz = int(cont.size());
	if (sz < 1)
        cerr << "Container size 0";
	int idx = randRange(1, sz);
	return cont[idx];
}

	template<typename Cont>
  typename Cont::value_type
randElemVal (const Cont& cont) {
	int sz = int(cont.size());
	if (sz < 1)
        cerr<<"Container size 0";
	int idx = randRange(1, sz);
	return cont[idx - 1];
}

// DEPRECATED: LEAVING IN FOR OLDER GAMES
    template<typename Cont>
  typename Cont::value_type
popOut (Cont& c, typename Cont::value_type ele) {
    auto ret = *std::find(c.begin(), c.end(), ele);
    std::remove_copy_if(c.begin(), c.end(), c.begin(), [&](auto& x) { return x == ret; } );
    c.pop_back();
    return ret;
}

    template<typename Cont, typename Pred>
 typename Cont::value_type*
findFirstWhich (Cont& c, Cont& d, Pred p) {
    return &(*(find_first_of(c.begin(), c.end(), d.begin(), d.end(), p)));
}



/*
 IMPLEMENT AND TEST  (code gotten from perplexity)
 More efficient data structure for constant appending and removal of elements

template <typename K, typename V>
class VectorMap {
private:
	std::vector<std::pair<K, V>> data;
	std::unordered_map<K, size_t> index_map;

public:
	void insert(const K& key, const V& value) {
		if (index_map.find(key) == index_map.end()) {
			data.push_back({key, value});
			index_map[key] = data.size() - 1;
		} else {
			size_t index = index_map[key];
			data[index].second = value;
		}
	}

	void remove(const K& key) {
		auto it = index_map.find(key);
		if (it != index_map.end()) {
			size_t index = it->second;
			size_t last_index = data.size() - 1;
			
			if (index != last_index) {
				std::swap(data[index], data[last_index]);
				index_map[data[index].first] = index;
			}
			
			data.pop_back();
			index_map.erase(it);
		}
	}

	V& operator[](const K& key) {
		auto it = index_map.find(key);
		if (it == index_map.end()) {
			insert(key, V());
			return data.back().second;
		}
		return data[it->second].second;
	}

	// Other methods like size(), clear(), etc.
};
*/

#endif /* jwz_hpp */
