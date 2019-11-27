#include <set>
#include <iostream>
#include <queue>
#include <math.h>
#include <utility>
#include <stdlib.h>
#include <vector>

#define BOARD_SIZE 25

using namespace std;

typedef set <pair <pair <int, int>, pair <int, int> > > Constraints;
typedef vector < vector <vector <int> > > Domains;
typedef vector <pair <pair<int, int>, int> > Assignments;

bool is_consistent(const pair <int, int> &var, const int &domain_val, const Assignments &assigned, const Constraints &C);

vector <pair <int, int>> get_neighbors(const pair <int, int> &var, const set <pair<int, int> > &unassigned);

pair <int, int> select_unassigned_var(set <pair<int, int> > &unassigned, const Domains &Y);

bool revise (const pair <int, int> &xi, const pair <int, int> &xj, Domains &Y);

bool AC3(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y);

bool forward_checking(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y, const Constraints &C, const int &domain_val);

int number_of_eliminations(set <pair<int, int> > unassigned, pair <int, int> var, Domains Y, int domain_val);

vector <int> order_domain_vals (pair <int, int> var, vector <int> domain, set <pair<int, int> > unassigned, Domains Y);

bool backtrack(Assignments &assigned, set <pair<int, int> > unassigned, Domains Y, const Constraints &C);

bool run(int board[BOARD_SIZE][BOARD_SIZE]);
