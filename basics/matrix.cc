#include <iostream>
#include <limits>
#include <vector>

int main()
{
    std::vector<std::vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            std::cin >> arr[i][j];
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int max = -9 * 7;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i < 4 && j < 4) {
                int sum = arr[i][j] + arr[i][j + 1] + arr[i][j + 2] +
                      arr[i + 1][j + 1] +
                      arr[i + 2][j] + arr[i + 2][j + 1] + arr[i + 2][j + 2];
                if (max < sum) max = sum;
            }
        }
    }
    std::cout << max;

    return 0;
}
