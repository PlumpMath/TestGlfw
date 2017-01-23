#include "LoadSpeedTest.h"
#include "PerformanceTimer.h"
#include <vector>
#include "AssetManager.h"

static const std::string PATH_TO_ASSETS = "D:/gamewarrior/Assets/";
using namespace std;
std::vector<std::string> Concat(std::string str, int max, bool useDDS = true)
{
	std::vector<std::string> out;
	for (int i = 0; i < max; i++)
	{
		std::string copy(str);
		if (i < 10)
		{
			copy += "_00" + std::to_string(i);
		}
		else if (i < 100)
		{
			copy += "_0" + std::to_string(i);
		}
		else
		{
			copy += "_" + std::to_string(i);
		}

		/*if (useDDS)
		copy += ".png";
		else*/
		copy += ".png";

		out.push_back(copy);
	}
	return out;
}

void LoadTexture(const std::string& path)
{
	AssetManager::LoadTexture(path);
}

void LoadAll(std::vector<std::string> paths)
{
	static int num = 0;
	for (const auto& path : paths)
	{
		std::cout << "Loading: " << path << " (" << to_string(++num) <<")\n";
		LoadTexture(path);
	}
}

void LoadSymbolsIndividual()
{
	vector<string> list;
	string base = PATH_TO_ASSETS + "Graphics/SlotVideo/5Reel/20Line/DevilsDeux/Symbols/";

	auto concat = Concat(base + "Ace/Ace", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Cherries/Cherries", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Jack/Jack", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "King/King", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Logo/Logo", 45);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Nine/Nine", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Nine/Nine", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Queen/Queen", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Scatter/Scatter", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Seven/Seven", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "snakeDollar/snakeDollar", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Ten/Ten", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "WildBlue/WildBlue", 45);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "WildRed/WildRed", 45);
	list.insert(end(list), begin(concat), end(concat));

	list.push_back(base + "logo.png");
	list.push_back(base + "Pitchfork.png");
	list.push_back(base + "scatter.png");
	list.push_back(base + "snakeDollar.png");

	PerformanceTimer t{ "Symbols (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

void LoadAtlases()
{
	vector<string> list;
	string base = "C:/Users/Robert/Desktop/PlatformVS/TestAssets/DevilsDeux/Symbols/";

	list.push_back(base + "ace.png");
	list.push_back(base + "cherries.png");
	list.push_back(base + "jack.png");
	list.push_back(base + "king.png");
	list.push_back(base + "logo.png");
	list.push_back(base + "nine.png");
	list.push_back(base + "queen.png");
	list.push_back(base + "scatter.png");
	list.push_back(base + "seven.png");
	list.push_back(base + "snakeDollar.png");
	list.push_back(base + "ten.png");
	list.push_back(base + "wildBlue.png");
	list.push_back(base + "wildRed.png");

	PerformanceTimer t{ "Atlases (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

void LoadBackgroundAnims()
{
	vector<string> list;
	string base = PATH_TO_ASSETS + "Graphics/SlotVideo/5Reel/20Line/DevilsDeux/";

	auto concat = Concat(base + "Background/fsScreenLoopBG/fsScreenLoopBG", 45);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "Background/fsTransInBG/fsTransInBG", 45);
	list.insert(end(list), begin(concat), end(concat));

	// Ofcourse these assets dont follow the naming conventions of the REST OF THE 
	// FUCKING CODEBASE.  Expected reel_000.png -> actual reel_00.png
	/*list.push_back(base + "Background/ScatterReel/reel_00.png");
	list.push_back(base + "Background/ScatterReel/reel_01.png");
	list.push_back(base + "Background/ScatterReel/reel_02.png");
	list.push_back(base + "Background/ScatterReel/reel_03.png");
	list.push_back(base + "Background/ScatterReel/reel_04.png");
	list.push_back(base + "Background/ScatterReel/reel_05.png");*/

	concat = Concat(base + "Background/TransitionFromFreespins/fsTransOutBG", 15);
	list.insert(end(list), begin(concat), end(concat));


	concat = Concat(base + "Background/ScatterReel/ReelTrans", 6);
	list.insert(end(list), begin(concat), end(concat));

	/*list.push_back(base + "Background/Generic.png");
	list.push_back(base + "Background/mainScreen.png");*/

	list.push_back(base + "Background/Generic.png");
	list.push_back(base + "Background/mainScreen.png");

	PerformanceTimer t{ "Background animations (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

void LoadSecondaryScreen()
{
	vector<string> list;
	string base = PATH_TO_ASSETS + "Graphics/SlotVideo/5Reel/20Line/DevilsDeux/";

	auto concat = Concat(base + "SecondaryScreen/topScreenBG/topScreenBG", 30);
	list.insert(end(list), begin(concat), end(concat));

	/*list.push_back(base + "SecondaryScreen/any.png");
	list.push_back(base + "SecondaryScreen/Denom00.png");
	list.push_back(base + "SecondaryScreen/Denom01.png");
	list.push_back(base + "SecondaryScreen/Denom02.png");
	list.push_back(base + "SecondaryScreen/Denom03.png");
	list.push_back(base + "SecondaryScreen/Denom04.png");
	list.push_back(base + "SecondaryScreen/of_a_kind.png");
	list.push_back(base + "SecondaryScreen/splash.png");*/

	list.push_back(base + "SecondaryScreen/any.png");
	list.push_back(base + "SecondaryScreen/Denom00.png");
	list.push_back(base + "SecondaryScreen/Denom01.png");
	list.push_back(base + "SecondaryScreen/Denom02.png");
	list.push_back(base + "SecondaryScreen/Denom03.png");
	list.push_back(base + "SecondaryScreen/Denom04.png");
	list.push_back(base + "SecondaryScreen/of_a_kind.png");
	list.push_back(base + "SecondaryScreen/splash.png");

	PerformanceTimer t{ "Secondary animations (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

void LoadSummaryScreen()
{
	vector<string> list;
	string base = PATH_TO_ASSETS + "Graphics/SlotVideo/5Reel/20Line/DevilsDeux/";

	auto concat = Concat(base + "Summary/Summary", 25);
	list.insert(end(list), begin(concat), end(concat));

	PerformanceTimer t{ "Summary animation (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

void LoadMisc()
{
	vector<string> list;
	string base = PATH_TO_ASSETS + "Graphics/SlotVideo/5Reel/20Line/DevilsDeux/Misc/";

	auto concat = Concat(base + "boxLines/boxLine", 101);
	list.insert(end(list), begin(concat), end(concat));

	list.push_back(base + "lines/line01.png");
	list.push_back(base + "lines/line02.png");
	list.push_back(base + "lines/line03.png");
	list.push_back(base + "lines/line04.png");
	list.push_back(base + "lines/line05.png");
	list.push_back(base + "lines/line06.png");
	list.push_back(base + "lines/line07.png");
	list.push_back(base + "lines/line08.png");
	list.push_back(base + "lines/line09.png");
	list.push_back(base + "lines/line10.png");
	list.push_back(base + "lines/line11.png");
	list.push_back(base + "lines/line12.png");
	list.push_back(base + "lines/line13.png");
	list.push_back(base + "lines/line14.png");
	list.push_back(base + "lines/line15.png");
	list.push_back(base + "lines/line16.png");
	list.push_back(base + "lines/line17.png");
	list.push_back(base + "lines/line18.png");
	list.push_back(base + "lines/line19.png");
	list.push_back(base + "lines/line20.png");
	list.push_back(base + "lines/line21.png");
	list.push_back(base + "lines/line22.png");
	list.push_back(base + "lines/line23.png");
	list.push_back(base + "lines/line24.png");
	list.push_back(base + "lines/line25.png");

	list.push_back(base + "LineTags/lineTag01.png");
	list.push_back(base + "LineTags/lineTag02.png");
	list.push_back(base + "LineTags/lineTag03.png");
	list.push_back(base + "LineTags/lineTag04.png");
	list.push_back(base + "LineTags/lineTag05.png");
	list.push_back(base + "LineTags/lineTag06.png");
	list.push_back(base + "LineTags/lineTag07.png");
	list.push_back(base + "LineTags/lineTag08.png");
	list.push_back(base + "LineTags/lineTag09.png");
	list.push_back(base + "LineTags/lineTag10.png");
	list.push_back(base + "LineTags/lineTag11.png");
	list.push_back(base + "LineTags/lineTag12.png");
	list.push_back(base + "LineTags/lineTag13.png");
	list.push_back(base + "LineTags/lineTag14.png");
	list.push_back(base + "LineTags/lineTag15.png");
	list.push_back(base + "LineTags/lineTag16.png");
	list.push_back(base + "LineTags/lineTag17.png");
	list.push_back(base + "LineTags/lineTag18.png");
	list.push_back(base + "LineTags/lineTag19.png");
	list.push_back(base + "LineTags/lineTag20.png");
	list.push_back(base + "LineTags/lineTag21.png");
	list.push_back(base + "LineTags/lineTag22.png");
	list.push_back(base + "LineTags/lineTag23.png");
	list.push_back(base + "LineTags/lineTag24.png");
	list.push_back(base + "LineTags/lineTag25.png");

	concat = Concat(base + "msgDiabolical/msgDiabolical", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "msgFreespins/msgFreespins", 30);
	list.insert(end(list), begin(concat), end(concat));

	concat = Concat(base + "msgWicked/msgWicked", 30);
	list.insert(end(list), begin(concat), end(concat));

	PerformanceTimer t{ "Misc images (count: " + to_string(list.size()) + ")" };
	LoadAll(list);
	t.Expire();
}

LoadSpeedTest::~LoadSpeedTest()
{
}

void LoadSpeedTest::Init()
{
	PerformanceTimer t{ "Everything " };
	//LoadSymbolsIndividual();
	//LoadAtlases();

	//LoadBackgroundAnims();
	LoadSecondaryScreen();
	LoadSummaryScreen();
	LoadMisc();

	t.Expire();
}

void LoadSpeedTest::ProcessInput(float delta, double mouse_x, double mouse_y)
{
}

void LoadSpeedTest::Update(float delta)
{
}

void LoadSpeedTest::Render()
{

}
