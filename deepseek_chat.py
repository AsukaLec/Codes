from openai import OpenAI

client = OpenAI(
    api_key="sk-f9f70760d3e043589968f2b8548c4fbe",
    base_url="https://api.deepseek.com/v1"
)

def chat(message: str) -> str:
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=[{"role": "user", "content": message}]
    )
    return response.choices[0].message.content

if __name__ == "__main__":
    while True:
        user_input = input("You: ")
        if user_input.lower() in ["quit", "exit"]:
            break
        print(f"DeepSeek: {chat(user_input)}")
