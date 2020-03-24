#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Navigation.h"
#include "MoveMap.h"
#include "PathFinder.h"
#include "Game.h"
#include "Offsets.h"

using namespace std::experimental::filesystem::v1;
using namespace std;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace Agony
{
    namespace Native
    {
        Navigation* Navigation::s_singletonInstance = NULL;

        Navigation* Navigation::GetInstance()
        {
            if (s_singletonInstance == NULL)
                s_singletonInstance = new Navigation();
            return s_singletonInstance;
        }

        void Navigation::Initialize(unsigned int desiredMapId)
        {
            dtAllocSetCustom(dtCustomAlloc, dtCustomFree);

            MMAP::MMapManager* manager = MMAP::MMapFactory::createOrGetMMapManager();

            for (auto& p : std::filesystem::directory_iterator(Navigation::GetMmapsPath()))
            {
                string path = p.path().string();
                string extension = path.substr(path.find_last_of(".") + 1);
                if (extension == "mmtile")
                {
                    string filename = path.substr(path.find_last_of("\\") + 1);

                    int xTens = filename[4] - '0';
                    int xOnes = filename[5] - '0';
                    int yTens = filename[6] - '0';
                    int yOnes = filename[7] - '0';

                    int x = (xTens * 10) + xOnes;
                    int y = (yTens * 10) + yOnes;

                    string subfile = filename.substr(0, 4);
                    int mapID = stoi(subfile);

                    if (mapID == desiredMapId)
                    {
                        manager->loadMap(mapID, x, y);
                    }

                    /*if (filename[0] == '0' && filename[1] == '0' && filename[2] == '0')
                        manager->loadMap(0, x, y);
                    else if (filename[0] == '0' && filename[1] == '0' && filename[2] == '1')
                        manager->loadMap(1, x, y);
                        */
                }
            }
        }

        void Navigation::Release()
        {
            MMAP::MMapFactory::createOrGetMMapManager()->~MMapManager();
        }

        void Navigation::ClickToMove(Vector3* location)
        {
            if (Game::IsInGame())
            {
                WoWObject* player = Agony::Native::Game::Me();
                reinterpret_cast<void(__fastcall*)(WoWObject*, Vector3*)>(Offsets::Base + Offsets::TerrainClick)(player, location);
            }
        }

        void Navigation::FreePathArr(Vector3* pathArr)
        {
            delete[] pathArr;
        }

        Vector3* Navigation::CalculatePath(unsigned int mapId, Vector3 start, Vector3 end, bool straightPath, int* length, bool allowSwimming)
        {
            PathFinder pathFinder(mapId, 1, allowSwimming);
            pathFinder.setUseStrightPath(!straightPath);
            pathFinder.calculate(start.x, start.y, start.z, end.x, end.y, end.z);

            PointsArray pointPath = pathFinder.getPath();
            *length = pointPath.size();
            Vector3* pathArr = new Vector3[pointPath.size()];

            for (unsigned int i = 0; i < pointPath.size(); i++)
            {
                pathArr[i].x = pointPath[i].x;
                pathArr[i].y = pointPath[i].y;
                pathArr[i].z = pointPath[i].z;
            }

            return pathArr;
        }

        string Navigation::GetMmapsPath()
        {
            WCHAR DllPath[MAX_PATH] = { 0 };
            GetModuleFileNameW((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
            wstring ws(DllPath);
            string pathAndFile(ws.begin(), ws.end());
            char* c = const_cast<char*>(pathAndFile.c_str());
            int strLength = strlen(c);
            int lastOccur = 0;
            for (int i = 0; i < strLength; i++)
            {
                if (c[i] == '\\') lastOccur = i;
            }
            string pathToMmap = pathAndFile.substr(0, lastOccur + 1);
            pathToMmap = pathToMmap.append("mmaps\\");

            return pathToMmap;
        }
    }
}
