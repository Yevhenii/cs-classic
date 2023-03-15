#include <cstring>
#include <iostream>
#include <string>
#include <vector>

bool print_board = false;
int N = 0;
int num_of_solutions = 0;
std::vector<std::string> board;
std::vector<int> colums;
std::vector<int> first_diag;
std::vector<int> second_diag;


void init()
{
    board.reserve(N);
    for (auto i = 0; i < N; i++)
    {
       board.push_back(std::string(N, '.'));
    }

    colums = std::vector<int>(N, 0);
    first_diag = std::vector<int>(N * 2, 0);
    second_diag = std::vector<int>(N * 2, 0);
}


void backtrack(int row)
{
    if (row == N)
    {
        num_of_solutions++;
        if (print_board)
        {
            for (const auto& r : board)
            {
                std::cout << r << std::endl;
            }
            std::cout << std::string(N, '-');
        }
    }

    for (int col = 0; col < N; col++)
    {
        if (colums[col] || first_diag[row + col] || second_diag[row - col + N - 1])
        {
            continue;
        }
        
        colums[col] = first_diag[row + col] = second_diag[row - col + N - 1] = 1;

        backtrack(row + 1);

        colums[col] = first_diag[row + col] = second_diag[row - col + N - 1] = 0;
    }
}


void print_help(const char* executable)
{
    std::cout << "Usage : " << executable << " [NUMBER] [OPTIONAL -p]" << std::endl;
    std::cout << "Solves n queens puzzle - all positions of n queens on nxn board" << std::endl;
    std::cout << "NUMBER - number of queens and dimension of board" << std::endl;
    std::cout << "OPTIONAL -p argument can be used to output all possible configurations to standart output" << std::endl;
    std::cout << "- h --help argument prints this message" << std::endl;
}


bool read_cmd_argumens(int argc, char *argv[])
{
    if (argc == 1 || strcmp("-h", argv[1]) == 0 || strcmp("-help", argv[1]) == 0 || strcmp("--help", argv[1]) == 0)
    {
        print_help(argv[0]);
        return false;
    }

    if (argc >= 2)
    {
        N = atoi(argv[1]);
        if (N <= 1)
        {
            std::cerr << "error: " << argv[1] << " is invalid dimension for queen puzzle. Please use positive number greater then one" << std::endl;
            print_help(argv[0]);
            return false;
        }

        if (argc == 3)
        {
            if (strcmp("-p", argv[2]) == 0)
            {
                print_board = true;
            }
            else
            {
                std::cerr << "error: unknown argument " << argv[2] << std::endl;
                print_help(argv[0]);
                return false;
            }
        }
    }

    return true;
}


int main(int argc, char *argv[])
{
    if (!read_cmd_argumens(argc, argv))
    {
        return EXIT_FAILURE;
    }

    backtrack(0);

    std::cout << "solutions: " << num_of_solutions << std::endl;

    return 0;
}