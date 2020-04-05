// TestOffmesh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    const char* offMeshFilePath = "D:\\AgonyWoW\\OffmeshConnections.txt";
    FILE* fp = fopen(offMeshFilePath, "rb");
    if (!fp)
    {
        printf(" loadOffMeshConnections:: input file %s not found!\n", offMeshFilePath);
        return 0;
    }
    char* buf = new char[512];
    while (fgets(buf, 512, fp))
    {
        float p0[3], p1[3];
        uint32_t mid, tx, ty, bidirectional;
        float size;
        if (sscanf(buf, "%u %u,%u (%f %f %f) (%f %f %f) %f %u", &mid, &tx, &ty,
            &p0[0], &p0[1], &p0[2], &p1[0], &p1[1], &p1[2], &size, &bidirectional) != 11)
            continue;
        std::cout << "MapID: " << mid << " X: " << tx << " Y: " << ty << std::endl;
        std::cout << "Point 0: " << p0[1] << ", " << p0[2] << ", " << p0[0] << std::endl;
        std::cout << "Point 1: " << p1[1] << ", " << p1[2] << ", " << p1[0] << std::endl;
        std::cout << "Size: " << size << std::endl;
        std::cout << "Bi-Directional: " << bidirectional << std::endl;
    }
    delete[] buf;
    fclose(fp);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
