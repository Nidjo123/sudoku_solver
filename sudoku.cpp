#include <iostream>
#include <array>
#include <vector>
#include <queue>
 
class Sudoku {
  private:
    std::array<std::array<int, 9>, 9> grid;
    std::array<std::array<bool, 9>, 9> empty_cells;
    std::array<std::array<std::queue<int>, 9>, 9> possibles; //possible numbers
    std::queue<std::pair<int, int>> empty_coords;
    std::pair<int, int> leastPos;
    int empty_cell_num;
 
    bool resetAndCheckArray(std::array<bool, 9>& a) {
      for (int i = 0; i < 9; i++) {
        if (!a[i])
          return false;
      }
 
      a.fill(false);
 
      return true;
    }
 
  public:
    Sudoku(std::array<std::array<int, 9>, 9>& _grid) : grid(_grid), empty_cell_num(0) {
      //setup empty_cells
      for (int i = 0; i < 9; i++) {
        empty_cells[i].fill(false);
 
        for (int j = 0; j < 9; j++)
          if (grid[i][j] == 0)
            empty_cells[i][j] = true;
      }
 
      int pos = 9;
 
      //setup queues
      for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
          if (empty_cells[i][j]) {
            std::array<bool, 9> taken;
            taken.fill(false);
 
            empty_cell_num++;
 
            for (int jj = 0; jj < 9; jj++) {
              if (!empty_cells[i][jj]) //row
                taken[grid[i][jj] - 1] = true;
 
              if (!empty_cells[jj][j]) //column
                taken[grid[jj][j] - 1] = true;
            }
 
            //square
            int si = i / 3 * 3;
            int sj = j / 3 * 3;
 
            for (int ii = si; ii < si + 3; ii++)
              for (int jj = sj; jj < sj + 3; jj++)
                if (!empty_cells[ii][jj])
                  taken[grid[ii][jj] - 1] = true;
 
            for (int ii = 0; ii < 9; ii++)
              if (!taken[ii])
                possibles[i][j].push(ii + 1);
 
            //set starting position
            if (possibles[i][j].size() < pos) {
              pos = possibles[i][j].size();
              leastPos = std::make_pair(i, j);
            }
          }
        }
    }
 
    bool isValid() {
      std::array<bool, 9> taken;
      taken.fill(false);
 
      for (int i = 0; i < 9; i++) {
        //row
        for (int j = 0; j < 9; j++) {
          taken[grid[i][j] - 1] = true;
        }
 
        if (!resetAndCheckArray(taken))
          return false;
 
        //column
        for (int j = 0; j < 9; j++) {
          taken[grid[j][i] - 1] = true;
        }
 
        if (!resetAndCheckArray(taken))
          return false;
      }
 
      //sqares
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
          for (int ii = i * 3; ii < i * 3 + 3; ii++)
            for (int jj = j * 3; jj < j * 3 + 3; jj++) {
              taken[grid[ii][jj] - 1] = true;
            }
 
          if (!resetAndCheckArray(taken))
            return false;
        }
 
      return true;
    }
 
    bool solve() {
      if (empty_cell_num == 0) {
        if (isValid())
          return true;
 
        return false;
      }
 
      auto coord = leastPos;
 
      if (possibles[coord.first][coord.second].empty())
        return false;
 
 
      while (!possibles[coord.first][coord.second].empty()) {
        int n = possibles[coord.first][coord.second].front();
        possibles[coord.first][coord.second].pop();
        grid[coord.first][coord.second] = n;
 
        Sudoku sudoku(grid);
 
        if (sudoku.solve()) {
          grid = sudoku.grid;
          return true;
        }
      }
 
      return false;
    }
 
    void print() {
      std::cout << std::endl;
 
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          std::cout << grid[i][j] << " ";
 
          if ((j + 1) % 3 == 0 && j < 8) std::cout << "| ";
        }
 
        if ((i + 1) % 3 == 0 && i < 8)
          std::cout << std::endl << "- - - + - - - + - - -";
 
        std::cout << std::endl;
      }
 
      std::cout << std::endl;
    }
};
