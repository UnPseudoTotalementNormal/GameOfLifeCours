#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

void Render(std::vector<int>& Grid, int SizeX, int SizeY) {
    //system("cls");
    std::cout << "--------------------------------\n";
    for (int X = 0; X < SizeX; X++) {
        for (int Y = 0; Y < SizeY; Y++) {
            const int Index = X * SizeY + Y;
            if (Grid[Index] == 1) {
                std::cout << "1";
            }
            else {
                std::cout << "0";
            }
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------------" << std::endl;
}

int GetPos(std::vector<int> grid, int x, int y, int SizeX)
{
    if (x < 0 || y < 0 || x >= SizeX || y >= SizeX) {
        return 0;
    }
    return x * SizeX + y;
}

int GetAliveNeighbors(std::vector<int> grid, int x, int y, int SizeX)
{
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int neighborX = x + i;
            int neighborY = y + j;
            if (neighborX >= 0 && neighborY >= 0 && neighborX < SizeX && neighborY < SizeX) {
                aliveNeighbors += grid[GetPos(grid, neighborX, neighborY, SizeX)];
            }
        }
    }
    return aliveNeighbors;
}

int main(int argc, char* argv[]){

    const int sizeX = 30;
    const int sizeY = 30;
    const int maxIterations = 25;
    std::vector Grid(sizeX * sizeY, 0);

    std::vector initialAliveCellsIdx = { GetPos(Grid, 1, 2, sizeX), GetPos(Grid, 2, 3, sizeX), GetPos(Grid, 3, 1, sizeX), GetPos(Grid, 3, 2, sizeX), GetPos(Grid, 3, 3, sizeX) };

    for (int index : initialAliveCellsIdx)
    {
        Grid[index] = 1;
    }
    Render(Grid, sizeX, sizeY);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000LL));

    int currentIteration = 0;
    while (currentIteration < maxIterations)
    {
        std::vector<int> cellsToKill;
        std::vector<int> cellsToRevive;
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
                int aliveNeighbors = GetAliveNeighbors(Grid, x, y, sizeX);
                int index = GetPos(Grid, x, y, sizeX);
                if (Grid[index] == 0)
                {
                    if (aliveNeighbors == 3 && Grid[index] == 0)
                    {
                        cellsToRevive.push_back(index);
                    }
                }
                else
                {
                    if (aliveNeighbors != 2 && aliveNeighbors != 3 && Grid[index] == 1)
                    {
                        cellsToKill.push_back(index);
                    }
                }
            }
        }
        for (int index : cellsToKill)
        {
            Grid[index] = 0;
        }
        for (int index : cellsToRevive)
        {
            Grid[index] = 1;
        }
        currentIteration++;
        Render(Grid, sizeX, sizeY);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000LL));
    }
    return 0;
}
