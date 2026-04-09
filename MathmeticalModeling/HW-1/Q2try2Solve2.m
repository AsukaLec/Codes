%% --- 1. 基础数据 ---
P_vector = [1, 1, 0, 1, 1, 0, 1]; 
c_orig   = [7, 4, 3, 9, 8, 5, 4]; 
x_labels = {'A1', 'A2', 'A3(S)', 'A4', 'A5', 'A6(S)', 'A7'};

N = length(P_vector);
d = 0.85;                        
selected_idx = find(P_vector == 1); 
k = length(selected_idx);           % 5个可选城市
num_sim = 1000;                      % 每个阶段随机模拟次数

% 存储平均 Rank 值
mean_ranks = zeros(k + 1, N); 

figure('Color', 'w', 'Name', 'Random Connectivity Snapshot', 'Position', [100, 100, 1200, 700]);

%% --- 2. 核心演化循环 ---
for stage = 0:k
    temp_ranks = zeros(num_sim, N); % 存储当前阶段多次实验的结果
    
    for sim = 1:num_sim
        A = zeros(N, N); 
        
        % --- 随机生成逻辑 ---
        % A3 随机选 stage 个活跃城市作为入度来源
        idx_for_A3 = selected_idx(randperm(k, stage));
        % A6 独立随机选 stage 个活跃城市作为入度来源
        idx_for_A6 = selected_idx(randperm(k, stage));
        
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
                A(:, j) = 0; % Sink 依然无出度
            end
        end

        % --- PageRank 迭代 ---
        R = c_orig'; 
        for iter = 1:1000
            R_new = d * A * R + ((1 - d) / N) * sum(c_orig) * ones(N, 1);
            if norm(R_new - R, 1) < 1e-6, break; end
            R = R_new;
        end
        temp_ranks(sim, :) = R';
        
        % 仅在第一次模拟时画出拓扑图快照

% 仅在第一次模拟时画出拓扑图快照
        if sim == 1
            subplot(2, 3, stage + 1);
            G = digraph(A', x_labels);
            
            % 1. 准备节点颜色矩阵
            colors_map = repmat([0.2 0.4 0.6], N, 1); % 默认蓝色 (选中城市)
            colors_map(3, :) = [0.8 0.2 0.2];         % A3 红色
            colors_map(6, :) = [0.2 0.7 0.2];         % A6 绿色
            
            % 2. 绘制基础图形
            p = plot(G, 'Layout', 'circle', 'NodeColor', colors_map, 'MarkerSize', 8);
            
            % --- 3. 关键修改：区分边的颜色 ---
            % 获取图中所有边的起点和终点
            [Edges_Start, Edges_End] = findedge(G);
            
            % 初始化所有边的颜色为浅灰色 (代表城市间的内循环)
            p.EdgeColor = [0.7 0.7 0.7]; 
            p.LineStyle = '--'; % 内循环用虚线表示，更显层次
            
            % 找到指向 A3 或 A6 的边的索引
            % 注意：G.Nodes 中的索引或直接用数字 3 和 6
            to_sink_edges = find(Edges_End == 3 | Edges_End == 6);
            
            % 将指向 Sink-node 的资助边设为深黑色实线，以示强调
            highlight(p, 'Edges', to_sink_edges, 'EdgeColor', [0 0 0], ...
                      'LineWidth', 1.5, 'LineStyle', '-');
            
            % 4. 设置标题和坐标轴
            title(['Sink-node入度=', num2str(stage)]);
            axis off;
        end
    end
    
    % 计算当前阶段的平均值
    mean_ranks(stage + 1, :) = mean(temp_ranks);
end

%% --- 3. 结果分析图 ---
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

% --- 新增：输出所有点的平均 Rank 值表格 ---
fprintf('\n--- 随机连接实验报告 (1000次蒙特卡洛平均结果) ---\n');

% 构造表头，包含入度信息
RowNames = strcat('入度_', string(0:k));
ResultTableAll = array2table(mean_ranks, 'VariableNames', x_labels, 'RowNames', RowNames);

% 在终端显示完整表格
disp(ResultTableAll);

% 如果你想看更直观的数值分布，可以打印均值总结
fprintf('所有阶段各城市平均 Rank 值之和（稳定性指标）：\n');
SummaryTable = table(x_labels', mean(mean_ranks)', 'VariableNames', {'城市', '总平均Rank'});
disp(SummaryTable);