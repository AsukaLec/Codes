import torch
import time
import json
from datasets import load_dataset, Dataset
from transformers import AutoTokenizer, AutoModelForCausalLM
from trl import GRPOConfig, GRPOTrainer
import re
import string

# 1. 系统提示词
SYSTEM_PROMPT = (
    "You are a precise question-answering assistant." 
    "Provide the most concise answerpossible to the user's question." 
    "Your response MUST start with The answer is:  followed by the answer itself." 
    "Do not include any explanations, reasoning, or additional text. Only putput the required formatted answer."
)

# 2. 加载数据集
def get_local_hotpotqa(file_paths: list) -> Dataset:
    dataset = load_dataset("parquet", data_files={"train": file_paths}, split="train")
   
    def format_data(x):
        gold_answer = x['answer']
        
        lines = []
        for sentence in x['context']['sentences']:
            for line in sentence:
                lines.append(line)
        context = " ".join(lines)
        
        return {
            'prompt': [
                {'role': 'system', 'content': SYSTEM_PROMPT},
                {'role': 'user', 'content': f"Context: {context}\n\nQuestion: {x['question']}\n\nAnswer:"}
            ],
            'answer': gold_answer
        }

    return dataset.map(format_data)

# 3. 答案提取
def extract_direct_answer(text: str) -> str:
    # if "思考" in text or "thinking" in text.lower():
    #     text = re.sub(r'<think>.*?', '', text, flags=re.DOTALL)
    #     text = re.sub(r'思考.*?\n', '', text)
    
    lines = [line.strip() for line in text.strip().split('\n') if line.strip()]
    if not lines:
        return ""
        
    last_line = lines[-1]
    clean_answer = re.sub(r'^(the answer is|answer|it is|result is)[:\s]*', '', last_line, flags=re.IGNORECASE)
    return clean_answer.strip()

# 4. 标准 normalization
def normalize_answer(s):
    s = s.lower()
    s = ''.join(ch for ch in s if ch not in string.punctuation)
    s = ' '.join(s.split())
    return s

# 5. 奖励函数：简洁输出
def correctness_reward_func(prompts, completions, answer, **kwargs) -> list[float]:
    responses = [completion[0]['content'] for completion in completions]
    extracted_responses = [extract_direct_answer(r) for r in responses]
    
    rewards = []
    for r, a in zip(extracted_responses, answer):
        r_clean = normalize_answer(r)
        a_clean = normalize_answer(a)

        if r_clean == a_clean:
            reward = 1.0
        else:
            reward = 0.0

        rewards.append(reward)

    print(f"\n{'='*80}")
    print(f"Step | Batch: {len(prompts)} samples")
    print(f"{'='*80}")
    
    for i, (raw_response, extracted, gold, reward) in enumerate(
        zip(responses, extracted_responses, answer, rewards)
    ):
        status = "✓" if reward == 1.0 else "✗"
        print(f"\n[{status}] Sample {i+1} | Reward: {reward}")
        print(f"Raw Output: {raw_response}")
        print(f"Extracted: '{extracted}'")
        print(f"Gold:      '{gold}'")
    
    correct = sum(rewards)
    print(f"\nAccuracy: {correct}/{len(rewards)} ({100*correct/len(rewards):.1f}%)")
    print(f"{'='*80}")
    
    return rewards

# 6. 配置参数
model_name = "/data/LLM_MODEL/Qwen3-0.6B"
output_dir = "Qwen3-0.6B-GRPO-HotPotQA-Local"
local_parquet_path = ["hotpotqa/hotpotqa/train-00000-of-00002.parquet", 
                      "hotpotqa/hotpotqa/train-00001-of-00002.parquet"] 

training_args = GRPOConfig(
    output_dir=output_dir,
    run_name="qwen3-HotPotQA-local-direct",
    learning_rate=5e-6,
    adam_beta1=0.9,
    adam_beta2=0.99,
    weight_decay=0.1,
    warmup_steps=100,
    lr_scheduler_type='cosine',
    logging_steps=1,
    bf16=True,

    per_device_train_batch_size=1,
    gradient_accumulation_steps=4,
    num_generations=8, 
    max_completion_length=1024,
    max_prompt_length=4096,
    max_grad_norm=0.1,

    num_train_epochs=1,
    save_steps=100,
    report_to="none",
    use_vllm=False,
    log_completions=False,
)

# 7. 加载模型 & 数据集
dataset = get_local_hotpotqa(local_parquet_path)

model_qwen = AutoModelForCausalLM.from_pretrained(
    model_name,
    dtype=torch.bfloat16,
    device_map="auto"
)
if not hasattr(model_qwen, 'warnings_issued'):
    model_qwen.warnings_issued = {}

# 8. 训练
trainer = GRPOTrainer(
    model=model_qwen,
    reward_funcs=[correctness_reward_func],
    args=training_args,
    train_dataset=dataset
)
trainer.train()

# 9. 保存
trainer.save_model(output_dir)
print(f"Training complete! Model saved to {output_dir}")
