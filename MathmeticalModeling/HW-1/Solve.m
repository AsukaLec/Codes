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
    
    options = optimoptions('intlinprog', 'Display', 'off'); %关日志
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



%% 问题二
P_vector = [1, 1, 0, 1, 1, 0, 1]; 
x_labels = {'A1', 'A2', 'A3(S)', 'A4', 'A5', 'A6(S)', 'A7'};

N = length(P_vector);
d = 0.85;                        
selected_idx = find(P_vector == 1); 
k = length(selected_idx);           
num_sim = 1000;                      % 每个阶段随机模拟次数

% 存储平均 Rank 值
mean_ranks = zeros(k + 1, N); 

figure('Color', 'w', 'Name', 'Random Connectivity Snapshot', 'Position', [100, 100, 1200, 700]);

%% 求解
for stage = 0:k
    temp_ranks = zeros(num_sim, N); 
    
    for sim = 1:num_sim
        A = zeros(N, N); 
        
        idx_for_A3 = selected_idx(randperm(k, stage));
        idx_for_A6 = selected_idx(randperm(k, stage)); %独立随机选 stage 个活跃城市作为入度来源
        
        % 转移矩阵
        for j = 1:N
            if P_vector(j) == 1
                targets = setdiff(selected_idx, j);
                if ismember(j, idx_for_A3), targets = [targets, 3]; end
                if ismember(j, idx_for_A6), targets = [targets, 6]; end 
                
                targets = unique(targets);
                if ~isempty(targets)
                    A(targets, j) = 1 / length(targets);
                end
            else
                A(:, j) = 0; 
            end
        end

        % PageRank
        R = c'; 
        for iter = 1:1000
            R_new = d * A * R + ((1 - d) / N) * sum(c) * ones(N, 1);
            if norm(R_new - R, 1) < 1e-6, break; end
            R = R_new;
        end
        temp_ranks(sim, :) = R';
        
        % 拓补图
        if sim == 1
            subplot(2, 3, stage + 1);
            G = digraph(A', x_labels);
            
            colors_map = repmat([0.2 0.4 0.6], N, 1); 
            colors_map(3, :) = [0.8 0.2 0.2];        
            colors_map(6, :) = [0.2 0.7 0.2];        
            
            p = plot(G, 'Layout', 'circle', 'NodeColor', colors_map, 'MarkerSize', 8);
            
            [Edges_Start, Edges_End] = findedge(G);
            p.EdgeColor = [0.7 0.7 0.7]; 
            p.LineStyle = '--'; 
            to_sink_edges = find(Edges_End == 3 | Edges_End == 6);
            
            highlight(p, 'Edges', to_sink_edges, 'EdgeColor', [0 0 0], ...
                      'LineWidth', 1.5, 'LineStyle', '-');
            
            title(['Sink-node入度=', num2str(stage)]);
            axis off;
        end
    end
    
    % 计算当前阶段的平均值
    mean_ranks(stage + 1, :) = mean(temp_ranks);
end

%% 折线图
figure('Color', 'w', 'Name', 'Monte Carlo PageRank Analysis');
hold on;
colors = lines(N);
for i = 1:N
    plot(0:k, mean_ranks(:, i), '-o', 'Color', colors(i,:), 'LineWidth', 2, 'DisplayName', x_labels{i});
end
grid on;
xlabel('Sink-node入度');
ylabel('期望 Rank 值');
title('各城市地位的期望演变');
legend('Location', 'northeastoutside');

%% 具体数值
RowNames = strcat(string(0:k));
ResultTableAll = array2table(mean_ranks, 'VariableNames', x_labels, 'RowNames', RowNames);
disp(ResultTableAll);
