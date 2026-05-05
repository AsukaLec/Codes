clc, clear

w = [0 1 0 0 0 1 1
     1 0 1 0 0 0 1
     0 1 0 1 0 0 1
     0 0 1 0 1 1 0
     0 0 0 1 0 1 0
     1 0 0 1 1 0 1
     1 1 1 0 0 1 0];

n = size(w, 1);

[ni, nj] = find(w);
w = w + w';
deg = sum(w); K = max(deg); 
prob = optimproblem;
x = optimvar('x', n, K + 1, 'Type', 'integer', 'LowerBound', 0, 'UpperBound', 1);
y = optimvar('y'); prob.Objective = y;
prob.Constraints.con1 = sum(x, 2) == 1;
prob.Constraints.con2 = x(ni, :) + x(nj, :) <= 1;
prob.Constraints.con3 = x * [1:K+1]' <= y;
[sol, fval, flag, out] = solve(prob);
fprintf('最少需要 %d 颜色\n', fval);


