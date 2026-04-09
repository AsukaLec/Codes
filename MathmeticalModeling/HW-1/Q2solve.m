clear; clc; close all;

%% --- 1. 用户输入信息 ---
P_vector = [1, 1, 0, 1, 1, 0, 1]; 
c_orig   = [7, 4, 3, 9, 8, 5, 4]; 
x_labels = {'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7'};

%% --- 2. 参数初始化 ---
N = length(P_vector);
d = 0.85;                        
selected_idx = find(P_vector == 1); 
sink_idx = find(P_vector == 0);
max_in = length(selected_idx);   

all_ranks = zeros(max_in + 1, N); 

% 创建一个大画布用来画网络拓扑图
figure('Color', 'w', 'Name', 'Network Topology Evolution');

%% --- 3. 核心计算循环 ---
for in_deg = 0:max_in
    A = zeros(N, N); 
    
    for j = 1:N
        if P_vector(j) == 1
            targets = setdiff(selected_idx, j);
            current_pos_in_P = find(selected_idx == j);
            if current_pos_in_P <= in_deg
                targets = [targets, sink_idx];
            end
            if ~isempty(targets)
                A(targets, j) = 1 / length(targets);
            end
        else
            A(:, j) = 0; % Sink Node 无出度
        end
    end

    % --- Step 3.5: 绘制当前情况下的网络图 ---
    subplot(2, 3, in_deg + 1); % 创建 2x3 的子图布局
    G = digraph(A', x_labels); % 注意 A' 是因为 digraph 默认行是起点
    
    % 设置节点颜色：选中城市为绿色，Sink Node 为红色
    node_colors = repmat([0.2 0.6 0.2], N, 1); % 默认绿色
    node_colors(sink_idx, :) = repmat([0.8 0.2 0.2], length(sink_idx), 1); % Sink设为红色
    
    p = plot(G, 'Layout', 'circle', 'NodeColor', node_colors, ...
             'MarkerSize', 8, 'LineWidth', 1, 'ArrowSize', 10);
    title(['Sink Node 入度 = ', num2str(in_deg)]);
    axis off;

    % --- 迭代求解 PageRank ---
    R = c_orig'; 
    for iter = 1:100
        R_new = d * A * R + ((1 - d) / N) * sum(c_orig) * ones(N, 1);
        if norm(R_new - R, 1) < 1e-6
            break;
        end
        R = R_new;
    end
    all_ranks(in_deg + 1, :) = R';
end

%% --- 4. 结果可视化与报表 ---

% 绘制灵敏度曲线（这会开第二个窗口）
figure('Color', 'w', 'Name', 'PageRank Sensitivity Analysis');
plot(0:max_in, all_ranks, '-o', 'LineWidth', 2, 'MarkerSize', 6);
grid on;
xlabel('选中城市中指向 Sink Node 的数量 (in-degree)');
ylabel('最终 Rank 值');
title('灵敏度分析：Sink Node 接入程度对城市重要性的影响');
legend(x_labels, 'Location', 'northeastoutside');

% 打印对比表
fprintf('--- PageRank 灵敏度分析报告 ---\n');
disp(table((0:max_in)', all_ranks, 'VariableNames', {'In_Degree', 'Ranks_A1_to_A7'}));