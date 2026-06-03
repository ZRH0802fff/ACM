def create_config(**kwargs):
    c = {
        "learning_rate": 0.001,
        "batch_size": 32,
        "epochs": 10
    }
    c.update(kwargs)
    return c

ans = create_config(learning_rate=0.01, dropout=0.5)
print(ans)