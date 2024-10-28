import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
import random
import time

DIGITS = 1
OPERATOR = "+"
NUM_EQUATIONS = 5
N = 100

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

random.seed(time.time())

model_name = "eryk-mazus/polka-1.1b"

tokenizer = AutoTokenizer.from_pretrained(model_name, padding_side="left")
tokenizer.pad_token = tokenizer.eos_token

model = AutoModelForCausalLM.from_pretrained(
    model_name, device_map="auto")


def gen_equation(digits, operator):
    a = random.randint(0, 10**digits)
    b = random.randint(0, 10**digits)
    if operator == "+":
        return f"{a} {operator} {b} = {a + b}"
    elif operator == "-":
        return f"{a} {operator} {b} = {a - b}"
    elif operator == "*":
        return f"{a} {operator} {b} = {a * b}"
    elif operator == "/":
        return f"{a} {operator} {b} = {a / b}"


def gen_prompt(digits, operator, num_equations):
    prompt = ""
    for _ in range(num_equations):
        prompt += gen_equation(digits, operator) + "\n"
    end = prompt.rfind("=")
    return prompt[:end+1]


ops = ["ADD", "SUB", "MUL"]

for op in ops:
    OPERATOR = ["+", "-"][ops.index(op)]

    for digits in [2, 3]:
        DIGITS = digits

        for num_eq in [1, 2, 3, 4, 5, 10]:
            NUM_EQUATIONS = num_eq

            outFile = open(
                f"{op}/output_{DIGITS}_{NUM_EQUATIONS}.txt", "w")
            for i in range(N):
                prompt = gen_prompt(DIGITS, OPERATOR, NUM_EQUATIONS)
                model_inputs = tokenizer([prompt],
                                         return_tensors="pt").to(DEVICE)
                with torch.no_grad():
                    generated_ids = model.generate(
                        **model_inputs,
                        max_new_tokens=digits+1,
                        do_sample=True,
                        penalty_alpha=0.6,
                        pad_token_id=tokenizer.eos_token_id,
                        top_k=1
                    )

                output = tokenizer.batch_decode(
                    generated_ids, skip_special_tokens=True)[0]
                output = output.split("\n")[NUM_EQUATIONS-1]
                outFile.write(f"{output}\n")
                print(i)

            outFile.close()
