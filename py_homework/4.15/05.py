model_config = {
    "model_name": "ResNet50",
    "input_size": 224,
    "num_classes": 1000,
    "learning_rate": 0.001,
    "batch_size": 32,
    "optimizer": "SGD"
}

def update_config(config, updates):
    """返回更新后的新配置字典，原字典不变"""
    new_config = config.copy()  
    new_config.update(updates)
    return new_config

updates_dict = {
    "learning_rate": 0.0001,
    "momentum": 0.9
}

new_config = update_config(model_config, updates_dict)

print("原始配置:")
print(model_config)
print("\n更新后的配置:")
print(new_config)