from sklearn.linear_model import LinearRegression
import joblib

X = [[1], [2], [3]]
y = [2, 4, 6]

model = LinearRegression()
model.fit(X, y)

joblib.dump(model, 'linear.pkl')

loaded_model = joblib.load('linear.pkl')

ans = loaded_model.predict([[4]])
print(ans)