
%% --- 1. 用户输入信息 ---
% 假设 A6 不存在，我们只保留 6 个城市进行分析
% 原 A1, A2, A3(Sink), A4, A5, A7 -> 重新映射为 1, 2, 3, 4, 5, 6
P_vector = [1, 1, 0, 1, 1, 1];     % 只有索引 3 是 Sink Node
c_orig   = [7, 4, 3, 9, 8, 4];     % 对应的初始利润 (去掉了原 A6 的 5)
x_labels = {'A1', 'A2', 'A3(Sink)', 'A4', 'A5', 'A7'};

%% --- 2. 参数初始化 ---
N = length(P_vector);
d = 0.85;                        
selected_idx = find(P_vector == 1); 
sink_idx = find(P_vector == 0);    % 仅包含 A3
max_in = length(selected_idx);     % 最大入度为 5 (A1,A2,A4,A5,A7)

all_ranks = zeros(max_in + 1, N); 

% 创建画布：展示拓扑演变
figure('Color', 'w', 'Name', 'Single Sink Node Topology Evolution', 'Position', [100, 100, 1000, 600]);

%% --- 3. 核心计算循环 ---
for in_deg = 0:max_in
    A = zeros(N, N); 
    
    for j = 1:N
        if P_vector(j) == 1
            % 选中城市的目标：其他选中的小伙伴
            targets = setdiff(selected_idx, j);
            
            % 按照入度顺序，决定当前城市 j 是否指向唯一的 Sink Node (A3)
            current_pos_in_P = find(selected_idx == j);
            if current_pos_in_P <= in_deg
                targets = [targets, sink_idx];
            end
            
            if ~isempty(targets)
                A(targets, j) = 1 / length(targets);
            end
        else
            % Sink Node A3：严格无出度
            A(:, j) = 0; 
        end
    end

    % --- 绘制网络图 ---
    subplot(2, 3, in_deg + 1); 
    G = digraph(A', x_labels); % 转置矩阵以匹配 digraph 起点逻辑
    
    % 节点颜色：选中城市为深青色，Sink Node 为鲜红色
    node_colors = repmat([0 0.45 0.74], N, 1); 
    node_colors(sink_idx, :) = repmat([1 0 0], length(sink_idx), 1); 
    
    p = plot(G, 'Layout', 'force', 'NodeColor', node_colors, ...
             'MarkerSize', 10, 'LineWidth', 1.2, 'ArrowSize', 12);
    title(['A3 接收来自 ', num2str(in_deg), ' 个城市的输入']);
    axis off;

    % --- 迭代求解 PageRank ---
    R = c_orig'; 
    for iter = 1:100
        % 能量补偿公式：d*A*R + (1-d)/N * 总能量
        R_new = d * A * R + ((1 - d) / N) * sum(c_orig) * ones(N, 1);
        if norm(R_new - R, 1) < 1e-6
            break;
        end
        R = R_new;
    end
    all_ranks(in_deg + 1, :) = R';
end

%% --- 4. 结果可视化与报表 ---

% 绘制灵敏度分析折线图
figure('Color', 'w', 'Name', 'PageRank Sensitivity Analysis (Single Sink)');
plot(0:max_in, all_ranks, '-p', 'LineWidth', 2, 'MarkerSize', 8);
grid on;
set(gca, 'FontSize', 12);
xlabel('指向 A3 的选中城市数量', 'FontWeight', 'bold');
ylabel('平衡状态下的 Rank 值', 'FontWeight', 'bold');
title('单一 Sink Node (A3) 接入程度对全网排名的影响');
legend(x_labels, 'Location', 'northeastoutside');

% 打印简报
fprintf('\n--- 单一 Sink Node 实验报告 ---\n');
disp(table((0:max_in)', all_ranks, 'VariableNames', {'入度', '各城市最终Rank值'}));