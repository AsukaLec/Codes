T = [5, 10, 15, 20, 25, 30, 35, 40, 50, 60]; 
b = [12, 5, 8, 6, 6, 4, 3];
c = [7, 4, 3, 9, 8, 5, 4]; 

%% 问题一
results = zeros(length(T), 8); 
for k = 1:length(T)
    T_current = T(k);
    
    prob = optimproblem('ObjectiveSense', 'minimize');
    a = optimvar('a', 7, 'Type', 'integer', 'LowerBound', 0, 'UpperBound', 1);
    
    prob.Objective = -sum(c .* a');
    prob.Constraints.c1 = sum(a(1:3)) <= 2;
    prob.Constraints.c2 = sum(a(4:5)) >= 1;
    prob.Constraints.c3 = sum(a(6:7)) <= 1;
    prob.Constraints.c4 = a(1) == a(7);
    prob.Constraints.c5 = sum(b .* a') <= T_current;
    
    options = optimoptions('intlinprog', 'Display', 'off');
    [sol, fval, flag] = solve(prob,"Options", options);
    
    if flag > 0
        results(k, 1:7) = sol.a';    
        results(k, 8) = -fval;       
    else
        results(k, :) = 0;     
    end
end

%% 折线图
T_header = T';
ResultTable = table(T_header, results(:,1), results(:,2), results(:,3), ...
    results(:,4), results(:,5), results(:,6), results(:,7), results(:,8), ...
    'VariableNames', {'T', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', '总利润'});
disp(ResultTable);

figure;
plot(T, results(:, 8), '-o', 'LineWidth', 2); 
grid on;
xlabel('投资总额'); ylabel('最大利润');
title('投资总额与利润关系');
legend('最大利润', 'Location', 'NorthWest');



%% 热力图
binary_data = results(:, 1:7);

x_labels = {'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7'};
y_labels = string(T);

figure;
h = heatmap(x_labels, y_labels, binary_data);

h.Title = '各投资总额下销售中心的建造情况';
h.XLabel = '城市 (A_i)';
h.YLabel = '总投资总额';

%% 问题二：针对 Sink Node 入度变化的灵敏度分析
