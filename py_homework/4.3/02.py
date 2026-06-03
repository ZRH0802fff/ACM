features = [0.2, 0.5, 0.8, 0.3, 0.9, 0.1]

print(features[:3])

print(features[-2:])

print(features[::2])

indexed_features = list(enumerate(features))
sorted_features = sorted(indexed_features, key=lambda x: x[1], reverse=True)
top_3_indices = [item[0] for item in sorted_features[:3]]
print(top_3_indices)