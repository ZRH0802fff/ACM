class LinearRegression:
    def __init__(self):
        self.w = None
        self.b = None

    def fit(self, X, y):
        n = len(X)
        mean_x = sum(X) / n
        mean_y = sum(y) / n

        numerator = sum((X[i] - mean_x) * (y[i] - mean_y) for i in range(n))
        denominator = sum((X[i] - mean_x) ** 2 for i in range(n))

        self.w = numerator / denominator
        self.b = mean_y - self.w * mean_x

    def predict(self, X):
        if isinstance(X, (int, float)):
            X = [X]
        return [self.w * x + self.b for x in X]

    def __call__(self, X):
        return self.predict(X)


if __name__ == "__main__":
    model = LinearRegression()

    X = [1, 2, 3]
    y = [2, 4, 6]

    model.fit(X, y)

    ans = model([4])
    print(ans)