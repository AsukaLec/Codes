# <center> HW-1-陈新安-郑骏远-卜思翔 </center>

## 问题一
### 1.第一小问
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="Q1_1.png " width="200"/>
  </div>
</div>

### 2.第二小问
求解代码：

```matlab
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
```

求解结果：

**最少需要三种颜色**

---

## 问题二
