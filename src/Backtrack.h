#ifndef BACKTRACK_H
#define BACKTRACK_H

#define BOARD_SIZE 9

#include <set>
#include <iostream>
#include <queue>
#include <math.h>
#include <utility>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

class Backtrack
{
  public:
    static int backtracks;
    typedef set <pair <pair <int, int>, pair <int, int> > > Constraints;
    typedef vector < vector <vector <int> > > Domains;
    typedef vector <pair <pair<int, int>, int> > Assignments;
    
    struct Comparator {
      set <pair<int, int> > unassigned;
      Domains Y;
      pair <int, int> var;
      Comparator(pair <int, int> var, set <pair<int, int> > unassigned, Domains Y);
      bool operator() (int p1, int p2);
    };

    static bool is_consistent(const pair <int, int> &var, const int &domain_val, const Assignments &assigned, const Constraints &C);

    static vector <pair <int, int>> get_neighbors(const pair <int, int> &var, const set <pair<int, int> > &unassigned);

    static pair <int, int> select_unassigned_var(set <pair<int, int> > &unassigned, const Domains &Y);

    static bool revise (const pair <int, int> &xi, const pair <int, int> &xj, Domains &Y);

    static bool AC3(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y);

    static bool forward_checking(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y, const Constraints &C, const int &domain_val);

    static int number_of_eliminations(set <pair<int, int> > unassigned, pair <int, int> var, Domains Y, int domain_val);

    static vector <int> order_domain_vals (pair <int, int> var, vector <int> domain, set <pair<int, int> > unassigned, Domains Y);

    static bool backtrack(Assignments &assigned, set <pair<int, int> > unassigned, Domains Y, const Constraints &C);

    static bool run(int board[BOARD_SIZE][BOARD_SIZE]);
};
#endif