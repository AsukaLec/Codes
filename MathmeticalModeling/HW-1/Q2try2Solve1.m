clear; clc; close all;

%% --- 1. 基础数据 ---
P_vector = [1, 1, 0, 1, 1, 0, 1]; % A3(3), A6(6) 是 Sink Nodes
c_orig   = [7, 4, 3, 9, 8, 5, 4]; % 初始利润 Ci
x_labels = {'A1', 'A2', 'A3(S)', 'A4', 'A5', 'A6(S)', 'A7'};

N = length(P_vector);
d = 0.85;                        
selected_idx = find(P_vector == 1); % [1, 2, 4, 5, 7]
k = length(selected_idx);           % 选中城市共 5 个

all_ranks = zeros(k + 1, N); 

% 准备画布
figure('Color', 'w', 'Name', 'Disjoint Sink Connectivity', 'Position', [100, 100, 1200, 700]);

%% --- 2. 核心演化循环 ---
for stage = 0:k
    A = zeros(N, N); 
    
    % 确定当前阶段 A3 和 A6 分别被哪些活跃城市连接
    % A3 选前 stage 个，A6 选后 stage 个
    targets_for_A3 = selected_idx(1:stage);
    targets_for_A6 = selected_idx(end-stage+1:end);
    
    for j = 1:N
        if P_vector(j) == 1
            % 基础连接：选中城市之间的内循环
            targets = setdiff(selected_idx, j);
            
            % --- 错位连接逻辑 ---
            % 检查当前城市 j 是否在 A3 的帮扶名单里
            if ismember(j, targets_for_A3)
                targets = [targets, 3]; 
            end
            % 检查当前城市 j 是否在 A6 的帮扶名单里
            if ismember(j, targets_for_A6)
                targets = [targets, 6]; 
            end
            
            % 归一化分配（确保列和为1或0）
            targets = unique(targets);
            if ~isempty(targets)
                A(targets, j) = 1 / length(targets);
            end
        else
            % Sink Nodes 严格无出度
            A(:, j) = 0; 
        end
    end

    % --- 验证入度是否严格同步 ---
    in_deg_A3 = sum(A(3, :) > 0);
    in_deg_A6 = sum(A(6, :) > 0);
    fprintf('阶段 %d: A3入度=%d, A6入度=%d\n', stage, in_deg_A3, in_deg_A6);

    % --- 绘制拓扑图 ---
    subplot(2, 3, stage + 1);
    G = digraph(A', x_labels);
    
    node_colors = repmat([0.2 0.4 0.6], N, 1); 
    node_colors(3, :) = [0.8 0.2 0.2]; % A3 红色
    node_colors(6, :) = [0.2 0.7 0.2]; % A6 绿色
    
    plot(G, 'Layout', 'circle', 'NodeColor', node_colors, ...
         'MarkerSize', 10, 'LineWidth', 1.2, 'ArrowSize', 10);
    title(['阶段 ', num2str(stage), ' (入度均为', num2str(stage), ')']);
    axis off;

    % --- PageRank 迭代 ---
    R = c_orig'; 
    for iter = 1:100
        R_new = d * A * R + ((1 - d) / N) * sum(c_orig) * ones(N, 1);
        if norm(R_new - R, 1) < 1e-6, break; end
        R = R_new;
    end
    all_ranks(stage + 1, :) = R';
end

%% --- 3. 结果分析图 ---
figure('Color', 'w', 'Name', 'Rank Differentiation Plot');
plot(0:k, all_ranks, '-o', 'LineWidth', 2, 'MarkerSize', 6);
grid on;
set(gca, 'XTick', 0:k);
xlabel('同步增长的入度数量');
ylabel('最终 Rank 值');
title('入度同步但来源错位下的城市排名分化');
legend(x_labels, 'Location', 'northeastoutside');

% 打印对比数据
fprintf('\n--- A3 vs A6 排名分化表 ---\n');
disp(table((0:k)', all_ranks(:,3), all_ranks(:,6), ...
    'VariableNames', {'入度', 'A3_Rank', 'A6_Rank'}));