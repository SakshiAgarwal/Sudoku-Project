#include "Backtrack.h"

int Backtrack::backtracks = 0; // number of backtracks

bool Backtrack::is_consistent(const pair <int, int> &var, const int &domain_val, const Assignments &assigned, const Constraints &C)
{
    for (int j = 0; j < assigned.size(); j++) {
        if (assigned[j].second == domain_val) {
            pair <int, int> p1, p2;
            if (var.first*10 + var.second < 10*assigned[j].first.first + assigned[j].first.second) {
                p1 = var;
                p2 = assigned[j].first;
            }
            else {
                p1 = assigned[j].first;
                p2 = var;
            }
            
            if (C.find(make_pair(p1, p2)) != C.end()) {
                return false;
            }
        }
    }
    return true;
}

vector <pair <int, int>> Backtrack::get_neighbors(const pair <int, int> &var, const set <pair<int, int> > &unassigned)
{
    vector <pair <int, int>> result;
    int number_of_boxes = sqrt(BOARD_SIZE);
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            if (make_pair(i, j) != var && (i == var.first || j == var.second || ((i/number_of_boxes == var.first/number_of_boxes) && j/number_of_boxes == var.second/number_of_boxes)) && unassigned.find(make_pair(i, j)) != unassigned.end()) {
                result.push_back(make_pair(i, j));
            }
        }
    }
    return result;
}

pair <int, int> Backtrack::select_unassigned_var(set <pair<int, int> > &unassigned, const Domains &Y)
{
    // MRV
    // degree heuristic resulted in more backtracks, so commented it out
    set <pair<int, int> >::iterator iter, current_iter;
    int current_min = INT8_MAX;
    int degree_max = INT8_MIN;
    pair <int, int> current_pair = *unassigned.begin();
    for (iter = unassigned.begin(); iter != unassigned.end(); iter++) {
        int domain_size = Y[(*iter).first][(*iter).second].size();
        //int degree = get_neighbors(*iter, unassigned).size();
        if (domain_size < current_min //|| (domain_size == current_min && degree > degree_max)
            ) {
            current_min = domain_size;
            //degree_max = degree;
            current_pair = make_pair((*iter).first, (*iter).second);
            current_iter = iter;
        }
    }
    unassigned.erase(current_iter);
    return current_pair;
}

bool Backtrack::revise (const pair <int, int> &xi, const pair <int, int> &xj, Domains &Y)
{
    bool revised = false;
    vector <int>::iterator iter = Y[xi.first][xi.second].begin();
    while(iter != Y[xi.first][xi.second].end()) {
        bool found = false;
        for (int j = 0; j < Y[xj.first][xj.second].size(); j++) {
            if (Y[xj.first][xj.second][j] != *iter) {
                found = true;
            }
        }
        if (!found) {
            Y[xi.first][xi.second].erase(iter);
            iter--;
            revised = true;
        }
        iter++;
    }
    return revised;
}

bool Backtrack::AC3(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y)
{
    queue <pair <pair <int, int>, pair<int, int>>> q;
    vector <pair <int, int> > neighbors = get_neighbors(var, unassigned);
    for (int i = 0; i<neighbors.size(); i++) {
        q.push(make_pair(neighbors[i], var));
    }
    pair <pair <int, int>, pair<int, int>> current_arc;
    while (q.size()) {
        current_arc = q.front();
        q.pop();
        if (revise(current_arc.first, current_arc.second, Y)) {
            if (Y[current_arc.first.first][current_arc.first.second].size() == 0) {
                return false;
            }
            else if (Y[current_arc.first.first][current_arc.first.second].size() == 1){
                assigned.push_back(make_pair(make_pair(current_arc.first.first, current_arc.first.second), Y[current_arc.first.first][current_arc.first.second][0]));
                set <pair<int, int> >::iterator iter = unassigned.find(current_arc.first);
                if (iter != unassigned.end()) {
                    unassigned.erase(iter);
                }
            }

            neighbors = get_neighbors(current_arc.first, unassigned);
            for (int i = 0; i<neighbors.size(); i++) {
                if (neighbors[i] != current_arc.second) {
                    q.push(make_pair(neighbors[i], current_arc.first));
                }
            }
        }
    }
    return true;
}


bool Backtrack::forward_checking(Assignments &assigned, set <pair<int, int> > &unassigned, const pair <int, int> &var, Domains &Y, const Constraints &C, const int &domain_val)
{
    vector <pair <int, int> > neighbors = get_neighbors(var, unassigned);
    for (int i = 0; i<neighbors.size(); i++) {
        for (int j = 0; j<Y[neighbors[i].first][neighbors[i].second].size(); j++) {
            if (Y[neighbors[i].first][neighbors[i].second][j] == domain_val) {
                Y[neighbors[i].first][neighbors[i].second].erase(Y[neighbors[i].first][neighbors[i].second].begin() + j);
                if (Y[neighbors[i].first][neighbors[i].second].size() == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int Backtrack::number_of_eliminations(set <pair<int, int> > unassigned, pair <int, int> var, Domains Y, int domain_val)
{
    int result=0;
    vector <pair <int, int> > neighbors = get_neighbors(var, unassigned);
    for (int i = 0; i<neighbors.size(); i++) {
        for (int j = 0; j<Y[neighbors[i].first][neighbors[i].second].size(); j++) {
            if (Y[neighbors[i].first][neighbors[i].second][j] == domain_val) {
                result+=1;
            }
        }
    }
    return result;
}

Backtrack::Comparator::Comparator(pair <int, int> var, set <pair<int, int> > unassigned, Domains Y) {
  this->var = var; 
  this->unassigned = unassigned; 
  this->Y = Y;
}

bool Backtrack::Comparator::operator() (int p1, int p2)
{
    return (Backtrack::number_of_eliminations(this->unassigned, this->var, this->Y, p1) > Backtrack::number_of_eliminations(this->unassigned, this->var, this->Y, p2));
}

vector <int> Backtrack::order_domain_vals (pair <int, int> var, vector <int> domain, set <pair<int, int> > unassigned, Domains Y)
{
    vector <int> result = domain;
    
    // least constraining value heuristic, but "most constraining" actually works better!?
    sort(result.begin(), result.end(), Comparator(var, unassigned, Y));
    //qsort(&result[0], result.size(), sizeof(int), Comparator(var, unassigned, Y).operator());

    return result;
}

bool Backtrack::backtrack(Assignments &assigned, set <pair<int, int> > unassigned, Domains Y, const Constraints &C)
{
    backtracks++;
    if (!unassigned.size()) {
        return true;
    }
    pair<int, int> var = select_unassigned_var(unassigned, Y);
    vector <int> domain = order_domain_vals(var, Y[var.first][var.second], unassigned, Y);
    for (int i = 0; i < domain.size(); i++) {
        if (is_consistent(var, domain[i], assigned, C)) {
            int old_assigned_size = assigned.size();
            assigned.push_back(make_pair(make_pair(var.first, var.second), domain[i]));
            Domains newY(Y);
            newY[var.first][var.second].clear();
            newY[var.first][var.second].push_back(domain[i]);
            set <pair<int, int> > newUnassigned(unassigned);
            if (AC3(assigned, newUnassigned, var, newY) //&& forward_checking(assigned, newUnassigned, var, newY, C, domain[i])
                ) {
                bool result = backtrack(assigned, newUnassigned, newY, C);
                if (result) {
                    return result;
                }
            }
            int difference = assigned.size()-old_assigned_size;
            for (int i = 0; i< difference; i++) {
                assigned.pop_back();
            }
        }
    }
    return false;
}

bool Backtrack::run(int board[BOARD_SIZE][BOARD_SIZE])
{
    backtracks = 0;
    // initialize domain for each index
    Domains Y(BOARD_SIZE, vector <vector <int> >(BOARD_SIZE, vector <int>()));
    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    Y[i][j].push_back(k+1);
                }
            }
            else {
                Y[i][j].push_back(board[i][j]);
            }
        }
    }
    
    // represent "not equal to" constraints as pairs of pairs: ((xi, xj), (yi, yj)) means board elements x and y cannot be the same
    // elements x and y each have i, j index as pair elements
    // populate constraints
    // first add row alldiffs, then column alldiffs, lastly box alldiffs
    Constraints C;
    // row alldiffs
    for (int i = 0; i< BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            for (int k = j+1; k < BOARD_SIZE; k++) {
                C.insert(make_pair(make_pair(i, j), make_pair(i, k)));
            }
        }
    }
    
    // column alldiffs
    for (int i = 0; i< BOARD_SIZE - 1; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = i+1; k < BOARD_SIZE; k++) {
                C.insert(make_pair(make_pair(i, j), make_pair(k, j)));
            }
        }
    }
        
    // box alldiffs
    int number_of_boxes = sqrt(BOARD_SIZE);
    for (int i = 0; i < number_of_boxes; i++) {
        for (int j = 0; j < number_of_boxes; j++) {
            for (int x = i*number_of_boxes; x < (i+1)*number_of_boxes; x++) {
                for (int y = j*number_of_boxes; y < (j+1)*number_of_boxes; y++) {
                    for (int z = i*number_of_boxes; z < (i+1)*number_of_boxes; z++) {
                        for (int w = j*number_of_boxes; w < (j+1)*number_of_boxes; w++) {
                            if (x!=z || y != w) {
                                if (C.find(make_pair(make_pair(z, w), make_pair(x, y))) == C.end()) {
                                    C.insert(make_pair(make_pair(x, y), make_pair(z, w)));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    // initialize vectors for assigned and unassigned variables
    set <pair<int, int> > unassigned;
    Assignments assigned = {};
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1) {
                unassigned.insert(make_pair(i, j));
            }
            else {
                assigned.push_back(make_pair(make_pair(i, j), board[i][j]));
            }
        }
    }
    // call recursive backtrack
    bool result = backtrack(assigned, unassigned, Y, C);
    for (int i = 0; i < assigned.size(); i++) {
        board[assigned[i].first.first][assigned[i].first.second] = assigned[i].second;
    }
    if(result)
    {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "number of backtracks: " << backtracks << endl;
    }
    else {
        cout << "fail" << endl;
    }
    return result;
}
/*
int main()
{
    // initialize board
    int board[BOARD_SIZE][BOARD_SIZE];

    for (int i = 0; i<BOARD_SIZE; i++) {
        for (int j = 0; j<BOARD_SIZE; j++) {
            board[i][j] = -1;
        }
    }

    int result = run(board);
    
    if (result) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "number of backtracks: " << backtracks << endl;
    }
    else {
        cout << "fail" << endl;
    }

}

*/