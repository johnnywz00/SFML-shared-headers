//
//  resourcemanager.hpp
//
//  Created by John Ziegler on 1/3/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#ifndef resourcemanager_hpp
#define resourcemanager_hpp

#include "jwzsfml.hpp"


class Resources
{
public:
	static void initialize (int argc, char* argv[])
	{
		if (argc > 0 && argv[0]) {
			exeDir = std::filesystem::absolute(argv[0]).parent_path();
		}
		else {
			exeDir = current_path().parent_path();
		}
		loadResources();
	}
	
	static path executingDir () {
/* This directive is for personal convenience only,
 * having to do with XCode and my local computer setup
 */
#ifdef DEBUG
		return path();
		
/* For cross-platform compiling, we need the absolute path */
#else
		return exeDir;
#endif
	}
	
	static string executingDirStr () { return Resources::executingDir().string(); }
	
	/* Returning non-const references to resources so that
	 * game projects can reuse this file with minimal adjustment
	 * and still be able to utilize methods like setRepeated(),
	 * setVolume() etc. after resource loading.
	 */
	static Texture& getTex (string key) { return txMap[key]; }
	
	static Font& getFont (string key) { return fontMap[key]; }
	
	static Sound& getSound (string key) { return soundMap[key]; }
	
private:
	static void loadResources ()
	{
		txMap.clear();
		fontMap.clear();
		soundMap.clear();
		buffers.clear();
		
		Texture tex;
		Font font;
		SoundBuffer sb;
			
		/* Set up filestream */
		path rscPath = Resources::executingDir() / "resources";
		ifstream rscData {rscPath / "resources.txt"};
		if (!rscData.is_open()) {
			cerr << "Couldn't load resources.txt \n";
			return;
		}
		string line;
		string section;
		
		/* Count sounds for buffers.reserve() */
		int soundCt = 0;
		while (getline(rscData, line)) {
			if (line.empty() || line[0] == '#')
				continue;
			if (line[0] == '@') {
				section = line.substr(1);
				continue;
			}
			if (section == "sounds")
				++soundCt;
		}
		buffers.reserve(soundCt);
		resetGetline(rscData);
		
		/* Main parsing to load resources */
		while (getline(rscData, line)) {
			if (line.empty() || line[0] == '#')
				continue;
			if (line[0] == '@') {
				section = line.substr(1);
				continue;
			}
			
			stringstream ss {line};
			string fileName;
			string key;
			ss >> fileName >> key;
			if (section == "images") {
				string filePath {(rscPath / "images" / fileName).string()};
				if (!tex.loadFromFile(filePath))
					cerr << "Couldn't load texture " << fileName << endl;
				else {
					string tok;
					while (ss >> tok) {
						if (tok == "repeat")
							tex.setRepeated(true);
						// else if any future tokens used
					}
					txMap.insert({key, tex});
				}
			}
			
			else if (section == "fonts") {
				string filePath {(rscPath / "fonts" / fileName).string()};
				if (!font.loadFromFile(filePath))
					cerr << "Couldn't load font " << fileName << endl;
				else
					fontMap.insert({key, font});
			}
			
			else if (section == "sounds") {
				string filePath {(rscPath / "sounds" / fileName).string()};
				if (!sb.loadFromFile(filePath))
					cerr << "Couldn't load sound file " << fileName << endl;
				else {
					buffers.push_back(sb);
					Sound snd {buffers.back()};
					soundMap.insert({key, snd});
				}
			}
		} // end while getline
	}
	
	static inline std::filesystem::path exeDir;
	
	static inline map<string, Texture> txMap;
	
	static inline map<string, Font> fontMap;
	
	static inline map<string, Sound> soundMap;
	
	static inline vector<SoundBuffer> buffers;
	
};

#endif /* resourcemanager_hpp */
