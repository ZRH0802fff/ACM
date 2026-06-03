class MyDataset:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __len__(self):
        return len(self.x)

    def __getitem__(self, idx):
        return self.x[idx], self.y[idx]


class DataLoader:
    def __init__(self, dataset, batch_size):
        self.dataset = dataset
        self.batch_size = batch_size
        self.index = 0

    def __iter__(self):
        self.index = 0
        return self

    def __next__(self):
        if self.index >= len(self.dataset):
            raise StopIteration

        batch = []
        end_idx = min(self.index + self.batch_size, len(self.dataset))
        for i in range(self.index, end_idx):
            batch.append(self.dataset[i])
            self.index += 1

        return batch


if __name__ == "__main__":
    x = [1, 2, 3]
    y = [2, 4, 6]
    dataset = MyDataset(x, y)

    loader = DataLoader(dataset, batch_size=2)

    for batch in loader:
        print(batch)