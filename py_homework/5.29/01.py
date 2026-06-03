import pymysql
import json
import random

conn = pymysql.connect(host='localhost', user='root', password='88888888')
cursor = conn.cursor()

cursor.execute("CREATE DATABASE IF NOT EXISTS ai_lab")
cursor.execute("USE ai_lab")

cursor.execute("""
CREATE TABLE IF NOT EXISTS results (
    id INT AUTO_INCREMENT PRIMARY KEY,
    model TEXT,
    params TEXT,
    accuracy FLOAT,
    train_time FLOAT
)
""")

records = [
    ("ResNet50", json.dumps({"lr": 0.01, "batch_size": 32}), 0.85, 120.5),
    ("VGG16", json.dumps({"lr": 0.001, "batch_size": 64}), 0.76, 180.2),
    ("MobileNet", json.dumps({"lr": 0.05, "batch_size": 128}), 0.91, 65.8)
]
cursor.executemany("INSERT INTO results (model, params, accuracy, train_time) VALUES (%s, %s, %s, %s)", records)
conn.commit()

cursor.execute("SELECT * FROM results WHERE accuracy > 0.8 ORDER BY accuracy DESC")
for row in cursor.fetchall():
    print(row)


def train_and_log(model_name, epochs):
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS logs (
        epoch INT,
        loss FLOAT,
        acc FLOAT
    )
    """)
    cursor.execute("TRUNCATE TABLE logs")

    for epoch in range(1, epochs + 1):
        loss = round(random.uniform(0.1, 0.9), 4)
        acc = round(random.uniform(0.5, 0.99), 4)
        cursor.execute("INSERT INTO logs (epoch, loss, acc) VALUES (%s, %s, %s)", (epoch, loss, acc))
    conn.commit()

    cursor.execute("SELECT * FROM logs")
    for row in cursor.fetchall():
        print(row)

train_and_log("My_Model", 5)

cursor.close()
conn.close()