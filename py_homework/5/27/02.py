import json

config = {
    "model_name": "my_model",
    "learning_rate": 0.001,
    "optimizer": "adam",
    "dataset_path": "/path/to/dataset"
}

with open("config.json", "w", encoding="utf-8") as f:
    json.dump(config, f)


def update_config(key, value):
    with open("config.json", "r", encoding="utf-8") as f:
        data = json.load(f)

    data[key] = value

    with open("config.json", "w", encoding="utf-8") as f:
        json.dump(data, f)


# 测试调用
update_config("learning_rate", 0.05)