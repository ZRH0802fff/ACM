import json

a = {
    "model_name": "my_model",
    "input_dim": 100,
    "hidden_dim": 50,
    "output_dim": 10,
    "activation": "sigmoid"
}

with open("model.json", "w") as f1:
    json.dump(a, f1)

with open("model.json", "r") as f2:
    b = json.load(f2)

print(b)

b["activation"] = "relu"

with open("model.json", "w") as f3:
    json.dump(b, f3)